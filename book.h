#ifndef book_h
#define book_h
#include <iostream>
#include<string>
#include<vector>
#include<string.h>
#include<iomanip>
using namespace std;

class Book
{
	public:
		Book();
		~Book();
		static int booksum;
		
		string getbookname();
		string getauthorname();
		string gettype1();
		string gettype2();
		string gettype3();
		string getISBN();
		bool getexistance();

		void borrow();
		void returnbook();
		
		void setbookname(string a);
		void setauthorname(string a);
		void setISBN(string a);
		void settype1(string a);
		void settype2(string a);
		void settype3(string a);
		void setbook(bool f, string I, string book_name, string aname, string t1, string t2, string t3);
		
		
		void search( vector<Book>& Vbook);
		void showbooks( vector<Book>& b);

		friend ostream& operator <<(ostream& output, Book b)
		{
			output << b.ISBN << "      " << setw(4) << b.bookname << "               " << setw(3) << b.authorname << "         " << b.type1 << " " << b.type2 << " " << b.type3;
			return output;
		}
		friend bool operator ==(Book a, Book b)
		{
			if (a.bookname == b.bookname && a.ISBN == b.ISBN)
				return true;
			else
				return false;
		}


    private:
		bool existance;
		string bookname, authorname;
		string ISBN;
		string type1, type2, type3;
};
#endif

