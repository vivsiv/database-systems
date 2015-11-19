/**
 * Copyright (C) 2008 by The Regents of the University of California
 * Redistribution of this file is permitted under the terms of the GNU
 * Public License (GPL).
 *
 * @author Junghoo "John" Cho <cho AT cs.ucla.edu>
 * @date 3/24/2008
 */
 
#include "Bruinbase.h"
#include "SqlEngine.h"
#include "BTreeNode.h"
#include "BTreeIndex.h"
#include <cstdio>

void leafTest(){
	PageFile pf;
 	pf.open("test_leaf_node.txt", 'w');
 	int newPid = pf.endPid();

 	//READ
	// BTLeafNode ln;
	// ln.read(0, pf);
	// ln.printNode();

	// BTLeafNode sibling;
	// sibling.read(1, pf);
	// sibling.printNode();
 	

 	//WRITE
 	RecordFile rf;
 	rf.open("movie.tbl",'r');

 	RecordId rid;
 	rid.pid = 0;
 	rid.sid = 0;
 	int key;
 	std::string value;

	BTLeafNode ln;
	ln.read(newPid, pf);

 	for (int i=0; i < 8; i++){
 		rid.sid = i;
 		rf.read(rid,key,value);
	 	printf("Got record key:%d value:%s\n", key, value.c_str());
	 	ln.insert(key,rid);
 	}
 	ln.write(newPid,pf);
 	printf("\n");

	BTLeafNode sibling;
	int siblingKey;
	int siblingPid = pf.endPid();
	sibling.read(siblingPid, pf);

	rid.sid = 8;
	rf.read(rid,key,value);
	printf("Running insert and split with key:%d\n", key);
	printf("Got record key:%d value:%s\n", key, value.c_str());
	ln.insertAndSplit(key, rid, sibling, siblingKey);

	ln.write(newPid,pf);
	ln.printNode();

	printf("\n");
	printf("Sibling first Key is:%d\n",siblingKey);
	sibling.write(siblingPid, pf);
	sibling.printNode();


	int found;
	ln.locate(272,found);
	printf("found key:272 at index entry:%d\n",found);

	// ln.locate(3992,found);
	// printf("found key:3992 at index entry:%d\n",found);

	// ln.locate(0,found);
	// printf("found key:0 at index entry:%d\n",found);


	// ln.locate(2500,found);
	// printf("found key:2500 at index entry:%d\n",found);

	// int findKey;
	// RecordId findRecord;
	// ln.readEntry(0, findKey, findRecord);
	// printf("found entry:0 key:%d recordId: pid:%d sid:%d\n",findKey, findRecord.pid, findRecord.sid);
	// ln.readEntry(3, findKey, findRecord);
	// printf("found entry:3 key:%d recordId: pid:%d sid:%d\n",findKey, findRecord.pid, findRecord.sid);
}

void nonTest(){
	PageFile pf;
 	pf.open("test_non_leaf_node.txt", 'w');
 	int newPid = pf.endPid();


 	//READ
 // 	printf("First Non Existent page:%d\n",newPid);
	// BTNonLeafNode ln;
	// ln.read(0, pf);
	// ln.printNode();

	// BTNonLeafNode sibling;
	// sibling.read(1, pf);
	// sibling.printNode();

 	//WRITE
 	RecordFile rf;
 	rf.open("movie.tbl",'r');

 	RecordId rid;
 	rid.pid = 0;
 	rid.sid = 0;
 	int key;
 	std::string value;


	BTNonLeafNode ln;
	ln.read(newPid, pf);
	ln.printNode();

 	for (int i=0; i < 5; i++){
 		rid.pid = i;
 		rid.sid = i;
 		rf.read(rid,key,value);
	 	printf("Got record at page:%d key:%d value:%s\n", rid.pid, key, value.c_str());
	 	ln.insert(key,rid.pid);
 	}
 	printf("Writing to page:%d\n",newPid);
 	ln.write(newPid,pf);
 	ln.printNode();
 	printf("\n");

 	int locate;
 	ln.locateChildPtr(172,locate);
 	printf("Locating 172: %d\n",locate);
 	ln.locateChildPtr(173,locate);
 	printf("Locating 173: %d\n",locate);
 	ln.locateChildPtr(488,locate);
 	printf("Locating 488: %d\n",locate);
 	ln.locateChildPtr(489,locate);
 	printf("Locating 489: %d\n",locate);
 	ln.locateChildPtr(490,locate);
 	printf("Locating 490: %d\n",locate);
 	ln.locateChildPtr(3619,locate);
 	printf("Locating 3619: %d\n",locate);

 	BTNonLeafNode sibling;
	int midKey;
	int siblingPid = pf.endPid();
	sibling.read(siblingPid, pf);

	rid.pid = 5;
	rid.sid = 5;
	rf.read(rid,key,value);
	printf("Running insert and split with key:%d\n", key);
	printf("Got record page:%d key:%d value:%s\n", rid.pid, key, value.c_str());
	ln.insertAndSplit(key, rid.pid, sibling, midKey);

	ln.write(newPid,pf);
	ln.printNode();

	printf("Mid Key is:%d\n", midKey);
	printf("\n");

	//printf("Sibling first Key is:%d\n",sibli);
	sibling.write(siblingPid, pf);
	sibling.printNode();
}

