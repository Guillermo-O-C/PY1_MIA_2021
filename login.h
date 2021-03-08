#include <iostream>
#include "mountStructs.h"
#include "user.h"
#pragma once
using namespace std;

class _LOGIN{
    public:
        string partitionID;
        string user;
        string password;
        _LOGIN(){
            this->partitionID="";
            this->user="";
            this->password="";
        };
        void setUsr(string user, bool isCadena);
        void setPwd(string first, string second);
        void setId(string partitionID);
        void exe();
        string toUpperCase(string cadena);
        void logout();
};

void _LOGIN::setUsr(string user, bool isCadena){
     if(isCadena){
        this->user = user.substr(1, user.length()-2);
    }else{
        this->user = user;
    }
};

void _LOGIN::setPwd(string first, string second, bool isCadena){
    if(isCadena){
        this->password = first.substr(1, first.length()-2);
    }else{
        for(int i =0;i<first.length();i++){
            this->password+=first[i];
        }
        for(int i =0;i<second.length();i++){
            this->password+=second[i];
        } 
    }
    
};

void _LOGIN::setId(string partitionID){
    this->partitionID=toUpperCase(partitionID);
};

void _LOGIN::exe(){
    if(this->user=="" || this->password=="" || this->partitionID==""){
        cout << "Los parámetros user, password e Id son obligatorios."<<endl;
        return;
    }
    if(usuarioActivo.user!=""){
        cout << "ERROR:Ya existe una sesión activa"<<endl;
        return;
    }
    usuarioActivo.partitionID=this->partitionID;
    usuarioActivo.password=this->password;
    usuarioActivo.user=this->user;
    if(this->user=="root" && this->password=="123"){
        cout << "Inicio de sesión como usuario root."<<endl;
    }else{
        cout << "ERROR:Error de usuario y contraseña, inténtalo de nuevo."<<endl;
    }
}

void _LOGIN::logout(){
    if(usuarioActivo.user==""){
        cout <<"ERROR:No hay una sesión activa."<<endl;
        return;
    }
    usuarioActivo.user="";
    usuarioActivo.password="";
    usuarioActivo.partitionID="";
    cout <<"Se ha cerrado la sesión como usuario root." <<endl;
}

string _LOGIN::toUpperCase(string cadena){
    string lowered="";
    for (char c : cadena){
        if(97<=int(c) && int(c)<=122){
            lowered+=char(int(c)-32);
        }else{
            lowered+=c;
        }
    }
    return lowered;
}
