#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
} Data;

typedef struct {
    char nome[40];
    char telefone[15];
    char celular[15];
    char email[40];
    Data dataAniversario;
} Contato;

typedef struct elemento {
    Contato info;
    struct elemento* prox;
} Elemento;

Elemento* cria_agenda() {
    return NULL;
}

void limparBufferTeclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Elemento* insere_contato(Elemento* lista) {
    Elemento* novo = (Elemento*) malloc(sizeof(Elemento));
    printf("\n--- Novo Contato ---\n");
    printf("Nome: ");
    scanf(" %39[^\n]", novo->info.nome); 
    printf("Telefone: ");
    scanf(" %14[^\n]", novo->info.telefone);
    printf("Celular: ");
    scanf(" %14[^\n]", novo->info.celular);
    printf("Email: ");
    scanf(" %39[^\n]", novo->info.email);
    printf("Aniversario (DD MM): ");
    scanf("%d %d", &novo->info.dataAniversario.dia, &novo->info.dataAniversario.mes);
    novo->prox = NULL;

    if (lista == NULL) {
        printf("Contato salvo!\n");
        return novo; 
    }

    Elemento* atual = lista;
    while (atual->prox != NULL) atual = atual->prox;
    atual->prox = novo;
    printf("Contato salvo!\n");
    return lista;
}

void lista_contatos(Elemento* lista) {
    if (lista == NULL) {
        printf("\nAgenda vazia.\n");
        return;
    }
    Elemento* atual = lista;
    printf("\n--- Lista de Contatos ---\n");
    while (atual != NULL) {
        printf("Nome: %s\n", atual->info.nome);
        printf("Telefone: %s\n", atual->info.telefone);
        printf("Celular: %s\n", atual->info.celular);
        printf("Email: %s\n", atual->info.email);
        printf("Aniversario: %d/%d\n", atual->info.dataAniversario.dia, atual->info.dataAniversario.mes);
        printf("---------------------------\n");
        atual = atual->prox; 
    }
}

Elemento* busca_contato(Elemento* lista, char* nome) {
    Elemento* atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->info.nome, nome) == 0)
            return atual;
        atual = atual->prox;
    }
    return NULL; 
}

Elemento* remove_contato(Elemento* lista) {
    char nome[40];
    printf("\nQual nome deseja remover? ");
    scanf(" %39[^\n]", nome);
    Elemento *ant = NULL, *atual = lista;

    while (atual != NULL && strcmp(atual->info.nome, nome) != 0) {
        ant = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Contato nao encontrado.\n");
        return lista;
    }

    if (ant == NULL)
        lista = atual->prox;
    else
        ant->prox = atual->prox;

    free(atual);
    printf("Contato removido!\n");
    return lista;
}

void atualiza_contato(Elemento* lista) {
    char nome[40];
    printf("\nQual nome deseja editar? ");
    scanf(" %39[^\n]", nome);
    Elemento* c = busca_contato(lista, nome);

    if (c == NULL) {
        printf("Contato nao encontrado.\n");
        return;
    }

    printf("Novo Nome: ");
    scanf(" %39[^\n]", c->info.nome);
    printf("Novo Telefone: ");
    scanf(" %14[^\n]", c->info.telefone);
    printf("Novo Celular: ");
    scanf(" %14[^\n]", c->info.celular);
    printf("Novo Email: ");
    scanf(" %39[^\n]", c->info.email);
    printf("Novo Aniversario (DD MM): ");
    scanf("%d %d", &c->info.dataAniversario.dia, &c->info.dataAniversario.mes);
    printf("Contato atualizado!\n");
}

int main() {
    Elemento* agenda = cria_agenda();
    int opcao = 0;

    do {
        printf("\n--- AGENDA ---\n");
        printf("1. Inserir\n2. Listar\n3. Buscar\n4. Editar\n5. Remover\n6. Sair\nEscolha: ");
        scanf("%d", &opcao);
        limparBufferTeclado();

        switch(opcao) {
            case 1: agenda = insere_contato(agenda); break;
            case 2: lista_contatos(agenda); break;
            case 3: {
                char nome[40];
                printf("Nome: ");
                scanf(" %39[^\n]", nome);
                Elemento* c = busca_contato(agenda, nome);
                if (c != NULL)
                    printf("\nNome: %s\nTelefone: %s\nCelular: %s\n", c->info.nome, c->info.telefone, c->info.celular);
                else
                    printf("Contato nao encontrado.\n");
                break;
            }
            case 4: atualiza_contato(agenda); break;
            case 5: agenda = remove_contato(agenda); break;
            case 6: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }

        if (opcao != 6) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    } while (opcao != 6);

    return 0;
}
