#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include "rc4.c"
#include "crc32.c"
#include "elf.c"

int main(int argc, char *argv[]) {

    if(argc < 3) {
        printf("Usage: %s <elf> <key>", argv[0]);
        return -1;
    }

    char* data;
	int fd;
	struct stat st;
	off_t offset;
	int size;
	
	if ( stat(argv[1],&st) == -1 ) {
		perror("stat");
		exit(-1);
	}
	
	if ( NULL == (data = malloc(st.st_size))) {
		perror("malloc");
		exit(-2);
	}
	
	if ( 0 < (fd = open(argv[1], O_RDWR ))) {
		read(fd, data, st.st_size);
		if ( get_elf_section( ".upx" , data , st.st_size , &offset , &size )) {
	    printf("Not found\n");
		}
        #ifdef DEBUG 
        else {
	    printf("offset = %lu; size = %u\n",offset, size);
		}
        #endif
	}

    size_t need_size, page_size;

    page_size = sysconf(_SC_PAGESIZE);

	need_size = (st.st_size + (page_size - 1 )) & (~(page_size-1));

    lseek(fd, 0, SEEK_SET);

    unsigned char *ptr = mmap(NULL, need_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if ( MAP_FAILED == ptr ) {
        perror("mmap");
        close(fd);
        return __LINE__;
    }

    unsigned char *ciphertext = malloc(size - 4);

    RC4(argv[2], ptr + offset, ciphertext, size - 4);

    int crc = crc32(ptr + offset, size-4);

#ifdef DEBUG
    printf("source: ");
    for(int i = 0; i < size - 4; i++)
        printf("%02X", ptr[offset + i]);

    printf("\nciphertext: ");
    for(size_t i = 0; i < size-4; i++) {
        printf("%02X", ciphertext[i]);
    }

    unsigned char *deciphertext = malloc(size - 4);

    RC4(argv[2], ciphertext, deciphertext, size - 4);

    printf("\ndeciphertext: ");
    for(size_t i = 0; i < size-4; i++) {
        printf("%02X", deciphertext[i]);
    } 
    
    printf("\nCRC32: %08X", crc);

#endif

    memcpy(ptr + offset, ciphertext, size-4);
    *(int*)(ptr+offset+size - 4) = crc;

    munmap(ptr, need_size);
    close(fd);
    free(data);
    free(ciphertext);
    free(deciphertext);
	return 0;
}
