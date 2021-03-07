#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "mbr.h"
#include "mountStructs.h"
#include "partitionStructs.h"


class _REP{
    private:
    string name;
    string path;
    string id;
    string ruta;
    string diskPath;
    int partSpot;
    int diskSpot;
    public:
    _REP(){
        this->name="";
        this->path="";
        this->id="";
    };
    void setPath(string path, bool isCadena);
    void setName(string name);
    void setId(string id);
    void setRuta(string ruta);
    void exe();
    void graphMbr();
    void graphDisk();
    void Print(string content, string name);
    string toLowerCase(string cadena);
    void graphBM_Inodos();
    void graphBM_Blocks();
    void graphInodos();
    void graphBlocks();
    void graphTree();
    void graphSB();
    string toUpperCase(string cadena);
    string nameToString(char * name);
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
    this->id=toUpperCase(id);
    int diskSpot = (int)id[3]-65;
    int partSpot=id[2]-'0';//se le resta uno para obotener la posición en el array
    partSpot--;
    if(int(id[3])<65){//es una partición con un número de <9
        char temp[2]={ id[2], id[3]};
        partSpot=atoi(temp)-1;//restamos uno para obtener la posición del array
        diskSpot = (int)id[4]-65;
    }
    this->diskPath=discosMontados[diskSpot].path;
    this->diskSpot=diskSpot;
    this->partSpot=partSpot;
};
void _REP::setRuta(string ruta){
    this->ruta=ruta;
};
void _REP::exe(){
    if(this->id==""){
        cout << "ERROR: El parámetro ID es obligatorio."<<endl;
        return;
    }else if(this->name==""){
        cout << "ERROR: El parámetro name es obligatorio."<<endl;
        return;
    }else if(this->path==""){
        cout << "ERROR: El parámetro path es obligatorio."<<endl;
        return;
    }
    if(this->name=="mbr"){
        graphMbr();
    }else if(this->name=="disk"){
        graphDisk();
    }else if(this->name=="inode"){
        graphInodos();
    }else if(this->name=="block"){
        graphBlocks();
    }else if(this->name=="bm_inode"){
        graphBM_Inodos();
    }else if(this->name=="bm_block"){
        graphBM_Blocks();
    }else if(this->name=="tree"){
        graphTree();
    }else if(this->name=="sb"){
        graphSB();
    }else{
        cout <<"No se reconoce el name "<<this->name<<" como un reporte." <<endl;
        return;
    }
};

void _REP::graphMbr(){
    FILE *search =  fopen(this->diskPath.c_str(), "rb+");
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
    FILE *search =  fopen(this->diskPath.c_str(), "rb+");
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
                            //colspan++;
                            extended = extended + "<td>EBR</td>"/*<td>Libre <br/>"+to_string(porcentaje)+"%</td>"*/;
                        }/*se quita porque ya no se guardan los EBR deshabilitados
                        else{
                            int porcentaje = ebr.part_size*100;
                            porcentaje=porcentaje/mbr.mbr_tamanio;
                            extended = extended + "<td>Libre <br/>"+to_string(porcentaje)+"%</td>";
                        }*/
                    }
                    if(ebr.part_next==-1){
                        break;
                    }
                    int spaceBetween = ebr.part_next-(ebr.part_start+ebr.part_size);
                    if(ebr.part_start==particiones[i].part_start+sizeof(EBR) && ebr.part_status=='0'){//en caso de que el primer EBR esté dehabilitado
                        spaceBetween = ebr.part_next-(ebr.part_start-sizeof(EBR));
                    }
                    if(ebr.part_start>0){
                        int porcentaje = (spaceBetween)*100;
                        porcentaje=porcentaje/mbr.mbr_tamanio;
                        extended = extended + "<td>Libre <br/>"+to_string(porcentaje)+"%</td>";
                        colspan++;
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
        int freeSpace = particiones[i+1].part_start-(particiones[i].part_start+particiones[i].part_size);
        int porcentajeFree = freeSpace * 100;
        porcentajeFree=porcentajeFree/mbr.mbr_tamanio;
        if(freeSpace>0){
            graph=graph+"<td rowspan=\"2\">Libre <br/>"+to_string(porcentajeFree)+"%</td>";
        }
    }
    int freeSpace =  mbr.mbr_tamanio-sizeof(MBR)-mbr.mbr_partition_1.part_size-mbr.mbr_partition_2.part_size-mbr.mbr_partition_3.part_size-mbr.mbr_partition_4.part_size;
    if(freeSpace>0) graph=graph+"<td rowspan=\"2\">Libre <br/>"+to_string((freeSpace*100)/mbr.mbr_tamanio)+"%</td>";
    graph=(extended=="</tr><tr>")?graph+"</tr></table>>;}":graph+extended+"</tr></table>>;}";
    Print(graph, "DISK");
    fclose(search);
}

