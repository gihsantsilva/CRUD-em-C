# CRUD em C com MySQL

Este projeto é uma implementação de um sistema CRUD (Create, Read, Update, Delete) em linguagem C, utilizando um banco de dados MySQL para gerenciar dados de clientes. O projeto inclui funcionalidades para cadastrar, visualizar, atualizar e excluir informações de clientes no banco de dados.

## Índice
- [Descrição do Projeto](#descrição-do-projeto)
- [Pré-requisitos](#pré-requisitos)
- [Configuração do Banco de Dados](#configuração-do-banco-de-dados)
- [Como Executar o Projeto](#como-executar-o-projeto)
- [Funcionalidades](#funcionalidades)
- [Licença](#licença)

## Descrição do Projeto
Este programa conecta-se ao banco de dados MySQL e realiza operações de CRUD para gerenciar registros de clientes, incluindo:
- Inserção de dados a partir de um arquivo `.txt`.
- Cadastramento manual de clientes.
- Visualização de registros no banco.
- Atualização e remoção de registros.

## Pré-requisitos
- **C** (Compilador, como GCC)
- **MySQL** (Servidor MySQL em execução)
- **Biblioteca MySQL para C**: Certifique-se de instalar as bibliotecas de desenvolvimento do MySQL para C.


## Instalação da Biblioteca MySQL para C
No Windows, você pode instalar com:
1. Baixe o MySQL Installer para Windows e instale o MySQL Server.
2. Durante a instalação, selecione a opção de instalar as bibliotecas e ferramentas de desenvolvimento, incluindo o C Connector do MySQL.
3. Adicione o diretório de instalação (por exemplo, C:\Program Files\MySQL\MySQL Server X.Y\lib) ao PATH do Windows para facilitar o acesso durante a compilação.

No Ubuntu, você pode instalar com:
```
sudo apt-get install libmysqlclient-dev
```
No Fedora, você pode instalar com:
```
sudo dnf install mysql-devel
```

## Configuração do Banco de Dados
1. Certifique-se de que o servidor MySQL está em execução.
2. Crie o banco de dados e a tabela necessárias:
```
CREATE DATABASE clientes;
USE clientes;

CREATE TABLE cadastrocliente (
    nome VARCHAR(50),
    cpf INT PRIMARY KEY,
    email VARCHAR(50)
);
```
## Como Executar o Projeto
1. Compile o programa:
```
gcc -o crud_mysql CRUD\ -\ Mysql.c -lmysqlclient
```
2. Execute o programa:
```
./crud_mysql
```
Operações: O programa possui um menu para cadastrar, visualizar, atualizar e remover clientes. Siga as instruções no terminal.

## Funcionalidades
- Carregar Dados: Insere registros a partir de um arquivo .txt.
- Cadastrar Cliente: Permite adicionar novos clientes ao banco.
- Visualizar Clientes: Exibe a lista de clientes cadastrados.
- Atualizar Cliente: Altera as informações de um cliente existente.
- Remover Cliente: Exclui um cliente do banco de dados.

## Licença
Este projeto é de uso educacional e pode ser livremente modificado.
