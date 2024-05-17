#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbd_agenda.h"

void inicializar(CLIENT *clnt) {
    void *result = inicializar_1(NULL, clnt);
    if (result == NULL) {
        printf("Erro ao inicializar a agenda.\n");
    } else {
        printf("################## Agenda inicializada com sucesso ##################n");
    }
}

void insere(CLIENT *clnt, contato *c) {
    int *result = insere_1(c, clnt);
    if (result == NULL || *result == 0) {
        printf("-->Erro ao inserir contato.\n");
    } else {
        printf("-->Contato inserido com sucesso.\n");
    }
}

void remover_contato(CLIENT *clnt, char *nome) {
    int *result = remove_1(&nome, clnt);
    if (result == NULL || *result == 0) {
        printf("-->Erro ao remover contato.\n");
    } else {
        printf("-->Contato removido com sucesso.\n");
    }
}

void busca(CLIENT *clnt, char *nome) {
    contato *result = busca_1(&nome, clnt);
    if (result == NULL || result->nome[0] == '\0') {
        printf("-->Contato não encontrado.\n");
    } else {
        printf("-->Contato encontrado:\nNome: %s\nCPF: %s\nTelefone: %s\nEndereço: %s\n",
               result->nome, result->cpf, result->telefone, result->endereco);
    }
}

void lista(CLIENT *clnt) {
    agenda *result = lista_1(NULL, clnt);
    if (result == NULL) {
        printf("-->Erro ao listar contatos.\n");
    } else{
        printf("-->Contatos cadastrados:\n");
        for (int i = 0; i < result->tam; i++) {
            printf("%s\n", result->contatos[i].nome);
        }
        }
    
}

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    char *server;
    int opcao;
    char nome[50];

    if (argc < 2) {
        printf("Uso: %s <servidor>\n", argv[0]);
        exit(1);
    }
    server = argv[1];

    clnt = clnt_create(server, RBDPROG, RDBVERS, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(server);
        exit(1);
    }
    inicializar(clnt);

    // Menu interativo
    while (1) {
        printf("\n1. Inserir contato\n");
        printf("2. Remover contato\n");
        printf("3. Buscar contato\n");
        printf("4. Listar contatos\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                {
                    contato c;
                    printf("Digite o nome: ");
                    scanf("%s", c.nome);
                    printf("Digite o CPF: ");
                    scanf("%s", c.cpf);
                    printf("Digite o telefone: ");
                    scanf("%s", c.telefone);
                    printf("Digite o endereço: ");
                    scanf("%s", c.endereco);
                    insere(clnt, &c);
                    break;
                }
            case 2:
                printf("Digite o nome do contato a ser removido: ");
                scanf("%s", nome);
                remover_contato(clnt, nome);
                break;
            case 3:
                printf("Digite o nome do contato a ser buscado: ");
                scanf("%s", nome);
                busca(clnt, nome);
                break;
            case 4:
                lista(clnt);
                break;
            case 5:
                clnt_destroy(clnt);
                exit(0);
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}

