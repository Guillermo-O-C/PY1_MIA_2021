#include <iostream>
using namespace std;
#include "ebr.h"


class _FDISK{
    private:
    int size;
    string u;
    string path;
    string type;
    string f;
    string delete_;
    string name;
    int add;
    public:
    _FDISK(){
        this->size=0;
        this->path="";
        this->u="k";
        this->type="p";
        this->f="wf";
        this->delete_ = "";
        this->name="";
        this->add=0;
    };
    void setSize(int size);
    void setUnit(string u);
    void setPath(string path, bool isCadena);
    void setType(string type);
    void setFit(string f);
    void setDelete(string delete_);
    void setName(string name, bool isCadena);
    void setAdd(int add);
    void exe();
    int choosePartition(MBR& mbr);
    int createLogicPartition(partition& particion);
    string toLowerCase(string cadena);
    void deletePartition();
    string toString(char * name);
};

void _FDISK::setSize(int size){
    this->size=size;
};
void _FDISK::setUnit(string u){
    this->u=toLowerCase(u);
};
void _FDISK::setPath(string path, bool isCadena){
    if(isCadena){
        this->path = path.substr(1, path.length()-2);
    }else{
        this->path = path;
    }
};
void _FDISK::setType(string type){
    this->type=toLowerCase(type);
};
void _FDISK::setFit(string f){
    this->f=toLowerCase(f);
};
void _FDISK::setDelete(string delete_){
    this->delete_=toLowerCase(delete_);
};
void _FDISK::setName(string name, bool isCadena){
    if(isCadena){
        this->name = name.substr(1, name.length()-2);
    }else{
        this->name = name;
    }
};
void _FDISK::setAdd(int add){
    this->add=add;
};

