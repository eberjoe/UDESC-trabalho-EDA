#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void mostra_int(void *x);
int compara_int(void *x, void *y);
int disjuntos(Conjuntos c);
void mostra_tudoXXX(Conjuntos m);
void destroiTudo(Conjuntos m);

int main() {
    int lin, i, x, op;
    printf("Digite o numero de conjuntos: ");
    scanf("%d", &lin);
    Conjuntos m, sub, a, b;
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
        printf("\nEscolha uma opcao:\n[1] Unir conjuntos\n[2] Mostrar conjuntos\n[3] Remover conjunto\n[4] Buscar conjunto\n[5] Fazer faxina e sair: ");
        scanf("%d", &op);
        switch(op) {
        case 1:
            while (1) {
                printf("\nDigite um representante do primeiro conjunto (que recebe a uniao): ");
                scanf("%d", &rep1);
                if (busca_conj(&m, &a, &rep1, compara_int) > ERROLISTA_VAZIA)
                    break;
                else
                    printf("\nConjunto nao encontrado!\n");
            }
            while (1) {
                printf("\nDigite um representante do segundo conjunto (que cede): ");
                scanf("%d", &rep2);
                if (busca_conj(&m, &b, &rep2, compara_int) > ERROLISTA_VAZIA)
                    break;
                else
                    printf("\nConjunto nao encontrado!\n");
            }

            uniao(&m, &rep1, &rep2, compara_int);

            mostra_tudoXXX(m);

            break;
        case 2:
            mostra_tudoXXX(m);
            break;
        case 3:
            printf("\nEntre o representante do conjunto a ser removido: ");
            scanf("%d", &x);
            i = (busca_conj(&m, &sub, &x, compara_int));
            if (i > ERROLISTA_VAZIA)
                removeDaPos(&m, &sub, i);
            else
                printf("\nConjunto nao encontrado!\n");
            break;
        case 4:
            printf("\nDigite o representante: ");
            scanf("%d", &x);

            if (busca_conj(&m, &sub, &x, compara_int) > ERROLISTA_VAZIA)
                mostra_conjuntos(sub, mostra_int);
            else
                printf("\nConjunto nao encontrado!\n");
            break;
        case 5:
            destroiTudo(m);
            return 1;
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

