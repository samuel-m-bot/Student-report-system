#include<iostream>
#include<string>
#include<fstream>

using namespace std;
// the class that stores data
class module
{
    private:
        char module_code[7],module_name[25];
    public:
        void getdata();
        void showdata() const;
        string getmodule_code() const;
        module fetch_module(string n);
}; //class ends here