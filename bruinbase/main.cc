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


int main()
{
  // run the SQL engine taking user commands from standard input (console).
  //SqlEngine::run(stdin);

 	
 //leafTest();
	nonTest();


  	return 0;
}
