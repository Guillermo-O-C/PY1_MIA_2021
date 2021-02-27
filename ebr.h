#include <iostream>
using namespace std;

struct EBR{
    public:
        char part_status='0';
        char part_fit='W';
        int part_start=-1;
        int part_size=0;
        int part_next=-1;
        char part_name[16]="";
};