#include <iostream>
using namespace std;

class _MKDISK{
    private:
        int size;
        string f;
        string path;
        string u;
    public:
        _MKDISK(){
            this->f = "bf";
        };
        void setSize(int size);
        void setFit(string f);
        void setPath(string path);
        void setUnit(string u);
        int getSize();
        string getFit();
        string getPath();
        string getUnit();
        void exe();
        string toLowerCase(string cadena);
};
void _MKDISK::setSize(int size){
    this->size = size;
};
void _MKDISK::setFit(string f){
    this->f = toLowerCase(f);
};
void _MKDISK::setPath(string path){
    this->path = toLowerCase(path);
};
void _MKDISK::setUnit(string u){
    this->u = toLowerCase(u);
};
int _MKDISK::getSize(){
    return this->size;
};
string _MKDISK::getFit(){
    return this->f;
};
string _MKDISK::getPath(){
    return this->path;
};
string _MKDISK::getUnit(){
    return this->u;
};
void _MKDISK::exe(){
    cout << "creating disk..."<<endl;
    if(this->size<=0){
        cout<<"ERROR:no se puede crear un disco con el tamaño " << this->size <<endl;
    }else if(this->u!="k" && this->u!="m"){
        cout<<"ERROR:no existe la unidad de datos "<<this->u<<endl;
    }else if(this->f!="bf" && this->f!="ff" && this->f!="wf"){
        cout<<"ERROR:no existe el fit "<<this->f<<endl;
    }else{
        time_t t;
        struct tm *tm;
        char fechayhora[20];

        t = time(NULL);
        tm = localtime(&t);
        strftime(fechayhora, 20, "%Y/%m/%d %H:%M:%S", tm);
        cout << fechayhora<<endl;

        if(this->u=="k"){
            this->size=this->size*1024;
        }else{
            this->size=this->size*1024*1024;
        }

        string filename = "", folders ="";
        for(int i=this->path.length(); i>=0; i--){
            if(this->path[i]=='/'){
                filename = this->path.substr(i+1, this->path.length());
                folders = this->path.substr(1, i-1);
                break;
            }
        }
        cout << "creating folders "<<folders<<endl;
        string command = "mkdir -p \\"+folders;
        system(command.c_str());
        command = "sudo chmod -R 777 \'"+folders+"\'";
        system(command.c_str());      
/*        return;
        FILE *exists = fopen(this->path.c_str(),"r");
        if(exists!=NULL){
            cout << "ERROR: El disco ya existe"<<endl;
            fclose(exists);
            return;
        }else{
            FILE * createFile;
            cout <<filename<<endl;
            createFile = fopen(filename.c_str(), "w");
            fclose(createFile);
        }
*/
        FILE * searchFile =  fopen(this->path.c_str(), "wb");
        if(searchFile != NULL){
            fwrite("\0", 1, 1, searchFile);
            fseek(searchFile, this->size-1, SEEK_SET);
            fwrite("\0", 1, 1, searchFile);
            rewind(searchFile);
            cout<<"Disco Creado con éxito"<<endl;
        }else{
            cout << "no existe"<<endl;
            
        }
        fclose(searchFile);
    }
}

string _MKDISK::toLowerCase(string cadena){
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