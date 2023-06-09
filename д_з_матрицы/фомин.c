#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>

void mul_one();
void mul_two();
void start();
long long **MatrixA, **MatrixB, **MatrixC, stolbA=1, stolbB=1, lineA=0, lineB=0, temp=0;

int main(int argc, char* argv[]){
char c;
    if(argc < 3){
        fprintf(stderr, "use 3 params\n");
        return 1;
    }
    FILE *FileMatrixA, *FileMatrixB;
    FileMatrixA = fopen(argv[1], "r");
    if(FileMatrixA == NULL){
      fprintf(stderr, "error open file\n");
      return 2;
    }
// Заполнение первого массива
    fscanf(FileMatrixA, "%c", &c);
    while(c != '\n'){
      fscanf(FileMatrixA, "%c", &c);
      if(c == ' '){
          stolbA++;
      }
    }
    while(!feof(FileMatrixA)){
      fscanf(FileMatrixA, "%c", &c);
      if(c == '\n'){
          lineA++;
      }
    }
    rewind(FileMatrixA);

    MatrixA = ((long long  **)malloc(lineA * sizeof(long long*)));
    for(long long i = 0; i < lineA; i++) {
       MatrixA[i] = ((long long *)malloc((i+1) * sizeof(long long)));
    }
    for ( long long i=0; i<lineA; ++i){
      for (long long j=0; j<stolbA; ++j){
            fscanf(FileMatrixA, "%lld", &temp);
            MatrixA[i][j] = temp;
        }
    }

  fclose(FileMatrixA);
// Заполнение второго массива
  FileMatrixB = fopen(argv[2], "r");
  if(FileMatrixB == NULL){
    fprintf(stderr, "error open file\n");
    return 2;
  }
  fscanf(FileMatrixB, "%c", &c);
  while(c != '\n'){
    fscanf(FileMatrixB, "%c", &c);
    if(c == ' '){
        stolbB++;
    }
  }
  while(!feof(FileMatrixB)){
    fscanf(FileMatrixB, "%c", &c);
    if(c == '\n'){
        lineB++;
    }
  }
  rewind(FileMatrixB);
  MatrixB = ((long long  **)malloc(lineB * sizeof(long long*)));
  for(long long i = 0; i < lineB; i++) {
     MatrixB[i] = ((long long *)malloc((i+1) * sizeof(long long)));
  }
  for ( long long i=0; i<lineB; ++i){
    for (long long j=0; j<stolbB; ++j){
          fscanf(FileMatrixB, "%lld", &temp);
          //printf("%lld\n", temp);
          MatrixB[i][j] = temp;
      }
  }
fclose(FileMatrixB);
MatrixC = ((long long  **)malloc(stolbA * sizeof(long long*)));
for(long long i = 0; i < lineB; i++) {
   MatrixC[i] = ((long long *)malloc((i+1) * sizeof(long long)));
}

  pthread_t thread_start;
  pthread_create(&thread_start,NULL,start,argv);
  pthread_join(thread_start,NULL);


  FILE *FileMatrixC;
  FileMatrixC = fopen(argv[3], "a+");

  for(long long i=0; i<stolbA; i++){
           for (long long j=0; j<lineB; j++){
       fprintf(FileMatrixC, "%lld ", MatrixC[i][j]);
       }
   fprintf(FileMatrixC,"%c",'\n');
   }

   fclose(FileMatrixC);

free(MatrixA);
free(MatrixB);
free(MatrixC);
return 0;
}
void start(char **argv){
  pthread_t mul1;
  pthread_t mul2;

  pthread_create(&mul1,NULL,mul_one,argv);
  pthread_join(mul1, NULL);
  pthread_create(&mul2,NULL,mul_two,argv);
  pthread_join(mul2, NULL);
}
void mul_one(char **argv){
  for(long long k=0; k<(lineA/2); k++){
    for(long long i=0; i<(stolbB/2); i++){
      MatrixC[k][i] = 0;
        for(long long j=0; j<lineB; j++){
          MatrixC[k][i] += MatrixA[k][j]*MatrixB[j][i];
      }
    }
  }
}
void mul_two(char **argv){
  for(long long k=(lineA/2)-1; k<lineA; k++){
    for(long long i=(stolbB/2)-1; i<stolbB; i++){
      MatrixC[k][i] = 0;
      for(long long j=0; j<lineB; j++){
        MatrixC[k][i] += MatrixA[k][j]*MatrixB[j][i];
      }
    }
  }
}