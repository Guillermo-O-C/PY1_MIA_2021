#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "mbr.h"


class _REP{
    private:
    string name;
    string path;
    string id;
    string ruta;
    public:
    _REP(){};
    void setPath(string path, bool isCadena);
    void setName(string name);
    void setId(string id);
    void setRuta(string ruta);
    void exe();
    void graphMbr();
    void graphDisk();
    void Print(string content, string name);
    string toLowerCase(string cadena);
};

void _REP::setPath(string path, bool isCadena){
    if(isCadena){
        this->path = path.substr(1, path.length()-2);
    }else{
        this->path = path;
    }
};
void _REP::setName(string name){
    this->name=toLowerCase(name);
};
void _REP::setId(string id){
    this->id=id;
};
void _REP::setRuta(string ruta){
    this->ruta=ruta;
};
void _REP::exe(){
    if(this->name=="mbr"){
        graphMbr();
    }else if(this->name=="disk"){
        graphDisk();
    }
};

void _REP::graphMbr(){
    FILE *search =  fopen("/home/mis discos/Disco3.dk", "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    fclose(search);
    string diskName = "";
    string graph = "digraph G {\nlabel = <<table><tr><td colspan=\"2\">MBR "+diskName+"</td></tr>";
    graph=graph+"<tr><td>mbr_tamaño:</td><td>"+to_string(mbr.mbr_tamanio);
    string fecha = mbr.mbr_fecha_creacion;
    graph=graph+"</td></tr><tr><td>mbr_fecha_creacion:</td><td>"+fecha.substr(0,  fecha.length()-2);
    graph=graph+"</td></tr><tr><td>mbr_disk_signture:</td><td>"+to_string(mbr.mbr_disk_signature);
    graph=graph+"</td></tr><tr><td>Disk_fit:</td><td>"+mbr.disk_fit;
    graph=graph+"</td></tr><tr><td>part_status_1:</td><td>"+mbr.mbr_partition_1.part_status;
    graph=graph+"</td></tr><tr><td>part_type_1:</td><td>"+mbr.mbr_partition_1.part_type;
    graph=graph+"</td></tr><tr><td>part_fit_1:</td><td>"+mbr.mbr_partition_1.part_fit;
    graph=graph+"</td></tr><tr><td>part__stax_1:</td><td>";
    graph=graph+"</td></tr><tr><td>part_size_1:</td><td>"+to_string(mbr.mbr_partition_1.part_size);
    graph=graph+"</td></tr><tr><td>part_name_1:</td><td>"+mbr.mbr_partition_1.part_name;
    graph=graph+"</td></tr></table>>;\n}";
    Print(graph, "MBR");
}

void _REP::graphDisk(){
    FILE *search =  fopen("/home/mis discos/Disco3.dk", "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    fclose(search);
    string extended, graph = "digraph G {\nlabel = <<table><tr><td rowspan=\"2\">MBR</td>";

    //calcular los porcantajes de disco de cada particion
    
    int size1, size2, size3, size4;
    if(mbr.mbr_partition_1.part_type=='E'){
        graph=graph+"<td>Extendida</td>";
        extended="<tr><td";

        //recolectar los datos de la extendida 

        extended=extended+"</td></tr>";
    }else if(mbr.mbr_partition_1.part_size==0){
        graph=graph+"<td rowspan=\"2\">Libre "+to_string(size1)+"% del disco</td>";
    }else{
        graph=graph+"<td rowspan=\"2\">Principal</td>";
    }
    if(mbr.mbr_partition_2.part_type=='E'){
        graph=graph+"<td>Extendida</td>";
        extended="<tr><td";

        //recolectar los datos de la extendida 

        extended=extended+"</td></tr>";
    }else if(mbr.mbr_partition_2.part_size==0){
        graph=graph+"<td rowspan=\"2\">Libre \n"+to_string(size2)+"% del disco</td>";
    }else{
        graph=graph+"<td rowspan=\"2\">Principal</td>";
    }
    if(mbr.mbr_partition_3.part_type=='E'){
        graph=graph+"<td>Extendida</td>";
        extended="<tr><td";

        //recolectar los datos de la extendida 

        extended=extended+"</td></tr>";
    }else if(mbr.mbr_partition_3.part_size==0){
        graph=graph+"<td rowspan=\"2\">Libre \n"+to_string(size3)+"% del disco</td>";
    }else{
        graph=graph+"<td rowspan=\"2\">Principal</td>";
    }
    if(mbr.mbr_partition_4.part_type=='E'){
        graph=graph+"<td>Extendida</td>";
        extended="<tr><td";

        //recolectar los datos de la extendida 

        extended=extended+"</td></tr>";
    }else if(mbr.mbr_partition_4.part_size==0){
        graph=graph+"<td rowspan=\"2\">Libre \n"+to_string(size4)+"% del disco</td>";
    }else{
        graph=graph+"<td rowspan=\"2\">Principal</td>";
    }
    graph=graph+extended+"</tr></table>>;}";
    Print(graph, "DISK");
}

void _REP::Print(string content, string name){
    FILE *searchFile =  fopen((this->path.substr(0, this->path.length()-4)+".txt").c_str(), "wb+");
    if(searchFile==NULL){
        string command = "mkdir -p \""+this->path+"\"";
        system(command.c_str()); 
        command = "rmdir \'"+this->path+"\'";        
        system(command.c_str());
    }

    ofstream graphFile;
    graphFile.open(this->path.substr(0, this->path.length()-4)+".txt");
    graphFile << content;
    graphFile.close();
    std::string filePath;
    if(toLowerCase(this->path.substr(this->path.length()-3, this->path.length()))=="png"){
        filePath="dot -Tpng \""+this->path.substr(0, this->path.length()-3)+"txt\" -o \""+this->path.substr(0, this->path.length()-3)+"png\"";
    }else if(toLowerCase(this->path.substr(this->path.length()-3, this->path.length()))=="jpg"){
        filePath="dot -Tjpg \""+this->path.substr(0, this->path.length()-3)+"txt\" -o \""+this->path.substr(0, this->path.length()-3)+"jpg\"";
    }else if(toLowerCase(this->path.substr(this->path.length()-3, this->path.length()))=="pdf"){
        filePath="dot -Tpdf \""+this->path.substr(0, this->path.length()-3)+"txt\" -o \""+this->path.substr(0, this->path.length()-3)+"pdf\"";
    }
    system(filePath.c_str());
    cout <<"Reporte Generado con éxito."<<endl;
}

string _REP::toLowerCase(string cadena){
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