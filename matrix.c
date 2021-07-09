/* UFPB - CI - CDIA
Programação Estruturada
Alunos: 
Davi Ribeiro Pereira Pinto - 20200023844
Thalles Emannuel Batista Pinheiro - 20200025580
*/

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*********************************

Funções para criação de matrizes

**********************************/

struct matrix create_matrix(int *data, int n_rows, int n_cols) {
    struct matrix matriz;

    matriz.data = malloc((n_rows * n_cols) * sizeof(int));
    for (int i = 0; i < (n_rows * n_cols); i++) {
        matriz.data[i] = data[i];
    }
    matriz.n_rows = n_rows;
    matriz.n_cols = n_cols;
    matriz.offset = 0;
    matriz.stride_cols = 1;
    matriz.stride_rows = n_cols;

    return matriz;
}


struct matrix zeros_matrix(int n_rows, int n_cols) {

    struct matrix zeros_m;
    int n_elements = (n_rows * n_cols);
    int *array = malloc(n_elements * sizeof(int));

    for (int i = 0; i < n_elements; i++) {
        array[i] = 0;
    }

    zeros_m = create_matrix(array, n_rows, n_cols);
    return zeros_m;
}


struct matrix random_matrix(int n_rows, int n_cols, int b, int e) {

    struct matrix random_m;
    int n_elements = n_rows * n_cols;
    int *array = malloc(n_elements * sizeof(int));

    srand(time(0));
    for (int i = 0; i < n_elements; i++) {
        array[i] = (rand() % (e - b + 1)) + b; //intervalo[b, e]
    }

    random_m = create_matrix(array, n_rows, n_cols);
    return random_m;
}


struct matrix i_matrix(int n){
    struct matrix i_m;
    i_m = zeros_matrix(n, n);
    for (int i = 0; i < n * n; i += (n + 1)) {
        i_m.data[i] = 1;
    }
    return i_m;
}


/******************************

Funções para acessar elementos

*******************************/

int get_element(struct matrix a_matrix, int ri, int ci){
    
    int first_line = a_matrix.offset / a_matrix.stride_rows;
    int first_column = (a_matrix.offset - first_line * a_matrix.stride_rows) / a_matrix.stride_cols;
    
    int position = ((first_line + ri) * a_matrix.stride_rows) + ((first_column + ci) * a_matrix.stride_cols);
    return a_matrix.data[position];
}


void put_element(struct matrix a_matrix, int ri, int ci, int elem){
    
    int first_line = a_matrix.offset / a_matrix.stride_rows;
    int first_column = (a_matrix.offset - first_line * a_matrix.stride_rows) / a_matrix.stride_cols;
    
    int position = ((first_line + ri) * a_matrix.stride_rows) + ((first_column + ci) * a_matrix.stride_cols);
    
    a_matrix.data[position] = elem;
}


int count_numbers(int num); //Função usada para contar algarismos

void print_matrix(struct matrix a_matrix) {
    
    int *array = a_matrix.data;
    int biggest = max(a_matrix);

    int first_line = floor(a_matrix.offset / a_matrix.stride_rows);
    int first_column = (a_matrix.offset - first_line * a_matrix.stride_rows) / a_matrix.stride_cols;

    for (int i = first_line; i < a_matrix.n_rows + first_line; i++) {
        printf("|");
        for (int j = first_column; j < a_matrix.n_cols + first_column; j++) {
            printf(" %*d ", count_numbers(biggest), array[(i * a_matrix.stride_rows) + (j * a_matrix.stride_cols)]);
        }
        printf("|\n");
    }
}


/*************************************

Funções para manipulação de dimensões

**************************************/

struct matrix transpose(struct matrix a_matrix) {
    struct matrix T_m;
    T_m.data = a_matrix.data;
    T_m.n_rows = a_matrix.n_cols;
    T_m.n_cols = a_matrix.n_rows;
    T_m.stride_rows = a_matrix.stride_cols;
    T_m.stride_cols = a_matrix.stride_rows;
    T_m.offset = 0;
    
    return T_m;
}


struct matrix reshape(struct matrix a_matrix, int new_n_rows, int new_n_cols) {

    int n_elements = (a_matrix.n_rows * a_matrix.n_cols);

