#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

void mostra_int(void *x);
int compara_int(void *x, void *y);
int disjuntos(Conjuntos c);
void mostra_tudoXXX(Conjuntos m);
void destroiTudo(Conjuntos m);

int main() {
    int lin, i, x, op, rep, cont;
    printf("Digite o numero de conjuntos: ");
    scanf("%d", &lin);
    Conjuntos m;
    int rep1, rep2;

    inicializa_conjuntos(&m, sizeof(Conjuntos));
    for (i = 1; i <= lin; i++) {
        printf("Entre um elemento representante 'int' para o conjunto %d: ", i);
        scanf("%d", &x);
        if (cria_conjunto(&m, &x, compara_int) == ERRO_ELEMENTOREPETIDO) {
            printf("Os elementos devem ser diferentes!");
            return 0;
        }
    }

    mostra_tudoXXX(m);

    while (1) {
        printf("\nEscolha uma opcao:\n[1] Unir conjuntos\n[2] Mostrar conjuntos\n[3] Remover conjunto\n[4] Buscar conjunto\n[5] Fazer faxina e sair:\n");
        scanf("%d", &op);
        switch(op) {
        case 1:
            printf("Digite um representante do primeiro conjunto: ");
            scanf("%d", &rep1);
            printf("Digite um representante do segundo conjunto: ");
            scanf("%d", &rep2);

            Conjuntos a, b;
            a = busca_conj(&m, &rep1, compara_int);
            b = busca_conj(&m, &rep2, compara_int);

            uniao(&a, &b);

            m.cabeca->proximo = m.cabeca->proximo->proximo;
            m.qtd--;

            mostra_tudoXXX(m);
        case 2:
            mostra_tudoXXX(m);
        case 4:
            printf("Digite o representante: ");
            scanf("%d", &x);

            Conjuntos sub;
            sub = busca_conj(&m, &x, compara_int);

            if (sub.qtd > 0) {
                mostra_conjuntos(sub, mostra_int);
            } else {
                printf("\nConjunto não encontrado!");
            }
        case 5:
            destroiTudo(m);
        default:
            break;
        }
    }
    return 1;
}

void destroiTudo(Conjuntos m) {
    Conjuntos sub;
    int i;
    for (i = 0; i < m.qtd; i++) {
        leNaPos(&m, &sub, i);
        limpa_lista(&sub);
    }
    limpa_lista(&m);
}

void mostra_int(void *x) {
    printf("%d\t", *(int*) x);
}

int compara_int(void *x, void *y) {
    float *a = x, *b = y;
    if (*a > *b) return 1;
    if (*a < *b) return -1;
    return 0;
}

void mostra_tudoXXX(Conjuntos m) {
    int i;
    Conjuntos sub;
    printf("Dados dos conjuntos:\n");
    for (i = 0; i < m.qtd; i++) {
        leNaPos(&m, &sub, i);
        mostra_conjuntos(sub, mostra_int);
        printf("\n");
    }
}

