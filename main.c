/* UFPB - CI - CDIA
Programação Estruturada
Alunos: 
Davi Ribeiro Pereira Pinto - 20200023844
Thalles Emannuel Batista Pinheiro - 20200025580
*/

#include <stdio.h>
#include "matrix.h"

int main(void)
{

    // Array unidimensional original
    int array[] = {1, 2, 3, 4, 5, 6};
    struct matrix x = create_matrix(array, 2, 3);
    printf("Matriz criada com o array {1, 2, 3, 4, 5, 6}, shape(2,3): \n");
    print_matrix(x);

    printf("\n");

    struct matrix zero = zeros_matrix(3, 3);
    printf("Matriz de Zeros:\n");
    print_matrix(zero);

    printf("\n");

    struct matrix random = random_matrix(3, 4, 5, 20);
    printf("Matriz Randomica de 10 a 99, shape(3,4):\n");
    print_matrix(random);

    printf("\n");

    struct matrix i = i_matrix(5);
    printf("Matriz Identidade:\n");
    print_matrix(i);

    printf("\n\n");

    int element = get_element(random, 2, 1);
    printf("ELemento escolhido da matriz Random[2,1], : %d\n", element);

    printf("\n\n");

    put_element(random, 2, 2, 99);
    printf("Matriz Random Alterada na posição (2,2), elemento= 99:\n");
    print_matrix(random);

    printf("\n");

    struct matrix T = transpose(random);
    printf("Matriz Transposta da Random:\n");
    print_matrix(T);

    printf("\n");

    struct matrix reshap = reshape(random, 6, 2);
    printf("Matriz Reshape da Random:\n");
    print_matrix(reshap);

    printf("\n");

    struct matrix flat = flatten(random);
    printf("Matriz Flatten da Random:\n");
    print_matrix(flat);

    printf("\n");

    struct matrix sliced = slice(random, 1, 3, 1, 3);
    printf("Matriz \'Fatiada\' da Random:\nlinha[1,3)\ncoluna[1,3):\n");
    print_matrix(sliced);

    printf("\n");

    int result_sum = sum(x);
    printf("Matriz X:\n");
    print_matrix(x);
    printf("A soma dos elementos da matriz X é: %d\n", result_sum);

    printf("\n");

    float result_mean = mean(x);
    printf("A média dos elementos da matriz X é: %.2f\n", result_mean);

    printf("\n");

    int min_element = min(x);
    printf("O menor elemento da matriz X é: %d\n", min_element);

    printf("\n");

    int max_element = max(x);
    printf("O maior elemento da matriz X é: %d\n", max_element);

    printf("\n\n");

    struct matrix add_matrix = add(x, x);
    printf("Matriz somada(x + x):\n");
    print_matrix(add_matrix);

    printf("\n");

    struct matrix sub_matrix = sub(x, x);
    printf("Matriz subtraida(x - x):\n");
    print_matrix(sub_matrix);

    printf("\n");

    struct matrix div_matrix = division(x, x);
    printf("Matriz dividida(x / x):\n");
    print_matrix(div_matrix);

    printf("\n");

    struct matrix mul_matrix = mul(x, x);
    printf("Matriz multiplicada(x * x):\n");
    print_matrix(mul_matrix);

    printf("\n");

    // Array criado para ser usado na matmul
    struct matrix y = random_matrix(3, 2, 1, 10);
    struct matrix t = random_matrix(2, 4, 5, 10);

    printf("\ny: \n");
    print_matrix(y);
    printf("\n");

    printf("t: \n");
    print_matrix(t);
    printf("\n");

    printf("MatMul(y , t):\n");
    print_matrix(matmul(y, t));
    printf("\n");

    return 0;
}
/*
struct matrix x, y, z, t;
    
    x = random_matrix(3,2,1,10);
    y = random_matrix(3,2,5,15);
    z = random_matrix(5,5,1,10);
    t = random_matrix(2,4,5,10);

    printf("x: \n");
    print_matrix(x);
    printf("\n");
    
    printf("t: \n");
    print_matrix(t);
    printf("\n");
    
    print_matrix( matmul(x,t) );
    printf("\n");
    
    printf("y: \n");
    print_matrix(y);
    printf("\n");
    
    printf("z: \n");
    print_matrix(z);
    printf("\n");
    
    printf("slice(z): \n");
    print_matrix(slice(z,1,4,3,5));
    printf("\n");
    
    printf("get 0,0: ");
    printf("%d", get_element(slice(z,1,4,3,5), 0,0));
    printf("\n");
    
    printf("put 0,0: 171");
    put_element(slice(z,1,4,3,5), 0,0, 171);
    printf("\n\n");
    
    printf("z: \n");
    print_matrix(z);
    printf("\n");
    
    printf("slice(z): \n");
    print_matrix(slice(z,1,4,3,5));
    printf("\n");
    
    printf("y.slice(z) = \n");
    print_matrix( mul( y,slice(z,1,4,3,5) ) );
    printf("\n sum( y.slice(z) ) = %d\n", sum( mul( y,slice(z,1,4,3,5) ) ) );
    printf("\n mean( y.slice(z) ) = %.2f\n", mean( mul( y,slice(z,1,4,3,5) ) ) );
    printf("\n min( y.slice(z) ) = %d\n", min( mul( y,slice(z,1,4,3,5) ) ) );
    printf("\n max( y.slice(z) ) = %d\n", max( mul( y,slice(z,1,4,3,5) ) ) );

    return 0;
} */