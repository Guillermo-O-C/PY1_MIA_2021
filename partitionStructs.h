#include <iostream>
#pragma once
using namespace std;
struct SB {
    int s_filesystem_type=-1;
    int s_inodes_count=-1;
    int s_blocks_count=-1;
    int s_free_blocks_count=-1;
    int s_free_inodes_count=-1;
    char s_mtime[16]="";
    char s_umtime[16]="";
    int s_mnt_count=-1;
    int s_magic=-1;
    int s_inode_size=-1;
    int s_block_size=-1;
    int s_first_ino=-1;//Primer inodo libre
    int s_first_blo=-1;//Primer bloque libre
    int s_bm_inode_start=-1;
    int s_bm_block_start=-1;
    int s_inode_start=-1;
    int s_block_start=-1;
};

struct inode{
    int i_uid=1;
    int i_gid=1;
    int i_size=0;
    char i_atime[16]="";
    char i_ctime[16]="";
    char i_mtime[16]="";//ultima edición
    int i_block[15]={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    char i_type='0';
    int i_perm=664;
};

struct content
{
    char b_name[12]="";
    int b_inodo=-1;
};

struct folder_block {
    content b_content[4];
};

struct file_block {
    char b_content[64]="";
};

struct pointers {
    int b_pointers[16]={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
};

struct Journaling
{
    char tipo_operacion[10] = "";
    char tipo = '\0';
    char path[60] = "";
    char contenido[100] = "";
    char log_fecha[16] = "";
    int size = 0;
    int nextAvailable(FILE * search, int partStart){
        SB superBloque;
        fseek(search, partStart, SEEK_SET);
        fread(&superBloque, sizeof(SB), 1, search);
        Journaling temp;
        for(int i =0;i<superBloque.s_inodes_count;i++){
            fseek(search, partStart+sizeof(SB)+i*sizeof(Journaling), SEEK_SET);
            fread(&temp, sizeof(Journaling), 1, search);
            if(temp.tipo!='1' && temp.tipo!='2' && temp.tipo!='3' && temp.tipo!='4' && temp.tipo!='5'){//posición disponible
                return i;
            }
        }
        return 0;
    }
};