// ... (Cole aqui as structs e as funções acima) ...

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    do {
        printf("\n\n=== HOTEL DESCANSO GARANTIDO ===\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Funcionario\n");
        printf("3. Cadastrar Quarto\n");
        printf("4. Cadastrar Estadia (Check-in)\n");
        printf("5. Dar Baixa em Estadia (Check-out)\n");
        printf("6. Pesquisar Cliente\n");
        printf("7. Pesquisar Funcionario\n");
        printf("8. Mostrar Estadias de um Cliente\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // Substitua o fflush(stdin) por limparBuffer() se usar a minha função
        // ou mantenha fflush(stdin) se estiver no Windows.
        // limparBuffer(); 

        switch(opcao) {
            case 1: cadastrarCliente(); break;
            case 2: cadastrarFuncionario(); break;
            case 3: cadastrarQuarto(); break;
            case 4: cadastrarEstadia(); break;
            case 5: darBaixaEstadia(); break;
            case 6: pesquisarCliente(); break;
            case 7: pesquisarFuncionario(); break;
            case 8: mostrarEstadiasCliente(); break;
            case 0: printf("Saindo do sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}