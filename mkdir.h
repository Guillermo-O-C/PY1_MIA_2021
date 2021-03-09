#include <iostream>
#include "mountStructs.h"
#include "user.h"
#include "mbr.h"
#include "partitionStructs.h"
#include <vector>
using namespace std;

class _MKDIR{
    private:
    string path;
    bool p;
    public:
    _MKDIR(){
        path="";
        p=false;
    }
    void setPath(string path, bool isCadena);
    void setP();
    void exe();
    vector<string> split(string path, string split);
    string getFolderN(string path,string split, int folderN);
    string charToString(char * name, int loops);
    int searchForFolder(FILE * search, SB superBloque,inode carpetaTemporal, string folderName);
    void createFolder(FILE * search, int partStart, SB superBloque, inode carpetaTemporal, string folderName, int abuelo, int padre);
};
void _MKDIR::setPath(string path, bool isCadena){
    if(isCadena){
        this->path = path.substr(1, path.length()-2);
    }else{
        this->path = path;
    }
};
void _MKDIR::setP(){
    this->p=true;
};
void _MKDIR::exe(){
    string id=usuarioActivo.partitionID;
    int diskSpot = (int)id[3]-65;
    int partSpot=id[2]-'0';//se le resta uno para obotener la posición en el array
    partSpot--;
    if(int(id[3])<65){//es una partición con un número de <9
        char temp[2]={ id[2], id[3]};
        partSpot=atoi(temp)-1;//restamos uno para obtener la posición del array
        diskSpot = (int)id[4]-65;
    }
    FILE *search =  fopen(discosMontados[diskSpot].path, "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    string name = discosMontados[diskSpot].particiones[partSpot].name;  
    for(int i =0;i<4;i++){
        if(opciones[i].part_status=='1' && opciones[i].part_type=='p'){
            if(name==charToString(opciones[i].part_name, 12)){//está dentro de la partición
                SB superBloque;
                fseek(search, opciones[i].part_start, SEEK_SET);
                fread(&superBloque, sizeof(SB), 1, search);
                inode raiz;
                fseek(search, superBloque.s_inode_start, SEEK_SET);
                fread(&raiz, sizeof(inode), 1, search);
                inode carpetaTemporal=raiz;
                int abuelo=0;
                int padre=0;
                this->path=(this->path[0]=='/')?this->path.substr(1, this->path.length()):this->path;
                vector<string> carpetas = split(this->path, "/");
                for(int e =0;e<carpetas.size();e++){//ciclo para iterar entre las carpetas de la ruta
                    string folderName =carpetas[e];
                    int folderLocation = searchForFolder(search, superBloque, carpetaTemporal, folderName);
                    cout << "se busca la carpeta "<<folderName<<endl;
                    if(abuelo==padre) padre=folderLocation;
                    if(padre!=folderLocation){
                        abuelo=padre;
                        padre=folderLocation;
                    }
                    if(folderLocation!=0){
                        if(e==carpetas.size()-1){//es la carpeta que hay que crear
                            cout << "ERROR: Ya existe la carpeta "+folderName<<endl;
                            return;
                        }
                        cout << "La carpeta ya existe"<<endl;
                        fseek(search, superBloque.s_inode_start+sizeof(inode)*folderLocation,SEEK_SET);
                        fread(&carpetaTemporal, sizeof(inode), 1, search);
                    }
                    else{
                        if(e==carpetas.size()-1 || this->p){//es la carpeta que hay que crear || se crea la carpeta
                            createFolder(search, opciones[i].part_start, superBloque, carpetaTemporal, folderName, abuelo, padre);
                            return;//por ahora
                        }
                        else{
                            cout << "ERROR: No existe la carpeta "+getFolderN(this->path, "/", e)<<endl;
                            return;
                        }
                    }
                }
            }
        }
    }
};

vector<string> _MKDIR::split(string path, string split){
    /*int pos =0;
    int n=0;
    if(path[0]=='/')path.erase(0,1);
    while ((pos = path.find(split)) != std::string::npos) { 
        path.erase(0, pos + split.length());
        cout << path.substr(0, pos+split.length())<<endl;
        n++;
    }
    return n;*/
    vector<string> list;
    string s = string(path);
    size_t pos = 0;
    string token;
    while ((pos = s.find(split)) != string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + split.length());
    }
    list.push_back(s);
    return list;
}

string _MKDIR::getFolderN(string path, string split, int folderN){
    string folder;
    int pos =0;
    for(int i =0;i<folderN;i++){
        if(path[0]=='/')path.erase(0,1); 
        pos=path.find(split);
        if((path.find(split))==std::string::npos) break; 
        folder = path.substr(0, pos);
        cout << folder;
        path.erase(0, pos + split.length());
    }
    return folder;
}