    if (n_elements == (new_n_rows * new_n_cols)) {
        a_matrix.n_rows = new_n_rows;
        a_matrix.n_cols = new_n_cols;
        a_matrix.stride_rows = a_matrix.n_cols;
    }
    else {
        int new_linha, new_coluna;
        while(1) {
            printf("\nA quantidade de elementos nao é igual. Tente novamente...\n");
            printf("\nDigite a quantidade de linhas do seu array redimensionado: ");
            scanf("%d", &new_linha);

            printf("\nDigite a quantidade de colunas do seu array redimensionado: ");
            scanf("%d", &new_coluna);

            if (n_elements == (new_linha * new_coluna)) {
                break;
            }   
        }
        a_matrix.n_rows = new_linha;
        a_matrix.n_cols = new_coluna;
        a_matrix.stride_rows = a_matrix.n_cols;
    }

    return a_matrix;
}


struct matrix flatten(struct matrix a_matrix) {

    int *array = a_matrix.data;
    int n_elements = (a_matrix.n_rows * a_matrix.n_cols);
    a_matrix.n_rows = 1;
    a_matrix.n_cols = n_elements;
    a_matrix.stride_rows = n_elements;

    return a_matrix;
}


struct matrix slice(struct matrix a_matrix, int rs, int re, int cs, int ce) {
    struct matrix s_m;
    s_m.data = a_matrix.data;
    s_m.n_rows = re - rs;
    s_m.n_cols = ce - cs;
    s_m.stride_rows = a_matrix.stride_rows;
    s_m.stride_cols = a_matrix.stride_cols;
    s_m.offset = (rs * s_m.stride_rows) + (cs * s_m.stride_cols);
    
    return s_m;
}


/**********************

Funções de agregação

***********************/

int sum(struct matrix a_matrix) {

    int position;
    
    int first_line = a_matrix.offset / a_matrix.stride_rows;
    int first_column = (a_matrix.offset - first_line * a_matrix.stride_rows) / a_matrix.stride_cols;
    
    int soma = 0;
    
    for (int i = 0; i < a_matrix.n_rows; i++) {
        for (int j = 0; j < a_matrix.n_cols; j++) {
            position = ((i + first_line) * a_matrix.stride_rows) + ((j + first_column) * a_matrix.stride_cols);
            soma += a_matrix.data[position];
        }
    }
    
    return soma;
}


float mean(struct matrix a_matrix) {

    int n_elements = a_matrix.n_rows * a_matrix.n_cols;
    float soma = sum(a_matrix);
    float media = soma / n_elements ;
    return media;
}


int min(struct matrix a_matrix) {

    int position;
    
    int first_line = a_matrix.offset / a_matrix.stride_rows;
    int first_column = (a_matrix.offset - first_line * a_matrix.stride_rows) / a_matrix.stride_cols;
 
    position = (first_line) * a_matrix.stride_rows + (first_column) * a_matrix.stride_cols;
    int menor = a_matrix.data[position];
    
    for (int i = 0; i < a_matrix.n_rows; i++) {
        for (int j = 0; j < a_matrix.n_cols; j++) {
            position = ((i + first_line) * a_matrix.stride_rows) + ((j + first_column) * a_matrix.stride_cols);
            if (a_matrix.data[position] < menor){
                menor = a_matrix.data[position];
            }
        }
    }
    
    return menor;
}


int max(struct matrix a_matrix) {

    int position;
    
    int first_line = a_matrix.offset / a_matrix.stride_rows;
    int first_column = (a_matrix.offset - first_line * a_matrix.stride_rows) / a_matrix.stride_cols;
    
    position = (first_line) * a_matrix.stride_rows + (first_column) * a_matrix.stride_cols;
    int maior = a_matrix.data[position];
    
    for (int i = 0; i < a_matrix.n_rows; i++) {
        for (int j = 0; j < a_matrix.n_cols; j++) {
            position = ((i + first_line) * a_matrix.stride_rows) + ((j + first_column) * a_matrix.stride_cols);
            if (a_matrix.data[position] > maior){
                maior = a_matrix.data[position];
            }
        }
    }
    
    return maior;
}


/********************************

Funções de operações aritméticas

*********************************/

struct matrix add(struct matrix a_matrix, struct matrix b_matrix) {

