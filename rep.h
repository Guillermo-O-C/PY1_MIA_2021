#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
#include "mbr.h"
#include "mountStructs.h"
#include "partitionStructs.h"
#include "mkfile.h"

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
    void setRuta(string ruta, bool isCadena);
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
    void graphFile();
    void graphLs();
    void graphJournaling();
    string toUpperCase(string cadena);
    string nameToString(char * name);
    string recorrerArbol(FILE* search,SB superbloque, inode inodo, string content, int inodoNo);
    string folderToString(char * name);
    string nToString(char * name, int n);
    string toHex(int hex);
    string recorrerInodo(FILE* search, SB superbloque, inode inodo);
    string listarInodos(FILE* search, SB superbloque, inode inodo, string content, string folderName);
    string traducirPermisos(int perm);
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
    id=toUpperCase(id);
    this->id=id;
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
void _REP::setRuta(string ruta, bool isCadena){
    if(isCadena){
        this->ruta = ruta.substr(1, ruta.length()-2);
    }else{
        this->ruta = ruta;
    }
};
void _REP::exe(){
    if(discosMontados[this->diskSpot].status==1){//el disco funciona
        if(discosMontados[this->diskSpot].particiones[this->partSpot].status!=1){
            cout << "ERROR:No hay una partición montada en el espacio "<<(char)(this->partSpot+1)<<endl;
            return;
        }
    }else{
        cout << "ERROR:No hay un disco en el espacio de la letra "<<(char)(this->diskSpot+65)<<endl;
        return;
    }
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
    }
    else if(this->name=="disk"){
        graphDisk();
    }
    else if(this->name=="inode"){
        graphInodos();
    }
    else if(this->name=="block"){
        graphBlocks();
    }
    else if(this->name=="bm_inode"){
        graphBM_Inodos();
    }
    else if(this->name=="bm_block"){
        graphBM_Blocks();
    }
    else if(this->name=="tree"){
        graphTree();
    }
    else if(this->name=="sb"){
        graphSB();
    }
    else if(this->name=="file"){
        graphFile();
    }
    else if(this->name=="ls"){
        graphLs();
    }
    else if(this->name=="journaling"){
        graphJournaling();
    }
    else{
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
        int porcentaje = particiones[i].part_size/(float)mbr.mbr_tamanio*100;
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
                    bitmap=(byte!='0')?bitmap+'1':bitmap+'0';
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
                        graph=graph+"<tr><td>i_type</td><td>"+inodo.i_type+"</td></tr>";
                        graph=graph+"<tr><td>i_perm</td><td>"+to_string(inodo.i_perm)+"</td></tr>";
                        graph=graph+"</table>>];\n";
                        arrow='1';
                    }
                }
                Print(graph+punteros+";\n}", "Inodos");
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
                string graph= "digraph G {\nnode[ shape=box fontname=Helvetica ] rankdir = LR;";
                string punteros;
                SB superbloque;
                fseek(search, opciones[i].part_start, SEEK_SET);
                fread(&superbloque, sizeof(SB), 1, search);
                char arrow = '0';
                cout<< "Generando reporte, por favor espera..."<<endl;
                for(int e = 0;e<superbloque.s_first_blo;e++){
                    fseek(search, superbloque.s_bm_block_start+e, SEEK_SET);
                    char byte;
                    fread(&byte, 1, 1, search);
                    if(byte=='1'){//carpetas
                        if(arrow=='1') punteros=punteros+"->";
                        folder_block folder;
                        fseek(search, superbloque.s_block_start+64*(e), SEEK_SET);
                        fread(&folder, sizeof(folder_block), 1, search);
                        punteros=punteros+"block"+to_string(e);
                        graph=graph+"block"+to_string(e)+" [label=<<table border=\"1\">";
                        graph=graph+"<tr><td colspan=\"2\">Block_"+to_string(e)+"</td></tr>";
                        for(int o=0;o<4;o++){
                            graph=graph+"<tr><td>"+folderToString(folder.b_content[o].b_name)+"</td><td>"+to_string(folder.b_content[o].b_inodo)+"</td></tr>";
                        }
                        graph=graph+"</table>>];\n";
                        arrow='1';
                    }
                    else if(byte=='2'){//contenido
                        if(arrow=='1') punteros=punteros+"->";
                        file_block file;
                        fseek(search, superbloque.s_block_start+64*(e), SEEK_SET);
                        fread(&file, sizeof(file_block), 1, search);
                        punteros=punteros+"block"+to_string(e);
                        graph=graph+"block"+to_string(e)+" [label=<<table border=\"1\">";
                        string fileContent="";
                        int relleno=0;
                        for(int o=0;o<64;o++){
                            if(file.b_content[o]=='\0'){
                                break;
                            }
                            fileContent=fileContent+file.b_content[o];
                        }
                        graph=graph+"<tr><td >Block_"+to_string(e)+"</td></tr>";
                        graph=graph+"<tr><td>"+fileContent+"</td></tr>";
                        graph=graph+"</table>>];\n";
                        arrow='1';
                    }
                    else if(byte=='3'){//punteros
                        if(arrow=='1') punteros=punteros+"->";
                        pointers apuntadores;
                        fseek(search, superbloque.s_block_start+64*(e), SEEK_SET);
                        fread(&apuntadores, sizeof(file_block), 1, search);
                        punteros=punteros+"block"+to_string(e);
                        graph=graph+"block"+to_string(e)+" [label=<<table border=\"1\">";
                        graph=graph+"<tr><td colspan=\"2\">Block_"+to_string(e)+"</td></tr>";
                        for(int o=0;o<12;o++){
                            graph=graph+"<tr><td>APD"+to_string(o)+"</td><td>"+to_string(apuntadores.b_pointers[o])+"</td></tr>";
                        }
                        graph=graph+"<tr><td>API1</td><td>"+to_string(apuntadores.b_pointers[12])+"</td></tr>";
                        graph=graph+"<tr><td>API2</td><td>"+to_string(apuntadores.b_pointers[12])+"</td></tr>";
                        graph=graph+"<tr><td>API3</td><td>"+to_string(apuntadores.b_pointers[13])+"</td></tr>";
                        graph=graph+"</table>>];\n";
                        arrow='1';
                    }
                }
                Print(graph+punteros+";\n}", "Bloques");
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
                string punteros;
                SB superbloque;
                fseek(search, opciones[i].part_start, SEEK_SET);
                fread(&superbloque, sizeof(SB), 1, search);
                string graph="digraph structs {\nnode [shape=plaintext]\nrankdir=LR;\n";
                inode raiz;
                fseek(search, superbloque.s_inode_start, SEEK_SET);
                fread(&raiz, sizeof(inode), 1, search);
                graph = recorrerArbol(search,superbloque, raiz, graph, 0);
                Print(graph+"\n}", "Tree");
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

