#include <iostream>
#include <vector>
#include <ctime>
#include <experimental/random>
#include <fstream>

struct Aresta
{
    int no;
    int custo;
};

class Grafo
{
    private:
        int N;
        std::vector<std::vector<Aresta>> nos;
        std::vector<int> visitado;
        std::vector<int> caminho;

    public:
        Grafo(int N);
        bool DFS(int u, int v);
};

Grafo::Grafo(int N)
{
    std::srand(std::time(NULL));
    std::vector<Aresta> ligacao;
    for(int i = 0; i <= N; i++)
    {
        nos.push_back(ligacao);
        visitado.push_back(0);
    }

    for(int i = 1; i <= N; i++)
    {
        Aresta aux;
        aux.custo = 1000;
        aux.no = (i + 1);
        nos[i].push_back(aux);
    }
    nos[N][0].no = 1;
    for(int i = 1; i <= N; i++)
    {
        Aresta aux;
        aux.custo = 1000;
        aux.no = (i - 1);
        nos[i].push_back(aux);
    }
    nos[1][1].no = N;
    for(int i = 1; i <= N; i++)
    {
        int valor1, valor2, valor3;
        do
        {
            valor1 = (std::rand() % ((int)(N/3))) + 1; // std::experimental::randint(1,(int)(N/3));
        } while (valor1 == i || valor1 == i + 1 || valor1 == i - 1);
        do
        {
            valor2 = (std::rand() % ((int)(N/3))) + ((int)(N/3)) + 1; // std::experimental::randint((int)(N/3)+1,(int)(2*N/3));
        } while (valor2 == i || valor2 == i + 1 || valor2 == i - 1);
        do
        {
            valor3 = (std::rand() % ((int)(N/3))) + ((int)(2 * N/3)) + 1;// std::experimental::randint((int)(2*N/3)+1,N);
        } while (valor3 == i || valor3 == i + 1 || valor3 == i - 1);

        Aresta aux1;
        aux1.custo = 1000;
        aux1.no = valor1;
        Aresta aux2;
        aux2.custo = 1000;
        aux2.no = valor2;
        Aresta aux3;
        aux3.custo = 1000;
        aux3.no = valor3;

        nos[i].push_back(aux1);
        nos[i].push_back(aux2);
        nos[i].push_back(aux3);
    }

    int u, v;
    do
    {
        u = (std::rand() % 100) + 1;// std::experimental::randint(1,100);
        v = (std::rand() % 100) + 1;// std::experimental::randint(1,100);
    } while (u == v);
    
    DFS(u, v);

    std::ofstream arq;
    arq.open("gerado.txt");
    arq << N << " " << N * 5 << " " << 1 << std::endl;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 0; j < (int)nos[i].size(); j++)
        {
            arq << i << " " << nos[i][j].no << " " << nos[i][j].custo << std::endl;
        }
    }
    arq << u << " " << v << std::endl;
    arq << u << " ";
    for(int i = (int)caminho.size() - 1; i >= 0; i--)
    {
        arq << caminho[i] << " ";
    }
}

bool Grafo::DFS(int u, int v)
{
    for(int i = 0; i < (int)nos[u].size(); i++)
    {
        int no = nos[u][i].no;
        if(visitado[no] == 0)
        {
            visitado[no] = 1;
            if(no == v)
            {
                caminho.push_back(no);
                nos[u][i].custo = 2000;
                return 1;
            }
            if(DFS(no, v))
            {
                caminho.push_back(no);
                nos[u][i].custo = 2000;
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    std::srand(std::time(nullptr));
    int N;
    std::cin >> N;
    if(N >= 12)
    {
        Grafo grafo(N);

    }
    return 0;
}