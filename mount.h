#include <iostream>
using namespace std;

struct particionMontada{    
    public:
        char path[100]="";
        char name[16]="";
        void setPath(string path, bool isCadena);
        void setName(string name, bool isCadena);
};
struct disco{
    public:
        char letra='0';
        char path[100]="";
        int status=0;
        particionMontada particiones[99];
};

/*extern*/ disco discosMontados[26];

class _MOUNT{
    public:
    string path;
    string name;
    _MOUNT(){};
    void setPath(string path, bool isCadena);
    void setName(string name, bool isCadena);
    string pathToString(char * name);
    string nameToString(char * name);
    void exe();
};
void _MOUNT::setPath(string path, bool isCadena){
    if(isCadena){
        this->path = path.substr(1, path.length()-2);
    }else{
        this->path = path;
    }
};
void _MOUNT::setName(string name, bool isCadena){
    if(isCadena){
        this->name=name.substr(1, name.length()-2);
    }else{
        this->name=name;
    }
};
string _MOUNT::pathToString(char * name){
    string str;
    for(int i=0;i < 100;i++){
        if(name[i]==int(NULL)) break;
        str=str+name[i];
    }
    return str;
}
string _MOUNT::nameToString(char * name){
    string str;
    for(int i=0;i < 16;i++){
        if(name[i]==int(NULL)) break;
        str=str+name[i];
    }
    return str;
}
void _MOUNT::exe(){
    FILE *existe = fopen(this->path.c_str(),"r");
    if(existe==NULL){
        cout << "ERROR: El disco "<<this->path<<" no existe."<<endl;
        return;
    }
    fclose(existe);

    
    int diskSpot=-1;
    for(int i =0;i < 26;i++){
        diskSpot=i;
        if(discosMontados[i].status==0){
            //es un espacio sin utilizar entonces se monta en este espacio
            discosMontados[i].letra=char(65+i);//cuando es 0 es A y aumenta hasta la Z
            strcpy(discosMontados[i].path,this->path.c_str());
            discosMontados[i].status=1;
            break;
        }
        if(pathToString(discosMontados[i].path)==this->path){//el disco ya está montado en un espacio
            break;
        }
        if(i==25){//todos los discos están llenos y no hay espacio para más
            cout << "ERROR:No hay espacio para montar otro disco y así la partición."<<endl;
            return;
        }
    }

    
};