# Atividades

## Exercício 1 (Básico): Leitura Defensiva com Validação do fscanf

Um programa de jogo precisa ler os parâmetros de áudio e tela contidos em um arquivo de texto settings.txt.

O formato esperado do arquivo é:

```txt

VOLUME=80
SFX=1

```

Sua Tarefa:

Escreva a função bool ler_config_audio(const char *caminho, int *volume_out, int *sfx_out) que:

1. Abra o arquivo em modo de leitura ("r").

2. Valide o ponteiro retornado por fopen.

3. Use fscanf para extrair os dois inteiros e valide rigorosamente o valor de retorno do fscanf. Se o retorno for diferente de 2 (indicando arquivo corrompido, formato incorreto ou inexistência de tokens), a função deve retornar false.

4. Garanta o fechamento do arquivo com fclose em qualquer cenário de saída.

## Exercício 2 (Intermediário): Parsing e Modificação de Arquivo de Score

Um jogo salva o recorde atual do jogador em um arquivo highscore.txt no formato:

```txt

JOGADOR=PILOTO_ALPHA
PONTOS=4500

```

Sua Tarefa:

Implemente a função bool atualizar_highscore(const char *caminho, const char *novo_nome, int novos_pontos) que:

1. Abra o arquivo para leitura e leia a pontuação recorde atual.

2. Se o arquivo não existir ou se novos_pontos for maior do que os pontos gravados no arquivo, a função deve regravar (ou criar) o arquivo em modo de escrita ("w") atualizando o nome do jogador e a nova pontuação formatada.

3. Se os pontos atuais do arquivo forem maiores ou iguais a novos_pontos, o arquivo não deve ser sobrescrito e a função deve retornar false.

## Exercício 3 (Avançado): Módulo de Inicialização Automática com Fallback

Sistemas profissionais criam seus arquivos de configuração padrão automaticamente na primeira execução ou se o arquivo for apagado pelo usuário.

Sua Tarefa:

Escreva a função defensiva bool carregar_ou_criar_config(const char *caminho, int *largura, int *altura, int *fps) que atenda às seguintes regras de negócio:

1. Tentativa de Leitura: Abre o arquivo em modo "r". Se existir e o fscanf converter com sucesso exatamente os 3 parâmetros (LARGURA=%d\nALTURA=%d\nFPS=%d), fecha o arquivo e retorna true.

2. Criação Automática com Padrões: Se o arquivo não existir (fopen retornar NULL) ou se o fscanf falhar na conversão dos 3 parâmetros (arquivo corrompido):

- Tenta reabrir/criar o arquivo em modo de escrita ("w").

- Escreve os valores padrão de fábrica: LARGURA=800, ALTURA=600, FPS=60.

- Atribui esses mesmos valores padrão às variáveis apontadas pelos ponteiros de saída e retorna true.

3. Se houver falha de permissão no sistema operacional ao tentar criar o arquivo em "w", a função deve retornar false.
