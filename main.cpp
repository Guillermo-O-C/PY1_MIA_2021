#include <iostream>
using namespace std;
#include "scanner.h"
#include "parser.h"
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;
extern int yyparse(void);

void parse(){
    string entry;
    getline(cin,entry);
    entry+="\n";
    YY_BUFFER_STATE buffer = yy_scan_string(entry.c_str());    
    if(yyparse()==0){
        //parse correcto
    }else{
        //error
    }
    yy_delete_buffer(buffer);
};
int main(){
    system("clear");
    while(true){
        parse();
    }
    return 0;
};