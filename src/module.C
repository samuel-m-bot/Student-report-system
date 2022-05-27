#include "module.h"
#include<cstring>

// the class that stores data

void module::getdata(){
    cout<<"\nEnter module code: ";
    cin.ignore();
    cin.getline(module_code,7);
    cout<<"\n\nEnter module name: ";
    cin.getline(module_name,25);
}

void module::showdata() const{
    string module_code_space="";
    if(strlen(module_code)!=14){
        for(int i=strlen(module_code);i<14;i++){
            module_code_space=module_code_space+" ";
        }
    }
    cout<<"\n"<<module_code<<module_code_space<<module_name;
}

string module::getmodule_code() const{
    string str(module_code);
    return str;
}
module module::fetch_module(string n) {
    module teach;
    ifstream iFile;
    iFile.open("module.dat",ios::binary);
    if(!iFile){
        cout<<"File could not be opened... Press any Key to exit";
        cin.ignore();
        cin.get();
        return teach;
    }
    bool flag=false;
    while(iFile.read(reinterpret_cast<char *> (&teach), sizeof(module))){
        if(teach.getmodule_code()==n){
            return teach;
        }
    }
    iFile.close();
    return teach;
}