string _REP::recorrerArbol(FILE* search, SB superbloque, inode inodo, string content, int inodeNo){
    //color inodo 54b4eb, content f7de1b, carpetas 04ff00, apuntadores ff8c00
    content=content+"inode"+to_string(inodeNo)+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#54b4eb\"><tr><td colspan=\"2\">Inodo_"+to_string(inodeNo)+"</td></tr>";    
    if(inodo.i_type=='0'){
        content=content+"<tr><td>tipo</td><td>0</td></tr>";
        content=content+"<tr><td>tamaño</td><td>0</td></tr>";
        for(int i =0;i<12;i++){
            content=content+"<tr><td>APD"+to_string(i)+"</td><td PORT=\"f"+to_string(i)+"\">"+to_string(inodo.i_block[i])+"</td></tr>";       
        }
        content=content+"<tr><td>API"+to_string(1)+"</td><td PORT=\"f"+to_string(13)+"\">"+to_string(inodo.i_block[12])+"</td></tr>";
        content=content+"<tr><td>API"+to_string(2)+"</td><td PORT=\"f"+to_string(14)+"\">"+to_string(inodo.i_block[13])+"</td></tr>";
        content=content+"<tr><td>API"+to_string(3)+"</td><td PORT=\"f"+to_string(15)+"\">"+to_string(inodo.i_block[14])+"</td></tr></table>>];";
        for(int i =0;i<12;i++){
            if(inodo.i_block[i]!=-1){
                //existe una carpeta
                content=content+"\ninode"+to_string(inodeNo)+":f"+to_string(i)+"->folder"+to_string(inodo.i_block[i])+";\n";
                content=content+"folder"+to_string(inodo.i_block[i])+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#04ff00\">";
                content=content+"<tr><td colspan=\"2\">Bloque_"+to_string(inodo.i_block[i])+"</td></tr>";
                folder_block folder;
                fseek(search, superbloque.s_block_start+inodo.i_block[i]*64, SEEK_SET);
                fread(&folder, 64, 1, search);
                for(int e =0;e<4;e++){
                    content=content+"<tr><td>"+folderToString(folder.b_content[e].b_name)+"</td><td PORT=\"f"+to_string(e)+"\">"+to_string(folder.b_content[e].b_inodo)+"</td></tr>";
                }
                content=content+"</table>>];";  
                for(int e =0;e<4;e++){
                    if(folder.b_content[e].b_inodo!=-1){
                        if(i==0 && e==0 || i==0 && e==1)continue;//para que no se encicle con el padre y abuelo
                        content=content+"folder"+to_string(inodo.i_block[i])+":f"+to_string(e)+"->inode"+to_string(folder.b_content[e].b_inodo)+";\n";
                        fseek(search, superbloque.s_inode_start+folder.b_content[e].b_inodo*sizeof(inode),SEEK_SET);
                        inode next;
                        fread(&next, sizeof(inode), 1, search);
                        content = recorrerArbol(search, superbloque, next, content, folder.b_content[e].b_inodo);
                    }                    
                }      
            }
        }
        //API1
        if(inodo.i_block[12]!=-1){//API1 en uso
            content=content+"inode"+to_string(inodeNo)+":f13->API"+to_string(inodo.i_block[12])+";\n";
            content=content+"API"+to_string(inodo.i_block[12])+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#ff8c00\">";
            content=content+"<tr><td>Bloque_"+to_string(inodo.i_block[12])+"</td></tr>";
            pointers apuntadores;
            fseek(search, 64*inodo.i_block[12]+superbloque.s_block_start, SEEK_SET);
            fread(&apuntadores, 64, 1, search);
            for(int i=0;i<16;i++){
                content=content+"<tr><td PORT=\"f"+to_string(i)+"\">"+to_string(apuntadores.b_pointers[i])+"</td></tr>";
            }
            content=content+"</table>>];";  
            for(int i=0;i<16;i++){
                if(apuntadores.b_pointers[i]!=-1){//dirigen a un bloque de tipo carpeta
                    content=content+"API"+to_string(inodo.i_block[12])+":f"+to_string(i)+"->folder"+to_string(apuntadores.b_pointers[i])+";\n";
                    content=content+"folder"+to_string(apuntadores.b_pointers[i])+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#04ff00\">";
                    content=content+"<tr><td colspan=\"2\">Bloque_"+to_string(apuntadores.b_pointers[i])+"</td></tr>";
                    folder_block folder;
                    fseek(search, superbloque.s_block_start+apuntadores.b_pointers[i]*64, SEEK_SET);
                    fread(&folder, 64, 1, search);
                    for(int e =0;e<4;e++){
                        content=content+"<tr><td>"+folderToString(folder.b_content[e].b_name)+"</td><td PORT=\"f"+to_string(e)+"\">"+to_string(folder.b_content[e].b_inodo)+"</td></tr>";
                    }
                    content=content+"</table>>];";  
                    for(int e =0;e<4;e++){
                        if(folder.b_content[e].b_inodo!=-1){
                            content=content+"folder"+to_string(apuntadores.b_pointers[i])+":f"+to_string(e)+"->inode"+to_string(folder.b_content[e].b_inodo)+";\n";
                            fseek(search, superbloque.s_inode_start+folder.b_content[e].b_inodo*sizeof(inode),SEEK_SET);
                            inode next;
                            fread(&next, sizeof(inode), 1, search);
                            content = recorrerArbol(search, superbloque, next, content, folder.b_content[e].b_inodo);
                        }                    
                    } 
                }                    
            }    
        }
    }
    else{
        content=content+"<tr><td>tipo</td><td>1</td></tr>";
        content=content+"<tr><td>tamaño</td><td>"+to_string(inodo.i_size)+"</td></tr>";
        for(int i =0;i<12;i++){
            content=content+"<tr><td>APD"+to_string(i)+"</td><td PORT=\"f"+to_string(i)+"\">"+to_string(inodo.i_block[i])+"</td></tr>";  
            if(i==12)break;     
        }
        content=content+"<tr><td>API"+to_string(1)+"</td><td PORT=\"f"+to_string(13)+"\">"+to_string(inodo.i_block[12])+"</td></tr>";
        content=content+"<tr><td>API"+to_string(2)+"</td><td PORT=\"f"+to_string(14)+"\">"+to_string(inodo.i_block[13])+"</td></tr>";
        content=content+"<tr><td>API"+to_string(3)+"</td><td PORT=\"f"+to_string(15)+"\">"+to_string(inodo.i_block[14])+"</td></tr></table>>];";
        if(inodo.i_size!=0){
            //existe un archivo
            int sizePrinted=0;
            for(int i =0;i<12;i++){
                file_block file;
                fseek(search, superbloque.s_block_start+inodo.i_block[i]*64, SEEK_SET);
                fread(&file, 64, 1, search);
                string fileContent="";
                if(inodo.i_size-sizePrinted>64){
                    //imprime los 64 bytes del bloque
                    for(int e =0;e<64;e++){
                        if(file.b_content[e]=='\n'){
                            fileContent=fileContent+"\\n";
                        }else{
                            fileContent=fileContent+file.b_content[e];

                        }
                        sizePrinted++;
                    }
                }else{
                    for(int e =0;e<inodo.i_size-sizePrinted;e++){
                        if(file.b_content[e]=='\n'){
                            fileContent=fileContent+"\\n";
                            continue;
                        }
                        fileContent=fileContent+file.b_content[e];
                    }/*
                    int relleno=0;
                    for(int e =inodo.i_size-sizePrinted;e<64;e++){
                        fileContent=fileContent+to_string(relleno);
                        if(relleno==9)relleno=0;
                        relleno++;
                    }*/
                    sizePrinted=inodo.i_size;
                }
                content=content+"inode"+to_string(inodeNo)+":f"+to_string(i)+"->file"+to_string(inodo.i_block[i])+";";
                content=content+"file"+to_string(inodo.i_block[i])+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#f7de1b\">";
                content=content+"<tr><td>BLOQUE_"+to_string(inodo.i_block[i])+"</td></tr>";
                content=content+"<tr><td>"+fileContent.c_str()+"</td></tr></table>>];";
                if(sizePrinted==inodo.i_size)break;
            } 
            if(sizePrinted==inodo.i_size)return content;
            //API1
            if(inodo.i_block[12]==-1)return content;
            pointers API1;
            fseek(search, superbloque.s_block_start+inodo.i_block[12]*64, SEEK_SET);
            fread(&API1, 64, 1, search);
            content=content+"inode"+to_string(inodeNo)+":f"+to_string(13)+"->pointers"+to_string(inodo.i_block[12])+";";
            content=content+"pointers"+to_string(inodo.i_block[12])+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#ff8c00\">";
            content=content+"<tr><td colspan=\"2\">BLOQUE_"+to_string(inodo.i_block[12])+"</td></tr>";
            for(int i =0;i<16;i++){
                content=content+"<tr><td>APD"+to_string(i)+"</td><td PORT=\"f"+to_string(i)+"\">"+to_string(API1.b_pointers[i])+"</td></tr>";  
            }
            content=content+"</table>>];";
            for(int i =0;i<16;i++){
                if(sizePrinted==inodo.i_size || API1.b_pointers[i]==-1)break;//si apunta a -1 igual se arruinaría el grafo así que mejor break
                file_block file;
                fseek(search, superbloque.s_block_start+ API1.b_pointers[i]*64, SEEK_SET);
                fread(&file, 64, 1, search);
                string fileContent="";
                if(inodo.i_size-sizePrinted>64){
                    //imprime los 64 bytes del bloque
                    for(int e =0;e<64;e++){
                        if(file.b_content[e]=='\n'){
                            fileContent=fileContent+"\\n";
                        }else{
                            fileContent=fileContent+file.b_content[e];
                        }
                        sizePrinted++;
                    }
                }else{
                    for(int e =0;e<inodo.i_size-sizePrinted;e++){
                        if(file.b_content[e]=='\n'){
                            fileContent=fileContent+"\\n";
                            continue;
                        }
                        fileContent=fileContent+file.b_content[e];
                    }
                    sizePrinted=inodo.i_size;
                }
                content=content+"pointers"+to_string(inodo.i_block[12])+":f"+to_string(i)+"->file"+to_string(API1.b_pointers[i])+";";
                content=content+"file"+to_string(API1.b_pointers[i])+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#f7de1b\">";
                content=content+"<tr><td>BLOQUE_"+to_string(API1.b_pointers[i])+"</td></tr>";
                content=content+"<tr><td>"+fileContent.c_str()+"</td></tr></table>>];";
            }
            //API2
            if(inodo.i_block[13]==-1)return content;
            pointers API2;
            fseek(search, superbloque.s_block_start+inodo.i_block[13]*64, SEEK_SET);
            fread(&API2, 64, 1, search);
            content=content+"inode"+to_string(inodeNo)+":f"+to_string(14)+"->pointers"+to_string(inodo.i_block[13])+";";
            content=content+"pointers"+to_string(inodo.i_block[13])+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#ff8c00\">";
            content=content+"<tr><td colspan=\"2\">BLOQUE_"+to_string(inodo.i_block[13])+"</td></tr>";
            for(int i =0;i<16;i++){
                content=content+"<tr><td>APD"+to_string(i)+"</td><td PORT=\"f"+to_string(i)+"\">"+to_string(API2.b_pointers[i])+"</td></tr>";  
            }
            content=content+"</table>>];";
            for(int e =0;e<16;e++){
                if(API2.b_pointers[e]!=-1){
                    pointers API1;
                    fseek(search, superbloque.s_block_start+API2.b_pointers[e]*64, SEEK_SET);
                    fread(&API1, 64, 1, search);
                    content=content+"pointers"+to_string(inodo.i_block[13])+":f"+to_string(e)+"->pointers"+to_string(API2.b_pointers[e])+";";
                    content=content+"pointers"+to_string(API2.b_pointers[e])+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#ff8c00\">";
                    content=content+"<tr><td colspan=\"2\">BLOQUE_"+to_string(API2.b_pointers[e])+"</td></tr>";
                    for(int i =0;i<16;i++){
                        content=content+"<tr><td>APD"+to_string(i)+"</td><td PORT=\"f"+to_string(i)+"\">"+to_string(API1.b_pointers[i])+"</td></tr>";  
                    }
                    content=content+"</table>>];";
                    for(int i =0;i<16;i++){
                        if(sizePrinted==inodo.i_size || API1.b_pointers[i]==-1)break;//si apunta a -1 igual se arruinaría el grafo así que mejor break
                        file_block file;
                        fseek(search, superbloque.s_block_start+ API1.b_pointers[i]*64, SEEK_SET);
                        fread(&file, 64, 1, search);
                        string fileContent="";
                        if(inodo.i_size-sizePrinted>64){
                            //imprime los 64 bytes del bloque
                            for(int e =0;e<64;e++){
                                if(file.b_content[e]=='\n'){
                                    fileContent=fileContent+"\\n";
                                }else{
                                    fileContent=fileContent+file.b_content[e];

                                }
                                sizePrinted++;
                            }
                        }else{
                            for(int e =0;e<inodo.i_size-sizePrinted;e++){
                                if(file.b_content[e]=='\n'){
                                    fileContent=fileContent+"\\n";
                                    continue;
                                }
                                fileContent=fileContent+file.b_content[e];
                            }
                            sizePrinted=inodo.i_size;
                        }
                        content=content+"pointers"+to_string(API2.b_pointers[e])+":f"+to_string(i)+"->file"+to_string(API1.b_pointers[i])+";";
                        content=content+"file"+to_string(API1.b_pointers[i])+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#f7de1b\">";
                        content=content+"<tr><td>BLOQUE_"+to_string(API1.b_pointers[i])+"</td></tr>";
                        content=content+"<tr><td>"+fileContent.c_str()+"</td></tr></table>>];";
                        if(sizePrinted==inodo.i_size)break;
                    }
                }
            }
            //API3
            if(inodo.i_block[14]==-1)return content;
            pointers API3;
            fseek(search, superbloque.s_block_start+inodo.i_block[14]*64, SEEK_SET);
            fread(&API3, 64, 1, search);
            content=content+"inode"+to_string(inodeNo)+":f"+to_string(15)+"->pointers"+to_string(inodo.i_block[14])+";";
            content=content+"pointers"+to_string(inodo.i_block[14])+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#ff8c00\">";
            content=content+"<tr><td colspan=\"2\">BLOQUE_"+to_string(inodo.i_block[14])+"</td></tr>";
            for(int i =0;i<16;i++){
                content=content+"<tr><td>APD"+to_string(i)+"</td><td PORT=\"f"+to_string(i)+"\">"+to_string(API3.b_pointers[i])+"</td></tr>";  
            }
            content=content+"</table>>];";

            for(int o=0;o<16;o++){
                if(API3.b_pointers[o]!=-1){
                    pointers API2;
                    fseek(search, superbloque.s_block_start+API3.b_pointers[o]*64, SEEK_SET);
                    fread(&API2, 64, 1, search);
                    content=content+"pointers"+to_string(inodo.i_block[14])+":f"+to_string(o)+"->pointers"+to_string(API3.b_pointers[o])+";";
                    content=content+"pointers"+to_string(API3.b_pointers[o])+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#ff8c00\">";
                    content=content+"<tr><td colspan=\"2\">BLOQUE_"+to_string(API3.b_pointers[o])+"</td></tr>";
                    for(int i =0;i<16;i++){
                        content=content+"<tr><td>APD"+to_string(i)+"</td><td PORT=\"f"+to_string(i)+"\">"+to_string(API2.b_pointers[i])+"</td></tr>";  
                    }
                    content=content+"</table>>];";
                    //return content;
                    for(int e =0;e<16;e++){
                        if(API2.b_pointers[e]!=-1){
                            pointers API1;
                            fseek(search, superbloque.s_block_start+API2.b_pointers[e]*64, SEEK_SET);
                            fread(&API1, 64, 1, search);
                            content=content+"pointers"+to_string(API3.b_pointers[o])+":f"+to_string(e)+"->pointers"+to_string(API2.b_pointers[e])+";";
                            content=content+"pointers"+to_string(API2.b_pointers[e])+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#ff8c00\">";
                            content=content+"<tr><td colspan=\"2\">BLOQUE_"+to_string(API2.b_pointers[e])+"</td></tr>";
                            for(int i =0;i<16;i++){
                                content=content+"<tr><td>APD"+to_string(i)+"</td><td PORT=\"f"+to_string(i)+"\">"+to_string(API1.b_pointers[i])+"</td></tr>";  
                            }
                            content=content+"</table>>];";
                            for(int i =0;i<16;i++){
                                if(sizePrinted==inodo.i_size || API1.b_pointers[i]==-1)break;//si apunta a -1 igual se arruinaría el grafo así que mejor break
                                file_block file;
                                fseek(search, superbloque.s_block_start+ API1.b_pointers[i]*64, SEEK_SET);
                                fread(&file, 64, 1, search);
                                string fileContent="";
                                if(inodo.i_size-sizePrinted>64){
                                    //imprime los 64 bytes del bloque
                                    for(int e =0;e<64;e++){
                                        if(file.b_content[e]=='\n'){
                                            fileContent=fileContent+"\\n";
                                        }else{
                                            fileContent=fileContent+file.b_content[e];

                                        }
                                        sizePrinted++;
                                    }
                                }else{
                                    for(int e =0;e<inodo.i_size-sizePrinted;e++){
                                        if(file.b_content[e]=='\n'){
                                            fileContent=fileContent+"\\n";
                                            continue;
                                        }
                                        fileContent=fileContent+file.b_content[e];
                                    }
                                    sizePrinted=inodo.i_size;
                                }
                                content=content+"pointers"+to_string(API2.b_pointers[e])+":f"+to_string(i)+"->file"+to_string(API1.b_pointers[i])+";";
                                content=content+"file"+to_string(API1.b_pointers[i])+"[label=<<table BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"#f7de1b\">";
                                content=content+"<tr><td>BLOQUE_"+to_string(API1.b_pointers[i])+"</td></tr>";
                                content=content+"<tr><td>"+fileContent.c_str()+"</td></tr></table>>];";
                                if(sizePrinted==inodo.i_size)break;
                            }
                        }
                    }
                }
            }
        }
    }
    return content;
}

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
                graph=graph+"<tr><td>s_magic</td><td>0x"+toHex(superbloque.s_magic)+"</td></tr>";
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