void _FDISK::exe(){
    if(this->delete_!="" && this->add!=0){
        cout <<"ERROR: Parámetros incompatibles, llamado a delete y add. "<<endl;
    }
    //if(this->delete_=="") this->delete_="fast";

    if(this->size<=0 && this->delete_=="" && this->add==0){
        cout<<"ERROR:no se puede crear un disco con el tamaño " << this->size <<endl;
    }else if(this->path==""){
        cout<<"ERROR:el parámetro PATH es obligatorio."<<endl;
    }else if(this->type!="p" && this->type!="e" && this->type!="l"){
        cout<<"ERROR:no existe la type "<<this->type<<endl;
    }else if(this->u!="b" && this->u!="k" && this->u!="m"){
        cout<<"ERROR:no existe la unidad de datos "<<this->u<<endl;
    }else if(this->f!="bf" && this->f!="ff" && this->f!="wf"){
        cout<<"ERROR:no existe el fit "<<this->f<<endl;
    }/*else if(this->delete_!="fast" && this->delete_!="full"){
        cout<<"ERROR:el parametro delete no acepta el valor "<<this->delete_<<endl; 
    }*/else if(this->name==""){
        cout<<"ERROR:el parámetro NAME es obligatorio."<<endl;
    }else{
        if(this->delete_!=""){
            deletePartition();
            return;
        }

        if(this->u=="k"){
            this->size=this->size*1024;
        }
        else if(this->u=="m"){
            this->size=this->size*1024*1024;
        }

        FILE *existe = fopen(this->path.c_str(),"r");
        if(existe==NULL){
            cout << "ERROR: El disco "<<this->path<<" no existe."<<endl;
            return;
        }
        fclose(existe);

        FILE *search =  fopen(this->path.c_str(), "rb+");
        MBR mbr;
        fread(&mbr, sizeof(MBR), 1, search);
        
        if(mbr.mbr_partition_1.part_name==this->name && mbr.mbr_partition_1.part_status=='1' ||  mbr.mbr_partition_2.part_name==this->name && mbr.mbr_partition_2.part_status=='1' || mbr.mbr_partition_3.part_name==this->name && mbr.mbr_partition_3.part_status=='1' || mbr.mbr_partition_4.part_name==this->name && mbr.mbr_partition_4.part_status=='1'){
            cout << "ERROR: Nombre repetido de particiones en este disco."<<endl;
            return;
        }else if(mbr.mbr_partition_1.part_type=='e' && mbr.mbr_partition_1.part_status=='1' || mbr.mbr_partition_2.part_type=='e' && mbr.mbr_partition_2.part_status=='1' || mbr.mbr_partition_3.part_type=='e' && mbr.mbr_partition_3.part_status=='1' || mbr.mbr_partition_4.part_type=='e' && mbr.mbr_partition_4.part_status=='1'){
            partition extendida = (mbr.mbr_partition_1.part_type=='e')?mbr.mbr_partition_1:(mbr.mbr_partition_2.part_type=='e')?mbr.mbr_partition_2:(mbr.mbr_partition_3.part_type=='e')?mbr.mbr_partition_3:mbr.mbr_partition_4;
            EBR ebr;
            fseek(search, extendida.part_start, SEEK_SET);
            fread(&ebr, sizeof(EBR), 1, search);
            int i =1;
            while(true){
                if(this->name==toString(ebr.part_name)){
                    //logic partition found, delete
                    cout << "ERROR: Nombre repetido de particiones lógicas en este disco."<<endl;
                    return;
                }
                if(ebr.part_next==-1){
                    break;
                }
                fseek(search, ebr.part_next, SEEK_SET);
                fread(&ebr, sizeof(EBR), 1, search);
                i++;
            }
        } 

        int freeSpace =  mbr.mbr_tamanio-sizeof(MBR)-mbr.mbr_partition_1.part_size-mbr.mbr_partition_2.part_size-mbr.mbr_partition_3.part_size-mbr.mbr_partition_4.part_size;

        if(this->type=="p" || this->type=="e"){
            if(this->type=="e"){
                if(mbr.mbr_partition_1.part_type=='e' && mbr.mbr_partition_1.part_status=='1' || mbr.mbr_partition_2.part_type=='e' && mbr.mbr_partition_2.part_status=='1' || mbr.mbr_partition_3.part_type=='e' && mbr.mbr_partition_3.part_status=='1' || mbr.mbr_partition_4.part_type=='e' && mbr.mbr_partition_4.part_status=='1'){
                    cout << "ERROR: Ya existe una partición extendida en este disco.";
                    return;
                }
            }
            if(mbr.mbr_partition_1.part_status=='0' || mbr.mbr_partition_2.part_status=='0' || mbr.mbr_partition_3.part_status=='0' || mbr.mbr_partition_4.part_status=='0'){
                int option = choosePartition(mbr);
                if(option==-1) return;
                partition * bestOption = (option==1)?&mbr.mbr_partition_1: (option==2)?&mbr.mbr_partition_2:(option==3)?&mbr.mbr_partition_3:&mbr.mbr_partition_4;
                if(bestOption->part_size==0 && (this->size>freeSpace)){
                    cout<< "ERROR: No hay suficiente espacio para crear la particion, solo hay "+to_string(freeSpace)+" bytes."<<endl; ;
                    return;
                }
                if(bestOption->part_size==0){
                    int start = sizeof(MBR)+mbr.mbr_partition_1.part_size+mbr.mbr_partition_2.part_size+mbr.mbr_partition_3.part_size+mbr.mbr_partition_4.part_size;
                    bestOption->part_start=start;
                }
                bestOption->part_fit=this->f.c_str()[0]; 
                strcpy(bestOption->part_name,this->name.c_str());
                bestOption->part_size=this->size;
                bestOption->part_type=this->type.c_str()[0];
                bestOption->part_status='1';
                if(this->type=="e"){
                    EBR ebr;
                    ebr.part_start=bestOption->part_start+sizeof(EBR);
                    fseek(search, bestOption->part_start, SEEK_SET);
                    fwrite(&ebr, sizeof(EBR), 1, search);
                    fflush(search);
                    rewind(search);
                }
            }else{
                cout << "ERROR:No se ha creado la partición en el disco indicado ya que ya hay 4 particiones en existencia."<<endl;
                return;
            }
        }
        else{
            if(mbr.mbr_partition_1.part_type=='e' && mbr.mbr_partition_1.part_status=='1' || mbr.mbr_partition_2.part_type!='e' && mbr.mbr_partition_2.part_status=='1' || mbr.mbr_partition_3.part_type!='e' && mbr.mbr_partition_3.part_status=='1' || mbr.mbr_partition_4.part_type!='e' && mbr.mbr_partition_4.part_status=='1'){
                partition extendida = (mbr.mbr_partition_1.part_type=='e')?mbr.mbr_partition_1:(mbr.mbr_partition_2.part_type=='e')?mbr.mbr_partition_2:(mbr.mbr_partition_3.part_type=='e')?mbr.mbr_partition_3:mbr.mbr_partition_4;
                EBR ebr, bestOption;
                fseek(search, extendida.part_start, SEEK_SET);
                fread(&ebr, sizeof(EBR), 1, search);
                cout << to_string(ebr.part_start)<<endl;
                bestOption=ebr;
                int lastStart;
                while(lastStart<ebr.part_next){
                    lastStart=ebr.part_next;
                    cout << "primer while"<<endl;
                    if(ebr.part_status=='0'){
                        cout << "ebr in " + to_string(ebr.part_start)+" is ok"<<endl;
                        if(extendida.part_type=='b'){
                            if(bestOption.part_size>ebr.part_size){
                                bestOption=ebr;
                            }
                        }else if(extendida.part_type=='w'){
                            if(bestOption.part_size<ebr.part_size){
                                bestOption=ebr;
                            }
                        }else{
                            if(bestOption.part_size<=ebr.part_size){
                                bestOption=ebr;    
                            }
                        }  
                    }
                    cout << "ebr next " + to_string(ebr.part_next)<<endl;
                    fseek(search, ebr.part_next, SEEK_SET);
                    fread(&ebr, sizeof(EBR), 1, search);
                }
                if(bestOption.part_start==extendida.part_start+sizeof(EBR) && bestOption.part_status=='0'){
                    cout << "if"<<endl;
                    //es el primer ebr de la extendida
                    bestOption.part_fit=this->f.c_str()[0];
                    bestOption.part_size=this->size;
                    bestOption.part_status='1';
                    bestOption.part_next=-1;
                    strcpy(bestOption.part_name,this->name.c_str());
                    fseek(search,bestOption.part_start-sizeof(EBR), SEEK_SET);
                    fwrite(&bestOption, sizeof(EBR), 1, search);
                }else if(bestOption.part_status=='1'/* && bestOption.part_size<this->size*/){
                    cout << "else if"<<endl;
                    //no consiguio un fit
                    EBR lastEBR;
                    fseek(search, extendida.part_start, SEEK_SET);
                    fread(&lastEBR, sizeof(EBR), 1, search);
                    int lastStart=-2;
                    while(lastStart<lastEBR.part_next){
                        lastStart=lastEBR.part_next;
                        if(lastEBR.part_next==-1){
                            break;
                        }
                        fseek(search, lastEBR.part_next, SEEK_SET);
                        fread(&lastEBR, sizeof(EBR), 1, search);
                    }
                    EBR nuevoEBR;
                    nuevoEBR.part_start=lastEBR.part_start+lastEBR.part_size;//incluye el espacio del ebr del nuevo
                    nuevoEBR.part_fit=this->f.c_str()[0]; 
                    strcpy(nuevoEBR.part_name,this->name.c_str());
                    nuevoEBR.part_size=this->size;
                    nuevoEBR.part_status='1';
                    nuevoEBR.part_next=-1;

                    lastEBR.part_next=nuevoEBR.part_start-sizeof(EBR);
                    fseek(search,lastEBR.part_start-sizeof(EBR), SEEK_SET);
                    fwrite(&lastEBR, sizeof(EBR), 1, search);
                    fflush(search);
                    fseek(search,nuevoEBR.part_start-sizeof(EBR), SEEK_SET);
                    fwrite(&nuevoEBR, sizeof(EBR), 1, search);
                    fflush(search);
                }else{
                    cout << "else"<<endl;
                    bestOption.part_fit=this->f.c_str()[0]; 
                    strcpy(bestOption.part_name,this->name.c_str());
                    bestOption.part_status='1';
                    fseek(search,bestOption.part_start-sizeof(EBR), SEEK_SET);
                    fwrite(&bestOption, sizeof(EBR), 1, search);
                }
                fflush(search);
            }
        }
        fclose(search);
        FILE *f = fopen(this->path.c_str(), "rb+");
        fwrite(&mbr, sizeof(MBR), 1, f);
        fflush(f);
        fclose(f);
        
        cout <<"La partición ha sido creada exitosamente."<<endl;
    }
}
int _FDISK::choosePartition(MBR& mbr){
    int bestOption=-1;//indicar que el objeto nunca ha sido asignado
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    opciones[2].part_size=this->size;
    opciones[3].part_size=this->size+100;
    for(int i =0;i<4;i++){
        //cout << "probando la particion " + to_string(i)<<endl;
        if(opciones[i].part_status=='0'){
            if(opciones[i].part_size==0 || opciones[i].part_size>=this->size){//es una nueva o es una con suficiente espacio
                if(mbr.disk_fit=='B'){
                    if(bestOption==-1){
                        bestOption=i;
                        //cout << "best fit is  " + to_string(i)<<endl;
                    }else{
                        if(opciones[bestOption].part_size>opciones[i].part_size){
                            bestOption=i;
                            //cout << "best fit changed to " + to_string(i)<<endl;
                        }
                    }
                }else if(mbr.disk_fit=='W'){
                    if(bestOption==-1){
                        bestOption=i;
                        //cout << "worst fit is  " + to_string(i)<<endl;
                    }else{
                        if(opciones[bestOption].part_size<opciones[i].part_size){
                            bestOption=i;
                            //cout << "worst fit changed to " + to_string(i)<<endl;
                        }
                    }
                }else{//FIRST FIT
                    bestOption=i;
                    break;
                    //cout << "first fit is  " + to_string(i)<<endl;
                }
            }
        }
    }
    if(bestOption==-1){
        cout << "No se a podido crear la partición, ninguna tiene suficiente espacio."<<endl;
        bestOption=-2;
    }
    return bestOption+1; 
}
int _FDISK::createLogicPartition(partition& particion){
    FILE * logic = fopen(this->path.c_str(), "rb+");
    EBR ebr, bestOption;
    cout << "1st ebr will seek in "+to_string(particion.part_start)<<endl;
    fseek(logic, particion.part_start, SEEK_SET);
    fread(&ebr, sizeof(EBR), 1, logic);
    while(true){
        if(ebr.part_status=='0'){
            if(ebr.part_size==0 || ebr.part_size>=this->size){//es una nueva o es una con suficiente espacio
                if(particion.part_fit=='B'){
                    if(bestOption.part_start==-1){
                        bestOption=ebr;
                    }else{
                        if(bestOption.part_size>ebr.part_size){
                            bestOption=ebr;
                        }
                    }
                }else if(particion.part_fit=='W'){
                    if(bestOption.part_start==-1){
                        bestOption=ebr;
                        //cout << "worst fit is  " + to_string(i)<<endl;
                    }else{
                        if(bestOption.part_size<ebr.part_size){
                            bestOption=ebr;
                            //cout << "worst fit changed to " + to_string(i)<<endl;
                        }
                    }
                }else{//FIRST FIT
                    bestOption=ebr;
                    break;
                    //cout << "first fit is  " + to_string(i)<<endl;
                }
            }
        }
        if(ebr.part_next==-1)break;
        fseek(logic, ebr.part_next, SEEK_SET);
        fread(&ebr, sizeof(EBR), 1, logic);
    }
    return bestOption.part_start;
}
string _FDISK::toLowerCase(string cadena){
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
string _FDISK::toString(char * name){
    string str;
    for(int i=0;i < 16;i++){
        if(name[i]==int(NULL)) break;
        str=str+name[i];
    }
    return str;
}
void _FDISK::deletePartition(){
    if(this->delete_!="fast" && this->delete_!="full"){
        cout<<"ERROR:el parametro delete no acepta el valor "<<this->delete_<<endl; 
        return;
    }
    FILE *search =  fopen(this->path.c_str(), "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    for(int i =0;i<4;i++){
        if(opciones[i].part_status=='1'){
            if(this->name==toString(opciones[i].part_name)){
                cout << "Se borrará la partición "+this->name+" del siguiente path:\n"<<this->path<<"\n ¿Estás seguro de eliminar el disco? S/n"<<endl;
                string answer;
                getline(cin, answer);
                if(toLowerCase(answer)=="s"){
                    if(this->delete_=="fast"){
                        (opciones[i].part_start==mbr.mbr_partition_1.part_start)?mbr.mbr_partition_1.part_status='0':(opciones[i].part_start==mbr.mbr_partition_2.part_start)?mbr.mbr_partition_2.part_status='0':(opciones[i].part_start==mbr.mbr_partition_3.part_start)?mbr.mbr_partition_3.part_status='0':mbr.mbr_partition_4.part_status='0';
                        //opciones[i].part_status='0';
                        fseek(search, 0, SEEK_SET);
                        fwrite(&mbr, sizeof(MBR), 1, search);
                        fflush(search);
                    }else{
                        (opciones[i].part_start==mbr.mbr_partition_1.part_start)?mbr.mbr_partition_1.part_status='0':(opciones[i].part_start==mbr.mbr_partition_2.part_start)?mbr.mbr_partition_2.part_status='0':(opciones[i].part_start==mbr.mbr_partition_3.part_start)?mbr.mbr_partition_3.part_status='0':mbr.mbr_partition_4.part_status='0';
                        //opciones[i].part_status='0';
                        fseek(search, 0, SEEK_SET);
                        fwrite(&mbr, sizeof(MBR), 1, search);
                        fflush(search);
                        cout << "Eliminando toda la partición, esto podría tomar un poco de tiempo."<<endl;
                        for(int i =opciones[i].part_start; i<opciones[i].part_start+opciones[i].part_size; i++){
                            fseek(search, i,SEEK_SET);
                            fwrite("\0", 1, 1, search);
                            fflush(search);
                        }
                    }
                    cout << "Se ha elimidado la partición "+toString(opciones[i].part_name)<<endl;
                }else{
                    cout << "No se ha eliminado la partición."<<endl;
                }
                return;
            } 
        }        
    }
    if(mbr.mbr_partition_1.part_type=='e' && mbr.mbr_partition_1.part_status=='1' || mbr.mbr_partition_2.part_type=='e' && mbr.mbr_partition_2.part_status=='1' || mbr.mbr_partition_3.part_type=='e' && mbr.mbr_partition_3.part_status=='1' || mbr.mbr_partition_4.part_type=='e' && mbr.mbr_partition_4.part_status=='1'){
        partition extendida = (mbr.mbr_partition_1.part_type=='e')?mbr.mbr_partition_1:(mbr.mbr_partition_2.part_type=='e')?mbr.mbr_partition_2:(mbr.mbr_partition_3.part_type=='e')?mbr.mbr_partition_3:mbr.mbr_partition_4;
        EBR ebr;
        fseek(search, extendida.part_start, SEEK_SET);
        fread(&ebr, sizeof(EBR), 1, search);
        int i =1;
        while(true){
            if(this->name==toString(ebr.part_name)){
                //logic partition found, delete
               cout << "Se borrará la partición "+this->name+" del siguiente path:\n"<<this->path<<"\n ¿Estás seguro de eliminar el disco? S/n"<<endl;
                string answer;
                getline(cin, answer);
                if(toLowerCase(answer)=="s"){
                    if(this->delete_=="fast"){
                        ebr.part_status='0';
                        fseek(search, ebr.part_start-sizeof(EBR),SEEK_SET);
                        fwrite(&ebr, sizeof(EBR), 1, search);
                        fflush(search);
                    }else{
                        ebr.part_status='0';
                        fseek(search, ebr.part_start-sizeof(EBR),SEEK_SET);
                        fwrite(&ebr, sizeof(EBR), 1, search);
                        fflush(search);
                        cout << "Eliminando toda la partición, esto podría tomar un poco de tiempo."<<endl;
                        for(int i =ebr.part_start; i<ebr.part_start+opciones[i].part_size-sizeof(EBR); i++){
                            fseek(search, i ,SEEK_SET);
                            fwrite("\0", 1, 1, search);
                            fflush(search);
                        }
                    }
                    cout << "Se ha elimidado la partición "+toString(ebr.part_name)<<endl;
                }else{
                    cout << "No se ha eliminado la partición."<<endl;
                }
                return;
            }
            if(ebr.part_next==-1){
                break;
            }
            fseek(search, ebr.part_next, SEEK_SET);
            fread(&ebr, sizeof(EBR), 1, search);
            i++;
        }
    } 
}