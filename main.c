//
//
//  Created by Rosilene Moura  on 28/03/20.
//  Copyright © 2020 Rosilene Moura . All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node *No;

No raiz = NULL; // nó raiz - onde tudo começa
No maxNo = NULL;
No minNo = NULL;

No ArvoreA = NULL;
No ArvoreB = NULL;
No ArvoreC = NULL;

enum Cores {
    BLACK,
    RED
};

struct Node {
    int valor;
    struct Node *pai;
    struct Node *esquerda;
    struct Node *direita;
    int cor;
};

void inicializarRaiz(No arvore, int valor);
void corretude(No arvore, No novoNo);
void alteraCor(No novoNo);
void rotacaoEsquerda (No arvore, No novoNo);
void rotacaoDireita (No arvore, No novoNo);
void rotacaoEsquerdaDireita (No arvore, No novoNo);
void rotacaoDireitaEsquerda (No arvore, No novoNo);
void inserir (int valor);
void inserirParte2(No arvore, int valor);
void buscaPreOrdem(No pNo, int valor);
void buscaInsercaoPreOrdem(No arvore, No pNo, int valor, bool menorQueX);
void buscaAtravesDoMax(No raizDir, No maxValor, int valor);
void buscaAtravesDoMin(No raizEsq, No minValor, int valor);
void split (int valor);
void splitMaker (No noValor);

// inicializa raiz
void inicializarRaiz(No arvore, int valor)
{
    arvore->valor = valor;
    arvore->cor = BLACK;
    arvore->esquerda = NULL;
    arvore->direita = NULL;
    arvore->pai = NULL;
}

void corretude(No arvore, No novoNo)
{
    while ((novoNo->pai != NULL) && (novoNo->pai->cor == RED))
    {
        
        if (novoNo->pai->pai != NULL)
        {
            
            if ((novoNo->pai->pai->esquerda != NULL) && (novoNo->pai->pai->esquerda == novoNo->pai))
            { // nó pai está à esquerda?
                // meu tio está à direita
                
                if ((novoNo->pai->pai->direita != NULL) && (novoNo->pai->pai->direita->cor == RED))
                { // tio do nó está à direita
                    // se eu tenho um tio e ele é rubro, então eu só tenho de recolorir
                    
                    novoNo->pai->pai->esquerda->cor = BLACK;
                    novoNo->pai->pai->direita->cor = BLACK;
                    
                    // verificando se meu avô não é o nó raiz
                    if (novoNo->pai->pai->pai != NULL)
                    {
                        novoNo->pai->pai->cor = RED; // avô
                    } else
                    {
                        // avô é a raiz
                        novoNo->pai->pai->cor = BLACK;
                    }
                } else if ((novoNo->pai->direita != NULL) && (novoNo->pai->direita == novoNo))
                {
                    // se meu pai é filho da esquerda e eu sou filho da direita, logo é uma left-right-rotate
                    
                    rotacaoEsquerdaDireita(arvore, novoNo);
                    
                } else
                {
                    
                    rotacaoDireita(arvore, novoNo);
                }
                
            } else if ((novoNo->pai->pai->direita != NULL) && (novoNo->pai->pai->direita == novoNo->pai))
            {
                
                // meu tio está à esquerda
                
                if ((novoNo->pai->pai->esquerda != NULL) && (novoNo->pai->pai->esquerda->cor == RED))
                {
                    novoNo->pai->pai->esquerda->cor = BLACK;
                    novoNo->pai->pai->direita->cor = BLACK;
                    
                    // verificando se meu avô não é o nó raiz
                    if (novoNo->pai->pai->pai != NULL)
                    {
                        novoNo->pai->pai->cor = RED; // avô
                    } else
                    {
                        novoNo->pai->pai->cor = BLACK;
                    }
                } else if ((novoNo->pai->esquerda != NULL) && (novoNo->pai->esquerda == novoNo))
                {
                    // se meu pai é filho da direita e eu sou filho da esquerda, logo é uma right-left-rotate
                    
                    rotacaoDireitaEsquerda(arvore, novoNo);
                    
                } else
                {
                    rotacaoEsquerda(arvore, novoNo);
                }
            }
        }
    }
}


