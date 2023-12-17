#include "arquivo.h"

Arquivo::Arquivo(QWidget *parent) : vetor(0)
{
    endereco_arquivo = QFileDialog::getOpenFileName(parent, "Abrir arquivo", "/home/");
}

void Arquivo::abrir()
{
    if (endereco_arquivo.isEmpty())
    {
        throw QString("Endereco vazio");
    }
    QFile arquivo(endereco_arquivo);
    if (!arquivo.open(QIODevice::ReadOnly))
        throw QString("Nao foi possivel abrir o arquivo");
    QTextStream in(&arquivo);
    carregar_elementos(in);
    arquivo.close();
}

Arquivo::~Arquivo()
{
    if (vetor)
    {
        delete vetor;
    }
}

int Arquivo::getTamanhoGrafo() const
{
    if (!vetor)
    {
        throw QString("Vetor nao criado");
    }
    return vetor->getNVertices();
}

int Arquivo::getTamanhoListaGrafo(const int& indice)const{
    if (!vetor){
        throw QString("Vetor nao criado");
    }
    return vetor->getTamanhoListaGrafo(indice);
}

NOGrafo<int> Arquivo::getVetor(const int &linha, const int &coluna) const
{
    return vetor->getNOGrafo(linha, coluna);
}

void Arquivo::carregar_elementos(QTextStream &in)
{
    bool i = true;
    while (!in.atEnd())
    {
        QString linha = in.readLine();
        if (i)
        {
            try
            {
                vetor = new GrafoDirecionado<int>(linha.toInt());
            }
            catch (std::bad_alloc &e)
            {
                throw QString("erro ao alocar memoria");
            }
            i = false;
            continue;
        }
        if (!vetor)
        {
            throw QString("Vetor nao criado");
        }
        QStringList parts = linha.split(";");
        int vertice1 = parts[0].toInt();
        int vertice2 = parts[1].toInt();
        int peso = parts[2].toInt();
        vetor->inserirAresta(vertice1, vertice2, peso);
    }
}
