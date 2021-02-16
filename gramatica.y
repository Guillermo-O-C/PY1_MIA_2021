%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include "scanner.h"
using namespace std;
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;
extern void yyerror(const char *s);
extern int linea;
%}

%start INIT

%token<NUM> numero
%token<NUM> negativo
%token<STRING> cadena
%token<STRING> guion
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

%type<STRING> INIT
%type<STRING> INSTRUCCION
%type<STRING> INSTRUCCIONES
%type<STRING> MKPARAM

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
    mkdisk MKDISKP {cout << "mkdisk";}
    | error {std::cout << "error";}
;

MKDISKP:
    MKDISKP MKPARAM
    | MKPARAM
;

MKPARAM :
        guion size {cout << "size";}
    |   guion f {cout << "f";}
    |   guion u {cout << "u";}
    |   guion path {std::cout << "path";}
;

%%
void yyerror(const char *s)
{
    printf("Error sintactico en la linea %i: %s\n", linea, s);
}
