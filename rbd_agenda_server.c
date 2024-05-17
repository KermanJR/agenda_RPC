#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rbd_agenda.h"

static agenda agenda_data;

void *inicializar_1_svc(void *argp, struct svc_req *rqstp) {
    static int result;
    agenda_data.tam = 0;
    result = 1;
    return &result;
}

int *insere_1_svc(contato *argp, struct svc_req *rqstp) {
    static int result;
    if (agenda_data.tam < 100) {
        agenda_data.contatos[agenda_data.tam++] = *argp;
        result = 1;
    } else {
        result = 0; // Agenda cheia
    }
    return &result;
}

int *remove_1_svc(char **argp, struct svc_req *rqstp) {
    static int result;
    result = 0;
    for (int i = 0; i < agenda_data.tam; i++) {
        if (strcmp(agenda_data.contatos[i].nome, *argp) == 0) {
            for (int j = i; j < agenda_data.tam - 1; j++) {
                agenda_data.contatos[j] = agenda_data.contatos[j + 1];
            }
            agenda_data.tam--;
            result = 1;
            break;
        }
    }
    return &result;
}

contato *busca_1_svc(char **argp, struct svc_req *rqstp) {
    static contato result;
    for (int i = 0; i < agenda_data.tam; i++) {
        if (strcmp(agenda_data.contatos[i].nome, *argp) == 0) {
            result = agenda_data.contatos[i];
            return &result;
        }
    }
    memset(&result, 0, sizeof(result)); 
    return &result;
}

agenda *lista_1_svc(void *argp, struct svc_req *rqstp) {
    return &agenda_data;
}

