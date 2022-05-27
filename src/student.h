#include<iostream>
#include<string>
#include<fstream>

using namespace std;
// the class that stores data
class student
{
    private:
        int age;
        char id[15],fname[25],sname[25],email[40];
    public:
        void getdata(string,string);
        void showdata() const;
        string getid() const;
        string getemail() const;
        string getpassword() const;
        student fetch_student(string);
        void view_reports() const;
}; //class ends here