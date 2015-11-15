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
}

void BTreeIndex::setTreeHeight(int height){
	treeHeight = height;
	rootPageHeader* rpHeader = getRootHeader();
	rpHeader->height = height;
}

void BTreeIndex::setRootPage(PageId rootPage){
	rootPid = rootPage;
	rootPageHeader* rpHeader = getRootHeader();
	rpHeader->rPid = rootPage;
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

	status = pf.open(ifilename, 'w');
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
	printf("Located Node, page:%d\n", cursor.pid);
	BTLeafNode node;
	node.read(cursor.pid,pf);
	//printf("Have Node of size %d\n",node.getKeyCount());
	node.printNode();
	if (node.getKeyCount() == node.MAX_NODE_SIZE){
		int siblingKey;
		BTLeafNode sibling;
		sibling.read(pf.endPid(), pf);

		node.insertAndSplit(key, rid, sibling, siblingKey);

		node.write(node.getPageId(), pf);
		sibling.write(sibling.getPageId(), pf);

		BTNonLeafNode parent;
		if (treeHeight == 1){
			parent.read(pf.endPid(), pf);
			parent.initializeRoot(node.getPageId(), siblingKey, sibling.getPageId());
			parent.write(parent.getPageId(), pf);

			setTreeHeight(treeHeight + 1);
			setRootPage(parent.getPageId());

			node.setParent(parent.getPageId());
			node.write(node.getPageId(), pf);

			sibling.setParent(parent.getPageId());
			sibling.write(sibling.getPageId(), pf);
			

			printf("Split Happens\n");
			printf("Parent on page:%d...", parent.getPageId());
			parent.printNode();
			printf("\n");
			printf("Child1 on page:%d...", node.getPageId());
			node.printNode();
			printf("\n");
			printf("Child2 on page:%d...", sibling.getPageId());
			sibling.printNode();
			printf("\n");
		}
		else {
			// int currentHeight = treeHeight - 1;
			// PageId parentPage = node.getParent();
			// sibling.setParent(parentPage);
			// PageId pageT
			
			// while (){
			// 	parent.read(parentPage, pf);
			// 	if (parent.getKeyCount() == node.MAX_NODE_SIZE){
			// 		parent.insertAndSplit(siblinkgKey, sibling.getPageId())
			// 	}
			// 	else {
			// 		parent.insert(siblingKey,sibling.getPageId());
			// 		break;
			// 	}
			// }
		}
	}
	else {
		node.insert(key,rid);
		if (treeHeight == 1) node.setParent(BTLeafNode::NO_PARENT);
		node.write(node.getPageId(),pf);
	}
    return 0;
}

// PageId insertUp(int key, PageId pid, int currHeight){

// 	BTNonLeafNode nl;
// 	nl.read(parentPage, pf);

// }


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
	nl.printNode();
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
    return 0;
}
