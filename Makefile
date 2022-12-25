CC=gcc
CXX=g++
RM=del
EXT=exe

all:
	$(CXX) src/*.cpp -o aria 
	./aria.$(EXT)
	$(RM) aria.$(EXT)

# only works on 64 bit linux
asm:
	nasm -felf64 aria.asm
	$(CC) -static -o aria aria.o
	./aria

asm_win:
	nasm -felf64 aria.asm
	$(CC) -static -o aria.exe aria.o
	./aria.exe

clean:
	$(RM) *.$(EXT) *.o *.out