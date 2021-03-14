#include <iostream>
#include "mountStructs.h"
#include "user.h"
#include "mbr.h"
#include "partitionStructs.h"
#include "mkfile.h"
#include <vector>
using namespace std;
#pragma once

class _REN{
    private:
        string path;
        string name;
    public:
        _REN(){
            this->name="";
            this->path="";
        };
        void setPath(string path, bool isCadena);
        void setName(string name, bool isCadena);
        void exe();
        void renombrar(FILE *search,SB superBloque,int partStart,inode carpetaTemporal,string folderName);
        string nameToString(char * name);
        string charToString(char *name, int loops);
        void addToJournal(FILE *search, int partStart, SB superBloque, inode carpetaTemporal);
};

void _REN::setPath(string path, bool isCadena)
{
    if (isCadena)
    {
        this->path = path.substr(1, path.length() - 2);
    }
    else
    {
        this->path = path;
    }
};

void _REN::setName(string name, bool isCadena)
{
    if (isCadena)
    {
        this->name = name.substr(1, name.length() - 2);
    }
    else
    {
        this->name = name;
    }
};

void _REN::exe(){
    if(this->path=="" || this->name==""){
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
                SB superbloque;
                fseek(search, opciones[i].part_start, SEEK_SET);
                fread(&superbloque, sizeof(SB), 1, search);
                _MKFILE buscador;
                int inodeLocation =0;
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
                        renombrar(search,superBloque, opciones[i].part_start, carpetaTemporal, folderName);
                        return;
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
                        }
                    }
                }

            }
        }
    }
};

void _REN::renombrar(FILE *search,SB superBloque, int partStart,inode carpetaTemporal,string folderName){
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
                        strcpy(folder.b_content[o].b_name,this->name.c_str());
                        fseek(search, superBloque.s_block_start + 64 * carpetaTemporal.i_block[j], SEEK_SET);
                        fwrite(&folder, 64, 1, search);
                        fflush(search);
                        addToJournal(search, partStart, superBloque, carpetaTemporal);
                        cout << "Se ha renombrado el archivo o carpeta con exitosamente."<<endl;
                        return;
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
                            strcpy(folder.b_content[o].b_name,this->name.c_str());
                            fseek(search, superBloque.s_block_start + 64 * apuntadores.b_pointers[i], SEEK_SET);
                            fwrite(&folder, 64, 1, search);
                            fflush(search);
                            addToJournal(search, partStart, superBloque, carpetaTemporal);
                            cout << "Se ha renombrado el archivo o carpeta con exitosamente."<<endl;
                            return;
                        }
                    }
                }
            }
        }
    }
    cout << "ERROR: No se ha podido renombrar el archivo o carpeta."<<endl;
}

string _REN::nameToString(char * name){
    string str;
    for(int i=0;i < 16;i++){
        if(name[i]==int(NULL)) break;
        str=str+name[i];
    }
    return str;
}

string _REN::charToString(char *name, int loops)
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

void _REN::addToJournal(FILE *search, int partStart, SB superBloque, inode carpetaTemporal){
    Journaling nuevo;
    int posicion = nuevo.nextAvailable(search, partStart);
    time_t t;
    struct tm *tm;
    char fechayhora[16];
    t = time(NULL);
    tm = localtime(&t);
    nuevo.size=0;
    nuevo.tipo='3';
    strftime(fechayhora, 20, "%d/%m/%Y %H:%M", tm);
    strcpy(nuevo.path,this->path.c_str());
    strcpy(nuevo.log_fecha, fechayhora);
    strcpy(nuevo.tipo_operacion,"ren");
    strcpy(nuevo.contenido, this->name.c_str());
    fseek(search, partStart+sizeof(SB)+posicion*sizeof(Journaling), SEEK_SET);
    fwrite(&nuevo, sizeof(Journaling), 1, search);
    fflush(search);
}
