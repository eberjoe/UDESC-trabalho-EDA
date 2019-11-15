#define ERROLISTA_VAZIA -1
#define ERRO_POS_INVALIDA -2

typedef struct ele {
    void *info;
    struct ele *proximo;
}Elemento;

typedef struct {
    Elemento *cabeca;
    int tamInfo, qtd;
}Conjuntos;

void inicializa_conjuntos(Conjuntos *l, int t);
int lista_vazia(Conjuntos *l);
int insereNoInicio(Conjuntos *l, void *info);
int removeDoInicio(Conjuntos *l, void *info);
int insereNoFim(Conjuntos *l, void *info);
int removeDoFim(Conjuntos *l, void *info);
int insereNaPos(Conjuntos *l, void *info, int pos);
int removeDaPos(Conjuntos *l, void *info, int pos);
int modificaNaPos(Conjuntos *l, void *info, int pos);
int leNaPos(Conjuntos *l, void *info, int pos);
int insereNaOrdem(Conjuntos *l, void *info, int (*comp) (void *, void *));
void mostra_conjuntos(Conjuntos l, void (*mostra) (void *));
void limpa_lista(Conjuntos *l);

// funcoes especializadas para o trabalho

int cria_conjunto(Conjuntos *p, void *representante, int(*comp) (void *, void *));
int inicio(Conjuntos *p, void *rep1, void *rep2, int(*comp) (void *, void *));

