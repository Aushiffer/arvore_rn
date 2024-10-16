#include "arv_rn.h"

No no_nil;
ArvRN nil = &no_nil;

void inicia_arv(ArvRN *arv_rn) { *arv_rn = nil; }

ArvRN cria_no(ArvRN pai, Cor cor, int chave) {
    ArvRN novo_no;

    if (!(novo_no = (ArvRN)malloc(sizeof(No)))) return NULL;

    novo_no->cor = cor;
    novo_no->esq = novo_no->dir = nil;
    novo_no->item = chave;
    novo_no->pai = pai;

    return novo_no;
}

unsigned char rn_vazia(ArvRN arv_rn) { return arv_rn == nil; }

ArvRN insere_rn_apriori(ArvRN pai, ArvRN arv_rn, ArvRN *no_ins, int chave) {
    if (rn_vazia(arv_rn)) {
        ArvRN novo_no = cria_no(pai, RED, chave);
        *no_ins = novo_no;

        return novo_no;
    }

    if (arv_rn->item > chave)
        arv_rn->esq = insere_rn_apriori(arv_rn, arv_rn->esq, no_ins, chave);
    else if (arv_rn->item < chave)
        arv_rn->dir = insere_rn_apriori(arv_rn, arv_rn->dir, no_ins, chave);
    else
        return arv_rn;

    return arv_rn;
}

ArvRN insere_rn(ArvRN arv_rn, int chave) {
    if (rn_vazia(arv_rn)) return cria_no(nil, BLACK, chave);

    ArvRN no_ins;

    if (arv_rn->item > chave)
        arv_rn->esq = insere_rn_apriori(arv_rn, arv_rn->esq, &no_ins, chave);
    else
        arv_rn->dir = insere_rn_apriori(arv_rn, arv_rn->dir, &no_ins, chave);

    balanceia_rn(&arv_rn, &no_ins);

    return arv_rn;
}

void rot_esq(ArvRN *raiz, ArvRN no_rot) {
    if (rn_vazia(no_rot) || !no_rot->dir) return;

    ArvRN filho_dir = no_rot->dir;
    no_rot->dir = filho_dir->esq;

    if (filho_dir->esq)
        filho_dir->esq->pai = no_rot;

    filho_dir->pai = no_rot->pai;

    if (no_rot->pai == nil)
        *raiz = filho_dir;
    else if (no_rot == no_rot->pai->esq)
        no_rot->pai->esq = filho_dir;
    else
        no_rot->pai->dir = filho_dir;

    filho_dir->esq = no_rot;
    no_rot->pai = filho_dir;
}

void rot_dir(ArvRN *raiz, ArvRN no_rot) {
    if (rn_vazia(no_rot) || !no_rot->esq) return;

    ArvRN filho_esq = no_rot->esq;
    no_rot->esq = filho_esq->dir;

    if (filho_esq->dir)
        filho_esq->dir->pai = no_rot;

    filho_esq->pai = no_rot->pai;

    if (no_rot->pai == nil)
        *raiz = filho_esq;
    else if (no_rot == no_rot->pai->esq)
        no_rot->pai->esq = filho_esq;
    else
        no_rot->pai->dir = filho_esq;

    filho_esq->dir = no_rot;
    no_rot->pai = filho_esq;
}

// Obrigado Cormen!
void balanceia_rn(ArvRN *raiz, ArvRN *no_ins) {
    ArvRN tio;

    while (*no_ins != *raiz && (*no_ins)->pai->cor == RED) {
        if ((*no_ins)->pai == (*no_ins)->pai->pai->esq) {
            tio = (*no_ins)->pai->pai->dir;

            if (tio == nil || tio->cor == BLACK) {
                if ((*no_ins) == (*no_ins)->pai->dir) {
                    (*no_ins) = (*no_ins)->pai;
                    
                    rot_esq(raiz, *no_ins);
                }

                (*no_ins)->pai->cor = BLACK;
                (*no_ins)->pai->pai->cor = RED;
                
                rot_dir(raiz, (*no_ins)->pai->pai);
            } else {
                (*no_ins)->pai->cor = BLACK;
                tio->cor = BLACK;
                (*no_ins)->pai->pai->cor = RED;
                (*no_ins) = (*no_ins)->pai->pai;
            }
        } else {
            tio = (*no_ins)->pai->pai->esq;

            if (tio == nil || tio->cor == BLACK) {
                if ((*no_ins) == (*no_ins)->pai->esq) {
                    (*no_ins) = (*no_ins)->pai;

                    rot_dir(raiz, *no_ins);
                }

                (*no_ins)->pai->cor = BLACK;
                (*no_ins)->pai->pai->cor = RED;

                rot_esq(raiz, (*no_ins)->pai->pai);
            } else {
                (*no_ins)->pai->cor = BLACK;
                tio->cor = BLACK;
                (*no_ins)->pai->pai->cor = RED;
                (*no_ins) = (*no_ins)->pai->pai;
            }
        }
    }

    if ((*raiz)->cor == RED)
        (*raiz)->cor = BLACK;
}

void destroi_rn(ArvRN arv_rn) {
    if (rn_vazia(arv_rn)) return;

    destroi_rn(arv_rn->esq);
    destroi_rn(arv_rn->dir);
    free(arv_rn);
}

void imprime_rn(ArvRN arv_rn) {
    if (rn_vazia(arv_rn)) {
        printf("()");

        return;
    }

    printf("(");
    printf("%d", arv_rn->item);
    imprime_rn(arv_rn->esq);
    imprime_rn(arv_rn->dir);
    printf(")");
}