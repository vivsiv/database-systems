/*
 * Copyright (C) 2008 by The Regents of the University of California
 * Redistribution of this file is permitted under the terms of the GNU
 * Public License (GPL).
 *
 * @author Junghoo "John" Cho <cho AT cs.ucla.edu>
 * @date 3/24/2008
 */
 
#include "BTreeIndex.h"
#include "BTreeNode.h"
#include <iostream>
#include <fstream>

using namespace std;

/*
 * BTreeIndex constructor
 */
BTreeIndex::BTreeIndex()
{
    rootPid = -1;
}

void BTreeIndex::printTree(){
	BTNonLeafNode root;
	printf("Printing Tree at rootPage: %d\n", rootPid);
	root.read(rootPid, pf);
	root.printNode();
	// PageId child1 page;
	// BTLeafNode child1 = root.locateChildPtr();
}

BTreeIndex::rootPageHeader* BTreeIndex::getRootHeader(){
	return reinterpret_cast<rootPageHeader*>(buffer);
}

void BTreeIndex::initRoot(){
	rootPageHeader* rpHeader = getRootHeader();
	rootPid = rpHeader->rPid;
	treeHeight = rpHeader->height;
	printf("Found root:%d and height:%d in index info page\n", rootPid, treeHeight);
}

void BTreeIndex::setTreeHeight(int height){
	treeHeight = height;
	rootPageHeader* rpHeader = getRootHeader();
	rpHeader->height = height;
	pf.write(INDEX_INFO,buffer);
}

void BTreeIndex::setRootPage(PageId rootPage){
	rootPid = rootPage;
	rootPageHeader* rpHeader = getRootHeader();
	rpHeader->rPid = rootPage;
	pf.write(INDEX_INFO,buffer);
}

/*
 * Open the index file in read or write mode.
 * Under 'w' mode, the index file should be created if it does not exist.
 * @param indexname[IN] the name of the index file
 * @param mode[IN] 'r' for read, 'w' for write
 * @return error code. 0 if no error
 */
RC BTreeIndex::open(const string& indexname, char mode)
{
	RC status;
	const string ifilename = indexname + ".idx";

	status = pf.open(ifilename, mode);
	status = pf.read(INDEX_INFO,buffer);
	printf("End pid is %d\n", pf.endPid());
	if (pf.endPid() == INDEX_INFO){
		rootPid = 1;
		treeHeight = 1;
	}
	else {
		initRoot();
	}
	status = pf.read(rootPid, buffer);
    return status;
}

/*
 * Close the index file.
 * @return error code. 0 if no error
 */
RC BTreeIndex::close()
{
	RC status;
	status = pf.close();
    return status;
}

/*
 * Insert (key, RecordId) pair to the index.
 * @param key[IN] the key for the value inserted into the index
 * @param rid[IN] the RecordId for the record being inserted into the index
 * @return error code. 0 if no error
 */
RC BTreeIndex::insert(int key, const RecordId& rid)
{
	RC errcode;
	IndexCursor cursor;
	locate(key, cursor);
	BTLeafNode node;
	node.read(cursor.pid,pf);
	//printf("Have Node of size %d\n",node.getKeyCount());
	printf("Node Before Insert (page:%d)..\n", cursor.pid);
	node.printNode();
	printf("\n");
	if (node.getKeyCount() == node.MAX_NODE_SIZE){
		int siblingKey;
		BTLeafNode sibling;
		sibling.read(pf.endPid(), pf);

		printf("Leaf Split Happens\n");
		node.insertAndSplit(key, rid, sibling, siblingKey);

		node.write(node.getPageId(), pf);
		sibling.write(sibling.getPageId(), pf);
		
		propagateLeaf(siblingKey, node.getParent(), node, sibling, treeHeight);

		// BTNonLeafNode parent;
		// if (treeHeight == 1){
		// 	parent.read(pf.endPid(), pf);
		// 	parent.initializeRoot(node.getPageId(), siblingKey, sibling.getPageId());
		// 	parent.write(parent.getPageId(), pf);

		// 	setTreeHeight(treeHeight + 1);
		// 	setRootPage(parent.getPageId());

		// 	node.setParent(parent.getPageId());
		// 	node.write(node.getPageId(), pf);

		// 	sibling.setParent(parent.getPageId());
		// 	sibling.write(sibling.getPageId(), pf);
			

		// 	printf("Split Happens\n");
		// 	printf("Parent on page:%d...", parent.getPageId());
		// 	parent.printNode();
		// 	printf("\n");
		// 	printf("Child1 on page:%d...", node.getPageId());
		// 	node.printNode();
		// 	printf("\n");
		// 	printf("Child2 on page:%d...", sibling.getPageId());
		// 	sibling.printNode();
		// 	printf("\n");
		// }
		// else {
		// 	int currentHeight = treeHeight - 1;
		// 	PageId parentPage = node.getParent();
		// 	sibling.setParent(parentPage);
		// 	sibling.write(sibling.getPageId(), pf);
		// 	while (currentHeight > 0){
		// 		parent.read(parentPage, pf);
		// 		if (parent.getKeyCount() == node.MAX_NODE_SIZE){
		// 			parent.insertAndSplit(siblinkgKey, sibling.getPageId())
		// 		}
		// 		else {
		// 			parent.insert(siblingKey,sibling.getPageId());
		// 			break;
		// 		}
		// 	}
		// }
	}
	else {
		node.insert(key,rid);
		if (treeHeight == 1) node.setParent(BTLeafNode::NO_PARENT);
		node.write(node.getPageId(),pf);
		printf("Inserted Leaf Node at (page:%d)\n", node.getPageId());
		node.printNode();
	}
    return 0;
}

