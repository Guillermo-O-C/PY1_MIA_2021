%option noyywrap
%option case-insensitive
%option yylineno
%option nounput

%{
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "parser.h"
int linea = 1;
%}

comentario [#]([^\n])* 
numero [-]?[0-9]+
partition_id "66"[0-9]+[A-Z]
cadena \"(\\\"|\\n|\\t|\\r|\\\\|[^\"])*\" 
ruta (([/]([a-zA-Z]|[0-9]|"_"|".")+)+)
id ([a-zA-Z])([a-zA-Z]|[0-9]|"_")*

%%
('\s'|'\r'|'\t')+ {};
"\n" {linea++;};
{comentario} {};
{partition_id} {yylval.STRING = strdup(yytext);return (partition_id);};
{numero} {yylval.STRING = strdup(yytext);return (numero);};
{cadena} {yylval.STRING = strdup(yytext); return (cadena);};
("–"|"-") {yylval.STRING = strdup(yytext);return (guion);};
[=] {yylval.STRING = strdup(yytext);return (igual);};
"mkdisk" {yylval.STRING = strdup(yytext);return (mkdisk);};
"size" {yylval.STRING = strdup(yytext);return (size);};
"f" {yylval.STRING = strdup(yytext);return (f);};
"u" {yylval.STRING = strdup(yytext);return (u);};
"path" {yylval.STRING = strdup(yytext);return (path);};
"rmdisk" {yylval.STRING = strdup(yytext);return (rmdisk);};
"fdisk" {yylval.STRING = strdup(yytext);return (fdisk);};
"type" {yylval.STRING = strdup(yytext);return (type);};
"delete" {yylval.STRING = strdup(yytext);return (delete_);};
"name" {yylval.STRING = strdup(yytext);return (name);};
"add" {yylval.STRING = strdup(yytext);return (add);};
"mount" {yylval.STRING = strdup(yytext);return (mount);};
"unmount" {yylval.STRING = strdup(yytext);return (unmount);};
"mkfs" {yylval.STRING = strdup(yytext);return (mkfs);};
"fs" {yylval.STRING = strdup(yytext);return (fs);};
"usr" {yylval.STRING = strdup(yytext);return (usr);};
"pwd" {yylval.STRING = strdup(yytext);return (pwd);};
"login" {yylval.STRING = strdup(yytext);return (login);};
"logout" {yylval.STRING = strdup(yytext);return (logout);};
"mkgrp" {yylval.STRING = strdup(yytext);return (mkgrp);};
"rmgrp" {yylval.STRING = strdup(yytext);return (rmgrp);};
"mkusr" {yylval.STRING = strdup(yytext);return (mkusr);};
"rmusr" {yylval.STRING = strdup(yytext);return (rmusr);};
"chmod" {yylval.STRING = strdup(yytext);return (chmod);};
"ugo" {yylval.STRING = strdup(yytext);return (ugo);};
"rep" {yylval.STRING = strdup(yytext);return (rep);};
"id" {yylval.STRING = strdup(yytext);return (R_id);};
"ruta" {yylval.STRING = strdup(yytext);return (R_ruta);};
"exec" {yylval.STRING = strdup(yytext);return (exec);};
"pause" {yylval.STRING = strdup(yytext);return (pause_);};
{id} {yylval.STRING = strdup(yytext); return (id);};
{ruta} {yylval.STRING = strdup(yytext); return (ruta);};
. {}
%%