void alteraCor(No novoNo)
{
    // correção de cores
    
    novoNo->pai->cor = BLACK;
    novoNo->pai->esquerda->cor = RED;
    novoNo->pai->direita->cor = RED;
}

void rotacaoEsquerda(No arvore, No novoNo)
{
    
    No aux = (struct Node *)malloc(sizeof(struct Node));
    No auxRaiz = (struct Node *)malloc(sizeof(struct Node));
    
    aux = novoNo->pai->pai->pai; // pai do avô do novo nó
    *auxRaiz = *arvore;
    
    if (aux == NULL)
    {
        // significa que se meu avô não tem pai, logo ele é a raiz da árvore.
        
        novoNo->pai->esquerda = auxRaiz;
        novoNo->pai->esquerda->direita = NULL;
        novoNo->pai->esquerda->pai = novoNo->pai;
        novoNo->pai->pai = NULL;
        
        alteraCor(novoNo);
        
        *arvore = *novoNo->pai;
        minNo = novoNo->pai->esquerda;
        
        
    } else
    {
        if ((aux->direita != NULL) && (aux->direita == novoNo->pai->pai))
        {
            aux->direita = novoNo->pai;
        } else
        {
            aux->esquerda = novoNo->pai;
        }
        
        novoNo->pai->esquerda = novoNo->pai->pai;
        novoNo->pai->esquerda->direita = NULL;
        novoNo->pai->pai = aux;
        novoNo->pai->esquerda->pai = novoNo->pai;
        
        alteraCor(novoNo);
    }
    
}

void rotacaoDireita(No arvore, No novoNo)
{
    
    No aux = (struct Node *)malloc(sizeof(struct Node));
    No auxRaiz = (struct Node *)malloc(sizeof(struct Node));
    
    aux = novoNo->pai->pai->pai; // pai do avô do novo nó
    *auxRaiz = *arvore;
    
    if (aux == NULL)
    {
        // significa que se meu avô não tem pai, logo ele é a raiz da árvore.
        // então novoNo->pai->pai == raiz
        
        novoNo->pai->direita = auxRaiz;
        novoNo->pai->direita->esquerda = NULL;
        novoNo->pai->direita->pai = novoNo->pai;
        novoNo->pai->pai = NULL;
        
        
        alteraCor(novoNo);
        
        *arvore = *novoNo->pai;
        maxNo = novoNo->pai->direita;
        
        
        
    } else
    {
        if ((aux->esquerda != NULL) && (aux->esquerda == novoNo->pai->pai))
        {
            aux->esquerda = novoNo->pai;
        } else
        {
            aux->direita = novoNo->pai;
        }
        
        novoNo->pai->direita = novoNo->pai->pai;
        novoNo->pai->direita->esquerda = NULL;
        novoNo->pai->pai = aux;
        novoNo->pai->direita->pai = novoNo->pai;
        
        alteraCor(novoNo);
    }
    
    
}

void rotacaoEsquerdaDireita(No raiz, No novoNo)
{
    
    No aux = (struct Node *)malloc(sizeof(struct Node));
    
    aux = novoNo->pai->pai;
    
    if (aux->pai == NULL)
    {
        // auxB é o nó raiz
        // então raiz == auxB
        
        novoNo->esquerda = novoNo->pai;
        novoNo->pai->direita = NULL;
        novoNo->pai->pai = novoNo;
        novoNo->pai = raiz;
        raiz->esquerda = novoNo;
        
    } else
    {
        
        novoNo->esquerda = novoNo->pai; // o filho da esquerda do novo nó é o que antes era o pai dele
        novoNo->pai->direita = NULL;
        novoNo->pai->pai = novoNo;
        novoNo->pai = aux; // pai do novo nó agora é o que antes era o avô dele
        aux->esquerda = novoNo; // o filho da esquerda do auxB é o antigo neto dele
        
    }
    
    rotacaoDireita(raiz, novoNo->esquerda);
}

