# 🏨 Hotel Descanso Garantido | Sistema de Gestão

> **Trabalho Interdisciplinar - Engenharia de Software (PUC Minas)** > *Automatização de processos hoteleiros com persistência de dados em C.*

---

## 📖 Sobre o Projeto
Este projeto consiste no desenvolvimento de um sistema de software para a gestão do **Hotel Descanso Garantido**, localizado em Itacaré - BA. 

O objetivo principal é a informatização dos processos de controle de estadias, clientes e funcionários, substituindo o uso de planilhas e controles manuais. O sistema garante a integridade e o armazenamento dos dados através de **persistência em arquivos binários**, assegurando que as informações não sejam perdidas ao fechar o programa.

### 🎓 Contexto Acadêmico
* **Instituição:** Pontifícia Universidade Católica de Minas Gerais (PUC Minas)
* **Curso:** Engenharia de Software
* **Disciplinas Integradas:** * Fundamentos de Engenharia de Software
    * Algoritmos e Estruturas de Dados I
* **Professores:** Roberto Rocha e Laerte Xavier

---

## ⚙️ Funcionalidades

O sistema foi desenvolvido seguindo os princípios da programação estruturada e modular.

### 1. Cadastros (CRUD)
* **👥 Clientes:** Cadastro completo com validação de código único.
* **👔 Funcionários:** Registro da equipe administrativa e operacional (com cargos e salários).
* **🛏️ Quartos:** Gestão de capacidade, definição de valor da diária e controle de status (*Livre/Ocupado*).

### 2. Gestão de Estadias (Core)
* **Check-in Inteligente:** O sistema verifica disponibilidade e impede conflitos de datas (reservar um quarto já ocupado).
* **Check-out Automatizado:** Realiza a baixa no sistema, libera o status do quarto para "Desocupado" e calcula o valor total a pagar.
* **Validações:** Garante que apenas clientes e quartos cadastrados possam gerar uma estadia.

### 3. Diferenciais
* **💎 Programa de Fidelidade:** Cálculo automático de **10 pontos** de fidelidade para cada diária utilizada.
* **🔍 Relatórios e Pesquisas:** * Busca rápida de Clientes e Funcionários (por nome).
    * Histórico completo de estadias de um cliente específico.

---

## 📂 Estrutura de Arquivos

O projeto utiliza **Modularização** para separar a interface, a lógica e os dados.

| Arquivo | Descrição |
| :--- | :--- |
| `main.c` | **Interface:** Contém o menu principal e o loop de interação com o usuário. |
| `hotel.h` | **Cabeçalho:** Definição das `structs`, constantes e protótipos das funções. |
| `hotel.c` | **Implementação:** Lógica de negócio, manipulação de arquivos binários (`.dat`) e validações. |
| `testes.c` | **QA:** Suíte de testes automatizados utilizando o framework **µnit**. |

---

## 🚀 Como Compilar e Executar

### Pré-requisitos
* Compilador **GCC** instalado.
* Ambiente Windows, Linux ou macOS.
* Biblioteca **Munit** (arquivos `munit.c` e `munit.h`) na pasta raiz (necessário apenas para rodar os testes).

### 1. Executando o Sistema (Hotel)
Para utilizar o sistema de gestão, compile o menu principal junto com a implementação das funções:

```bash
# Compilar
gcc main.c hotel.c -o sistema_hotel

# Executar (Linux/Mac)
./sistema_hotel

# Executar (Windows)
sistema_hotel.exe

🛠️ Metodologia e Ferramentas
Metodologia Ágil: O desenvolvimento seguiu o framework Scrum, com divisão de tarefas em sprints e controle de backlog.

Linguagem: C (C99 Standard).

Persistência: Arquivos Binários (wb, rb, ab).

Testes: Framework Munit.

Versionamento: Git & GitHub.

👨‍💻 Autores
Matheus Nicoli

Christiano Gonçalves

Thiago Nobre