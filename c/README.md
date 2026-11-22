# Implementacao em C

Implementacao modular do sistema de gerenciamento de chamados, conforme os requisitos do repositorio.

## Estruturas utilizadas

- Fila FIFO encadeada: chamados aguardando triagem.
- Heap binario maximo: chamados pendentes, ordenados por prioridade e, em empate, pela ordem de chegada.
- Tabela hash com encadeamento: acesso aos chamados por ID.
- Lista encadeada: historico de eventos de cada chamado.
- Pilha: desfazer a ultima alteracao administrativa ainda reversivel.

A tabela hash e proprietaria dos registros dos chamados. Fila, heap e pilha mantem ponteiros para esses registros; portanto, os chamados nao sao duplicados.

## Compilar e executar

Requer compilador C11 e GNU Make:

```sh
cd c
make
./build/chamados
```

Build de depuracao com AddressSanitizer e UndefinedBehaviorSanitizer:

```sh
make debug
./build/chamados
```

Limpar os arquivos gerados:

```sh
make clean
```

## Organizacao

- `include/`: interfaces e tipos compartilhados.
- `src/`: implementacoes das estruturas e regras de negocio.
- `Makefile`: compilacao do programa.
