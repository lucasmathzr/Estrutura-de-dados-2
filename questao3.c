#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    double valor;
    struct node* prox;
} Node;

typedef struct {
    Node* topo;
} Pilha;

Pilha* cria_pilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

int vazia(Pilha* p) {
    return p->topo == NULL;
}

void push(Pilha* p, double v) {
    Node* novo = (Node*) malloc(sizeof(Node));
    novo->valor = v;
    novo->prox = p->topo;
    p->topo = novo;
}

double pop(Pilha* p) {
    if (vazia(p)) {
        printf("Erro: pilha vazia.\n");
        exit(1);
    }
    Node* t = p->topo;
    double v = t->valor;
    p->topo = t->prox;
    free(t);
    return v;
}

void libera_pilha(Pilha* p) {
    while (!vazia(p)) pop(p);
    free(p);
}

double calculaRPN(char* expr) {
    Pilha* p = cria_pilha();
    char* token = strtok(expr, " ");
    while (token != NULL) {
        if (strcmp(token, "+") == 0) {
            double b = pop(p), a = pop(p);
            push(p, a + b);
        } else if (strcmp(token, "-") == 0) {
            double b = pop(p), a = pop(p);
            push(p, a - b);
        } else if (strcmp(token, "*") == 0) {
            double b = pop(p), a = pop(p);
            push(p, a * b);
        } else if (strcmp(token, "/") == 0) {
            double b = pop(p), a = pop(p);
            if (b == 0) {
                printf("Erro: divisao por zero.\n");
                exit(1);
            }
            push(p, a / b);
        } else {
            push(p, atof(token));
        }
        token = strtok(NULL, " ");
    }
    double r = pop(p);
    if (!vazia(p)) {
        printf("Erro: expressao invalida.\n");
        exit(1);
    }
    libera_pilha(p);
    return r;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s \"<expressao>\"\n", argv[0]);
        return 1;
    }
    char expr[256];
    strcpy(expr, argv[1]);
    double r = calculaRPN(expr);
    printf("Resultado: %.2f\n", r);
    return 0;
}
