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
    int direcao;
};

class Grafo
{
    private:
        int N, M, Q;
        std::vector<std::vector<Aresta>> nos;
        std::vector<Aresta> apath;
        std::vector<int> explorado;
        int gargalo;
        int maior_custo;
    public:
        Grafo();
        bool DFS(int u, int v);
        void add_fluxo(int u, int v);
        void realiza_consultas();
        void imprime_grafo();
};

Grafo::Grafo()
{
    std::cin >> this->N;
    std::cin >> this->M;
    std::cin >> this->Q;
    this->maior_custo = 0;

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
        if(this->maior_custo < w)
        {
            this->maior_custo = w;
        }
        Aresta aux;
        aux.no = v;
        aux.custo = w;
        aux.usado = 0;
        aux.direcao = 1;
        this->nos[u].push_back(aux);
        aux.no = u;
        aux.direcao = -1;
        this->nos[v].push_back(aux);
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
        Aresta no = this->nos[u][i];
        //dfs normal
        if(this->explorado[no.no] == 0 && ((no.direcao == 1 && no.usado != no.custo) || (no.direcao == -1 && no.usado != 0)))
        {
            this->explorado[no.no] = 1;
            if(no.no == v)
            {
                this->apath.push_back(no);
                if(no.direcao == 1)
                {
                    if(this->gargalo > (no.custo - no.usado))
                    {
                        this->gargalo = no.custo - no.usado;
                    }
                }
                if(no.direcao == -1)
                {
                    if(this->gargalo > no.usado)
                    {
                        this->gargalo = no.usado;
                    }
                }
                return 1;
            }
            if(DFS(no.no, v))
            {
                this->apath.push_back(no);
                if(no.direcao == 1)
                {
                    if(this->gargalo > (no.custo - no.usado))
                    {
                        this->gargalo = no.custo - no.usado;
                    }
                }
                if(no.direcao == -1)
                {
                    if(this->gargalo > no.usado)
                    {
                        this->gargalo = no.usado;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

void Grafo::add_fluxo(int u, int v)
{
    int atual = u;
    std::cout << this->gargalo << std::endl;
    for(int i = (int)this->apath.size() - 1; i >= 0; i--)
    {
        for(int j = 0; j < this->nos[atual].size(); j++)
        {
            // std::cout << this->nos[atual][j].no << " " << this->apath[i].no << std::endl;
            if(this->nos[atual][j].no == this->apath[i].no && this->nos[atual][j].direcao == this->apath[i].direcao)
            {
                if(this->nos[atual][j].direcao == 1)
                {
                    this->nos[atual][j].usado += this->gargalo;
                    for(int k = 0; k < (int)this->nos[this->nos[atual][j].no].size(); k++)
                    {
                        if(this->nos[this->nos[atual][j].no][k].no == atual && this->nos[this->nos[atual][j].no][k].direcao == -1)
                        {
                            this->nos[this->nos[atual][j].no][k].usado = this->nos[atual][j].usado;
                            break;
                        }
                    }
                }
                if(this->nos[atual][j].direcao == -1)
                {
                    this->nos[atual][j].usado -= this->gargalo;
                    for(int k = 0; k < (int)this->nos[this->nos[atual][j].no].size(); k++)
                    {
                        if(this->nos[this->nos[atual][j].no][k].no == atual && this->nos[this->nos[atual][j].no][k].direcao == 1)
                        {
                            this->nos[this->nos[atual][j].no][k].usado = this->nos[atual][j].usado;
                            break;
                        }
                    }
                }
                std::cout << this->nos[atual][j].no << " " << this->nos[atual][j].usado << std::endl;
            }
        }
        atual = this->apath[i].no;
    }
}

void Grafo::realiza_consultas()
{
    for(int i = 0; i < this->Q; i++)
    {
        int u, v;
        std::cin >> u;
        std::cin >> v;
        do
        {
            this->apath.clear();
            this->gargalo = 0;
            for(int j = 0; j < this->explorado.size(); j++)
            {
                this->explorado[j] = 0;
            }
            this->explorado[u] = 1;
            this->gargalo = this->maior_custo;
            if(DFS(u, v))
            {
                add_fluxo(u, v);
                // imprime_grafo();
            }
            else
            {
                break;
            }
        }while(1);
        int fluxo_maximo = 0;
        for(int j = 0; j < (int)this->nos[v].size(); j++)
        {
            std::cout << fluxo_maximo << " ";
            fluxo_maximo += this->nos[v][j].usado;
        }
        std::cout << fluxo_maximo << std::endl;
    }

}

void Grafo::imprime_grafo()
{
    // for(int i = 1; i <= this->N; i++)
    // {
    //     std::cout << "No " << i << std::endl;
    //     for(int j = 0; j < (int)this->nos[i].size(); j++)
    //     {
    //         std::cout << this->nos[i][j].no << " " << this->nos[i][j].custo << std::endl;
    //     }
    // }
    std::cout << std::endl;
    for(int i = 0; i < ((int)this->apath.size()); i++)
    {
        std::cout << this->apath[i].no << " " << this->apath[i].usado << " | ";
    }
    std::cout << std::endl;
}

int main()
{
    Grafo grafo;
    grafo.realiza_consultas();

    return 0;
}