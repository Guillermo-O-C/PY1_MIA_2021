#include <iostream>
#include "mountStructs.h"
#include "user.h"
#include "mbr.h"
#include "partitionStructs.h"
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
    void setPath(string path);
    void setP();
    void exe();
};
void setPath(string path, bool isCadena){
    if(isCadena){
        this->path = path.substr(1, path.length()-2);
    }else{
        this->path = path;
    }
};
void setP(){
    this->p=true;
};
void exe(){

    this->id=toUpperCase(id);
    int diskSpot = (int)id[3]-65;
    int partSpot=id[2]-'0';//se le resta uno para obotener la posición en el array
    partSpot--;
    if(int(id[3])<65){//es una partición con un número de <9
        char temp[2]={ id[2], id[3]};
        partSpot=atoi(temp)-1;//restamos uno para obtener la posición del array
        diskSpot = (int)id[4]-65;
    }
    FILE *search =  fopen(discosMontados[diskSpot].path.c_str(), "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    string name = discosMontados[this->diskSpot].particiones[this->partSpot].name;  
    for(int i =0;i<4;i++){
        if(opciones[i].part_status=='1' && opciones[i].part_type=='p'){
            if(name==nameToString(opciones[i].part_name)){//está dentro de la partición
                SB superBloque;
                fseek(search, opciones[i].part_start, SEEK_SET);
                fread(&superBloque, sizeof(SB), 1, search);
                
            }
        }
    }
};