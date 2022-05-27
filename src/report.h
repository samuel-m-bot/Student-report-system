#include<iostream>
#include<string>
#include<fstream>

using namespace std;
// the class that stores data
class report
{
    private:
        char id[7],student_id[15],module_code[7];
        int grade;
    public:
        void create_report(string,string);
        void view_report()const;
        string getstudent_id() const;
        string get_id() const;
}; //class ends here