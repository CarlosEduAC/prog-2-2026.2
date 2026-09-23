# Revisão de Programação de Computadores II

## 0. Por que VS Code + Terminal?

Usar VS Code com terminal é a melhor escolha para aprender programação em C:

1. **É a stack utilizada na indústria e no mercado profissional**
   - Profissionais em C/C++ utilizam essa combinação diariamente
   - Companhias de software, sistemas embarcados e desenvolvimento de baixo nível preferem esse workflow
   - Garante que o aluno aprende as mesmas ferramentas usadas no mercado

2. **Usar o terminal força o aluno a entender a etapa de compilação (`gcc`)**
   - Compreender o processo de compilação é fundamental para programação em C
   - Aumenta a consciência sobre como o código se torna executável
   - Permite controlar com precisão as opções do compilador
   - Evita a "mágica preta" de IDEs que compilam automaticamente

3. **Facilita o uso de ferramentas de diagnóstico de memória (como **Valgrind**) nas aulas futuras**
   - Valgrind e outras ferramentas CLI integram-se perfeitamente com workflows baseados em terminal
   - Essencial para detectar vazamentos de memória e bugs sutis
   - Prepara o aluno para debugging profissional de aplicações em C
   - Terminal oferece feedback direto e detalhado das ferramentas de análise

## 1. Instalação no Windows

No Windows, instalaremos o **VS Code** e o compilador **GCC** por meio do pacote **MinGW-w64** via o gerenciador de pacotes MSYS2 (método oficial e mais estável).

### Passo 1.1: Instalar o VS Code

1. Acesse o site oficial: [code.visualstudio.com](https://code.visualstudio.com/).
2. Baixe o instalador `.exe` para Windows e execute-o.
3. Marque todas as caixas de seleção durante a instalação (especialmente **"Adicionar ao PATH"** e **"Adicionar a ação 'Abrir com Code' ao menu de contexto"**).

### Passo 1.2: Instalar o Compilador GCC (MinGW-w64 via MSYS2)

1. Acesse [msys2.org](https://www.msys2.org/) e baixe o instalador.
2. Execute o instalador mantendo a pasta padrão (`C:\msys64`).
3. Ao final da instalação, marque para abrir o terminal do MSYS2.
4. No terminal do MSYS2 que abrir, digite o seguinte comando para atualizar os pacotes:

```bash
pacman -Syu
```

5. Em seguida, instale a cadeia de ferramentas do GCC digitando:

```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```

*(Pressione `Enter` quando perguntar quais pacotes instalar para selecionar todos).*

### Passo 1.3: Adicionar o GCC às Variáveis de Ambiente do Windows

1. Pressione as teclas `Win + R`, digite `sysdm.cpl` e pressione `Enter`.
2. Vá para a aba **Avançado** e clique em **Variáveis de Ambiente...**
3. Na seção *Variáveis do Usuário* (ou *Variáveis do Sistema*), selecione a variável **Path** e clique em **Editar...**
4. Clique em **Novo** e cole o seguinte caminho:

   ```txt
   C:\msys64\ucrt64\bin
   ```

5. Clique em **OK** em todas as janelas abertas.

### Passo 1.4: Verificar a Instalação no Windows

1. Abra um novo **PowerShell** ou **Prompt de Comando (cmd)**.
2. Digite:

```bash
gcc --version
```

3. Se aparecer a versão do GCC (ex: `gcc (GCC) 21.x.x...`), a instalação foi concluída com sucesso!

## 2. Instalação no Linux (Ubuntu / Debian e Derivados)

No Linux, o processo é direto e realizado via terminal.

### Passo 2.1: Instalar o VS Code

Abra o terminal (`Ctrl + Alt + T`) e execute os comandos:

```bash
sudo apt update
sudo apt install snapd
sudo snap install code --classic
```

*(Caso prefira, você também pode baixar o pacote `.deb` no site oficial do VS Code).*

### Passo 2.2: Instalar o GCC e Ferramentas de Construção

No terminal, instale o pacote `build-essential` (que inclui o `gcc`, `g++`, `make` e bibliotecas base):

```bash
sudo apt update
sudo apt install build-essential gdb
```

### Passo 2.3: Verificar a Instalação no Linux

No terminal, verifique se o compilador foi instalado:

```bash
gcc --version
```

## 3. Compilando com avisos estritos ativados (boas práticas)

```bash
gcc -Wall -Wextra -std=c99 teste.c -o teste
```

**Explicação das flags:**

- `-Wall`: Ativa todos os avisos comuns
- `-Wextra`: Ativa avisos adicionais mais rigorosos
- `-std=c99`: Define o padrão C99 para compilação
- `-o programa`: Define o nome do executável de saída

### Executando no Linux/macOS

```bash
./teste
```

### Executando no Windows

```bash
.\teste.exe
```
