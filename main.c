#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void mostra_int(void *x);
int compara_int(void *x, void *y);
void mostra_tudoXXX(Conjuntos m);

int main() {
    int lin, i, j, x, op;
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

    while (1) {
        printf("\nEscolha uma opcao:\n[1] Unir conjuntos\n[2] Mostrar conjuntos\n[3] Remover conjunto\n[4] Buscar conjunto\n[5] Fazer faxina e sair: ");
        scanf("%d", &op);
        switch(op) {
        case 1:
            while (1) {
                printf("\nDigite um representante do primeiro conjunto (que recebe a uniao): ");
                scanf("%d", &rep1);
                if (busca_conj(&m, &a, &rep1, compara_int) != ERRO_CONJUNTO_INEXISTENTE)
                    break;
                else
                    printf("\nConjunto nao encontrado!\n");
            }
            while (1) {
                printf("\nDigite um representante do segundo conjunto (que cede): ");
                scanf("%d", &rep2);
                if (busca_conj(&m, &b, &rep2, compara_int) != ERRO_CONJUNTO_INEXISTENTE)
                    break;
                else
                    printf("\nConjunto nao encontrado!\n");
            }
            if (uniao(&m, &rep1, &rep2, compara_int))
                printf("\nUniao feita com sucesso!\n");
            break;
        case 2:
            printf("Dados dos conjuntos:\n");
            for (i = 0; i < m.qtd; i++) {
                leNaPos(&m, &sub, i);
                mostra_conjuntos(sub, mostra_int);
                printf("\n");
            }
            break;
        case 3:
            printf("\nEntre o representante do conjunto a ser removido: ");
            scanf("%d", &x);
            i = (busca_conj(&m, &sub, &x, compara_int));
            if (i != ERRO_CONJUNTO_INEXISTENTE) {
                for (j = 0; j < i; j++)
                    removeDaPos(&sub, &x, j);
                removeDaPos(&m, &sub, i);
                printf("\nConjunto removido!\n");
            }
            else
                printf("\nConjunto nao encontrado!\n");
            break;
        case 4:
            printf("\nDigite o representante: ");
            scanf("%d", &x);

            if (busca_conj(&m, &sub, &x, compara_int) != ERRO_CONJUNTO_INEXISTENTE){
                mostra_conjuntos(sub, mostra_int);
                printf("\n");
            }
            else
                printf("\nConjunto nao encontrado!\n");
            break;
        case 5:
            for (i = 0; i < m.qtd; i++) {
                leNaPos(&m, &sub, i);
                limpa_conjunto(&sub);
            }
            limpa_conjunto(&m);
            printf("\nTchau!\n");
            return 1;
        default:
            break;
        }
    }
    return 1;
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
