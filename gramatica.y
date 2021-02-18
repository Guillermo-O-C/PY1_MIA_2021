%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>

#include "scanner.h"
#include "mkdisk.h"

using namespace std;
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;
extern void yyerror(const char *s);
extern int linea;

_MKDISK * mkdiskV;
%}

%start INIT

%token<NUM> numero
%token<NUM> negativo
%token<STRING> cadena
%token<STRING> guion
%token<STRING> igual
%token<STRING> mkdisk
%token<STRING> size
%token<STRING> f
%token<STRING> u
%token<STRING> path
%token<STRING> rmdisk
%token<STRING> fdisk
%token<STRING> type
%token<STRING> delete_
%token<STRING> name
%token<STRING> add
%token<STRING> mount
%token<STRING> unmount
%token<STRING> mkfs
%token<STRING> id
%token<STRING> fs
%token<STRING> usuario
%token<STRING> password
%token<STRING> login
%token<STRING> logout
%token<STRING> mkgrp
%token<STRING> rmgrp
%token<STRING> mkusr
%token<STRING> rmusr
%token<STRING> chmod
%token<STRING> ugo
%token<STRING> ruta
%token<STRING> BF
%token<STRING> FF
%token<STRING> WF
%token<STRING> k
%token<STRING> m
%type<STRING> INIT
%type<STRING> INSTRUCCION
%type<STRING> INSTRUCCIONES
%type<STRING> MKDISKPARAM

%define parse.error verbose
%locations

%union{
    char*STRING;
    char*NUM;
}

%%
INIT:
    INSTRUCCIONES
;

INSTRUCCIONES:
    INSTRUCCIONES INSTRUCCION
    | INSTRUCCION
;

INSTRUCCION:
    mkdisk {mkdiskV = new _MKDISK();} MKDISKP {mkdiskV->exe();/*realiza la creación del disco*/}
    | error {std::cout << "error";}
;

MKDISKP:
    MKDISKP MKDISKPARAM
    | MKDISKPARAM
;

MKDISKPARAM :
        guion size igual numero {mkdiskV->setSize(atoi($4)); cout <<"size is "<<mkdiskV->getSize()<<endl;}
    |   guion f igual BF {mkdiskV->setFit($4); cout <<"Fit is "<<mkdiskV->getFit()<<endl;}
    |   guion f igual FF {mkdiskV->setFit($4); cout <<"Fit is "<<mkdiskV->getFit()<<endl;}
    |   guion f igual WF {mkdiskV->setFit($4); cout <<"Fit is "<<mkdiskV->getFit()<<endl;}
    |   guion u igual k {mkdiskV->setUnit($4); cout <<"Unit is "<<mkdiskV->getUnit()<<endl;}
    |   guion u igual m {mkdiskV->setUnit($4); cout <<"Unit is "<<mkdiskV->getUnit()<<endl;}
    |   guion path igual ruta {mkdiskV->setPath($4); cout <<"Path is "<<mkdiskV->getPath()<<endl;}
    |   guion path igual cadena {mkdiskV->setPath($4); cout <<"Path is "<<mkdiskV->getPath()<<endl;}
;

%%
void yyerror(const char *s)
{
    printf("Error sintactico en la linea %i: %s\n", linea, s);
}