void _REP::graphFile(){
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
                _MKFILE buscador;
                int inodeLocation =0;
                this->ruta = (this->ruta[0] == '/') ? this->ruta.substr(1, this->ruta.length()) : this->ruta;
                vector<string> carpetas = buscador.split(this->ruta, "/");
                for (int e = 0; e < carpetas.size(); e++)
                { //ciclo para iterar entre las carpetas de la ruta
                    if (e == carpetas.size() - 1)
                    { //el último elelmento es el archivo a crear
                        SB superBloque;
                        fseek(search, opciones[i].part_start, SEEK_SET);
                        fread(&superBloque, sizeof(SB), 1, search);
                        inode carpetaTemporal;
                        fseek(search, superBloque.s_inode_start + sizeof(inode) * inodeLocation, SEEK_SET);
                        fread(&carpetaTemporal, sizeof(inode), 1, search);
                        string folderName = carpetas[e];
                        inodeLocation = buscador.searchFile(search, superBloque, carpetaTemporal, folderName);
                        if (inodeLocation != 0)
                        {
                            fseek(search, superBloque.s_inode_start + sizeof(inode) * inodeLocation, SEEK_SET);
                            fread(&carpetaTemporal, sizeof(inode), 1, search);
                            string fileContent = recorrerInodo(search, superBloque, carpetaTemporal);
                            string graph = "digraph G {\n node [ shape=box fontname=Helvetica ] sb [label = <<table><tr><td>"+folderName+"</td></tr>";
                            graph=graph+"<tr><td>"+fileContent+"</td></tr></table>>];}";
                            Print(graph, "File");
                            return;
                        }
                        else
                        {
                            cout << "ERROR: No se ha encontrado el archivo "<<folderName<<endl;
                            return;
                        }
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
                            cout << "ERROR: No se ha encontrado el archivo en la ruta "<<this->ruta<<endl;
                        }
                    }
                }

            }
        }
    }
};

