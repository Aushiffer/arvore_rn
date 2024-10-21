#include "arv_rn.h"

int main() {
    ArvRN arv_rn; 
    int chave;

    inicia_nil();
    inicia_arv(&arv_rn);

    do {
        scanf("%d", &chave);

        if (chave != -1)
            arv_rn = insere_rn(arv_rn, chave);
    } while (chave != -1);

    remove_rn(arv_rn, 64);
    imprime_rn(arv_rn);
    printf("\n");

    if (arv_rn->cor == RED)
        puts("RAIZ VERMELHA");
    else
        puts("RAIZ PRETA");

    destroi_rn(arv_rn);
    destroi_nil();

    return 0;
}