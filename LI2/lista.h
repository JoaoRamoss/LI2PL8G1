/**
 * @file lista.h
 * Definição da lista ligada.
 */
#ifndef LI2_LISTA_H
#define LI2_LISTA_H

typedef struct nodo {
    void *head;
    struct nodo *proximo;
} *LISTA, Nodo;

/**
 * \brief Inicializa a lista vazia, tendo o valor NULL no seu único nodo.
 * @return A lista inicializada.
 */
LISTA criar_lista ();

/**
 * \brief Insere um apontador void na cabeça da lista.
 * @param L Atual cabeça da lista, antes de ser inserida uma nova.
 * @param valor Futura cabeça da lista.
 * @return Lista atualizada, em que "void *valor" é a nova cabeça da lista.
 */
LISTA insere_cabeca(LISTA L, void *valor);

/**
 * \brief Função que vai buscar o valor da cabeça da lista.
 * @param L Lista.
 * @return O apontador void correspondente à cabeça da lista.
 */
void *devolve_cabeca(LISTA L);

/**
 * \brief Função para obter o proximo nodo da lista.
 * @param L Lista.
 * @return O próximo nodo da lista.
 */
LISTA proximo(LISTA L);

/**
 * \brief Função para remover a cabeça da lista.
 * @param L Lista.
 * @return A lista, com a sua cabeça removida (isto é, uma lista sem o seu primeiro elemento).
 */
LISTA remove_cabeca(LISTA L);
int lista_esta_vazia(LISTA L);

#endif
