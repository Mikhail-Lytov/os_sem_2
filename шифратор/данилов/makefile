all: elf.c main.c upx_start.asm upx_end.asm cipher.c crc32.c rc4.c
		nasm -f elf64 upx_start.asm
		nasm -f elf64 upx_end.asm
		gcc -o main.exe upx_start.o main.c upx_end.o
		gcc cipher.c -DDEBUG -o ./Cipher.exe
clean:
		rm -f *.exe *.o
