/**
 * Copyright (C) 2008 by The Regents of the University of California
 * Redistribution of this file is permitted under the terms of the GNU
 * Public License (GPL).
 *
 * @author Junghoo "John" Cho <cho AT cs.ucla.edu>
 * @date 3/24/2008
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Bruinbase.h"
#include "SqlEngine.h"
#include "BTreeIndex.h"

using namespace std;

// external functions and variables for load file and sql command parsing 
extern FILE* sqlin;
int sqlparse(void);


RC SqlEngine::run(FILE* commandline)
{
  fprintf(stdout, "Bruinbase> ");

  // set the command line input and start parsing user input
  sqlin = commandline;
  sqlparse();  // sqlparse() is defined in SqlParser.tab.c generated from
               // SqlParser.y by bison (bison is GNU equivalent of yacc)

  return 0;
}

RC SqlEngine::select(int attr, const string& table, const vector<SelCond>& cond)
{
  RecordFile rf;   // RecordFile containing the table
  RecordId   rid;  // record cursor for table scanning

  RC     rc;
  int    key;     
  string value;
  int    count;
  int    diff;
  
  // open the table file
  if ((rc = rf.open(table + ".tbl", 'r')) < 0) {
    fprintf(stderr, "Error: table %s does not exist\n", table.c_str());
    return rc;
  }

  // check for existence of index
  RC index;
  bool isIndex = false;
  BTreeIndex idx;
  const string idxname = table + ".idx";
  //fprintf(stdout, "Opening index %s\n", idxname.c_str());
  index = idx.open(table, 'r');
  if (index != 0) {
    fprintf(stdout, "There is no index %s\n", idxname.c_str());
  }
  else {
    isIndex = true;
    //fprintf(stdout, "Index %s found!\n", idxname.c_str());
    //return 0;
  }
  
  // filter value key conditions and value conditions into separate vectors
  vector<SelCond> keyConds;
  vector<SelCond> valConds;
  int upper = INT_MAX; 
  int lower = 0;
  int equal = 0;
  int equal_count = 0;
  bool eq = 0;
  size_t numConds = cond.size();
  for (int j=0; j<numConds; j++) {
    if (cond[j].attr == 1) { 
      keyConds.push_back(cond[j]);
      switch (cond[j].comp) {
        case SelCond::EQ:
          equal = atoi(cond[j].value);
          eq = true;
          ++equal_count;
          break;
        case SelCond::NE:
          isIndex = false;
          break;
        case SelCond::LT:
          if (atoi(cond[j].value)-1 < upper) upper = atoi(cond[j].value) - 1;
          break;
        case SelCond::GT:
          if (atoi(cond[j].value)+1 > lower) lower = atoi(cond[j].value) + 1;
          break;
        case SelCond::LE:
          if (atoi(cond[j].value) < upper) upper = atoi(cond[j].value);
          break;
        case SelCond::GE:
          if (atoi(cond[j].value) > lower) lower = atoi(cond[j].value);
          break;
      }
    }
    else valConds.push_back(cond[j]);
  }
  
  // use the index to answer the query
  if (keyConds.size() >= 1 && isIndex) {
    // check if query is invalid and if so return reasonable error code
    // assumes any query with more than one value condition is false
    // also assumes negative keys are invalid
    if (upper < lower || upper == lower || (upper < equal && eq) || (lower > equal && eq) || equal_count > 1 || valConds.size() > 1) {
      printf("upper = %d, lower = %d\n", upper, lower);
      fprintf(stderr, "Invalid query!\n");
      return 0;
    }
      // iterate through keys
      IndexCursor cursor;
      int count = 0;
      int matches = 0;
      
      if (eq) {
        key = equal;
        upper = equal;
      } else key = lower;
      
      rc = idx.locate(key, cursor);
      if (rc != 0 && rc != RC_NO_SUCH_RECORD) { fprintf(stderr, "rc=%d, count=%d\n", rc, count); return rc; }
      rc = idx.readForward(cursor, key, rid);
      if (rc != 0) { fprintf(stderr, "rc=%d, count=%d\n", rc, count); return rc; }

      while (key <= upper) {
          switch(attr) {
            case 1:
              if (valConds.size() > 0) {
                rf.read(rid, key, value);
                if (strcmp(valConds[0].value, value.c_str()) == 0) {
                  ++matches;
                  fprintf(stdout, "%d\n", key);
                }
              }
              else {
                ++matches;
                fprintf(stdout, "%d\n", key);
              }
              break;
            case 2:
              rf.read(rid, key, value);
              if (valConds.size() > 0) {
                if (strcmp(valConds[0].value, value.c_str()) == 0) {
                  ++matches;
                  fprintf(stdout, "%s\n", value.c_str());
                }
              }
              else {
                ++matches;
                fprintf(stdout, "%s\n", value.c_str());
              }
              break;
            case 3:
              rf.read(rid, key, value);
              if (valConds.size() > 0) {
                if (strcmp(valConds[0].value, value.c_str()) == 0) {
                  ++matches;
                  fprintf(stdout, "%d '%s'\n", key, value.c_str());
                }
              }
              else {
                ++matches;
                fprintf(stdout, "%d '%s'\n", key, value.c_str());
              }
              break;
            case 4:
              if (valConds.size() > 0) {
                rf.read(rid, key, value);
                if (strcmp(valConds[0].value, value.c_str()) == 0) {
                  ++matches;
                  fprintf(stdout, "%d\n", key);
                }
              }
              else ++matches;
              break;
          }
        rc = idx.readForward(cursor, key, rid);
        if (rc == RC_END_OF_TREE) { 
          break;
        }
        ++count;
      }
      if (attr == 4) fprintf(stdout, "%d\n", matches);
      //fprintf(stdout, "count=%d\n", count);
      //fprintf(stdout, "matches=%d\n", matches);
      rf.close();
      idx.close();
      return 0;
    //}
  }

  // scan the table file from the beginning
  rid.pid = rid.sid = 0;
  count = 0;
  while (rid < rf.endRid()) {
    // read the tuple
    if ((rc = rf.read(rid, key, value)) < 0) {
      fprintf(stderr, "Error: while reading a tuple from table %s\n", table.c_str());
      goto exit_select;
    }

    // check the conditions on the tuple
    for (unsigned i = 0; i < cond.size(); i++) {
      // compute the difference between the tuple value and the condition value
      switch (cond[i].attr) {
      case 1:
	diff = key - atoi(cond[i].value);
	break;
      case 2:
	diff = strcmp(value.c_str(), cond[i].value);
	break;
      }

      // skip the tuple if any condition is not met
      switch (cond[i].comp) {
      case SelCond::EQ:
	if (diff != 0) goto next_tuple;
	break;
      case SelCond::NE:
	if (diff == 0) goto next_tuple;
	break;
      case SelCond::GT:
	if (diff <= 0) goto next_tuple;
	break;
      case SelCond::LT:
	if (diff >= 0) goto next_tuple;
	break;
      case SelCond::GE:
	if (diff < 0) goto next_tuple;
	break;
      case SelCond::LE:
	if (diff > 0) goto next_tuple;
	break;
      }
    }

    // the condition is met for the tuple. 
    // increase matching tuple counter
    count++;

    // print the tuple 
    switch (attr) {
    case 1:  // SELECT key
      fprintf(stdout, "%d\n", key);
      break;
    case 2:  // SELECT value
      fprintf(stdout, "%s\n", value.c_str());
      break;
    case 3:  // SELECT *
      fprintf(stdout, "%d '%s'\n", key, value.c_str());
      break;
    }

    // move to the next tuple
    next_tuple:
    ++rid;
  }

  // print matching tuple count if "select count(*)"
  if (attr == 4) {
    fprintf(stdout, "%d\n", count);
  }
  rc = 0;

  // close the table file and return
  exit_select:
  rf.close();
  return rc;
}

RC SqlEngine::load(const string& table, const string& loadfile, bool index)
{
    // assume initially index is always false
  // create RecordFile with name <table>.tbl
  RC status;
  const string rfilename = table + ".tbl";
  RecordFile rcfile;
  BTreeIndex idx;
  string record;

  status = rcfile.open(rfilename, 'w');
  if (status !=0) return EXIT_FAILURE; 

  // create index
  if (index) {
    status = idx.open(table, 'w');
    if (status != 0) {
      fprintf(stderr, "Not able to open index file %s.idx\n", table.c_str());
      return EXIT_FAILURE;
    }
  }

  // open and read tuples from file loadfile
  ifstream ldfile(loadfile.c_str());
  if (!ldfile.is_open()) {
    cerr << loadfile << " not found!" << endl;
    return EXIT_FAILURE;
  }

  int counter = 0;
  while (getline(ldfile, record)) {
    if (ldfile.eof()) break;
    int key; string value;
    // parse tuples using SqlEngine::parseLoadLine() method
    status = parseLoadLine(record, key, value);
    if (status != 0) return EXIT_FAILURE;
    // insert tuples into <table>.tbl
    RecordId last_record = rcfile.endRid();
    status = rcfile.append(key, value, last_record);
    if (status != 0) return EXIT_FAILURE;
    // add key, rid to index
    if (index) {
       //if (counter == 141) return 0;
       status = idx.insert(key, last_record);
       ++counter;
       if (status != 0) return EXIT_FAILURE;
    }
  }
  //fprintf(stdout, "number of tuples added = %d\n", counter);
  // close index
  if (index) idx.close();
  // close the loadfile and record file
  rcfile.close();
  ldfile.close();
  return 0;
    
}


RC SqlEngine::parseLoadLine(const string& line, int& key, string& value)
{
    const char *s;
    char        c;
    string::size_type loc;
    
    // ignore beginning white spaces
    c = *(s = line.c_str());
    while (c == ' ' || c == '\t') { c = *++s; }

    // get the integer key value
    key = atoi(s);

    // look for comma
    s = strchr(s, ',');
    if (s == NULL) { return RC_INVALID_FILE_FORMAT; }

    // ignore white spaces
    do { c = *++s; } while (c == ' ' || c == '\t');
    
    // if there is nothing left, set the value to empty string
    if (c == 0) { 
        value.erase();
        return 0;
    }

    // is the value field delimited by ' or "?
    if (c == '\'' || c == '"') {
        s++;
    } else {
        c = '\n';
    }

    // get the value string
    value.assign(s);
    loc = value.find(c, 0);
    if (loc != string::npos) { value.erase(loc); }

    return 0;
}
