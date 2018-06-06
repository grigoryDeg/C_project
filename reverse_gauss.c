#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define N 4
#define MAX_NUM_LENGTH 10 //with minus

typedef struct {
    int num; //÷èñëèòåëü
    int denom; //çíàìåíàòåëü
}frac; //fraction - äðîáü, ëîë

int** readM();
void show_intM(int** ptM, int sizeM, char* text);
int** cutM(int row, int col, int** ptM);
int find(int* mass, int size, int quest);
void sum_strM(int str1, int str2, frac coeff, frac** pfrM, int sizestr);
frac** intM_to_fracM(int sizeM, int** ptM);
void show_fracM(frac** pfrM, int rows, int cols, char* text);
void extendingM(frac** pfrM, int sizeM);
void zeroing(FILE *pf, frac** pfrM, int rows, int cols); //size - num of rows
int eukl_NOD(int a, int b);
void swap_strM(int str1, int str2, frac** pfrM);
void reduc_frac(frac** frac_ptr_mass, int mass_size); //ñîêðàùåíèå äðîáåé
void make_invM(frac** pfrM, int rows, int cols);
frac sum_frac(frac fr1, frac fr2);
frac div_frac(frac fr1, frac fr2);
frac mult_frac(frac fr1, frac fr2);
frac create_frac(int num, int denom);
void checking_det_det(int** ptM, int sizeM);
void zero_issue(int problem_str, frac** pfrM, int rows, int cols);
void print_matrix(FILE *pfile ,int** pA, int rows, int cols);
void print_matrix_frac(FILE *pfile, frac** pfrM, int rows, int cols);

int main(){
    FILE *pf;
    pf = fopen("new_file.tex", "w");
    int **ptM = readM();
    int detM;
    if (ptM != NULL){
        show_intM(ptM, N, "");
        if (checking_det(ptM, N) == 0){
            printf("The determinant of this matrix is zero, so it's impossible to find invers of it.\n");
            exit(EXIT_SUCCESS);
        }
        else {
            if(pf != NULL) {
                printf("New file created successfully\n");
                fputs("\\documentclass{article}\n", pf);
                fputs("\\usepackage[utf8]{inputenc}\n", pf);
                fputs("\\usepackage[russian]{babel}\n", pf);
                fputs("\\usepackage{amsmath}\n", pf);
                fputs("\\usepackage{hyperref}\n", pf);
                fputs("\\newenvironment{comment}{}{}\n", pf);
                fputs("\\textwidth= 18 cm\n", pf);
                fputs("\\oddsidemargin= -0.5 cm\n", pf);
                fputs("\\mathsurround=2pt\n", pf);
                fputs("\\renewcommand{\\baselinestretch}{2.0}\n", pf);
                fputs("\\begin{document}\n", pf);
                fputs("\\title{Task 2; Raschetka 3}\n", pf);
                fputs("\\date{}\n", pf);
                fputs("\\maketitle\n", pf);
                    printf("Determinant of the Matrix is not null, so we'll continue...\n");
                    printf("HERE WE GO\n\n");
                        fputs("\\noindent Matrix of integers:\\\\[6pt] \n", pf);
                        fputs("$\n", pf);
                        print_matrix(pf, ptM, N, N);
                        fputs("$\\\\[6pt] \n", pf);
                    frac** pfrM = intM_to_fracM(N, ptM);
                    extendingM(pfrM, N);
                    show_fracM(pfrM, N, N*2 , "Gauss matrix\n");
                        fputs("Gauss matrix:\\\\[6pt] \n", pf);
                        print_matrix_frac(pf, pfrM, N, 2*N);
                    zeroing(pf, pfrM, N, N*2);
                    make_invM(pfrM, N, N*2); //sizes of extended Matrix
                        fputs("Now we're deviding each row to coefficients we need\\\\[6pt] \n", pf);
                    show_fracM(pfrM, N, N, "And finally, we have the Matrix:\n");
                        fputs("And finally, we have the Matrix:\\\\[6pt] \n", pf);
                    print_matrix_frac(pf, pfrM, N, N);
                        fputs("\\end{document}\n", pf);
            }
            else {
                fprintf(stderr, "Can not create a file\n");
            }
        }
    }
    else{
        printf("ptM is NULL.\n");
    }
        fclose(pf);
}

