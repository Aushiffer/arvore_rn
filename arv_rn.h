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

void rot_esq(ArvRN *raiz, ArvRN no_rot);

void rot_dir(ArvRN *raiz, ArvRN no_rot);

void balanceia_rn(ArvRN *raiz, ArvRN *no_ins);

unsigned char rn_vazia(ArvRN arv_rn);

void imprime_rn(ArvRN arv_rn);

void destroi_rn(ArvRN arv_rn);

#endif // __ARV_RN__