    struct matrix add_m;
    int n_elements = a_matrix.n_rows * a_matrix.n_cols;
    int *array = malloc(n_elements * sizeof(int));
    
    int position_a, position_b;
    int a_first_line, a_first_column, b_first_line, b_first_column;

    if ((a_matrix.n_rows == b_matrix.n_rows) && (a_matrix.n_cols == b_matrix.n_cols)) {

        a_first_line = a_matrix.offset / a_matrix.stride_rows;
        a_first_column = (a_matrix.offset - a_first_line * a_matrix.stride_rows) / a_matrix.stride_cols;
        
        b_first_line = b_matrix.offset / b_matrix.stride_rows;
        b_first_column = (b_matrix.offset - b_first_line * b_matrix.stride_rows) / b_matrix.stride_cols;
        
        int pos = 0;
        
        for (int i = 0; i < a_matrix.n_rows; i++) {
            for (int j = 0; j < a_matrix.n_cols; j++) {
                position_a = ((i + a_first_line) * a_matrix.stride_rows) + ((j + a_first_column) * a_matrix.stride_cols);
                position_b = ((i + b_first_line) * b_matrix.stride_rows) + ((j + b_first_column) * b_matrix.stride_cols);
                array[pos++] = a_matrix.data[position_a] + b_matrix.data[position_b];
            }
        }
        
        add_m = create_matrix(array, a_matrix.n_rows, a_matrix.n_cols);
        return add_m;
    }

    else {
        printf("\nAs duas matrizes nao contem o mesmo numero \nde linhas e colunas. Tente novamente...\n");
    }
}


struct matrix sub(struct matrix a_matrix, struct matrix b_matrix) {

    struct matrix sub_m;
    int n_elements = a_matrix.n_rows * a_matrix.n_cols;
    int *array = malloc(n_elements * sizeof(int));
    
    int position_a, position_b;
    int a_first_line, a_first_column, b_first_line, b_first_column;

    if ((a_matrix.n_rows == b_matrix.n_rows) && (a_matrix.n_cols == b_matrix.n_cols)) {

        a_first_line = a_matrix.offset / a_matrix.stride_rows;
        a_first_column = (a_matrix.offset - a_first_line * a_matrix.stride_rows) / a_matrix.stride_cols;
        
        b_first_line = b_matrix.offset / b_matrix.stride_rows;
        b_first_column = (b_matrix.offset - b_first_line * b_matrix.stride_rows) / b_matrix.stride_cols;
        
        int pos = 0;
        
        for (int i = 0; i < a_matrix.n_rows; i++) {
            for (int j = 0; j < a_matrix.n_cols; j++) {
                position_a = ((i + a_first_line) * a_matrix.stride_rows) + ((j + a_first_column) * a_matrix.stride_cols);
                position_b = ((i + b_first_line) * b_matrix.stride_rows) + ((j + b_first_column) * b_matrix.stride_cols);
                array[pos++] = a_matrix.data[position_a] - b_matrix.data[position_b];
            }
        }
        
        sub_m = create_matrix(array, a_matrix.n_rows, a_matrix.n_cols);
        return sub_m;
    }

    else {
        printf("\nAs duas matrizes nao contem o mesmo numero \nde linhas e colunas. Tente novamente...\n");
    }
}


struct matrix division(struct matrix a_matrix, struct matrix b_matrix) {

    struct matrix div_m;
    int n_elements = a_matrix.n_rows * a_matrix.n_cols;
    int *array = malloc(n_elements * sizeof(int));
    
    int position_a, position_b;
    int a_first_line, a_first_column, b_first_line, b_first_column;

    if ((a_matrix.n_rows == b_matrix.n_rows) && (a_matrix.n_cols == b_matrix.n_cols)) {

        a_first_line = a_matrix.offset / a_matrix.stride_rows;
        a_first_column = (a_matrix.offset - a_first_line * a_matrix.stride_rows) / a_matrix.stride_cols;
        
        b_first_line = b_matrix.offset / b_matrix.stride_rows;
        b_first_column = (b_matrix.offset - b_first_line * b_matrix.stride_rows) / b_matrix.stride_cols;
        
        int pos = 0;
        
        for (int i = 0; i < a_matrix.n_rows; i++) {
            for (int j = 0; j < a_matrix.n_cols; j++) {
                position_a = ((i + a_first_line) * a_matrix.stride_rows) + ((j + a_first_column) * a_matrix.stride_cols);
                position_b = ((i + b_first_line) * b_matrix.stride_rows) + ((j + b_first_column) * b_matrix.stride_cols);
                array[pos++] = a_matrix.data[position_a] / b_matrix.data[position_b];
            }
        }
        
        div_m = create_matrix(array, a_matrix.n_rows, a_matrix.n_cols);
        return div_m;
    }