void _REP::graphLs(){
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
                string graph = "digraph G {\n node [ shape=box fontname=Helvetica ] sb [label = <<table>\n";
                graph = graph + "<tr><td>Permisos</td><td>Dueño</td><td>Grupo</td><td>Size</td><td>Fecha</td><td>Hora</td><td>Tipo</td><td>Name</td></tr>\n";
                inode raiz;
                fseek(search, superbloque.s_inode_start, SEEK_SET);
                fread(&raiz, sizeof(inode), 1, search);
                graph = listarInodos(search, superbloque, raiz, graph, "/");
                Print(graph+"</table>>];\n}", "LS");
            }
        }
    }
};

void _REP::graphJournaling(){
    FILE *search =  fopen(this->diskPath.c_str(), "rb+");
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
                Journaling temp;
                string graph = "digraph G {\n node [ shape=box fontname=Helvetica ] ";
                string arrow="";
                for(int e =0;e<superBloque.s_inodes_count;e++){
                    fseek(search, opciones[i].part_start+sizeof(SB)+e*sizeof(Journaling), SEEK_SET);
                    fread(&temp, sizeof(Journaling), 1, search);
                    if(temp.tipo!='1' && temp.tipo!='2'){//sin usar
                        break;
                    }
                    if(e!=0)arrow=arrow+"->";
                    graph=graph+"journal"+to_string(e)+"[label = <<table><tr><td colspan=\"6\">Journal "+to_string(e)+"-"+this->id+"</td></tr>";
                    graph=graph+"<tr><td>Tipo de Operacion</td><td>Tipo</td><td>Path</td><td>Contenido</td><td>Size</td><td>Fecha</td></tr>";
                    graph=graph+"<tr><td>"+nToString(temp.tipo_operacion, 10)+"</td>";
                    graph=graph+"<td>"+temp.tipo+"</td>";
                    graph=graph+"<td>"+nToString(temp.path,60)+"</td>";
                    graph=graph+"<td>"+nToString(temp.contenido, 100)+"</td>";
                    graph=graph+"<td>"+to_string(temp.size)+"</td>";
                    graph=graph+"<td>"+nToString(temp.log_fecha, 16)+"</td></tr></table>>];\n";
                    arrow=arrow+"journal"+to_string(e);
                }
                Print(graph+arrow+";\n}", "Journaling");
            }
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

