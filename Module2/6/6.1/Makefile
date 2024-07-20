object: 
	gcc -c social_network.c work_info.c contact.c list.c person.c 
lib: 
	ar rc libPhoneBook.a contact.o list.o person.o social_network.o work_info.o
execute:
	gcc main.c input.c -o main.out -L. -lPhoneBook
