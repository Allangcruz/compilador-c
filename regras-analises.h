// A tabela ASCII utilizada esta referente ao site abaixo:
// http://www.ricardoarrigoni.com.br/tabela-ascii-completa/

// Definicao de analise lexia e estudos
// https://johnidm.gitbooks.io/compiladores-para-humanos/content/part1/lexical-analysis.html

// Vetor com palavras reservadas.
char palavrasReservadas[NU_PALAVRA_RESERVADAS][10] = {"main", "function", "in", "out", "switch", "case", "break", "default", "foreach", "integer", "char", "float"};

// Vetor com palavras reservadas para tipo de variaveis.
char tiposVariaveis[NU_TIPO_VARIAVEL][10] = {"integer", "char", "float"};

// Imprime o vetor com todas as palavras reservadas
void imprimirPalavrasReservadas() {
	int i;
	memoriaConsumida(sizeof(i), 1);

	for (i = 0; i < NU_PALAVRA_RESERVADAS; i++) {
		printf("%i => %s \n",i ,palavrasReservadas[i]);
	}
}

// Imprime o vetor com todas as palavras reservadas
void imprimirTiposVariaveis() {
	int i;
	memoriaConsumida(sizeof(i), 1);

	for (i = 0; i < NU_TIPO_VARIAVEL; i++) {
		printf("%i => %s \n",i ,tiposVariaveis[i]);
	}
}

// Verifica os duplos balanceamento de aspas, parenteses e conchetes.
void verificarDuploBalanceamentoAspasParentesConchetes(char *palavra, int nuLinha) {
	int i, valorAscii, isBalanceamentoApostofo = 0, isBalanceamentoAspas = 0, isBalanceamentoColchetes = 0, isBalanceamentoParenteses = 0;

	memoriaConsumida(sizeof(i), 1);
	memoriaConsumida(sizeof(valorAscii), 1);
	memoriaConsumida(sizeof(isBalanceamentoApostofo), 1);
	memoriaConsumida(sizeof(isBalanceamentoAspas), 1);
	memoriaConsumida(sizeof(isBalanceamentoColchetes), 1);
	memoriaConsumida(sizeof(isBalanceamentoParenteses), 1);

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

	// verifica se a palavra inicializa com $ = 36
	if (valorAscii == 36) {
		// apenas a-z
		if ((int) palavra[1] >= 97 && (int) palavra[1] <= 122) {
			isValido = 1;
		} else {
			isValido = 0;
			// printf("\n[Declaracao variavel]\n");
			error(nuLinha, 10, palavra);
		}

		for (i = 2; i < strlen(palavra); i++) {
			valorAscii = (int) palavra[i];

			// permiter apenas a-z, 0-9, A-Z, [, ], .
			if (! ((valorAscii >= 97 && valorAscii <= 122) || (valorAscii >= 48 && valorAscii <= 57) || (valorAscii >= 65 && valorAscii <= 90) || valorAscii == 91 || valorAscii == 93 || valorAscii == 46)) {
				isValido = 0;
				// printf("\n[Declaracao variavel]\n");
				error(nuLinha, 10, palavra);
			}
		}
	}

	return isValido;
}

