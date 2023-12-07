#ifndef CAMINHO_H
#define CAMINHO_H

#include "grafo.h"
#include "etiqueta.h"
template <class TYPE>
class Caminho
{
private:
    Grafo<TYPE>* grafo;
    Lista<Etiqueta<TYPE>>** etiquetas;
public:
    Caminho(const Grafo<TYPE>* grafo): grafo(grafo){
        try{
            etiquetas = new Lista<Etiqueta<TYPE>>*[grafo->getNVertices()];
            for(int i = 0; i < grafo->getNVertices(); ++i){
                etiquetas[i] = new Lista<Etiqueta<TYPE>>;
            }
        }catch(std::bad_alloc& e){
            throw QString("Erro ao alocar memoria");
        }
    }
    void desenharCaminho(const int& vertice1, const int& vertice2){
        if (!grafo){
            throw QString("Grafo nao inicializado");
        }
        if (!etiquetas){
            throw QString("Lista de etiquetas nao inicializada");
        }
        if ((vertice1 < 0 || vertice1 >= grafo->getNVertices()) || (vertice2 < 0 || vertice2 >= grafo->getNVertices())){
            throw QString("Vertice invalido");
        }
        if (vertice1 == vertice2){
            etiquetas[vertice1 - 1]->inserirInicio(Etiqueta<TYPE>(0,0,0,true));
            return;
        }
        etiquetas[vertice1 - 1]->inserirInicio(Etiqueta<TYPE>(0,0,0,true));
        for (int i = 0; i < grafo->getTamanhoLista(vertice1 - 1); ++i){
            if (grafo->getTamanhoLista(vertice1 - 1) == 1){
                etiquetas[grafo->getNOGrafo(vertice1, i).getVertice()]->inserirInicio(Etiqueta<TYPE>(0,0,0,true));
            }else{
                Etiqueta<TYPE> temp;
            }

        }
    }
    ~Caminho(){
        if (etiquetas){
            for (int i = 0; i < grafo->getNVertices(); ++i){
                if (etiquetas[i]){
                    delete etiquetas[i];
                    etiquetas[i] = 0;
                }
            }
            delete[] etiquetas;
            etiquetas = 0;
        }
    }
};

#endif // CAMINHO_H
