#ifndef CAMINHO_H
#define CAMINHO_H

#include "grafo.h"
#include "etiqueta.h"
template <class TYPE>
class Caminho
{
private:
    Grafo<TYPE>* grafo;
    Lista<Etiqueta<TYPE>>** etiqueta;
    int n_vertices;
public:
    Caminho(const Grafo<TYPE>* grafo):  grafo(grafo),
                                        etiqueta(0),
                                        n_vertices(0)
    {
        if (!grafo){
            throw QString("Grafo nao inicializado");
        }
        try{
            n_vertices = grafo->getNVertices();
            etiqueta = new Lista<Etiqueta<TYPE>>*[n_vertices];
            for(int i = 0; i < n_vertices; ++i){
                etiqueta[i] = new Lista<Etiqueta<TYPE>>;
            }
        }catch(std::bad_alloc& e){
            throw QString("Erro ao alocar memoria");
        }
    }
    void encontrarCaminho(const int& vertice1, const int& vertice2){
        if (!grafo){
            throw QString("Grafo nao inicializado");
        }
        if (!etiqueta){
            throw QString("Lista de etiqueta nao inicializada");
        }
        if ((vertice1 < 0 || vertice1 >= n_vertices) || (vertice2 < 0 || vertice2 >= n_vertices)){
            throw QString("Vertice invalido");
        }
        if (vertice1 == vertice2){
            etiqueta[vertice1 - 1]->inserirInicio(Etiqueta<TYPE>(TYPE(),0,0,true));
            return;
        }
        etiqueta[vertice1 - 1]->inserirInicio(Etiqueta<TYPE>(TYPE(),0,0,true));
        for (int i = 0; i < grafo->getTamanhoLista(vertice1 - 1); ++i){
            if (grafo->getTamanhoLista(vertice1 - 1) == 1){
                NOGrafo<TYPE> temp = grafo->getNOGrafo(vertice1 - 1, i);
                etiqueta[temp.getVertice()]->inserirInicio(Etiqueta<TYPE>(temp.getPeso(),vertice1,,true));
            }else{
            }
        }
    }
    ~Caminho(){
        if (etiqueta){
            for (int i = 0; i < n_vertices; ++i){
                if (etiqueta[i]){
                    delete etiqueta[i];
                    etiqueta[i] = 0;
                }
            }
            delete[] etiqueta;
            etiqueta = 0;
        }
    }
};

#endif // CAMINHO_H
