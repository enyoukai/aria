CC=gcc
CXX=g++
RM=del
EXT=exe

all:
	$(CXX) *.cpp -o aria 
	./aria.$(EXT)
	$(RM) aria.$(EXT)

# only works on 64 bit linux
asm:
	nasm -felf64 out.asm
	(CC) -static -o out.out out.o
	./out.out

clean:
	$(RM) *.$(EXT) *.o *.asm *.out