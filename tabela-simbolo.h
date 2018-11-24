// Struct que armazena a informacoes do simbolo da tabela de simbolos.
typedef struct simbolo {
	char tipo[UCHAR_MAX];
    char palavra[UCHAR_MAX];
    char valor[UCHAR_MAX];
    char funcao_modulo[UCHAR_MAX];
    char tamanho[UCHAR_MAX];
} Simbolo;

// Struct que armazena os elementos da lista, de acordo com o tipo do dado.
typedef struct elemSimbolo {
    struct elemSimbolo *ant;
    Simbolo dados;
    struct elemSimbolo *prox;
} ElemSimbolo;

typedef struct elemSimbolo* TabelaSimbolo;

// Cria a lista, que armazena a tabela de simbolos.
TabelaSimbolo* criaListaTabelaSimbolo() {
    TabelaSimbolo* lista = (TabelaSimbolo*) malloc(sizeof(TabelaSimbolo));

    if (lista != NULL) {
        *lista = NULL;
    }

    return lista;
}

// Remove todos os elementos da lista.
void liberaListaTabelaSimbolo(TabelaSimbolo* lista) {
    if (lista != NULL) {
        ElemSimbolo* no;

        while ((*lista) != NULL) {
            no = *lista;
            *lista = (*lista)->prox;
            free(no);
        }

        free(lista);
    }
}

// Inseri no final da lista de acordo com parametros informados.
int insereFinalTabelaSimbolo(TabelaSimbolo* lista, Simbolo simbolo) {
    if (lista == NULL) {
        return 0;
    }

    ElemSimbolo *no;
    no = (ElemSimbolo*) malloc(sizeof(ElemSimbolo));
    if (no == NULL) {
        return 0;
    }

    no->dados = simbolo;
    no->prox = NULL;

    // lista vazia: insere inicio
    if ((*lista) == NULL) {
        no->ant = NULL;
        *lista = no;
    } else {
        ElemSimbolo *aux;
        aux = *lista;

        while (aux->prox != NULL) {
            aux = aux->prox;
        }

        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

// Inseri no inicio da lista de acordo com parametros informados.
int insereInicioTabelaSimbolo(TabelaSimbolo* lista, Simbolo simbolo) {
    if (lista == NULL) {
        return 0;
    }

    ElemSimbolo* no;
    no = (ElemSimbolo*) malloc(sizeof(ElemSimbolo));

    if (no == NULL) {
        return 0;
    }

    no->dados = simbolo;
    no->prox = (*lista);
    no->ant = NULL;

    //lista nao vazia: apontar para o anterior!
    if (*lista != NULL) {
        (*lista)->ant = no;
    }

    *lista = no;

    return 1;
}

// Retorna o total de itens que compoen a lista.
int tamanhoTabelaSimbolo(TabelaSimbolo* lista) {
    if (lista == NULL) {
        return 0;
    }

    int cont = 0;
    ElemSimbolo* no = *lista;

    while (no != NULL) {
        cont++;
        no = no->prox;
    }

    return cont;
}

// Verifica se a lista esta vazia.
int isVazioTabelaSimbolo(TabelaSimbolo* lista) {
	int isVazio = 0;

    if (lista == NULL) {
        isVazio = 1;
    }

    if (*lista == NULL) {
        isVazio = 1;
    }

    return isVazio;
}

// Imprime os itens da lista.
void imprimeTabelaSimbolo(TabelaSimbolo* lista) {
    if (lista == NULL) {
        return;
    }

    ElemSimbolo* no = *lista;
    bool isListaVazia = isVazioTabelaSimbolo(lista);
    printf("####################################################################\n");
    printf("# TABELA DE SIMBOLOS \n");
    printf("####################################################################\n");

    if (isListaVazia == 1) {
    	printf("# A TABELA DE SIMBOLOS ESTA VAZIA.\n");
    	printf("####################################################################\n\n");
	}

    while (no != NULL) {
        printf("Tipo de dado: %s \n", no->dados.tipo);
        printf("Nome: %s \n", no->dados.palavra);
        printf("Possivel valor: %s \n", no->dados.valor);
        printf("Funcao/modulo:  \n");
        printf("Tamanho da variavel: %s \n", no->dados.tamanho);
        // printf("Função/modulo: %s \n", no->dados.funcao_modulo);
        printf("-------------------------------------------------------------------\n");
        no = no->prox;
    }
}

