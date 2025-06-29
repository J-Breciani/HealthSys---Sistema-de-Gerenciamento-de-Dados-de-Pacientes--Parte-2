
#ifndef INTERFACE_H
#define INTERFACE_H

#include "bd_paciente.h" // Para usar BDPaciente nas funções da interface

/* Exibe o menu principal do sistema. */
void exibir_menu_principal();

/* Obtém a opção do usuário para o menu principal (retorna '1', '5', ou 'Q' em maiúscula). */
char obter_opcao_menu_principal();

/* Gerencia o submenu e o processo de consulta de pacientes. */
void processar_opcao_consulta(const BDPaciente* bd);

/*  Exibe o submenu de opções de consulta. */
void exibir_submenu_consulta();

/* Obtém a opção do usuário para o submenu de consulta (retorna '1', '2', ou '3'). */
char obter_opcao_submenu_consulta();

/* Solicita ao usuário um termo para busca (nome ou CPF).
 'tipo_busca' é a mensagem prompt, 'valor_digitado' é o buffer, 'tamanho_buffer' é seu tamanho. */
void solicitar_termo_busca(const char* tipo_busca, char* valor_digitado, int tamanho_buffer);

/* Exibe uma mensagem de erro formatada. */
void exibir_mensagem_erro(const char* mensagem);

/* Exibe uma mensagem informativa formatada. */
void exibir_mensagem(const char* mensagem);

/* "Limpa" a tela do console (imprimindo várias linhas novas). */
void limpar_tela();

/* Pausa a execução e aguarda o usuário pressionar ENTER. */
void pausar_execucao();

#endif // INTERFACE_H