void setLeafParents(BTNonLeafNode& parent){
	BTLeafNode child;

}

void BTreeIndex::propagateLeaf(int key, PageId parentPage, BTLeafNode& node, BTLeafNode& sibling, int currHeight){
	BTNonLeafNode parent;
	if (parentPage == BTLeafNode::NO_PARENT){
		parent.read(pf.endPid(), pf);
		parent.initializeRoot(node.getPageId(), key, sibling.getPageId());
		parent.write(parent.getPageId(), pf);

		setTreeHeight(treeHeight + 1);
		setRootPage(parent.getPageId());

		node.setParent(parent.getPageId());
		node.write(node.getPageId(), pf);

		sibling.setParent(parent.getPageId());
		sibling.write(sibling.getPageId(), pf);

		printf("Parent on page:%d...", parent.getPageId());
		parent.printNode();
		printf("\n");
		printf("Child1 on page:%d...", node.getPageId());
		node.printNode();
		printf("\n");
		printf("Child2 on page:%d...", sibling.getPageId());
		sibling.printNode();
		printf("\n");
		return;
	}
	else {
		parent.read(parentPage, pf);
		printf("Parent keys: %d\n", parent.getKeyCount());
		if (parent.getKeyCount() == parent.MAX_NODE_SIZE){
			BTNonLeafNode parentSibling;
			parentSibling.read(pf.endPid(), pf);
			int parentMidKey;

			printf("Non Leaf Split Happens\n");
			parent.insertAndSplit(key, sibling.getPageId(), parentSibling, parentMidKey);

			parent.write(parent.getPageId(), pf);
			parentSibling.write(parentSibling.getPageId(), pf);
			
			parentSibling.setLeafChildParent(pf);
			//sibling.getPageId() == parent.getLastPointer() ? sibling.setParent(parent.getPageId()) : sibling.setParent(parentSibling.getPageId());
			//sibling.write(sibling.getPageId(), pf);
			//set last parent pointers

			printf("Leaf parents were split\n");
			// printf("Parent on page:%d...", parent.getPageId());
			// parent.printNode();
			// printf("\n");
			// printf("Parent Sibling on page:%d...", parentSibling.getPageId());
			// parentSibling.printNode();
			// printf("\n");
			printf("Child1 on page:%d...", node.getPageId());
			node.printNode();
			printf("\n");
			printf("Child2 on page:%d...", sibling.getPageId());
			sibling.printNode();
			printf("\n");
			return propagateNonLeaf(parentMidKey, parent.getParent(), parent, parentSibling, currHeight - 1);
		}
		else {
			parent.insert(key, sibling.getPageId());
			parent.write(parent.getPageId(), pf);
			sibling.setParent(parent.getPageId());
			sibling.write(sibling.getPageId(),pf);

			printf("Parent on page:%d...", parent.getPageId());
			parent.printNode();
			printf("\n");
			printf("Child1 on page:%d...", node.getPageId());
			node.printNode();
			printf("\n");
			printf("Child2 on page:%d...", sibling.getPageId());
			sibling.printNode();
			printf("\n");
			return;
		}
	}
}

