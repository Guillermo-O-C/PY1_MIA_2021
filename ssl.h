#include <iostream>
#include "mountStructs.h"
#include "mbr.h"
#include "partitionStructs.h"
#include "mkdir.h"
#include "mkfile.h"
#include "ren.h"
#include "commands.h"
using namespace std;

class _SSL{
    private:
    string id;
    public:
    _SSL(){};
    void setId(string id);
    void simulateLoss();
    void simulateRecovery();
    string toUpperCase(string cadena);
    string charToString(char *name, int loops);
};

void _SSL::setId(string id){
    this->id=toUpperCase(id);
};

void _SSL::simulateLoss(){
    int diskSpot = (int)this->id[3]-65;
    int partSpot=this->id[2]-'0';//se le resta uno para obotener la posición en el array
    partSpot--;
    if(int(this->id[3])<65){//es una partición con un número de <9
        char temp[2]={ this->id[2], this->id[3]};
        partSpot=atoi(temp)-1;//restamos uno para obtener la posición del array
        diskSpot = (int)this->id[4]-65;
    }
    if(discosMontados[diskSpot].status==1){//el disco funciona
        if(discosMontados[diskSpot].particiones[partSpot].status==1){
            FILE * search = fopen(discosMontados[diskSpot].path, "rb+");
            MBR mbr;
            fread(&mbr, sizeof(MBR), 1, search);
            partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
            SB superBloque;
            for(int i =0;i<4;i++){
                if(opciones[i].part_status=='1' && opciones[i].part_type=='p'){
                    if(charToString(discosMontados[diskSpot].particiones[partSpot].name, 16)==charToString(opciones[i].part_name, 16)){//se encontró la partición
                        fseek(search, opciones[i].part_start, SEEK_SET);
                        fread(&superBloque, sizeof(SB), 1, search);
                        if(superBloque.s_filesystem_type!=3){
                            cout <<"ERROR: No se puede usar el comando Loss sobre un sistema de archivos EXT2"<<endl;
                            return;
                        }
                        for(int e=0;e<superBloque.s_inodes_count;e++){
                            fseek(search, superBloque.s_bm_inode_start + e, SEEK_SET);
                            fwrite("0", 1, 1, search);
                            fflush(search);
                        }
                        for(int e=0;e<superBloque.s_blocks_count;e++){
                            fseek(search, superBloque.s_bm_block_start + e, SEEK_SET);
                            fwrite("0", 1, 1, search);
                            fflush(search);
                        }
                        for(int e=0;e<superBloque.s_inodes_count;e++){
                            fseek(search, superBloque.s_inode_start + e*sizeof(inode) , SEEK_SET);
                            fwrite("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", sizeof(inode), 1, search);
                            fflush(search);
                        }
                        for(int e=0;e<superBloque.s_inodes_count*3;e++){
                            fseek(search, superBloque.s_block_start+e*64, SEEK_SET);
                            fwrite("000000000000000000000000000000000000000000000000000000000000000", 64, 1, search);
                            fflush(search);
                        }
                        cout <<"La partición "+this->id+" ha sufrido un fallo, usar el recovery para recuperar la información."<<endl; 
                        return;
                    } 
                }        
            }
        }else{
            cout << "ERROR:No hay una partición montada en el espacio "<<(char)(partSpot+1)<<endl;
        }
    }else{
        cout << "ERROR:No hay un disco en el espacio de la letra "<<(char)(diskSpot+65)<<endl;
    }
};

