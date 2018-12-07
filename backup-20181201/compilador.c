#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <limits.h>
#include <stdbool.h>

// Alunos:
// Isabella Carolina Morais de Barros
// Julio Rodrigues Lobo

// Armazena o total de memoria utilizada no compilador.
int TOTAL_CONSUMO_MEMORIA = 0;

// Foi utilizado o site para converter o valor de mega para bytes (https://www.gbmb.org/mb-to-bytes)
// Valor maximo de cosumo de memoria em bytes 10485760  bytes => 10 megabytes
int MAX_TOTAL_CONSUMO_MEMORIA = 10485760;

// Constante com o total de palavras reservadas.
#define NU_PALAVRA_RESERVADAS 12
#define NU_TIPO_VARIAVEL 3

// Assinaturas de funcoes
void memoriaConsumida(int memoria, int situacao);

#include "estrutura-arquivo.h"
#include "utils.h"
#include "tabela-simbolo.h"
#include "regras-analises.h"

int main () {
	setlocale(LC_ALL, "PORTUGUESE");
	printf("####################################################################\n");
	printf("# Alunos:\n");
	printf("# Isabella Carolina Morais de Barros\n");
	printf("# Julio Rodrigues Lobo\n");
	printf("# Compilador 2018\n");
	printf("####################################################################\n\n");

	Lista* linhas;

	// Leitura de arquivo
	linhas = carregarArquivo();

	memoriaConsumida(sizeof(linhas), 1);

	// Imprime conteudo da lista
	// imprimeLista(linhas);

	// Imprime as palavras reservadas definidas
	// imprimirPalavrasReservadas();

	// Tabela de simbolos
	TabelaSimbolo* tabelaSimbolos = criaListaTabelaSimbolo();

	// Analise e regras
	analiseRegras(linhas, tabelaSimbolos);

	// limpar memoria lista com conteudo do arquivo
	liberaLista(linhas);

	// exibir dados na tabela de simbolos
	imprimeTabelaSimbolo(tabelaSimbolos);

	// Gerenciamento de limite de memoria
	exibirConsumoMemoria();

	// limpa os dados da tabela de simbolo
	liberaListaTabelaSimbolo(tabelaSimbolos);

    printf("\n\n");
    system("pause");

    return 0;
}

