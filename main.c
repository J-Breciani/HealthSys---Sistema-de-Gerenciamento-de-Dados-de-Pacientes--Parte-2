#include <stdio.h>
#include <stdlib.h> // Para EXIT_SUCCESS e EXIT_FAILURE

/* Nossos módulos */
#include "paciente.h"    // Embora não usemos diretamente Paciente aqui, os outros módulos dependem dele.
#include "bd_paciente.h" // Para gerenciar o banco de dados de pacientes
#include "interface.h"   // Para todas as interações com o usuário

/* Constantes definidas para o programa principal */
#define ARQUIVO_CSV "bd_paciente.csv"
#define ITENS_POR_PAGINA 10

int main() {
    BDPaciente banco_de_dados; // Nossa estrutura principal para armazenar os dados
    char opcao_menu;

    /* 1. Inicializar o TAD BDPaciente */
    inicializar_bd(&banco_de_dados); // Define a quantidade_atual de pacientes como 0.

    /* 2. Carregar os dados do arquivo CSV para a memória */
    if (!carregar_dados_csv(&banco_de_dados, ARQUIVO_CSV)) {
        exibir_mensagem_erro("Falha ao carregar dados do arquivo CSV. Verifique se 'bd_paciente.csv' existe e esta formatado corretamente.");
        return EXIT_FAILURE; // Termina o programa se não conseguir carregar os dados
    }
   

    // 3. Loop principal do menu
    do {
        limpar_tela();
        exibir_menu_principal(); // Mostra as opções: 1-Consultar, 5-Imprimir, Q-Sair
        opcao_menu = obter_opcao_menu_principal(); // Pega a escolha do usuário

        limpar_tela(); // Limpa a tela antes de processar a opção

        switch (opcao_menu) {
            case '1': // Consultar paciente
                processar_opcao_consulta(&banco_de_dados);
                // A função processar_opcao_consulta já inclui pausas internas.
                break;

            case '5': // Imprimir lista de pacientes
                exibir_mensagem("Imprimindo lista de pacientes...");
                imprimir_lista_pacientes_paginada(&banco_de_dados, ITENS_POR_PAGINA);
                pausar_execucao(); // Pausa após a listagem completa
                break;

            case 'Q': // Sair do sistema
                exibir_mensagem("Encerrando o HealthSys. Ate logo!");
                break;

            default: // Opção inválida
                exibir_mensagem_erro("Opcao invalida! Por favor, escolha uma das opcoes do menu.");
                pausar_execucao(); // Pausa para o usuário ler a mensagem de erro
                break;
        }

    } while (opcao_menu != 'Q');

    return EXIT_SUCCESS; // Indica que o programa terminou com sucesso
}