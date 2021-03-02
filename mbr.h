#include <iostream>
#pragma once
#include "partition.h"
using namespace std;

struct MBR {
    public:
        int mbr_disk_signature=0;
        char disk_fit='F';
        partition mbr_partition_1;
        partition mbr_partition_2;
        partition mbr_partition_3;
        partition mbr_partition_4;
        int mbr_tamanio=0;
        char mbr_fecha_creacion[16]="";
};
