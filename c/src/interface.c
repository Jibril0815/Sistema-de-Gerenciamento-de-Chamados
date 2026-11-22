#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
static bool linha(const char *prompt,char *b,size_t n){printf("%s",prompt);if(!fgets(b,(int)n,stdin))return false;size_t l=strlen(b);if(l&&b[l-1]=='\n')b[l-1]='\0';else{int ch;while((ch=getchar())!='\n'&&ch!=EOF){} }return b[0]!='\0';}
static bool numero(const char *p,uint64_t *v){char b[64],*fim;if(!linha(p,b,sizeof b)||b[0]=='-')return false;errno=0;unsigned long long x=strtoull(b,&fim,10);while(isspace((unsigned char)*fim))fim++;if(errno||fim==b||*fim)return false;*v=(uint64_t)x;return true;}
static bool escolha(const char *p,unsigned max,unsigned *v){uint64_t x;if(!numero(p,&x)||x>max)return false;*v=(unsigned)x;return true;}
static void mostrar(const Chamado *c){if(!c){puts("Chamado nao encontrado.");return;}printf("\nID: %" PRIu64 "\nStatus: %s\nCategoria: %s\nPrioridade: %s\nSolicitante: %s\nTitulo: %s\nDescricao: %s\n",c->id,status_nome(c->status),categoria_nome(c->categoria),prioridade_nome(c->prioridade),c->solicitante,c->titulo,c->descricao);}
void interface_executar(Sistema *s){
    char nome[96],titulo[128],desc[512];unsigned op,a,b;uint64_t id;Chamado *c;
    for(;;){puts("\n=== GERENCIAMENTO DE CHAMADOS ===\n1 Cadastrar\n2 Listar aguardando triagem\n3 Triar proximo\n4 Listar pendentes (prioridade)\n5 Iniciar proximo atendimento\n6 Listar em atendimento\n7 Concluir chamado\n8 Consultar por ID\n9 Historico\n10 Alterar categoria\n11 Alterar prioridade\n12 Desfazer alteracao\n13 Listar todos\n0 Sair");
        if(!escolha("Opcao: ",13,&op)){puts("Entrada invalida.");continue;}if(!op)break;
        switch(op){
        case 1: if(!linha("Solicitante: ",nome,sizeof nome)||!linha("Titulo: ",titulo,sizeof titulo)||!linha("Descricao: ",desc,sizeof desc)){puts("Dados invalidos.");break;}c=sistema_cadastrar(s,nome,titulo,desc);if(c)printf("Chamado cadastrado. ID: %" PRIu64 "\n",c->id);else puts("Falha ao cadastrar.");break;
        case 2:sistema_listar_status(s,STATUS_TRIAGEM);break;
        case 3:if(!escolha("Categoria (0 Hardware, 1 Software, 2 Rede, 3 Acesso, 4 Outros): ",4,&a)||!escolha("Prioridade (0 Baixa, 1 Media, 2 Alta, 3 Critica): ",3,&b)||!sistema_triar_proximo(s,(Categoria)a,(Prioridade)b))puts("Nao foi possivel triar.");else puts("Triagem realizada.");break;
        case 4:sistema_listar_pendentes(s);break;
        case 5:c=sistema_iniciar_proximo(s);if(c){printf("Atendimento iniciado: %" PRIu64 "\n",c->id);}else puts("Nao ha chamados pendentes ou ocorreu uma falha.");break;
        case 6:sistema_listar_status(s,STATUS_ATENDIMENTO);break;
        case 7:if(!numero("ID: ",&id)||!sistema_concluir(s,id))puts("Nao foi possivel concluir.");else puts("Chamado concluido.");break;
        case 8:if(!numero("ID: ",&id))puts("ID invalido.");else mostrar(sistema_buscar(s,id));break;
        case 9:if(!numero("ID: ",&id))puts("ID invalido.");else{c=sistema_buscar(s,id);if(c)sistema_listar_historico(c);else puts("Chamado nao encontrado.");}break;
        case 10:if(!numero("ID: ",&id)||!escolha("Nova categoria (0-4): ",4,&a)||!sistema_alterar_categoria(s,id,(Categoria)a))puts("Alteracao nao realizada.");else puts("Categoria atualizada.");break;
        case 11:if(!numero("ID: ",&id)||!escolha("Nova prioridade (0-3): ",3,&a)||!sistema_alterar_prioridade(s,id,(Prioridade)a))puts("Alteracao nao realizada.");else puts("Prioridade atualizada.");break;
        case 12:puts(sistema_desfazer(s)?"Alteracao desfeita.":"Nao ha alteracao reversivel.");break;
        case 13:sistema_listar_todos(s);break;
        default:break;
        }
    }
}