void _REP::graphBM_Inodos(){
    FILE *search =  fopen(this->diskPath.c_str(), "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    string name = discosMontados[this->diskSpot].particiones[this->partSpot].name; 
    for(int i =0;i<4;i++){
        if(opciones[i].part_status=='1' && opciones[i].part_type=='p'){
            if(name==nameToString(opciones[i].part_name)){
                string bitmap="";
                SB superbloque;
                fseek(search, opciones[i].part_start, SEEK_SET);
                fread(&superbloque, sizeof(SB), 1, search);
                int row=0;
                cout<< "Generando reporte, por favor espera..."<<endl;
                for(int e = superbloque.s_bm_inode_start;e<superbloque.s_bm_inode_start+superbloque.s_inodes_count;e++){
                    fseek(search, e, SEEK_SET);
                    char byte;
                    fread(&byte, 1, 1, search);
                    if(byte=='\0')cout<<to_string(e)<<" es null"<<endl;
                    bitmap=bitmap+byte;
                    row++;
                    if(row==20){
                        bitmap=bitmap+"\n";
                        row=0;
                    }
                }
                ofstream graphFile;
                graphFile.open(this->path.substr(0, this->path.length()-4)+".txt");
                graphFile << bitmap;
                graphFile.close();
                cout << "Reporte generado exitosamente."<<endl;
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

void _REP::graphBM_Blocks(){
    FILE *search =  fopen(this->diskPath.c_str(), "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    string name = discosMontados[diskSpot].particiones[partSpot].name; 
    for(int i =0;i<4;i++){
        if(opciones[i].part_status=='1' && opciones[i].part_type=='p'){
            if(name==nameToString(opciones[i].part_name)){
                string bitmap="";
                SB superbloque;
                fseek(search, opciones[i].part_start, SEEK_SET);
                fread(&superbloque, sizeof(SB), 1, search);
                int row=0;
                cout<< "Generando reporte, por favor espera..."<<endl;
                for(int e = superbloque.s_bm_block_start;e<superbloque.s_bm_block_start+superbloque.s_blocks_count;e++){
                    fseek(search, e, SEEK_SET);
                    char byte;
                    fread(&byte, 1, 1, search);
                    if(byte=='\0')cout<<to_string(e)<<" es null"<<endl;
                    bitmap=bitmap+byte;
                    row++;
                    if(row==20){
                        bitmap=bitmap+"\n";
                        row=0;
                    }
                }
                ofstream graphFile;
                graphFile.open(this->path.substr(0, this->path.length()-4)+".txt");
                graphFile << bitmap;
                graphFile.close();
                cout << "Reporte generado exitosamente."<<endl;
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

void _REP::graphInodos(){
    FILE *search =  fopen(this->diskPath.c_str(), "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    string name = discosMontados[diskSpot].particiones[partSpot].name; 
    for(int i =0;i<4;i++){
        if(opciones[i].part_status=='1' && opciones[i].part_type=='p'){
            if(name==nameToString(opciones[i].part_name)){
                string graph= "digraph G {\nnode[ shape=box fontname=Helvetica ] rankdir = LR;";
                string punteros;
                SB superbloque;
                fseek(search, opciones[i].part_start, SEEK_SET);
                fread(&superbloque, sizeof(SB), 1, search);
                char arrow = '0';
                cout<< "Generando reporte, por favor espera..."<<endl;
                for(int e = superbloque.s_bm_inode_start;e<superbloque.s_bm_inode_start+superbloque.s_inodes_count;e++){
                    fseek(search, e, SEEK_SET);
                    char byte;
                    fread(&byte, 1, 1, search);
                    if(byte=='1'){
                        if(arrow=='1') punteros=punteros+"->";
                        inode inodo;
                        fseek(search, superbloque.s_inode_start+sizeof(inode)*(e-superbloque.s_bm_inode_start), SEEK_SET);
                        fread(&inodo, sizeof(inode), 1, search);
                        punteros=punteros+"inode"+to_string(e-superbloque.s_bm_inode_start);
                        graph=graph+"inode"+to_string(e-superbloque.s_bm_inode_start)+" [label=<<table border=\"1\">";
                        graph=graph+"<tr><td colspan=\"2\">Inodo_"+to_string(e-superbloque.s_bm_inode_start)+"</td></tr>";
                        graph=graph+"<tr><td>i_uid</td><td>"+to_string(inodo.i_uid)+"</td></tr>";
                        graph=graph+"<tr><td>i_gid</td><td>"+to_string(inodo.i_gid)+"</td></tr>";
                        graph=graph+"<tr><td>i_size</td><td>"+to_string(inodo.i_size)+"</td></tr>";
                        graph=graph+"<tr><td>i_atime</td><td>"+nameToString(inodo.i_atime)+"</td></tr>";
                        graph=graph+"<tr><td>i_ctime</td><td>"+nameToString(inodo.i_ctime)+"</td></tr>";
                        graph=graph+"<tr><td>i_mtime</td><td>"+nameToString(inodo.i_mtime)+"</td></tr>";
                        for(int o=0;o<12;o++){
                            graph=graph+"<tr><td>APD"+to_string(o)+"</td><td>"+to_string(inodo.i_block[o])+"</td></tr>";
                        }
                        graph=graph+"<tr><td>API1</td><td>"+to_string(inodo.i_block[12])+"</td></tr>";
                        graph=graph+"<tr><td>API2</td><td>"+to_string(inodo.i_block[13])+"</td></tr>";
                        graph=graph+"<tr><td>API3</td><td>"+to_string(inodo.i_block[14])+"</td></tr>";
                        graph=graph+"<tr><td>i_type</td><td>"+to_string(inodo.i_type)+"</td></tr>";
                        graph=graph+"<tr><td>i_perm</td><td>"+to_string(inodo.i_perm)+"</td></tr>";
                        graph=graph+"</table>>];\n";
                        arrow='1';
                    }
                }
                Print(graph+punteros+";\n}", "Inodos");
                cout << "Reporte generado exitosamente."<<endl;
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

void _REP::graphBlocks(){
    FILE *search =  fopen(this->diskPath.c_str(), "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    string name = discosMontados[diskSpot].particiones[partSpot].name; 
    for(int i =0;i<4;i++){
        if(opciones[i].part_status=='1' && opciones[i].part_type=='p'){
            if(name==nameToString(opciones[i].part_name)){

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

void _REP::graphTree(){
    FILE *search =  fopen(this->diskPath.c_str(), "rb+");
    MBR mbr;
    fread(&mbr, sizeof(MBR), 1, search);
    partition opciones[4] = {mbr.mbr_partition_1, mbr.mbr_partition_2, mbr.mbr_partition_3,mbr.mbr_partition_4};
    string name = discosMontados[diskSpot].particiones[partSpot].name; 
    for(int i =0;i<4;i++){
        if(opciones[i].part_status=='1' && opciones[i].part_type=='p'){
            if(name==nameToString(opciones[i].part_name)){

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

void _REP::graphSB(){
    FILE *search =  fopen(this->diskPath.c_str(), "rb+");
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
                string graph = "digraph G {\n node [ shape=box fontname=Helvetica ] sb [label = <<table><tr><td colspan=\"2\">SuperBloque "+this->id+"</td></tr>";
                graph=graph+"<tr><td>s_filesystem_type</td><td>"+to_string(superbloque.s_filesystem_type)+"</td></tr>";
                graph=graph+"<tr><td>s_inodes_count</td><td>"+to_string(superbloque.s_inodes_count)+"</td></tr>";
                graph=graph+"<tr><td>s_blocks_count</td><td>"+to_string(superbloque.s_blocks_count)+"</td></tr>";
                graph=graph+"<tr><td>s_free_blocks_count</td><td>"+to_string(superbloque.s_free_blocks_count)+"</td></tr>";
                graph=graph+"<tr><td>s_free_inodes_count</td><td>"+to_string(superbloque.s_free_inodes_count)+"</td></tr>";
                graph=graph+"<tr><td>s_mtime</td><td>";
                graph=graph+nameToString(superbloque.s_mtime);
                graph=graph+"</td></tr>";
                graph=graph+"<tr><td>s_umtime</td><td>";
                graph=graph+nameToString(superbloque.s_umtime);
                graph=graph+"</td></tr>";
                graph=graph+"<tr><td>s_mnt_count</td><td>"+to_string(superbloque.s_mnt_count)+"</td></tr>";
                graph=graph+"<tr><td>s_magic</td><td>"+to_string(superbloque.s_magic)+"</td></tr>";
                graph=graph+"<tr><td>s_inode_size</td><td>"+to_string(superbloque.s_inode_size)+"</td></tr>";
                graph=graph+"<tr><td>s_block_size</td><td>"+to_string(superbloque.s_block_size)+"</td></tr>";
                graph=graph+"<tr><td>s_first_ino</td><td>"+to_string(superbloque.s_first_ino)+"</td></tr>";
                graph=graph+"<tr><td>s_first_blo</td><td>"+to_string(superbloque.s_first_blo)+"</td></tr>";
                graph=graph+"<tr><td>s_bm_inode_start</td><td>"+to_string(superbloque.s_bm_inode_start)+"</td></tr>";
                graph=graph+"<tr><td>s_bm_block_start</td><td>"+to_string(superbloque.s_bm_block_start)+"</td></tr>";
                graph=graph+"<tr><td>s_inode_start</td><td>"+to_string(superbloque.s_inode_start)+"</td></tr>";
                graph=graph+"<tr><td>s_block_start</td><td>"+to_string(superbloque.s_block_start)+"</td></tr>";
                graph=graph+"</table>>]\n}";
                Print(graph, "SB");
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

string _REP::toUpperCase(string cadena){
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

string _REP::nameToString(char * name){
    string str;
    for(int i=0;i < 16;i++){
        if(name[i]==int(NULL)) break;
        str=str+name[i];
    }
    return str;
}