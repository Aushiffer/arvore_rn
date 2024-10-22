#include "arv_rn.h"

ArvRN nil;

void inicia_arv(ArvRN *arv_rn) { *arv_rn = nil; }

void inicia_nil() {
    if (!(nil = (ArvRN)malloc(sizeof(No)))) return;

    nil->item = INT_MIN;
    nil->pai = nil->esq = nil->dir = NULL;
    nil->cor = BLACK;
}

void destroi_nil() { if (nil) free(nil); }

ArvRN cria_no(ArvRN pai, Cor cor, int chave) {
    ArvRN novo_no;

    if (!(novo_no = (ArvRN)malloc(sizeof(No)))) return NULL;

    novo_no->cor = cor;
    novo_no->esq = novo_no->dir = nil;
    novo_no->item = chave;
    novo_no->pai = pai;

    return novo_no;
}

unsigned char eh_nulo(ArvRN arv_rn) { return arv_rn == nil || !arv_rn; }

ArvRN insere_rn_apriori(ArvRN pai, ArvRN arv_rn, ArvRN *no_ins, int chave) {
    if (eh_nulo(arv_rn)) {
        ArvRN novo_no = cria_no(pai, RED, chave);
        *no_ins = novo_no;

        return novo_no;
    }

    if (arv_rn->item > chave)
        arv_rn->esq = insere_rn_apriori(arv_rn, arv_rn->esq, no_ins, chave);
    else if (arv_rn->item < chave)
        arv_rn->dir = insere_rn_apriori(arv_rn, arv_rn->dir, no_ins, chave);

    return arv_rn;
}

ArvRN insere_rn(ArvRN arv_rn, int chave) {
    if (eh_nulo(arv_rn)) return cria_no(nil, BLACK, chave);

    ArvRN no_ins = arv_rn; // Evitando acesso à regiões não inicializadas da memória.

    if (arv_rn->item > chave)
        arv_rn->esq = insere_rn_apriori(arv_rn, arv_rn->esq, &no_ins, chave);
    else if (arv_rn->item < chave)
        arv_rn->dir = insere_rn_apriori(arv_rn, arv_rn->dir, &no_ins, chave);
    else
        return arv_rn;

    bal_insercao(&arv_rn, &no_ins);

    return arv_rn;
}

void rot_esq(ArvRN *raiz, ArvRN no_rot) {
    if (eh_nulo(no_rot) || eh_nulo(no_rot->dir)) return;

    ArvRN filho_dir = no_rot->dir;
    no_rot->dir = filho_dir->esq;

    if (!eh_nulo(filho_dir->esq))
        filho_dir->esq->pai = no_rot;

    filho_dir->pai = no_rot->pai;

    if (eh_nulo(no_rot->pai))
        *raiz = filho_dir;
    else if (no_rot == no_rot->pai->esq)
        no_rot->pai->esq = filho_dir;
    else
        no_rot->pai->dir = filho_dir;

    filho_dir->esq = no_rot;
    no_rot->pai = filho_dir;
}

void rot_dir(ArvRN *raiz, ArvRN no_rot) {
    if (eh_nulo(no_rot) || eh_nulo(no_rot->esq)) return;

    ArvRN filho_esq = no_rot->esq;
    no_rot->esq = filho_esq->dir;

    if (!eh_nulo(filho_esq->dir))
        filho_esq->dir->pai = no_rot;

    filho_esq->pai = no_rot->pai;

    if (eh_nulo(no_rot->pai))
        *raiz = filho_esq;
    else if (no_rot == no_rot->pai->esq)
        no_rot->pai->esq = filho_esq;
    else
        no_rot->pai->dir = filho_esq;

    filho_esq->dir = no_rot;
    no_rot->pai = filho_esq;
}

void bal_insercao(ArvRN *raiz, ArvRN *no_ins) {
    ArvRN tio;

    while (*no_ins != *raiz && (*no_ins)->pai->cor == RED) {
        if ((*no_ins)->pai == (*no_ins)->pai->pai->esq) {
            tio = (*no_ins)->pai->pai->dir;

            if (eh_nulo(tio) || tio->cor == BLACK) {
                if ((*no_ins) == (*no_ins)->pai->dir) {
                    (*no_ins) = (*no_ins)->pai;
                    
                    rot_esq(raiz, *no_ins);
                }

                (*no_ins)->pai->cor = BLACK;
                (*no_ins)->pai->pai->cor = RED;
                
                rot_dir(raiz, (*no_ins)->pai->pai);
            } else {
                tio->cor = BLACK;
                (*no_ins)->pai->cor = BLACK;
                (*no_ins)->pai->pai->cor = RED;
                (*no_ins) = (*no_ins)->pai->pai;
            }
        } else {
            tio = (*no_ins)->pai->pai->esq;

            if (eh_nulo(tio) || tio->cor == BLACK) {
                if ((*no_ins) == (*no_ins)->pai->esq) {
                    (*no_ins) = (*no_ins)->pai;

                    rot_dir(raiz, *no_ins);
                }

                (*no_ins)->pai->cor = BLACK;
                (*no_ins)->pai->pai->cor = RED;

                rot_esq(raiz, (*no_ins)->pai->pai);
            } else {
                tio->cor = BLACK;
                (*no_ins)->pai->cor = BLACK;
                (*no_ins)->pai->pai->cor = RED;
                (*no_ins) = (*no_ins)->pai->pai;
            }
        }
    }

    (*raiz)->cor = BLACK;
}