void _SSL::simulateRecovery(){
int diskSpot = (int)this->id[3]-65;
    int partSpot=this->id[2]-'0';//se le resta uno para obotener la posición en el array
    partSpot--;
    if(int(this->id[3])<65){//es una partición con un número de <9
        char temp[2]={ this->id[2], this->id[3]};
        partSpot=atoi(temp)-1;//restamos uno para obtener la posición del array
        diskSpot = (int)this->id[4]-65;
    }
    if(discosMontados[diskSpot].status==1){//el disco funciona
        if(discosMontados[diskSpot].particiones[partSpot].status==1){
            FILE * search = fopen(discosMontados[diskSpot].path, "rb+");
            MBR mbr;
            time_t t;
            struct tm *tm;
            char fechayhora[16];
            t = time(NULL);
            tm = localtime(&t);
            strftime(fechayhora, 20, "%d/%m/%Y %H:%M", tm);
            fread(&mbr, sizeof(MBR), 1, search);
            partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
            SB superBloque;
            for(int i =0;i<4;i++){
                if(opciones[i].part_status=='1' && opciones[i].part_type=='p'){
                    if(charToString(discosMontados[diskSpot].particiones[partSpot].name, 16)==charToString(opciones[i].part_name, 16)){//se encontró la partición
                        fseek(search, opciones[i].part_start, SEEK_SET);
                        fread(&superBloque, sizeof(SB), 1, search); 
                        if(superBloque.s_filesystem_type!=3){
                            cout <<"ERROR: No se puede usar el comando Recovery sobre un sistema de archivos EXT2"<<endl;
                            return;
                        } 
                        superBloque.s_first_ino=2;//0 es de raiz y 1 es de users.txt
                        superBloque.s_first_blo=2;//0 es bloque de carpeta de raiz y 1 es de contenido para users.txt 
                        superBloque.s_free_blocks_count=superBloque.s_blocks_count-2;
                        superBloque.s_free_inodes_count=superBloque.s_inodes_count-2;
                        fseek(search, opciones[i].part_start, SEEK_SET);
                        fwrite(&superBloque, sizeof(SB), 1, search);
                        fflush(search);
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
                        users.i_type='1';
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
                        fwrite("2", 1, 1, search);
                        fflush(search);
                        Journaling temp;
                        int puntoDeRetorno=temp.nextAvailable(search, opciones[i].part_start);
                        for(int e =2;e<superBloque.s_inodes_count;e++){
                            fseek(search, opciones[i].part_start+sizeof(SB)+e*sizeof(Journaling), SEEK_SET);
                            fread(&temp, sizeof(Journaling), 1, search);
                            if(temp.tipo!='1' && temp.tipo!='2' && temp.tipo!='3' && temp.tipo!='4' && temp.tipo!='5'){//termina el journal
                                cout << "La recuperación del sistema ha terminado."<<endl;
                                break;
                            }
                            if(charToString(temp.tipo_operacion, 10)=="mkdir" || temp.tipo=='1'){
                                _MKDIR mkdir;
                                mkdir.setP();
                                mkdir.setPath(charToString(temp.path, 60), false);
                                mkdir.exe();
                            }else if(charToString(temp.tipo_operacion, 10)=="mkfile" || temp.tipo=='2'){
                                _MKFILE mkfile;
                                mkfile.setR();
                                if(temp.size==-1){
                                    mkfile.setCont(charToString(temp.contenido,100), false);
                                }else{
                                    mkfile.setSize(temp.size);
                                }
                                mkfile.setPath(charToString(temp.path,60), false);
                                mkfile.exe();
                            }else if(charToString(temp.tipo_operacion, 10)=="ren" || temp.tipo=='3'){
                                _REN ren;
                                ren.setPath(charToString(temp.path,60), false);
                                ren.setName(charToString(temp.contenido, 100), false);
                                ren.exe();
                            }else if(charToString(temp.tipo_operacion, 10)=="mv" || temp.tipo=='4'){
                                _COMMANDS command;
                                command.setPath(charToString(temp.path,60), false);
                                command.setDest(charToString(temp.contenido, 100), false);
                                command.exeMv();
                            }else if(charToString(temp.tipo_operacion, 10)=="chmod" || temp.tipo=='5'){
                                _COMMANDS command;
                                if(temp.size==-1)command.setR();
                                command.setPath(charToString(temp.path,60), false);
                                command.exeChmod();
                            }
                        } 
                        for(int e =puntoDeRetorno;e<superBloque.s_inodes_count;e++){
                            fseek(search, opciones[i].part_start+sizeof(SB)+e*sizeof(Journaling), SEEK_SET);
                            fwrite("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", sizeof(Journaling), 1, search);
                            fflush(search);
                        }    
                    } 
                }        
            }
        }else{
            cout << "ERROR:No hay una partición montada en el espacio "<<(char)(partSpot+1)<<endl;
        }
    }else{
        cout << "ERROR:No hay un disco en el espacio de la letra "<<(char)(diskSpot+65)<<endl;
    }
};

string _SSL::toUpperCase(string cadena){
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

string _SSL::charToString(char *name, int loops)
{
    string str;
    for (int i = 0; i < loops; i++)
    {
        if (name[i] == int(NULL))
            break;
        str = str + name[i];
    }
    return str;
}