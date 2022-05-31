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
        std::vector<int> explorado;
        int custo_maximo;
        int gargalo;

    public:
        Grafo();
        bool DFS(int u, int v, int custo);
        void realiza_consultas();
        void imprime_grafo();
};

Grafo::Grafo()
{
    std::cin >> this->N;
    std::cin >> this->M;
    std::cin >> this->Q;
    this->custo_maximo = 0;

    int u, v, w;

    std::vector<Aresta> ligacao;
    for(int i = 0; i <= this->N; i++)
    {
        this->nos.push_back(ligacao);
    }

    for(int i = 0; i < this->M; i++)
    {
        std::cin >> u;
        std::cin >> v;
        std::cin >> w;
        if(w > this->custo_maximo)
        {
            this->custo_maximo = w;
        }
        Aresta aux;
        aux.no = v;
        aux.custo = w;
        this->nos[u].push_back(aux);
    }

    for(int i = 0; i <= this->N; i++)
    {
        this->explorado.push_back(0);
    }
}

int menor(int a, int b)
{
    if(a < b)
    {
        return a;
    }
    return b;
}

int maior(int a, int b)
{
    if(a > b)
    {
        return a;
    }
    return b;
}

bool Grafo::DFS(int u, int v, int custo)
{
    for(int i = 0; i < (int)this->nos[u].size(); i++)
    {
        Aresta no = this->nos[u][i];

        if(this->explorado[no.no] == 0)
        {
            this->explorado[no.no] = 1;
            if(no.no == v)
            {
                this->explorado[no.no] = 0;
                this->gargalo = maior(menor(no.custo, custo), this->gargalo);
            }
            else
            {
                DFS(no.no, v, menor(custo, no.custo));
                this->explorado[no.no] = 0;
            }
        }
    }
    return 0;
}

void Grafo::realiza_consultas()
{
    for(int i = 0; i < this->Q; i++)
    {
        this->gargalo = 0;
        int u, v;
        std::cin >> u;
        std::cin >> v;
        this->explorado[u] = 1;
        DFS(u, v, this->custo_maximo);
        std::cout << this->gargalo << std::endl; 
        for(int i = 0; i < (int)this->explorado.size(); i++)
        {
            this->explorado[i] = 0;
        }
        this->gargalo = 0;
    }
}

int main()
{
    Grafo grafo;
    grafo.realiza_consultas();

    return 0;
}