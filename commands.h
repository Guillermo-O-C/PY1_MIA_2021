#include <iostream>
#include "mountStructs.h"
#include "user.h"
#include "mbr.h"
#include "partitionStructs.h"
#include "mkfile.h"
#include <vector>
using namespace std;
#pragma once

class _COMMANDS{
    private:
    string path;
    string dest;
    int ugo;
    bool r;
    public:
    _COMMANDS(){
        this->path="";
        this->dest="";
        this->r=false;
        this->ugo=3;
    }
    void setPath(string path, bool isCadena);
    void setDest(string dest, bool isCadena);
    void setUgo(int ugo);
    void setR();
    void exeMv();
    void exeChmod();
    int borrarReferecias(FILE * search, SB superBloque,int partStart, inode carpetaTemporal, string folderName);
    void agregarReferecias(FILE * search, SB superBloque,int partStart, inode carpetaTemporal, string folderName, int inodeLocation);
    void addToJournal(FILE *search, int partStart, SB superBloque, inode carpetaTemporal, int command);
    string nameToString(char * name);
    string charToString(char *name, int loop);
    void cambiarPermisos(FILE* search, SB superbloque, inode inodo, int inodeLocation);
    int searchForFolder(FILE *search, SB superBloque, inode carpetaTemporal, string folderName);
};

void _COMMANDS::setPath(string path, bool isCadena){
    if (isCadena)
    {
        this->path = path.substr(1, path.length() - 2);
    }
    else
    {
        this->path = path;
    }
};

void _COMMANDS::setDest(string dest, bool isCadena){
    if (isCadena)
    {
        this->dest = dest.substr(1, dest.length() - 2);
    }
    else
    {
        this->dest = dest;
    }
};

void _COMMANDS::setUgo(int ugo){
    this->ugo= ugo;
};

void _COMMANDS::setR(){
    this->r=true;
};

