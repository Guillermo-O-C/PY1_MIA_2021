#include <iostream>
using namespace std;

struct particionMontada{    
    public:
        char path[100]="";
        char name[16]="";
        void setPath(string path, bool isCadena);
        void setName(string name, bool isCadena);
};
struct disco{
    public:
        char letra='0';
        char path[100]="";
        int status=0;
        particionMontada particiones[99];
};

extern disco discosMontados[26];