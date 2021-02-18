#include <iostream>
using namespace std;

class _MKDISK{
    private:
        int size;
        string f;
        string path;
        string u;
    public:
        _MKDISK(){};
        void setSize(int size);
        void setFit(string f);
        void setPath(string path);
        void setUnit(string u);
        int getSize();
        string getFit();
        string getPath();
        string getUnit();
        void exe();
};
void _MKDISK::setSize(int size){
    this->size = size;
};
void _MKDISK::setFit(string f){
    this->f = f;
};
void _MKDISK::setPath(string path){
    this->path = path;
};
void _MKDISK::setUnit(string u){
    this->u = u;
};
int _MKDISK::getSize(){
    return this->size;
};
string _MKDISK::getFit(){
    return this->f;
};
string _MKDISK::getPath(){
    return this->path;
};
string _MKDISK::getUnit(){
    return this->u;
};
void _MKDISK::exe(){
cout << "creating disk..."<<endl;
}