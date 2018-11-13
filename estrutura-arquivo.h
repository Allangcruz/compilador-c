// Struct que armazena a informacoes do dado da lista.
typedef struct linha {
    char conteudo[200];
    int linha;
} Linha;

// Struct que armazena os elementos da lista, de acordo com o tipo do dado.
typedef struct elemento {
    struct elemento *ant;
    Linha dados;
    struct elemento *prox;
} Elem;

typedef struct elemento* Lista;

// Cria a lista.
Lista* criaLista() {
    Lista* lista = (Lista*) malloc(sizeof(Lista));

    if (lista != NULL) {
        *lista = NULL;
    }

    return lista;
}

// Remove todos os elementos da lista.
void liberaLista(Lista* lista) {
    if (lista != NULL) {
        Elem* no;

        while ((*lista) != NULL) {
            no = *lista;
            *lista = (*lista)->prox;
            free(no);
        }

        free(lista);
    }
}

// Inseri no final da lista de acordo com parametros informados.
int insereListaFinal(Lista* lista, Linha lin) {
    if (lista == NULL) {
        return 0;
    }

    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) {
        return 0;
    }

    no->dados = lin;
    no->prox = NULL;

    // lista vazia: insere início
    if ((*lista) == NULL) {
        no->ant = NULL;
        *lista = no;
    } else {
        Elem *aux;
        aux = *lista;

        while (aux->prox != NULL) {
            aux = aux->prox;
        }

        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

// Remove o item da lista de acordo com o numero da linha informado.
int removeLista(Lista* lista, int nuLinha) {
    if (lista == NULL) {
        return 0;
    }

    // lista vazia
    if ((*lista) == NULL) {
        return 0;
    }

    Elem *no = *lista;
    while (no != NULL && no->dados.linha != nuLinha) {
        no = no->prox;
    }

    // não encontrado
    if(no == NULL) {
        return 0;
    }

    // remover o primeiro?
    if (no->ant == NULL) {
        *lista = no->prox;
    } else {
        no->ant->prox = no->prox;
    }

    // não é o último?
    if (no->prox != NULL) {
        no->prox->ant = no->ant;
    }

    free(no);
    return 1;
}

// Remove o item no final da lista.
int removeListaFinal(Lista* lista) {
    if(lista == NULL) {
        return 0;
    }

    // lista vazia
    if ((*lista) == NULL) {
        return 0;
    }

    Elem *no = *lista;

    while(no->prox != NULL) {
        no = no->prox;
    }

    // remover o primeiro e único
    if(no->ant == NULL) {
        *lista = no->prox;
    } else {
        no->ant->prox = NULL;
    }

    free(no);
    return 1;
}

// Retorna o total de itens que compoen a lista.
int tamanhoLista(Lista* lista) {
    if (lista == NULL) {
        return 0;
    }

    int cont = 0;
    Elem* no = *lista;

    while (no != NULL) {
        cont++;
        no = no->prox;
    }

    return cont;
}

/**
 * Verifica se a lista esta vazia.
 *
 * @param Lista* lista
 * @return int
 */
int listaVazia(Lista* lista) {
    if (lista == NULL) {
        return 1;
    }

    if (*lista == NULL) {
        return 1;
    }

    return 0;
}

// Imprime os itens da lista.
void imprimeLista(Lista* lista) {
    if (lista == NULL) {
        return;
    }

    Elem* no = *lista;

    while (no != NULL) {
        printf("Linha: %d \n", no->dados.linha);
        printf("Conteudo: %s \n", no->dados.conteudo);
        printf("Total caracter linha: %ld \n", strlen(no->dados.conteudo));
        printf("------------------------------------------\n");
        no = no->prox;
    }
}
