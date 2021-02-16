
echo "Bison-------------------------"
bison -o parser.cpp --defines=parser.h gramatica.y
echo "Flex--------------------------"
flex -o scanner.cpp --header-file=scanner.h lexico.l
echo "Compilación Completada."
g++ main.cpp parser.cpp scanner.cpp -o main