#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int **matrix_1;
int **matrix_2;
int i = 0, j = 0,k = 0;
int line_matrix_1 = 0,column_1 = 0;
int line_matrix_2 = 0,column_2 = 0;
int c;
int res = 0;

int line;
int column;
int **matrix_3;

int main(int argc,char* argv[]) 
{
    
    FILE *matrex_file;
    FILE *matrex_file_2;

    if ((matrex_file = fopen(argv[1],"r")) == NULL){
		printf("file error\n");
		getchar();
		exit(EXIT_SUCCESS);
		//return 0;

	}
	//setbuf(matrex_file,buffer);
	// узнаем размеры матрцицы
	while((c = fgetc(matrex_file)) != EOF){
		if (c == '\n'){
			//printf("%c",buffer[j]);
			++line_matrix_1;
			if ((i += 1) > column_1){
				column_1  = i;
			}
			i = 0;
		}
		if(c == ' '){
			i++;
		
		}
	}
	printf("%d\n",column_1);
	fclose(matrex_file);

	// создаем массив под первую матрицу

    matrix_1 = (int**) malloc(line_matrix_1 * sizeof(int*));
 
    for (i = 0; i < line_matrix_1; i++) {
        matrix_1[i] = (int*) malloc(column_1 * sizeof(int));
    }
	
    if ((matrex_file = fopen(argv[1],"r")) == NULL){
		printf("file error\n");
		getchar();
		exit(EXIT_SUCCESS);
		//return 0;
	}

    //считываем косячную матрицу
    for(i = 0; i < line_matrix_1; i++){
    	for(j = 0; j < column_2; j++){
    		matrix_1[i][j] = 0;
    	}
    }


    c = 0;
    i = 0;
    j = 0;
    c = fgetc(matrex_file);
    // обнулить массив на всякий 
    while(c != EOF && c != '\n'){
 			if(c != ' ' && c != '\n' && c != EOF){
 				res = res * 10 +c - 48;
 				//printf("res: %d",res);
 				c = fgetc(matrex_file);

 			}

 			if(c == ' ' || c == '\n' || c == EOF){
 				matrix_1[i][j] = res;
 				printf("matrix_1[%d][%d] = %d\n",i,j,matrix_1[i][j]);
 				res = 0;
 				j++;
 				if(c == EOF || c == '\n'){
 					for(j ;j < column_1;j++){
 						matrix_1[i][j] = 0;
 					}
 					j = 0;
 					i ++;
 				}

 				if(c == EOF){
 					break;
 				}

 				c = fgetc(matrex_file);
 			}
 		}

	fclose(matrex_file);
	//освобождает матрицу
	for(i = 0; i < line_matrix_1; i++){
		for (j = 0; j < column_1;j++){
			printf("%d",matrix_1[i][j]);
		}
		printf("\n");
	}    
    if ((matrex_file_2 = fopen(argv[2],"r")) == NULL){
		printf("file error\n");
		getchar();
		exit(EXIT_SUCCESS);
		//return 0;

	}
	c = 0;
    i = 0;
    j = 0;
	//setbuf(matrex_file_2,buffer);
	// узнаем размеры матрцицы
	while((c = fgetc(matrex_file_2)) != EOF){
		if (c == '\n'){
			//printf("%c",buffer[j]);
			++line_matrix_2;
			if ((i += 1) > column_2){
				column_2  = i;
			}
			i = 0;
		}
		if(c == ' '){
			i ++;
		
		}
	}
	fclose(matrex_file_2);

	// создаем массив под первую матрицу

    matrix_2 = (int**) malloc(line_matrix_2 * sizeof(int*));
 
    for (i = 0; i < line_matrix_2; i++) {
        matrix_2[i] = (int*) malloc(column_2 * sizeof(int));
    }
	
    if ((matrex_file_2 = fopen(argv[2],"r")) == NULL){
		printf("file error\n");
		getchar();
		exit(EXIT_SUCCESS);
		//return 0;
	}
	 for(i = 0; i < line_matrix_2; i++){
    	for(j = 0; j < column_2; j++){
    		matrix_2[i][j] = 0;
    	}
    }


    //считываем косячную матрицу
    c = 0;
    i = 0;
    j = 0;
    res = 0;
    c = fgetc(matrex_file_2);
    while(c != EOF && c != '\n'){
 			if(c != ' ' && c != '\n' && c != EOF){
 				res = res * 10 +c - 48;
 				//printf("res: %d",res);
 				c = fgetc(matrex_file_2);

 			}

 			if(c == ' ' || c == '\n' || c == EOF){
 				matrix_2[i][j] = res;
 				printf("matrix_2[%d][%d] = %d\n",i,j,matrix_2[i][j]);
 				res = 0;
 				j++;
 				if(c == EOF || c == '\n'){
 					for(j ;j < column_2;j++){
 						matrix_2[i][j] = 0;
 					}
 					j = 0;
 					i ++;
 				}

 				if(c == EOF){
 					break;
 				}

 				c = fgetc(matrex_file_2);
 			}
 		}

	fclose(matrex_file_2);
	//освобождает матрицу
	printf("column_2:%d\n",column_2);
	printf("line_matrix_2:%d\n",line_matrix_2);
	printf("column_1:%d\n",column_1);
	printf("line_matrix_1:%d\n",line_matrix_1);
	
	
	for(i = 0; i < line_matrix_1; i++){
		for (j = 0; j < column_1;j++){
			printf("%d ",matrix_1[i][j]);
		}
		printf("\n");
	}

	for(i = 0; i < line_matrix_2; i++){
		for (j = 0; j < column_2;j++){
			printf("%d ",matrix_2[i][j]);
		}
		printf("\n");
	}

	printf("%d\n",line_matrix_2);
	printf("%d\n",column_1);
	k = 0;
	line = line_matrix_1;
	column = column_2;
   
    matrix_3 = (int**) malloc(line * sizeof(int*)); 
    for (i = 0; i < line; i++) {
        matrix_3[i] = (int*) malloc(column * sizeof(int));
    }
    printf("\n");
    for(i = 0; i < line; i++){
    	for(j = 0; j < column; j++){
    		matrix_3[i][j] = 0;
    	}
    }


  	
    for (i = 0; i < (line/2); i++){
		for(j = 0; j <= (column/2); j++){
			for (k = 0; k < line; k++){
				matrix_3[i][j] = matrix_3[i][j] + matrix_1[i][k]*matrix_2[k][j];
				printf("matrix_3[%d][%d] = %d\n",i,j,matrix_3[i][j]);
			}
			
		}
		
	}
	printf("\n%d\n", column);
	for (i = line/2; i < line; i++){
		for(j = (column/2) - 1; j < column; j++){
			for (k = 0; k < line; k++){
				matrix_3[i][j] = matrix_3[i][j] + matrix_1[i][k]*matrix_2[k][j];
				printf("matrix_3[%d][%d] = %d\n",i,j,matrix_3[i][j]);
			}
			
		}
		
	}

	FILE *matrex_file_3;
  	matrex_file_3 = fopen(argv[3],"a+");

  	for(i = 0; i<line;i++){
  		for(j = 0;j<column;j++){
  			fprintf(matrex_file_3, "%d ", matrix_3[i][j]);
  		}
  		fprintf(matrex_file_3,"%c",'\n');
  	}
  	fclose(matrex_file_3);
	for (i = line_matrix_1-1; i > 0; i--) {
        free(matrix_1[i]);
    }
    free(matrix_1);

    for (i = line_matrix_2-1; i > 0; i--) {
        free(matrix_2[i]);
    }
    free(matrix_2);

    for (i = line-1; i > 0; i--) {
        free(matrix_3[i]);
    }
    free(matrix_3);
    return 0;
}