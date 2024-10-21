#ifndef __ARV_RN__
#define __ARV_RN__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Cores dos nós
enum Cor {RED, BLACK};
typedef enum Cor Cor;

// Definição de Árvore Rubro-Negra (ARN)
typedef struct No *ArvRN;
typedef struct No {
    ArvRN esq, dir, pai;
    int item;
    Cor cor;
} No;

// Recebe um ponteiro para uma ARN e o inicializa com NIL.
void inicia_arv(ArvRN *arv_rn);

// Inicia a sentinela global NIL.
void inicia_nil();

// Recebe uma ARN que define o pai do novo nó, a cor e a chave.
// Retorna uma novo nó que possui os atributos especificados.
ArvRN cria_no(ArvRN pai, Cor cor, int chave);

// Recebe uma ARN e uma chave a ser buscada.
// Retorna o nó na ARN através de busca binária na ARN.
ArvRN busca_rn(ArvRN arv_rn, int chave);

// Recebe uma ARN e a chave a ser atribuída ao nó que será inserido.
// A função serve como interface para insere_rn_apriori(), apenas chamando a função de balanceamento após a inserção.
ArvRN insere_rn(ArvRN arv_rn, int chave);

// Recebe uma ARN que define o pai do nó a ser inserido, a ARN na qual a inserção ocorrerá, um ponteiro que receberá o nó inserido e a chave que será atribuída ao nó inserido.
// Insere um nó com a chave especificada na ARN, apontando o ponteiro para o nó inserido e definindo seu pai adequadamente.
// A inserção ocorre exatamente como na ABB, então não há balanceamento nessa função.
ArvRN insere_rn_apriori(ArvRN pai, ArvRN arv_rn, ArvRN *no_ins, int chave);

// Recebe uma ARN e uma chave.
// Remove o nó com a chave especificada; retorna 1 caso a remoção tenha ocorrido com sucesso, e 0 caso contrário.
unsigned char remove_rn(ArvRN arv_rn, int chave);

// Recebe uma ARN e retorna o seu predecessor dentro da árvore.
ArvRN predec(ArvRN arv_rn);

// Recebe um ponteiro para a raiz da ARN e duas raízes de subárvores 'a' e 'b'.
// 'Transplanta' a raiz da árvore enraizada em 'b' na raiz da árvore enraizada em 'a'.
void transplant(ArvRN *raiz, ArvRN a, ArvRN b);

// Recebe um ponteiro para a raiz da ARN e o nó a ser rotacionado na árvore.
// Rotaciona o nó para a esquerda e ajusta os ponteiros para os pais dos nós envolvidos na rotação. 
void rot_esq(ArvRN *raiz, ArvRN no_rot);

// Recebe um ponteiro para a raiz da ARN e o nó a ser rotacionado na árvore.
// Rotaciona o nó para a direita e ajusta os ponteiros para os pais dos nós envolvidos na rotação. 
void rot_dir(ArvRN *raiz, ArvRN no_rot);

// Recebe um ponteiro para a raiz de uma ARN e um ponteiro para o nó recentemente inserido na ARN.
// Balanceia a ARN de tal forma que as propriedades continuem sendo respeitadas.
void bal_insercao(ArvRN *raiz, ArvRN *no_ins);

// Recebe um ponteiro para a raiz de uma ARN e um ponteiro para o nó recentemente removido da ARN.
// Balanceia a ARN de tal forma que as propriedades continuem sendo respeitadas.
void bal_remocao(ArvRN *raiz, ArvRN *no_rem);

// Recebe uma ARN e a imprime em ordem.
void imprime_rn(ArvRN arv_rn);

// Recebe uma ARN e libera toda a memória alocada para ela.
// Não libera a sentinela NIL.
void destroi_rn(ArvRN arv_rn);

// Libera a sentinela global NIL.
void destroi_nil();

#endif // __ARV_RN__