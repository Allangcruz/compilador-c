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
		error(0, 2, "");
        exit(1);
    }
    
    Elem* no = *lista;
    
    int i, valorAscii, nuLinha, count = 0;
    char palavraAux[UCHAR_MAX], conteudoLinha[UCHAR_MAX], palavraAuxVariavel[UCHAR_MAX], tipoVariavel[UCHAR_MAX], tamanhoPalavra[UCHAR_MAX], auxTamanhoPalavra[UCHAR_MAX];
    bool isVariavel = false, isPalavraReservada = false, isCondicaoParada = false, isLinhaComVariavel = false, isString = false, isPossuiPontoVirgula = false, isLeia = false;

    while (no != NULL) {
     	strcpy(conteudoLinha, no->dados.conteudo);
		nuLinha = no->dados.linha;
		
		removePalavrasComAspas(conteudoLinha, nuLinha);
		
		printf("Numero linha (%i):\n", no->dados.linha);
		puts(no->dados.conteudo);
		printf("Sem aspas:\n");
		puts(conteudoLinha);
		printf("\n\n");
		
//		for (i = 0; i < strlen(conteudoLinha); i++) {
//			valorAscii = (int) conteudoLinha[i];
//			printf("Linha => %i - Coluna => %i - Valor (%c)\n", nuLinha, i , conteudoLinha[i]);
//		} // fim for que percorre as colunas da linha
		
		no = no->prox;
		printf("\n------------------------------------------\n");
		
	} // fim while que percorre as linhas
    
	// declaracaoMain(lista);
	
	//removePalavrasComAspas();
	
	printf("\n\n");
}

// Verifica declaracao do modulo/funcao main
void declaracaoMain(Lista* lista) {
	if (lista == NULL) {
        exit(1);
    }

    Elem* no = *lista;
    char inicio[UCHAR_MAX], final[UCHAR_MAX], palavraAux[UCHAR_MAX];
    int i, nuLinha, count = 0, valorAscii;
    
    limparLixoVetor(final);
    limparLixoVetor(inicio);
    limparLixoVetor(palavraAux);
    
    strcpy(inicio, no->dados.conteudo);
    nuLinha = no->dados.linha;

    for (i = 0; i < strlen(inicio); i++) {
		valorAscii = (int) inicio[i]; 
		
		// \0, quebra de linha
		if (valorAscii != 10) {
			
			// apenas se nao for espaço e tabs
			if (valorAscii != 32 && valorAscii != 9) {
				palavraAux[count] = (char) valorAscii;
				count++;
			}
		} 
	}

	if (strcmp(palavraAux, palavrasReservadas[0]) != 0) {
		error(nuLinha, 1, palavraAux);
	}
	
	// valida a palavra fim na ultima linha 
	limparLixoVetor(palavraAux);
	count = 0;

	while (no != NULL) {
		if (no->prox == NULL) {
			strcpy(final, no->dados.conteudo);		
			nuLinha = no->dados.linha;
		}
        no = no->prox;
    }

    for (i = 0; i < strlen(inicio); i++) {
		valorAscii = (int) final[i]; 
		
		// \0, quebra de linha
		if (valorAscii != 10) {
			
			// apenas se nao for espaço e tabs
			if (valorAscii != 32 && valorAscii != 9) {
				palavraAux[count] = (char) valorAscii;
				count++;
			}
		}
	}

	if (strcmp(palavraAux, palavrasReservadas[9]) != 0) {
		error(nuLinha, 2, palavraAux);
	}
}

// Remove palavras que estejam dentro de aspas e que possua duplo balanceamento valido.
void removePalavrasComAspas(char *palavra, int nuLinha) {
	
	int i, valorAscii, count = 0, isPossuiAspas = 0;
	
	char palavraSemConteudoAspas[UCHAR_MAX];
	limparLixoVetor(palavraSemConteudoAspas);
	
	for (i = 0; i < strlen(palavra); i++) {
		
		valorAscii = (int) palavra[i];
		
		//  se não abriu as aspas e este é a primeira abertura de aspas (34 = ")
		if (isPossuiAspas == 0 && valorAscii == 34) {
			isPossuiAspas = 1;
			palavraSemConteudoAspas[count] = palavra[i];
			count++;
			continue;
		}
		
		if (isPossuiAspas > 0 && valorAscii != 34) {
			palavraSemConteudoAspas[count] = palavra[i];
			count++;
		}
		
		if (isPossuiAspas == 1 && valorAscii == 34) {
			palavraSemConteudoAspas[count] = palavra[i];
			count++;
			isPossuiAspas = 0;
		}
	}
	
	strcpy(palavra, palavraSemConteudoAspas);
}

