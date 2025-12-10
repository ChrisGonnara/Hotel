#include "hotel.h"

#define CLIENTES_FILE "clientes_novo.dat"
#define FUNCIONARIOS_FILE "funcionarios_novo.dat"
#define QUARTOS_FILE "quartos_novo.dat"
#define ESTADIAS_FILE "estadias_novo.dat"


int gerarNovoCodigoCliente() {
    FILE *f = fopen(CLIENTES_FILE, "rb");
    int count = 0;
    if (f != NULL) {
        Cliente c;
        while (fread(&c, sizeof(Cliente), 1, f) == 1) {
            count++;
        }
        fclose(f);
    }
    return count + 1;
}

int gerarNovoCodigoFuncionario() {
    FILE *f = fopen(FUNCIONARIOS_FILE, "rb");
    int count = 0;
    if (f != NULL) {
        Funcionario x;
        while (fread(&x, sizeof(Funcionario), 1, f) == 1) {
            count++;
        }
        fclose(f);
    }
    return count + 1;
}

int gerarNovoCodigoEstadia() {
    FILE *f = fopen(ESTADIAS_FILE, "rb");
    int count = 0;
    if (f != NULL) {
        Estadia e;
        while (fread(&e, sizeof(Estadia), 1, f) == 1) {
            count++;
        }
        fclose(f);
    }
    return count + 1;
}

