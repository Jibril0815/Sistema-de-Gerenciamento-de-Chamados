# Metodologia

## 1. Objetivo da Comparação

A metodologia tem como objetivo estabelecer critérios e procedimentos para comparar duas implementações do Sistema de Gerenciamento de Chamados de Suporte Técnico, desenvolvidas nas linguagens C e Rust.

A comparação buscará identificar diferenças relacionadas ao desempenho, consumo de memória, gerenciamento de recursos e complexidade de implementação.

Para garantir resultados consistentes, ambas as versões deverão implementar as mesmas funcionalidades, regras de negócio e estruturas de dados equivalentes.

## 2. Abordagem

O trabalho será desenvolvido por meio de uma abordagem experimental e comparativa.

Inicialmente, será realizada a implementação do sistema nas duas linguagens. Em seguida, serão executados testes utilizando conjuntos de dados equivalentes, com o objetivo de coletar informações sobre o comportamento das aplicações.

Os resultados serão registrados e analisados para identificar semelhanças e diferenças entre as implementações.

## 3. Critérios de Comparação

### 3.1 Desempenho

Será analisado o tempo de execução das principais operações realizadas pelo sistema.

As operações consideradas incluem:

- Inserção de elementos;
- Remoção de elementos;
- Busca por identificador;
- Atualização de prioridade;
- Organização e extração de chamados do heap.

Os tempos serão registrados em unidades adequadas, preferencialmente milissegundos ou microssegundos, conforme a duração das operações.

### 3.2 Consumo de Memória

Será observado o consumo de memória das duas aplicações durante a execução.

A análise deverá considerar:

- Memória utilizada durante a inicialização;
- Memória utilizada com diferentes quantidades de chamados;
- Variação do consumo conforme o crescimento das estruturas;
- Comportamento durante a liberação dos recursos.

### 3.3 Gerenciamento de Memória

Será analisada a maneira como cada linguagem administra os recursos utilizados pelo sistema.

Na implementação em C, serão observadas as operações explícitas de alocação e liberação de memória.

Na implementação em Rust, serão analisados os mecanismos de propriedade, empréstimo e gerenciamento automático de memória.

### 3.4 Segurança de Memória

Será realizada uma análise qualitativa dos mecanismos oferecidos por cada linguagem para prevenir problemas relacionados à memória.

Entre os aspectos considerados estão:

- Acesso inválido à memória;
- Uso de memória após sua liberação;
- Liberação duplicada;
- Vazamentos de memória;
- Acesso concorrente inseguro, quando aplicável.

Essa análise não será baseada apenas nos resultados dos benchmarks, mas também nas características das linguagens e na implementação realizada.

### 3.5 Complexidade de Implementação

Será observada a complexidade necessária para implementar e organizar as estruturas de dados e as funcionalidades do sistema.

Serão considerados aspectos como:

- Quantidade e organização do código;
- Necessidade de gerenciamento manual de memória;
- Tratamento de erros;
- Dificuldade de implementação das estruturas;
- Clareza e manutenção do código.

## 4. Ambiente de Testes

As duas implementações deverão ser executadas no mesmo ambiente de testes, utilizando:

- Mesmo computador;
- Mesmo sistema operacional;
- Mesma quantidade de dados;
- Mesma sequência de operações;
- Configurações de compilação equivalentes, respeitando as particularidades de cada compilador.

As versões dos compiladores e as configurações utilizadas deverão ser documentadas para permitir a reprodução dos experimentos.

## 5. Conjuntos de Dados

Serão utilizados conjuntos de dados com diferentes quantidades de chamados, permitindo observar o comportamento das aplicações conforme aumenta o volume de informações.

Os tamanhos inicialmente propostos são:

| Conjunto | Quantidade de chamados |
|---|---:|
| Teste 1 | 1.000 |
| Teste 2 | 5.000 |
| Teste 3 | 10.000 |
| Teste 4 | 50.000 |

Os mesmos conjuntos de dados deverão ser utilizados nas duas implementações.

Os dados deverão apresentar características equivalentes, incluindo distribuição de prioridades e sequência de operações.

## 6. Execução dos Experimentos

Cada cenário de teste deverá ser executado pelo menos 10 vezes em cada linguagem.

Os resultados serão registrados para posterior análise.

Sempre que possível, serão utilizadas as seguintes medidas:

- Média do tempo de execução;
- Mediana do tempo de execução;
- Menor tempo registrado;
- Maior tempo registrado;
- Consumo de memória observado.

A utilização de múltiplas execuções permitirá reduzir a influência de variações ocasionais no ambiente de testes.

## 7. Registro dos Resultados

Os resultados serão organizados em tabelas e gráficos para facilitar a comparação.

As informações registradas deverão incluir:

- Linguagem utilizada;
- Estrutura de dados avaliada;
- Quantidade de elementos;
- Operação executada;
- Número da execução;
- Tempo de execução;
- Consumo de memória, quando aplicável.

Os resultados também deverão identificar o ambiente e as configurações utilizadas em cada experimento.

## 8. Análise dos Resultados

Após a execução dos testes, os resultados serão comparados considerando os critérios estabelecidos.

A análise deverá identificar:

- Qual implementação apresentou menor tempo de execução em cada operação;
- Como o aumento da quantidade de chamados afetou o desempenho;
- Como o consumo de memória variou entre as versões;
- Quais diferenças foram observadas no gerenciamento de memória;
- Quais características das linguagens influenciaram a implementação;
- Quais dificuldades foram encontradas durante o desenvolvimento.

A análise deverá considerar que um resultado de desempenho isolado não é suficiente para determinar a superioridade geral de uma linguagem.

## 9. Limitações do Experimento

Os resultados serão válidos dentro das condições específicas do ambiente de testes e das implementações desenvolvidas.

Diferenças de compiladores, configurações de otimização, hardware e sistema operacional poderão influenciar os resultados.

Além disso, a comparação será limitada ao sistema e às estruturas de dados definidos neste trabalho, não representando necessariamente o desempenho geral das linguagens C e Rust em outros cenários.