string _MKDIR::charToString(char * name, int loops){
    string str;
    for(int i=0;i < loops;i++){
        if(name[i]==int(NULL)) break;
        str=str+name[i];
    }
    return str;
}

int _MKDIR::searchForFolder(FILE * search,SB superBloque,inode carpetaTemporal, string folderName){
    for(int j=0;j<=12;j++){//iterando sobre los 12 apuntadores directos
        if(carpetaTemporal.i_block[j]!=-1){//direcciona a un bloque de carpeta
        folder_block folder;
        fseek(search, superBloque.s_block_start+64*carpetaTemporal.i_block[j],SEEK_SET);
        fread(&folder, 64, 1, search);
            for(int o=0;o<4;o++){//iterando sobre los nombres del bloque de carpetas
                if(folder.b_content[o].b_inodo!=-1){
                   if(charToString(folder.b_content[o].b_name, 12) == folderName){
                        //la carpeta ya existe
                        fseek(search, superBloque.s_inode_start+sizeof(inode)*folder.b_content[o].b_inodo, SEEK_SET);
                        fread(&carpetaTemporal, sizeof(inode), 1, search);
                        if(carpetaTemporal.i_type=='0'){
                            return folder.b_content[o].b_inodo;
                        }
                    } 
                }                
            }
        }
    }
    if(carpetaTemporal.i_block[13]!=-1){//se está usando el API1
        pointers apuntadores;
        fseek(search, superBloque.s_block_start+64*carpetaTemporal.i_block[13], SEEK_SET);
        fread(&apuntadores, 64, 1, search);
        for(int i =0;i<16;i++){
            if(apuntadores.b_pointers[i]!=-1){//direcciona a un bloque de carpeta
            folder_block folder;
            fseek(search, superBloque.s_block_start+64*apuntadores.b_pointers[i],SEEK_SET);
            fread(&folder, 64, 1, search);
                for(int o=0;o<4;o++){//iterando sobre los nombres del bloque de carpetas
                    if(folder.b_content[o].b_inodo!=-1){
                        if(charToString(folder.b_content[o].b_name, 12) == folderName){
                            //la carpeta ya existe
                            fseek(search, superBloque.s_inode_start+sizeof(inode)*folder.b_content[o].b_inodo, SEEK_SET);
                            fread(&carpetaTemporal, sizeof(inode), 1, search);
                            if(carpetaTemporal.i_type=='0'){
                                return folder.b_content[o].b_inodo;
                            }
                        } 
                    }
                }
            }
        }
    }
    if(carpetaTemporal.i_block[14]!=-1){//se está usando el API2
        pointers API;//API2
        fseek(search, superBloque.s_block_start+64*carpetaTemporal.i_block[14], SEEK_SET);
        fread(&API, 64, 1, search);
        for(int j=0;j<2;j++){
            if(API.b_pointers[j]!=-1){
                pointers APD2;
                fseek(search, superBloque.s_block_start+64*API.b_pointers[j],SEEK_SET);
                fread(&APD2, 64, 1, search);
                for(int i =0;i<16;i++){
                    if(APD2.b_pointers[i]!=-1){//direcciona a un bloque de carpeta
                        folder_block folder;
                        fseek(search, superBloque.s_block_start+64*APD2.b_pointers[i],SEEK_SET);
                        fread(&folder, 64, 1, search);
                        for(int o=0;o<4;o++){//iterando sobre los nombres del bloque de carpetas
                            if(folder.b_content[o].b_inodo!=-1){
                               if(charToString(folder.b_content[o].b_name, 12) == folderName){
                                    //la carpeta ya existe
                                    fseek(search, superBloque.s_inode_start+sizeof(inode)*folder.b_content[o].b_inodo, SEEK_SET);
                                    fread(&carpetaTemporal, sizeof(inode), 1, search);
                                    if(carpetaTemporal.i_type=='0'){
                                        return folder.b_content[o].b_inodo;
                                    }
                                } 
                            }
                        }
                    }
                }  
            }            
        }
    }
    if(carpetaTemporal.i_block[15]!=-1){//se está usando el API3
        pointers API;//API2
        fseek(search, superBloque.s_block_start+64*carpetaTemporal.i_block[15], SEEK_SET);
        fread(&API, 64, 1, search);
        for(int j=0;j<3;j++){
            if(API.b_pointers[j]!=-1){
                pointers APD2;
                fseek(search, superBloque.s_block_start+64*API.b_pointers[j],SEEK_SET);
                fread(&APD2, 64, 1, search);
                for(int i =0;i<16;i++){
                    if(APD2.b_pointers[i]!=-1){//direcciona a un bloque de carpeta
                        folder_block folder;
                        fseek(search, superBloque.s_block_start+64*APD2.b_pointers[i],SEEK_SET);
                        fread(&folder, 64, 1, search);
                        for(int o=0;o<4;o++){//iterando sobre los nombres del bloque de carpetas
                            if(folder.b_content[o].b_inodo!=-1){
                               if(charToString(folder.b_content[o].b_name, 12) == folderName){
                                    //la carpeta ya existe
                                    fseek(search, superBloque.s_inode_start+sizeof(inode)*folder.b_content[o].b_inodo, SEEK_SET);
                                    fread(&carpetaTemporal, sizeof(inode), 1, search);
                                    if(carpetaTemporal.i_type=='0'){
                                        return folder.b_content[o].b_inodo;
                                    }
                                } 
                            }                            
                        }
                    }
                }  
            }
        }
    }
    return 0;
}

