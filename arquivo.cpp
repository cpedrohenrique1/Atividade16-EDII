#include "arquivo.h"

Arquivo::Arquivo() : vetor(0),
                    n_vertices(0)
{
}

void Arquivo::abrir()
{

    QString endereco_arquivo = "/home/cpedrohenrique1/Documents/development/qtcreator/Atividade15-EDII/dados/grafo";
    QFile arquivo(endereco_arquivo);
    if (!arquivo.open(QIODevice::ReadOnly))
        throw QString("Nao foi possivel abrir o arquivo");
    QTextStream in(&arquivo);
    carregar_elementos(in);
    arquivo.close();
}

int Arquivo::getVertices()const{
    return n_vertices;
}

Grafo* Arquivo::getVetor()const{
    return vetor;
}

void Arquivo::carregar_elementos(QTextStream &in)
{
    bool i = true;
    while (!in.atEnd())
    {
        QString linha = in.readLine();
        if (i){
            try{
                n_vertices = linha.toInt();
                vetor = new Grafo(n_vertices);
            }catch(std::bad_alloc& e){
                throw QString("erro ao alocar memoria");
            }
            i = false;
            continue;
        }
        if (!vetor){
            throw QString("Vetor nao criado");
        }
        QStringList parts = linha.split(";");
        int vertice1 = parts[0].toInt();
        int vertice2 = parts[1].toInt();
        int peso = parts[2].toInt();
        vetor->inserirAresta(vertice1, vertice2, peso);
    }
}