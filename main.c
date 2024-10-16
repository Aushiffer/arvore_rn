#include "arv_rn.h"

int main() {
    ArvRN arv_rn; inicia_arv(&arv_rn);
    int chave;

    do {
        scanf("%d", &chave);

        if (chave != -1)
            arv_rn = insere_rn(arv_rn, chave);
    } while (chave != -1);

    imprime_rn(arv_rn);
    printf("\n");
    printf("Cor da raiz: %d\n", arv_rn->cor);
    destroi_rn(arv_rn);

    return 0;
}