void rotacaoDireitaEsquerda(No raiz, No novoNo)
{
    
    No aux = (struct Node *)malloc(sizeof(struct Node));
    
    aux = novoNo->pai->pai;
    
    if (aux->pai == NULL)
    {
        // auxB é o nó raiz
        // então raiz == auxB
        
        novoNo->direita = novoNo->pai;
        novoNo->pai->esquerda = NULL;
        novoNo->pai->pai = novoNo;
        novoNo->pai = raiz;
        raiz->direita = novoNo;
        
    } else
    {
        
        novoNo->direita = novoNo->pai; // o filho da esquerda do novo nó é o que antes era o pai dele
        novoNo->pai->esquerda = NULL;
        novoNo->pai->pai = novoNo;
        novoNo->pai = aux; // pai do novo nó agora é o que antes era o avô dele
        aux->direita = novoNo; // o filho da esquerda do auxB é o antigo neto dele
        
    }
    
    rotacaoEsquerda(raiz, novoNo->direita);
}

void inserir(int valor)
{
    if (raiz == NULL)
    {
        raiz = (struct Node *)malloc(sizeof(struct Node));
        
        inicializarRaiz(raiz, valor);
        
        maxNo = (struct Node *)malloc(sizeof(struct Node));
        minNo = (struct Node *)malloc(sizeof(struct Node));
        
        maxNo = raiz;
        minNo = raiz;
    } else {
        
        inserirParte2(raiz, valor);
        
    }
}

void inserirParte2(No raiz, int valor)
{
    No novoNo = (struct Node *)malloc(sizeof(struct Node));
    
    novoNo->cor = RED;
    novoNo->valor = valor;
    novoNo->direita = NULL;
    novoNo->esquerda = NULL;
    novoNo->pai = NULL;
    
    if ((novoNo->valor > maxNo->valor))
    {
        //novoNo->pai = maxNo;
        //maxNo->direita = novoNo;
        maxNo = novoNo;
        
        //corretude(raiz, novoNo);
        
        //return;
    } else if ((novoNo->valor < minNo->valor))
    {
        //novoNo->pai = minNo;
        //minNo->esquerda = novoNo;
        minNo = novoNo;
        
        //corretude(raiz, novoNo);
        
        //return;
    }
    
    /*
    if ((novoNo->valor > maxNo->valor))
    {
        novoNo->pai = maxNo;
        maxNo->direita = novoNo;
        maxNo = novoNo;
        
        corretude(raiz, novoNo);
        
        return;
    } else if ((novoNo->valor < minNo->valor))
    {
        novoNo->pai = minNo;
        minNo->esquerda = novoNo;
        minNo = novoNo;
        
        corretude(raiz, novoNo);
        
        return;
    } else
    {
     */
        No auxiliarA = (struct Node *)malloc(sizeof(struct Node));
        No auxiliarB = (struct Node *)malloc(sizeof(struct Node));
        
        auxiliarA = raiz;
        
        while (auxiliarA != NULL)
        {
            auxiliarB = auxiliarA;
            
            if (novoNo->valor > auxiliarA->valor)
            {
                auxiliarA = auxiliarA->direita;
            } else
            {
                auxiliarA = auxiliarA->esquerda;
            }
        }
        
        novoNo->pai = auxiliarB;
        
        if (novoNo->valor < auxiliarB->valor)
        {
            auxiliarB->esquerda = novoNo;
        } else
        {
            auxiliarB->direita = novoNo;
        }
        
        // se ele é a raiz significa que eu não andei na árvore, logo só há o nó raiz. Então o nó é filho do nó raiz.
        if (auxiliarB->pai != NULL)
        {
            
            corretude(raiz, novoNo);
        }
        
    //}
}

