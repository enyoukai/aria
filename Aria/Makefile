CC=gcc
CXX=g++
RM=rm -f
EXT=exe

all:
	$(CXX) *.cpp -o aria 
	./aria.$(EXT)
	$(RM) aria.$(EXT)

# only works on 64 bit linux
asm:
	nasm -felf64 aria.asm
	$(CC) -static -o aria.out aria.o
	./aria.out

clean:
	$(RM) *.$(EXT) *.o *.out