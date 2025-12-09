# Hotel
Hotelzinho
## Sistema de Gestão - Hotel Descanso Garantido 🏨
Este projeto consiste no desenvolvimento de um sistema de software para gestão do Hotel Descanso Garantido, localizado em Itacaré - BA.
O objetivo é informatizar os processos de controle de estadias, clientes e funcionários, substituindo o uso de planilhas e cadernos manuais e garantindo a integridade dos dados através de persistência em arquivos binários.
Trabalho Interdisciplinar desenvolvido para os cursos de Engenharia de Software da PUC Minas.

### Autores (Grupo)
Matheus Nicoli
Christiano Gonçalves
Thiago Nobre

### Disciplinas e Contexto
Instituição: Pontifícia Universidade Católica de Minas Gerais (PUC Minas)
Curso: Engenharia de Software
Disciplinas Integradas:
- Fundamentos de Engenharia de Software
- Algoritmos e Estruturas de Dados I
Professor: Roberto Rocha e Larte Xavier


### Funcionalidades do Sistema
O sistema foi desenvolvido em Linguagem C e implementa as seguintes funcionalidades:
1. Cadastros (CRUD)
- Clientes: Cadastro com validação de código único
- Funcionários: Registro de equipe com cargos e salários
- Quartos: Controle de capacidade, valor da diária e status (Ocupado/Desocupado)
2. Gestão de Estadias (Core)
- Check-in Inteligente: O sistema localiza automaticamente quartos disponíveis compatíveis com a quantidade de hóspedes solicitada para o período desejado
- Validações: Impede conflito de datas (reservar quarto já ocupado) e verifica existência de cadastros prévios
- Check-out (Baixa): Calcula o valor total a ser pago, libera o quarto (status "desocupado") e gera pontos de fidelidade
3. Programa de Fidelidade
- Cálculo automático de 10 pontos de fidelidade para cada diária utilizada pelo cliente
4. Relatórios e Pesquisas
- Pesquisa de Clientes e Funcionários por nome ou código
- Histórico de todas as estadias de um cliente específico

### Arquitetura e Estrutura de Arquivos
O projeto segue uma estrutura modularizada utilizando bibliotecas próprias e persistência de dados em arquivos de acesso direto (binários).

Arquivos de Código Fonte
- main.c: Contém o menu principal e o loop de interação com o usuário
- hotel.h: Biblioteca (Header): Definição das structs e protótipos das funções
- hotel.c: Implementação: Lógica de negócio, manipulação de arquivos e validações
- testes.c: Suíte de testes automatizados utilizando o framework µnit (Munit)

Arquivos de Dados (Gerados Automaticamente)
- clientes.bin
- funcionarios.bin
- quartos.bin
- estadias.bin

### Como Compilar e Executar
Pré-requisitos
- Compilador GCC instalado.
- Ambiente Windows, Linux ou MacOS.

1. Compilar o Sistema Principal (Hotel)
Para utilizar o sistema de gestão, compile o menu principal junto com a biblioteca do hotel:

```bash
gcc main.c hotel.c -o hotel_sistema
./hotel_sistema
```

2. Executar os Testes Automatizados
O projeto utiliza a biblioteca µnit para testes unitários. Para validar as funções:

```bash
gcc testes.c hotel.c munit.c -o executar_testes
./executar_testes
```

Observação: Certifique-se de que os arquivos munit.c e munit.h estejam na pasta do projeto.

### Metodologia
O desenvolvimento seguiu a metodologia Scrum, com divisão de tarefas em sprints, controle de backlog e versionamento via Git.
Foram realizados testes unitários para garantir a confiabilidade dos módulos desenvolvidos.
