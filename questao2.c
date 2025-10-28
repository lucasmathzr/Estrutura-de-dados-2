#include <stdio.h>
#include <stdlib.h>

int* cria_vetor(int n) {
    int* v = (int*) malloc(n * sizeof(int));
    if (v == NULL) {
        printf("Erro de memoria!\n");
        exit(1);
    }
    return v;
}

void imprime_vetor(int* v, int n) {
    printf("\n--- Vetor ---\n");
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void libera_vetor(int* v) {
    free(v);
    printf("Memoria liberada!\n");
}

int main() {
    int n;
    printf("Tamanho do vetor: ");
    scanf("%d", &n);
    int* v = cria_vetor(n);

    for (int i = 0; i < n; i++) {
        printf("Elemento %d: ", i);
        scanf("%d", &v[i]);
    }

    imprime_vetor(v, n);
    libera_vetor(v);
    return 0;
}
