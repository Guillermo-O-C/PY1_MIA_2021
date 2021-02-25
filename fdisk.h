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
    void setName(string name);
    void setAdd(int add);
    void exe();
    void setPartition(MBR mbr, int NoParticion, int start);
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
void _FDISK::setName(string name){
    this->name=toLowerCase(name);
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

        if(this->type=="p"){
            if(mbr.mbr_partition_1.part_name==""){
                setPartition(mbr, 1, start);
            }else if(mbr.mbr_partition_2part_name!=""){
                setPartition(mbr, 2, start);
            }else if(mbr.mbr_partition_3.part_name!=""){
                setPartition(mbr, 3, start);
            }else if(mbr.mbr_partition_4.part_name!=""){
                setPartition(mbr, 4, start);
            }else{
                cout << "ERROR:No se ha creado la partición en el disco indicado ya que ya hay 4 particiones en existencia."
            }
        }
        else if(this->type=="e"){
            if(mbr.mbr_partition_1.part_type!="e" && mbr.mbr_partition_2.part_type!="e" && mbr.mbr_partition_3.part_type!="e" && mbr.mbr_partition_4.part_type!="e"){
                cout << "ERROR: Ya existe una partición extendida en este disco.";
            }else if(mbr.mbr_partition_1.part_name==""){
                setPartition(mbr, 1, start);
            }else if(mbr.mbr_partition_2part_name!=""){
                setPartition(mbr, 2, start);
            }else if(mbr.mbr_partition_3.part_name!=""){
                setPartition(mbr, 3, start);
            }else if(mbr.mbr_partition_4.part_name!=""){
                setPartition(mbr, 4, start);
            }else{
                cout << "ERROR:No se ha creado la partición en el disco indicado ya que ya hay 4 particiones en existencia."
            }
        }
        else{
            if(mbr.mbr_partition_1.part_type!="e" && mbr.mbr_partition_2.part_type!="e" && mbr.mbr_partition_3.part_type!="e" && mbr.mbr_partition_4.part_type!="e"){
                cout << "ERROR: No se puede crear la partición lógica porque no existe una partición extendida en este disco.";
            }
        }
        
        fflush(search);
        fclose(search);
    }
}

void _FDISK::setPartition(MBR mbr, int NoParticion, int start){
    switch(NoParticion){
        case 1:
            mbr.mbr_partition_1.part_fit=this->f;
            mbr.mbr_partition_1.part_name=this->name;
            mbr.mbr_partition_1.part_size=this->size;
            mbr.mbr_partition_1.part_start=start;
            mbr.mbr_partition_1.part_type=this->type;
            break;
        case 2:
            mbr.mbr_partition_2.part_fit=this->f;
            mbr.mbr_partition_2.part_name=this->name;
            mbr.mbr_partition_2.part_size=this->size;
            mbr.mbr_partition_2.part_start=start;
            mbr.mbr_partition_2.part_type=this->type;
            break;
        case 3:
            mbr.mbr_partition_3.part_fit=this->f;
            mbr.mbr_partition_3.part_name=this->name;
            mbr.mbr_partition_3.part_size=this->size;
            mbr.mbr_partition_31.part_start=start;
            mbr.mbr_partition_3.part_type=this->type;
            break;
        case 4:
            mbr.mbr_partition_4.part_fit=this->f;
            mbr.mbr_partition_4.part_name=this->name;
            mbr.mbr_partition_4.part_size=this->size;
            mbr.mbr_partition_4.part_start=start;
            mbr.mbr_partition_4.part_type=this->type;
            break;
    }
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