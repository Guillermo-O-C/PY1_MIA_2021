#include <iostream>
#pragma once
using namespace std;

struct partition{
    public:
    char part_status='0';
    char part_type='P';
    char part_fit='W';
    int part_start=-1;
    int part_size=0;
    char part_name[16]="";
};