int** readM(){
    char answer; //'f' - file or 'c' - console
    printf("Where is Matrix will be taken from?(FILE(f/c)CONSOLE)\n");
    scanf("%c", &answer);
    int **ptM = malloc(N * sizeof(int*));
    int i, j, k, num_cntr = 0;
    if(answer == 'c'){
        for(i=0;i<N;i++){
            ptM[i] = malloc(N * sizeof(int));
            for(j=0;j<N;j++){
                printf("Enter %d %d:", i, j);
                scanf("%d", &ptM[i][j]);
            }
        }
    }
    else if(answer == 'f'){
        printf("Extracting from file:\n");
        char filename[] = "M.txt",
            symb,
            box[MAX_NUM_LENGTH]; //it's char massive for long (more than one symbol) numbers
        int fst_c_of_n = 0; //value of 'j' (pos in string) at first char of current num
        printf("\tOpening file...\n");
        FILE *FwithM = fopen(filename, "r");
        if (FwithM != NULL){
            printf("\tReading from file...\n");
            for(i=0;i<N;i++){
                ptM[i] = malloc(N * sizeof(int));
                num_cntr = 0;
                for(j=0;num_cntr<N;j++){ //N+1 because of \n in the end of every string
                    symb = fgetc(FwithM);
                    if ((symb >= 48 && symb <= 57) || symb ==45){
                        if (fst_c_of_n == -1)//45 - '-', 48 - '0', 57 - '9', 10 - '\n'
                            fst_c_of_n = j;
                        box[j-fst_c_of_n] = symb;
                    }
                    else{
                        ptM[i][num_cntr] = atoi(box);
                        num_cntr++;

                        for (k=0;k<MAX_NUM_LENGTH;k++)
                            box[k] = 't';

                        fst_c_of_n = -1;
                    }
            }
        }
    }
        else{
            printf("File wasn't opened. We'll stop 'readM'.\n");
            return NULL;
        }
    }
    else{
        printf("Something goes wrong and you enter not 'f' or 'c'. We'll stop 'readM'.\n");
        printf("answer %c\n", answer);
        return NULL;
    }
    return ptM;
}

void show_intM(int** ptM, int sizeM, char* text){
    if (text == "")
        printf("\nThe Matrix of integers:\n");
    else{
        printf("%s", text);
    }
    int i, j;
    for(i=0;i<sizeM;i++){
        for(j=0;j<sizeM;j++)
            printf("%d ", ptM[i][j]);
        printf("\n");
    }
    printf("\n");
}

int** cutM(int row, int col, int** ptM){
    int i, j,
        rec_cntr = 0,
        ctN = N - 1, //cuted N
        **ptcM = malloc(ctN * sizeof(int*)); // pointer to cuted Matrix
    for (i=0;i<N;i++){
        ptcM[i] = malloc(ctN * sizeof(int));
        for(j=0;j<N;j++){
            if (i != row && j != col){
                ptcM[rec_cntr / ctN][rec_cntr % ctN] = ptM[i][j];
                rec_cntr++;
            }
        }
    }
    return ptcM;
}

int find(int* mass, int size, int quest){
    int i;
    for(i = 0; i<size;i++)
        if (mass[i] == quest)
            return i;
    return -1;
}

int checking_det(int** ptM, int sizeM){
    int i, j, cff, box,
        det = 0,
        minor = 0;
    if(sizeM != 2){
        for(j=0;j<sizeM;j++){
            if ((i+j) % 2)
                cff = -1;
            else
                cff = 1;
            minor = checking_det(cutM(0, j, ptM), sizeM-1);
            box = det;
            det += cff * ptM[0][j] * minor;
        }
    }
    else
        det = ptM[0][0] * ptM[1][1] - ptM[0][1] * ptM[1][0];
    return det;
}

frac** intM_to_fracM(int sizeM, int** ptM){
    int i, j;
    frac **pfrM = malloc(sizeM * sizeof(frac*));
    for (i=0;i<sizeM;i++){
        pfrM[i] = malloc(sizeM * sizeof(frac));
        for (j=0;j<sizeM;j++){
            pfrM[i][j].num = ptM[i][j];
            pfrM[i][j].denom = 1;
        }
    }
    return pfrM;
}

void show_fracM(frac** pfrM, int rows, int cols, char* text){
    if (text == "")
        printf("\nThe Matrix of fractions:\n");
    else{
        printf("%s", text);
    }
    int i, j;
    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++)
            printf("%d/%d ", pfrM[i][j].num, pfrM[i][j].denom);
        printf("\n");
    }
    printf("\n");
}

void sum_strM(int str1, int str2, frac coeff, frac** pfrM, int sizestr){
    int i;
    for (i=0;i<sizestr;i++){
        pfrM[str1][i] = sum_frac(pfrM[str1][i], div_frac(pfrM[str2][i], coeff));
    }
}

void extendingM(frac** pfrM, int sizeM){
    int i, j;
    for (i=0;i<sizeM;i++){
        pfrM[i] = realloc(pfrM[i], sizeM*2 * sizeof(frac));
        for (j=0;j<sizeM*2;j++){
            if (j >= sizeM)
                if (i+sizeM == j){
                    pfrM[i][j].num = 1;
                    pfrM[i][j].denom = 1;
                }
                else{
                    pfrM[i][j].num = 0;
                    pfrM[i][j].denom = 1;
                }
        }
    }
}

int eukl_NOD(int a, int b){
    a = abs(a);
    b = abs(b);
    while (a != 0 && b != 0){
        if (a > b)
            a = a % b;
        else
            b = b % a;
    }
    return a + b;
}

void swap_strM(int str1, int str2, frac** pfrM){
    frac *box = pfrM[str1];
    pfrM[str1] = pfrM[str2];
    pfrM[str2] = box;
}

