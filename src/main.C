#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include <vector>
#include "admin.h"
#include "student.h"
#include "teacher.h"
#include "module.h"
#include "report.h"
#include "user.h"

using namespace std;
//function declaration
void create_user();//create a user class and store in data file
void change_student(string);//edit particular student record
bool login(string,string);//login to system
string checkforaccount(string ema, string pass);//checks all user data files for input
void choose_display(admin);//options for which records the admin can dispaly
void choose_delete(admin);//options for which records the admin can delete
void logged_in_options(user);//main mnue for users after they login
//MAIN
int main(){
    char ch;//used for user input throughout whole system
    int login_times=3;
    string current_id="";
    string email,password;
    system("clear");//clears screen
    cout<<"\n\n\t1.Login";
    cout<<"\n\n\t2.Create user";
    cout<<"\n\nWhat is your Choice (1/2) ";
    cin>>ch;
    if(ch=='1'){       //option for logging into system
        cin.ignore();
        system("clear");
        cout<<"\n\n\tLogin ";
        cout<<"\n-----------------------------------";
        do{
            cout<<"\n\n\tEnter email: ";
            getline(cin,email);
            cout<<"\n\n\tEnter password: ";
            getline(cin,password); 
            if(!login(email,password)){ //passes user input to check for account in data files
                login_times--;
                continue;
            }else{
                user current_user;
                current_user=current_user.fetch_user(email,password); //fetched the user object from data files
                logged_in_options(current_user);  //loads menue option for particular user
                break;
            }
        }while(login_times>0);
        if(login_times==0){
            cout<<"\nYou have exceded the max login times. Exiting program\n\n";
        }
    }else if(ch='2'){
        create_user(); //creates a user object and stores it into the 'user'data file
        system("clear");
        cout<<"\n\n\tLogin ";
        cout<<"\n-----------------------------------";
        do{
            cout<<"\n\n\tEnter email: ";
            getline(cin,email);
            cout<<"\n\n\tEnter password: ";
            getline(cin,password);
            if(!login(email,password)){
                login_times--;
                continue;
            }else{
                user current_user;
                current_user=current_user.fetch_user(email,password);
                logged_in_options(current_user);
                break;
            }
        }while(login_times>0);
        if(login_times==0){
            cout<<"\nYou have exceded the max login times. Exiting program\n\n";
        }
    }
    return 0;
}
//creates a user object and stores it into the 'user'data file
void create_user(){
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
//Will check for email and password and return ture if a user accounts exits or false if it doesent
bool login(string email,string password){
    string id;
    id=checkforaccount(email,password);
    if(id==""){
        cout<<"\nIncorrect email and password";
        return false;
    }else if(id=="pass"){
        cout<<"\nIncorrect password";
        return false;
    }else{
        return true;
    }
}
//goes through 'user' data file and checks for user with matching email and password
string checkforaccount(string ema, string pass){
    user use;
    ifstream iFile;
    string id="";
    string test="";
    iFile.open("user.dat",ios::binary);
    if(!iFile){
        cout<<"File could not be opened... Press any Key to exit";
        cin.ignore();
        cin.get();
        return NULL;
    }
    while(iFile.read(reinterpret_cast<char *> (&use), sizeof(user))){
        if(use.getemail()==ema&&use.getpassword()==pass){
            id=use.getid();
        }else if(use.getemail()==ema&&use.getpassword()!=pass){
            id="pass";
        }
    }
    iFile.close();
    return id;
}
//options for which records the admin can dispaly
void choose_display(admin current_admin){
    char ch;
    system("clear");
    cout<<"\n\n\t1. Display user records ";
    cout<<"\n\n\t2. Display admin records ";
    cout<<"\n\n\t3. Display students records ";
    cout<<"\n\n\t4. Display teacher records ";
    cout<<"\n\n\t5. Display module records ";
    cout<<"\n\n\t6. Display report records ";
    cout<<"\n\n\t7. Display all records ";
    cin>>ch;
    system("clear");
    switch(ch){
        case '1':current_admin.display_all_users();
        cin.ignore();
        cin.get();  
        break;
        case '2':current_admin.display_all_admins();
        cin.ignore();
        cin.get();  
        break;
        case '3':current_admin.display_all_students();
        cin.ignore();
        cin.get();  
        break;
        case '4':current_admin.display_all_teachers();
        cin.ignore();
        cin.get();  
        break;
        case '5':current_admin.display_all_modules();
        cin.ignore();
        cin.get();  
        break;
        case '6':current_admin.display_all_reports();
        cin.ignore();
        cin.get();  
        break;
        case '7':current_admin.display_all_records();
        cin.ignore();
        cin.get();  
        break;
    }
}
//options for which records the admin can delete
void choose_delete(admin current_admin){
    string stu;
    char ch;
    system("clear");
    cout<<"\n\n\t1. Delete admin records ";
    cout<<"\n\n\t2. Delete students records ";
    cout<<"\n\n\t3. Delete teacher records ";
    cout<<"\n\n\t4. Delete module records ";
    cout<<"\n\n\t5. Delete report records ";
    cin>>ch;
    system("clear");
    switch(ch){
        case '1':current_admin.display_all_admins();
        cin.ignore();
        cin.get(); 
        cout<<"\n\n Enter id of admin to delete: ";
        getline(cin,stu);
        if(stu==current_admin.getid()){
            cout<<"\n\n Cannot delete current user ";
        }else{
            current_admin.delete_admin(stu);
        } 
        break;
        case '2':current_admin.display_all_students();
        cin.ignore();
        cin.get(); 
        cout<<"\n\n Enter id of student to delete: ";
        getline(cin,stu);
        current_admin.delete_student(stu); 
        break;
        case '3':current_admin.display_all_teachers();
        cin.ignore();
        cin.get(); 
        cout<<"\n\n Enter id of teacher to delete: ";
        getline(cin,stu);
        current_admin.delete_teacher(stu); 
        break;
        case '4':current_admin.display_all_modules();
        cin.ignore();
        cin.get(); 
        cout<<"\n\n Enter code of module to delete: ";
        getline(cin,stu);
        current_admin.delete_module(stu); 
        break;
        case '5':current_admin.display_all_reports();
        cin.ignore();
        cin.get(); 
        cout<<"\n\n Enter id of report to delete: ";
        getline(cin,stu);
        current_admin.delete_report(stu); 
        break;
    }
}
//menu for users who have logged in
void logged_in_options(user current_user){
    char ch;
    string store=current_user.getid().substr(0,2);
    if(store=="UG"||store=="MA"||store=="PH"){
        student current_student;
        current_student=current_student.fetch_student(current_user.getid());
        do{
            system("clear");
            cout<<"\n\n\n\tSTUDENT MENU";
            cout<<"\n\nUser id:"<<current_user.getid()<<endl;
            cout<<"\n\n\t1.View profile";
            cout<<"\n\n\t2.View reports";
            cout<<"\n\n\t3.Exit";
            cout<<"\n\nWhat is your Choice (1/2/3) ";
            cin>>ch;
            system("clear");
            switch(ch){
                case '1':
                cout<<"\nID----------First name---------------Surname------------------Email-----------------------------------Age";
                current_student.showdata();
                cin.ignore();
                cin.get(); 
                break;
                case '2':
                cout<<"\n---------------------------------------------------------------------------------";
                cout<<"\n--------------------------------------Reports------------------------------------\n";
                cout<<"\n\nID-----Student id-----Module code---Grade----------------------------------------";
                current_student.view_reports(); break;
            }
        }while(ch!='3');
    }else if(store=="TE"){
        teacher current_teacher;
        current_teacher=current_teacher.fetch_teacher(current_user.getid());
        do{
        system("clear");
        cout<<"\n\n\n\tTEACHER MENU";
        cout<<"\n\nUser id:"<<current_user.getid()<<endl;
        cout<<"\n\n\t1.View profile";
        cout<<"\n\n\t2.Create report for student";
        cout<<"\n\n\t3.Exit";
        cout<<"\n\nWhat is your Choice (1/2/3) ";
        cin>>ch;
        system("clear");
        switch(ch){
            case '1':
            cout<<"\nID----------First name---------------Surname------------------Email-----------------------------------";
            current_teacher.showdata();
            cin.ignore();
            cin.get(); 
            break;
            case '2':current_teacher.create_report(); break;
        }
        }while(ch!='3');
    }else if(store=="AD"){
        admin current_admin;
        current_admin=current_admin.fetch_admin(current_user.getid());
        string stu;
        do{
        system("clear");
        cout<<"\n\n\n\tADMIN MENU";
        cout<<"\n\nUser id:"<<current_user.getid()<<endl;
        cout<<"\n\n\t1. View profile";
        cout<<"\n\n\t2. Create user record";
        cout<<"\n\n\t3. Create module record";
        cout<<"\n\n\t4. Create report for student";
        cout<<"\n\n\t5. Search student record";
        cout<<"\n\n\t6. Choose what record to display ";
        cout<<"\n\n\t7. Choose what record to delete";
        cout<<"\n\n\t8. Change student record";
        cout<<"\n\n\t9. Exit";
        cout<<"\n\nWhat is your Choice (1/2/3/4/5/6/7/8/9/a/b/c/e) ";
        cin>>ch;
        system("clear");
        switch(ch){
            case '1':
            cout<<"\nID----------First name---------------Surname------------------Email-----------------------------------";
            current_admin.showdata();
            cin.ignore();
            cin.get();
            break;
            case '2':current_admin.create_user(); break;
            case '3':current_admin.create_module(); break;
            case '4':current_admin.create_report(); break;
            case '5':current_admin.display_sp(); break;
            case '6':choose_display(current_admin);  
            break;
            case '7':choose_delete(current_admin);
            break;
            case '8':current_admin.display_all_students();
            cin.ignore();
            cin.get(); 
            cout<<"\n\n Enter id of student to delete: ";
            getline(cin,stu);
            current_admin.change_student(stu);
            }
        }while(ch!='8');
    }
}