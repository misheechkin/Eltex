obj-m += chardev.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

main:
	gcc main.c -o main.out

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm main.out