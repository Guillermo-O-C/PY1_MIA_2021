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
    string diskName = "";
    string graph = "digraph G {\n node [ shape=box fontname=Helvetica ] mbr [label = <<table><tr><td colspan=\"2\">MBR "+diskName+"</td></tr>";
    graph=graph+"<tr><td>mbr_tamaño:</td><td>"+to_string(mbr.mbr_tamanio);
    string fecha = mbr.mbr_fecha_creacion;
    graph=graph+"</td></tr><tr><td>mbr_fecha_creacion:</td><td>"+fecha.substr(0,  fecha.length()-2);
    graph=graph+"</td></tr><tr><td>mbr_disk_signture:</td><td>"+to_string(mbr.mbr_disk_signature);
    graph=graph+"</td></tr><tr><td>Disk_fit:</td><td>"+mbr.disk_fit;
    graph=graph+"</td></tr><tr><td>part_name_1:</td><td>"+mbr.mbr_partition_1.part_name;
    graph=graph+"</td></tr><tr><td>part_status_1:</td><td>"+mbr.mbr_partition_1.part_status;
    graph=graph+"</td></tr><tr><td>part_type_1:</td><td>"+mbr.mbr_partition_1.part_type;
    graph=graph+"</td></tr><tr><td>part_fit_1:</td><td>"+mbr.mbr_partition_1.part_fit;
    graph=graph+"</td></tr><tr><td>part__start_1:</td><td>"+to_string(mbr.mbr_partition_1.part_start);
    graph=graph+"</td></tr><tr><td>part_size_1:</td><td>"+to_string(mbr.mbr_partition_1.part_size);
    graph=graph+"</td></tr><tr><td>part_name_2:</td><td>"+mbr.mbr_partition_2.part_name;
    graph=graph+"</td></tr><tr><td>part_status_2:</td><td>"+mbr.mbr_partition_2.part_status;
    graph=graph+"</td></tr><tr><td>part_type_2:</td><td>"+mbr.mbr_partition_2.part_type;
    graph=graph+"</td></tr><tr><td>part_fit_2:</td><td>"+mbr.mbr_partition_2.part_fit;
    graph=graph+"</td></tr><tr><td>part__start_2:</td><td>"+to_string(mbr.mbr_partition_2.part_start);
    graph=graph+"</td></tr><tr><td>part_size_2:</td><td>"+to_string(mbr.mbr_partition_2.part_size);
    graph=graph+"</td></tr><tr><td>part_name_3:</td><td>"+mbr.mbr_partition_3.part_name;
    graph=graph+"</td></tr><tr><td>part_status_3:</td><td>"+mbr.mbr_partition_3.part_status;
    graph=graph+"</td></tr><tr><td>part_type_3:</td><td>"+mbr.mbr_partition_3.part_type;
    graph=graph+"</td></tr><tr><td>part_fit_3:</td><td>"+mbr.mbr_partition_3.part_fit;
    graph=graph+"</td></tr><tr><td>part__start_3:</td><td>"+to_string(mbr.mbr_partition_3.part_start);
    graph=graph+"</td></tr><tr><td>part_size_3:</td><td>"+to_string(mbr.mbr_partition_3.part_size);
    graph=graph+"</td></tr><tr><td>part_name_4:</td><td>"+mbr.mbr_partition_4.part_name;
    graph=graph+"</td></tr><tr><td>part_status_4:</td><td>"+mbr.mbr_partition_4.part_status;
    graph=graph+"</td></tr><tr><td>part_type_4:</td><td>"+mbr.mbr_partition_4.part_type;
    graph=graph+"</td></tr><tr><td>part_fit_4:</td><td>"+mbr.mbr_partition_4.part_fit;
    graph=graph+"</td></tr><tr><td>part__start_4:</td><td>"+to_string(mbr.mbr_partition_4.part_start);
    graph=graph+"</td></tr><tr><td>part_size_4:</td><td>"+to_string(mbr.mbr_partition_4.part_size);
    graph=graph+"</td></tr></table>>]";
    if(mbr.mbr_partition_1.part_type=='e' && mbr.mbr_partition_1.part_status=='1' || mbr.mbr_partition_2.part_type=='e' && mbr.mbr_partition_2.part_status=='1' || mbr.mbr_partition_3.part_type=='e' && mbr.mbr_partition_3.part_status=='1' || mbr.mbr_partition_4.part_type=='e' && mbr.mbr_partition_4.part_status=='1'){
        partition extendida = (mbr.mbr_partition_1.part_type=='e')?mbr.mbr_partition_1:(mbr.mbr_partition_2.part_type=='e')?mbr.mbr_partition_2:(mbr.mbr_partition_3.part_type=='e')?mbr.mbr_partition_3:mbr.mbr_partition_4;
        EBR ebr;
        fseek(search, extendida.part_start, SEEK_SET);
        fread(&ebr, sizeof(EBR), 1, search);
        int i =1;
        while(true){
            cout << "this next is at "+to_string(ebr.part_next)<<endl;
            graph=graph+"ebr"+to_string(i)+"[label=<<table>";
            graph=graph+"<tr><td colspan=\"2\">EBR_"+to_string(i)+"</td></tr>";
            graph=graph+"<tr><td>Nombre</td><td>Valor</td></tr>";
            graph=graph+"<tr><td>part_status_"+to_string(i)+"</td><td>"+ebr.part_status+"</td></tr>";
            graph=graph+"<tr><td>part_fit_"+to_string(i)+"</td><td>"+ebr.part_fit+"</td></tr>";
            graph=graph+"<tr><td>part_size_"+to_string(i)+"</td><td>"+to_string(ebr.part_size)+"</td></tr>";
            graph=graph+"<tr><td>part_start_"+to_string(i)+"</td><td>"+to_string(ebr.part_start)+"</td></tr>";
            graph=graph+"<tr><td>part_next_"+to_string(i)+"</td><td>"+to_string(ebr.part_next)+"</td></tr>";
            graph=graph+"<tr><td>part_name_"+to_string(i)+"</td><td>"+ebr.part_name+"</td></tr>";
            graph=graph+"</table>>]";
            if(ebr.part_next==-1){
                break;
            }
            fseek(search, ebr.part_next, SEEK_SET);
            fread(&ebr, sizeof(EBR), 1, search);
            i++;
        }
    }    
    Print(graph+"\n}", "MBR");
}

