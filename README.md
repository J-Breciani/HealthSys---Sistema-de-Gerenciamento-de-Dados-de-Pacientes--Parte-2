# 🏥 HealthSys - Sistema de Gerenciamento de Dados de Pacientes (Parte II)

Este projeto consiste na **implementação da segunda e última parte de um sistema para gerenciamento de pacientes**, desenvolvido em linguagem C.  
O sistema oferece funcionalidades de **Cadastro, Consulta, Atualização, Remoção e Listagem** de registros, utilizando uma **lista encadeada dinâmica (TAD LinkedList)** para um gerenciamento de memória eficiente e número ilimitado de pacientes.

---

## 📚 Projeto da Disciplina

> **Disciplina:** Estrutura de Dados  
> **Período:** 3º Período – Bacharelado em Sistemas de Informação  
> **Instituição:** IFES – Campus Serra  
> **Professor:** Thiago M. Paixão  
> **Alunas:** Lívia Rosario e Jullyana Breciani  

---

## 🚀 Começando

### 📋 Pré-requisitos

- Linux Ubuntu 22.04  
- GCC versão 11  

### 🔧 Instalação

1️⃣ Clone o repositório:
```bash
git clone https://github.com/J-Breciani/HealthSys---Sistema-de-Gerenciamento-de-Dados-de-Pacientes--Parte-2.git
cd HealthSys---Sistema-de-Gerenciamento-de-Dados-de-Pacientes--Parte-2
```
2️⃣ Compile o projeto:
```bash
gcc main.c interface.c bd_paciente.c paciente.c -o healthsys
```
3️⃣ Garanta que o arquivo `bd_paciente.csv` esteja no diretório do executável. Se não existir, o sistema criará um novo ao salvar.

---

## ▶️ Execução

```bash
./healthsys
```
💡 O sistema carrega automaticamente os dados ao iniciar e salva as alterações ao encerrar.

---

## 🗂️ Estrutura do Repositório

```
.
├── main.c               # Ponto de entrada
├── paciente.h           # Definição do struct Paciente
├── paciente.c           # Funções auxiliares (se houver)
├── bd_paciente.h/.c     # TAD da lista encadeada de pacientes
├── interface.h/.c       # Interação com o usuário e menus
├── bd_paciente.csv      # Banco de dados
└── README.md            # Documentação
```

---

## 🧱 Principais TADs e Funções

### `Paciente`
```c
typedef struct {
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[11];
} Paciente;
```
| Função | Descrição |
|---|---|
| `imprimir_paciente(p)` | Exibe os dados de um paciente formatados. |

### `BDPaciente`
| Função | Descrição |
|---|---|
| `bd_create()` | Inicializa o banco em memória. |
| `bd_free()` | Libera a memória do banco. |
| `bd_append(paciente)` | Adiciona paciente ao final da lista. |
| `bd_remove(id)` | Remove paciente pelo ID. |
| `bd_load_csv(filepath)` | Carrega dados do CSV. |
| `bd_save_csv(filepath)` | Salva dados no CSV. |
| `bd_find_by_id(id)` | Busca paciente por ID. |
| `bd_find_by_cpf(cpf)` | Busca paciente por CPF. |
| `bd_update_node_info(node, paciente)` | Atualiza os dados de um nó. |

### `Interface`
| Função | Descrição |
|---|---|
| `iniciarLoopPrincipal()` | Gerencia o menu principal. |
| `ui_inserirPaciente()` | Fluxo de cadastro com validação. |
| `ui_atualizarPaciente()` | Fluxo de atualização de registro. |
| `ui_removerPaciente()` | Fluxo de remoção com confirmação. |
| `ui_consultarPaciente()` | Consulta por nome ou CPF. |
| `ui_imprimirLista()` | Listagem paginada de pacientes. |

---

## 🧠 Decisões de Implementação

- **Lista encadeada dinâmica:** Para eliminar limite fixo e otimizar uso de memória.
- **Persistência automática:** Salva automaticamente após inserção, atualização e remoção.
- **Validação completa:** Verificação de CPF, idade e duplicidade durante inserção e atualização.
- **UX aprimorada:** Uso de cores e limpeza de tela para maior clareza no terminal.
- **Modularização:** Divisão em módulos com alta coesão e baixo acoplamento.

---

## 📌 Limitações

- Busca linear pode ser lenta em bases muito grandes.
- O CSV precisa estar bem formatado; não há tratamento para linhas corrompidas.

---

## 📈 Futuras Expansões

- Implementar árvore ou hash table para acelerar buscas.
- Criar testes automatizados.
- Usar formato binário ou banco como SQLite para persistência.
- Desenvolver uma interface gráfica.

---

## 🛠️ Construído com

- **C (GCC)**  
- **Linux Ubuntu 22.04**
