#include <iostream>
using namespace std;
#include "partitionStructs.h"
#include "mountStructs.h"
#pragma once

class _MKFS{
    private:
    string id;
    string type;
    int fs;
    public:
    _MKFS(){
        this->id="";
        this->type="full";
        this->fs=2;
    };
    void setId(string id);
    void setType(string type);
    void setFs(int fs);
    void exe();
    string nameToString(char * name);
    int getN(int tamanio);
    string toLowerCase(string cadena);
    string toUpperCase(string cadena);
};
void _MKFS::setId(string id){
    this->id=toUpperCase(id);
};
void _MKFS::setType(string type){
    this->type=toLowerCase(type);
};
void _MKFS::setFs(int fs){
    this->fs=fs;
};
string _MKFS::nameToString(char * name){
    string str;
    for(int i=0;i < 16;i++){
        if(name[i]==int(NULL)) break;
        str=str+name[i];
    }
    return str;
}
string _MKFS::toLowerCase(string cadena){
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
string _MKFS::toUpperCase(string cadena){
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
void _MKFS::exe(){
    if(this->id==""){
        cout <<"ERROR:El parámetro id es obligatorio."<<endl;
        return;
    }else if(this->type!="fast" && this->type!="full"){

    }
    int diskSpot = (int)this->id[3]-65;
    int partSpot=id[2]-'0';//se le resta uno para obotener la posición en el array
    partSpot--;
    if(int(this->id[3])<65){//es una partición con un número de <9
        char temp[2]={ this->id[2], this->id[3]};
        partSpot=atoi(temp)-1;//restamos uno para obtener la posición del array
        diskSpot = (int)id[4]-65;
    }
    string name = discosMontados[diskSpot].particiones[partSpot].name; 
    if(discosMontados[diskSpot].status==0){
        cout <<"La partición indicada no se encuentra montada."<<endl;
        return;
    }
    FILE * search = fopen(discosMontados[diskSpot].path, "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    SB superBloque;
    for(int i =0;i<4;i++){
        if(opciones[i].part_status=='1' && opciones[i].part_type=='p'){
            if(name==nameToString(opciones[i].part_name)){//se encontró la partición
                int n = getN(opciones[i].part_size);
                //cout << "n="<<to_string(n)<<endl;
                superBloque.s_filesystem_type=this->fs;
                time_t t;
                struct tm *tm;
                char fechayhora[16];
                t = time(NULL);
                tm = localtime(&t);
                strftime(fechayhora, 20, "%d/%m/%Y %H:%M", tm);
                strcpy(superBloque.s_mtime,fechayhora);
                superBloque.s_magic=0xEF53;
                superBloque.s_inode_size=sizeof(inode);
                superBloque.s_block_size=64;
                superBloque.s_first_ino=2;//0 es de raiz y 1 es de users.txt
                superBloque.s_first_blo=2;//0 es bloque de carpeta de raiz y 1 es de contenido para users.txt 
                superBloque.s_inodes_count=n;
                superBloque.s_blocks_count=3*n;
                superBloque.s_free_blocks_count=3*n-2;
                superBloque.s_free_inodes_count=n-2;
                switch(this->fs){
                    case 2:
                        superBloque.s_bm_inode_start=opciones[i].part_start+sizeof(superBloque);
                        superBloque.s_bm_block_start=opciones[i].part_start+sizeof(superBloque)+n;
                        superBloque.s_inode_start=opciones[i].part_start+sizeof(superBloque)+4*n;
                        superBloque.s_block_start=opciones[i].part_start+sizeof(superBloque)+4*n+n*sizeof(inode);
                        break;
                    case 3://contando el journaling
                        superBloque.s_bm_inode_start=opciones[i].part_start+sizeof(superBloque)+sizeof(Journaling)*n;
                        superBloque.s_bm_block_start=opciones[i].part_start+sizeof(superBloque)+sizeof(Journaling)*n+n;
                        superBloque.s_inode_start=opciones[i].part_start+sizeof(superBloque)+sizeof(Journaling)*n+4*n;
                        superBloque.s_block_start=opciones[i].part_start+sizeof(superBloque)+sizeof(Journaling)*n+4*n+n*sizeof(inode);
                        break;
                }
                fseek(search, opciones[i].part_start, SEEK_SET);
                fwrite(&superBloque, sizeof(SB), 1, search);
                fflush(search);
                int lastStart = opciones[i].part_start+sizeof(SB);
                if(this->fs==3){
                    Journaling journal;
                    for(int e =lastStart; e<lastStart+n*sizeof(Journaling);e=e+sizeof(Journaling)){
                        fseek(search, e, SEEK_SET);
                        fwrite(&journal, sizeof(Journaling), 1, search);
                        fflush(search);
                    }
                    lastStart=lastStart+n*sizeof(Journaling);
                }
                //bitmap de inodos
                cout << "inode bitmap stars in "<<to_string(lastStart)<<endl;
                for(int e=lastStart;e<lastStart+n;e++){
                    fseek(search, e, SEEK_SET);
                    fwrite("0", 1, 1, search);
                    fflush(search);
                }
                lastStart=lastStart+n;
                cout << "block bitmap stars in "<<to_string(lastStart)<<endl;
                //bitmap de bloques
                for(int e=lastStart;e<lastStart+3*n;e++){
                    fseek(search, e, SEEK_SET);
                    fwrite("0", 1, 1, search);
                    fflush(search);
                }
                lastStart=lastStart+3*n;
                if(this->type=="full"){
                    //bloque de inodos
                    inode inodo;
                    for(int e =lastStart; e<lastStart+n*sizeof(inode);e=e+sizeof(inode)){
                        fseek(search, e, SEEK_SET);
                        fwrite(&inodo, sizeof(inode), 1, search);
                        fflush(search);
                    }
                    lastStart=lastStart+n*sizeof(inode);
                    //bloque de bloques
                    folder_block carpeta;
                    for(int e =lastStart; e<lastStart+n*sizeof(folder_block);e=e+sizeof(folder_block)){
                        fseek(search, e, SEEK_SET);
                        fwrite(&carpeta, sizeof(folder_block), 1, search);
                        fflush(search);
                    }
                    lastStart=lastStart+n*sizeof(folder_block);
                    file_block archivo;
                    for(int e =lastStart; e<lastStart+n*sizeof(file_block);e=e+sizeof(file_block)){
                        fseek(search, e, SEEK_SET);
                        fwrite(&archivo, sizeof(file_block), 1, search);
                        fflush(search);
                    }
                    lastStart=lastStart+n*sizeof(file_block);
                    pointers pointer;
                    for(int e =lastStart; e<lastStart+n*sizeof(pointers);e=e+sizeof(pointers)){
                        fseek(search, e, SEEK_SET);
                        fwrite(&inodo, sizeof(pointers), 1, search);
                        fflush(search);
                    }
                    lastStart=lastStart+n*sizeof(pointers);
                }
                //crear carpeta raiz y archivo users.txt        
                inode raiz;
                strcpy(raiz.i_atime,fechayhora);
                strcpy(raiz.i_ctime,fechayhora);
                strcpy(raiz.i_mtime,fechayhora);
                raiz.i_block[0]=0;
                fseek(search, superBloque.s_inode_start, SEEK_SET);
                fwrite(&raiz, sizeof(inode), 1, search);
                fflush(search);
                //crear bloque de raiz
                folder_block raizBlock;
                strcpy(raizBlock.b_content[0].b_name,".");
                raizBlock.b_content[0].b_inodo=0;
                strcpy(raizBlock.b_content[1].b_name,"..");
                raizBlock.b_content[1].b_inodo=0;
                strcpy(raizBlock.b_content[2].b_name,"users.txt");
                raizBlock.b_content[2].b_inodo=1;
                fseek(search, superBloque.s_block_start, SEEK_SET);
                fwrite(&raizBlock, sizeof(folder_block), 1, search);
                fflush(search);
                //crear archivo
                inode users;
                strcpy(users.i_atime,fechayhora);
                strcpy(users.i_ctime,fechayhora);
                strcpy(users.i_mtime,fechayhora);
                users.i_type=1;
                users.i_block[0]=1;
                users.i_size=sizeof("1,G,root\n1,U,root,root,123\n");
                fseek(search, superBloque.s_inode_start+sizeof(inode), SEEK_SET);
                fwrite(&users, sizeof(inode), 1, search);
                fflush(search);
                //crear contenido de users
                file_block root;
                strcpy(root.b_content,"1,G,root\n1,U,root,root,123\n");
                fseek(search, superBloque.s_block_start+sizeof(folder_block), SEEK_SET);
                fwrite(&root, sizeof(file_block), 1, search);
                fflush(search);
                //marcar como usados en los bitmaps
                fseek(search, superBloque.s_bm_inode_start, SEEK_SET);
                fwrite("1", 1, 1, search);
                fflush(search);
                fseek(search, superBloque.s_bm_inode_start+1, SEEK_SET);
                fwrite("1", 1, 1, search);
                fflush(search);
                fseek(search, superBloque.s_bm_block_start, SEEK_SET);
                fwrite("1", 1, 1, search);
                fflush(search);
                fseek(search, superBloque.s_bm_block_start+1, SEEK_SET);
                fwrite("1", 1, 1, search);
                fflush(search);
                cout << "Se ha formateado el disco exitosasmente, ahora cuenta con un sistema de archivos EXT"+to_string(this->fs)+"."<<endl;
                return;
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
            if(name==nameToString(ebr.part_name) && ebr.part_status=='1'){
                
            }
            if(ebr.part_next==-1){
                break;
            }
            anterior = ebr.part_start;
            fseek(search, ebr.part_next, SEEK_SET);
            fread(&ebr, sizeof(EBR), 1, search);
        }
    }
};

int _MKFS::getN(int tamanio){
    int n=0;
    if(this->fs==2){
        n = (tamanio-sizeof(SB))/((3*64)+(4+sizeof(inode)));
    }else if(this->fs==3){
        n = (tamanio-sizeof(SB))/((3*64)+(4+sizeof(inode)+sizeof(Journaling)));
    }else{
        cout <<"ERROR:Las únicas opciones de sistema de archivos son 2fs y 3fs"<<endl;
    }
    return floor(n);
}