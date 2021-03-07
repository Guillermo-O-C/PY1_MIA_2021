#include <iostream>
#include <fstream>
#include "scanner.h"
#include "parser.h"
using namespace std;
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;
extern int yyparse(void);

class _EXEC {
    private:
    string path="";
    public:
    _EXEC(){};
    void setPath(string path, bool isCadena);
    void exe();
};
void _EXEC::setPath(string path, bool isCadena){
    if(isCadena){
        this->path = path.substr(1, path.length()-2);
    }else{
        this->path = path;
    }
}
void _EXEC::exe(){
    ifstream file(this->path);
    if(!file) cout << "No se ha encontrado el script"<<endl;
    string contenido, linea;
    YY_BUFFER_STATE buffer;
    while (getline(file, linea)) {
        cout << linea <<endl;
        if(linea=="\n")continue;
        if(linea[0]=='#')continue;
        buffer = yy_scan_string((linea+"\n").c_str());    
        if(yyparse()==0){
            //parse correcto
        }else{
            //error
        }
    }
    cout <<"Fin de la ejecución del Script."<<endl;
    return;
    yy_delete_buffer(buffer);
}