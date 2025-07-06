#include <stdio.h>
#include "paciente.h"
#include "interface.h"

/* Função para imprimir as informações do paciente */
void imprimir_paciente(const Paciente* p) { 
    if (p != NULL) { // Verifica se o ponteiro do paciente é nulo
        printf("%-5d %-15s %-30s %-10d %-15s\n", // Ajeitar a impressão
               p->id,
               p->cpf,
               p->nome,
               p->idade,
               p->data_cadastro); 
    }
}