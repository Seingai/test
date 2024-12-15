#include"Adm.h"
#include"book.h"
#include"record.h"
#include"users.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<string>
using namespace std;
void readfile_books(vector<Book>& Vbook) {
	Book temp;
	ifstream fin_book("Book.txt", ios::in);
	while (!fin_book.eof()) {
		bool f; string I; string book_name; string aname; string t1; string t2; string t3;
		fin_book >> f >> I >> book_name >> aname >> t1 >> t2 >> t3;
		temp.setbook(f, I, book_name, aname, t1, t2, t3);
		Vbook.push_back(temp);
	}
	Vbook.pop_back();
	fin_book.close();
}
char cinget() {
	char a; a = cin.get(); return a;
}


void readfile_users(vector<Users>& Vuser) {
	ifstream fin_user("Users.txt", ios::in);
	Users tempu;
	while (!fin_user.eof())
	{
		string pname, pa, I, book_name, aname, f1, f2, f3;
		int inname, bbname;
		fin_user >> pname >> pa >> inname >> bbname;
		tempu.setsuser(pname, pa, inname, bbname);

		if (bbname != 0)                        
		{

			Record* temp_r = NULL;
			Record* head_r = NULL;
			Book temp_b;
			for (int i = 0; i < bbname; i++)
			{
				bool flag; Record* tp_r = new Record;
				fin_user >> flag >> I >> book_name >> aname >> f1 >> f2 >> f3;


				temp_b.setbook(flag, I, book_name, aname, f1, f2, f3);
				tp_r->setbook(temp_b);
				tp_r->setref(flag);
				if (i == 0) head_r = tp_r;
				else temp_r->setnext(tp_r);
				temp_r = tp_r;

			}
			tempu.sethead(head_r);
		}

		Vuser.push_back(tempu);
	}
	Vuser.pop_back();
	fin_user.close();
}

void savefile_users(vector<Users>& Vuser) {
	ofstream foutuser("Users.txt", ios::out | ios::trunc);
	for (unsigned j = 0; j < Vuser.size(); j++)
	{
		foutuser << Vuser[j].getusersname() << "  " << Vuser[j].getuserspassword() << "  " << Vuser[j].getintime() << "  "
			<< Vuser[j].getbooknumber() << endl;
		if (Vuser[j].getbooknumber() != 0)
		{
			Record* temp = Vuser[j].gethead();
			for (unsigned i = 0; i < Vuser[j].getbooknumber(); i++)
			{
				Book temp_b;
				temp_b = temp->getmybook();
				foutuser << temp->getref() << "  " << temp_b.getISBN() << "  " << temp_b.getbookname() << "  " << temp_b.getauthorname() << "  " << temp_b.gettype1() << "  " << temp_b.gettype2() << "  " << temp_b.gettype3() << endl;
				temp = temp->getnext();
			}
		}
	}
	foutuser.close();
}
void savefile_books(vector<Book>& Vbook) {
	ofstream foutbook("Book.txt", ios::out | ios::trunc);
	for (unsigned i = 0; i < Vbook.size(); i++) {
		foutbook << Vbook[i].getexistance() << "  ";
		foutbook << Vbook[i].getISBN() << "  ";
		foutbook << Vbook[i].getbookname() << "  ";
		foutbook << Vbook[i].getauthorname() << "  ";
		foutbook << Vbook[i].gettype1() << "  ";
		foutbook << Vbook[i].gettype2() << "  ";
		foutbook << Vbook[i].gettype3() << endl;
	}
	foutbook.close();
}
void savefile_administrators(vector<Administrators>& Vadmin) {
	ofstream foutadmin("Administrators.txt", ios::out | ios::trunc);
	for (unsigned i = 0; i < Vadmin.size(); i++) {
		foutadmin << Vadmin[i].getadminnameame() << "  ";
		foutadmin << Vadmin[i].getadminpassword() << endl;
	}
	foutadmin.close();
}

void shut(vector<Book>& Vbook, vector<Users>& Vuser, vector<Administrators>& Vadmin) {
	cout << "Shutting the system..." << endl;
	savefile_books(Vbook);
	savefile_users(Vuser);
	savefile_administrators(Vadmin);
}


