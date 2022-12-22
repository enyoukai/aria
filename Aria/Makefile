all:
	
asm:
	nasm -felf64 aria.asm
	gcc -static -o aria aria.o
	./aria

clean:
	del *.exe *.o *.asm