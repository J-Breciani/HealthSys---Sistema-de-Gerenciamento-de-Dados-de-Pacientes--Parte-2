#include <stdio.h>
#include <ctype.h>   // Para toupper
#include <string.h>  // Para strcspn (em solicitar_termo_busca)
#include "interface.h" // Declaração das funções
#include "bd_paciente.h" // Para chamar as funções de consulta e listagem do BDPaciente
#include "paciente.h"    // Se precisarmos de MAX_NOME, MAX_CPF para buffers

/* Exibe o menu principal do sistema HealthSys. */
void exibir_menu_principal() {
    printf("\n===== HealthSys =====\n");
    printf("1 - Consultar paciente\n"); //
    printf("5 - Imprimir lista de pacientes\n"); //
    printf("Q - Sair\n"); //
    printf("=====================\n");
}

/* Obtém e valida a opção do usuário para o menu principal. */
char obter_opcao_menu_principal() {
    char opcao;
    printf("Escolha uma opcao: ");
    scanf(" %c", &opcao); // O espaço antes de %c consome newlines pendentes
    // Limpa o restante do buffer de entrada para evitar problemas com leituras futuras
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return toupper(opcao); // Retorna a opção em maiúscula para facilitar o switch no main
}

/* Exibe o submenu de consulta. */
void exibir_submenu_consulta() {
    printf("\n--- Modo de Consulta ---\n");
    printf("1 - Por nome\n"); 
    printf("2 - Por CPF\n"); 
    printf("3 - Retornar ao menu principal\n"); 
    printf("------------------------\n");
}

/* Obtém e valida a opção do usuário para o submenu de consulta. */
char obter_opcao_submenu_consulta() {
    char opcao;
    printf("Escolha uma opcao de consulta: ");
    scanf(" %c", &opcao); // Lê a opção de consulta
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
    return opcao; // Não precisa de toupper se vamos comparar com '1', '2', '3'
}

/* Solicita ao usuário o termo de busca (nome ou CPF). */
void solicitar_termo_busca(const char* tipo_busca, char* valor_digitado, int tamanho_buffer) {
    printf("%s", tipo_busca); // Ex: "Digite o nome: " ou "Digite o CPF: "
    if (fgets(valor_digitado, tamanho_buffer, stdin)) {
        // Remove o newline que fgets pode adicionar ao final da string
        valor_digitado[strcspn(valor_digitado, "\n")] = 0;
    } else {
        // Se fgets falhar, limpa o buffer e define uma string vazia
        valor_digitado[0] = '\0';
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
    }
}

/* Processa a opção de consulta escolhida pelo usuário. */
void processar_opcao_consulta(const BDPaciente* bd) {
    char opcao_submenu;
    /* Usaremos MAX_NOME para o buffer, pois é o maior entre nome e CPF */
    char termo_busca[MAX_NOME]; // Supondo que MAX_NOME é definido em paciente.h e é > MAX_CPF

    do {
        limpar_tela(); // Limpa a tela antes de mostrar o submenu
        exibir_submenu_consulta();
        opcao_submenu = obter_opcao_submenu_consulta();
        limpar_tela(); // Limpa a tela após a escolha, antes de pedir o termo ou mostrar resultados

        switch (opcao_submenu) {

            /* O primeiro caso define uma busca pelo nome do paciente*/
            case '1':
                solicitar_termo_busca("Digite o nome (ou prefixo): ", termo_busca, MAX_NOME);
                if (strlen(termo_busca) > 0) { // Verifica se o termo de busca não está vazio
                    consultar_pacientes_por_nome(bd, termo_busca); // Chama a função responsável pela consulta por nome
                } else {
                    exibir_mensagem_erro("Termo de busca por nome nao pode ser vazio."); 
                }
                pausar_execucao();
                break;

            /* O termo de busca será pelo CPF dos pacientes cadastrados*/
            case '2':
                solicitar_termo_busca("Digite o CPF (ou prefixo): ", termo_busca, MAX_CPF); // Usar MAX_CPF aqui
                if (strlen(termo_busca) > 0) { // Verifica se o termo de busca não está vazio
                    consultar_pacientes_por_cpf(bd, termo_busca); // Chama a função responsável pela consulta por CPF
                } else {
                    exibir_mensagem_erro("Termo de busca por CPF nao pode ser vazio.");
                }
                pausar_execucao();
                break;

            /* Opção de retornar ao Menu Principal */
            case '3':
                exibir_mensagem("Retornando ao menu principal...");
                break;
            
            /* Informa erro */
            default:
                exibir_mensagem_erro("Opcao de consulta invalida! Tente novamente.");
                pausar_execucao();
                break;
        }
    } while (opcao_submenu != '3');
}


/* Exibe uma mensagem de erro padronizada. */
void exibir_mensagem_erro(const char* mensagem) {
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("ERRO: %s\n", mensagem);
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}

/* Exibe uma mensagem informativa. */
void exibir_mensagem(const char* mensagem) {
    printf("\n>>> %s <<<\n", mensagem);
}

/* Limpa a tela do console (de forma simples, imprimindo novas linhas). */
void limpar_tela() {

    /* Para portabilidade simples ou se system() não for permitido: */
    for (int i = 0; i < 30; i++) { // Imprime várias linhas novas
        printf("\n");
    }
}

/* Pausa a execução até que o usuário pressione Enter. */
void pausar_execucao() {
    printf("\nPressione ENTER para continuar...");
    // getchar() sozinho pode pegar um \n residual.

    // Agora, espera pelo Enter real do usuário.
    getchar(); // Este getchar() espera o Enter do usuário.
}