# Arquitetura do Sistema

## 1. Visão Geral

O Sistema de Gerenciamento de Chamados de Suporte Técnico será desenvolvido em duas implementações independentes: uma utilizando a linguagem C e outra utilizando Rust.

As duas versões deverão seguir a mesma arquitetura lógica, implementar as mesmas funcionalidades e utilizar estruturas de dados equivalentes. Essa padronização será necessária para garantir uma comparação justa entre as linguagens.

A aplicação utilizará uma interface de terminal (CLI), com os dados armazenados em memória durante a execução.

## 2. Organização em Camadas

A arquitetura será dividida em três camadas principais:

### 2.1 Interface

Responsável pela comunicação entre o usuário e o sistema.

Suas responsabilidades incluem:

- Exibir menus e opções disponíveis;
- Receber dados fornecidos pelos usuários;
- Apresentar informações dos chamados;
- Exibir mensagens de sucesso e erro;
- Encaminhar as operações solicitadas para a camada de lógica de negócio.

### 2.2 Lógica de Negócio

Responsável por implementar as regras e operações do sistema.

Suas responsabilidades incluem:

- Cadastrar chamados;
- Realizar a triagem;
- Definir categorias e prioridades;
- Organizar os chamados para atendimento;
- Atualizar o estado dos chamados;
- Consultar informações;
- Registrar alterações no histórico;
- Executar operações de desfazer.

### 2.3 Estruturas de Dados

Responsável pelo armazenamento e organização dos dados utilizados pelo sistema.

Essa camada será composta por cinco estruturas de dados implementadas manualmente:

- Fila;
- Heap binário máximo;
- Tabela hash;
- Lista encadeada;
- Pilha.

## 3. Estruturas de Dados

### 3.1 Fila (Queue)

**Finalidade:** armazenar os chamados que aguardam triagem.

A fila seguirá o princípio FIFO (First In, First Out), no qual o primeiro elemento inserido será o primeiro a ser removido.

Operações principais:

- `enqueue`: inserir um chamado na fila;
- `dequeue`: remover o primeiro chamado;
- `front`: consultar o primeiro chamado.

Complexidade esperada:

- Inserção: O(1);
- Remoção: O(1);
- Consulta do primeiro elemento: O(1).

### 3.2 Heap Binário Máximo (Max Heap)

**Finalidade:** organizar os chamados pendentes de acordo com sua prioridade.

O heap deverá garantir que o chamado de maior prioridade esteja sempre na raiz da estrutura.

A prioridade seguirá a seguinte ordem:

Crítica > Alta > Média > Baixa.

Em caso de empate, deverá prevalecer o chamado que chegou primeiro à fila de atendimento.

Operações principais:

- `heap_insert`: inserir um chamado;
- `heap_extract_max`: remover e retornar o chamado de maior prioridade;
- `heap_update`: atualizar a prioridade de um chamado.

Complexidade esperada:

- Inserção: O(log n);
- Remoção do maior elemento: O(log n);
- Consulta do maior elemento: O(1).

A atualização da prioridade poderá exigir uma busca pelo elemento e o reajuste do heap. Na implementação inicial, essa operação poderá apresentar complexidade O(n) para localizar o elemento, além do reajuste O(log n).

### 3.3 Tabela Hash (Hash Table)

**Finalidade:** armazenar e localizar os registros dos chamados por meio de seus identificadores únicos.

A tabela hash será utilizada como estrutura central de armazenamento dos registros completos.

Operações principais:

- `hash_insert`: inserir um chamado;
- `hash_search`: localizar um chamado pelo identificador;
- `hash_remove`: remover um chamado.

A implementação poderá utilizar encadeamento separado para tratar colisões.

Complexidade esperada:

- Inserção: O(1) em média;
- Busca: O(1) em média;
- Remoção: O(1) em média.

No pior caso, as operações poderão apresentar complexidade O(n).

### 3.4 Lista Encadeada (Linked List)

**Finalidade:** armazenar o histórico de alterações realizadas em cada chamado.

Cada elemento da lista representará um evento, contendo informações como:

- Tipo de alteração;
- Valor anterior;
- Novo valor;
- Data ou sequência da alteração.

