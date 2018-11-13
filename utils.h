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
        /*
		case 1:
			printf("1 - Erro => Deve possuir a palavra reserva 'programa' no inicio, foi encontrado: (%s). [linha - %d].\n", palavra, nuLinha);
		break;

        */
		default:
			printf("Error informado não definido na tabela de erros.\n");
		break;
	}
	exit(1);
}

// Conta a quantidade de memoria consumida, incrementado e subtraindo da constante TOTAL_CONSUMO_MEMORIA
// http://www.cprogressivo.net/2013/03/A-funcao-sizeof-e-blocos-vizinhos-de-memoria-em-C.html
// situacao: 1 - incrementa, 2 - subtrai
void memoriaConsumida(int memoria, int situacao) {
	char a[1] = "a";
	if (situacao == 1) {
		TOTAL_CONSUMO_MEMORIA = TOTAL_CONSUMO_MEMORIA + memoria;
	} else {
		TOTAL_CONSUMO_MEMORIA = TOTAL_CONSUMO_MEMORIA - memoria;
	}

	if (TOTAL_CONSUMO_MEMORIA > MAX_TOTAL_CONSUMO_MEMORIA) {
		error(0, 12, a);
	}
}
