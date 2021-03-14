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
#include "exec.h"
#include "mount.h"
#include "mkfs.h"
#include "login.h"
#include "mkdir.h"
#include "mkfile.h"
#include "ssl.h"
#include "ren.h"

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
_EXEC * execV;
_MOUNT * mountV;
_MKFS * mkfsV;
_LOGIN *loginV;
_MKDIR *mkdirV;
_MKFILE *mkfileV;
_SSL * sslV;
_REN * renV;
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
%token<STRING> p
%token<STRING> r
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
%token<STRING> usr
%token<STRING> pwd
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
%token<STRING> exec
%token<STRING> pause_
%token<STRING> mkdir
%token<STRING> mkfile
%token<STRING> cont
%token<STRING> loss
%token<STRING> recovery
%token<STRING> ren

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
%type<STRING> MOUNTP
%type<STRING> MOUNTPARAM
%type<STRING> MKFSP
%type<STRING> MKFSPARAM
%type<STRING> LOGINP
%type<STRING> LOGINPARAM
%type<STRING> MKDIRP
%type<STRING> MKDIRPARAM
%type<STRING> MKFILEP
%type<STRING> MKFILEPARAM
%type<STRING> RENP
%type<STRING> RENPARAM

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
    | exec guion path igual cadena {execV = new _EXEC(); execV->setPath($5, true); execV->exe();}
    | exec guion path igual ruta {execV = new _EXEC(); execV->setPath($5, false); execV->exe();}
    | pause_ {cout << "\nLa ejecución del script se ha pausado, por favor presiona cualquier tecla para continuar."<<endl; cin.get();}
    | mount {mountV = new _MOUNT();} MOUNTP {mountV->exe();/*realiza la eliminación del disco*/}
    | unmount guion R_id igual partition_id {mountV->unmount($5); }
    | mkfs {mkfsV = new _MKFS();} MKFSP {mkfsV->exe();}
    | mkdir {mkdirV = new _MKDIR();} MKDIRP {mkdirV->exe();}
    | login {loginV = new _LOGIN();} LOGINP {loginV->exe();}
    | logout {loginV->logout();} 
    | mkfile {mkfileV = new _MKFILE();} MKFILEP {mkfileV->exe();}
    | ren {renV = new _REN();} RENP {renV->exe();}
    | loss guion R_id igual partition_id {sslV = new _SSL(); sslV->setId($5); sslV->simulateLoss();}
    | recovery guion R_id igual partition_id {sslV->setId($5); sslV->simulateRecovery();}
    | error {} 
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
    |   guion type igual p {fdiskV->setType($4);}
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
    |   guion R_ruta igual ruta {repV->setRuta($4, false);}
    |   guion R_ruta igual cadena {repV->setRuta($4, true);}
;

MOUNTP:
    MOUNTP MOUNTPARAM
    | MOUNTPARAM
;

MOUNTPARAM :
        guion name igual id {mountV->setName($4, false);}
    |   guion name igual cadena {mountV->setName($4, true);}
    |   guion path igual ruta {mountV->setPath($4, false);}
    |   guion path igual cadena {mountV->setPath($4, true);}
;

MKFSP:
    MKFSP MKFSPARAM
    | MKFSPARAM
;

MKFSPARAM :
        guion R_id igual partition_id {mkfsV->setId($4);}
    |   guion type igual id {mkfsV->setType($4);}
    |   guion fs igual numero fs {mkfsV->setFs(atoi($4)); }
;

LOGINP:
    LOGINP LOGINPARAM
    | LOGINPARAM
;

LOGINPARAM :
        guion R_id igual partition_id {loginV->setId($4);}
    |   guion usr igual id {loginV->setUsr($4, false);}
    |   guion usr igual cadena {loginV->setUsr($4, true);}
    |   guion pwd igual id {loginV->setPwd($4,"", false); }
    |   guion pwd igual numero id {loginV->setPwd($4,$5, false); }
    |   guion pwd igual numero {loginV->setPwd($4,"", false); }
    |   guion pwd igual cadena {loginV->setPwd($4,"", true); }
;

MKDIRP:
    MKDIRP MKDIRPARAM
    | MKDIRPARAM
;

MKDIRPARAM :
        guion p {mkdirV->setP();}
    |   guion path igual ruta {mkdirV->setPath($4, false);}
    |   guion path igual cadena {mkdirV->setPath($4, true);}
;

MKFILEP:
    MKFILEP MKFILEPARAM
    | MKFILEPARAM
;

MKFILEPARAM :
        guion r {mkfileV->setR();}
    |   guion path igual ruta {mkfileV->setPath($4, false);}
    |   guion path igual cadena {mkfileV->setPath($4, true);}
    |   guion size igual numero {mkfileV->setSize(atoi($4));}
    |   guion cont igual ruta {mkfileV->setCont($4, false);}
    |   guion cont igual cadena {mkfileV->setCont($4, true);}
;

RENP:
    RENP RENPARAM
    | RENPARAM
;

RENPARAM :
        guion path igual ruta {renV->setPath($4, false);}
    |   guion path igual cadena {renV->setPath($4, true);}
    |   guion name igual id {renV->setName($4, false);}
    |   guion name igual cadena {renV->setName($4, true);}
;
%%
void yyerror(const char *s)
{
    printf("Error sintactico en la linea %i: %s\n", linea, s);
}
