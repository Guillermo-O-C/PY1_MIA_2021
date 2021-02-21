#include <iostream>
using namespace std;

class partition{
    private:
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];

    public:
    partition(){};
    void setStatus(char status);
    void setType(char type);
    void setFit(char fit);
    void setStart(int start);
    void setSize(int size);
    void setName(char name[16]);
};
void partition::setStatus(char status){
    this->part_status=status;
};
void partition::setType(char type){
    this->part_type=type;
};
void partition::setFit(char fit){
    this->part_fit=fit;
};
void partition::setStart(int start){
    this->part_start=start;
};
void partition::setSize(int size){
    this->part_size=size;
};
void partition::setName(char name[16]){
    this->part_name=name;
};