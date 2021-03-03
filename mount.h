#include <iostream>
#include "mountStructs.h"
using namespace std;

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
    void unmount(char * id);
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
    
    int diskSpot;
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
    
    for(int i =0;i<99;i++){
        if(nameToString(discosMontados[diskSpot].particiones[i].name)==this->name && discosMontados[diskSpot].particiones[i].status==1){
            cout << "ERROR: La partición "+this->name+" ya está montada."<<endl;
            return;
        }
    }
    
    FILE *search =  fopen(this->path.c_str(), "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    for(int i =0;i<4;i++){
        if(opciones[i].part_status=='1' && opciones[i].part_type=='p'){
            if(this->name==nameToString(opciones[i].part_name)){//se encontró la partición
                for(int e =0;e<99;e++){
                    if(discosMontados[diskSpot].particiones[e].status==0){
                        strcpy(discosMontados[diskSpot].particiones[e].name,opciones[i].part_name);
                        discosMontados[diskSpot].particiones[e].status=1;
                        discosMontados[diskSpot].particiones[e].numero=e+1;//se le guarda como uno más de su posición de array
                        cout << discosMontados[diskSpot].particiones[e].name<<endl;
                        cout << "Se ha montado la partición correctamente, su id es 66"<<to_string(discosMontados[diskSpot].particiones[e].numero)+discosMontados[diskSpot].letra<<endl;
                        return;
                    }
                }
            } 
        }        
    }
    if(mbr.mbr_partition_1.part_type=='e' && mbr.mbr_partition_1.part_status=='1' || mbr.mbr_partition_2.part_type=='e' && mbr.mbr_partition_2.part_status=='1' || mbr.mbr_partition_3.part_type=='e' && mbr.mbr_partition_3.part_status=='1' || mbr.mbr_partition_4.part_type=='e' && mbr.mbr_partition_4.part_status=='1'){
        partition extendida = (mbr.mbr_partition_1.part_type=='e')?mbr.mbr_partition_1:(mbr.mbr_partition_2.part_type=='e')?mbr.mbr_partition_2:(mbr.mbr_partition_3.part_type=='e')?mbr.mbr_partition_3:mbr.mbr_partition_4;
        EBR ebr;
        int anterior;
        fseek(search, extendida.part_start, SEEK_SET);
        fread(&ebr, sizeof(EBR), 1, search);
        while(true){
            if(this->name==nameToString(ebr.part_name) && ebr.part_status=='1'){
                for(int e =0;e<99;e++){
                    if(discosMontados[diskSpot].particiones[e].status==0){
                        strcpy(discosMontados[diskSpot].particiones[e].name,ebr.part_name);
                        discosMontados[diskSpot].particiones[e].status=1;
                        discosMontados[diskSpot].particiones[e].numero=e+1;//se le guarda como uno más de su posición de array
                        cout << "Se ha montado la partición correctamente, su id es 66"<<to_string(discosMontados[diskSpot].particiones[e].numero)+discosMontados[diskSpot].letra<<endl;
                        return;
                    }
                }
            }
            if(ebr.part_next==-1){
                break;
            }
            anterior = ebr.part_start;
            fseek(search, ebr.part_next, SEEK_SET);
            fread(&ebr, sizeof(EBR), 1, search);
        }
    }
    cout << "ERROR:No se ha encontrado la partición en el path indicado."<<endl;
};
void _MOUNT::unmount(char * id){
    int diskSpot = (int)id[3]-65;
    int partSpot=id[2]-'0';//se le resta uno para obotener la posición en el array
    partSpot--;
    if(int(id[3])<65){//es una partición con un número de <9
        char temp[2]={ id[2], id[3]};
        partSpot=atoi(temp)-1;//restamos uno para obtener la posición del array
        diskSpot = (int)id[4]-65;
    }
    if(discosMontados[diskSpot].status==1){//el disco funciona
        if(discosMontados[diskSpot].particiones[partSpot].status==1){
            discosMontados[diskSpot].particiones[partSpot].status=0;
            cout << "Se ha desmontado la partición "<<id<<" exitosamente."<<endl;
        }else{
            cout << "ERROR:No hay una partición montada en el espacio "<<(char)(partSpot+1)<<endl;
        }
    }else{
        cout << "ERROR:No hay un disco en el espacio de la letra "<<(char)(diskSpot+65)<<endl;
    }
}