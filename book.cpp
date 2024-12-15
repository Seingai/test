#include "book.h"
#include"users.h"
#include<string>
#include<algorithm>
#include<functional>
using namespace std;

int Book::booksum = 0;
bool cmpDic(Book a, Book b) { return a.getbookname() < b.getbookname(); }
bool cmpTypes(Book a, Book b) {
	if (a.gettype1() == b.gettype1()) {
		if (a.gettype2() == b.gettype2()) {
			if (a.gettype3() == b.gettype3()) {
				{return a.getbookname() < b.getbookname(); }
			}
			else {
				string x = a.gettype3(); string y = b.gettype3();
				return x[2] < y[2];
			}
		}
		else {
			string x = a.gettype2(); string y = b.gettype2();
			return x < y;
		}
	}
	else { return a.gettype1() < b.gettype1(); }
}

Book::Book() { existance = 1; booksum++; bookname = " "; ISBN = " "; type1 = ""; type2 = ""; type3 = ""; }



string Book::getbookname() { return bookname; }
string Book::getauthorname() { return authorname; }
string Book::gettype1() { return type1; }
string Book::gettype2() { return type2; }
string Book::gettype3() { return type3; }
string Book::getISBN() { return ISBN; }
bool Book::getexistance() { return existance; }

void Book::borrow() {
	if (existance == 0) cout << "The book has been borrowed！" << endl;
	else { existance = 0; cout << "Sccessful book borrowing！" << endl; }
}
void Book::returnbook() {
	if (existance == 1) cout << "You didn't borrow the book！" << endl;
	else { existance = 1; cout << "Sccessful book returning！" << endl; }
}
void Book::setbook(bool f, string I, string book_name, string aname, string t1, string t2, string t3) 
	{existance = f; ISBN = I; bookname = book_name; authorname = aname; type1 = t1; type2 = t2; type3 = t3; }


void Book::settype2(string a) { type2 = a; }
void Book::setauthorname(string a) { authorname = a; }