void startinterface() {
	cout<<"=================================="<<endl;
	cout<<"|Welcome to Library of HNU!      |"<< endl;
	cout<<"|   1.Access as a user.          |" << endl;
	cout<<"|   2.Access as an administrator.|" << endl;
	cout<<"|   3.Access as a visitor.       |" << endl;
	cout<<"|   4.Shut down the system.      |" << endl;
	cout<<"=================================="<<endl;
	cout<<"Please enter your access method:" << endl;
}
void readfile_adm(vector<Administrators>& Vadmin) {
	Administrators temp;
	ifstream fin_adm("Administrators.txt", ios::in);
	while (!fin_adm.eof()) {
		string name; string password;
		fin_adm >> name >> password;
		temp.setadmins(name, password);
		Vadmin.push_back(temp);
	}
	Vadmin.pop_back();
	fin_adm.close();
}
int userlogin(vector<Book>& Vbook, vector<Users>& Vuser, vector<Administrators>& Vadmin) {
	system("cls");
	cout << "Please enter your user name:" << endl;
	string uname;
	cin >> uname;
	int judge = 0,num = -1;
	for (unsigned i = 0;i < Vuser.size(); i++) {
		if (Vuser[i].getusersname() == uname) {
			judge = 1;
			num = i;
			break;
		}
	}
		if (judge == 1) {
			cout << "User name confirmed." << endl << "Now please enter your password:" << endl;
			string u_password;
			cin >> u_password;
			if (Vuser[num].getuserspassword() == u_password) {
				return num;
			}
			else {
				cout << "Wrong password!" << endl;
				cout << "R: retry" << endl;
				cin.get();
				if (cinget() == 'R') 
					userlogin(Vbook, Vuser, Vadmin);
				else { 
					cout << "Sorry to shut down the system!";
					shut(Vbook, Vuser, Vadmin);
					exit(0); 
				}
			}
		}
		else {
			cout << "The account does not existe!" << endl;
			cout << "R: retry" << endl;
			cin.get();
			if (cinget() == 'R') 
				userlogin(Vbook, Vuser, Vadmin);
			else { 
				cout << "Sorry to shut down the system!";
				shut(Vbook, Vuser, Vadmin);
				exit(0); 
			}
		}
	
}
int adminlogin(vector<Book>& Vbook, vector<Users>& Vuser, vector<Administrators>& Vadmin) {
	system("cls");
	cout << "Please enter your administrator name:" << endl;
	string adm_name;
	cin >> adm_name;
	for (unsigned i = 0; i < Vadmin.size(); i++) {
		if (Vadmin[i].getadminnameame() == adm_name) {
			cout << "Administrator name confirmed." << endl << "Now please enter your password:" << endl;
			string adm_password; cin >> adm_password;
			if (Vadmin[i].getadminpassword() == adm_password) {
				return i;
			}
			else {
				cout << "Wrong password!" << endl;
				cout << "R: retry" << endl;
				cin.get();
				if (cinget() == 'R') 
					adminlogin(Vbook, Vuser, Vadmin);
				else { 
					cout << "Sorry to shut down the system!";
					shut(Vbook, Vuser, Vadmin);
					exit(0); 
				}
			}
		}
		else {
			cout << "The account does not existe!" << endl;
			cout << "R: retry" << endl; cin.get();
			if (cinget() == 'R') { adminlogin(Vbook, Vuser, Vadmin); }
			else { cout << "Sorry to shut down the system!"; shut(Vbook, Vuser, Vadmin); exit(0);
			}
		}
	}
}
void usermanip(vector<Administrators>& Vadmin, vector<Users>& Vuser, vector<Book>& Vbook, vector<Record>& Vrecord, char c, Book& btemp, Users& utemp, int n) {
	while (1) {
		utemp.usershowmenu(); 
		char d = cinget();
		if (d == '1') {
			btemp.search(Vbook);	
		}
		else if (d == '2') {
		conborrow:
			cout << "Please enter the book name:" << endl;
			int jud = 0; string bn; cin >> bn;
			for (unsigned i = 0; i < Vbook.size(); i++) {
				if (Vbook[i].getbookname() == bn) {
					Vuser[n].borrowbook(Vbook[i]);
					jud = 1;
					break;
				}
			}
			if (jud == 1) {
				cout << "Continue to borrow Y/N?" << endl;
				cin.get();
				if (cin.get() == 'Y') { goto conborrow; }
				else utemp.usershowmenu();
			}
			else {
				cout << "Couldn't find the book!" << endl;
				cout << "Continue to borrow Y/N?" << endl;
				cin.get();
				if (cin.get() == 'Y') 
					goto conborrow;
				else utemp.usershowmenu();
			}
		}
		else if (d == '3') {
		conreturn:
			cout << "Please enter the book name:" << endl;
			bool jud=false; 
			string book_name; 
			cin >> book_name;
			int ifbook = 0;
			for (unsigned k = 0; k < Vbook.size(); k++) {
				if (Vbook[k].getbookname() == book_name) {
					ifbook = 1;
					break;
				}
			}
			if (ifbook == 1) {
				for (unsigned i = 0; i < Vbook.size(); i++) {
					if (Vbook[i].getbookname() == book_name) {
						jud = Vuser[n].returnbook(Vbook[i]);
						break;
					}
				}
				if (jud == true) {
					cout << "Continue to return Y/N?" << endl;
					cin.get();
					if (cin.get() == 'Y') 
						goto conreturn;
					else continue;
				}
				else {
					cout << "You didn't borrow the book!" << endl;
					cout << "Continue to return Y/N?" << endl;
					cin.get();
					if (cin.get() == 'Y') 
						goto conreturn;
					else continue;
				}
			}
			else {
				cout << "The book doesn't exist!" << endl;
				cout << "Continue to return Y/N?" << endl;
				cin.get();
				if (cin.get() == 'Y') 
					goto conreturn;
				else continue;
			}
		}
		else if (d == '4') {
			system("cls");
			if (Vuser[n].getbooknumber() == 0) {
				cout << "You have no records!" << endl;
				cout << "R: return to the menu." << endl; 
				cin.get();
				if (cin.get() == 'R') 
					continue;
				else { 
					shut(Vbook, Vuser, Vadmin); 
					exit(0);
				}
			}
			else {
				cout << "You have " << Vuser[n].getbooknumber() << " loan record(s)." << endl;
				Record* tmpp = Vuser[n].gethead();
				cout << "    ISBN          Bookname          Author          Type          State" << endl;
				for (int i = 0; i < Vuser[n].getbooknumber();i++) {
					Book btmp = tmpp->getmybook();
					cout << btmp;
					if (tmpp->getref() == true) {
						cout << "      " << "Borrowing" << endl;
					}
					else { 
						cout << "      " << "Returned" << endl;
					}
					tmpp = tmpp->getnext();
				}
				cout << "B: only check for borrowing books.    R: return to the menu." << endl; 
				cin.get();
				char r = cinget();
				if (r == 'B') {
					vector<Book> vtmpb = Vuser[n].getmybook();
					cout << "    ISBN          Bookname          Author          Type          State" << endl;
					for (unsigned i = 0; i < vtmpb.size(); i++) {
						Book bttmp = vtmpb[i];
						cout << bttmp << "      " << "Borrowing" << endl;
					}
					cout << "R: return to the menu." << endl; 
					cin.get();
					if (cin.get() == 'R') 
						continue;
					else { 
						shut(Vbook, Vuser, Vadmin); 
						exit(0);
					}
				}
				else if (r == 'R') { continue; }
				else { 
					shut(Vbook, Vuser, Vadmin); 
					exit(0);
				}
			}
		}
		else if (d == '5') {
		changeagain:
			system("cls");
			cout << "Please enter your old password:" << endl;
			string tp; 
			cin >> tp;
			if (tp == Vuser[n].getuserspassword()) {
				cout << "Verification passed!" << endl;
			cca:
				cout << "Please enter your new password:" << endl;
				string a, b; 
				cin >> a;
				cout << "Please enter it again:" << endl; 
				cin >> b;
				if (a == b) {
					Vuser[n].setuserpassword(tp);
					cout << "Password has been changed!" << endl;
					cout << "R: return to the menu." << endl; 
					cin.get();
					if (cin.get() == 'R') 
						continue;
					else {
						shut(Vbook, Vuser, Vadmin); 
						exit(0);
					}
				}
				else {
					cout << "Not the same! Please try again:" << endl;
					goto cca;
				}
			}
			else {
				cout << "Wrong password!   Maybe you should ask your admin for help." << endl;
				cout << "T: try again.    R: return to the menu." << endl; 
				cin.get();
				char k = cin.get();
				if (k == 'T') 
					goto changeagain;
				else if (k == 'R') 
					continue; 
				else { 
					shut(Vbook, Vuser, Vadmin);
					exit(0);
				}
			}
		}
		else if (d == '6') {
			int inti = Vuser[n].getintime();
			if (inti == 1) {
				cout << "You have only been in the library for once." << endl;
				cout << "R: return to the menu." << endl; 
				cin.get();
				if (cin.get() == 'R') 
					continue;
				else {
					shut(Vbook, Vuser, Vadmin); 
					exit(0);
				}
			}
			else {
				cout << "You have been in the library for " << inti << " times." << endl; 
				cout << "R: return to the menu." << endl;
				cin.get();
				if (cin.get() == 'R') 
					continue;
				else {
					shut(Vbook, Vuser, Vadmin); 
					exit(0);
				}
			}


		}
		else if (d == '7') {
			shut(Vbook, Vuser, Vadmin); 
			exit(0);
		}
		else {
		cout << "Invalid choice!" << endl;
		cout << "Sorry to shut down the system!";
		shut(Vbook, Vuser, Vadmin);
	}
	}
}
void adminmanip(vector<Administrators>& Vadmin, vector<Users>& Vuser, vector<Book>& Vbook, vector<Record>& Vrecord, char c, Book& btemp, Users& utemp, Administrators& atemp, int n) {
	while (1) {
		atemp.adminshowmenu();
		char d = cinget();
		if (d == '1') {
			btemp.search(Vbook);
		}
		else if (d == '2') {
		conaddinguser:
			cout << "Please enter usersname and password:" << endl;
		adddd:
			string tun, tup; 
			cin >> tun >> tup; 
			bool juddd = false;
			for (unsigned i = 0; i < Vuser.size(); i++) {
				if (Vuser[i].getusersname() == tun) {
					juddd = true; break;
				}
			}
			if (juddd == false) {
				utemp.setsuser(tun, tup, 0, 0);
				Vadmin[n].adduser(utemp, Vuser);
				cout << "The new user has been added." << endl;
				cout << "C: continue adding.   R: return to the menu." << endl; 
				cin.get();
				char o = cinget();
				if (o == 'C') 
					goto conaddinguser; 
				else if (o == 'R') 
					continue;
				else { 
					shut(Vbook, Vuser, Vadmin); 
					exit(0); 
				}
			}
			else {
				cout << "The user name has been taken, please use another usersname and password:" << endl;
				goto adddd;
			}
		}
		else if (d == '3') {
		condeletinguser:
			cout << "Please enter the user's usersname:" << endl;
			string tun; 
			cin >> tun; 
			int judge = 0, uuu = 0;
			for (unsigned i = 0; i < Vuser.size(); i++) {
				if (tun == Vuser[i].getusersname()) {
					judge = 1; 
					uuu = i;
					break;
				}
			}
			if (judge == 1) {
				cout << "Found the user! Reconfirm Y/N?" << endl; 
				cin.get();
				if (cin.get() == 'Y') {
					Vadmin[n].deleteuser(Vuser[uuu], Vuser);
					cout << "The user has been deleted!" << endl;
					cout << "C: continue deleting.   R: return to the menu." << endl; 
					cin.get();
					char o = cinget();
					if (o == 'C')  
						goto condeletinguser; 
					else if (o == 'R')  
						continue; 
					else { 
						shut(Vbook, Vuser, Vadmin); 
						exit(0);
					}
				}
				else  
					continue; 
			}
			else {
				cout << "The user does not exist!" << endl;
				cout << "T: try again.  R; return to the menu." << endl; 
				cin.get();
				char r = cinget();
				if (r == 'T')  
					goto condeletinguser; 
				else if (r == 'R')  
					continue; 
				else { 
					shut(Vbook, Vuser, Vadmin); 
					exit(0);
				}
			}
		}
		else if (d == '4') {
		conaddingbook:
			cout << "Please enter bookname, ISBN, author, and types:" << endl;
			string tbn, tbi, tba, tt1, tt2, tt3; 
			cin >> tbn >> tbi >> tba >> tt1 >> tt2 >> tt3;
			btemp.setbook(1, tbi, tbn, tba, tt1, tt2, tt3);
			Vadmin[n].addbook(btemp, Vbook);
			cout << "The new book has been added." << endl;
			cout << "C: continue adding.   R: return to the menu." << endl; 
			cin.get();
			char o = cinget();
			if (o == 'C')  
				goto conaddingbook; 
			else if (o == 'R')  
				continue; 
			else { 
				shut(Vbook, Vuser, Vadmin); 
				exit(0);
			}
		}
		else if (d == '5') {
		condeletingbook:
			cout << "Please enter the bookname:" << endl;
			string tbn; 
			cin >> tbn; 
			int judge = 0, uuu = 0;
			for (unsigned i = 0; i < Vbook.size(); i++) {
				if (tbn == Vbook[i].getbookname()) {
					judge = 1; 
					uuu = i;
					break;
				}
			}
			if (judge == 1) {
				cout << "Found the book! Reconfirm Y/N?" << endl; 
				cin.get();
				if (cin.get() == 'Y') {
					Vadmin[n].deletebook(Vbook[uuu], Vbook);
					cout << "The book has been deleted!" << endl;
					cout << "C: continue deleting.   R: return to the menu." << endl; 
					cin.get();
					char o = cinget();
					if (o == 'C')  
						goto condeletingbook; 
					else if (o == 'R')  
						continue; 
					else { 
						shut(Vbook, Vuser, Vadmin); 
						exit(0);
					}
				}
				else { continue; }
			}
			else {
				cout << "The book does not exist!" << endl;
				cout << "T: try again.  R: return to the menu." << endl; 
				cin.get();
				char r = cinget();
				if (r == 'T')  
					goto condeletingbook; 
				else if (r == 'R') 
					continue; 
				else {
					shut(Vbook, Vuser, Vadmin);
					exit(0);
				}
			}
		}
		else if (d == '6') {
		conchangebook:
			cout << "Please enter the bookname:" << endl;
			string tpsr; 
			cin >> tpsr; 
			int jude = 0, e;
			for (unsigned i = 0; i < Vbook.size(); i++) {
				if (tpsr == Vbook[i].getbookname()) {
					jude = 1; e = i; 
					break;
				}
			}
			if (jude == 1) {
				cout << "Found the book!" << endl;
			conthisbook:
				cout << "Now please enter what you want to change:" << endl;
				cout << "1:Bookname 2:ISBN 3:Author 4:Type" << endl; 
				cin.get();
				char y;
				y = cin.get();
				if (y == '1') {
					cout << "Please enter the new bookname:" << endl;
					string v; 
					cin >> v;
					cout << "The new bookname will be: " << v << " Confirm Y/N?" << endl; 
					cin.get();
					if (cin.get() == 'Y') {
						Vbook[e].setbookname(v);
						cout << "New bookname has been set." << endl;
						cout << "C: continue changing the same book.  A: change another book.  R: return to the menu." << endl; cin.get();
						char o = cinget();
						if (o == 'A')  
							goto conchangebook; 
						else if (o == 'C')  
							goto conthisbook; 
						else if (o == 'R') 
							continue; 
						else { 
							shut(Vbook, Vuser, Vadmin); 
							exit(0);
						}
					}
					else { continue; }
				}
				else if (y == '2') {
					cout << "Please enter the new ISBN:" << endl;
					string v; 
					cin >> v;
					cout << "The new ISBN will be:" << v << " Confirm Y/N?" << endl; 
					cin.get();
					if (cin.get() == 'Y') {
						Vbook[e].setISBN(v);
						cout << "New ISBN has been set." << endl;
						cout << "C: continue changing the same book.  A: change another book.  R: return to the menu." << endl; 
						cin.get();
						char o = cinget();
						if (o == 'A') 
							goto conchangebook; 
						else if (o == 'C') 
							goto conthisbook; 
						else if (o == 'R') 
							continue; 
						else {
							shut(Vbook, Vuser, Vadmin); 
							exit(0);
						}
					}
					else { continue; }
				}
				else if (y == '3') {
					cout << "Please enter the new authorname:" << endl;
					string v; 
					cin >> v;
					cout << "The new authorname will be:" << v << " Confirm Y/N?" << endl; 
					cin.get();
					if (cin.get() == 'Y') {
						Vbook[e].setauthorname(v);
						cout << "New authorname has been set." << endl;
						cout << "C: continue changing the same book.  A: change another book.  R: return to the menu." << endl; 
						cin.get();
						char o = cinget();
						if (o == 'A') 
							goto conchangebook; 
						else if (o == 'C') 
							goto conthisbook; 
						else if (o == 'R') 
							continue; 
						else {
							shut(Vbook, Vuser, Vadmin); 
							exit(0);
						}
					}
					else { continue; }
				}
				else if (y == '4') {
					cout << "Please enter the type1, type2 and type3." << endl;
					string ttt1, ttt2, ttt3; 
					cin >> ttt1 >> ttt2 >> ttt3;
					cout << "The new types will be:" << ttt1 << " " << ttt2 << " " << ttt3 << " " << "Confirm Y/N?" << endl; 
					cin.get();
					if (cin.get() == 'Y') {
						Vbook[e].settype1(ttt1);
						Vbook[e].settype2(ttt2);
						Vbook[e].settype3(ttt3);
						cout << "New types has been set." << endl;
						cout << "C: continue changing the same book.  A: change another book.  R: return to the menu." << endl; 
						cin.get();
						char o = cinget();
						if (o == 'A') 
							goto conchangebook; 
						else if (o == 'C') 
							goto conthisbook; 
						else if (o == 'R') 
							continue; 
						else {
							shut(Vbook, Vuser, Vadmin); 
							exit(0);
						}
					}
					else { continue; }
					
				}
			}
			else {
				cout << "The book does not existe!" << endl;
				cout << "A: try agian.  R: return to the menu." << endl; 
				cin.get();
				char r = cinget();
				if (r == 'A') 
					goto conchangebook;
				else if (r == 'R') 
					continue; 
				else { 
					shut(Vbook, Vuser, Vadmin); 
					exit(0);
				}
			}
		}
		else if (d == '7') {
		changeadminagain:
			system("cls");
			cout << "Please enter your old password:" << endl;
		changgge:
			string tp; 
			cin >> tp;
			if (tp == Vadmin[n].getadminpassword()) {
				cout << "Verification passed!" << endl;
				cout << "Now please enter your new password:" << endl;
				cin >> tp;
				cout << "Now please enter it agian:" << endl;
				string tpp; 
				cin >> tpp;
				if (tp == tpp) {
					Vadmin[n].setadminpassword(tp);
					cout << "Password has been changed!" << endl;
					cout << "R: return to the menu." << endl; 
					cin.get();
					if (cin.get() == 'R')  
						continue; 
					else { 
						shut(Vbook, Vuser, Vadmin); 
						exit(0);
					}
				}
				else {
					cout << "Not the same! Please enter it again:" << endl; 
					goto changgge;
				}
			}
			else {
				cout << "Wrong password!" << endl;
				cout << "T: try again.    R: return to the menu." << endl; 
				cin.get();
				char k = cin.get();
				if (k == 'T') 
					goto changeadminagain; 
				else if (k == 'R')  
					continue; 
				else { 
					shut(Vbook, Vuser, Vadmin); 
					exit(0);
				}
			}
		}
		else if (d == '8') {
		conreset:
			cout << "Please enter the user's name:" << endl;
			string uuname; 
			cin >> uuname; 
			int jjud = 0, un;
			for (unsigned i = 0; i < Vuser.size(); i++) {
				if (uuname == Vuser[i].getusersname()) {
					jjud = 1; 
					un = i; 
					break;
				}
			}
			if (jjud == 1) {
				Vuser[un].resetpassword();
				cout << "The user's password has been reset." << endl;
				cout << "C: continue resetting.  R: return to the menu." << endl; 
				cin.get();
				char w = cin.get();
				if (w == 'C')  
					goto conreset; 
				else if (w == 'R')  
					continue; 
				else { 
					shut(Vbook, Vuser, Vadmin); 
					exit(0);
				}
			}
			else {
				cout << "The user doesn't exist!" << endl;
				cout << "T: try again.  R: return to the menu." << endl; 
				cin.get();
				char q = cinget();
				if (q == 'T')  
					goto conreset; 
				else if (q == 'R')  
					continue; 
				else { 
					shut(Vbook, Vuser, Vadmin); 
					exit(0);
				}
			}
		}
		else if (d == '9') {
			Users tmpus; int page = 1; unsigned n = Vuser.size();
		ssss:
			cout << "There are ";
			cout << Vuser.size();
			cout << " users in total." << endl;
			cout << " Usersname               InTimes           BorrowTimes"<<endl;
			for (int i = (page - 1) * 20; i < page * 20 && i < n; i++) { 
				cout << Vuser[i].getusersname() <<"                "<<Vuser[i].getintime()<<"                   "<<Vuser[i].getbooknumber()<< endl; }
				cout << "Page" << page << "/500" << endl;
		show112:
			cout << "L: previous page." << "         " << "R: next page." << "         " << "M: return to the menu." << endl; cin.get();
			char l; l = cin.get();
			if (l == 'L' && page != 1) { page--; system("cls"); goto ssss; }
			else if (l == 'R' && page != 500) { page++; system("cls"); goto ssss; }
			else if (l == 'M') { system("cls"); }
			else if (l == 'L' && page == 1) { cout << "There's no page before that!" << endl; goto show112; }
			else if (l == 'R' && page == 500) { cout << "There's no page after that!" << endl; goto show112; }
		}
		else if (d == '0') { shut(Vbook, Vuser, Vadmin); exit(0);
}
		else {
		cout << "Invalid choice!" << endl;
		cout << "Sorry to shut down the system!";
		shut(Vbook, Vuser, Vadmin);
	}
	}
}

