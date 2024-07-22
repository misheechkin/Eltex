object:
	gcc -fPIC -c contact.c list.c person.c work_info.c social_network.c
lib: 
	gcc -shared contact.o list.o person.o social_network.o work_info.o -o libPhoneBook.so
execute:
	gcc  main.c input.c -L. -lPhoneBook -o main.out
libpath:
	export LD_LIBRARY_PATH=.
