// Limpa o lixo contido no vetor.
void limparLixoVetor(char vetor[]) {
	int i = 0;

	while (i < UCHAR_MAX) {
		vetor[i] = '\0';
		i ++;
	}
}

// Remove a quebra de linha da palavra informada
void removerQuebraLinha(char* palavra) {
	int i, valorAscii, count = 0;
	char palavraAux[UCHAR_MAX];

	limparLixoVetor(palavraAux);

	for (i = 0; i < strlen(palavra); i++) {
		valorAscii = (int) palavra[i];

		if (valorAscii != 10) {
			palavraAux[count] = palavra[i];
			count++;
		}
	}

	strcpy(palavra, palavraAux);
}

// Retorna a mensagem de error conforme parametros informados.
void error(int nuLinha, int tipoErro, char *palavra) {

	removerQuebraLinha(palavra);

	switch(tipoErro) {
        case 1:
			printf("1 - Memória Insuficiente.\n");
		break;
		
		case 2:
			printf("2 -Arquivos está vazio.\n");
		break;
		
		case 3:
			printf("3 - Não Existe a definicao do 'main()'.\n");
		break;
        
		default:
			printf("Error informado nao definido na tabela de erros.\n");
		break;
	}
	exit(1);
}

// Conta a quantidade de memoria consumida, incrementado e subtraindo da constante TOTAL_CONSUMO_MEMORIA
// http://www.cprogressivo.net/2013/03/A-funcao-sizeof-e-blocos-vizinhos-de-memoria-em-C.html
// situacao: 1 - incrementa, 2 - subtrai
void memoriaConsumida(int memoria, int situacao) {
	if (situacao == 1) {
		TOTAL_CONSUMO_MEMORIA = TOTAL_CONSUMO_MEMORIA + memoria;
	} else {
		TOTAL_CONSUMO_MEMORIA = TOTAL_CONSUMO_MEMORIA - memoria;
	}

	if (TOTAL_CONSUMO_MEMORIA > MAX_TOTAL_CONSUMO_MEMORIA) {
		char a[1] = "a";
		error(0, 1, a);
	}
}

// Referencia do arquivo
FILE *arquivo;

// Carrega o arquivo para processar os seu conteudo
Lista* carregarArquivo() {
	char nomeArquivo[]="arquivo.txt";
	char conteudoLinha[200];
	int nuLinhas = 1;

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
    	printf("\nArquivo nao encontrado, verifique o caminho ou nome do arquivo.\n");
        exit(1);
	}

	Lista* linhas = criaLista();

    if (arquivo != NULL) {
		while ((fgets(conteudoLinha, sizeof(conteudoLinha), arquivo)) != NULL) {

			if (strlen(conteudoLinha) != 1) {
				Linha item;
				item.linha = nuLinhas;
				strcpy(item.conteudo, conteudoLinha);
				insereListaFinal(linhas, item);

				memoriaConsumida(sizeof(item), 1);
			}

			nuLinhas ++;
		}
	}

	memoriaConsumida(sizeof(conteudoLinha), 1);
	memoriaConsumida(sizeof(nomeArquivo), 1);
	memoriaConsumida(sizeof(linhas), 1);
	memoriaConsumida(sizeof(arquivo), 1);
	memoriaConsumida(sizeof(nuLinhas), 1);

	fclose(arquivo);
	return linhas;
}

// Exibe total de consumo de memoria
void exibirConsumoMemoria() {
	printf("\n####################################################################");
	printf("\n# CONSUMO DE MEMORIA: %d bytes", TOTAL_CONSUMO_MEMORIA);
	printf("\n####################################################################");
}