void Book::settype3(string a) { type3 = a; }
void Book::setISBN(string a) { ISBN = a; }
void Book::settype1(string a) { type1 = a; }
void Book::setbookname(string a) { bookname = a; }
void Book::search(vector<Book>& Vbook) {
	unsigned n = Vbook.size();
Searchingcontinue:
	cout << "1:Bookname 2:ISBN 3:Author 4:Type" << endl; cin.get();
	string y;
	y = cin.get();
	if (y == "1") { 
		cout << "Input the Bookname please:"; string shuming; cin >> shuming;
		int j = 0;
		for (unsigned i = 0; i < n; i++)
			if (shuming == Vbook[i].bookname) {
				j = 1; cout << "Found!" << endl << "    ISBN          Bookname          Author          Type" << endl << Vbook[i] << endl << "Continue searching Y/N?" << endl; cin.get();
				if (cin.get() == 'Y') goto Searchingcontinue; else { system("cls");/*显示上一层菜单*/   break; }
			}//未完成
		if (j == 0) {
			cout << "Sorry, couldn't find it!" << endl << "Continue searching Y/N?" << endl; cin.get();
			if (cin.get() == 'Y') goto Searchingcontinue; else { system("cls");/*显示上一层菜单*/ 
			}
		}//未完成 
	}
	else if(y == "2") {
		cout << "Input the ISBN please:"; string isbn; cin >> isbn;
		int j = 0;
		for (unsigned i = 0; i < n; i++)
			if (isbn == Vbook[i].ISBN) {
				j = 1; cout << "Found!" << endl << "    ISBN          Bookname          Author          Type" << endl << Vbook[i] << endl << "Continue searching Y/N?" << endl; cin.get();
				if (cin.get() == 'Y') goto Searchingcontinue; else { system("cls");/*显示上一层菜单*/ break; }
			}//未完成
		if (j == 0) {
			cout << "Sorry, couldn't find it!" << endl << "Continue searching Y/N?" << endl; cin.get();
			if (cin.get() == 'Y') goto Searchingcontinue; else { system("cls");/*显示上一层菜单*/
			}
		}//未完成 
	}
	else if (y == "3") {
		string zuozhe; vector<Book> tempbook; 
		cout << "Input the Author please:"; cin >> zuozhe;
		for (unsigned i = 0; i < n; i++)
		{
			if (Vbook[i].authorname == zuozhe)
			{
				tempbook.push_back(Vbook[i]);
			}
		}
		if (tempbook.size() != 0)
		{
			int page = 1;
			sort(tempbook.begin(), tempbook.end(), cmpDic);
		Showing1:
			cout << "Found!" << endl << "    ISBN          Bookname          Author          Type" << endl;
			for (int i = (page - 1) * 20; i < page * 20 && i < tempbook.size(); i++) { cout << tempbook[i] << endl; }
			cout << "                          Page" << page << "/500" << endl;
		show111:
			cout << "L: previous page." << "         " << "R: next page." << "         " << "M: return to the menu." << "         "<<"C: continue searching."<<endl; cin.get();
			char l; l = cin.get();
			if (l == 'L' && page != 1) { page--; system("cls"); goto Showing1; }
			else if (l == 'R' && page != 500) { page++; system("cls"); goto Showing1; }
			else if (l == 'C') { system("cls"); goto Searchingcontinue;/*显示上一层菜单*/ }//未完成
			else if (l == 'M') { system("cls"); }
			else if (l == 'L' && page == 1) { cout << "There's no page before that!" << endl; goto show111; }
			else if (l == 'R' && page == 500) { cout << "There's no page after that!" << endl; goto show111; }
			
		}
		else {
			cout << "Sorry, couldn't find it!" << endl << "Continue searching Y/N?" << endl; cin.get();
		}
		if (cin.get() == 'Y') { goto Searchingcontinue; }
		else { system("cls");/*显示上一层菜单*/ }
	}
	else if (y == "4") {
		cout << "Input the Type(A, A1 or A11 etc) please:"<<endl; string t; cin >> t;
		if (t.length() == 1) {
			vector<Book> temp; int page = 1;
			for (unsigned i = 0; i < n; i++)
				if (t == Vbook[i].type1) {
					temp.push_back(Vbook[i]);
				}
			if (temp.size()!= 0) {
				sort(temp.begin(), temp.end(), cmpDic); 
			tpye1:
				cout << "Found!" << endl << "    ISBN          Bookname          Author          Type" << endl;
				for (int i = (page - 1) * 20; i < page * 20 && i < temp.size(); i++) { cout << temp[i] << endl; }
				cout << "                          Page" << page << "/500" << endl;
			tpye11:
				cout << "L: previous page." << "         " << "R: next page." << "         " << "M: return to the menu." << "         " << "C: continue searching." << endl; cin.get();
				char l; l = cin.get();
				if (l == 'L' && page != 1) { page--; system("cls"); goto tpye1; }
				else if (l == 'R' && page != 500) { page++; system("cls"); goto tpye1; }
				else if (l == 'C') { system("cls"); goto Searchingcontinue;/*显示上一层菜单*/ }//未完成
				else if (l == 'M') { system("cls"); }
				else if (l == 'L' && page == 1) { cout << "There's no page before that!" << endl; goto tpye11; }
				else if (l == 'R' && page == 500) { cout << "There's no page after that!" << endl; goto tpye11; }
			}
			else {cout << "Sorry, couldn't find it!" << endl << "Continue searching Y/N?" << endl; cin.get();}
			if (cin.get() == 'Y') { goto Searchingcontinue; }
			else { system("cls");/*显示上一层菜单*/ }
		}
		else if (t.length() == 2) {
			vector<Book> temp; int page = 1;
			for (unsigned i = 0; i < n; i++)
				if (t == Vbook[i].type2) {
					temp.push_back(Vbook[i]);
				}
			if (temp.size() != 0) {
				sort(temp.begin(), temp.end(), cmpDic); 
			tpye2:
				cout << "Found!" << endl << "    ISBN          Bookname          Author          Type" << endl;
				for (int i = (page - 1) * 20; i < page * 20 && i < temp.size(); i++) { cout << temp[i] << endl; }
				cout << "                          Page" << page << "/500" << endl;
			tpye22:
				cout << "L: previous page." << "         " << "R: next page." << "         " << "M: return to the menu." << "         " << "C: continue searching." << endl; cin.get();
				char l; l = cin.get();
				if (l == 'L' && page != 1) { page--; system("cls"); goto tpye2; }
				else if (l == 'R' && page != 500) { page++; system("cls"); goto tpye2; }
				else if (l == 'C') { system("cls"); goto Searchingcontinue;/*显示上一层菜单*/ }//未完成
				else if (l == 'M') { system("cls"); }
				else if (l == 'L' && page == 1) { cout << "There's no page before that!" << endl; goto tpye22; }
				else if (l == 'R' && page == 500) { cout << "There's no page after that!" << endl; goto tpye22; }
			}
			else { cout << "Sorry, couldn't find it!" << endl << "Continue searching Y/N?" << endl; cin.get(); }
			if (cin.get() == 'Y') { goto Searchingcontinue; }
			else { system("cls");/*显示上一层菜单*/ }
		}
		else if (t.length() == 3) {
			vector<Book> temp; int page = 1;
			for (unsigned i = 0; i < n; i++)
				if (t == Vbook[i].type3) {
					temp.push_back(Vbook[i]);
				}
			if (temp.size() != 0) {
				sort(temp.begin(), temp.end(), cmpDic); 
			tpye3:
				cout << "Found!" << endl << "    ISBN          Bookname          Author          Type" << endl;
				for (int i = (page - 1) * 20; i < page * 20 && i < temp.size(); i++) { cout << temp[i] << endl; }
				cout << "                          Page" << page << "/500" << endl;
			tpye33:
				cout << "L: previous page." << "         " << "R: next page." << "         " << "M: return to the menu." << "         " << "C: continue searching." << endl; cin.get();
				char l; l = cin.get();
				if (l == 'L' && page != 1) { page--; system("cls"); goto tpye3; }
				else if (l == 'R' && page != 500) { page++; system("cls"); goto tpye3; }
				else if (l == 'C') { system("cls"); goto Searchingcontinue;/*显示上一层菜单*/ }//未完成
				else if (l == 'M') { system("cls"); }
				else if (l == 'L' && page == 1) { cout << "There's no page before that!" << endl; goto tpye33; }
				else if (l == 'R' && page == 500) { cout << "There's no page after that!" << endl; goto tpye33; }
			}
			else { cout << "Sorry, couldn't find it!" << endl << "Continue searching Y/N?" << endl; cin.get(); }
			if (cin.get() == 'Y') { goto Searchingcontinue; }
			else { system("cls");/*显示上一层菜单*/ }
		}
	}

}
void Book::showbooks(vector<Book>& b) {
	int page = 1;
Showing:
	system("cls");
	int n = b.size();
	sort(b.begin(), b.end(), cmpTypes);
	cout << "    ISBN          Bookname          Author          Type" << endl;
	for (int i = (page - 1) * 20; i < page * 20 && i < n; i++) { cout << b[i] << endl; }
	cout << "                          Page"<<page<<"/500" << endl;
show11:
	cout << "L: previous page." << "         " << "R: next page." << "         " << "M: return to the menu." << endl; cin.get();
	char l; l = cin.get();
	if (l == 'L' && page != 1 ) { page--; system("cls"); goto Showing; }
	else if (l == 'R' && page != 500 ) { page++; system("cls"); goto Showing; }
	else if (l == 'M') { system("cls"); /*显示上一层菜单*/}//未完成
	else if (l == 'L' && page == 1) { cout << "There's no page before that!" << endl; goto show11; }
	else if (l == 'R' && page == 500) { cout << "There's no page after that!" << endl; goto show11; }
}
Book::~Book() { booksum--; }
