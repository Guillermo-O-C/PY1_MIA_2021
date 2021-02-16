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
numero [0-9]+
negativo [-][0-9]+
cadena \"(\\\"|\\n|\\t|\\r|\\\\|[^\"])*\" 
ruta ([a-zA-Z])([a-zA-Z]|0-9|"_")*(\/([a-zA-Z])([a-zA-Z]|0-9|"_")*)*
id ([a-zA-Z])([a-zA-Z]|0-9|"_")*

%%
('\s'|'\r'|'\t')+ {};
"\n" {linea++;};
{comentario} {};
{numero} {yylval.STRING = strdup(yytext);return (numero);};
{negativo} {yylval.STRING = strdup(yytext);return (negativo);};
{cadena} {yylval.STRING = strdup(yytext); return (cadena);};
[-] {yylval.STRING = strdup(yytext);return (guion);};
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
"id" {yylval.STRING = strdup(yytext);return (id);};
"fs" {yylval.STRING = strdup(yytext);return (fs);};
"usuario" {yylval.STRING = strdup(yytext);return (usuario);};
"password" {yylval.STRING = strdup(yytext);return (password);};
"login" {yylval.STRING = strdup(yytext);return (login);};
"logout" {yylval.STRING = strdup(yytext);return (logout);};
"mkgrp" {yylval.STRING = strdup(yytext);return (mkgrp);};
"rmgrp" {yylval.STRING = strdup(yytext);return (rmgrp);};
"mkusr" {yylval.STRING = strdup(yytext);return (mkusr);};
"rmusr" {yylval.STRING = strdup(yytext);return (rmusr);};
"chmod" {yylval.STRING = strdup(yytext);return (chmod);};
"ugo" {yylval.STRING = strdup(yytext);return (ugo);};
{id} {yylval.STRING = strdup(yytext); return (id);};
{ruta} {yylval.STRING = strdup(yytext); return (ruta);};
. {}
%%