void _COMMANDS::exeMv(){
if(this->path=="" || this->dest==""){
        cout << "ERROR: Los parámetros path y name son obligatorios."<<endl;
        return;
    }
    string id = usuarioActivo.partitionID;
    int diskSpot = (int)id[3] - 65;
    int partSpot = id[2] - '0'; //se le resta uno para obotener la posición en el array
    partSpot--;
    if (int(id[3]) < 65)
    { //es una partición con un número de <9
        char temp[2] = {id[2], id[3]};
        partSpot = atoi(temp) - 1; //restamos uno para obtener la posición del array
        diskSpot = (int)id[4] - 65;
    }

    FILE *search =  fopen(discosMontados[diskSpot].path, "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    string name = discosMontados[diskSpot].particiones[partSpot].name; 
    for(int i =0;i<4;i++){
        if(opciones[i].part_status=='1' && opciones[i].part_type=='p'){
            if(name==nameToString(opciones[i].part_name)){
                SB superBloque;
                fseek(search, opciones[i].part_start, SEEK_SET);
                fread(&superBloque, sizeof(SB), 1, search);
                _MKFILE buscador;
                int inodeLocation =0;
                int posicion=0;
                string movido="";
                this->path = (this->path[0] == '/') ? this->path.substr(1, this->path.length()) : this->path;
                vector<string> carpetas = buscador.split(this->path, "/");
                for (int e = 0; e < carpetas.size(); e++)
                { //ciclo para iterar entre las carpetas del path
                    if (e == carpetas.size() - 1)
                    { //el último elelmento es el archivo o carpeta a renombrar
                        SB superBloque;
                        fseek(search, opciones[i].part_start, SEEK_SET);
                        fread(&superBloque, sizeof(SB), 1, search);
                        inode carpetaTemporal;
                        fseek(search, superBloque.s_inode_start + sizeof(inode) * inodeLocation, SEEK_SET);
                        fread(&carpetaTemporal, sizeof(inode), 1, search);
                        string folderName = carpetas[e];
                        //borrar las referencias
                        posicion = borrarReferecias(search, superBloque, opciones[i].part_start, carpetaTemporal,  folderName);
                        movido=folderName;
                        break;
                    }
                    else
                    {
                        SB superBloque;
                        fseek(search, opciones[i].part_start, SEEK_SET);
                        fread(&superBloque, sizeof(SB), 1, search);
                        inode carpetaTemporal;
                        fseek(search, superBloque.s_inode_start + sizeof(inode) * inodeLocation, SEEK_SET);
                        fread(&carpetaTemporal, sizeof(inode), 1, search);
                        string folderName = carpetas[e];
                        inodeLocation = buscador.searchForFolder(search, superBloque, carpetaTemporal, folderName);
                        if (inodeLocation == 0)
                        {
                            cout << "ERROR: No se ha encontrado el archivo el path "<<this->path<<endl;
                            return;
                        }
                    }
                }
                this->dest = (this->dest[0] == '/') ? this->dest.substr(1, this->dest.length()) : this->dest;
                carpetas = buscador.split(this->dest, "/");
                inodeLocation=0;
                for (int e = 0; e < carpetas.size(); e++)
                { //ciclo para iterar entre las carpetas del dest
                    SB superBloque;
                    fseek(search, opciones[i].part_start, SEEK_SET);
                    fread(&superBloque, sizeof(SB), 1, search);
                    inode carpetaTemporal;
                    fseek(search, superBloque.s_inode_start + sizeof(inode) * inodeLocation, SEEK_SET);
                    fread(&carpetaTemporal, sizeof(inode), 1, search);
                    string folderName = carpetas[e];
                    inodeLocation = buscador.searchForFolder(search, superBloque, carpetaTemporal, folderName);
                    if (inodeLocation == 0)
                    {
                        cout << "ERROR: No se ha encontrado el archivo el destino "<<this->dest<<endl;
                        return;
                    }
                }
                //cuando sale del for hay que pegar el inodo
                inode carpetaTemporal;
                fseek(search, superBloque.s_inode_start + sizeof(inode) * inodeLocation, SEEK_SET);
                fread(&carpetaTemporal, sizeof(inode), 1, search);
                agregarReferecias(search, superBloque,  opciones[i].part_start, carpetaTemporal, movido, posicion);
                addToJournal(search, opciones[i].part_start, superBloque, carpetaTemporal, 4);
                return;
            }
        }
    }
};

void _COMMANDS::exeChmod(){
    if(this->path == "" || this->ugo==0){
        cout <<"ERROR: Los parámetros path y ugo son obligatorios."<<endl;
        return;
    }else if(this->ugo<0 || this->ugo>777){
        cout << "ERROR: Los límetes del parámetro ugo son [000-777]."<<endl;
        return;
    }
   string id = usuarioActivo.partitionID;
    int diskSpot = (int)id[3] - 65;
    int partSpot = id[2] - '0'; //se le resta uno para obotener la posición en el array
    partSpot--;
    if (int(id[3]) < 65)
    { //es una partición con un número de <9
        char temp[2] = {id[2], id[3]};
        partSpot = atoi(temp) - 1; //restamos uno para obtener la posición del array
        diskSpot = (int)id[4] - 65;
    }
    FILE *search =  fopen(discosMontados[diskSpot].path, "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    string name = discosMontados[diskSpot].particiones[partSpot].name; 
    for(int i =0;i<4;i++){
        if(opciones[i].part_status=='1' && opciones[i].part_type=='p'){
            if(name==nameToString(opciones[i].part_name)){
                SB superBloque;
                fseek(search, opciones[i].part_start, SEEK_SET);
                fread(&superBloque, sizeof(SB), 1, search);
                _MKFILE buscador;
                int inodeLocation =0;
                this->path = (this->path[0] == '/') ? this->path.substr(1, this->path.length()) : this->path;
                vector<string> carpetas = buscador.split(this->path, "/");
                cout << this->path<<" n="<<carpetas.size()<<endl;
                for (int e = 0; e < carpetas.size(); e++)
                { //ciclo para iterar entre las carpetas del path
                    SB superBloque;
                    fseek(search, opciones[i].part_start, SEEK_SET);
                    fread(&superBloque, sizeof(SB), 1, search);
                    inode carpetaTemporal;
                    fseek(search, superBloque.s_inode_start + sizeof(inode) * inodeLocation, SEEK_SET);
                    fread(&carpetaTemporal, sizeof(inode), 1, search);
                    string folderName = carpetas[e];
                    inodeLocation = searchForFolder(search, superBloque, carpetaTemporal, folderName);
                    if (inodeLocation != 0)
                    {
                        if (e == carpetas.size() - 1)
                        { //es la carpeta que hay que crear
                            if(this->r){
                                fseek(search, superBloque.s_inode_start + sizeof(inode) * inodeLocation, SEEK_SET);
                                fread(&carpetaTemporal, sizeof(inode), 1, search);
                                cambiarPermisos(search,  superBloque, carpetaTemporal, inodeLocation);
                            }else{
                                fseek(search, superBloque.s_inode_start + sizeof(inode) * inodeLocation, SEEK_SET);
                                fread(&carpetaTemporal, sizeof(inode), 1, search);
                                carpetaTemporal.i_perm=this->ugo;
                                fseek(search, superBloque.s_inode_start+sizeof(inode)*inodeLocation, SEEK_SET);
                                fwrite(&carpetaTemporal, sizeof(inode), 1, search);
                                fflush(search);
                            }
                            addToJournal(search, opciones[i].part_start, superBloque, carpetaTemporal, 5);
                            cout << "Se han cambiado los permisos exitosamente."<<endl;
                            return;
                        }
                      /*  abuelo = padre;
                        padre = inodeLocation;*/
                    }
                    else
                    {
                      /*  if (e == carpetas.size() - 1 || this->p)
                        { //es la carpeta que hay que crear || se crea la carpeta
                            abuelo = padre;
                            padre = superBloque.s_first_ino;
                            createFolder(search, opciones[i].part_start, superBloque, carpetaTemporal, folderName, abuelo, padre);
                            inodeLocation = superBloque.s_first_ino;
                            if(e == carpetas.size()-1 && superBloque.s_filesystem_type==3) addToJournal(search, opciones[i].part_start, superBloque, carpetaTemporal);
                        }
                        else
                        {*/
                            cout << "ERROR: No existe la carpeta " + folderName << endl;
                            return;
                       // }
                    }
                }
                return;
            }
        }
    }
};

int _COMMANDS::borrarReferecias(FILE * search, SB superBloque,int partStart, inode carpetaTemporal, string folderName){
    for (int j = 0; j < 12; j++)
    { //iterando sobre los 12 apuntadores directos
        if (carpetaTemporal.i_block[j] != -1)
        { //direcciona a un bloque de carpeta
            folder_block folder;
            fseek(search, superBloque.s_block_start + 64 * carpetaTemporal.i_block[j], SEEK_SET);
            fread(&folder, 64, 1, search);
            for (int o = 0; o < 4; o++)
            { //iterando sobre los nombres del bloque de carpetas
                if (folder.b_content[o].b_inodo != -1)
                {
                    if (charToString(folder.b_content[o].b_name, 12) == folderName)
                    {
                        int posicion  = folder.b_content[o].b_inodo;
                        strcpy(folder.b_content[o].b_name,"");
                        folder.b_content[o].b_inodo=-1;
                        fseek(search, superBloque.s_block_start + 64 * carpetaTemporal.i_block[j], SEEK_SET);
                        fwrite(&folder, 64, 1, search);
                        fflush(search);
                        return posicion;
                    }
                }
            }
        }
    }
    if (carpetaTemporal.i_block[12] != -1)
    { //se está usando el API1
        pointers apuntadores;
        fseek(search, superBloque.s_block_start + 64 * carpetaTemporal.i_block[12], SEEK_SET);
        fread(&apuntadores, 64, 1, search);
        for (int i = 0; i < 16; i++)
        {
            if (apuntadores.b_pointers[i] != -1)
            { //direcciona a un bloque de carpeta
                folder_block folder;
                fseek(search, superBloque.s_block_start + 64 * apuntadores.b_pointers[i], SEEK_SET);
                fread(&folder, 64, 1, search);
                for (int o = 0; o < 4; o++)
                { //iterando sobre los nombres del bloque de carpetas
                    if (folder.b_content[o].b_inodo != -1)
                    {
                        if (charToString(folder.b_content[o].b_name, 12) == folderName)
                        {                            
                            int posicion  = folder.b_content[o].b_inodo;
                            strcpy(folder.b_content[o].b_name,"");
                            folder.b_content[o].b_inodo=-1;
                            fseek(search, superBloque.s_block_start + 64 * apuntadores.b_pointers[i], SEEK_SET);
                            fwrite(&folder, 64, 1, search);
                            fflush(search);
                            return posicion;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void _COMMANDS::agregarReferecias(FILE * search, SB superBloque,int partStart, inode carpetaTemporal, string folderName, int inodeLocation){
    time_t t;
    struct tm *tm;
    char fechayhora[16];
    t = time(NULL);
    tm = localtime(&t);
    for (int j = 0; j < 12; j++)
    { //iterando sobre los 12 apuntadores directos
        if (carpetaTemporal.i_block[j] != -1)
        { //direcciona a un bloque de carpeta
            folder_block folder;
            fseek(search, superBloque.s_block_start + 64 * carpetaTemporal.i_block[j], SEEK_SET);
            fread(&folder, 64, 1, search);
            for (int o = 0; o < 4; o++)
            { //iterando sobre los nombres del bloque de carpetas
                fseek(search, superBloque.s_block_start + 64 * carpetaTemporal.i_block[j], SEEK_SET);
                fread(&folder, 64, 1, search);
                if (folder.b_content[o].b_inodo == -1)
                { 
                    //actualizar el bloque de carpeta actual
                    folder.b_content[o].b_inodo = inodeLocation; //se aumenta el siguiente inodo libre
                    strcpy(folder.b_content[o].b_name, folderName.c_str());
                    fseek(search, superBloque.s_block_start + 64 * carpetaTemporal.i_block[j], SEEK_SET);
                    fwrite(&folder, 64, 1, search);
                    fflush(search);
                    cout << "Se ha movido la carpeta o archivo " + folderName + " exitosamente" << endl;
                    folder_block padre;
                    fseek(search, carpetaTemporal.i_block[0]*64+superBloque.s_block_start, SEEK_SET);
                    fread(&padre, 64, 1, search);
                    inode movido;
                    fseek(search, superBloque.s_inode_start + sizeof(inode)*inodeLocation, SEEK_SET);
                    fread(&movido, sizeof(inode), 1, search);
                    folder_block block0;
                    fseek(search, movido.i_block[0]*64+superBloque.s_block_start, SEEK_SET);
                    fread(&block0, 64, 1, search);
                    block0.b_content[1].b_inodo=padre.b_content[0].b_inodo;
                    fseek(search, movido.i_block[0]*64+superBloque.s_block_start, SEEK_SET);
                    fwrite(&block0, 64, 1, search);
                    fflush(search);
                    return;
                }
            }
        }
        else
        {
            folder_block padre;
            fseek(search, carpetaTemporal.i_block[0]*64+superBloque.s_block_start, SEEK_SET);
            fread(&padre, 64, 1, search);
            //actualizar el espacio del apuntador j
            fseek(search, superBloque.s_inode_start + padre.b_content[0].b_inodo * sizeof(inode), SEEK_SET);
            fread(&carpetaTemporal, sizeof(inode), 1, search);
            //cout << "previo->"<<carpetaTemporal.i_block[j-1]<<endl;/
            carpetaTemporal.i_block[j] = superBloque.s_first_blo; //se aumenta el siguiente bloque libre
            //strcpy(carpetaTemporal.i_mtime, fechayhora);  //borra los apuntadores de i_block en j-1
            fseek(search, superBloque.s_inode_start + padre.b_content[0].b_inodo * sizeof(inode), SEEK_SET);
            fwrite(&carpetaTemporal, sizeof(inode), 1, search);
            fflush(search);
            //cout << "previo->"<<carpetaTemporal.i_block[j-1]<<endl;
            //actualizar bm de bloque
            fseek(search, superBloque.s_bm_block_start + superBloque.s_first_blo, SEEK_SET); //era de inodos
            fwrite("1", 1, 1, search);
            fflush(search);
            //actualizar superBloque
            superBloque.s_first_blo++;
            superBloque.s_free_blocks_count--;
            fseek(search, partStart, SEEK_SET);
            fwrite(&superBloque, sizeof(SB), 1, search);
            fflush(search);
            //actualizar el bloque de carpeta actual creando bloque carpeta en posición j
            folder_block carpeta;
            carpeta.b_content[0].b_inodo = inodeLocation; //se aumenta el siguiente inodo libre
            strcpy(carpeta.b_content[0].b_name, folderName.c_str());
            fseek(search, superBloque.s_block_start + 64 * carpetaTemporal.i_block[j], SEEK_SET);
            fwrite(&carpeta, 64, 1, search);
            fflush(search);
            //actualizar bitmap de inodos
            fseek(search, superBloque.s_bm_block_start + superBloque.s_first_blo, SEEK_SET);
            fwrite("1", 1, 1, search);
            fflush(search);
            //actualizar el superbloque
            superBloque.s_first_blo++;
            superBloque.s_free_blocks_count--;
            fseek(search, partStart, SEEK_SET);
            fwrite(&superBloque, sizeof(SB), 1, search);
            fflush(search);
            //actualizar fecha de modificación del inodo
            inode movido;
            fseek(search, superBloque.s_inode_start + sizeof(inode)*inodeLocation, SEEK_SET);
            fread(&movido, sizeof(inode), 1, search);
            folder_block block0;
            fseek(search, movido.i_block[0]*64+superBloque.s_block_start, SEEK_SET);
            fread(&block0, 64, 1, search);
            block0.b_content[1].b_inodo=padre.b_content[0].b_inodo;
            fseek(search, movido.i_block[0]*64+superBloque.s_block_start, SEEK_SET);
            fwrite(&block0, 64, 1, search);
            fflush(search);
            cout << "Se ha movido la carpeta " + folderName + " exitosamente" << endl;
            return;
        }
    }
    //se está usando el API1
    if(carpetaTemporal.i_block[12]==-1){//crear el bloque de apuntadores
        folder_block padre;
        fseek(search, carpetaTemporal.i_block[0]*64+superBloque.s_block_start, SEEK_SET);
        fread(&padre, 64, 1, search);
        int temporal = carpetaTemporal.i_block[0];
        carpetaTemporal.i_block[12] = superBloque.s_first_blo; //se aumenta el siguiente bloque libre
        strcpy(carpetaTemporal.i_mtime, fechayhora);
        fseek(search, superBloque.s_inode_start + padre.b_content[0].b_inodo * sizeof(inode), SEEK_SET);
        fwrite(&carpetaTemporal, sizeof(inode), 1, search);
        fflush(search);
        carpetaTemporal.i_block[0] = temporal; //se aumenta el siguiente bloque libre
        fseek(search, superBloque.s_inode_start + padre.b_content[0].b_inodo * sizeof(inode), SEEK_SET);
        fwrite(&carpetaTemporal, sizeof(inode), 1, search);
        fflush(search);
        pointers apuntadores;
        fseek(search, superBloque.s_block_start + 64 * carpetaTemporal.i_block[12], SEEK_SET);
        fwrite(&apuntadores, 64, 1, search);
        fflush(search);
        //actualizar bitmap de bloques
        fseek(search, superBloque.s_bm_block_start + superBloque.s_first_blo, SEEK_SET);
        fwrite("3", 1, 1, search);
        fflush(search);
        //actualizar el superbloque
        superBloque.s_first_blo++;
        superBloque.s_free_blocks_count--;
        fseek(search, partStart, SEEK_SET);
        fwrite(&superBloque, sizeof(SB), 1, search);
        fflush(search);
    }
    pointers API1;
    for (int i = 0; i < 16; i++)
    {
        fseek(search, superBloque.s_block_start + 64 * carpetaTemporal.i_block[12], SEEK_SET);
        fread(&API1, 64, 1, search);
        if (API1.b_pointers[i] != -1){
            folder_block folder;
            fseek(search, superBloque.s_block_start + 64 * API1.b_pointers[i], SEEK_SET);
            fread(&folder, 64, 1, search);
            for (int o = 0; o < 4; o++){ //iterando sobre los nombres del bloque de carpetas
                //actualizar el bloque de carpeta actual
                folder.b_content[o].b_inodo = inodeLocation; //se aumenta el siguiente inodo libre
                strcpy(folder.b_content[o].b_name, folderName.c_str());
                fseek(search, superBloque.s_block_start + 64 *API1.b_pointers[i], SEEK_SET);
                fwrite(&folder, 64, 1, search);
                fflush(search);
                cout << "Se ha movido la carpeta o archivo " + folderName + " exitosamente" << endl;
                folder_block padre;
                fseek(search, carpetaTemporal.i_block[0]*64+superBloque.s_block_start, SEEK_SET);
                fread(&padre, 64, 1, search);
                inode movido;
                fseek(search, superBloque.s_inode_start + sizeof(inode)*inodeLocation, SEEK_SET);
                fread(&movido, sizeof(inode), 1, search);
                folder_block block0;
                fseek(search, movido.i_block[0]*64+superBloque.s_block_start, SEEK_SET);
                fread(&block0, 64, 1, search);
                cout << "el nuevo abuelo es "<<padre.b_content[0].b_inodo<<endl;
                block0.b_content[1].b_inodo=padre.b_content[0].b_inodo;
                fseek(search, movido.i_block[0]*64+superBloque.s_block_start, SEEK_SET);
                fwrite(&block0, 64, 1, search);
                fflush(search);
                return;
            }
        }
        else
        {
            folder_block padre;
            fseek(search, carpetaTemporal.i_block[0]*64+superBloque.s_block_start, SEEK_SET);
            fread(&padre, 64, 1, search);
            //actualizar el espacio del apuntador j
            fseek(search, superBloque.s_inode_start + padre.b_content[0].b_inodo * sizeof(inode), SEEK_SET);
            fread(&carpetaTemporal, sizeof(inode), 1, search);
            //cout << "previo->"<<carpetaTemporal.i_block[j-1]<<endl;/
            API1.b_pointers[i] = superBloque.s_first_blo; //se aumenta el siguiente bloque libre
            //strcpy(carpetaTemporal.i_mtime, fechayhora);  //borra los apuntadores de i_block en j-1
            fseek(search, superBloque.s_inode_start + padre.b_content[0].b_inodo * sizeof(inode), SEEK_SET);
            fwrite(&carpetaTemporal, sizeof(inode), 1, search);
            fflush(search);
            //cout << "previo->"<<carpetaTemporal.i_block[j-1]<<endl;
            //actualizar bm de bloque
            fseek(search, superBloque.s_bm_block_start + superBloque.s_first_blo, SEEK_SET); //era de inodos
            fwrite("1", 1, 1, search);
            fflush(search);
            //actualizar superBloque
            superBloque.s_first_blo++;
            superBloque.s_free_blocks_count--;
            fseek(search, partStart, SEEK_SET);
            fwrite(&superBloque, sizeof(SB), 1, search);
            fflush(search);
            //actualizar el bloque de carpeta actual creando bloque carpeta en posición j
            folder_block carpeta;
            carpeta.b_content[0].b_inodo = inodeLocation; //se aumenta el siguiente inodo libre
            strcpy(carpeta.b_content[0].b_name, folderName.c_str());
            fseek(search, superBloque.s_block_start + 64 * API1.b_pointers[i], SEEK_SET);
            fwrite(&carpeta, 64, 1, search);
            fflush(search);
            //actualizar bitmap de inodos
            fseek(search, superBloque.s_bm_block_start + superBloque.s_first_blo, SEEK_SET);
            fwrite("1", 1, 1, search);
            fflush(search);
            //actualizar el superbloque
            superBloque.s_first_blo++;
            superBloque.s_free_blocks_count--;
            fseek(search, partStart, SEEK_SET);
            fwrite(&superBloque, sizeof(SB), 1, search);
            fflush(search);
            //actualizar fecha de modificación del inodo
            inode movido;
            fseek(search, superBloque.s_inode_start + sizeof(inode)*inodeLocation, SEEK_SET);
            fread(&movido, sizeof(inode), 1, search);
            folder_block block0;
            fseek(search, movido.i_block[0]*64+superBloque.s_block_start, SEEK_SET);
            fread(&block0, 64, 1, search);
            block0.b_content[1].b_inodo=padre.b_content[0].b_inodo;
            fseek(search, movido.i_block[0]*64+superBloque.s_block_start, SEEK_SET);
            fwrite(&block0, 64, 1, search);
            fflush(search);
            cout << "Se ha movido la carpeta " + folderName + " exitosamente" << endl;
            return;
        }
    }
}

void _COMMANDS::addToJournal(FILE *search, int partStart, SB superBloque, inode carpetaTemporal, int command){
    
    Journaling nuevo;
    int posicion = nuevo.nextAvailable(search, partStart);
    time_t t;
    struct tm *tm;
    char fechayhora[16];
    t = time(NULL);
    tm = localtime(&t);
    strftime(fechayhora, 20, "%d/%m/%Y %H:%M", tm);
    
    switch(command){
        case 4:
            strcpy(nuevo.path,this->path.c_str());
            strcpy(nuevo.tipo_operacion,"mv");
            strcpy(nuevo.contenido, this->dest.c_str());
            strcpy(nuevo.log_fecha, fechayhora);
            nuevo.size=0;
            nuevo.tipo='4';
            fseek(search, partStart+sizeof(SB)+posicion*sizeof(Journaling), SEEK_SET);
            fwrite(&nuevo, sizeof(Journaling), 1, search);
            fflush(search);
            break;
        case 5:
            strcpy(nuevo.path,this->path.c_str());
            strcpy(nuevo.tipo_operacion,"chmod");
            strcpy(nuevo.contenido, to_string(this->ugo).c_str());
            strcpy(nuevo.log_fecha, fechayhora);
            nuevo.size=(this->r)?-1:0;
            nuevo.tipo='5';
            fseek(search, partStart+sizeof(SB)+posicion*sizeof(Journaling), SEEK_SET);
            fwrite(&nuevo, sizeof(Journaling), 1, search);
            fflush(search);
            break;
    }
}

string _COMMANDS::nameToString(char * name){
    string str;
    for(int i=0;i < 16;i++){
        if(name[i]==int(NULL)) break;
        str=str+name[i];
    }
    return str;
}

string _COMMANDS::charToString(char *name, int loops)
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

void _COMMANDS::cambiarPermisos(FILE* search, SB superbloque, inode inodo, int inodeLocation){
    //color inodo 54b4eb, content f7de1b, carpetas 04ff00, apuntadores ff8c00
    inodo.i_perm=this->ugo;
    fseek(search, superbloque.s_inode_start+sizeof(inode)*inodeLocation, SEEK_SET);
    fwrite(&inodo, sizeof(inode), 1, search);
    fflush(search);
    if(inodo.i_type=='0'){
        for(int i =0;i<12;i++){
            if(inodo.i_block[i]!=-1){
                //existe una carpeta
                folder_block folder;
                fseek(search, superbloque.s_block_start+inodo.i_block[i]*64, SEEK_SET);
                fread(&folder, 64, 1, search);
                for(int e =0;e<4;e++){
                    if(folder.b_content[e].b_inodo!=-1){
                        if(i==0 && e==0 || i==0 && e==1)continue;//para que no se encicle con el padre y abuelo
                        fseek(search, superbloque.s_inode_start+folder.b_content[e].b_inodo*sizeof(inode),SEEK_SET);
                        inode next;
                        fread(&next, sizeof(inode), 1, search);
                        cambiarPermisos(search, superbloque, next, folder.b_content[e].b_inodo);
                    }                    
                }      
            }
        }
        //API1
        if(inodo.i_block[12]!=-1){//API1 en uso
            pointers apuntadores;
            fseek(search, 64*inodo.i_block[12]+superbloque.s_block_start, SEEK_SET);
            fread(&apuntadores, 64, 1, search);
            for(int i=0;i<16;i++){
                if(apuntadores.b_pointers[i]!=-1){//dirigen a un bloque de tipo carpeta
                    folder_block folder;
                    fseek(search, superbloque.s_block_start+apuntadores.b_pointers[i]*64, SEEK_SET);
                    fread(&folder, 64, 1, search);
                    for(int e =0;e<4;e++){
                        if(folder.b_content[e].b_inodo!=-1){
                            fseek(search, superbloque.s_inode_start+folder.b_content[e].b_inodo*sizeof(inode),SEEK_SET);
                            inode next;
                            fread(&next, sizeof(inode), 1, search);
                            cambiarPermisos(search, superbloque, next, folder.b_content[e].b_inodo);
                        }                    
                    } 
                }                    
            }    
        }
    }
}

int _COMMANDS::searchForFolder(FILE *search, SB superBloque, inode carpetaTemporal, string folderName)
{
    for (int j = 0; j < 12; j++)
    { //iterando sobre los 12 apuntadores directos
        if (carpetaTemporal.i_block[j] != -1)
        { //direcciona a un bloque de carpeta
            folder_block folder;
            fseek(search, superBloque.s_block_start + 64 * carpetaTemporal.i_block[j], SEEK_SET);
            fread(&folder, 64, 1, search);
            for (int o = 0; o < 4; o++)
            { //iterando sobre los nombres del bloque de carpetas
                if (folder.b_content[o].b_inodo != -1)
                {
                    cout << folder.b_content[o].b_name<<" ? "<<folderName<<endl;
                    if (charToString(folder.b_content[o].b_name, 12) == folderName)
                    {
                        fseek(search, superBloque.s_inode_start + sizeof(inode) * folder.b_content[o].b_inodo, SEEK_SET);
                        fread(&carpetaTemporal, sizeof(inode), 1, search);
                        return folder.b_content[o].b_inodo;
                    }
                }
            }
        }
    }
    if (carpetaTemporal.i_block[12] != -1)
    { //se está usando el API1
        pointers apuntadores;
        fseek(search, superBloque.s_block_start + 64 * carpetaTemporal.i_block[12], SEEK_SET);
        fread(&apuntadores, 64, 1, search);
        for (int i = 0; i < 16; i++)
        {
            if (apuntadores.b_pointers[i] != -1)
            { //direcciona a un bloque de carpeta
                folder_block folder;
                fseek(search, superBloque.s_block_start + 64 * apuntadores.b_pointers[i], SEEK_SET);
                fread(&folder, 64, 1, search);
                for (int o = 0; o < 4; o++)
                { //iterando sobre los nombres del bloque de carpetas
                    if (folder.b_content[o].b_inodo != -1)
                    {
                        if (charToString(folder.b_content[o].b_name, 12) == folderName)
                        {
                            //la carpeta ya existe
                            fseek(search, superBloque.s_inode_start + sizeof(inode) * folder.b_content[o].b_inodo, SEEK_SET);
                            fread(&carpetaTemporal, sizeof(inode), 1, search);
                            return folder.b_content[o].b_inodo;
                        }
                    }
                }
            }
        }
    }
    return 0;   
}