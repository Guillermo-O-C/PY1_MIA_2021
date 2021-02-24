#include <iostream>
#pragma once
#include "partition.h"
using namespace std;

class MBR {
    private:
        int mbr_tamanio;
        char mbr_fecha_creacion[16];
        int mbr_disk_signature;
        char disk_fit;
        partition mbr_partition_1;
        partition mbr_partition_2;
        partition mbr_partition_3;
        partition mbr_partition_4;

    public:
        MBR(){};
        void setTamanio(int tamanio);
        void setTime(char * tiempo);
        void setSignature(int signature);
        void setFit(char fit);
        void setPartition(partition partition, int Pnumber);
};

void MBR::setTamanio(int tamanio){
    this->mbr_tamanio=tamanio;
};
void MBR::setTime(char * tiempo){
    strcpy(this->mbr_fecha_creacion, tiempo);
};
void MBR::setSignature(int signature){
    this->mbr_disk_signature=signature;
};
void MBR::setFit(char fit){
    this->disk_fit=fit;
};
void MBR::setPartition(partition partition, int Pnumber){
    switch (Pnumber)
    {
    case 1:
        this->mbr_partition_1=partition;
        break;
    case 2:
        this->mbr_partition_2=partition;
        break;
    case 3:
        this->mbr_partition_3=partition;
        break;
    case 4:
        this->mbr_partition_4=partition;
        break;
    }
};

