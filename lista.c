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

void mostra_conjuntos(Conjuntos l, void (*mostra) (void *)) {
    if (lista_vazia(&l))
        printf("\nConjunto vazio!\n");
    else {
        printf("\nElementos do conjunto:\n");
        Elemento *p = l.cabeca;
        while (p) {
            mostra(p->info);
            p = p->proximo;
        }
    }
}

void limpa_conjunto(Conjuntos *l) {
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

int cria_conjunto(Conjuntos *p, void *rep, int (*comp)(void *, void *)) {
    int i;
    Conjuntos c;
    Elemento *ind = aloca_ele(&c, sizeof(Conjuntos));
    if (!ind)
        return 0;
    for (i = 0;i < p->qtd; i++){
        leNaPos(p, &ind, i);
        if (!comp(ind->info, rep))
            return ERRO_ELEMENTOREPETIDO;
    }
    inicializa_conjuntos(&c, sizeof(Conjuntos));

    if (insereNoInicio(&c, rep))
        return insereNoFim(p, &c);
    return 0;
}

int busca_conj(Conjuntos *m, Conjuntos *sub, void *rep, int(*comp) (void *, void *)){
    int i;
    for (i = 0; i < m->qtd; i++) {
        leNaPos(m, sub, i);
        if (!comp(sub->cabeca->info, rep)) {
            return i;
        }
    }
    return ERRO_CONJUNTO_INEXISTENTE;
}

int uniao(Conjuntos *m, void *rep1, void *rep2, int(*comp) (void *, void *)) {
    Conjuntos a, b;
    int i, j;
    for (i = 0; i < m->qtd; i++) {
        leNaPos(m, &a, i);
        if (!comp(a.cabeca->info, rep1))
            break;
    }
    for (j = 0; j < m->qtd; j++) {
        leNaPos(m, &b, j);
        if (!comp(b.cabeca->info, rep2))
            break;
    }
    if (!b.cabeca)
        return 0;
    Elemento *e = a.cabeca;
    while (e->proximo) {
        e = e->proximo;
    }
    e->proximo = b.cabeca;
    a.qtd += b.qtd;
    modificaNaPos(m, &a, i);
    removeDaPos(m, &b, j);
    return 1;
}
