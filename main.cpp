#include <iostream>
using namespace std;
#include "scanner.h"
#include "parser.h"
#include "mbr.h"
#include "mountStructs.h"

extern int yylex(void);
extern char *yytext;
extern FILE *yyin;
extern int yyparse(void);
disco discosMontados[26];

void parse(){
    string entry;
    getline(cin,entry);
    if(entry==""){ 
        //no action 
    }else{
        entry+="\n";
        YY_BUFFER_STATE buffer = yy_scan_string(entry.c_str());    
        if(yyparse()==0){
            //parse correcto
        }else{
            //error
        }
        yy_delete_buffer(buffer);
    }
};
int main(){
    system("clear");
    while(true){
        parse();
    }
    return 0;
};