void _MKDIR::createFolder(FILE * search, int partStart, SB superBloque, inode carpetaTemporal, string folderName, int abuelo, int padre){
    time_t t;
    struct tm *tm;
    char fechayhora[16];
    t = time(NULL);
    tm = localtime(&t);
    strftime(fechayhora, 20, "%d/%m/%Y %H:%M", tm);
    strcpy(superBloque.s_mtime,fechayhora);
    for(int j=0;j<=12;j++){//iterando sobre los 12 apuntadores directos
        if(carpetaTemporal.i_block[j]!=-1){//direcciona a un bloque de carpeta
            folder_block folder;
            fseek(search, superBloque.s_block_start+64*carpetaTemporal.i_block[j],SEEK_SET);
            fread(&folder, 64, 1, search);
            for(int o=0;o<4;o++){//iterando sobre los nombres del bloque de carpetas
                if(folder.b_content[o].b_inodo==-1){//crear el inodo, actualizar el bloque de carpeta, superbloque y bitmaps
                    inode nuevaCarpeta;
                    strcpy(nuevaCarpeta.i_atime,fechayhora);
                    strcpy(nuevaCarpeta.i_ctime,fechayhora);
                    strcpy(nuevaCarpeta.i_mtime,fechayhora);
                    nuevaCarpeta.i_block[0]=superBloque.s_first_blo;//se aumenta el siguiente bloque libre
                    fseek(search, superBloque.s_inode_start + superBloque.s_first_ino*sizeof(inode), SEEK_SET);
                    fwrite(&nuevaCarpeta, sizeof(inode), 1, search);
                    fflush(search);
                    //crear bloque 0
                    folder_block Block0;
                    strcpy(Block0.b_content[0].b_name,".");
                    Block0.b_content[0].b_inodo=padre;
                    strcpy(Block0.b_content[1].b_name,"..");
                    Block0.b_content[1].b_inodo=abuelo;
                    cout << "basic folder will be block "<<superBloque.s_first_blo<<endl;
                    fseek(search, superBloque.s_block_start+ 64*superBloque.s_first_blo, SEEK_SET);
                    fwrite(&Block0, sizeof(folder_block), 1, search);
                    fflush(search);
                    //actualizar el bloque de carpeta actual
                    folder.b_content[o].b_inodo=superBloque.s_first_ino;//se aumenta el siguiente inodo libre
                    cout <<"folder name=" <<folderName<<endl;
                    strcpy(folder.b_content[o].b_name,folderName.c_str());
                    cout << "father folder is "<<carpetaTemporal.i_block[j]<<endl;
                    fseek(search, superBloque.s_block_start+64*carpetaTemporal.i_block[j],SEEK_SET);
                    fwrite(&folder, 64, 1, search);
                    fflush(search);
                    //actualizar bitmap de inodos
                    fseek(search, superBloque.s_bm_inode_start + superBloque.s_first_ino,SEEK_SET);
                    fwrite("1",1, 1, search);
                    fflush(search);
                    fseek(search, superBloque.s_bm_block_start + superBloque.s_first_blo,SEEK_SET);
                    fwrite("1",1, 1, search);
                    fflush(search);
                    //actualizar el superbloque
                    superBloque.s_first_ino=superBloque.s_first_ino+1;
                    superBloque.s_first_blo=superBloque.s_first_blo+1;
                    superBloque.s_free_blocks_count=superBloque.s_free_blocks_count-1;
                    superBloque.s_free_inodes_count=superBloque.s_free_inodes_count-1;
                    fseek(search, partStart, SEEK_SET);
                    fwrite(&superBloque, sizeof(SB), 1, search);
                    fflush(search);
                    cout <<"Se ha creado la carpeta exitosamente"<<endl;
                    return;
                }                
            }
        }else{//crear bloque carpeta

        }
    }
    if(carpetaTemporal.i_block[13]!=-1){//se está usando el API1
        pointers apuntadores;
        fseek(search, superBloque.s_block_start+64*carpetaTemporal.i_block[13], SEEK_SET);
        fread(&apuntadores, 64, 1, search);
        for(int i =0;i<16;i++){
            if(apuntadores.b_pointers[i]!=-1){//direcciona a un bloque de carpeta
            folder_block folder;
            fseek(search, superBloque.s_block_start+64*apuntadores.b_pointers[i],SEEK_SET);
            fread(&folder, 64, 1, search);
                for(int o=0;o<4;o++){//iterando sobre los nombres del bloque de carpetas
                    if(folder.b_content[o].b_inodo!=-1){
                        if(charToString(folder.b_content[o].b_name, 12) == folderName){
                            //la carpeta ya existe
                            fseek(search, superBloque.s_inode_start+sizeof(inode)*folder.b_content[o].b_inodo, SEEK_SET);
                            fread(&carpetaTemporal, sizeof(inode), 1, search);
                            if(carpetaTemporal.i_type=='0'){
                               // return folder.b_content[o].b_inodo;
                            }
                        } 
                    }
                }
            }
        }
    }
    if(carpetaTemporal.i_block[14]!=-1){//se está usando el API2
        pointers API;//API2
        fseek(search, superBloque.s_block_start+64*carpetaTemporal.i_block[14], SEEK_SET);
        fread(&API, 64, 1, search);
        for(int j=0;j<2;j++){
            if(API.b_pointers[j]!=-1){
                pointers APD2;
                fseek(search, superBloque.s_block_start+64*API.b_pointers[j],SEEK_SET);
                fread(&APD2, 64, 1, search);
                for(int i =0;i<16;i++){
                    if(APD2.b_pointers[i]!=-1){//direcciona a un bloque de carpeta
                        folder_block folder;
                        fseek(search, superBloque.s_block_start+64*APD2.b_pointers[i],SEEK_SET);
                        fread(&folder, 64, 1, search);
                        for(int o=0;o<4;o++){//iterando sobre los nombres del bloque de carpetas
                            if(folder.b_content[o].b_inodo!=-1){
                               if(charToString(folder.b_content[o].b_name, 12) == folderName){
                                    //la carpeta ya existe
                                    fseek(search, superBloque.s_inode_start+sizeof(inode)*folder.b_content[o].b_inodo, SEEK_SET);
                                    fread(&carpetaTemporal, sizeof(inode), 1, search);
                                    if(carpetaTemporal.i_type=='0'){
                                    //    return folder.b_content[o].b_inodo;
                                    }
                                } 
                            }
                        }
                    }
                }  
            }            
        }
    }
    if(carpetaTemporal.i_block[15]!=-1){//se está usando el API3
        pointers API;//API2
        fseek(search, superBloque.s_block_start+64*carpetaTemporal.i_block[15], SEEK_SET);
        fread(&API, 64, 1, search);
        for(int j=0;j<3;j++){
            if(API.b_pointers[j]!=-1){
                pointers APD2;
                fseek(search, superBloque.s_block_start+64*API.b_pointers[j],SEEK_SET);
                fread(&APD2, 64, 1, search);
                for(int i =0;i<16;i++){
                    if(APD2.b_pointers[i]!=-1){//direcciona a un bloque de carpeta
                        folder_block folder;
                        fseek(search, superBloque.s_block_start+64*APD2.b_pointers[i],SEEK_SET);
                        fread(&folder, 64, 1, search);
                        for(int o=0;o<4;o++){//iterando sobre los nombres del bloque de carpetas
                            if(folder.b_content[o].b_inodo!=-1){
                               if(charToString(folder.b_content[o].b_name, 12) == folderName){
                                    //la carpeta ya existe
                                    fseek(search, superBloque.s_inode_start+sizeof(inode)*folder.b_content[o].b_inodo, SEEK_SET);
                                    fread(&carpetaTemporal, sizeof(inode), 1, search);
                                    if(carpetaTemporal.i_type=='0'){
                                       // return folder.b_content[o].b_inodo;
                                    }
                                } 
                            }                            
                        }
                    }
                }  
            }
        }
    }
}