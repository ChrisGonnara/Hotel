#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h" // Importa as structs do arquivo .h

// --- Funções Auxiliares (Internas) ---

// Função para limpar o buffer do teclado (substitui fflush em alguns casos)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para gerar código automático baseado no tamanho do arquivo
int gerarCodigo(char *nomeArquivo, size_t tamanhoStruct) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) return 1; // Se arquivo não existe, começa do 1
    fseek(arquivo, 0, SEEK_END);
    int qtd = ftell(arquivo) / tamanhoStruct;
    fclose(arquivo);
    return qtd + 1;
}

// --- Implementação das Funções Principais ---

void cadastrarCliente() {
    Cliente c;
    FILE *arquivo = fopen("clientes.dat", "ab");
    if (arquivo == NULL) { printf("Erro ao abrir arquivo!\n"); return; }

    printf("\n--- Cadastro de Cliente ---\n");
    c.codigo = gerarCodigo("clientes.dat", sizeof(Cliente));
    printf("Codigo gerado: %d\n", c.codigo);

    limparBuffer(); 
    printf("Nome: ");
    fgets(c.nome, 100, stdin);
    c.nome[strcspn(c.nome, "\n")] = 0; // Remove o enter do final

    printf("Endereco: ");
    fgets(c.endereco, 100, stdin);
    c.endereco[strcspn(c.endereco, "\n")] = 0;

    printf("Telefone: ");
    fgets(c.telefone, 20, stdin);
    c.telefone[strcspn(c.telefone, "\n")] = 0;

    fwrite(&c, sizeof(Cliente), 1, arquivo);
    fclose(arquivo);
    printf("Cliente salvo com sucesso!\n");
}

void cadastrarFuncionario() {
    Funcionario f;
    FILE *arquivo = fopen("funcionarios.dat", "ab");
    if (arquivo == NULL) { printf("Erro ao abrir arquivo!\n"); return; }

    printf("\n--- Cadastro de Funcionario ---\n");
    f.codigo = gerarCodigo("funcionarios.dat", sizeof(Funcionario));
    printf("Codigo gerado: %d\n", f.codigo);

    limparBuffer();
    printf("Nome: ");
    fgets(f.nome, 100, stdin);
    f.nome[strcspn(f.nome, "\n")] = 0;

    printf("Cargo: ");
    fgets(f.cargo, 50, stdin);
    f.cargo[strcspn(f.cargo, "\n")] = 0;

    printf("Salario: ");
    scanf("%f", &f.salario);

    fwrite(&f, sizeof(Funcionario), 1, arquivo);
    fclose(arquivo);
    printf("Funcionario salvo com sucesso!\n");
}

void cadastrarQuarto() {
    Quarto q;
    FILE *arquivo = fopen("quartos.dat", "ab");
    if (arquivo == NULL) { printf("Erro ao abrir arquivo!\n"); return; }

    printf("\n--- Cadastro de Quarto ---\n");
    printf("Numero do Quarto: ");
    scanf("%d", &q.numero);
    
    printf("Capacidade de Hospedes: ");
    scanf("%d", &q.quantidadeHospedes);

    printf("Valor da Diaria: ");
    scanf("%f", &q.valorDiaria);

    q.status = 0; // 0 = Livre

    fwrite(&q, sizeof(Quarto), 1, arquivo);
    fclose(arquivo);
    printf("Quarto salvo com sucesso!\n");
}

void cadastrarEstadia() {
    Estadia e;
    Quarto q;
    int encontrouQuarto = 0;

    printf("\n--- Cadastro de Estadia ---\n");
    printf("Codigo do Cliente: ");
    scanf("%d", &e.codigoCliente);

    printf("Numero do Quarto desejado: ");
    scanf("%d", &e.numeroQuarto);

    // Verificar se o quarto existe e está livre
    FILE *arqQuarto = fopen("quartos.dat", "rb+");
    if (arqQuarto != NULL) {
        while(fread(&q, sizeof(Quarto), 1, arqQuarto)) {
            if(q.numero == e.numeroQuarto) {
                if(q.status == 1) {
                    printf("Erro: Quarto ja esta ocupado!\n");
                    fclose(arqQuarto);
                    return;
                }
                q.status = 1; // Ocupa o quarto
                fseek(arqQuarto, -sizeof(Quarto), SEEK_CUR); // Volta o cursor para atualizar
                fwrite(&q, sizeof(Quarto), 1, arqQuarto);
                encontrouQuarto = 1;
                break;
            }
        }
        fclose(arqQuarto);
    } else {
        printf("Erro: Nenhum quarto cadastrado.\n");
        return;
    }

    if (!encontrouQuarto) {
        printf("Quarto nao encontrado!\n");
        return;
    }

    limparBuffer();
    e.codigoEstadia = gerarCodigo("estadias.dat", sizeof(Estadia));
    
    printf("Data de Entrada (DD/MM/AAAA): ");
    fgets(e.dataEntrada, 11, stdin);
    limparBuffer();

    printf("Quantidade de Diarias: ");
    scanf("%d", &e.quantidadeDiarias);

    strcpy(e.dataSaida, "Aberto");
    e.ativa = 1; 

    FILE *arqEstadia = fopen("estadias.dat", "ab");
    fwrite(&e, sizeof(Estadia), 1, arqEstadia);
    fclose(arqEstadia);

    printf("Check-in realizado! Codigo da Estadia: %d\n", e.codigoEstadia);
}