void _REP::graphDisk(){
    FILE *search =  fopen("/home/mis discos/Disco3.dk", "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    string extended="</tr><tr>", graph = "digraph G {\nlabel = <<table><tr><td rowspan=\"2\">MBR</td>";
    partition particiones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3, mbr.mbr_partition_4};

    //bubble sort
    for(int i =0;i<4;i++){
        for(int j=0;j<3;j++){
            if(particiones[j].part_start>particiones[j+1].part_start){
                partition temp = particiones[j];
                particiones[j] = particiones[j+1];
                particiones[j+1] = temp;
            }
        }
    }

    for(int i =0;i<4;i++){
        if(particiones[i].part_size==0) continue;
        int porcentaje = particiones[i].part_size*100;
        porcentaje=porcentaje/mbr.mbr_tamanio;
        if(particiones[i].part_status=='0'){
            graph=graph+"<td rowspan=\"2\">Libre <br/>"+to_string(porcentaje)+"%</td>";
        }else{
            if(particiones[i].part_type=='p'){
                graph=graph+"<td rowspan=\"2\">Primaria <br/>"+to_string(porcentaje)+"%</td>";
            }else{//extendida
                int colspan =1;//calcular el encabezado de la extendida
                EBR ebr;
                fseek(search, particiones[i].part_start, SEEK_SET);
                fread(&ebr, sizeof(EBR), 1, search);
                while(true){
                    colspan++;
                    if(ebr.part_status=='1'){                            
                        int porcentaje = ebr.part_size * 100;
                        porcentaje=porcentaje/mbr.mbr_tamanio;
                        colspan++;
                        extended = extended + "<td>EBR</td><td>Logica<br/>"+to_string(porcentaje)+"%</td>";
                    }else{
                        if(ebr.part_start==particiones[i].part_start+sizeof(EBR)){//en caso de que el primer EBR esté dehabilitado
                            int porcentaje = ebr.part_size*100;
                            porcentaje=porcentaje/mbr.mbr_tamanio;
                            colspan++;
                            extended = extended + "<td>EBR</td><td>Libre <br/>"+to_string(porcentaje)+"%</td>";
                        }
                        else{
                            int porcentaje = ebr.part_size*100;
                            porcentaje=porcentaje/mbr.mbr_tamanio;
                            extended = extended + "<td>Libre <br/>"+to_string(porcentaje)+"%</td>";
                        }
                    }
                    if(ebr.part_next==-1){
                        break;
                    }
                    fseek(search, ebr.part_next, SEEK_SET);
                    fread(&ebr, sizeof(EBR), 1, search);
                }
                if(ebr.part_start-sizeof(EBR)+ebr.part_size!=particiones[i].part_start-sizeof(MBR)+particiones[i].part_size){
                    int freeSpace = particiones[i].part_start-sizeof(MBR)+particiones[i].part_size-ebr.part_start-sizeof(EBR)+ebr.part_size;
                    int porcentaje = freeSpace * 100;
                    porcentaje=porcentaje/mbr.mbr_tamanio;
                    colspan++;
                    extended = extended + "<td>Libre <br/>"+to_string(porcentaje)+"%</td>";

                }
                graph=graph+"<td colspan=\""+to_string(colspan)+"\">Extendida</td>";
            }
        }
    }
    int freeSpace =  mbr.mbr_tamanio-sizeof(MBR)-mbr.mbr_partition_1.part_size-mbr.mbr_partition_2.part_size-mbr.mbr_partition_3.part_size-mbr.mbr_partition_4.part_size;
    if(freeSpace>0) graph=graph+"<td rowspan=\"2\">Libre <br/>"+to_string((freeSpace*100)/mbr.mbr_tamanio)+"%</td>";
    graph=(extended=="</tr><tr>")?graph+"</tr></table>>;}":graph+extended+"</tr></table>>;}";
    Print(graph, "DISK");
    fclose(search);
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