#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

static bool linha(const char *prompt, char *b, size_t n) {
    printf("%s", prompt);
    // fgets tenta ler uma linha inteira dentro do tamanho informado.
    if (!fgets(b, (int) n, stdin)) {
        return false;
    }

    // Remove o caractere de quebra de linha capturado pelo fgets.
    size_t l = strlen(b);
    if (l && b[l - 1] == '\n') {
        b[l - 1] = '\0';
    } else {
        // Se a entrada foi maior que o vetor, descarta o restante da linha.
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    return b[0] != '\0';
}// Função para ler uma linha de entrada do usuário, armazenando-a em um buffer 
//  e removendo a quebra de linha. Retorna true se a leitura foi bem-sucedida e 
//  false caso contrário. Se a entrada for maior que o tamanho do buffer, o restante
// da linha é descartado.

static bool numero(const char *p, uint64_t *v) {
    char b[64];
    char *fim;

    // Le uma linha e rejeita diretamente valores negativos.
    if (!linha(p, b, sizeof b) || b[0] == '-') {
        return false;
    }

    errno = 0;
    // Converte o texto decimal em um valor inteiro sem sinal.
    unsigned long long x = strtoull(b, &fim, 10);

    // Permite espacos apos o numero, mas nao permite texto adicional.
    while (isspace((unsigned char) *fim)) {
        fim++;
    }

    if (errno || fim == b || *fim) {
        return false;
    }

    *v = (uint64_t) x;
    return true;
}// Função para ler uma linha de entrada do usuário, armazenando-a em um buffer 
//  e removendo a quebra de linha.

static bool escolha(const char *p, unsigned max, unsigned *v) {
    uint64_t x;
    // Reaproveita a leitura numerica e verifica o limite da opcao.
    if (!numero(p, &x) || x > max) {
        return false;
    }

    *v = (unsigned) x;
    return true;
}// Função para ler uma escolha numérica do usuário, garantindo que o valor esteja
//  dentro do limite especificado. Retorna true se a leitura foi bem-sucedida

static void mostrar(const Chamado *c) {
    // A consulta nao pode mostrar dados quando o ID nao existe.
    if (!c) {
        puts("Chamado nao encontrado.");
        return;
    }// Converte os enums em nomes legiveis e imprime todos os dados.

    printf(
        "\nID: %" PRIu64
        "\nStatus: %s"
        "\nCategoria: %s"
        "\nPrioridade: %s"
        "\nSolicitante: %s"
        "\nTitulo: %s"
        "\nDescricao: %s\n",
        c->id,
        status_nome(c->status),
        categoria_nome(c->categoria),
        prioridade_nome(c->prioridade),
        c->solicitante,
        c->titulo,
        c->descricao
    );
}// Função para exibir os detalhes de um chamado, incluindo ID, status, categoria, 
//  prioridade, solicitante, título e descrição. Se o chamado não for encontrado, 
//  exibe uma mensagem informando que o chamado não foi localizado.

void interface_executar(Sistema *s){
    char nome[96];
    char titulo[128];
    char desc[512];
    unsigned op;
    unsigned a;
    unsigned b;
    uint64_t id;
    Chamado *c;

    for (;;) {
        // O menu e repetido ate o usuario informar a opcao zero.
        puts(
            "\n=== GERENCIAMENTO DE CHAMADOS ==="
            "\n1 Cadastrar"
            "\n2 Listar aguardando triagem"
            "\n3 Triar proximo"
            "\n4 Listar pendentes (prioridade)"
            "\n5 Iniciar proximo atendimento"
            "\n6 Listar em atendimento"
            "\n7 Concluir chamado"
            "\n8 Consultar por ID"
            "\n9 Historico"
            "\n10 Alterar categoria"
            "\n11 Alterar prioridade"
            "\n12 Desfazer alteracao"
            "\n13 Listar todos"
            "\n0 Sair"
        );

        if (!escolha("Opcao: ", 13, &op)) {
            puts("Entrada invalida.");
            continue;
        }
        if (!op) {
            break;
        }

        switch (op) {
            case 1:
                // Exige os tres campos antes de enviar os dados ao sistema.
                if (!linha("Solicitante: ", nome, sizeof nome)
                    || !linha("Titulo: ", titulo, sizeof titulo)
                    || !linha("Descricao: ", desc, sizeof desc)) {
                    puts("Dados invalidos.");
                    break;
                }

                c = sistema_cadastrar(s, nome, titulo, desc);
                if (c) {
                    printf("Chamado cadastrado. ID: %" PRIu64 "\n", c->id);
                } else {
                    puts("Falha ao cadastrar.");
                }
                break;

            case 2:
                sistema_listar_status(s, STATUS_TRIAGEM);
                break;

            case 3:
                if (!escolha("Categoria (0 Hardware, 1 Software, 2 Rede, 3 Acesso, 4 Outros): ", 4, &a)
                    || !escolha("Prioridade (0 Baixa, 1 Media, 2 Alta, 3 Critica): ", 3, &b)
                    || !sistema_triar_proximo(s, (Categoria) a, (Prioridade) b)) {
                    puts("Nao foi possivel triar.");
                } else {
                    puts("Triagem realizada.");
                }
                break;

            case 4:
                sistema_listar_pendentes(s);
                break;

            case 5:
                c = sistema_iniciar_proximo(s);
                if (c) {
                    printf("Atendimento iniciado: %" PRIu64 "\n", c->id);
                } else {
                    puts("Nao ha chamados pendentes ou ocorreu uma falha.");
                }
                break;

            case 6:
                sistema_listar_status(s, STATUS_ATENDIMENTO);
                break;

            case 7:
                if (!numero("ID: ", &id) || !sistema_concluir(s, id)) {
                    puts("Nao foi possivel concluir.");
                } else {
                    puts("Chamado concluido.");
                }
                break;

            case 8:
                if (!numero("ID: ", &id)) {
                    puts("ID invalido.");
                } else {
                    mostrar(sistema_buscar(s, id));
                }
                break;

            case 9:
                if (!numero("ID: ", &id)) {
                    puts("ID invalido.");
                } else {
                    c = sistema_buscar(s, id);
                    if (c) {
                        sistema_listar_historico(c);
                    } else {
                        puts("Chamado nao encontrado.");
                    }
                }
                break;

            case 10:
                if (!numero("ID: ", &id)
                    || !escolha("Nova categoria (0-4): ", 4, &a)
                    || !sistema_alterar_categoria(s, id, (Categoria) a)) {
                    puts("Alteracao nao realizada.");
                } else {
                    puts("Categoria atualizada.");
                }
                break;

            case 11:
                if (!numero("ID: ", &id)
                    || !escolha("Nova prioridade (0-3): ", 3, &a)
                    || !sistema_alterar_prioridade(s, id, (Prioridade) a)) {
                    puts("Alteracao nao realizada.");
                } else {
                    puts("Prioridade atualizada.");
                }
                break;

            case 12:
                puts(sistema_desfazer(s)
                    ? "Alteracao desfeita."
                    : "Nao ha alteracao reversivel.");
                break;

            case 13:
                sistema_listar_todos(s);
                break;

            default:
                break;
        }
    }
}// Função principal da interface do usuário, que apresenta um menu de opções para 
//  gerenciar chamados.
