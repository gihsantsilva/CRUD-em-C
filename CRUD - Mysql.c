#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <locale.h>

#define MAX_STRING 255

MYSQL *conexao;

// Função para conectar ao banco de dados MySQL
void conectar() {
    conexao = mysql_init(NULL);

    if (conexao == NULL) {
        fprintf(stderr, "mysql_init() falhou\n");
        exit(1);
    }

    if (mysql_real_connect(conexao, "localhost", "root", "", "clientes", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s \n", mysql_error(conexao));
        mysql_close(conexao);
        exit(1);
    }
}

// Função para desconectar do banco de dados MySQL
void desconectar() {
    mysql_close(conexao);
}

// Função para carregar dados a partir de um arquivo TXT
int carregarDados(MYSQL *conexao, const char *caminhoArq)
{
    FILE *arquivo;

    arquivo = fopen(caminhoArq, "r");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo :(\n");
        return 1;
    }

    char query[200];
    char linha[255];
    int i = 0;
    while (fgets(linha,255, arquivo))
    {
        char nome[50], email[50];
        int cpf;
        sscanf(linha, "%s %d %s", &nome, &cpf, &email);

        sprintf(query, "insert into cadastrocliente (nome, cpf, email) values ('%s', %d, '%s')", nome, cpf, email);

        if(mysql_query(conexao,query)){
        	fprintf(stderr, "Erro ao executar a query: %s\n", mysql_error(conexao));
            mysql_close(conexao);
        }
        i++;
        printf("%d cliente inserido!\n", i);
    }
    return 0;
}

// Função para cadastrar um novo cliente
void cadastrarCliente() {
    char nome[MAX_STRING];
    int cpf;
    char email[MAX_STRING];

    printf("Digite o nome do cliente: ");
    scanf("%s", nome);
    
    printf("Digite o CPF do cliente: ");
    scanf("%d", &cpf);

    printf("Digite o email do cliente: ");
    scanf("%s", email);

    // Inserir os dados no banco de dados
    char query[MAX_STRING];
    sprintf(query, "INSERT INTO cadastrocliente (nome, cpf, email) VALUES ('%s', %d, '%s')", nome, cpf, email);

    if (mysql_query(conexao, query) != 0) {
        fprintf(stderr, "Erro ao executar a query: %s\n", mysql_error(conexao));
        return;
    }

    printf("Cliente cadastrado com sucesso!\n");
}

// Função para alterar um cliente
void alterarCliente() {
    int id;
    char nome[MAX_STRING];
    int cpf;
    char email[MAX_STRING];

    printf("Digite o ID do cliente que deseja alterar: ");
    scanf("%d", &id);

    printf("Digite o novo nome do cliente: ");
    scanf("%s", nome);

    printf("Digite o novo CPF do cliente: ");
    scanf("%d", &cpf);

    printf("Digite o novo email do cliente: ");
    scanf("%s", email);
    
    printf("\n");

    // Atualizar os dados no banco de dados
    char query[MAX_STRING];
    sprintf(query, "UPDATE cadastrocliente SET nome='%s', cpf=%d, email='%s' WHERE id=%d", nome, cpf, email, id);

    if (mysql_query(conexao, query) != 0) {
        fprintf(stderr, "Erro ao executar a query: %s\n", mysql_error(conexao));
        return;
    }

    printf("Cliente alterado com sucesso!\n");
}

// Função para deletar um cliente
void deletarCliente() {
    int id;

    printf("Digite o ID do cliente que deseja deletar: ");
    scanf("%d", &id);

    // Deletar cliente do banco de dados
    char query[MAX_STRING];
    sprintf(query, "DELETE FROM cadastrocliente WHERE id=%d", id);

    if (mysql_query(conexao, query) != 0) {
        fprintf(stderr, "Erro ao executar a query: %s\n", mysql_error(conexao));
        return;
    }

    printf("Cliente deletado com sucesso!\n");
}

// Função para listar todos os clientes
void listarClientes() {
    MYSQL_RES *resultado;
    MYSQL_ROW linha;

    if (mysql_query(conexao, "SELECT * FROM cadastrocliente") != 0) {
        fprintf(stderr, "Erro ao executar a query: %s\n", mysql_error(conexao));
        return;
    }

    resultado = mysql_store_result(conexao);

    if (resultado == NULL) {
        fprintf(stderr, "Erro ao obter o resultado da query\n");
        return;
    }

    printf("\nLista de Clientes:\n");
    while ((linha = mysql_fetch_row(resultado)) != NULL) {
        printf("ID: %s, Nome: %s, CPF: %s, Email: %s\n", linha[0], linha[1], linha[2], linha[3]);
    }

    mysql_free_result(resultado);
}

// Opções pro usuário selecionar
int main() {
	setlocale(LC_ALL, "Portuguese");
    int opcao;

    conectar();

    do {
    	printf("-------------------------------------------------------");
        printf("\nMenu:\n");
        printf("1 - Carga dos dados\n");
        printf("2 - Cadastramento de Registro\n");
        printf("3 - Alteração de Registro\n");
        printf("4 - Deleção de Registro\n");
        printf("5 - Listar registros\n");
        printf("6 - Sair\n");

        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
        	{
            getchar();
             printf("Insira o caminho do arquivo a ser carregado: ");
             char caminhoArquivo[100];
             scanf("%[^\n]", caminhoArquivo);

             carregarDados(conexao, caminhoArquivo);
                break;
            }
            case 2:
                cadastrarCliente();
                break;
            case 3:
                alterarCliente();
                break;
            case 4:
                deletarCliente();
                break;
            case 5:
                listarClientes();
                break;
            case 6:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 6);

    desconectar();

    return 0;
}
