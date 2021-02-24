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
    }
};

void _REP::graphMbr(){
 //   FILE *searchFile =  fopen(this->path.c_str(), "wb+");
 //   fread(&this->mbr, sizeof(MBR), 1, searchFile);

    string diskName = "";
    string graph = "digraph G {\nlabel = <<table><tr><td colspan=\"2\">MBR "+diskName+"</td></tr><tr><td>tabla</td></tr>";
    graph+="</table>>;\n}";
    Print(graph, "MBR");
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
        filePath="dot -Tpng "+this->path.substr(0, this->path.length()-3)+"txt -o "+this->path.substr(0, this->path.length()-3)+"png";
    }else if(toLowerCase(this->path.substr(this->path.length()-3, this->path.length()))=="jpg"){
        filePath="dot -Tjpg "+this->path.substr(0, this->path.length()-3)+"txt -o "+this->path.substr(0, this->path.length()-3)+"jpg";
    }else if(toLowerCase(this->path.substr(this->path.length()-3, this->path.length()))=="pdf"){
        filePath="dot -Tpdf "+this->path.substr(0, this->path.length()-3)+"txt -o "+this->path.substr(0, this->path.length()-3)+"pdf";
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