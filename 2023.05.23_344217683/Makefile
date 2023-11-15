.PHONY: all clean arc

all: integral

integral: main.o f1.o f2.o f3.o root.o integral.o example.o
	gcc -m32 $^ -lm -o integral.out -no-pie

main.o: main.c root.h integral.h f1.h f2.h f3.h example.h
	gcc -m32 -c $< -lm -o main.o 

f1.o: f1.asm
	nasm -f elf32 $< -o f1.o

f2.o: f2.asm
	nasm -f elf32 $< -o f2.o

f3.o: f3.asm
	nasm -f elf32 $< -o f3.o

%.o: %.c
	gcc -m32 -c $< -o $@

clean:
	-rm *.o integral.out

test: integral
	./integral.out -R 4:5:0.5:1:0.0001:0.8767
	./integral.out -R 5:6:0.1:0.5:0.0001:0.25555
	./integral.out -R 4:6:0.5:1:0.0001:0.63
	./integral.out -I 4:2:10:0.0001:330.666666
	./integral.out -I 5:3.5:4:0.0001:-0.282828
	./integral.out -I 6:2:6:0.0001:3.9561704

arc:
	mkdir -p ARC
	zip `date +%Y.%m.%d_%N`.zip integral.out example.c example.h f1.asm f1.h f2.asm f2.h f3.asm f3.h integral.c integral.h root.c root.h main.c Makefile
	mv *.zip ARC
