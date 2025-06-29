// Em paciente.c
#include <stdio.h>
#include "paciente.h"

void imprimir_paciente(const Paciente* p) {
    if (p != NULL) {
        /* ID   CPF              Nome                            Idade  Data Cadastro */
        printf("%-4d %-15s %-30s %-6d %-10s\n",
               p->id,
               p->cpf,
               p->nome,
               p->idade,
               p->data_cadastro);
    }
}