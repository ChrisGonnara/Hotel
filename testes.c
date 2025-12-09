// AQUI PARA TESTAR A LIB MUNIT PARA TESTES AUTOMATICOS#include "munit.h"
#include "hotel.h"



// Teste 1: ve se tem algo duplicado
static MunitResult teste_verificar_quarto(const MunitParameter params[], void* data) {
    // 1. Limpa o arquivo de teste 
    remove("quartos.bin");

    // 2. Cria um quarto manualmente
    Quarto q = {101, 2, 150.0, "desocupado"};
    FILE *f = fopen("quartos.bin", "wb");
    fwrite(&q, sizeof(Quarto), 1, f);
    fclose(f);

    // 3. Verifica: O sistema acha o quarto 101? 
    int existe = verificarQuartoExistente(101);
    munit_assert_int(existe, ==, 1);

    // 4. Verifica: O sistema acha o quarto 999? 
    int nao_existe = verificarQuartoExistente(999);
    munit_assert_int(nao_existe, ==, 0);

    return MUNIT_OK;
}

// Registro dos Testes 
static MunitTest testes[] = {
    { "/verificar_quarto_existente", teste_verificar_quarto, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/hotel-testes", testes, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

// Main exclusivo para rodar os testes  tal do def __name__ == "__main__" se fosse em piton
int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, (void*) "µnit", argc, argv);
}