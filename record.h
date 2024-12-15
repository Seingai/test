#ifndef record_h
#define record_h
#include"users.h"
#include"book.h"
using namespace std;

class Record
{	
	protected:
		Book mybook;
		Record* next;
		bool ref;
	public:
		Record();
		Record* getnext();
		void setbook(Book);
		void setnext(Record* p);
		void changeref();
		void setref(bool f);
		
		Book getmybook();
		bool getref();
		~Record();
};

#endif
