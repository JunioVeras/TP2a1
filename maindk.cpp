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

struct No
{
    int no;
    int gargalo;
    int pred;
    int visitado;
};

struct CompareNo {
    bool operator()(No const& p1, No const& p2)
    {
        return p1.gargalo > p2.gargalo;
    }
};

class Grafo
{
    private:
        int N, M, Q;
        std::vector<std::vector<Aresta>> nos;
        std::vector<No> arvore;
        std::priority_queue<No, std::vector<No>, CompareNo> pq;

    public:
        Grafo();
        void altera_chaves();
        int Dijkstra(int u, int v);
        void realiza_consultas();
        void imprime_grafo();
};

Grafo::Grafo()
{
    std::cin >> this->N;
    std::cin >> this->M;
    std::cin >> this->Q;

    int u, v, w;

    std::vector<Aresta> ligacao;
    for(int i = 0; i <= this->N; i++)
    {
        No aux;
        aux.no = i;
        this->arvore.push_back(aux);
        this->nos.push_back(ligacao);
    }

    for(int i = 0; i < this->M; i++)
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

void Grafo::altera_chaves()
{

}

int Grafo::Dijkstra(int u, int v)
{
    this->arvore[u].gargalo = 0;
    for(int i = 1; i <= this->N; i++)
    {
        this->pq.push(this->arvore[i]);
    }
    while(!this->pq.empty())
    {
        No aux = this->pq.top();
        this->pq.pop();
        if(this->arvore[aux.no].visitado == 0)
        {
            this->arvore[aux.no].visitado = 1;
            for(int i = 0; i < (int)this->nos[aux.no].size(); i++)
            {
                Aresta aresta = this->nos[aux.no][i];
                if(this->arvore[aresta.no].gargalo > this->arvore[aux.no].gargalo + aresta.custo)
                {
                    //
                    this->arvore[aresta.no].gargalo = this->arvore[aux.no].gargalo + aresta.custo;
                    this->arvore[aresta.no].pred = aux.no;
                    No aux2;
                    aux2.no = aresta.no;
                    aux2.gargalo = this->arvore[aresta.no].gargalo;
                    this->pq.push(aux2);
                }
            }
        }
    }
    return this->arvore[v].gargalo;
}

void Grafo::realiza_consultas()
{
    for(int i = 0; i < this->Q; i++)
    {
        int u, v;
        std::cin >> u;
        std::cin >> v;
        for(int j = 1; j <= this->N; j++)
        {
            this->arvore[j].gargalo = INT32_MAX;
            this->arvore[j].pred = 0;
            this->arvore[j].visitado = 0;
        }
        std::cout << Dijkstra(u, v) << std::endl;
    }
}

int main()
{
    Grafo grafo;
    grafo.realiza_consultas();

    return 0;
}