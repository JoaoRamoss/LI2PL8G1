/**
 * @file lista.h
 * Definição da lista ligada.
 */
#ifndef LI2_LISTA_H
#define LI2_LISTA_H
#include "dados.h"

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

/**
 * \brief Verifica se a lista esta vazia.
 * @param L Lista.
 * @return 1, caso esteja vazia, 0, caso nao esteja.
 */
int lista_esta_vazia(LISTA L);

/**
 * \brief Calcula o length da lista fornecida pelo utilizador.
 * @param L Lista ligada.
 * @return O inteiro com o valor do length da lista fornecida.
 */
int lengthLista(LISTA L);

/**
 * \brief Adiciona todas as casas onde o bot pode jogar na lista ligada.
 * @param e Estado atual do jogo.
 * @param L Lista ligada.
 * @return Lista ligada atualizada.
 */
LISTA add_livres (ESTADO *e, LISTA L);

/**
 * \brief Adiciona na lista ligada todas as casas para onde o bot poderá jogar, caso a peca branca se encontre atualmente no canto.
 * @param e Estado atual do jogo.
 * @param L Lista ligada.
 * @return Lista atualizada.
 */
LISTA add_cantos(ESTADO *e, LISTA L);

/**
 * \brief Adiciona na lista ligada todas as casas para onde o bot poderá jogar.
 * @param e Estado atual do jogo.
 * @param L Lista ligada.
 * @return Lista atualizada.
 */
LISTA add_arround (ESTADO *e, LISTA L);

/**
 * \brief Adiciona na lista ligada todas as casas para onde o bot podera jogar caso se encontre com col == 0 ou lin == 0.
 * @param e Estado atual do jogo.
 * @param L Lista ligada
 * @return Lista atualizada.
 */
LISTA add_lados (ESTADO *e, LISTA L);

/**
 * \brief Adiciona na lista ligada todas as casas para onde o bot podera  jogar caso se encontre com lin == 0 ou lin == 7.
 * @param e Estado atual do jogo.
 * @param L Lista ligada.
 * @return Lista atualizada.
 */
LISTA add_bottom (ESTADO  *e, LISTA L);

/**
 * \brief Liberta o espaço alocado na memória para a lista.
 * @param L Lista ligada.
 */
void freeLista (LISTA L);
#endif
