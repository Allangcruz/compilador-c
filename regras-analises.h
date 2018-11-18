// A tabela ASCII utilizada esta referente ao site abaixo:
// http://www.ricardoarrigoni.com.br/tabela-ascii-completa/

// Vetor com palavras reservadas.
char palavrasReservadas[NU_PALAVRA_RESERVADAS][10] = {"main", "function", "in", "out", "switch", "case", "break", "default", "foreach", "integer", "char", "float"};

// Vetor com palavras reservadas para tipo de variaveis.
char tiposVariaveis[NU_TIPO_VARIAVEL][10] = {"integer", "char", "float"};

// Imprime o vetor com todas as palavras reservadas
void imprimirPalavrasReservadas() {
	int i;
	memoriaConsumida(sizeof(i), 1);
	
	for (i = 0; i < NU_PALAVRA_RESERVADAS; i++) {
		printf("%iº => %s \n",i ,palavrasReservadas[i]);
	}
}

// Imprime o vetor com todas as palavras reservadas
void imprimirTiposVariaveis() {
	int i;
	memoriaConsumida(sizeof(i), 1);
	
	for (i = 0; i < NU_TIPO_VARIAVEL; i++) {
		printf("%iº => %s \n",i ,tiposVariaveis[i]);
	}
}

// Aplica validacoes referente a analise lexica e regras definidas na documentação
void analiseRegras(Lista* lista, TabelaSimbolo* tabelaSimbolos) {
	if (lista == NULL) {
		char a[1] = "a";
		error(0, 2, a);
        exit(1);
    }
    
    Elem* no = *lista;
    
    int i, valorAscii, nuLinha, count = 0;
    char palavraAux[UCHAR_MAX], conteudoLinha[UCHAR_MAX], conteudoLinhaComAspas[UCHAR_MAX], palavraAuxVariavel[UCHAR_MAX], tipoVariavel[UCHAR_MAX], tamanhoPalavra[UCHAR_MAX], auxTamanhoPalavra[UCHAR_MAX];
    bool isVariavel = false, isPalavraReservada = false, isCondicaoParada = false, isLinhaComVariavel = false, isString = false, isPossuiPontoVirgula = false, isLeia = false;
    int isDeclaracaoMain = 0;
    
    limparLixoVetor(palavraAux);
	limparLixoVetor(conteudoLinha);
	limparLixoVetor(conteudoLinhaComAspas);

    while (no != NULL) {
     	strcpy(conteudoLinha, no->dados.conteudo);
		nuLinha = no->dados.linha;
	
		removePalavrasComAspas(conteudoLinha, conteudoLinhaComAspas, nuLinha);
		isDeclaracaoMain = declaracaoMain(conteudoLinha, isDeclaracaoMain);
		
		// --------------------------------------------------------------
		// Teste de debug		
		// printf("Numero linha (%i):\n", no->dados.linha);
		// puts(no->dados.conteudo);
		// printf("Com aspas:\n");
		// puts(conteudoLinhaComAspas);
		// printf("Sem aspas:\n");
		// puts(conteudoLinha);
		// printf("\n\n");
		// --------------------------------------------------------------
		
		for (i = 0; i < strlen(conteudoLinha); i++) {
			valorAscii = (int) conteudoLinha[i];
			// printf("Linha => %i - Coluna => %i - Valor (%c)\n", nuLinha, i , conteudoLinha[i]);
		} // fim for que percorre as colunas da linha
		
		no = no->prox;
		
	} // fim while que percorre as linhas
	
	// Verifica a declaracao do 'main' pelo menos uma vez.
	if (isDeclaracaoMain == 0) {
		error(0, 3, conteudoLinha);
	}
    
	// declaracaoMain(lista);
	
	//removePalavrasComAspas();
	
	printf("\n\n");
}

// Verifica se o caracter informado é uma condição de parada.
// Caso seja uma condicao de parada retorna 'true' senao 'false'
int isCondicaoDeParada(int valorAscii) {
	int isValido = 0;
	
	// Verifica se a caracter ascii informado e uma condição de parada, para ser feita uma determinada analise.
	// As condiçoes de parada sao os caracterers : \0, (, ), virgula, ponto virgula, #
	if ((valorAscii == 10) || (valorAscii == 40) || (valorAscii == 41) || (valorAscii == 44) || (valorAscii == 59) || (valorAscii == 35)) {
		isValido = 1;
	}
	
	return isValido;
}

// Verifica declaracao do modulo/funcao main
int declaracaoMain(char *palavra, int isDeclaracaoMain) {
	
	if (isDeclaracaoMain == 1) {
		return isDeclaracaoMain;
	}
	
	int i, valorAscii, count = 0, isParadaCondicao = 0;
	char palavraAux[UCHAR_MAX];
	
	limparLixoVetor(palavraAux);

	for (i = 0; i < strlen(palavra); i++) {
		valorAscii = (int) palavra[i];
		
		isParadaCondicao = isCondicaoDeParada(valorAscii);
		
		if (isParadaCondicao == 0) {
			palavraAux[count] = palavra[i];
			count++;
			continue;
		}	
		
		if (isDeclaracaoMain == false && isParadaCondicao == 1) {
			if (strcmp(palavraAux, palavrasReservadas[0]) == 0) {
				isDeclaracaoMain = true;
			}
			
			limparLixoVetor(palavraAux);
			count = 0;
		}
	}
	return isDeclaracaoMain;
}

// Remove palavras que estejam dentro de aspas e que possua duplo balanceamento valido.
void removePalavrasComAspas(char *palavra, char *palavraComAspas, int nuLinha) {
	
	int i, valorAscii, countPalavra = 0, countPalavraValida = 0, isPossuiAspas = 0;
	
	char palavraComConteudoAspas[UCHAR_MAX];
	char palavraSemConteudoAspas[UCHAR_MAX];
	
	limparLixoVetor(palavraComConteudoAspas);
	limparLixoVetor(palavraSemConteudoAspas);
	limparLixoVetor(palavraComAspas);
	
	for (i = 0; i < strlen(palavra); i++) {
		
		valorAscii = (int) palavra[i];
		//printf("%c\n", palavra[i]);
		
		//  se não abriu as aspas e este é a primeira abertura de aspas (34 = ")
		if (isPossuiAspas == 0 && valorAscii == 34) {
			isPossuiAspas = 1;
			palavraComConteudoAspas[countPalavra] = palavra[i];
			countPalavra++;
			// printf("primerio if\n");
			continue;
		}	
		
		if (isPossuiAspas > 0 && valorAscii != 34) {
			palavraComConteudoAspas[countPalavra] = palavra[i];
			countPalavra++;
			// printf("segundo if\n");
			continue;
		}
		
		//  segunda aspa para fechar o duplo balanceamento existente nela
		if (isPossuiAspas == 1 && valorAscii == 34) {
			palavraComConteudoAspas[countPalavra] = palavra[i];
			countPalavra++;
			isPossuiAspas = 0;
			// printf("terceiro if\n");
			continue;
		}
		
		// monta conteudo palavra valida sem as aspas
		// Alem de ignorar "vazio" = 32 e "tabulacao" = 9
		if ((isPossuiAspas == 0) && (valorAscii != 32) && (valorAscii != 9)) {
			// printf("quarto if\n");
			palavraSemConteudoAspas[countPalavraValida] = palavra[i];
			countPalavraValida++;
		}
	}
	
	strcpy(palavra, palavraSemConteudoAspas);
	strcpy(palavraComAspas, palavraComConteudoAspas);
}

