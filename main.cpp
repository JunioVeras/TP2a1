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
    int usado;
};

class Grafo
{
    private:
        int N, M, Q;
        std::vector<std::vector<int>> nos;
        std::vector<int> apath;
        std::vector<int> explorado;
    public:
        Grafo();
        bool DFS(int u, int v);
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
    for(int i = 0; i <= this->M; i++)
    {
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
        aux.usado = 0;
        this->nos[u].push_back(aux);
    }

    for(int i = 0; i <= this->N; i++)
    {
        this->explorado.push_back(0);
    }
}

bool Grafo::DFS(int u, int v)
{
    for(int i = 0; i < (int)this->nos[u].size(); i++)
    {
        int no = this->nos[u][i].no;
        if(this->explorado[no] == 0)
        {
            this->explorado[no] = 1;
            if(no == v)
            {
                this->apath.push_back(no);
                return 1;
            }
            if(DFS(no, v))
            {
                this->apath.push_back(no);
                return 1;
            }
        }
    }
    return 0;
}

void Grafo::realiza_consultas()
{
    for(int i = 0; i < this->Q; i++)
    {
        int u, v;
        std::cin >> u;
        std::cin >> v;
        DFS(u, v);
        // while(DFS(u, v))
        // {
        //     // mexe no grafo
        // }
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
    std::cout << std::endl;
    for(int i = ((int)this->apath.size()) - 1; i >= 0; i--)
    {
        std::cout << this->apath[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    Grafo grafo;
    grafo.realiza_consultas();
    grafo.imprime_grafo();

    return 0;
}