void indexTest(){
	//WRITE
	// BTreeIndex idx;
	// idx.open("test_index", 'w');

	// RecordFile rf;
 // 	rf.open("movie.tbl",'r');

	// RecordId rid;
 // 	rid.pid = 0;
 // 	rid.sid = 0;
 // 	int key;
 // 	std::string value;

	// IndexCursor cursor;

 // 	for (int i=0; i < 5; i++){
 // 		rid.sid = i;
 // 		rf.read(rid,key,value);
	//  	printf("Got record key:%d value:%s\n", key, value.c_str());
	//  	idx.insert(key,rid);
	//  	idx.locate(key,cursor);
	//  	printf("Located key:%d. page:%d eid:%d\n", key, cursor.pid, cursor.eid);
	//  	printf("\n");
 // 	}
	//  idx.printTree();

 // 	idx.close();


 	//READ
 	BTreeIndex idx;
 	IndexCursor cursor;
 	int key;
	RecordId rid;
	idx.open("test_index", 'r');
	idx.locate(2342,cursor);
	printf("Located key:%d. page:%d eid:%d\n", 2342, cursor.pid, cursor.eid);
	idx.readForward(cursor,key,rid);
	printf("Read Forward key:%d, got page:%d,slot:%d\n",key,rid.pid,rid.sid);

	idx.locate(2965,cursor);
	printf("Located key:%d. page:%d eid:%d\n", 2965, cursor.pid, cursor.eid);
	idx.readForward(cursor,key,rid);
	printf("Read Forward key:%d, got page:%d,slot:%d\n",key,rid.pid,rid.sid);
	idx.close();

 }

 void indexTest2(){
 		//WRITE
	BTreeIndex idx;
	idx.open("test_index2", 'w');

	RecordFile rf;
 	rf.open("movie.tbl",'r');

	RecordId rid;
 	rid.pid = 0;
 	rid.sid = 0;
 	int key;
 	std::string value;

	IndexCursor cursor;
	
	int slotId;
 	for (int i=0; i < 14; i++){
 		if (i == 9) {
 			rid.pid += 1;
 			slotId = 0;
 		}
 		rid.sid = slotId;
 		rf.read(rid,key,value);
	 	printf("Inserting Record (key:%d|page:%d|slot:%d|value:%s)...\n", key, rid.pid, rid.sid, value.c_str());
	 	idx.insert(key,rid);
	 	printf("\n");
	 	idx.locate(key,cursor);
	 	printf("Located key:%d. page:%d eid:%d\n", key, cursor.pid, cursor.eid);
	 	printf("----------------------\n");
	 	 slotId++;
 	}
	
	printf("\n\n\n");
	// READ
	char buffer[PageFile::PAGE_SIZE];
	BTLeafNode *leaf;
	BTNonLeafNode *nonleaf;
        idx.read(0,(void *)buffer);
	printf("rootPageHeader: root PageId: %d, tree height: %d\n\n",*((int*)buffer),*(((int*)buffer)+1));
	for (int i=1; i<17; i++) {
		idx.read(i,(void *)buffer);
		leaf = reinterpret_cast<BTLeafNode*>(buffer);
		nonleaf = reinterpret_cast<BTNonLeafNode*>(buffer);
		printf("Printing node on page %d\n", i);
		leaf->printNode();
		nonleaf->printNode();
		printf("\n");
	}
		
 	idx.close();
 }


int main()
{
  	// run the SQL engine taking user commands from standard input (console).
  	SqlEngine::run(stdin);

 	
 	//leafTest();
	//nonTest();
	//indexTest();
	//indexTest2();
        /*BTreeIndex idx;
        idx.open("large", 'r');
        
        char buffer[PageFile::PAGE_SIZE];
        BTNonLeafNode *nonleaf;
        BTLeafNode *leaf;
        RC rc = 0;
        idx.read(0,(void *)buffer);
	printf("rootPageHeader: root PageId: %d, tree height: %d\n\n",*((int*)buffer),*(((int*)buffer)+1));
	for (int i=1; rc == 0; i++) {
          printf("Printing node: %d\n", i);
          rc = idx.read(i,(void*)buffer);
          if (i == 3 || i == 74 || i == 75) {
            nonleaf = reinterpret_cast<BTNonLeafNode*>(buffer);
            nonleaf->printNode();
	  } else {
            leaf = reinterpret_cast<BTLeafNode*>(buffer);
            leaf->printNode();
            printf("leaf on page %d -> leaf on page %d\n",i,leaf->getNextPage());
          }
          printf("\n");
        }
        idx.close();*/
  	return 0;
}