// Verifica se o caracter informado e uma condicao de parada.
// Caso seja uma condicao de parada retorna 'true' senao 'false'
int isCondicaoDeParada(int valorAscii) {
	int isValido = 0;

	// Verifica se a caracter ascii informado e uma condicao de parada, para ser feita uma determinada analise.
	// As condicoes de parada sao os caracterers : \0, (, ), virgula, ponto virgula, $
	if ((valorAscii == 10) || (valorAscii == 40) || (valorAscii == 41) || (valorAscii == 44) || (valorAscii == 59) || (valorAscii == 36)) {
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

	memoriaConsumida(sizeof(i), 1);
	memoriaConsumida(sizeof(valorAscii), 1);
	memoriaConsumida(sizeof(count), 1);
	memoriaConsumida(sizeof(isParadaCondicao), 1);
	memoriaConsumida(sizeof(palavraAux), 1);

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

	memoriaConsumida(sizeof(i), 1);
	memoriaConsumida(sizeof(valorAscii), 1);
	memoriaConsumida(sizeof(countPalavra), 1);
	memoriaConsumida(sizeof(countPalavraValida), 1);
	memoriaConsumida(sizeof(isPossuiAspas), 1);
	memoriaConsumida(sizeof(palavraComConteudoAspas), 1);
	memoriaConsumida(sizeof(palavraSemConteudoAspas), 1);

	limparLixoVetor(palavraComConteudoAspas);
	limparLixoVetor(palavraSemConteudoAspas);
	limparLixoVetor(palavraComAspas);

	for (i = 0; i < strlen(palavra); i++) {

		valorAscii = (int) palavra[i];

		//  se nao abriu as aspas e este e a primeira abertura de aspas (34 = ")
		if (isPossuiAspas == 0 && valorAscii == 34) {
			isPossuiAspas = 1;
			palavraComConteudoAspas[countPalavra] = palavra[i];
			countPalavra++;
			continue;
		}

		if (isPossuiAspas > 0 && valorAscii != 34) {
			palavraComConteudoAspas[countPalavra] = palavra[i];
			countPalavra++;
			continue;
		}

		//  segunda aspa para fechar o duplo balanceamento existente nela
		if (isPossuiAspas == 1 && valorAscii == 34) {
			palavraComConteudoAspas[countPalavra] = palavra[i];
			countPalavra++;
			isPossuiAspas = 0;
			continue;
		}

		// monta conteudo palavra valida sem as aspas
		// Alem de ignorar "vazio" = 32 e "tabulacao" = 9
		if ((isPossuiAspas == 0) && (valorAscii != 32) && (valorAscii != 9)) {
			palavraSemConteudoAspas[countPalavraValida] = palavra[i];
			countPalavraValida++;
		}
	}

	strcpy(palavra, palavraSemConteudoAspas);
	strcpy(palavraComAspas, palavraComConteudoAspas);
}

// Verifica se existe "ponto final" = ; na finalizacao de linhas.
int verificaPontoFinal(char *palavra, int nuLinha) {
	printf("Numero linha %d", nuLinha);
	puts(palavra);
	return 0;
}


// Valida palavras reservadas, utilizar como boleando, apos passar a palavra. validar separadamente.
int isPalavrasReservadas(char* palavra) {
	int isValido = 0, i;

	for (i = 0; i < NU_PALAVRA_RESERVADAS; i++) {
		if (strcmp(palavra, palavrasReservadas[i]) == 0) {
			isValido = 1;
			break;
		}
	}

	return isValido;
}


// Verifica se a palavra reservada � um tipo de variavel.
int isTipoVariavel(char *palavra) {
	int isValido = 0, i;

	for (i = 0; i < NU_TIPO_VARIAVEL; i++) {
		if (strcmp(palavra, tiposVariaveis[i]) == 0) {
			isValido = 1;
			break;
		}
	}

	return isValido;
}

// Aplica validacoes referente a analise lexica e regras definidas na documentacao
void analiseRegras(Lista* lista, TabelaSimbolo* tabelaSimbolos) {
	if (lista == NULL) {
		char a[1] = "a";
		error(0, 2, a);
        exit(1);
    }

    Elem* no = *lista;

    int i, valorAscii, nuLinha, count = 0;
    char palavraAux[UCHAR_MAX], conteudoLinha[UCHAR_MAX], conteudoLinhaComAspas[UCHAR_MAX], palavraAuxVariavel[UCHAR_MAX], tipoVariavel[UCHAR_MAX], tamanhoPalavra[UCHAR_MAX], auxTamanhoPalavra[UCHAR_MAX];
    bool isVariavel = false, isPalavraReservada = false, isCondicaoParada = false, isLinhaComVariavel = false, isString = false, isPossuiPontoVirgula = false, isIn = false;
    int isDeclaracaoMain = 0, isBalanceamentoChaves = 0;

    limparLixoVetor(palavraAux);
    limparLixoVetor(tipoVariavel);
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

			// Verifica se existe uma abertura de chaves = { = 123
			if (valorAscii == 123) {
				isBalanceamentoChaves++;
			}

			// Verifica se existe um fechamento de chaves = } = 125
			if (valorAscii == 125) {
				isBalanceamentoChaves--;
			}

			//printf("numero linha %i => %i\n", nuLinha, isBalanceamentoChaves);

			// acumula palavra ate encontra condicao de parada, assim realiza a verificacao.
			if (isCondicaoDeParada(valorAscii) == 0) {
				palavraAux[count] = (char) valorAscii;
				count++;
			} else {

				isVariavel = isDeclaracaoVariaveis(palavraAux, nuLinha);

				// verifica se nao e uma variavel, se ele nao variavel, verificar se e palavra reservada
				if (! isVariavel) {
					// printf("%d - [%s] - [%c] - [%s] - [%d] - Nao e uma variavel\n", nuLinha, palavraAux, conteudoLinha[i], tipoVariavel, isLinhaComVariavel);
					isPalavraReservada = isPalavrasReservadas(palavraAux);

					// quando for palavra reservada posso tratar aqui, exemplo se for tipo de variavel posso guarda para validar depois
					if (isPalavraReservada == true) {
						// caso seja: integer, char, float
						if (isTipoVariavel(palavraAux) == 1) {
							strcpy(tipoVariavel, palavraAux);
							isLinhaComVariavel = true;
						}

						// TODO caso seja 'in'
						// isIn = isPalavraIn(palavraAux, nuLinha, conteudoLinha);
						/*
						if (isLinhaComVariavel == true && isIn == true) {
							error(nuLinha, 16, conteudoLinha);
						}
						*/

						// TODO caso seja 'out'

						// TODO caso seja 'foreach'

						// TODO caso seja 'switch'

						// TODO caso seja 'case'

						// TODO caso seja 'break'

						// TODO caso seja 'default'
					}

				} else {
					// printf("%d - [%s] - [%c] - [%s] - [%d] - E uma variavel\n", nuLinha, palavraAux, conteudoLinha[i], tipoVariavel, isLinhaComVariavel);

					if (isLinhaComVariavel == true && isIn == false) {
						// validar se a variavel ja foi declarada.
						// if (validarVariavelDeclarada(palavraAux, tabelaSimbolos) == 1) {
							// error(nuLinha, 13, palavraAux);
						// }

						// verificar se tipo inteiro esta declarado com [, ]
						// verificarPresencaColchetes(palavraAux, tipoVariavel, nuLinha);

						// salva a variavel valida
	    				Simbolo novoSimbolo;
						// Salvar o modulo/funcao

						// Salvar valor

						// Salvar a palavra
	    				strcpy(novoSimbolo.palavra, palavraAux);

						// Salva o tipo da variavel
	    				strcpy(novoSimbolo.tipo, tipoVariavel);

						insereFinalTabelaSimbolo(tabelaSimbolos, novoSimbolo);
						limparLixoVetor(auxTamanhoPalavra);
					}
				}

				limparLixoVetor(palavraAux);
				count=0;
			}
			// puts(palavraAux);
			// printf("Linha => %i - Coluna => %i - Valor (%c)\n", nuLinha, i , conteudoLinha[i]);

			// apenas para inicio de variavel, os que inicializam  com $ - 36
			if (valorAscii == 36) {
				palavraAux[count] = (char) valorAscii;
				count++;
			}

		} // fim for que percorre as colunas da linha

		no = no->prox;

	} // fim while que percorre as linhas

	// Verifica a declaracao do 'main' pelo menos uma vez.
	if (isDeclaracaoMain == 0) {
		error(0, 3, conteudoLinha);
	}

	// Verifica o duplo balanceamento de chaves
	if (isBalanceamentoChaves != 0) {
		error(0, 9, conteudoLinha);
	}
}


