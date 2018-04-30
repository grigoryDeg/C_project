#include <stdio.h>
#include <stdlib.h>
int main (void)
{
int N = 5;
int i,j,p, line;
int A[N][N];
int MASS[N-1][N-1];


FILE *file;
file = fopen("new_file.txt", "w");


//for(i = 0; i < N; ++i) {
//for(j = 0; j < N; ++j) {
   //     scanf("%d", &p);
   //     A[i][j] = p;
//}
//}
for(i = 0; i < N; ++i) {
    for(j = 0; j < N; ++j){
            A[i][j] = rand() % 30 + 1;
         printf("%3d ",A[i][j]);
    }
    puts("\n");
}
printf("\n\n");
for(line = 0; line < N; ++line) {
for(i = 1; i < N; ++i) {
            for(j = 0; j < N; ++j) {
                    if(j != line) {
                MASS[i][j] = A[i][j];
            printf("%3d ",MASS[i][j]);
            }
        }
        puts("\n");

}
printf("\n\n");
}

if(file != NULL) {
        printf("New file created successfully\n");
        fputs("Fuck you nigga\n", file);
}
else{
    fprintf(stderr, "Can not create a file\n");
}
return 0;
}
