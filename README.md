# Sistema de Gerenciamento de Chamados — C vs Rust

## 1. Descrição do Projeto

Este projeto consiste no desenvolvimento de um Sistema de Gerenciamento de Chamados de Suporte Técnico, implementado em duas linguagens de programação: **C e Rust**.

O sistema tem como finalidade organizar o registro, a triagem e o atendimento de solicitações de suporte técnico. Para isso, serão utilizadas estruturas de dados implementadas manualmente, como filas, pilhas, listas encadeadas, tabelas hash e heaps binários.

O projeto também possui um caráter experimental, buscando comparar as duas linguagens em relação ao desempenho, gerenciamento de memória, segurança e complexidade de implementação.

## 2. Objetivos

### Objetivo Geral

Desenvolver um sistema de gerenciamento de chamados de suporte técnico em C e Rust, utilizando estruturas de dados implementadas manualmente, com o propósito de estudar e comparar as características das duas linguagens.

### Objetivos Específicos

- Desenvolver duas implementações funcionalmente equivalentes do sistema.
- Aplicar conceitos de estruturas de dados em um cenário prático.
- Implementar manualmente as estruturas de dados em C e Rust.
- Comparar o desempenho das operações realizadas pelas duas implementações.
- Analisar o consumo e o gerenciamento de memória.
- Identificar diferenças na complexidade de implementação e nas características das linguagens.

## 3. Tecnologias Utilizadas

| Tecnologia | Finalidade |
|---|---|
| C (C11 ou superior) | Desenvolvimento da primeira implementação. |
| Rust | Desenvolvimento da segunda implementação. |
| Git | Controle de versão. |
| GitHub | Hospedagem e gerenciamento do repositório. |
| Markdown | Elaboração da documentação. |

## 4. Documentação

A documentação técnica do projeto está organizada no diretório `docs/`, separada em três documentos principais.

| Documento | Descrição |
|---|---|
| [Requisitos](docs/requisitos.md) | Apresenta a descrição do sistema, os tipos de usuários, os requisitos funcionais e não funcionais, as regras de negócio e as limitações do escopo. |
| [Arquitetura](docs/arquitetura.md) | Descreve a organização em camadas, os módulos, as estruturas de dados utilizadas e o fluxo de funcionamento do sistema. |
| [Metodologia](docs/metodologia.md) | Apresenta os critérios, procedimentos e condições utilizados para comparar as implementações em C e Rust. |

## 5. Estruturas de Dados

O sistema utilizará cinco estruturas de dados, implementadas manualmente nas duas linguagens.

| Estrutura | Aplicação no Sistema |
|---|---|
| Fila (Queue) | Organizar os chamados que aguardam triagem, respeitando a ordem de chegada. |
| Heap Binário Máximo (Max Heap) | Organizar os chamados pendentes de acordo com sua prioridade. |
| Tabela Hash (Hash Table) | Armazenar e localizar chamados por meio de seus identificadores. |
| Lista Encadeada (Linked List) | Armazenar o histórico de alterações de cada chamado. |
| Pilha (Stack) | Armazenar alterações administrativas reversíveis, permitindo desfazer a última operação. |

A utilização dessas estruturas permitirá aplicar diferentes conceitos de organização e manipulação de dados em uma aplicação prática.

Os detalhes de implementação e integração estão disponíveis em [Arquitetura do Sistema](docs/arquitetura.md).

## 6. Organização do Repositório

```text
sistema-chamados-c-rust/
│
├── README.md
│
├── docs/
│   ├── requisitos.md
│   ├── arquitetura.md
│   └── metodologia.md
│
├── c/
│   ├── include/
│   ├── src/
│   └── tests/
│
├── rust/
│   ├── Cargo.toml
│   ├── src/
│   └── tests/
│
├── benchmarks/
│   ├── datasets/
│   ├── resultados/
│   └── scripts/
│
└── tests/
    └── casos-de-teste.md
```

### Diretórios

- **`docs/`**: documentação técnica e metodológica do projeto.
- **`c/`**: implementação do sistema utilizando a linguagem C.
- **`rust/`**: implementação do sistema utilizando a linguagem Rust.
- **`benchmarks/`**: arquivos relacionados aos experimentos de desempenho, conjuntos de dados e resultados.
- **`tests/`**: documentação dos casos de teste do sistema.

## 7. Comparação entre C e Rust

A comparação será realizada utilizando as duas implementações do sistema, considerando os seguintes critérios:

| Critério | Aspectos analisados |
|---|---|
| Desempenho | Tempo de execução das operações de inserção, remoção, busca e atualização. |
| Consumo de memória | Quantidade de memória utilizada durante a execução. |
| Gerenciamento de memória | Alocação, liberação e administração dos recursos. |
| Segurança de memória | Mecanismos oferecidos pelas linguagens para evitar erros relacionados à memória. |
| Complexidade de implementação | Organização, quantidade de código, tratamento de erros e dificuldades encontradas durante o desenvolvimento. |

Os experimentos utilizarão conjuntos de dados equivalentes e condições de execução padronizadas, buscando garantir uma comparação consistente.

Os procedimentos detalhados estão descritos em [Metodologia](docs/metodologia.md).

## 8. Resultados Esperados

Ao final do projeto, espera-se:

- Obter duas versões funcionais do sistema de gerenciamento de chamados.
- Demonstrar a aplicação prática de cinco estruturas de dados.
- Compreender as diferenças entre o gerenciamento de memória em C e Rust.
- Identificar diferenças de desempenho entre as implementações.
- Avaliar as características de segurança de memória das duas linguagens.
- Desenvolver uma análise comparativa fundamentada nos resultados dos experimentos.

---

**Projeto acadêmico desenvolvido para fins de estudo de Estrutura de Dados e comparação entre as linguagens C e Rust.**
