#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

#include "crc32.c"
#include "rc4.c"

void __attribute__((section(".upx"))) hello_world()
{
  char hello_str[] = "Hello, World!\n";
  printf(hello_str);
}

extern char upx_end;
extern char upx_start;

char* decrypt_upx(char* password)
{
  size_t size_section = (&upx_end) - (&upx_start);
  unsigned char *deciphertext = malloc(size_section);
  unsigned char *ciphertext = malloc(size_section);

  #ifdef DEBUG
  printf("size: %ld\n", size_section);
  #endif

  RC4(password, &upx_start, deciphertext, size_section);

  if(crc32(deciphertext, size_section) == *(int*)(&upx_end))
  {
    memcpy(ciphertext, &upx_start, size_section);
    memcpy(&upx_start, deciphertext, size_section);
  }
  else 
  {
    printf("Invalid password\n");
    free(ciphertext);
    return NULL;
  }
    
	free(deciphertext);
  return ciphertext;
}

int main(int argc, char *argv[])
{
  if(argc < 2) {
    printf("Usage: %s <key>", argv[0]);
    return -1;
  }

  int page_size = sysconf(_SC_PAGE_SIZE);

  #ifdef DEBUG
  printf("page size: %d\n", page_size);
  printf("start = %p , end = %p\n", &upx_start, &upx_end); 
  #endif  

  void *ptr;
  ptr = &upx_start;
  ptr -= ((off_t)ptr) & (page_size - 1);
  if ((-1) == mprotect((void*)ptr , page_size , PROT_READ|PROT_WRITE|PROT_EXEC)) {
    perror("mprotect");
    exit(-1);
  }

  char* ciphertext = decrypt_upx(argv[1]);
  if(ciphertext != NULL)
  {
    hello_world();
    memcpy(&upx_start, ciphertext, (&upx_end) - (&upx_start));
    free(ciphertext);
  }

  return 0;
}
