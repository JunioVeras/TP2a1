// ---------------------------------------------------------------------
//  Arquivo	    : main.cpp
//  Conteúdo	: codigo completo do programa
//  Autor		: Junio veras de Jesus Lima
// ---------------------------------------------------------------------

#include <vector>
#include <stack>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <list>

struct Aresta
{
    int no;
    int custo;
};

class Grafo
{
    private:
        int N, M, Q;
        std::vector<std::vector<Aresta>> nos;

    public:
        Grafo();

        void imprime_grafo();
};

Grafo::Grafo()
{
    std::cin >> this->N;
    std::cin >> this->M;
    std::cin >> this->Q;

    int u, v, w;

    std::vector<Aresta> ligacao;
    for(int i = 0; i <= M; i++)
    {
        this->nos.push_back(ligacao);
    }

    for(int i = 0; i < M; i++)
    {
        std::cin >> u;
        std::cin >> v;
        std::cin >> w;
        Aresta aux;
        aux.no = v;
        aux.custo = w;
        this->nos[u].push_back(aux);
    }
}

void Grafo::imprime_grafo()
{
    for(int i = 1; i <= this->N; i++)
    {
        std::cout << "No " << i << std::endl;
        for(int j = 0; j < (int)this->nos[i].size(); j++)
        {
            std::cout << this->nos[i][j].no << " " << this->nos[i][j].custo << std::endl;
        }
    }
}

int main()
{
    Grafo grafo;
    grafo.imprime_grafo();

    return 0;
}