int clienteExiste(int codigo) {
    FILE *f = fopen(CLIENTES_FILE, "rb");
    if (f == NULL) return 0;
    Cliente c;
    while (fread(&c, sizeof(Cliente), 1, f) == 1) {
        if (c.codigo == codigo) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int obterCodigoClientePorNome(const char *nomeBusca) {
    FILE *f = fopen(CLIENTES_FILE, "rb");
    if (f == NULL) return -1;
    Cliente c;
    while (fread(&c, sizeof(Cliente), 1, f) == 1) {
        if (strstr(c.nome, nomeBusca) != NULL) {
            fclose(f);
            return c.codigo;
        }
    }
    fclose(f);
    return -1;
}

int dataParaDias(const char *data) {
    int d, m, a;
    if (sscanf(data, "%d/%d/%d", &d, &m, &a) != 3) return 0;
    return a * 365 + m * 30 + d;
}

int diferencaDias(const char *entrada, const char *saida) {
    return dataParaDias(saida) - dataParaDias(entrada);
}

int quartoDisponivelPeriodo(int numeroQuarto, const char *entrada, const char *saida) {
    FILE *f = fopen(ESTADIAS_FILE, "rb");
    if (f == NULL) return 1;

    Estadia e;
    int iniNovo = dataParaDias(entrada);
    int fimNovo = dataParaDias(saida);

    while (fread(&e, sizeof(Estadia), 1, f) == 1) {
        if (e.numeroQuarto == numeroQuarto) {
            int ini = dataParaDias(e.dataEntrada);
            int fim = dataParaDias(e.dataSaida);

            if (!(fimNovo <= ini || iniNovo >= fim)) {
                fclose(f);
                return 0;
            }
        }
    }
    fclose(f);
    return 1;
}

int calcularPontosFidelidadeInterno(int codigoCliente) {
    FILE *f = fopen(ESTADIAS_FILE, "rb");
    if (f == NULL) return 0;

    Estadia e;
    int total = 0;

    while (fread(&e, sizeof(Estadia), 1, f) == 1) {
        if (e.codigoCliente == codigoCliente) {
            total += e.quantidadeDiarias;
        }
    }

    fclose(f);
    return total * 10;
}

void cadastrarCliente() {
    Cliente c;
    c.codigo = gerarNovoCodigoCliente();

    printf("\n+--------------------------------------+\n");
    printf("|          CADASTRO DE CLIENTE         |\n");
    printf("+--------------------------------------+\n\n");

    printf("Codigo gerado: %d\n\n", c.codigo);

    printf("Nome........: ");
    scanf(" %99[^\n]", c.nome);

    printf("Endereco....: ");
    scanf(" %149[^\n]", c.endereco);

    printf("Telefone....: ");
    scanf(" %19[^\n]", c.telefone);

    FILE *f = fopen(CLIENTES_FILE, "ab");
    if (f == NULL) f = fopen(CLIENTES_FILE, "wb");
    if (f == NULL) {
        printf("\n[ERRO] Arquivo nao abriu.\n");
        return;
    }

    fwrite(&c, sizeof(Cliente), 1, f);
    fclose(f);

    printf("\n[OK] Cliente cadastrado.\n");
}

void cadastrarFuncionario() {
    Funcionario f1;
    f1.codigo = gerarNovoCodigoFuncionario();

    printf("\n+--------------------------------------+\n");
    printf("|       CADASTRO DE FUNCIONARIO        |\n");
    printf("+--------------------------------------+\n\n");

    printf("Codigo gerado: %d\n\n", f1.codigo);

    printf("Nome........: ");
    scanf(" %99[^\n]", f1.nome);

    printf("Telefone....: ");
    scanf(" %19[^\n]", f1.telefone);

    printf("Cargo.......: ");
    scanf(" %49[^\n]", f1.cargo);

    printf("Salario (R$): ");
    scanf("%f", &f1.salario);

    FILE *f = fopen(FUNCIONARIOS_FILE, "ab");
    if (f == NULL) f = fopen(FUNCIONARIOS_FILE, "wb");
    if (f == NULL) {
        printf("\n[ERRO] Arquivo nao abriu.\n");
        return;
    }

    fwrite(&f1, sizeof(Funcionario), 1, f);
    fclose(f);

    printf("\n[OK] Funcionario cadastrado.\n");
}

void cadastrarQuarto() {
    Quarto q;
    int existe;

    printf("\n+--------------------------------------+\n");
    printf("|          CADASTRO DE QUARTO          |\n");
    printf("+--------------------------------------+\n\n");

    while (1) {
        printf("Numero do quarto...............: ");
        scanf("%d", &q.numero);

        FILE *f = fopen(QUARTOS_FILE, "rb");
        existe = 0;

        if (f != NULL) {
            Quarto aux;
            while (fread(&aux, sizeof(Quarto), 1, f) == 1) {
                if (aux.numero == q.numero) {
                    existe = 1;
                    break;
                }
            }
            fclose(f);
        }

        if (existe) {
            printf("[AVISO] Numero ja existe.\n\n");
        } else break;
    }

    printf("Capacidade maxima..............: ");
    scanf("%d", &q.quantidadeHospedes);

    printf("Valor diaria...................: ");
    scanf("%f", &q.valorDiaria);

    strcpy(q.status, "desocupado");

    FILE *f = fopen(QUARTOS_FILE, "ab");
    if (f == NULL) f = fopen(QUARTOS_FILE, "wb");
    if (f == NULL) {
        printf("\n[ERRO] Nao foi possivel abrir o arquivo.\n");
        return;
    }

    fwrite(&q, sizeof(Quarto), 1, f);
    fclose(f);

    printf("\n[OK] Quarto cadastrado.\n");
}

void cadastrarEstadia() {
    int codigoCliente, quantidadeHospedes;
    char entrada[11], saida[11];

    printf("\n+--------------------------------------+\n");
    printf("|          CADASTRO DE ESTADIA         |\n");
    printf("+--------------------------------------+\n\n");

    printf("Codigo do cliente........: ");
    scanf("%d", &codigoCliente);

    if (!clienteExiste(codigoCliente)) {
        printf("\n[ERRO] Cliente nao encontrado.\n");
        return;
    }

    printf("Quantidade de hospedes...: ");
    scanf("%d", &quantidadeHospedes);

    printf("Data entrada (dd/mm/aaaa): ");
    scanf(" %10s", entrada);

    printf("Data saida   (dd/mm/aaaa): ");
    scanf(" %10s", saida);

    int diarias = diferencaDias(entrada, saida);
    if (diarias <= 0) {
        printf("\n[ERRO] Datas invalidas.\n");
        return;
    }

    FILE *fq = fopen(QUARTOS_FILE, "rb+");
    if (fq == NULL) {
        printf("\n[ERRO] Sem quartos cadastrados.\n");
        return;
    }

    Quarto q;
    int achou = 0;
    long pos = 0;

    while (fread(&q, sizeof(Quarto), 1, fq) == 1) {
        if (q.quantidadeHospedes >= quantidadeHospedes &&
            strcmp(q.status, "desocupado") == 0 &&
            quartoDisponivelPeriodo(q.numero, entrada, saida)) {

            achou = 1;
            pos = ftell(fq) - sizeof(Quarto);
            break;
        }
    }

    if (!achou) {
        fclose(fq);
        printf("\n[AVISO] Nenhum quarto disponivel.\n");
        return;
    }

    Estadia e;
    e.codigo = gerarNovoCodigoEstadia();
    e.quantidadeDiarias = diarias;
    strcpy(e.dataEntrada, entrada);
    strcpy(e.dataSaida, saida);
    e.codigoCliente = codigoCliente;
    e.numeroQuarto = q.numero;

    FILE *fe = fopen(ESTADIAS_FILE, "ab");
    if (fe == NULL) fe = fopen(ESTADIAS_FILE, "wb");
    if (fe == NULL) {
        fclose(fq);
        printf("\n[ERRO] Arquivo nao abriu.\n");
        return;
    }

    fwrite(&e, sizeof(Estadia), 1, fe);
    fclose(fe);

    strcpy(q.status, "ocupado");
    fseek(fq, pos, SEEK_SET);
    fwrite(&q, sizeof(Quarto), 1, fq);
    fclose(fq);

    printf("\n[OK] Estadia cadastrada.\n");
}

void darBaixaEstadia() {
    int codigo;

    printf("\n+--------------------------------------+\n");
    printf("|             BAIXA EM ESTADIA         |\n");
    printf("+--------------------------------------+\n\n");

    printf("Codigo da estadia: ");
    scanf("%d", &codigo);

    FILE *fe = fopen(ESTADIAS_FILE, "rb");
    if (fe == NULL) {
        printf("\n[AVISO] Nenhuma estadia cadastrada.\n");
        return;
    }

    Estadia e;
    int achou = 0;

    while (fread(&e, sizeof(Estadia), 1, fe) == 1) {
        if (e.codigo == codigo) {
            achou = 1;
            break;
        }
    }
    fclose(fe);

    if (!achou) {
        printf("\n[ERRO] Estadia nao encontrada.\n");
        return;
    }

    FILE *fq = fopen(QUARTOS_FILE, "rb+");
    if (fq == NULL) {
        printf("\n[ERRO] Arquivo de quartos nao abriu.\n");
        return;
    }

    Quarto q;
    long pos = 0;
    int ok = 0;

    while (fread(&q, sizeof(Quarto), 1, fq) == 1) {
        if (q.numero == e.numeroQuarto) {
            ok = 1;
            pos = ftell(fq) - sizeof(Quarto);
            break;
        }
    }

    if (!ok) {
        fclose(fq);
        printf("\n[ERRO] Quarto nao encontrado.\n");
        return;
    }

    float total = e.quantidadeDiarias * q.valorDiaria;
    printf("\nValor total: R$ %.2f\n", total);

    strcpy(q.status, "desocupado");

    fseek(fq, pos, SEEK_SET);
    fwrite(&q, sizeof(Quarto), 1, fq);
    fclose(fq);

    printf("\n[OK] Baixa realizada.\n");
}

void pesquisarCliente() {
    int opcao;
    Cliente c;
    int achou = 0;

    printf("\n+--------------------------------------+\n");
    printf("|           PESQUISAR CLIENTE          |\n");
    printf("+--------------------------------------+\n\n");

    printf("1 - Codigo\n2 - Nome\nOpcao: ");
    scanf("%d", &opcao);
    getchar();

    FILE *f = fopen(CLIENTES_FILE, "rb");
    if (f == NULL) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }

    if (opcao == 1) {
        int codigo;
        printf("Informe o codigo: ");
        scanf("%d", &codigo);

        while (fread(&c, sizeof(Cliente), 1, f) == 1) {
            if (c.codigo == codigo) {
                printf("\nCodigo: %d\nNome: %s\nEndereco: %s\nTelefone: %s\n",
                    c.codigo, c.nome, c.endereco, c.telefone);
                achou = 1;
                break;
            }
        }

    } else if (opcao == 2) {
        char nome[100];
        printf("Informe parte do nome: ");
        scanf(" %99[^\n]", nome);

        while (fread(&c, sizeof(Cliente), 1, f) == 1) {
            if (strstr(c.nome, nome) != NULL) {
                printf("\nCodigo: %d\nNome: %s\nEndereco: %s\nTelefone: %s\n",
                    c.codigo, c.nome, c.endereco, c.telefone);
                achou = 1;
            }
        }

    } else {
        printf("\nOpcao invalida.\n");
        fclose(f);
        return;
    }

    fclose(f);

    if (!achou) printf("\nCliente nao encontrado.\n");
}

void pesquisarFuncionario() {
    int opcao;
    Funcionario f1;
    int achou = 0;

    printf("\n+--------------------------------------+\n");
    printf("|         PESQUISAR FUNCIONARIO        |\n");
    printf("+--------------------------------------+\n\n");

    printf("1 - Codigo\n2 - Nome\nOpcao: ");
    scanf("%d", &opcao);
    getchar();

    FILE *f = fopen(FUNCIONARIOS_FILE, "rb");
    if (f == NULL) {
        printf("\nNenhum funcionario cadastrado.\n");
        return;
    }

    if (opcao == 1) {
        int codigo;
        printf("Informe o codigo: ");
        scanf("%d", &codigo);

        while (fread(&f1, sizeof(Funcionario), 1, f) == 1) {
            if (f1.codigo == codigo) {
                printf("\nCodigo: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalario: %.2f\n",
                    f1.codigo, f1.nome, f1.telefone, f1.cargo, f1.salario);
                achou = 1;
                break;
            }
        }

    } else if (opcao == 2) {
        char nome[100];
        printf("Informe parte do nome: ");
        scanf(" %99[^\n]", nome);

        while (fread(&f1, sizeof(Funcionario), 1, f) == 1) {
            if (strstr(f1.nome, nome) != NULL) {
                printf("\nCodigo: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalario: %.2f\n",
                    f1.codigo, f1.nome, f1.telefone, f1.cargo, f1.salario);
                achou = 1;
            }
        }

    } else {
        printf("\nOpcao invalida.\n");
        fclose(f);
        return;
    }

    fclose(f);

    if (!achou) printf("\nFuncionario nao encontrado.\n");
}

void mostrarEstadiasCliente() {
    int opcao, codigoCliente;
    Estadia e;
    int achou = 0;

    printf("\n+--------------------------------------+\n");
    printf("|       ESTADIAS DE UM CLIENTE         |\n");
    printf("+--------------------------------------+\n\n");

    printf("1 - Codigo\n2 - Nome\nOpcao: ");
    scanf("%d", &opcao);
    getchar();

    if (opcao == 1) {
        printf("Codigo do cliente: ");
        scanf("%d", &codigoCliente);

        if (!clienteExiste(codigoCliente)) {
            printf("\nCliente nao encontrado.\n");
            return;
        }

    } else if (opcao == 2) {
        char nome[100];
        printf("Parte do nome: ");
        scanf(" %99[^\n]", nome);

        codigoCliente = obterCodigoClientePorNome(nome);
        if (codigoCliente == -1) {
            printf("\nCliente nao encontrado.\n");
            return;
        }

    } else {
        printf("\nOpcao invalida.\n");
        return;
    }

    FILE *f = fopen(ESTADIAS_FILE, "rb");
    if (f == NULL) {
        printf("\nNenhuma estadia cadastrada.\n");
        return;
    }

    while (fread(&e, sizeof(Estadia), 1, f) == 1) {
        if (e.codigoCliente == codigoCliente) {
            printf("\nCodigo estadia: %d\nEntrada: %s\nSaida: %s\nDiarias: %d\nQuarto: %d\n",
                e.codigo, e.dataEntrada, e.dataSaida, e.quantidadeDiarias, e.numeroQuarto);
            achou = 1;
        }
    }

    fclose(f);

    if (!achou) {
        printf("\nNenhuma estadia encontrado.\n");
    } else {
        int pontos = calcularPontosFidelidadeInterno(codigoCliente);
        printf("\nPontos de fidelidade: %d\n", pontos);
    }
}