void darBaixaEstadia() {
    int numQuarto;
    Estadia e;
    Quarto q;
    int achouEstadia = 0;
    float valorTotal = 0.0;

    printf("\n--- Baixa de Estadia ---\n");
    printf("Digite o numero do quarto para checkout: ");
    scanf("%d", &numQuarto);

    FILE *arqEstadia = fopen("estadias.dat", "rb+");
    if (arqEstadia == NULL) { printf("Sem estadias registradas.\n"); return; }

    while(fread(&e, sizeof(Estadia), 1, arqEstadia)) {
        if(e.numeroQuarto == numQuarto && e.ativa == 1) {
            
            // Buscar valor da diária no arquivo de quartos e liberar quarto
            FILE *arqQuarto = fopen("quartos.dat", "rb+");
            while(fread(&q, sizeof(Quarto), 1, arqQuarto)) {
                if(q.numero == numQuarto) {
                    valorTotal = q.valorDiaria * e.quantidadeDiarias;
                    q.status = 0; // Libera quarto
                    fseek(arqQuarto, -sizeof(Quarto), SEEK_CUR);
                    fwrite(&q, sizeof(Quarto), 1, arqQuarto);
                    break;
                }
            }
            fclose(arqQuarto);

            // Finalizar estadia
            e.ativa = 0;
            printf("Data de Saida (DD/MM/AAAA): ");
            limparBuffer();
            fgets(e.dataSaida, 11, stdin);
            
            fseek(arqEstadia, -sizeof(Estadia), SEEK_CUR);
            fwrite(&e, sizeof(Estadia), 1, arqEstadia);
            
            achouEstadia = 1;
            break;
        }
    }
    fclose(arqEstadia);

    if(achouEstadia) {
        printf("\n=== Checkout Sucesso ===\n");
        printf("Total a pagar: R$ %.2f\n", valorTotal);
    } else {
        printf("Nenhuma estadia ativa encontrada para este quarto.\n");
    }
}

void pesquisarCliente() {
    char nomeBusca[100];
    Cliente c;
    int encontrou = 0;

    limparBuffer();
    printf("\nDigite o nome (ou parte) para buscar: ");
    fgets(nomeBusca, 100, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    FILE *arquivo = fopen("clientes.dat", "rb");
    if (arquivo == NULL) { printf("Nenhum registro.\n"); return; }

    while(fread(&c, sizeof(Cliente), 1, arquivo)) {
        if(strstr(c.nome, nomeBusca) != NULL) {
            printf("ID: %d | Nome: %s | Tel: %s\n", c.codigo, c.nome, c.telefone);
            encontrou = 1;
        }
    }
    fclose(arquivo);
    if(!encontrou) printf("Ninguem encontrado.\n");
}

void pesquisarFuncionario() {
    char nomeBusca[100];
    Funcionario f;
    int encontrou = 0;

    limparBuffer();
    printf("\nDigite o nome do funcionario: ");
    fgets(nomeBusca, 100, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    FILE *arquivo = fopen("funcionarios.dat", "rb");
    if (arquivo == NULL) { printf("Nenhum registro.\n"); return; }

    while(fread(&f, sizeof(Funcionario), 1, arquivo)) {
        if(strstr(f.nome, nomeBusca) != NULL) {
            printf("ID: %d | Nome: %s | Cargo: %s\n", f.codigo, f.nome, f.cargo);
            encontrou = 1;
        }
    }
    fclose(arquivo);
    if(!encontrou) printf("Ninguem encontrado.\n");
}

void mostrarEstadiasCliente() {
    int codCliente;
    Estadia e;
    int encontrou = 0;

    printf("\nDigite o Codigo do Cliente: ");
    scanf("%d", &codCliente);

    FILE *arquivo = fopen("estadias.dat", "rb");
    if (arquivo == NULL) { printf("Nenhuma estadia registrada.\n"); return; }

    printf("\n--- Historico ---\n");
    while(fread(&e, sizeof(Estadia), 1, arquivo)) {
        if(e.codigoCliente == codCliente) {
            printf("Quarto: %d | Entrada: %s | Status: %s\n", 
                   e.numeroQuarto, e.dataEntrada, e.ativa ? "Ativa" : "Finalizada");
            encontrou = 1;
        }
    }
    fclose(arquivo);
    if(!encontrou) printf("Nada encontrado para este cliente.\n");
}