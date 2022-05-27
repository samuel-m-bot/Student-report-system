#include "report.h"
#include<cstring>


void report::create_report(string stud_id,string mod_code){
    cout<<"\nEnter report id: ";
    cin.ignore();
    cin.getline(id,7);
    strncpy(student_id, stud_id.c_str(), sizeof(student_id));
    student_id[sizeof(student_id) - 1] = 0;
    strncpy(module_code, mod_code.c_str(), sizeof(module_code));
    module_code[sizeof(module_code) - 1] = 0;
    cout<<"\n\nEnter the grade for the module: ";
    cin>>grade;
}

void report::view_report() const{
    string id_space,student_id_space,module_code_space="";
    if(strlen(id)!=7){
        for(int i=strlen(id);i<7;i++){
            id_space=id_space+" ";
        }
    }
    if(strlen(student_id)!=15){
        for(int i=strlen(student_id);i<15;i++){
            student_id_space=student_id_space+" ";
        }
    }
    if(strlen(module_code)!=14){
        for(int i=strlen(module_code);i<14;i++){
            module_code_space=module_code_space+" ";
        }
    }
    cout<<"\n"<<id<<id_space<<student_id<<student_id_space<<module_code<<module_code_space<<grade;
}
string report::getstudent_id() const{
    string str(student_id);
    return str;
}
string report::get_id() const{
    string str(id);
    return str;
}
// teacher teacher::fetch_teacher(string n) {
//     teacher teach;
//     ifstream iFile;
//     iFile.open("teacher.dat",ios::binary);
//     if(!iFile){
//         cout<<"File could not be opened... Press any Key to exit";
//         cin.ignore();
//         cin.get();
//         return teach;
//     }
//     bool flag=false;
//     while(iFile.read(reinterpret_cast<char *> (&teach), sizeof(teacher))){
//         if(teach.getid()==n){
//             return teach;
//         }
//     }
//     iFile.close();
//     return teach;
// }