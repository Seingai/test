#ifndef users_h
#define users_h
#include"book.h"
#include"record.h"
#include<string>
#include<iostream>
#include<vector>

using namespace std;
class Record;
class Users
{
	public:
		Users();
		~Users();

		static int usersum;

		void usershowmenu();
		string getusersname();
		string getuserspassword();
		int getbooknumber();
		int getintime();
		vector<Book> getmybook();
		Record* gethead();
		int getusersum();
		void sethead(Record* r);
		
		void borrowbook(Book& b);
		bool returnbook(Book& b);
		void inlibrary();
		void setuserpassword(string a);
		void resetpassword();
		void setsuser(string a, string b, int c, int d);
		vector<Book>::iterator itbook;
		
		
		
		
		
	private:
		string usersname;
		string userspassword;
		int booknumber;
		int intime;
		vector<Book> mybook;
		Record* head;
		
		
};
#endif


