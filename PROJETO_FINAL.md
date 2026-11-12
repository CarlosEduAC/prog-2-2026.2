# Atividade Avaliativa: Sistema de Gerenciamento de Catálogo de Livros

**Data de Entrega:** 24/11/2026
**Formato de Entrega:** Código-fonte compactado (`.zip` ou `.tar.gz`) contendo a estrutura modularizada do projeto e uma documentação com instruções claras de compilação via terminal.

---

## 1. Objetivo

Desenvolver uma aplicação em Linguagem C para gerenciar um catálogo simples de livros em memória, permitindo cadastro, listagem, ordenação, busca e armazenamento permanente em disco. O projeto deve ser simples em regras de negócio, mas rigoroso na aplicação dos conceitos estruturais estudados na disciplina.

---

## 2. Requisitos Técnicos Obrigatórios

Para que a atividade seja avaliada integralmente, a solução deve contemplar obrigatoriamente os seguintes tópicos:

1. **Tipos Abstratos de Dados (TADs):**
   * O catálogo deve ser projetado como um TAD utilizando **ponteiro opaco** (`typedef struct Catalogo Catalogo;`), impedindo que o arquivo principal (`main.c`) acesse diretamente os campos internos da estrutura.
2. **Implementação e Acesso a Bibliotecas:**
   * O projeto deve ser dividido em múltiplos arquivos (`.h` na pasta `include/` e `.c` na pasta `src/`), utilizando **guardas de inclusão** (`#ifndef / #define / #endif`) e funções auxiliares privadas marcadas com **`static`**.
3. **Alocação Dinâmica de Memória:**
   * Todas as instâncias do catálogo, seus nós internos e vetores temporários devem ser alocados dinamicamente no *Heap* (`malloc` / `calloc`) e devidamente liberados (`free`) ao encerrar o programa, sem vazamentos de memória (*memory leaks*).
4. **Estruturas de Dados Encadeadas:**
   * O armazenamento principal dos livros em memória deve ser feito por meio de uma **Lista Simplesmente ou Duplamente Encadeada** (cada livro contendo: `int codigo`, `char titulo[60]` e `int ano_publicacao`).
5. **Recursividade:**
   * Pelo menos **duas operações** sobre a lista encadeada devem ser implementadas de forma **recursiva** (por exemplo: contar o total de livros cadastrados, buscar um livro pelo código ou liberar os nós da lista).
6. **Métodos de Ordenação Interna:**
   * Deve haver uma funcionalidade para exibir os livros ordenados por **Ano de Publicação** (ou Código). Como listas encadeadas não possuem acesso indexado direto, você deve copiar os registros para um vetor dinâmico temporário, aplicar um **método de ordenação interna** visto em aula (ex: *Insertion Sort*, *Shell Sort*, *Merge Sort* ou *Quick Sort*), exibir o resultado e liberar o vetor.
7. **Arquivos e Persistência de Dados:**
   * Ao iniciar o programa, o sistema deve carregar automaticamente os livros salvos em um arquivo (`catalogo.bin` ou `catalogo.txt`), caso ele exista.
   * Ao encerrar o programa (ou via opção do menu), o estado atual da lista encadeada deve ser persistido no disco. *(Atenção: não salve os ponteiros da lista no arquivo, apenas os dados de cada livro).*

---

## 3. Funcionalidades Mínimas do Menu (`main.c`)

A interface em linha de comando deve oferecer um menu simples com as seguintes opções:

1. **Cadastrar novo livro** (insere na lista encadeada).
2. **Listar livros** (exibe na ordem atual da lista).
3. **Listar livros ordenados por ano** (aplica o método de ordenação interna).
4. **Consultar livro por código** (utiliza busca recursiva).
5. **Exibir total de livros cadastrados** (utiliza contagem recursiva).
0. **Salvar e Sair** (persiste os dados em arquivo e libera toda a memória alocada).

---

## 4. Critérios de Avaliação

| Critério | Peso | Descrição |
| --- | :---: | --- |
| **Modularização, TAD e Bibliotecas** | 2,5 pts | Uso correto de `.h` e `.c`, *include guards*, ponteiro opaco e `static`. |
| **Lista Encadeada e Recursividade** | 2,5 pts | Manipulação correta dos ponteiros da lista e implementação funcional das rotinas recursivas. |
| **Ordenação Interna** | 2,0 pts | Implementação própria e correta do algoritmo de ordenação escolhido. |
| **Persistência em Arquivo** | 2,0 pts | Gravação e recuperação íntegra dos dados entre diferentes execuções do programa. |
| **Gestão de Memória (Valgrind)** | 1,0 pt | Ausência de *segmentation faults* e liberação completa da memória alocada (`0 leaks`). |

---

## 5. Observações Importantes

* Não é permitido o uso de funções prontas de ordenação da biblioteca padrão (como `qsort` da `stdlib.h`).
* O código deve compilar sem erros ou alertas críticos utilizando as flags `-Wall -Wextra`.
* Entregas após o dia **24/11** estarão sujeitas às regras de penalização previstas no plano de ensino.
