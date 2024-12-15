#include "users.h"
#include<vector>
#include<iostream>
#include<string>
using namespace std;
void Users::usershowmenu(){
	system("cls");
	cout << "Hello, user@"<<getusersname()<<"!" << endl;
	cout << "1.Search for books" << endl;
	cout << "2.Borrow books" << endl;
	cout << "3.Returnbooks" << endl;
	cout << "4.Check records" << endl;
	cout << "5.Change password" << endl;
	cout << "6.Check in times" << endl;
	cout << "7.Log off" << endl; 
}
int Users::usersum = 0;
Users::Users() { usersname = " "; userspassword = "123456"; usersum++; booknumber = 0; intime = 0; head = NULL; }
Users::~Users() { usersum--; }
void Users::sethead(Record* r) { head = r; }
int Users::getintime() { return intime; }
int Users::getusersum() { return usersum; }
void Users::setsuser(string a, string b, int c, int d) { usersname = a; userspassword = b; intime = c; booknumber = d; }
string Users::getusersname() { return usersname; }
string Users::getuserspassword() { return userspassword; }
vector<Book> Users::getmybook() { return mybook;}
Record* Users::gethead() { return head; }
void Users::resetpassword() { userspassword = "123456"; }
int Users::getbooknumber() { return booknumber; }

void Users::inlibrary() { intime++; }
void Users::setuserpassword(string a) { userspassword = a; }
bool Users::returnbook(Book& boo) {
	bool f = false;
	if (boo.getexistance() == 0) {
		
		int i = 1; 
		Record* tempp = head;
		if (tempp->getmybook() == boo) {
			f = true;
		}
		else {
			while (!(tempp->getnext() == NULL)) {
				if (tempp->getmybook() == boo) {
					f = true; break;
				}
				else {
					tempp = tempp->getnext();
				}
			}
			if (tempp->getmybook() == boo) { f = true; }
		}
		if (f == true) {
			boo.returnbook();
			tempp->changeref();
		}
		else {
			cout << "You didn't borrow the book!" << endl;
		}
		for (itbook = mybook.begin(); itbook != mybook.end();) { if (boo == *itbook) { itbook = mybook.erase(itbook); } else itbook++; }
	}
	return f;
	
}
void Users::borrowbook(Book& boo) {
	if (boo.getexistance()) {
		mybook.push_back(boo);
		Record* p = new Record;
		p->setbook(boo);
		if (booknumber == 0) {
			head = p; booknumber++; 
		}
		else {
			Record* tempp = head;
			for (int i = 0; i < booknumber - 1; i++) {
				tempp = tempp->getnext();
			}
			tempp->setnext(p);
			booknumber++; 
		}
	}
	boo.borrow();
}


