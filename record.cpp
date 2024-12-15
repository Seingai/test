#include "record.h"
#include<vector>
#include<iostream>
#include<string>
using namespace std;
Record::Record()
{
	next = NULL;
	ref = true;
}
void Record::setnext(Record* p) { next = p; }
bool Record::getref() { return ref; }
void Record::setref(bool f) { ref = f; }
void Record::setbook(Book mbk) { mybook = mbk; }
void Record::changeref() { ref = false; }
Record::~Record()
{
	if (next->next != NULL) delete next;
	next = NULL;
}
Book Record::getmybook() { return mybook; }
Record* Record::getnext() { return next; }
