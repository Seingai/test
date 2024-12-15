#ifndef Adm_h
#define Adm_h
#include<string>
#include<iostream>
#include<vector>
#include"book.h"
#include"record.h"
#include"users.h"
using namespace std;
class Administrators
{
	private:
		Record* head;
		string adminpassword;
		string adminnameame;
	public:
		static int adminsum;
		string getadminnameame();
		Administrators();
		void changebookinfo(vector<Book>& Vbook);
		void addbook(Book& b, vector<Book>& Vbook);
		string getadminpassword();
		void changepassword();	
		void adminshowmenu();
		void usersearch(vector<Book>& Vbook);
		void deletebook(Book& b, vector<Book>& Vbook);
		void adduser(Users& u, vector<Users>& Vuser);
		void setadminpassword(string a);
		void deleteuser(Users& u, vector<Users>& Vuser);
		void setadmins(string a, string b);
		void resetuserpassword(Users& u);
		vector<Users>::iterator ituser;
		vector<Book>::iterator itbook;
};
#endif

