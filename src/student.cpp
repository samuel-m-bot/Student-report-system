#include "student.h"
#include "report.h"
#include<cstring>

// the class that stores data

void student::getdata(string i_id,string i_email){
    strncpy(id, i_id.c_str(), sizeof(id));
    id[sizeof(id) - 1] = 0;
    strncpy(email, i_email.c_str(), sizeof(email));
    email[sizeof(email) - 1] = 0;
    cout<<"\n\nEnter student first name: ";
    cin.getline(fname,25);
    cout<<"\n\nEnter student Surname name: ";
    cin.getline(sname,25);
    cout<<"\n\nEnter student age: ";
    cin>>age;
}

void student::showdata() const{
    string id_space,fname_space,sname_space,email_space="";
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
    if(strlen(email)!=40){
        for(int i=strlen(email);i<40;i++){
            email_space=email_space+" ";
        }
    }
    cout<<"\n"<<id<<id_space<<fname<<fname_space<<sname<<sname_space<<email<<email_space<<age;
}

string student::getid() const{
    string str(id);
    return str;
}
string student::getemail() const{
    string str(email);
    return str;
}
student student::fetch_student(string n) {
    student stud;
    ifstream iFile;
    iFile.open("student.dat",ios::binary);
    if(!iFile){
        cout<<"File could not be opened... Press any Key to exit";
        cin.ignore();
        cin.get();
        return stud;
    }
    bool flag=false;
    while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student))){
        if(stud.getid()==n){
            return stud;
        }
    }
    iFile.close();
    return stud;
}
void student::view_reports() const{
    report rep;
    ifstream iFile;
    iFile.open("report.dat",ios::binary);
    if(!iFile){
        cout<<"File could not be opened... Press any Key to exit";
        cin.ignore();
        cin.get();
    return;
    }
    bool flag=false;
    while(iFile.read(reinterpret_cast<char *> (&rep), sizeof(report))){
        if(rep.getstudent_id()==id){
            rep.view_report();
            cout<<"\n====================================\n";
            flag=true;
        }
    }
    iFile.close();
    if(flag==false)
        cout<<"\n\nYou have no reports";
        cin.ignore();
        cin.get();
}