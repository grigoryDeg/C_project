#include <stdio.h>
#include <stdlib.h>
int main (void)
{
int N = 5;
int i,j,o,p, line;
int A[N][N];
int MASS[N-1][N-1];
int massives[N][N-1][N-1];



FILE *file;
file = fopen("new_file.txt", "w");


/* for(i = 0; i < N; ++i) {
for(j = 0; j < N; ++j) {
scanf("%d", &p);
A[i][j] = p;
}
}
*/

for(i = 0; i < N; ++i) {
for(j = 0; j < N; ++j) {
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

if(j < line + 1) {
MASS[i-1][j] = A[i][j];
printf("%3d ", MASS[i-1][j]);
massives[line][i-1][j] = MASS[i-1][j];

}
else{
MASS[i-1][j-1] = A[i][j];
printf("%3d ", MASS[i-1][j-1]);
massives[line][i-1][j-1] = MASS[i-1][j-1];
}

}
}
puts("\n");


}

printf("\n\n");
}

/*
for(line = 0; line < N; ++line) {
  for(line_little = 0; line_little < N - 1; ++line_little)  {
    for(i = 1; i < N - 1; ++i) {
            for(j = 0; j < N - 2; ++j) {
                if(j != line_little) {
                        if(j < line_little + 1) {
                        MASS_little[i-1][j] = massives[line][i][j];
                        printf("%3d ", MASS_little[i-1][j]);
                        massives_little[line][line_little][i-1][j] = MASS_little[i-1][j];

                    }
                    else {
                        MASS_little[i-1][j-1] = massives[line][i-1][j-1];
                        printf("%3d ", MASS_little[i-1][j-1]);
                        massives_little[line][line_little][i-1][j-1] = MASS_little[i-1][j-1];
                    }
                }
            }
             puts("\n");
    }
     printf("\n\n");
    }
  }
  */

printf(" PROVERKA:\n\n");
for(o = 0; o < N-1; ++o) {
for(p = 0; p < N-1; ++p) {
printf("%3d", massives[4][o][p]);
}
puts("\n");
}


if(file != NULL) {
printf("New file created successfully\n");
fputs("not bad\n", file);
}
else {
fprintf(stderr, "Can not create a file\n");
}
return 0;
}