string _REP::folderToString(char * name){
    string str;
    for(int i=0;i < 12;i++){
        if(name[i]==int(NULL)) break;
        str=str+name[i];
    }
    return str;
}

string _REP::nToString(char * name, int n){
    string str;
    for(int i=0;i < n;i++){
        if(name[i]==int(NULL)) break;
        str=str+name[i];
    }
    return str;
}

string _REP::toHex(int hex){
    std::stringstream ss;
    ss << std::hex << hex;
    const std::string s = ss.str();
    return toUpperCase(s);
}

string _REP::recorrerInodo(FILE* search, SB superbloque, inode inodo){
    string fileContent="";
    if(inodo.i_type=='1'){
        if(inodo.i_size!=0){
            //existe un archivo
            int sizePrinted=0;
            for(int i =0;i<12;i++){
                file_block file;
                fseek(search, superbloque.s_block_start+inodo.i_block[i]*64, SEEK_SET);
                fread(&file, 64, 1, search);
                if(inodo.i_size-sizePrinted>64){
                    //imprime los 64 bytes del bloque
                    for(int e =0;e<64;e++){
                        if(file.b_content[e]=='\n'){
                            fileContent=fileContent+"<br/>";
                        }else{
                            fileContent=fileContent+file.b_content[e];

                        }
                        sizePrinted++;
                    }
                }else{
                    for(int e =0;e<inodo.i_size-sizePrinted;e++){
                        if(file.b_content[e]=='\n'){
                            fileContent=fileContent+"<br/>";
                            continue;
                        }
                        fileContent=fileContent+file.b_content[e];
                    }
                    sizePrinted=inodo.i_size;
                }
                if(sizePrinted==inodo.i_size)break;
            } 
            if(sizePrinted==inodo.i_size)return fileContent;
            //API1
            if(inodo.i_block[12]==-1)return fileContent;
            pointers API1;
            fseek(search, superbloque.s_block_start+inodo.i_block[12]*64, SEEK_SET);
            fread(&API1, 64, 1, search);
            for(int i =0;i<16;i++){
                if(sizePrinted==inodo.i_size || API1.b_pointers[i]==-1)break;//si apunta a -1 igual se arruinaría el grafo así que mejor break
                file_block file;
                fseek(search, superbloque.s_block_start+ API1.b_pointers[i]*64, SEEK_SET);
                fread(&file, 64, 1, search);
                if(inodo.i_size-sizePrinted>64){
                    //imprime los 64 bytes del bloque
                    for(int e =0;e<64;e++){
                        if(file.b_content[e]=='\0')break;
                        if(file.b_content[e]=='\n'){
                            fileContent=fileContent+"<br/>";
                        }else{
                            fileContent=fileContent+file.b_content[e];
                        }
                        sizePrinted++;
                    }
                }else{
                    for(int e =0;e<inodo.i_size-sizePrinted;e++){
                        if(file.b_content[e]=='\n'){
                            fileContent=fileContent+"<br/>";
                            continue;
                        }
                        fileContent=fileContent+file.b_content[e];
                    }
                    sizePrinted=inodo.i_size;
                }
            }
            //API2
            if(inodo.i_block[13]==-1)return fileContent;
            pointers API2;
            fseek(search, superbloque.s_block_start+inodo.i_block[13]*64, SEEK_SET);
            fread(&API2, 64, 1, search);
            for(int e =0;e<16;e++){
                if(API2.b_pointers[e]!=-1){
                    pointers API1;
                    fseek(search, superbloque.s_block_start+API2.b_pointers[e]*64, SEEK_SET);
                    fread(&API1, 64, 1, search);
                    for(int i =0;i<16;i++){
                        if(sizePrinted==inodo.i_size || API1.b_pointers[i]==-1)break;//si apunta a -1 igual se arruinaría el grafo así que mejor break
                        file_block file;
                        fseek(search, superbloque.s_block_start+ API1.b_pointers[i]*64, SEEK_SET);
                        fread(&file, 64, 1, search);
                        if(inodo.i_size-sizePrinted>64){
                            //imprime los 64 bytes del bloque
                            for(int e =0;e<64;e++){
                                if(file.b_content[e]=='\0')break;
                                if(file.b_content[e]=='\n'){
                                    fileContent=fileContent+"<br/>";
                                }else{
                                    fileContent=fileContent+file.b_content[e];

                                }
                                sizePrinted++;
                            }
                        }else{
                            for(int e =0;e<inodo.i_size-sizePrinted;e++){
                                if(file.b_content[e]=='\n'){
                                    fileContent=fileContent+"<br/>";
                                    continue;
                                }
                                fileContent=fileContent+file.b_content[e];
                            }
                            sizePrinted=inodo.i_size;
                        }
                        if(sizePrinted==inodo.i_size)break;
                    }
                }
            }
            //API3
            if(inodo.i_block[14]==-1)return fileContent;
            pointers API3;
            fseek(search, superbloque.s_block_start+inodo.i_block[14]*64, SEEK_SET);
            fread(&API3, 64, 1, search);
            for(int o=0;o<16;o++){
                if(API3.b_pointers[o]!=-1){
                    pointers API2;
                    fseek(search, superbloque.s_block_start+API3.b_pointers[o]*64, SEEK_SET);
                    fread(&API2, 64, 1, search);
                    for(int e =0;e<16;e++){
                        if(API2.b_pointers[e]!=-1){
                            pointers API1;
                            fseek(search, superbloque.s_block_start+API2.b_pointers[e]*64, SEEK_SET);
                            fread(&API1, 64, 1, search);
                            for(int i =0;i<16;i++){
                                if(sizePrinted==inodo.i_size || API1.b_pointers[i]==-1)break;//si apunta a -1 igual se arruinaría el grafo así que mejor break
                                file_block file;
                                fseek(search, superbloque.s_block_start+ API1.b_pointers[i]*64, SEEK_SET);
                                fread(&file, 64, 1, search);
                                if(inodo.i_size-sizePrinted>64){
                                    //imprime los 64 bytes del bloque
                                    for(int e =0;e<64;e++){
                                        if(file.b_content[e]=='\0')break;
                                        if(file.b_content[e]=='\n'){
                                            fileContent=fileContent+"<br/>";
                                        }else{
                                            fileContent=fileContent+file.b_content[e];

                                        }
                                        sizePrinted++;
                                    }
                                }else{
                                    for(int e =0;e<inodo.i_size-sizePrinted;e++){
                                        if(file.b_content[e]=='\n'){
                                            fileContent=fileContent+"<br/>";
                                            continue;
                                        }
                                        fileContent=fileContent+file.b_content[e];
                                    }
                                    sizePrinted=inodo.i_size;
                                }
                                if(sizePrinted==inodo.i_size)break;
                            }
                        }
                    }
                }
            }
        }
    }
    return fileContent;
}

