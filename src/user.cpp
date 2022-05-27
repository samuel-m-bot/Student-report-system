#include "user.h"
#include "student.h"
#include "teacher.h"
#include<cstring>

// the class that stores data

void user::getdata(){
    cout<<"\nEnter user id: ";
    cin.ignore();
    cin.getline(id,15);
    cout<<"\n\nEnter user email: ";
    cin.getline(email,40);
    cout<<"\n\nEnter user password: ";
    cin.getline(password,20);
}

void user::showdata() const{
    string id_space="";
    if(strlen(id)!=12){
        for(int i=strlen(id);i<12;i++){
            id_space=id_space+" ";
        }
    }
    cout<<"\n"<<id<<id_space<<email<<"     -"<<password;
}

string user::getid() const{
    string str(id);
    return str;
}
string user::getemail() const{
    string str(email);
    return str;
}
string user::getpassword() const{
    string str(password);
    return str;
}
user user::fetch_user(string email,string pass) {
    user use;
    ifstream iFile;
    iFile.open("user.dat",ios::binary);
    if(!iFile){
        cout<<"File could not be opened... Press any Key to exit";
        cin.ignore();
        cin.get();
        return use;
    }
    bool flag=false;
    while(iFile.read(reinterpret_cast<char *> (&use), sizeof(user))){
        if(use.getemail()==email&&use.getpassword()==pass){
            return use;
        }
    }
    iFile.close();
    return use;
}