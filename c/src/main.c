#include "interface.h"

int main(void) {
    Sistema sistema;

    // Prepara todas as estruturas internas do sistema.
    sistema_inicializar(&sistema);

    // Executa o menu ate o usuario escolher sair.
    interface_executar(&sistema);

    // Libera a memoria usada pelas estruturas internas.
    sistema_destruir(&sistema);

    return 0;
}