    else {
        printf("\nAs duas matrizes nao contem o mesmo numero \nde linhas e colunas. Tente novamente...\n");
    }
}


struct matrix mul(struct matrix a_matrix, struct matrix b_matrix) {

    struct matrix mul_m;
    int n_elements = a_matrix.n_rows * a_matrix.n_cols;
    int *array = malloc(n_elements * sizeof(int));
    
    int position_a, position_b;
    int a_first_line, a_first_column, b_first_line, b_first_column;

    if ((a_matrix.n_rows == b_matrix.n_rows) && (a_matrix.n_cols == b_matrix.n_cols)) {

        a_first_line = a_matrix.offset / a_matrix.stride_rows;
        a_first_column = (a_matrix.offset - a_first_line * a_matrix.stride_rows) / a_matrix.stride_cols;
        
        b_first_line = b_matrix.offset / b_matrix.stride_rows;
        b_first_column = (b_matrix.offset - b_first_line * b_matrix.stride_rows) / b_matrix.stride_cols;
        
        int pos = 0;
        
        for (int i = 0; i < a_matrix.n_rows; i++) {
            for (int j = 0; j < a_matrix.n_cols; j++) {
                position_a = ((i + a_first_line) * a_matrix.stride_rows) + ((j + a_first_column) * a_matrix.stride_cols);
                position_b = ((i + b_first_line) * b_matrix.stride_rows) + ((j + b_first_column) * b_matrix.stride_cols);
                array[pos++] = a_matrix.data[position_a] * b_matrix.data[position_b];
            }
        }
        
        mul_m = create_matrix(array, a_matrix.n_rows, a_matrix.n_cols);
        return mul_m;
    }

    else {
        printf("\nAs duas matrizes nao contem o mesmo numero \nde linhas e colunas. Tente novamente...\n");
    }
}


struct matrix matmul(struct matrix a_matrix, struct matrix b_matrix){
    struct matrix matmul_m;
    int n_elements = a_matrix.n_rows * b_matrix.n_cols;
    int *array = malloc(n_elements * sizeof(int) );
    
    if (a_matrix.n_cols == b_matrix.n_rows) {
        int a_first_line, a_first_column, b_first_line, b_first_column;
        
        a_first_line = a_matrix.offset / a_matrix.stride_rows;
        a_first_column = (a_matrix.offset - a_first_line * a_matrix.stride_rows) / a_matrix.stride_cols;
        
        struct matrix b_transpose = transpose(b_matrix);  
        b_first_line = b_transpose.offset / b_transpose.stride_rows;
        b_first_column = (b_transpose.offset - b_first_line * b_transpose.stride_rows) / b_transpose.stride_cols;
        
        struct matrix a_slice, b_slice;
        
        int x = 0;
        for (int i = a_first_line; i < a_matrix.n_rows + a_first_line; i++){
            a_slice = slice(a_matrix, i, i+1, a_first_column, a_first_column + a_matrix.n_cols);
            for (int j = b_first_line ; j < b_transpose.n_rows + b_first_line; j++){
                b_slice = slice(b_transpose, j, j+1, b_first_column, b_first_column + b_transpose.n_cols);    
                array[x++] = sum(mul(a_slice, b_slice));          
            }
        }
        
        matmul_m = create_matrix(array, a_matrix.n_rows, b_matrix.n_cols);
        return matmul_m; 
    }
    else{
        printf("\nNúmero de colunas da Matriz A diferente de número de linhas da Matriz B\nTente novamente assim: A[m,n] x B[n,p] = C[m,p]\n");
    }
}


/************************************************************

Função para contar algarismos e criar espaço no print_matrix

*************************************************************/

int count_numbers(int num) {
    int count = 0;
    while(num != 0) {  
        num = num / 10;  
        count++;  
    }  
    return count;  
}