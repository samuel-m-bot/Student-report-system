#include "admin.h"
#include "student.h"
#include "teacher.h"
#include "user.h"
#include "module.h"
#include "report.h"
#include<cstring>
#include <vector>

// the class that stores data

void admin::getdata(string i_id,string i_email){
    strncpy(id, i_id.c_str(), sizeof(id));
    id[sizeof(id) - 1] = 0;
    strncpy(email, i_email.c_str(), sizeof(email));
    email[sizeof(email) - 1] = 0;
    cout<<"\n\nEnter admin first name: ";
    cin.getline(fname,25);
    cout<<"\n\nEnter admin surname name: ";
    cin.getline(sname,25);
}

void admin::showdata() const{
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

string admin::getid() const{
    string str(id);
    return str;
}
string admin::getemail() const{
    string str(email);
    return str;
}
admin admin::fetch_admin(string n) {
    admin adm;
    ifstream iFile;
    iFile.open("admin.dat",ios::binary);
    if(!iFile){
        cout<<"File could not be opened... Press any Key to exit";
        cin.ignore();
        cin.get();
        return adm;
    }
    bool flag=false;
    while(iFile.read(reinterpret_cast<char *> (&adm), sizeof(admin))){
        if(adm.getid()==n){
            return adm;
        }
    }
    iFile.close();
    return adm;
}
void admin::create_user() const{
    user use;
    ofstream oFile;
    oFile.open("user.dat",ios::binary|ios::app);
    use.getdata();
    oFile.write(reinterpret_cast<char *> (&use), sizeof(user));
    oFile.close();
    cout<<"\n\nUser record Has Been Created ";
    string store="";
    store=(use.getid()).substr(0,2);
    if(store=="UG"||store=="MA"||store=="PH"){
        student stud;
        ofstream oFile_s;
        oFile_s.open("student.dat",ios::binary|ios::app);
        stud.getdata(use.getid(),use.getemail());
        oFile_s.write(reinterpret_cast<char *> (&stud), sizeof(student));
        oFile_s.close();
        cout<<"\n\nStudent record Has Been Created ";
    }else if(store=="TE"){
        teacher teach;
        ofstream oFile_t;
        oFile_t.open("teacher.dat",ios::binary|ios::app);
        teach.getdata(use.getid(),use.getemail());
        oFile_t.write(reinterpret_cast<char *> (&teach), sizeof(teacher));
        oFile_t.close();
        cout<<"\n\nTeacher record Has Been Created ";
    }else if(store=="AD"){
        admin adm;
        ofstream oFile_a;
        oFile_a.open("admin.dat",ios::binary|ios::app);
        adm.getdata(use.getid(),use.getemail());
        oFile_a.write(reinterpret_cast<char *> (&adm), sizeof(admin));
        oFile_a.close();
        cout<<"\n\nAdmin record Has Been Created ";
    }
    cin.ignore();
    cin.get();
}
void admin::create_module() const{
    module mod;
    ofstream oFile;
    oFile.open("module.dat",ios::binary|ios::app);
    mod.getdata();
    oFile.write(reinterpret_cast<char *> (&mod), sizeof(module));
    oFile.close();
    cout<<"\n\nModule record Has Been Created ";
    cin.ignore();
    cin.get();
}
void admin::display_sp() const{
    student stud;
    ifstream iFile;
    string n;
    iFile.open("student.dat",ios::binary);
    if(!iFile){
        cout<<"File could not be opened... Press any Key to exit";
        cin.ignore();
        cin.get();
    return;
    }
    cout<<"\n\n\tEnnter id of student: ";
    getline(cin,n);
    bool flag=false;
    while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student))){
        if(stud.getid()==n){
            stud.showdata();
            flag=true;
        }
    }
    iFile.close();
    if(flag==false)
        cout<<"\n\nrecord does not exist";
        cin.ignore();
        cin.get();
}
void admin::create_report() const{
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
void admin::display_all_users() const{
    user use;
    ifstream inFile;
    inFile.open("user.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"----------------------------------------------------\n";
    cout<<"------DISPLAYING ALL USER RECORDS-------------------\n";
    cout<<"\nID----------Email-----------------------------------";
    cout<<"\n----------------------------------------------------";
    while(inFile.read(reinterpret_cast<char *> (&use), sizeof(user))){
        use.showdata();
    }
    inFile.close();
}
void admin::display_all_admins() const{
    admin adm;
    ifstream inFile;
    inFile.open("admin.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"------------------------------------------------------------------------------------------------------\n";
    cout<<"------------------------------DISPLAYING ALL ADMIN RECORDS--------------------------------------------\n";
    cout<<"\nID----------First name---------------Surname------------------Email-----------------------------------";
    cout<<"\n------------------------------------------------------------------------------------------------------";
    while(inFile.read(reinterpret_cast<char *> (&adm), sizeof(admin))){
        adm.showdata();
    }
    inFile.close();
}
void admin::display_all_students() const{
    student stud;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"---------------------------------------------------------------------------------------------------------\n";
    cout<<"------------------------------DISPLAYING ALL STUDENTS RECORDS--------------------------------------------\n";
    cout<<"\nID----------First name---------------Surname------------------Email-----------------------------------Age";
    cout<<"\n---------------------------------------------------------------------------------------------------------";
    while(inFile.read(reinterpret_cast<char *> (&stud), sizeof(student))){
        stud.showdata();
    }
    inFile.close();
}
void admin::display_all_teachers() const{
    teacher stud;
    ifstream inFile;
    inFile.open("teacher.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"------------------------------------------------------------------------------------------------------\n";
    cout<<"------------------------------DISPLAYING ALL TEACHER RECORDS------------------------------------------\n";
    cout<<"\nID----------First name---------------Surname------------------Email-----------------------------------";
    cout<<"\n------------------------------------------------------------------------------------------------------";
    while(inFile.read(reinterpret_cast<char *> (&stud), sizeof(teacher))){
        stud.showdata();
    }
    inFile.close();
}
void admin::display_all_modules() const{
    module mod;
    ifstream inFile;
    inFile.open("module.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"----------------------------------------------------\n";
    cout<<"------DISPLAYING ALL MODULE RECORDS-----------------\n";
    cout<<"\nModule code---Module name---------------------------";
    cout<<"\n----------------------------------------------------";
    while(inFile.read(reinterpret_cast<char *> (&mod), sizeof(module))){
        mod.showdata();
    }
    inFile.close();
}
void admin::display_all_reports() const{
    report rep;
    ifstream inFile;
    inFile.open("report.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"-----------------------------------------\n";
    cout<<"-----DISPLAYING ALL REPORT RECORDS-------\n";
    cout<<"\nID-----Student_id-----Module_code---Grade";
    cout<<"\n-----------------------------------------";
    while(inFile.read(reinterpret_cast<char *> (&rep), sizeof(report))){
        rep.view_report();
    }
    inFile.close();
}
void admin::display_all_records() const{
    this->display_all_users();
    cout<<"\n\n";
    this->display_all_admins();
    cout<<"\n\n";
    this->display_all_students();
    cout<<"\n\n";
    this->display_all_teachers();
    cout<<"\n\n";
    this->display_all_modules();
    cout<<"\n\n";
    this->display_all_reports();
}
void admin::delete_admin(string n){
    admin adm;
    user use;
    ifstream iFile,iFile_2;
    bool found=false;
    iFile.open("admin.dat",ios::binary);
    if(!iFile){
        cout<<"File could not be opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    iFile_2.open("user.dat",ios::binary);
    if(!iFile_2){
        cout<<"File could not be opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile,oFile_2;
    oFile.open("admin.dat",ios::out);
    iFile.seekg(0,ios::beg);
    while(iFile.read(reinterpret_cast<char *> (&adm), sizeof(admin))){
        if(adm.getid()!=n){
            oFile.write(reinterpret_cast<char *> (&adm), sizeof(admin));
        }
        if(adm.getid()==n){
            found=true;
        }
    }
    oFile_2.open("Temp_2.dat",ios::out);
    iFile_2.seekg(0,ios::beg);
    while(iFile_2.read(reinterpret_cast<char *> (&use), sizeof(user))){
        if(use.getid()!=n){
            oFile_2.write(reinterpret_cast<char *> (&use), sizeof(user));
        }
        if(use.getid()==n){
            found=true;
        }
    }
    oFile.close();
    iFile.close();
    oFile_2.close();
    iFile_2.close();
    remove("admin.dat");
    rename("Temp.dat","admin.dat");
    remove("user.dat");
    rename("Temp_2.dat","user.dat");
    if(found){
        cout<<"\n\n\tRecord Deleted ..";
    }else{
        cout<<"\n\n\tID was not found";
    }
    cin.ignore();
    cin.get();
}
void admin::delete_student(string n){
    student stud;
    user use;
    ifstream iFile,iFile_2;
    bool found=false;
    iFile.open("student.dat",ios::binary);
    if(!iFile){
        cout<<"File could not be opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    iFile_2.open("user.dat",ios::binary);
    if(!iFile_2){
        cout<<"File could not be opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile,oFile_2;
    oFile.open("Temp.dat",ios::out);
    iFile.seekg(0,ios::beg);
    while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student))){
        if(stud.getid()!=n){
            oFile.write(reinterpret_cast<char *> (&stud), sizeof(student));
        }
        if(stud.getid()==n){
            found=true;
        }
    }
    oFile_2.open("Temp_2.dat",ios::out);
    iFile_2.seekg(0,ios::beg);
    while(iFile_2.read(reinterpret_cast<char *> (&use), sizeof(user))){
        if(use.getid()!=n){
            oFile_2.write(reinterpret_cast<char *> (&use), sizeof(user));
        }
        if(use.getid()==n){
            found=true;
        }
    }
    oFile.close();
    iFile.close();
    oFile_2.close();
    iFile_2.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    remove("user.dat");
    rename("Temp_2.dat","user.dat");
    if(found){
        cout<<"\n\n\tRecord Deleted ..";
    }else{
        cout<<"\n\n\tID was not found";
    }
    cin.ignore();
    cin.get();
}
void admin::delete_teacher(string n){
    teacher teach;
    user use;
    ifstream iFile,iFile_2;
    bool found=false;
    iFile.open("teacher.dat",ios::binary);
    if(!iFile){
        cout<<"File could not be opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    iFile_2.open("user.dat",ios::binary);
    if(!iFile_2){
        cout<<"File could not be opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile,oFile_2;
    oFile.open("Temp.dat",ios::out);
    iFile.seekg(0,ios::beg);
    while(iFile.read(reinterpret_cast<char *> (&teach), sizeof(teacher))){
        if(teach.getid()!=n){
            oFile.write(reinterpret_cast<char *> (&teach), sizeof(teacher));
        }
        if(teach.getid()==n){
            found=true;
        }
    }
    oFile_2.open("Temp_2.dat",ios::out);
    iFile_2.seekg(0,ios::beg);
    while(iFile_2.read(reinterpret_cast<char *> (&use), sizeof(user))){
        if(use.getid()!=n){
            oFile_2.write(reinterpret_cast<char *> (&use), sizeof(user));
        }
        if(use.getid()==n){
            found=true;
        }
    }
    oFile.close();
    iFile.close();
    oFile_2.close();
    iFile_2.close();
    remove("teacher.dat");
    rename("Temp.dat","teacher.dat");
    remove("user.dat");
    rename("Temp_2.dat","user.dat");
    if(found){
        cout<<"\n\n\tRecord Deleted ..";
    }else{
        cout<<"\n\n\tID was not found";
    }
    cin.ignore();
    cin.get();
}
void admin::delete_module(string n){
    module mod;
    ifstream iFile;
    iFile.open("module.dat",ios::binary);
    if(!iFile){
        cout<<"File could not be opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("Temp.dat",ios::out);
    iFile.seekg(0,ios::beg);
    while(iFile.read(reinterpret_cast<char *> (&mod), sizeof(module))){
        if(mod.getmodule_code()!=n){
            oFile.write(reinterpret_cast<char *> (&mod), sizeof(student));
        }
    }
    oFile.close();
    iFile.close();
    remove("module.dat");
    rename("Temp.dat","module.dat");
    cout<<"\n\n\tRecord Deleted ..";
    cin.ignore();
    cin.get();
}
void admin::delete_report(string n){
    report rep;
    ifstream iFile;
    iFile.open("report.dat",ios::binary);
    if(!iFile){
        cout<<"File could not be opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("Temp.dat",ios::out);
    iFile.seekg(0,ios::beg);
    while(iFile.read(reinterpret_cast<char *> (&rep), sizeof(report))){
        if(rep.get_id()!=n){
            oFile.write(reinterpret_cast<char *> (&rep), sizeof(report));
        }
    }
    oFile.close();
    iFile.close();
    remove("report.dat");
    rename("Temp.dat","report.dat");
    cout<<"\n\n\tRecord Deleted ..";
    cin.ignore();
    cin.get();
}
void admin::change_student(string n){
    string email,id;
    bool found=false;
    student stud;
    fstream fl;
    fl.open("student.dat",ios::binary|ios::in|ios::out);
    if(!fl){
        cout<<"File could not be opened. Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    while(!fl.eof() && found==false){
        fl.read(reinterpret_cast<char *> (&stud), sizeof(student));
        if(stud.getid()==n){
            stud.showdata();
            cout<<"\nEnter new student details:"<<endl;
            cout<<"\n\n\tEnter new id: ";
            getline(cin,id);
            cout<<"\n\n\tEnter new email: ";
            getline(cin,email);
            stud.getdata(id,email);
            int pos=(-1)*static_cast<int>(sizeof(stud));
            fl.seekp(pos,ios::cur);
            fl.write(reinterpret_cast<char *> (&stud), sizeof(student));
            cout<<"\n\n\t Record Updated";
            found=true;
        }
    }
    fl.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
        cin.ignore();
        cin.get();
}