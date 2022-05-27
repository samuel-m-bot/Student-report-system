#include<iostream>
#include<string>
#include<fstream>

using namespace std;
// the class that stores data
class teacher
{
    private:
        char id[15],fname[25],sname[25],email[40];
    public:
        void getdata(string,string);
        void showdata() const;
        string getid() const;
        string getemail() const;
        string getpassword() const;
        teacher fetch_teacher(string n);
        void create_report() const;
}; //class ends here