void buscarValor(No no, int valor)
{
    
    if (no->valor == valor)
    {
        printf("Achei\n");
        printf("Valor %d\n", no->valor);
        printf("Cor %d\n", no->cor);
        
        return;
    } else
    {
        if (no->valor > valor)
        {
            // então irei para a esquerda
            
            if (no->esquerda != NULL)
            {
                buscarValor(no->esquerda, valor);
            } else
            {
                printf("nada encontrado");
                return;
            }
            
            
        } else
        {
            // então irei para a direita
            
            if (no->direita != NULL)
            {
                buscarValor(no->direita, valor);
            } else
            {
                printf("nada encontrado");
                return;
            }
            
        }
    }
    
}

void buscaPreOrdem(No pNo, int valor)
{
    
    if(pNo != NULL)
    {
        if (pNo->valor == valor)
        {
            printf("achei na BuscaPreOrdem %d\n", pNo->valor);
            splitMaker(pNo);
            return;
        }
        
        buscaPreOrdem(pNo->esquerda, valor);
        buscaPreOrdem(pNo->direita, valor);
    }
    
}

void buscaAtravesDoMax(No raizDir, No maxValor, int valor)
{
    
    if (maxValor->valor == valor)
    {
        printf("achei na buscaAtravesDoMax\n");
        splitMaker(maxValor);
        return;
    } else if (maxValor->pai == NULL)
    {
        return;
    } else
    {
        if (valor > maxValor->pai->valor)
        {
            // ir para esquerda
            if (maxValor->esquerda != NULL)
            {
                maxValor = maxValor->esquerda;
                buscaPreOrdem(maxValor, valor);
                return;
            } else {
                return;
            }
        }
    }
    
    if (maxValor == raizDir)
    {
        return;
    }
    
    if (raizDir->valor == valor)
    {
        printf("achei na buscaAtravesDoMax\n");
        splitMaker(raizDir);
        return;
    } else
    {
        if (valor < raizDir->direita->valor)
        {
            // ir para esquerda
            if (raizDir->esquerda != NULL)
            {
                raizDir = raizDir->esquerda;
                buscaPreOrdem(raizDir, valor);
                return;
            } else {
                return;
            }
        }
    }
    
    maxValor = maxValor->pai;
    raizDir = raizDir->pai;
    
    
    buscaAtravesDoMax(raizDir, maxValor, valor);
    
}

void buscaAtravesDoMin(No raizEsq, No minValor, int valor)
{
    
    if (minValor->valor == valor)
    {
        printf("achei buscaAtravesDoMin\n");
        splitMaker(minValor);
        return;
    } else if (minValor->pai == NULL)
    {
        return;
    } else
    {
        if (valor < minValor->pai->valor)
        {
            // ir para esquerda
            if (minValor->direita != NULL)
            {
                minValor = minValor->direita;
                buscaPreOrdem(minValor, valor);
                return;
            } else {
                return;
            }
        }
    }
    
    if (minValor == raizEsq)
    {
        return;
    }
    
    if (raizEsq->valor == valor)
    {
        printf("achei buscaAtravesDoMin %d, \n", raizEsq->valor);
        splitMaker(raizEsq);
        return;
    } else
    {
        if (valor > raizEsq->esquerda->valor)
        {
            // ir para esquerda
            if (raizEsq->direita != NULL)
            {
                raizEsq = raizEsq->direita;
                buscaPreOrdem(raizEsq, valor);
                return;
            } else {
                return;
            }
        }
    }
    
    minValor = minValor->pai;
    raizEsq = raizEsq->pai;
    
    buscaAtravesDoMin(raizEsq, minValor, valor);
}

void split(int valor)
{
    
    if (valor == raiz->valor)
    {
        splitMaker(raiz);
        
    } else if (valor < raiz->valor)
    {
        buscaAtravesDoMin(raiz->esquerda, minNo, valor);
    } else
    {
        buscaAtravesDoMax(raiz->direita, maxNo, valor);
    }
}