int main()
{
	vector<Book> Vbook;
	vector<Users> Vuser;
	vector<Administrators> Vadmin;
	vector<Record> Vrecord;

	readfile_books(Vbook);
	readfile_adm(Vadmin);
	readfile_users(Vuser);
	

	startinterface();
	char c = cinget();
	if (c == '1') {
		int n;
		n = userlogin(Vbook, Vuser, Vadmin); 
		c = cinget();
		if (Vuser[n].gethead() != NULL) {
			Record* tpr = Vuser[n].gethead();
			if (tpr->getref() == true) { (Vuser[n].getmybook()).push_back(tpr->getmybook()); }
			while (tpr->getnext() != NULL) {
				tpr = tpr->getnext();
				if (tpr->getref() == true) { (Vuser[n].getmybook()).push_back(tpr->getmybook()); }
			}
		}
		Vuser[n].inlibrary();
		Book btemp; Users utemp; 
		usermanip(Vadmin, Vuser, Vbook, Vrecord, c, btemp, utemp, n);
	}
	else if (c == '2') {
		int n;
		n = adminlogin(Vbook, Vuser, Vadmin);
		c = cinget();
		Book btemp; Users utemp; Administrators atemp;
		adminmanip(Vadmin, Vuser, Vbook, Vrecord, c, btemp, utemp, atemp, n);
	}
	else if (c == '3') {
		while (1) {
			system("cls");
			cout << "1.View library book storage." << endl;
			cout << "2.View library users." << endl;
			cout << "3.Shut down the system." << endl; cin.get();
			char s = cin.get();
			if (s == '1') {
				Book tmpbo; tmpbo.showbooks(Vbook);
			}
			else if (s == '2') {
				Users tmpus; int page = 1; unsigned n = Vuser.size();
			ssss:
				cout << "There are ";
				cout << Vuser.size();
				cout << " users in total." << endl;
				cout << " Usersname" << endl;
				for (int i = (page - 1) * 20; i < page * 20 && i < n; i++) { cout << Vuser[i].getusersname() << endl; }
				cout << "Page" << page << "/500" << endl;
			show112:
				cout << "L: previous page." << "         " << "R: next page." << "         " << "M: return to the menu." << endl; cin.get();
				char l; l = cin.get();
				if (l == 'L' && page != 1) { page--; system("cls"); goto ssss; }
				else if (l == 'R' && page != 500) { page++; system("cls"); goto ssss; }
				else if (l == 'M') { system("cls");  }
				else if (l == 'L' && page == 1) { cout << "There's no page before that!" << endl; goto show112; }
				else if (l == 'R' && page == 500) { cout << "There's no page after that!" << endl; goto show112; }
			}
			else if (s == '3') {
				shut(Vbook, Vuser, Vadmin); exit(0);
			}
			else {
				cout << "Invalid choice!" << endl;
				cout << "Sorry to shut down the system!";
				shut(Vbook, Vuser, Vadmin); exit(0);
			}
		}
	}
	else if (c == '4') { shut(Vbook, Vuser, Vadmin); exit(0);
	}
	else {
		cout << "Invalid choice!" << endl;
		cout << "Sorry to shut down the system!";
		shut(Vbook, Vuser, Vadmin); exit(0);
	}
}
