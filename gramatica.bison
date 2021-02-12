%{ 
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <cstring> // strerror
# include <string>
# include "driver.hh"
# include "parser.hh"
%}

%option noyywrap nounput noinput batch debug

//gramatica
id [a-zA-Z][A-zA-Z_0-9]*
number [0-9]+
string \"(\\\"|\\n|\\t|\\r|\\\\|[^\"])*\" 

/*
tokens

mkdisk
-size
-f
-u
-path
rmdisk
fdisk
-type
-delete
-name
-add
mount
unmount
mkfs
-id
-fs
-usuario
-password
login
logout
mkgrp
rmgrp
mkusr
rmusr
chmod
-ugo
-rmdisk
mkfile
-cont
cat
-filen
rem
edit
ren
mkdir
cp
-dest
mv
find
?
*
-usr
-grp
-chgrp
mbr_tamano
mbr_fecha_creacion
mbr_disk_signature
disk_fit
mbr_partition_1
mbr_partition_2
mbr_partition_3
mbr_partition_4
part_status
part_type
part_fit
part_start
part_size
part_name
part_next
s_filesystem_type
s_inodes_count
s_blocks_count
s_free_blocks_count
s_free_inodes_count
s_mtime
s_umtime
s_mnt_count
s_magic
s_inode_size
s_block_size
s_first_ino
s_first_blo
s_bm_inode_start
s_bm_blovk_start
s_inode_start
s_block_start
i_uid
i_gid
i_size
i_atime
i_ctime
i_mtime
i_block
i_type
i_perm
b_content
b_name
b_inodo
b_content
b_pointers
-ruta
rep

*/