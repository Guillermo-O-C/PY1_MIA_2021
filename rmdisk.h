#include <iostream>
#include <stdio.h>
using namespace std;

class _RMDISK{
    private:
    string path;
    public:
    _RMDISK(){};
    void setPath(string path, bool isCadena);
    string getPath();
    void exe();
    string toLowerCase(string cadena);
};

void _RMDISK::setPath(string path, bool isCadena){
    if(isCadena){
        this->path = path.substr(1, path.length()-2);
    }else{
        this->path = path;
    }
};

string _RMDISK::getPath(){
    return this->path;
};

void _RMDISK::exe(){
    FILE *existe = fopen(this->path.c_str(),"r");
    if(existe==NULL){
        cout << "ERROR: El disco no existe."<<endl;
        // fclose(existe);
        return;
    }

    while(true){
        cout << "Se borrará el disco del siguiente path:\n"<<this->path<<"\n ¿Estás seguro de eliminar el disco? S/n"<<endl;
        string answer;
        getline(cin, answer);
        if(toLowerCase(answer)=="s"){
            //removes disk
            string command = "rm \'"+this->path+"\'";
            system(command.c_str());
            FILE *existe = fopen(this->path.c_str(),"r");
            if(existe!=NULL){
                cout << "ERROR: El disco no ha podido ser elimado."<<endl;
                //fclose(existe);
                return;
            }
            cout << "El disco ha sido eliminado exitosamente."<<endl; 
            break;
        }else if(toLowerCase(answer)=="n"){
            cout << "El disco no ha sido eliminado.";
            break;
        }
    }
};

string _RMDISK::toLowerCase(string cadena){
    string lowered="";
    for (char c : cadena){
        if(65<=int(c) && int(c)<=90){
            lowered+=char(int(c)+32);
        }else{
            lowered+=c;
        }
    }
    return lowered;
}