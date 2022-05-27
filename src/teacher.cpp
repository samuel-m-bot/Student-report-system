#include "teacher.h"
#include "student.h"
#include "module.h"
#include "report.h"
#include<cstring>
#include <vector>

// the class that stores data

void teacher::getdata(string i_id,string i_email){
    strncpy(id, i_id.c_str(), sizeof(id));
    id[sizeof(id) - 1] = 0;
    strncpy(email, i_email.c_str(), sizeof(email));
    email[sizeof(email) - 1] = 0;
    cout<<"\n\nEnter teacher first name: ";
    cin.getline(fname,25);
    cout<<"\n\nEnter teacher Surname name: ";
    cin.getline(sname,25);
}

void teacher::showdata() const{
    string id_space,fname_space,sname_space="";
    if(strlen(id)!=12){
        for(int i=strlen(id);i<12;i++){
            id_space=id_space+" ";
        }
    }
    if(strlen(fname)!=25){
        for(int i=strlen(fname);i<25;i++){
            fname_space=fname_space+" ";
        }
    }
    if(strlen(sname)!=25){
        for(int i=strlen(sname);i<25;i++){
            sname_space=sname_space+" ";
        }
    }
    cout<<"\n"<<id<<id_space<<fname<<fname_space<<sname<<sname_space<<email;
}

string teacher::getid() const{
    string str(id);
    return str;
}
string teacher::getemail() const{
    string str(email);
    return str;
}
teacher teacher::fetch_teacher(string n) {
    teacher teach;
    ifstream iFile;
    iFile.open("teacher.dat",ios::binary);
    if(!iFile){
        cout<<"File could not be opened... Press any Key to exit";
        cin.ignore();
        cin.get();
        return teach;
    }
    bool flag=false;
    while(iFile.read(reinterpret_cast<char *> (&teach), sizeof(teacher))){
        if(teach.getid()==n){
            return teach;
        }
    }
    iFile.close();
    return teach;
}
void teacher::create_report() const{
    std::vector< string > arr_m;
    int pick=0;
    module mod;
    ifstream inFile;
    inFile.open("module.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\n\t\tDISPLAYING ALL MODULES\n\n";
    while(inFile.read(reinterpret_cast<char *> (&mod), sizeof(module))){
        arr_m.push_back(mod.getmodule_code());
    }
    inFile.close();
    for (size_t i = 0; i < arr_m.size(); ++i) {
        cout << i<<") "<< arr_m.at(i) << endl;
    }
    cout<<"\n\nSELECT MODULE\n";
    cin>>pick;
    cout<<"\n\nYOU SELECTED: "<<arr_m[pick];

    std::vector< string > arr_s;
    int pick_2=0;
    student stu;
    ifstream inFile_2;
    inFile_2.open("student.dat",ios::binary);
    if(!inFile_2){
        cout<<"File could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\n\t\tDISPLAYING ALL STUDENTS\n\n";
    while(inFile_2.read(reinterpret_cast<char *> (&stu), sizeof(student))){
        arr_s.push_back(stu.getid());
    }
    inFile_2.close();
    for (size_t i = 0; i < arr_s.size(); ++i) {
        cout << i<<") "<< arr_s.at(i) << endl;
    }
    cout<<"\n\nSELECT STUDENTS\n";
    cin>>pick_2;
    cout<<"\n\nYOU SELECTED: "<<arr_s[pick_2];
    report rep;
    ofstream oFile;
    oFile.open("report.dat",ios::binary|ios::app);
    rep.create_report(arr_s[pick_2],arr_m[pick]);
    oFile.write(reinterpret_cast<char *> (&rep), sizeof(report));
    oFile.close();
    cout<<"\n\nReport for student: "<<arr_s[pick_2]<< " for module: "<<arr_m[pick]<<" has been created";
    cin.ignore();
    cin.get();
}