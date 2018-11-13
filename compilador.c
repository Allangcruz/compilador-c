#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <limits.h>

// Alunos:
// Isabella Carolina Morais de Barros
// Julio Rodrigues Lobo

// Armazena o total de memoria utilizada no compilador.
int TOTAL_CONSUMO_MEMORIA = 0;

// Valor maximo de cosumo de memoria em bytes 367001600 bytes => 350 megabytes
int MAX_TOTAL_CONSUMO_MEMORIA = 367001600;

#include "estrutura-arquivo.h"
#include "utils.h"

// Referencia do arquivo
FILE *arquivo;

// Carrega o arquivo para processar os seu conteudo
Lista* carregarArquivo() {
	char nomeArquivo[]="programa.txt";
	char ch[200];
	int nuLinhas = 1;

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
    	printf("\nArquivo não encontrado, verifique o caminho e nome.\n");
        exit(1);
	}

	Lista* linhas = criaLista();
	/*

    if (arquivo != NULL) {
		while ((fgets(ch, sizeof(ch), arquivo)) != NULL) {

			if (strlen(ch) != 1) {
				Linha item;
				item.linha = nuLinhas;
				strcpy(item.conteudo, ch);
				insereListaFinal(linhas, item);

				memoriaConsumida(sizeof(item), 1);
			}

			nuLinhas ++;
		}
	}

	memoriaConsumida(sizeof(ch), 1);
	memoriaConsumida(sizeof(nomeArquivo), 1);
	memoriaConsumida(sizeof(linhas), 1);
	memoriaConsumida(sizeof(arquivo), 1);
	memoriaConsumida(sizeof(nuLinhas), 1);
	*/

	fclose(arquivo);
	return linhas;
}

int main () {
	setlocale(LC_ALL, "PORTUGUESE");
	printf("Compilador 2018");

	Lista* linhas;

	// Leitura de arquivo
	linhas = carregarArquivo();

	// Tabela de simbolos

	// Tratamento de erros

	// Gerenciamento de limite de memoria

    printf("\n\n");
    system("pause");

    return 0;
}