void BTreeIndex::propagateNonLeaf(int key, PageId parentPage, BTNonLeafNode& node, BTNonLeafNode& sibling, int currHeight){
	BTNonLeafNode parent;
	if (parentPage == BTNonLeafNode::NO_PARENT){
		printf("New parent page:%d\n", pf.endPid());
		parent.read(pf.endPid(), pf);
		parent.initializeRoot(node.getPageId(), key, sibling.getPageId());
		parent.write(parent.getPageId(), pf);

		setTreeHeight(treeHeight + 1);
		setRootPage(parent.getPageId());

		node.setParent(parent.getPageId());
		node.write(node.getPageId(), pf);

		sibling.setParent(parent.getPageId());
		sibling.write(sibling.getPageId(), pf);

		printf("Parent on page:%d...", parent.getPageId());
		parent.printNode();
		printf("\n");
		printf("Child1 on page:%d...", node.getPageId());
		node.printNode();
		printf("\n");
		printf("Child2 on page:%d...", sibling.getPageId());
		sibling.printNode();
		printf("\n");
		return;
	}
	else {
		parent.read(parentPage, pf);
		if (parent.getKeyCount() == parent.MAX_NODE_SIZE){
			BTNonLeafNode parentSibling;
			parentSibling.read(pf.endPid(), pf);
			int parentMidKey;

			printf("Non Leaf Split Happens\n");
			parent.insertAndSplit(key, sibling.getPageId(), parentSibling, parentMidKey);
			parent.write(parent.getPageId(), pf);
			parentSibling.write(parentSibling.getPageId(), pf);
			
			parentSibling.setNonLeafChildParent(pf);
			//sibling.getPageId() == parent.getLastPointer() ? sibling.setParent(parent.getPageId()) : sibling.setParent(parentSibling.getPageId());
			//sibling.write(sibling.getPageId(), pf);

			printf("Parents getting split\n");
			// printf("Parent on page:%d...", parent.getPageId());
			// parent.printNode();
			// printf("\n");
			// printf("Parent Sibling on page:%d...", parentSibling.getPageId());
			// parentSibling.printNode();
			// printf("\n");
			printf("Child1 on page:%d...", node.getPageId());
			node.printNode();
			printf("\n");
			printf("Child2 on page:%d...", sibling.getPageId());
			sibling.printNode();
			printf("\n");
			//set last parent pointers
			return propagateNonLeaf(parentMidKey, parent.getParent(), parent, parentSibling, currHeight - 1);
		}
		else {
			parent.insert(key, sibling.getPageId());
			parent.write(parent.getPageId(), pf);
			sibling.setParent(parent.getPageId());
			sibling.write(sibling.getPageId(),pf);

			printf("Parent on page:%d...", parent.getPageId());
			parent.printNode();
			printf("\n");
			printf("Child1 on page:%d...", node.getPageId());
			node.printNode();
			printf("\n");
			printf("Child2 on page:%d...", sibling.getPageId());
			sibling.printNode();
			printf("\n");
			return;
		}
	}
}


/**
 * Run the standard B+Tree key search algorithm and identify the
 * leaf node where searchKey may exist. If an index entry with
 * searchKey exists in the leaf node, set IndexCursor to its location
 * (i.e., IndexCursor.pid = PageId of the leaf node, and
 * IndexCursor.eid = the searchKey index entry number.) and return 0.
 * If not, set IndexCursor.pid = PageId of the leaf node and
 * IndexCursor.eid = the index entry immediately after the largest
 * index key that is smaller than searchKey, and return the error
 * code RC_NO_SUCH_RECORD.
 * Using the returned "IndexCursor", you will have to call readForward()
 * to retrieve the actual (key, rid) pair from the index.
 * @param key[IN] the key to find
 * @param cursor[OUT] the cursor pointing to the index entry with
 *                    searchKey or immediately behind the largest key
 *                    smaller than searchKey.
 * @return 0 if searchKey is found. Othewise an error code
 */
RC BTreeIndex::locate(int searchKey, IndexCursor& cursor)
{
	RC errcode;
	BTLeafNode found = traverse(searchKey, rootPid, treeHeight);
	cursor.pid = found.getPageId();
	errcode = found.locate(searchKey, cursor.eid);
    return errcode;
}

BTLeafNode BTreeIndex::traverse(int searchKey, PageId pid, int currHeight){
	if (currHeight == 1){
		BTLeafNode found;
		found.read(pid,pf);
		return found;
	}
	BTNonLeafNode nl;
	nl.read(pid, pf);
	//nl.printNode();
	nl.locateChildPtr(searchKey, pid);
	return traverse(searchKey, pid, currHeight - 1);
}

/*
 * Read the (key, rid) pair at the location specified by the index cursor,
 * and move foward the cursor to the next entry.
 * @param cursor[IN/OUT] the cursor pointing to an leaf-node index entry in the b+tree
 * @param key[OUT] the key stored at the index cursor location.
 * @param rid[OUT] the RecordId stored at the index cursor location.
 * @return error code. 0 if no error
 */
RC BTreeIndex::readForward(IndexCursor& cursor, int& key, RecordId& rid)
{
	RC errcode;
	BTLeafNode ln;
	ln.read(cursor.pid, pf);
	errcode = ln.readEntry(cursor.eid,key,rid);
    return errcode;
}
