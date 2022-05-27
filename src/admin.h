#include<iostream>
#include<string>
#include<fstream>

using namespace std;
// the class that stores data
class admin
{
    private:
        char id[15],fname[25],sname[25],email[40];
    public:
        void getdata(string,string);
        void showdata() const;
        string getid() const;
        string getemail() const;
        admin fetch_admin(string);
        void create_user() const;
        void create_module() const;
        void create_report() const;
        void display_sp() const;
        void display_all_users() const;
        void display_all_admins() const;
        void display_all_students() const;
        void display_all_teachers() const;
        void display_all_modules() const;
        void display_all_reports() const;
        void display_all_records() const;
        void delete_admin(string);
        void delete_student(string);
        void delete_teacher(string);
        void delete_module(string);
        void delete_report(string);
        void change_student(string);
}; //class ends here