#include "BTreeNode.h"

using namespace std;

/*
 * Read the content of the node from the page pid in the PageFile pf.
 * @param pid[IN] the PageId to read
 * @param pf[IN] PageFile to read from
 * @return 0 if successful. Return an error code if there is an error.
 */
void BTLeafNode::printNode(){
	int size = *(reinterpret_cast<int*>(buffer));
	printf("Printing Node size: %d\n", size);
	char* startAddr = buffer + sizeof(int);
	LeafNodeEntry *currentEntry = reinterpret_cast<LeafNodeEntry *>(startAddr);
	for (int i=0; i < keyCount; i++){
		printf("Printing entry at addr %p\n", (void *)currentEntry);
		printf("Entry, key: %d pageId:%d slotId: %d\n", currentEntry->key, (currentEntry->recordId).pid, (currentEntry->recordId).sid);
		currentEntry++;
	}
	printf("\n");
}

RC BTLeafNode::read(PageId pid, const PageFile& pf)
{
	RC errcode;
	errcode = pf.read(pid, buffer);
	keyCount = 0;

	return errcode;
}
    
/*
 * Write the content of the node to the page pid in the PageFile pf.
 * @param pid[IN] the PageId to write to
 * @param pf[IN] PageFile to write to
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTLeafNode::write(PageId pid, PageFile& pf)
{ 
	return pf.write(pid,buffer);
}

/*
 * Return the number of keys stored in the node.
 * @return the number of keys in the node
 */
int BTLeafNode::getKeyCount()
{
	if (keyCount == 0){
		int numKeys = *(reinterpret_cast<int*>(buffer));
		keyCount = numKeys;
	}
	return keyCount;
}

/*
 * Insert a (key, rid) pair to the node.
 * @param key[IN] the key to insert
 * @param rid[IN] the RecordId to insert
 * @return 0 if successful. Return an error code if the node is full.
 */
RC BTLeafNode::insert(int key, const RecordId& rid)
{ 
	char* startAddr = buffer + sizeof(int);
	LeafNodeEntry *currentEntry = reinterpret_cast<LeafNodeEntry *>(startAddr);
	int currentKey = 0;
	while(currentKey < keyCount && currentEntry->key < key){
		currentEntry++;
		currentKey++;
	}
	LeafNodeEntry *newEntry = currentEntry;
	memmove(currentEntry + 1, currentEntry, (keyCount - currentKey) * sizeof(LeafNodeEntry));
	newEntry->recordId = rid;
	newEntry->key = key;
	keyCount++;
	*(reinterpret_cast<int*>(buffer)) = keyCount;
	return 0; 
}

/*
 * Insert the (key, rid) pair to the node
 * and split the node half and half with sibling.
 * The first key of the sibling node is returned in siblingKey.
 * @param key[IN] the key to insert.
 * @param rid[IN] the RecordId to insert.
 * @param sibling[IN] the sibling node to split with. This node MUST be EMPTY when this function is called.
 * @param siblingKey[OUT] the first key in the sibling node after split.
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTLeafNode::insertAndSplit(int key, const RecordId& rid, 
                              BTLeafNode& sibling, int& siblingKey)
{ return 0; }

/**
 * If searchKey exists in the node, set eid to the index entry
 * with searchKey and return 0. If not, set eid to the index entry
 * immediately after the largest index key that is smaller than searchKey,
 * and return the error code RC_NO_SUCH_RECORD.
 * Remember that keys inside a B+tree node are always kept sorted.
 * @param searchKey[IN] the key to search for.
 * @param eid[OUT] the index entry number with searchKey or immediately
                   behind the largest key smaller than searchKey.
 * @return 0 if searchKey is found. Otherwise return an error code.
 */
