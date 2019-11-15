#include "lista.h"

void mostra_float(void *x);
int compara_float(void *x, void *y);

int main() {
    int lin, col, i, j, x;
    printf("Digite o numero de linhas e o numero de colunas: ");
    scanf("%d %d", &lin, &col);
    Conjuntos m, sub;

    inicializa_conjuntos(&m, sizeof(Conjuntos));
    for (i = 0; i < lin; i++) {
        inicializa_conjuntos(&sub, sizeof(int));
        for (j = 0; j < col; j++) {
            printf("Entre um valor para a coordenada %d, %d: ", i, j);
            scanf("%d", &x);
            insereNoFim(&sub, &x);
        }
        insereNoFim(&m, &sub);
    }
    printf("Dados da matriz:\n");
    for (i = 0; i < lin; i++) {
        leNaPos(&m, &sub, i);
        for (j = 0; j < col; j++) {
            leNaPos(&sub, &x, j);
            printf("%d ", x);
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

