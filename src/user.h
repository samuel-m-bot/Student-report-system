#include<iostream>
#include<string>
#include<fstream>

using namespace std;
// the class that stores data
class user
{
    private:
        char id[15],email[40],password[20];
    public:
        void getdata();
        void showdata() const;
        string getid() const;
        string getemail() const;
        string getpassword() const;
        user fetch_user(string,string);
}; //class ends here