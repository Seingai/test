#include "Adm.h"

Administrators::Administrators() {
	head = NULL; adminnameame = " "; adminpassword = "123456";
}

void Administrators::adminshowmenu(){
	system("cls");
	cout << "Hello, admin@";
	cout<<adminnameame << "!" << endl;
	cout << "1.Search for books" << endl;
	cout << "2.Add user" << endl;
	cout << "3.Delete user" << endl;
	cout << "4.Add book" << endl;
	cout << "5.Delete book" << endl;
	cout << "6.Change book information" << endl;
	cout << "7.Change your password" << endl;
	cout << "8.Reset user's password" << endl;
	cout << "9.List users" << endl;
	cout << "0.Log off" << endl;
}
string Administrators::getadminnameame() { return  adminnameame; }
string Administrators::getadminpassword() { return adminpassword; }

void Administrators::setadminpassword(string a) { adminpassword = a; }
void Administrators::setadmins(string a, string b) { adminnameame = a; adminpassword = b; }
void Administrators::changepassword(){
	system("cls"); cout << "Please enter your new password:" << endl; string a; cin >> a; adminpassword = a; cout << "Password has been changed!" << endl << "R: return";
	if (cin.get() == 'R') { adminshowmenu(); }
}
void Administrators::usersearch(vector<Book>& Vbook){
	system("cls");
	Book x;
	x.search(Vbook);
	adminshowmenu();
}
void Administrators::deleteuser(Users& u,vector<Users>& Vuser){ 
	for (ituser = Vuser.begin(); ituser != Vuser.end();) { if (u.getusersname() == (*ituser).getusersname()) { ituser = Vuser.erase(ituser); break; } else ituser++; }
}
void Administrators::adduser(Users& u, vector<Users>& Vuser) { Vuser.push_back(u); }
void Administrators::deletebook(Book& b, vector<Book>& Vbook){
	for (itbook = Vbook.begin(); itbook != Vbook.end();) { if (b.getbookname() == (*itbook).getbookname()) { itbook = Vbook.erase(itbook); } else itbook++; }
}
void Administrators::addbook(Book& b, vector<Book>& Vbook) {
	Vbook.push_back(b);
}
void Administrators::changebookinfo(vector<Book>& Vbook) {
	int pos = -1;
	cout << "Please enter the book ISBN:" << endl;
	string isb; cin >> isb;
	for (unsigned i = 0; i < Vbook.size(); i++)
	{
		if (isb == Vbook[i].getbookname()) { pos = i; break; }
	}
	if (pos == -1) {
		cout << "Couldn't find the book!" << endl << "Try another Y/N?" << endl; cin.get();
		if (cin.get() == 'Y') { changebookinfo(Vbook); }
		else { adminshowmenu(); }
	}
	else {
		cout << "What information do you want to change?" << endl;
		cout << "1.Bookname  2.ISBN  3.First Type  4.Second Type  5.Third Type" << endl;
		string g; cin >> g;
		if (g == "1") {
			cout << "Please enter new Bookname:" << endl;
			string newname; cin >> newname;
			Vbook[pos].getbookname() = newname;
			cout << "The Bookname has been changed!" << endl << "Continue changing Y/N?" << endl; cin.get();
			if (cin.get() == 'Y') { changebookinfo(Vbook); }
			else { adminshowmenu(); }
		}
		if (g == "2") {
			cout << "Please enter new ISBN:" << endl;
			string newISBN; cin >> newISBN;
			Vbook[pos].getISBN() = newISBN;
			cout << "The ISBN has been changed!" << endl << "Continue changing Y/N?" << endl; cin.get();
			if (cin.get() == 'Y') { changebookinfo(Vbook); }
			else { adminshowmenu(); }
		}
		if (g == "3") {
			cout << "Please enter new Type1:" << endl;
			string newname; cin >> newname;
			Vbook[pos].gettype1() = newname;
			cout << "The Type1 has been changed!" << endl << "Continue changing Y/N?" << endl; cin.get();
			if (cin.get() == 'Y') { changebookinfo(Vbook); }
			else { adminshowmenu(); }
		}
		if (g == "4") {
			cout << "Please enter new Type2:" << endl;
			string newname; cin >> newname;
			Vbook[pos].gettype2() = newname;
			cout << "The Type2 has been changed!" << endl << "Continue changing Y/N?" << endl; cin.get();
			if (cin.get() == 'Y') { changebookinfo(Vbook); }
			else { adminshowmenu(); }
		}
		if (g == "5") {
			cout << "Please enter new Type3:" << endl;
			string newname; cin >> newname;
			Vbook[pos].gettype3() = newname;
			cout << "The Type3 has been changed!" << endl << "Continue changing Y/N?" << endl; cin.get();
			if (cin.get() == 'Y') { changebookinfo(Vbook); }
			else { adminshowmenu(); }
		}
	}
}
void Administrators::resetuserpassword(Users& u) { u.resetpassword(); }

