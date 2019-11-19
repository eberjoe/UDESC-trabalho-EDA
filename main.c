#include <stdio.h>
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
    Conjuntos m, sub;

    inicializa_conjuntos(&m, sizeof(Conjuntos));
    for (i = 1; i <= lin; i++) {
        printf("Entre um elemento representante 'int' para o conjunto %d: ", i);
        scanf("%d", &x);
        if (!cria_conjunto(&m, &x, compara_int)) {
            printf("Os elementos devem ser diferentes!");
            return 0;
        }
    }

    mostra_tudoXXX(m);

    while (1) {
        printf("\nEscolha uma opcao:\n[1] Inserir elementos\n[2] Unir conjuntos\n[3] Mostrar conjuntos\n[4] Remover conjunto\n[5] Fazer faxina e sair :");
        scanf("%d", &op);
        switch(op) {
        case 1:
            printf("Inserir em qual conjunto? ");
            scanf("%d", &rep);
            printf("Entre o valor a ser inserido: ");
            scanf("%d", &x);
            cont = 0;
            for (i = 0; i < m.qtd; i++) {
                leNaPos(&m, &sub, i);
                if (!compara_int(&sub.cabeca, &rep)) {
                    cont++;
                    printf("Voce perdeu! Deveria ter inserido um valor direfente!");
                    return 0;
                }
            }
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

