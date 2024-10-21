#ifndef __ARV_RN__
#define __ARV_RN__

#include <stdio.h>
#include <stdlib.h>

enum Cor {RED, BLACK};
typedef enum Cor Cor;

typedef struct No *ArvRN;
typedef struct No {
    ArvRN esq, dir, pai;
    int item;
    Cor cor;
} No;

void inicia_arv(ArvRN *arv_rn);

ArvRN cria_no(ArvRN pai, Cor cor, int chave);

ArvRN busca_rn(ArvRN arv_rn, int chave);

ArvRN insere_rn(ArvRN arv_rn, int chave);

ArvRN insere_rn_apriori(ArvRN pai, ArvRN arv_rn, ArvRN *no_ins, int chave);

unsigned char remove_rn(ArvRN arv_rn, int key);

ArvRN predec(ArvRN arv_rn);

// Recebe um ponteiro para a raiz da ARN e duas raízes de subárvores 'a' e 'b'.
// 'Transplanta' a raiz da árvore enraizada em 'b' na raiz enraizada em 'a'.
void transplant(ArvRN *raiz, ArvRN a, ArvRN b);

// Recebe um ponteiro para a raiz da ARN e o nó a ser rotacionado na árvore.
// Rotaciona o nó para a esquerda e ajusta os ponteiros para os pais dos nós envolvidos na rotação. 
void rot_esq(ArvRN *raiz, ArvRN no_rot);

// Recebe um ponteiro para a raiz da ARN e o nó a ser rotacionado na árvore.
// Rotaciona o nó para a direita e ajusta os ponteiros para os pais dos nós envolvidos na rotação. 
void rot_dir(ArvRN *raiz, ArvRN no_rot);

void bal_insercao(ArvRN *raiz, ArvRN *no_ins);

void bal_remocao(ArvRN *raiz, ArvRN *no_rem);

void imprime_rn(ArvRN arv_rn);

void destroi_rn(ArvRN arv_rn);

#endif // __ARV_RN__