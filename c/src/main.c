#include "interface.h"
int main(void){Sistema sistema;sistema_inicializar(&sistema);interface_executar(&sistema);sistema_destruir(&sistema);return 0;}
