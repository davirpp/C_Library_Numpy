/* UFPB - CI - CDIA
Programação Estruturada
Alunos: 
Davi Ribeiro Pereira Pinto - 20200023844
Thalles Emannuel Batista Pinheiro - 20200025580
*/

#ifndef MATRIX_H
#define MATRIX_H

struct matrix {
    int *data;
    int n_rows;
    int n_cols;
    int stride_rows;
    int stride_cols;
    int offset;
};

struct matrix create_matrix(int *data, int n_rows, int n_cols);

struct matrix zeros_matrix(int n_rows, int n_cols);

struct matrix random_matrix(int n_rows, int n_cols, int b, int e);

struct matrix i_matrix(int n);

int get_element(struct matrix a_matrix, int ri, int ci);

void put_element(struct matrix a_matrix, int ri, int ci, int elem);

void print_matrix(struct matrix a_matrix);

struct matrix transpose(struct matrix a_matrix);

struct matrix reshape(struct matrix a_matrix, int new_n_rows, int new_n_cols);

struct matrix flatten(struct matrix a_matrix);

struct matrix slice(struct matrix a_matrix, int rs, int re, int cs, int ce);

int sum(struct matrix a_matrix);

float mean(struct matrix a_matrix);

int min(struct matrix a_matrix);

int max(struct matrix a_matrix);

struct matrix add(struct matrix a_matrix, struct matrix b_matrix);

struct matrix sub(struct matrix a_matrix, struct matrix b_matrix);

struct matrix division(struct matrix a_matrix, struct matrix b_matrix);

struct matrix mul(struct matrix a_matrix, struct matrix b_matrix);

struct matrix matmul(struct matrix a_matrix, struct matrix b_matrix);
#endif