ArvRN busca_rn(ArvRN arv_rn, int chave) {
    if (eh_nulo(arv_rn) || arv_rn->item == chave) return arv_rn;

    if (arv_rn->item > chave)
        return busca_rn(arv_rn->esq, chave);
    
    return busca_rn(arv_rn->dir, chave);
}

ArvRN predec(ArvRN arv_rn) {
    if (eh_nulo(arv_rn)) return arv_rn;

    ArvRN no_atual = arv_rn->esq;

    while (!eh_nulo(no_atual) && !eh_nulo(no_atual->dir))
        no_atual = no_atual->dir;

    return no_atual;
}

void transplant(ArvRN *raiz, ArvRN a, ArvRN b) {
    if (eh_nulo(a->pai))
        *raiz = b;
    else if (a == a->pai->esq)
        a->pai->esq = b;
    else
        a->pai->dir = b;

    if (!eh_nulo(b))
        b->pai = a->pai;
}

unsigned char remove_rn(ArvRN arv_rn, int chave) {
    if (eh_nulo(arv_rn)) return 0;

    ArvRN z = busca_rn(arv_rn, chave);

    if (eh_nulo(z)) return 0;

    ArvRN y = z, x;
    Cor y_cor_og = y->cor;

    if (eh_nulo(z->esq)) {
        x = z->dir;

        transplant(&arv_rn, z, z->dir);
    } else if (eh_nulo(z->dir)) {
        x = z->esq;

        transplant(&arv_rn, z, z->esq);
    } else {
        y = predec(z);
        y_cor_og = y->cor;
        x = y->esq;
        z->item = y->item;

        transplant(&arv_rn, y, y->esq);

        if (!eh_nulo(y->esq))
            y->esq->cor = BLACK;
    }

    if (y_cor_og == BLACK)
        bal_remocao(&arv_rn, &x);

    free(y);

    return 1;
}

void bal_remocao(ArvRN *raiz, ArvRN *x) {
    if (eh_nulo(*x)) return;
    
    ArvRN w;

    while (*x != *raiz && (*x)->cor == BLACK) {
        if (*x == (*x)->pai->esq) {
            w = (*x)->pai->dir;

            if (w->cor == RED) {
                w->cor = BLACK;
                (*x)->pai->cor = RED;
                
                rot_esq(raiz, (*x)->pai);
                
                w = (*x)->pai->dir;
            }

            if ((eh_nulo(w->esq) && eh_nulo(w->dir)) || (w->esq->cor == BLACK && w->dir->cor == BLACK)) {
                w->cor = RED;
                (*x) = (*x)->pai;
            } else {
                if (w->esq->cor == RED) {
                    w->cor = RED;
                    w->esq->cor = BLACK;

                    rot_dir(raiz, w);
                }

                w->cor = (*x)->pai->cor;
                (*x)->pai->cor = BLACK;
                w->dir->cor = BLACK;

                rot_esq(raiz, (*x)->pai);

                *x = *raiz;
            }
        } else {
            w = (*x)->pai->esq;

            if (w->cor == RED) {
                w->cor = BLACK;
                (*x)->pai->cor = RED;
                
                rot_dir(raiz, (*x)->pai);
                
                w = (*x)->pai->esq;
            }

            if ((eh_nulo(w->esq) && eh_nulo(w->dir)) || (w->esq->cor == BLACK && w->dir->cor == BLACK)) {
                w->cor = RED;
                (*x) = (*x)->pai;
            } else {
                if (w->dir->cor == RED) {
                    w->cor = RED;
                    w->dir->cor = BLACK;

                    rot_esq(raiz, w);
                }

                w->cor = (*x)->pai->cor;
                (*x)->pai->cor = BLACK;
                w->esq->cor = BLACK;

                rot_dir(raiz, (*x)->pai);

                *x = *raiz;
            }
        }
    }
    
    (*x)->cor = BLACK;
}

void destroi_rn(ArvRN arv_rn) {
    if (eh_nulo(arv_rn)) return;

    destroi_rn(arv_rn->esq);
    destroi_rn(arv_rn->dir);
    free(arv_rn);
}

void imprime_rn(ArvRN arv_rn) {
    if (eh_nulo(arv_rn)) {
        printf("()");

        return;
    }

    printf("(");
    printf("%d", arv_rn->item);
    imprime_rn(arv_rn->esq);
    imprime_rn(arv_rn->dir);
    printf(")");
}