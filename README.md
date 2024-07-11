# Projeto de Sistema Operacional Para Fins Didáticos (FIFIOS)

## Descrição

Este projeto tem como objectivo criar um Sistema Operacional simplificado para fins didáticos denominado FIFIOS. Ele é projetado para ajudar estudantes e entusiastas a compreender os princípios fundamentais de sistemas operacionais, incluindo gerenciamento de processos, memória, sistemas de arquivos e comunicação entre processos.

## Funcionalidades previstas

- **Gerenciamento de Processos**: Criação, escalonamento e terminação de processos.
- **Gerenciamento de Memória**: Alocação e desalocação de memória, paginação e segmentação.
- **Sistema de Arquivos**: Criação, leitura, escrita e exclusão de arquivos.
- **Comunicação entre Processos**: Mecanismos de comunicação como pipes e sinais.
- **Interface de Linha de Comando**: Interface básica para interação com o sistema.

## Requisitos

- Compilador C/C++ (i386-elf-gcc)
- Montador Assembly (NASM) 
- Ferramentas de construção (Make, CMake)
- QEMU ou outro emulador de hardware para testes

## Uso

1. Clone o repositório:
    ```bash
    git clone https://github.com/ibrahim-manuel/fifios.git
    ```
2. Navegue até o diretório do projeto:
    ```bash
    cd fifios
    ```
3. Compile o projeto usando Make:
    ```bash
    make
    ```
4. Para iniciar o sistema operacional no qemu, use o seguinte comando:
   ```bash
   qemu-system-i386 -kernel output/kernel.elf
   ```


## Contribuição
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues e pull requests.

## Licença
Este projeto está licenciado sob a Licença MIT - veja o arquivo LICENSE para mais detalhes.

## Agradecimentos
Agradecemos a todos os colaboradores e a comunidade de desenvolvimento de sistemas operacionais Operating System Development do ``Discord``.
