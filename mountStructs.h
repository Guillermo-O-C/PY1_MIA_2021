#include <iostream>
using namespace std;
#pragma once


struct particionMontada{    
    public:
        char name[16]="";
        int status = 0;
        int numero = 0;
};

struct disco{
    public:
        char letra='0';
        char path[100]="";
        int status=0;
        particionMontada particiones[99];
};

extern disco discosMontados[26];