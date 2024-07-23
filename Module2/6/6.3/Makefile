object:
	gcc -fPIC -c ./lib/div.c ./lib/mult.c ./lib/sub.c ./lib/sum.c 
libDiv: 
	 gcc -shared div.o -o lib_Div.so
libSum: 
	 gcc -shared sum.o -o lib_Sum.so
libSub: 
	 gcc -shared sub.o -o lib_Sub.so
libMult: 
	 gcc -shared mult.o -o lib_Mult.so
execute:
	gcc main.c -o main.out -ldl && ./main.out

