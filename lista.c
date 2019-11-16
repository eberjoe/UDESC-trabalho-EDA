#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

void inicializa_conjuntos(Conjuntos *l, int t) {
    l->cabeca = NULL;
    l->tamInfo = t;
    l->qtd = 0;
}

int lista_vazia(Conjuntos *l) {
    return !l->qtd;
}

Elemento* aloca_ele(void *x, int t){
	Elemento *p = malloc(sizeof(Elemento));
	if (!p)
		return NULL; // falta memória
	p->info = malloc(t);
	if (!p->info){
		free(p);
		return NULL; // falta memória
	}
	memcpy(p->info, x, t);
	return p;
}

int insereNoInicio(Conjuntos *l, void *info) {
    Elemento *p = aloca_ele(info, l->tamInfo);
    if (!p)
        return 0; // falta memória
    p->proximo = l->cabeca;
    l->cabeca = p;
    l->qtd++;
    return 1; // sucesso
}

int removeDoInicio(Conjuntos *l, void *info) {
    if (lista_vazia(l))
        return ERROLISTA_VAZIA;
    Elemento *p = l->cabeca;
    memcpy(info, p->info, l->tamInfo);
    l->cabeca = p->proximo;
    l->qtd--;
    free(p->info);
    free(p);
    return 1; // sucesso
}

int insereNoFim(Conjuntos *l, void *info) {
    Elemento *p = aloca_ele(info, l->tamInfo);
    if (!p)
        return 0; // falta memória
    p->proximo = NULL;
    if (!l->cabeca) {
        return insereNoInicio(l, info);
    } else {
        Elemento *q = l->cabeca;
        while (q->proximo) {
            q = q->proximo;
        }
        q->proximo = p;
    }
    l->qtd++;
    return 1; // sucesso
}

int removeDoFim(Conjuntos *l, void *info) {
    if (lista_vazia(l))
        return ERROLISTA_VAZIA;
    if (l->qtd == 1)
        return removeDoInicio(l, info);
    Elemento *p = l->cabeca;
    while (p->proximo->proximo) { // penúltimo
        p = p->proximo;
    }
    memcpy(info, p->proximo->info, l->tamInfo);
    free(p->proximo->info);
    free(p->proximo);
    p->proximo = NULL;
    l->qtd--;
    return 1; // sucesso
}

int insereNaPos(Conjuntos *l, void *info, int pos) {
    if (pos < 0 || pos > l->qtd)
        return ERRO_POS_INVALIDA;
    if (!pos)
        return insereNoInicio(l, info);
    Elemento *p = l->cabeca;
    int cont;
    for (cont = 0; cont < pos-1; cont++)
        p = p->proximo;
    Elemento *novo = aloca_ele(info, l->tamInfo);
    if (!novo)
        return 0; // falta memória
    novo->proximo = p->proximo;
    p->proximo = novo;
    l->qtd++;
    return 1; // sucesso
}

int removeDaPos(Conjuntos *l, void *info, int pos) {
    if (lista_vazia(l))
        return ERROLISTA_VAZIA;
    if (pos < 0 || pos >= l->qtd)
        return ERRO_POS_INVALIDA;
    if (!pos)
        return removeDoInicio(l, info);
    Elemento *p = l->cabeca;
    int cont;
    for (cont = 0; cont < pos-1; cont++)
        p = p->proximo;
    Elemento *x = p->proximo;
    p->proximo = x->proximo;
    memcpy(info, x->info, l->tamInfo);
    free(x->info);
    free(x);
    l->qtd--;
    return 1; // sucesso
}

int modificaNaPos(Conjuntos *l, void *info, int pos) {
    if (lista_vazia(l))
        return ERROLISTA_VAZIA;
    if (pos < 0 || pos >= l->qtd)
        return ERRO_POS_INVALIDA;
    Elemento *p = l->cabeca;
    int cont;
    for (cont = 0; cont < pos; cont++)
        p = p->proximo;
    memcpy(p->info, info, l->tamInfo);
    return 1; // sucesso
}

int leNaPos(Conjuntos *l, void *info, int pos) {
    if (lista_vazia(l))
        return ERROLISTA_VAZIA;
    if (pos < 0 || pos >= l->qtd)
        return ERRO_POS_INVALIDA;
    Elemento *p = l->cabeca;
    int cont;
    for (cont = 0; cont < pos; cont++)
        p = p->proximo;
    memcpy(info, p->info, l->tamInfo);
    return 1; // sucesso
}

int insereNaOrdem(Conjuntos *l, void *info, int (*comp) (void *, void *)) {
    Elemento *p = l->cabeca;
    int cont = 0;
    while (p && comp(info, p->info) > 0) {
        p = p->proximo;
        cont++;
    }
    return insereNaPos(l, info, cont);
}

void mostra_conjuntos(Conjuntos l, void (*mostra) (void *)) {
    if (lista_vazia(&l))
        printf("\nConjunto vazio!\n");
    else {
        printf("\nElementos do conjunto:\n");
        Elemento *p = l.cabeca;
        int count =0;
        while (p) {
            printf("%d\t", count);
            mostra(p->info);
            p = p->proximo;
            count++;
        }
    }
}

void limpa_lista(Conjuntos *l) {
    Elemento *p = l->cabeca, *q;
    while (p) {
        q = p;
        p = p->proximo;
        free(q->info);
        free(q);
    }
    l->cabeca = NULL;
    l->qtd = 0;
}