void reduc_frac(frac** frac_ptr_mass, int mass_size){
    int i, NOD;
    for (i=0;i<mass_size;i++){
        NOD = eukl_NOD(frac_ptr_mass[i][0].num, frac_ptr_mass[i][0].denom);
        frac_ptr_mass[i][0].num /= NOD;
        frac_ptr_mass[i][0].denom /= NOD;
    }
}

frac sum_frac(frac fr1, frac fr2){
    if (fr1.denom == fr2.denom)
        fr1.num += fr2.num;
    else{
        fr1.num = fr1.num * fr2.denom + fr2.num * fr1.denom;
        fr1.denom *= fr2.denom;
    }
    frac* mass[] = {&fr1};
    reduc_frac(mass, 1);
    return fr1;
}

frac div_frac(frac fr1, frac fr2){
    if (fr2.num == 0){
        printf("Divison by zero.\n");
        exit(EXIT_FAILURE);
    }
    fr1.num *= fr2.denom;
    fr1.denom *= fr2.num;
    frac* mass[] = {&fr1};
    reduc_frac(mass, 1);
    if(fr1.denom < 0){
        fr1.num = -fr1.num;
        fr1.denom = -fr1.denom;
    }
    return fr1;
}

frac mult_frac(frac fr1, frac fr2){
    fr1.num *= fr2.num;
    fr1.denom *= fr2.denom;
    frac* mass[] = {&fr1};
    reduc_frac(mass, 1);
    return fr1;
}

frac create_frac(int num, int denom){
    frac box;
    box.num = num;
    box.denom = denom;
    return box;
}

void zeroing(FILE *pf, frac** pfrM, int rows, int cols){
    int i, j, k;
    frac cff;

    vse_zanovo:
    for (i=0;i<cols/2;i++){
        if (pfrM[i][i].num == 0){
            zero_issue(i, pfrM, rows, cols);
            goto vse_zanovo;
        }
        for (j=0;j<rows;j++){
            if (j != i){
                if (pfrM[j][i].num == 0)
                    continue;
                cff = div_frac(pfrM[i][i], pfrM[j][i]);
                printf("We're subtracting %d from %d string with coefficient %d/%d\n", j+1, i+1, cff.num, cff.denom);
                fprintf(pf,"We're subtracting %d from %d string with coefficient %d/%d: \n", j+1, i+1, cff.num, cff.denom);
                cff.num = -cff.num; //for vychitanie strok
                sum_strM(j, i, cff, pfrM, cols);
                show_fracM(pfrM, rows, cols, "Result:\n");
                print_matrix_frac(pf, pfrM, rows, cols);
            }
        }
    }

    for(i=0;i<rows;i++){
        cff = div_frac(create_frac(1, 1), pfrM[i][i]);
        for (j=0;j<cols;j++)
            pfrM[i][j] = mult_frac(pfrM[i][j], cff);
    }
}

void make_invM(frac** pfrM, int rows, int cols){
    int i, j,
        true_size = cols/2;
    frac *box;
    for (i=0;i<rows;i++){
        box = malloc(true_size * sizeof(frac));
        for (j=true_size;j<cols;j++)
            box[j-true_size] = pfrM[i][j];
        pfrM[i] = box;
    }
}

void zero_issue(int problem_str, frac** pfrM, int rows, int cols){
    int k;
    for (k=0;k<rows;k++){
        printf("swap_loop %d %d %d\n", problem_str, k, pfrM[k][problem_str].num);
        if (pfrM[k][problem_str].num != 0 && pfrM[problem_str][k].num != 0){
            swap_strM(problem_str, k, pfrM);
            printf("We just have swaped %d è %d strings.\n", k+1, problem_str+1);
            show_fracM(pfrM, rows, cols, "The Matrix after the swap:\n");
        }
    }
}

void print_matrix(FILE *pfile ,int** pA, int rows, int cols) {
    fputs("\\begin{vmatrix}\n", pfile);
    for(int i=0; i<rows; ++i){
        for(int j=0; j<cols; ++j) {
            if( j != cols - 1) {
                // printf("%i ", pA[i][j]);
                fprintf(pfile, "%i & ", pA[i][j]);
            }
            else{
                 // printf("%i ", pA[i][j]);
                fprintf(pfile, "%i\\\\ ", pA[i][j]);
            }
            }
        //printf("\n");
        fprintf(pfile, "\n");
    }
    fputs("\\end{vmatrix}\n", pfile);
}

void print_matrix_frac(FILE *pfile, frac** pfrM, int rows, int cols){
    int i, j;
    fputs("$\n", pfile);
    fputs("\\begin{vmatrix}\n", pfile);
    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++) {
            if(j != cols - 1) {
                fprintf(pfile, "\\tfrac{%d}%d & ", pfrM[i][j].num, pfrM[i][j].denom);
            }
            else{
                fprintf(pfile, "\\tfrac{%d}%d\\\\\n", pfrM[i][j].num, pfrM[i][j].denom);
            }
        }
        fprintf(pfile, "\n");
    }
    fputs("\\end{vmatrix}\n", pfile);
    fputs("$\\\\[6pt] \n",pfile);
}








