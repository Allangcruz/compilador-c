/**
 * Remove a quebra de linha da palavra informada
 *
 * @param char * palavra
 */
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

/**
 * Conta a quantidade de memoria consumida, incrementado e subtraindo da constante TOTAL_CONSUMO_MEMORIA
 *
 * http://www.cprogressivo.net/2013/03/A-funcao-sizeof-e-blocos-vizinhos-de-memoria-em-C.html
 *
 * @param int memoria
 * @param int situacao: 1 - incrementa, 2 - subtrai
 */
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