string _REP::listarInodos(FILE* search, SB superbloque, inode inodo, string content, string folderName){
    string fecha = "";
    string hora = "";
    for(int e=0;e<10;e++){
        fecha=fecha+inodo.i_atime[e];
        if(e<5){
            hora = inodo.i_atime[15-e]+hora;
        }
    }
    if(inodo.i_type=='0'){
        content=content+"<tr><td>"+traducirPermisos(inodo.i_perm)+"</td><td>root</td><td>root</td><td>"+to_string(inodo.i_size)+"</td><td>"+fecha+"</td><td>"+hora+"</td><td>Carpeta</td><td>"+folderName+"</td></tr>\n";
        for(int i =0;i<12;i++){
            if(inodo.i_block[i]!=-1){
                folder_block folder;
                fseek(search, superbloque.s_block_start+inodo.i_block[i]*64, SEEK_SET);
                fread(&folder, 64, 1, search);
                for(int e =0;e<4;e++){
                    if(folder.b_content[e].b_inodo!=-1){
                        if(i==0 && e==0 || i==0 && e==1)continue;//para que no se encicle con el padre y abuelo
                        fseek(search, superbloque.s_inode_start+folder.b_content[e].b_inodo*sizeof(inode),SEEK_SET);
                        inode next;
                        fread(&next, sizeof(inode), 1, search);
                        content = listarInodos(search, superbloque, next, content, folder.b_content[e].b_name);
                    }                    
                }      
            }
        }
        //API1
        if(inodo.i_block[12]!=-1){//API1 en uso
            pointers apuntadores;
            fseek(search, 64*inodo.i_block[12]+superbloque.s_block_start, SEEK_SET);
            for(int i=0;i<16;i++){
                if(apuntadores.b_pointers[i]!=-1){//dirigen a un bloque de tipo carpeta
                    folder_block folder;
                    fseek(search, superbloque.s_block_start+apuntadores.b_pointers[i]*64, SEEK_SET);
                     for(int e =0;e<4;e++){
                        if(folder.b_content[e].b_inodo!=-1){
                            fseek(search, superbloque.s_inode_start+folder.b_content[e].b_inodo*sizeof(inode),SEEK_SET);
                            inode next;
                            fread(&next, sizeof(inode), 1, search);
                            content = listarInodos(search, superbloque, next, content, folder.b_content[e].b_name);
                        }                    
                    } 
                }                    
            }    
        }
    }
    else{
        content=content+"<tr><td>"+traducirPermisos(inodo.i_perm)+"</td><td>root</td><td>root</td><td>"+to_string(inodo.i_size)+"</td><td>"+fecha+"</td><td>"+hora+"</td><td>Archivo</td><td>"+folderName+"</td></tr>\n";
    }
    return content;
}

string _REP::traducirPermisos(int perm){
    std::ostringstream os;
    os << perm;
    std::string digits = os.str();
    string translation;
    for(int i =0;i<3;i++){
        switch(digits[i]-'0'){
            case 0:
                translation = translation+"---";
                break;
            case 1:
                translation = translation+"--x";
                break;
            case 2:
                translation = translation+"-w-";
                break;
            case 3:
                translation = translation+"r--";
                break;
            case 4:
                translation = translation+"r-x";
                break;
            case 5:
                translation = translation+"r-x";
                break;
            case 6:
                translation = translation+"rw-";
                break;
            case 7:
                translation = translation+"rwx";
                break;
        }
    }
    return translation;
}