Operações principais:

- `history_append`: adicionar um evento ao histórico;
- `history_print`: exibir o histórico.

Complexidade esperada:

- Inserção no final, com ponteiro para o último nó: O(1);
- Percorrer o histórico: O(n).

### 3.5 Pilha (Stack)

**Finalidade:** armazenar informações necessárias para desfazer alterações administrativas reversíveis.

A pilha seguirá o princípio LIFO (Last In, First Out), no qual a última alteração armazenada será a primeira a ser desfeita.

Operações principais:

- `stack_push`: adicionar uma alteração à pilha;
- `stack_pop`: remover e retornar a última alteração;
- `stack_peek`: consultar a última alteração sem removê-la.

Complexidade esperada:

- Inserção: O(1);
- Remoção: O(1);
- Consulta do topo: O(1).

## 4. Integração das Estruturas

As estruturas trabalharão em conjunto, mas cada uma terá uma responsabilidade específica.

A tabela hash será responsável por armazenar os registros completos dos chamados. A fila e o heap armazenarão identificadores ou referências aos chamados, evitando a duplicação dos registros.

A lista encadeada manterá o histórico de alterações, enquanto a pilha armazenará as informações necessárias para executar operações de desfazer.

Essa organização permitirá que as estruturas sejam utilizadas de maneira integrada, mantendo suas responsabilidades separadas.

## 5. Fluxo de Funcionamento

### 5.1 Cadastro

1. O solicitante informa os dados do problema.
2. O sistema valida as informações.
3. Um identificador único é gerado.
4. O chamado é armazenado na tabela hash.
5. O identificador é inserido na fila de triagem.

### 5.2 Triagem

1. O atendente consulta os chamados aguardando triagem.
2. O próximo identificador é removido da fila.
3. O atendente define a categoria e a prioridade.
4. O chamado passa para o estado pendente.
5. Seu identificador é inserido no heap.

### 5.3 Atendimento

1. O atendente solicita o próximo chamado.
2. O sistema extrai do heap o chamado de maior prioridade.
3. O estado do chamado é atualizado para em atendimento.
4. A alteração é registrada no histórico.

### 5.4 Conclusão

1. O atendente conclui o atendimento.
2. O estado do chamado é atualizado para concluído.
3. A alteração é registrada no histórico.
4. O registro permanece na tabela hash para consultas posteriores.

### 5.5 Alteração e Desfazer

1. O atendente seleciona um chamado pendente.
2. O sistema permite alterar sua categoria ou prioridade.
3. A alteração é registrada no histórico.
4. As informações necessárias para desfazer a alteração são armazenadas na pilha.
5. Caso solicitado, o sistema recupera a última alteração reversível e restaura os valores anteriores.

## 6. Organização dos Módulos

### 6.1 Implementação em C

```text
c/
├── include/
│   ├── chamado.h
│   ├── fila.h
│   ├── heap.h
│   ├── hash.h
│   ├── historico.h
│   ├── pilha.h
│   └── gerenciamento.h
│
├── src/
│   ├── main.c
│   ├── interface.c
│   ├── gerenciamento.c
│   ├── fila.c
│   ├── heap.c
│   ├── hash.c
│   ├── historico.c
│   └── pilha.c
│
└── tests/
```

### 6.2 Implementação em Rust

```text
rust/
├── Cargo.toml
└── src/
    ├── main.rs
    ├── chamado.rs
    ├── interface.rs
    ├── gerenciamento.rs
    ├── fila.rs
    ├── heap.rs
    ├── hash.rs
    ├── historico.rs
    └── pilha.rs
```

## 7. Considerações de Implementação

As estruturas de dados deverão ser implementadas manualmente nas duas linguagens, sem utilizar bibliotecas que substituam as implementações propostas.

Na versão em C, será necessário administrar explicitamente a alocação e a liberação de memória.

Na versão em Rust, serão utilizados os mecanismos de propriedade (*ownership*) e empréstimo (*borrowing*), buscando evitar o uso de `unsafe` sempre que possível.

As duas implementações deverão manter equivalência funcional, mesmo que utilizem mecanismos internos diferentes para administrar a memória.