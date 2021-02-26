%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>

#include "scanner.h"
#include "mkdisk.h"
#include "rmdisk.h"
#include "fdisk.h"
#include "rep.h"

using namespace std;
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;
extern void yyerror(const char *s);
extern int linea;

_MKDISK * mkdiskV;
_RMDISK * rmdiskV;
_FDISK * fdiskV;
_REP * repV;
%}

%start INIT

%token<NUM> numero
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
%token<STRING> rep
%token<STRING> R_id
%token<STRING> R_ruta
%token<STRING> partition_id

%type<STRING> INIT
%type<STRING> INSTRUCCION
%type<STRING> INSTRUCCIONES
%type<STRING> MKDISKP
%type<STRING> MKDISKPARAM
%type<STRING> RMDISKP
%type<STRING> RMDISKPARAM
%type<STRING> FDISKP
%type<STRING> FDISKPARAM
%type<STRING> REPP
%type<STRING> REPPARAM

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
    | rmdisk {rmdiskV = new _RMDISK();} RMDISKP {rmdiskV->exe();/*realiza la eliminación del disco*/}
    | fdisk {fdiskV = new _FDISK();} FDISKP {fdiskV->exe();/*realiza la eliminación del disco*/}
    | rep {repV = new _REP();} REPP {repV->exe();/*Imprime los reportes*/}
    | error {std::cout << "error";}
;

MKDISKP:
    MKDISKP MKDISKPARAM
    | MKDISKPARAM
;

MKDISKPARAM :
        guion size igual numero {mkdiskV->setSize(atoi($4));}
    |   guion f igual id {mkdiskV->setFit($4);}
    |   guion u igual id {mkdiskV->setUnit($4);}
    |   guion path igual ruta {mkdiskV->setPath($4, false);}
    |   guion path igual cadena {mkdiskV->setPath($4, true);}
;

RMDISKP:
    RMDISKP RMDISKPARAM
    | RMDISKPARAM
;

RMDISKPARAM :
        guion path igual ruta {rmdiskV->setPath($4, false);}
    |   guion path igual cadena {rmdiskV->setPath($4, true);}
;

FDISKP:
    FDISKP FDISKPARAM
    | FDISKPARAM
;

FDISKPARAM :
        guion size igual numero {fdiskV->setSize(atoi($4));}
    |   guion u igual id {fdiskV->setUnit($4);}
    |   guion type igual id {fdiskV->setType($4);}
    |   guion f igual id {fdiskV->setFit($4);}
    |   guion delete_ igual id {fdiskV->setDelete($4);}
    |   guion name igual id {fdiskV->setName($4, false);}
    |   guion name igual cadena {fdiskV->setName($4, true);}
    |   guion add igual numero {fdiskV->setAdd(atoi($4));}
    |   guion path igual ruta {fdiskV->setPath($4, false);}
    |   guion path igual cadena {fdiskV->setPath($4, true);}
;

REPP:
    REPP REPPARAM 
    | REPPARAM
;

REPPARAM:
        guion name igual id {repV->setName($4);}
    |   guion path igual cadena {repV->setPath($4, true);}
    |   guion path igual ruta {repV->setPath($4, false);}
    |   guion R_id igual id {repV->setId($4);}
    |   guion R_id igual partition_id {repV->setId($4);}
    |   guion R_ruta igual ruta {repV->setRuta($4);}
;
%%
void yyerror(const char *s)
{
    printf("Error sintactico en la linea %i: %s\n", linea, s);
}
