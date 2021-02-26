#include <iostream>
using namespace std;

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
    string toLowerCase(string cadena);
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
    if(this->delete_=="") this->delete_="fast";

    if(this->size<=0){
        cout<<"ERROR:no se puede crear un disco con el tamaño " << this->size <<endl;
    }else if(this->path==""){
        cout<<"ERROR:el parámetro PATH es obligatorio."<<endl;
    }else if(this->type!="p" && this->type!="e" && this->type!="l"){
        cout<<"ERROR:no existe la type "<<this->type<<endl;
    }else if(this->u!="b" && this->u!="k" && this->u!="m"){
        cout<<"ERROR:no existe la unidad de datos "<<this->u<<endl;
    }else if(this->f!="bf" && this->f!="ff" && this->f!="wf"){
        cout<<"ERROR:no existe el fit "<<this->f<<endl;
    }else if(this->delete_!="fast" && this->delete_!="full"){
        cout<<"ERROR:el parametro delete no acepta el valor "<<this->delete_<<endl; 
    }else if(this->name==""){
        cout<<"ERROR:el parámetro NAME es obligatorio."<<endl;
    }else{
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

        //calcular con el size, y el fit el byte de inicio.
        int freeSpace =  mbr.mbr_tamanio-sizeof(MBR)-mbr.mbr_partition_1.part_size-mbr.mbr_partition_2.part_size-mbr.mbr_partition_3.part_size-mbr.mbr_partition_4.part_size;

        if(this->type=="p"){
            if(mbr.mbr_partition_1.part_status=='0' || mbr.mbr_partition_2.part_status=='0' || mbr.mbr_partition_3.part_status=='0' || mbr.mbr_partition_4.part_status=='0'){
                int option = choosePartition(mbr);
                partition * bestOption = (option==1)?&mbr.mbr_partition_1: (option==2)?&mbr.mbr_partition_2:(option==3)?&mbr.mbr_partition_3:&mbr.mbr_partition_4;
                if(bestOption->part_size==-1) return;
                if(bestOption->part_size==0 && (this->size>freeSpace)){
                    cout<< "ERROR: No hay suficiente espacio para crear la particion, solo hay "+to_string(freeSpace)+" bytes."<<endl; ;
                    return;
                }
                if(bestOption->part_size==0){
                    int start =  sizeof(MBR)+mbr.mbr_partition_1.part_size+mbr.mbr_partition_2.part_size+mbr.mbr_partition_3.part_size+mbr.mbr_partition_4.part_size;
                    bestOption->part_start=start;
                    cout << "the start byte will be "+to_string(start)<<endl;
                }
                bestOption->part_fit=this->f.c_str()[0]; 
                strcpy(bestOption->part_name,this->name.c_str());
                bestOption->part_size=this->size;
                bestOption->part_type=this->type.c_str()[0];
                bestOption->part_status='1';
            }else{
                cout << "ERROR:No se ha creado la partición en el disco indicado ya que ya hay 4 particiones en existencia.";
            }
        }
        else if(this->type=="e"){
            if(mbr.mbr_partition_1.part_type=='e' && mbr.mbr_partition_1.part_status=='1' || mbr.mbr_partition_2.part_type!='e' && mbr.mbr_partition_2.part_status=='1' || mbr.mbr_partition_3.part_type!='e' && mbr.mbr_partition_3.part_status=='1' || mbr.mbr_partition_4.part_type!='e' && mbr.mbr_partition_4.part_status=='1'){
                cout << "ERROR: Ya existe una partición extendida en este disco.";
            }else if(mbr.mbr_partition_1.part_status=='0' || mbr.mbr_partition_2.part_status=='0' || mbr.mbr_partition_3.part_status=='0' || mbr.mbr_partition_4.part_status=='0'){
                int option = choosePartition(mbr);
                partition * bestOption = (option==1)?&mbr.mbr_partition_1: (option==2)?&mbr.mbr_partition_2:(option==3)?&mbr.mbr_partition_3:&mbr.mbr_partition_4;
                if(bestOption->part_size==-1) return;
                if(bestOption->part_size==0 && (this->size>freeSpace)){
                    cout<< "ERROR: No hay suficiente espacio para crear la particion, solo hay "+to_string(freeSpace)+" bytes."<<endl; ;
                    return;
                }
                if(bestOption->part_size==0){
                    int start =  sizeof(MBR)+mbr.mbr_partition_1.part_size+mbr.mbr_partition_2.part_size+mbr.mbr_partition_3.part_size+mbr.mbr_partition_4.part_size;
                    bestOption->part_start=start;
                }
                bestOption->part_fit=this->f.c_str()[0]; 
                strcpy(bestOption->part_name,this->name.c_str());
                bestOption->part_size=this->size;
                bestOption->part_type=this->type.c_str()[0];
                bestOption->part_status='1';
            }else{
                cout << "ERROR:No se ha creado la partición en el disco indicado ya que ya hay 4 particiones en existencia.";
            }
        }
        else{
            if(mbr.mbr_partition_1.part_type=='e' && mbr.mbr_partition_1.part_status=='1' || mbr.mbr_partition_2.part_type!='e' && mbr.mbr_partition_2.part_status=='1' || mbr.mbr_partition_3.part_type!='e' && mbr.mbr_partition_3.part_status=='1' || mbr.mbr_partition_4.part_type!='e' && mbr.mbr_partition_4.part_status=='1'){
                cout << "ERROR: No se puede crear la partición lógica porque no existe una partición extendida en este disco.";
            }
        }
        fclose(search);
        FILE *f = fopen(this->path.c_str(), "wb+");
        fwrite(&mbr, sizeof(MBR), 1, f);
        fflush(f);
        fclose(f);
        cout <<"La partición ha sido creada exitosamente."<<endl;
    }
}
int _FDISK::choosePartition(MBR& mbr){
    int bestOption=-1;//indicar que el objeto nunca ha sido asignado
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    for(int i =0;i<4;i++){
        cout << "probando la particion " + to_string(i)<<endl;
        if(opciones[i].part_status=='0'){
            if(opciones[i].part_size==0 || opciones[i].part_size>=this->size){//es una nueva o es una con suficiente espacio
                if(mbr.disk_fit=='B'){
                    if(bestOption==-1){
                        bestOption=i;
        cout << "best fit is  " + to_string(i)<<endl;
                    }else{
                        if(opciones[bestOption].part_size>opciones[i].part_size){
                            bestOption=i;
        cout << "best fit changed to " + to_string(i)<<endl;
                        }
                    }
                }else if(mbr.disk_fit=='W'){
                    if(opciones[bestOption].part_size==-1){
                        bestOption=i;
        cout << "best fit is  " + to_string(i)<<endl;
                    }else{
                        if(opciones[bestOption].part_size<opciones[i].part_size){
                            bestOption=i;
        cout << "best fit changed to " + to_string(i)<<endl;
                        }
                    }
                }else{//FIRST FIT
                    bestOption=i;
                    break;
        cout << "best fit is  " + to_string(i)<<endl;
                }
            }
        }
    }
    if(bestOption==-1){
        cout << "No se a podido crear la partición, ninguna tiene suficiente espacio."<<endl;
    }
    return bestOption+1; 
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