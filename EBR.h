#include <iostream>
using namespace std;

class EBR{
    private:
    char part_status;
    char part_fit;
    int part_start;
    int part_next;
    char part_name[16];

    public:
    ERB(){};
    void setStatus(char status);
    void setFit(char fit);
    void setStart(int start);
    void setNext(int next);
    void setName(char name[16]);
}

void EBR::setStatus(char status){
    this->part_status=status;
};
void EBR::setFit(char fit){
    this->part_fit=fit;
};
void EBR::setStart(int start){
    this->part_start=start;
};
void EBR::setNext(int next){
    this->part_next=next;
};
void EBR::setName(char name[16]){
    this->part_name=name;
};