void buscaInsercaoPreOrdem(No arvore, No pNo, int valor, bool menorQueX)
{
    
    if (menorQueX)
    {
        if(pNo != NULL)
        {
            if (pNo->valor < valor)
            {
                inserirParte2(arvore, pNo->valor);
            }
            
            buscaInsercaoPreOrdem(arvore, pNo->esquerda, valor, true);
            buscaInsercaoPreOrdem(arvore, pNo->direita, valor, true);
            
        }
    } else
    {
        if(pNo != NULL)
        {
            if (pNo->valor > valor)
            {
                inserirParte2(arvore, pNo->valor);
            }
            
            buscaInsercaoPreOrdem(arvore, pNo->esquerda, valor, false);
            buscaInsercaoPreOrdem(arvore, pNo->direita, valor, false);
            
        }
    }
    
    
}

/*
 
 Assim que for encontrado o valor na busca, chama-se a função splitMaker(No noValor), onde o split será realizado.
 Ele printa as novas árvores.
 
 */

void splitMaker (No noValor)
{
 
    ArvoreA = (struct Node *)malloc(sizeof(struct Node));
    ArvoreB = (struct Node *)malloc(sizeof(struct Node));
    ArvoreC = (struct Node *)malloc(sizeof(struct Node));

    // colocando na árvore ArvoreA os valores menores que o noValor
    inicializarRaiz(ArvoreA, noValor->valor); // valores <= x
    buscaInsercaoPreOrdem(ArvoreA, raiz, noValor->valor, true);
    
    // colocando na árvore ArvoreB o valor igual ao noValor
    inicializarRaiz(ArvoreB, noValor->valor); // x
    
    // colocando na árvore ArvoreC os valores maiores que o noValor
    inicializarRaiz(ArvoreC, noValor->valor); // valores >= x
    buscaInsercaoPreOrdem(ArvoreC, raiz, noValor->valor, false);
    
}

void visita(No no)
{
    printf("Valor %d\n", no->valor);
    printf("Cor %d\n", no->cor);
    
}

void emOrdem(No pNo)
{
    if(pNo != NULL)
    {
        emOrdem(pNo->esquerda);
        visita(pNo);
        emOrdem(pNo->direita);
    }
}

void preOrdem(No pNo)
{
    if(pNo != NULL)
    {
        visita(pNo);
        
        preOrdem(pNo->esquerda);
        preOrdem(pNo->direita);
    }
}

void posOrdem(No pNo)
{
    if(pNo != NULL)
    {
        posOrdem(pNo->esquerda);
        posOrdem(pNo->direita);
        
        visita(pNo);
    }
}

void printHelper(No arvore, bool last)
{
    if (arvore != NULL) {
        if (last && (arvore->pai == NULL)) {
            printf("Raiz--");
            printf("   ");
        } else if (last) {
            //if (last) {
            printf("R----");
            printf("   ");
        } else {
            printf("L----");
            printf("|  ");
        }
        
        printf("%d     ", arvore->valor);
        printf("Cor: %d\n", arvore->cor);
        printHelper(arvore->esquerda, false);
        printHelper(arvore->direita, true);
    }
}

void print() {
    if (ArvoreC) {
        printHelper(ArvoreC, true);
    }
}

int main(int argc, const char * argv[]) {
    // ver condição de valor repetido
    
    /*
     inserir(30);
     inserir(10);
     inserir(40);
     inserir(50);
     inserir(60);
     inserir(5);
     inserir(2);
     */
    
    /*
     inserir(30);
     inserir(25);
     inserir(40);
     inserir(45);
     inserir(42);
     */
    
     inserir(30);
     inserir(15);
     inserir(50);
     inserir(40);
     inserir(45);
     inserir(26);
     inserir(20);
     inserir(14);
     inserir(27);
     inserir(17);
   
    /*
    inserir(20);
    inserir(15);
    inserir(14);
    inserir(17);
     */
    
    print();
    
    split(20);
  
    //preOrdem(ArvoreA);
    
    //preOrdem(ArvoreB);
    
   // preOrdem(ArvoreC);
    
    
    print();
    
    return 0;
}