RC BTLeafNode::locate(int searchKey, int& eid)
{ 
	int currKey, keyIdx;
	RC errcode;
	char* startAddr = buffer + sizeof(int);
	LeafNodeEntry *currentEntry = reinterpret_cast<LeafNodeEntry *>(startAddr);
	keyIdx = 0;
	errcode = 0;
	while (keyIdx < keyCount){
		currKey = currentEntry->key;
		if (currKey == searchKey){
			eid = keyIdx;
			break;
		}
		else if (currKey > searchKey){
			//if (keyIdx > 0) currentEntry--;
			eid = keyIdx;
			errcode = RC_NO_SUCH_RECORD;
			break;
		}
		currentEntry++;
		keyIdx++;
	}
	return errcode; 
}

/*
 * Read the (key, rid) pair from the eid entry.
 * @param eid[IN] the entry number to read the (key, rid) pair from
 * @param key[OUT] the key from the entry
 * @param rid[OUT] the RecordId from the entry
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTLeafNode::readEntry(int eid, int& key, RecordId& rid)
{ 
	RC errcode;
	if (eid > 0 && eid < keyCount){
		char* startAddr = buffer + sizeof(int);
		LeafNodeEntry *firstEntry = reinterpret_cast<LeafNodeEntry *>(startAddr);
		LeafNodeEntry *readEntry = firstEntry + eid;
		key = readEntry->key;
		rid = readEntry->recordId;
		errcode = 0;
	}
	else {
		errcode = RC_NO_SUCH_RECORD;
	}
	return errcode; 
}

/*
 * Return the pid of the next slibling node.
 * @return the PageId of the next sibling node 
 */
PageId BTLeafNode::getNextNodePtr()
{ 
	int* lastNode = reinterpret_cast<int *>((buffer + PageFile::PAGE_SIZE) - sizeof(int));
	return *lastNode;
}

/*
 * Set the pid of the next slibling node.
 * @param pid[IN] the PageId of the next sibling node 
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTLeafNode::setNextNodePtr(PageId pid)
{ 
	int* lastNode = reinterpret_cast<int *>((buffer + PageFile::PAGE_SIZE) - sizeof(int));
	*lastNode = pid;
	return 0; 
}

/*
 * Read the content of the node from the page pid in the PageFile pf.
 * @param pid[IN] the PageId to read
 * @param pf[IN] PageFile to read from
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTNonLeafNode::read(PageId pid, const PageFile& pf)
{ return 0; }
    
/*
 * Write the content of the node to the page pid in the PageFile pf.
 * @param pid[IN] the PageId to write to
 * @param pf[IN] PageFile to write to
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTNonLeafNode::write(PageId pid, PageFile& pf)
{ return 0; }

/*
 * Return the number of keys stored in the node.
 * @return the number of keys in the node
 */
int BTNonLeafNode::getKeyCount()
{ return 0; }


/*
 * Insert a (key, pid) pair to the node.
 * @param key[IN] the key to insert
 * @param pid[IN] the PageId to insert
 * @return 0 if successful. Return an error code if the node is full.
 */
RC BTNonLeafNode::insert(int key, PageId pid)
{ return 0; }

/*
 * Insert the (key, pid) pair to the node
 * and split the node half and half with sibling.
 * The middle key after the split is returned in midKey.
 * @param key[IN] the key to insert
 * @param pid[IN] the PageId to insert
 * @param sibling[IN] the sibling node to split with. This node MUST be empty when this function is called.
 * @param midKey[OUT] the key in the middle after the split. This key should be inserted to the parent node.
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTNonLeafNode::insertAndSplit(int key, PageId pid, BTNonLeafNode& sibling, int& midKey)
{ return 0; }

/*
 * Given the searchKey, find the child-node pointer to follow and
 * output it in pid.
 * @param searchKey[IN] the searchKey that is being looked up.
 * @param pid[OUT] the pointer to the child node to follow.
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTNonLeafNode::locateChildPtr(int searchKey, PageId& pid)
{ return 0; }

/*
 * Initialize the root node with (pid1, key, pid2).
 * @param pid1[IN] the first PageId to insert
 * @param key[IN] the key that should be inserted between the two PageIds
 * @param pid2[IN] the PageId to insert behind the key
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTNonLeafNode::initializeRoot(PageId pid1, int key, PageId pid2)
{ return 0; }
