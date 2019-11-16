#include <stdio.h>
#include "lista.h"

void mostra_float(void *x);
int compara_float(void *x, void *y);
int disjuntos(Conjuntos c);

int main() {
    int lin, i, j;
    float x;
    printf("Digite o numero de conjuntos: ");
    scanf("%d", &lin);
    Conjuntos m, sub;

    inicializa_conjuntos(&m, sizeof(Conjuntos));
    for (i = 1; i <= lin; i++) {
        inicializa_conjuntos(&sub, sizeof(float));
        printf("Entre um elemento representante 'float' para o conjunto %d: ", i);
        scanf("%f", &x);
        insereNoInicio(&sub, &x);
        insereNoFim(&m, &sub);
        if (!disjuntos(m)) {
            printf("Os conjuntos nao sao disjuntos! Os elementos devem ser diferentes!");
            return 1;
        }
    }

    printf("Dados da matriz:\n");
    for (i = 0; i < lin; i++) {
        leNaPos(&m, &sub, i);
        for (j = 0; j < sub.qtd; j++) {
            leNaPos(&sub, &x, j);
            printf("%f ", x);
        }
        printf("\n");
    }
    // Desalocando
    for (i = 0; i < lin; i++) {
        leNaPos(&m, &sub, i);
        limpa_lista(&sub);
    }
    limpa_lista(&m);

    return 0;
}

void mostra_float(void *x) {
    printf("%f\n", *(float*) x);
}

int compara_float(void *x, void *y) {
    float *a = x, *b = y;
    if (*a > *b) return 1;
    if (*a < *b) return -1;
    return 0;
}

int disjuntos(Conjuntos c) {
    if (c.qtd < 2)
        return 1;
    int i, j, k, l;
    float x, y;
    Conjuntos sub, sub2;
    for (i = 0; i < c.qtd-1; i++) {
        leNaPos(&c, &sub, i);
        for (j = 0; j < sub.qtd; j++) {
            leNaPos(&sub, &x, j);
            for (k = i+1; k < c.qtd; k++) {
                leNaPos(&c, &sub2, k);
                for (l = 0; l < sub2.qtd; l++) {
                    leNaPos(&sub2, &y, l);
                    if (!compara_float(&x, &y))
                        return 0;
                }
            }
        }
    }
    return 1; // sao disjuntos
}
