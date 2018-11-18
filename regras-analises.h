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
		printf("%i� => %s \n",i ,palavrasReservadas[i]);
	}
}

// Imprime o vetor com todas as palavras reservadas
void imprimirTiposVariaveis() {
	int i;
	memoriaConsumida(sizeof(i), 1);
	
	for (i = 0; i < NU_TIPO_VARIAVEL; i++) {
		printf("%i� => %s \n",i ,tiposVariaveis[i]);
	}
}

// Aplica validacoes referente a analise lexica e regras definidas na documenta��o
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
	
		verificarDuploBalanceamentoAspasParentesConchetes(conteudoLinha, nuLinha);
		removePalavrasComAspas(conteudoLinha, conteudoLinhaComAspas, nuLinha);
		isDeclaracaoMain = declaracaoMain(conteudoLinha, isDeclaracaoMain);
		
		//puts(conteudoLinha);
		
		for (i = 0; i < strlen(conteudoLinha); i++) {
			valorAscii = (int) conteudoLinha[i];

			// acumula palavra ate encontra condi��o de parada, assim realiza a verifica��o.
//			if (isCondicaoDeParada(valorAscii) == 0) {
//				palavraAux[count] = (char) valorAscii;
//				count++;
//			} else {
//				
//				isVariavel = isDeclaracaoVariaveis(palavraAux, nuLinha);
//				
//				// verifica se n�o e uma variavel, se ele nao variavel, verificar se � palavra reservada
//				if (! isVariavel) {
//					printf("If isVariavel\n");
//				} else {
//					printf("Else isVariavel\n");
//				}
//				
//				limparLixoVetor(palavraAux);
//				count=0;
//			}
			// puts(palavraAux);
			// printf("Linha => %i - Coluna => %i - Valor (%c)\n", nuLinha, i , conteudoLinha[i]);
			
			
			
		} // fim for que percorre as colunas da linha
		
		no = no->prox;
		
	} // fim while que percorre as linhas
	
	// Verifica a declaracao do 'main' pelo menos uma vez.
	if (isDeclaracaoMain == 0) {
		error(0, 3, conteudoLinha);
	}
    exit(1);
	printf("\n\n");
}

// Verifica os duplos balanceamento de aspas, parenteses e conchetes.
void verificarDuploBalanceamentoAspasParentesConchetes(char *palavra, int nuLinha) {
	int i, valorAscii, isBalanceamentoApostofo = 0, isBalanceamentoAspas = 0, isBalanceamentoColchetes = 0, isBalanceamentoParenteses = 0;
	
	for (i = 0; i < strlen(palavra); i++) {
		valorAscii = (int) palavra[i];
		
		// Verifica se existe um fechamento de apostofo = ' = 39
		if (valorAscii == 39 && isBalanceamentoApostofo > 0) {
			isBalanceamentoApostofo--;
			continue;
		}
		
		// Verifica se existe uma abertura de apostofo = ' = 39
		if (valorAscii == 39 && isBalanceamentoApostofo == 0) {
			isBalanceamentoApostofo++;
			continue;
		}
		
		// Verifica se existe um fechamento de aspas = " = 34
		if (valorAscii == 34 && isBalanceamentoAspas > 0) {
			isBalanceamentoAspas--;
			continue;
		}
		
		// Verifica se existe uma abertura de aspas = " = 34
		if (valorAscii == 34 && isBalanceamentoAspas == 0) {
			isBalanceamentoAspas++;
			continue;
		}
		
		// Verifica se existe uma abertura de parenteses ( = 40
		if (valorAscii == 40) {
			isBalanceamentoParenteses++;
			continue;
		}
		
		// Verifica se existe um fechamento de parenteses = ) = 41
		if (valorAscii == 41) {
			isBalanceamentoParenteses--;
			continue;
		}
		
		// Verifica se existe uma abertura de colchetes [ = 91
		if (valorAscii == 91) {
			isBalanceamentoColchetes++;
			continue;
		}
		
		// Verifica se existe um fechamento de colchetes = ] = 93
		if (valorAscii == 93) {
			isBalanceamentoColchetes--;
			continue;
		}		
	}
	
	if (isBalanceamentoApostofo != 0) {
		error(nuLinha, 8, palavra);
	}
	
	if (isBalanceamentoAspas != 0) {
		error(nuLinha, 7, palavra);
	}
	
	if (isBalanceamentoColchetes != 0) {
		error(nuLinha, 5, palavra);
	}
	
	if (isBalanceamentoParenteses != 0) {
		error(nuLinha, 6, palavra);
	}
}

// Valida declaracoes de variaveis.
int isDeclaracaoVariaveis(char *palavra, int nuLinha) {
	int isValido = 0, i, valorAscii;
	
	valorAscii = (int) palavra[0];
	printf("[isDeclaracaoVariaveis]:\n");
	puts(palavra);
	
	// verifica se a palavra inicializa com $ = 36
	if (valorAscii == 36) {
		// apenas a-z
		if ((int) palavra[1] >= 97 && (int) palavra[1] <= 122) {
			isValido = 1;
		} else {
			isValido = 0;
			printf("\n[Declara��o variavel]\n");
			error(nuLinha, 4, palavra);
		}
		
		for (i = 2; i < strlen(palavra); i++) {
			valorAscii = (int) palavra[i];
			
			// permiter apenas a-z, 0-9, A-Z, [, ], .
			if (! ((valorAscii >= 97 && valorAscii <= 122) || (valorAscii >= 48 && valorAscii <= 57) || (valorAscii >= 65 && valorAscii <= 90) || valorAscii == 91 || valorAscii == 93 || valorAscii == 46)) {
				isValido = 0;
				printf("\n[Declara��o variavel]\n");
				error(nuLinha, 4, palavra);
			}
		}
	}
	
	return isValido;
}

// Verifica se o caracter informado � uma condi��o de parada.
// Caso seja uma condicao de parada retorna 'true' senao 'false'
int isCondicaoDeParada(int valorAscii) {
	int isValido = 0;
	
	// Verifica se a caracter ascii informado e uma condi��o de parada, para ser feita uma determinada analise.
	// As condi�oes de parada sao os caracterers : \0, (, ), virgula, ponto virgula, #
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
		
		//  se n�o abriu as aspas e este � a primeira abertura de aspas (34 = ")
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

