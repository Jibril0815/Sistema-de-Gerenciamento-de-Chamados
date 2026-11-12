# Requisitos do Sistema

## 1. Descrição do Sistema

O Sistema de Gerenciamento de Chamados de Suporte Técnico tem como objetivo organizar o registro, a triagem e o atendimento de solicitações de suporte técnico. A aplicação permitirá que solicitantes registrem problemas e acompanhem seus chamados, enquanto os atendentes poderão realizar a triagem, definir prioridades, organizar a fila de atendimento e atualizar o estado das solicitações.

O sistema será desenvolvido em duas versões independentes, utilizando as linguagens C e Rust. Ambas deverão apresentar as mesmas funcionalidades e regras de negócio, permitindo uma comparação entre as linguagens e suas características.

## 2. Tipos de Usuário

- **Solicitante:** responsável por registrar chamados e consultar suas informações por meio do identificador.
- **Atendente:** responsável por realizar a triagem, classificar os chamados, definir prioridades, iniciar atendimentos, atualizar informações e concluir solicitações.

## 3. Requisitos Funcionais

| Código | Descrição | Prioridade |
|---|---|---|
| RF01 | O sistema deve permitir que o solicitante cadastre um chamado informando nome, título e descrição do problema. | Alta |
| RF02 | O sistema deve gerar automaticamente um identificador único para cada chamado. | Alta |
| RF03 | O sistema deve permitir que o atendente visualize e realize a triagem dos chamados, definindo categoria e prioridade. | Alta |
| RF04 | O sistema deve organizar os chamados pendentes de acordo com sua prioridade e ordem de chegada. | Alta |
| RF05 | O sistema deve permitir que o atendente inicie e conclua o atendimento de um chamado, respeitando seu estado atual. | Alta |
| RF06 | O sistema deve permitir que o solicitante ou atendente consulte um chamado por meio de seu identificador. | Alta |
| RF07 | O sistema deve permitir que o atendente consulte o histórico e altere a categoria ou prioridade de chamados pendentes. | Média |
| RF08 | O sistema deve permitir que o atendente desfaça a última alteração administrativa reversível. | Média |

## 4. Requisitos Não Funcionais

| Código | Categoria | Descrição | Prioridade |
|---|---|---|---|
| RNF01 | Compatibilidade | O sistema deverá ser implementado utilizando C11 ou superior e uma versão estável da linguagem Rust. | Alta |
| RNF02 | Compatibilidade | As duas versões deverão funcionar em ambientes Windows e Linux, desde que possuam os compiladores necessários. | Média |
| RNF03 | Desempenho | As operações de busca por identificador deverão apresentar tempo de execução inferior a 1 segundo para até 10.000 chamados, no ambiente de teste definido. | Alta |
| RNF04 | Desempenho | As operações de inserção e remoção deverão apresentar tempo de execução inferior a 1 segundo para até 10.000 elementos, no ambiente de teste definido. | Média |
| RNF05 | Segurança e integridade | O sistema deverá validar 100% das entradas fornecidas pelos usuários antes de executar operações que alterem os dados. | Alta |
| RNF06 | Gerenciamento de memória | Ambas as implementações deverão liberar adequadamente os recursos de memória associados aos chamados e às estruturas de dados. | Alta |
| RNF07 | Usabilidade | O sistema deverá apresentar menus, mensagens e instruções em português, identificando claramente as operações disponíveis e os erros encontrados. | Média |
| RNF08 | Comparabilidade | As duas versões deverão implementar as mesmas funcionalidades e utilizar estruturas de dados equivalentes, sendo submetidas às mesmas condições de teste. | Alta |

## 5. Regras de Negócio

| Código | Descrição | Prioridade |
|---|---|---|
| RN01 | Todo chamado deverá possuir um identificador único, solicitante, título e descrição para ser cadastrado. | Alta |
| RN02 | Todo chamado recém-cadastrado deverá passar pela triagem antes de ser encaminhado para atendimento. | Alta |
| RN03 | Todo chamado deverá possuir uma categoria e uma prioridade definidas durante a triagem. | Alta |
| RN04 | Os chamados deverão ser atendidos por ordem de prioridade: crítica, alta, média e baixa. Em caso de empate, deverá prevalecer a ordem de chegada. | Alta |
| RN05 | Somente chamados pendentes poderão ter sua categoria ou prioridade alterada, e somente chamados em atendimento poderão ser concluídos. | Alta |
| RN06 | Toda alteração de categoria, prioridade ou status deverá ser registrada no histórico. O desfazer deverá respeitar a ordem inversa das alterações e será limitado às alterações administrativas reversíveis. | Alta |

## 6. Categorias e Prioridades

### 6.1 Categorias

Os chamados poderão ser classificados nas seguintes categorias:

- Hardware;
- Software;
- Rede;
- Acesso;
- Outros.

### 6.2 Prioridades

Os chamados deverão possuir um dos seguintes níveis de prioridade:

1. Crítica;
2. Alta;
3. Média;
4. Baixa.

Em situações de empate, será respeitada a ordem de chegada dos chamados.

### 6.3 Estados dos Chamados

Um chamado poderá apresentar os seguintes estados:

- Aguardando triagem;
- Pendente;
- Em atendimento;
- Concluído.

## 7. Limitações do Escopo

A primeira versão do sistema será uma aplicação local executada por meio de uma interface de terminal (CLI).

Não fazem parte do escopo inicial:

- Banco de dados ou persistência permanente;
- Interface gráfica ou aplicação web;
- Sistema de autenticação;
- Atendimento simultâneo por múltiplos usuários;
- Notificações externas;
- Atendimento remoto;
- Integração com ferramentas externas.