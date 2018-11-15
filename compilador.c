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

// Valor maximo de cosumo de memoria em bytes 367001600 bytes => 350 megabytes
int MAX_TOTAL_CONSUMO_MEMORIA = 367001600;

#include "estrutura-arquivo.h"
#include "utils.h"
#include "tabela-simbolo.h"
#include "regras-analises.h"

int main () {
	setlocale(LC_ALL, "PORTUGUESE");
	printf("Compilador 2018");

	Lista* linhas;

	// Leitura de arquivo
	linhas = carregarArquivo();
	
	// Imprime conteudo da lista
	imprimeLista(linhas);

	// Tabela de simbolos
	TabelaSimbolo* tabelaSimbolos = criaListaTabelaSimbolo();
	
	// Analise e regras
	analiseRegras(linhas, tabelaSimbolos);
	
	// limpar memoria lista com conteudo do arquivo
	// liberaLista(linhas);

	// Tratamento de erros

	// Gerenciamento de limite de memoria
	printf("\nCONSUMO DE MEMORIA: %d bytes", TOTAL_CONSUMO_MEMORIA);

    printf("\n\n");
    system("pause");

    return 0;
}

