#include <stdio.h>
#include "bd_paciente.h"
#include "interface.h"

int main() {
    /* Constante com o nome do arquivo CSV */
    const char* NOME_ARQUIVO = "bd_paciente.csv";

    /* 1. Cria o banco de dados em memória */
    BDPaciente* banco = bd_create();

    /* 2. Carrega os dados do arquivo para a memória */
    bd_load_csv(banco, NOME_ARQUIVO);

    /* 3. Inicia a interface com o usuário, que gerencia o programa */
    iniciarLoopPrincipal(banco);

    /* 4. Salva os dados de volta no arquivo ao sair */
    bd_save_csv(banco, NOME_ARQUIVO);
    printf("Dados salvos em '%s'. Programa encerrado.\n", NOME_ARQUIVO);

    /* 5. Libera toda a memória alocada dinamicamente */
    bd_free(banco);

    return 0;
}