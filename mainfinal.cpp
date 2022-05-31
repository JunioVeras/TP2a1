// ---------------------------------------------------------------------
//  Arquivo	    : main.cpp
//  Conteúdo	: codigo completo do programa
//  Autor		: Junio veras de Jesus Lima
// ---------------------------------------------------------------------

#include <vector>
#include <iostream>
#include <queue>

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

struct ComparaNo
// metodo de comparacao da fila de prioridade (maior gargalo fica como primeiro elemento)
{
    bool operator()(No const& p1, No const& p2)
    {
        return p1.gargalo < p2.gargalo;
    }
};

class Grafo
{
    private:
        int N, M, Q;
        std::vector<std::vector<Aresta>> nos;
        std::vector<No> caminhos;
        std::priority_queue<No, std::vector<No>, ComparaNo> pq;

    public:
        Grafo();
        int Dijkstra(int u, int v);
        void realiza_consultas();
};

Grafo::Grafo()
// Descricao: Construtor do grafo
// Entrada: entrada do programa
// Saida: algumas das variaveis da classe sao inicializadas
{
    // inicializacao das variaveis de entrada
    std::cin >> this->N;
    std::cin >> this->M;
    std::cin >> this->Q;

    // criacao da lista de nos contendo a lista de todas as arestas incidentes
    // inicializacao da lista caminhos que sera usada para computar o caminho de maior gargalo
    std::vector<Aresta> ligacao;
    for(int i = 0; i <= this->N; i++)
    {
        No aux;
        aux.no = i;
        this->caminhos.push_back(aux);
        this->nos.push_back(ligacao);
    }

    // inicializacao da lista de nos contendo a lista de arestas
    int u, v, w;
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

int menor(int a, int b)
// Descricao: retorna o menor de 2 elementos
// Entrada: 2 elementos a e b
// Saida: o menor dos dois elementos
{
    if(a < b)
    {
        return a;
    }
    return b;
}

int maior(int a, int b)
// Descricao: retorna o maior de 2 elementos
// Entrada: 2 elementos a e b
// Saida: o maior dos dois elementos
{
    if(a > b)
    {
        return a;
    }
    return b;
}

int Grafo::Dijkstra(int u, int v)
// Descricao: realiza o algoritmo de dijkstra modificado para computar o caminho como maior gargalo
// Entrada: vertice de origem e destino da consulta
// Saida: o valor do gargalo do caminho encontrado
{
    // inicializa o gargalo do no de origem como infinito (no caso o maior numero de 32 bits possivel)
    this->caminhos[u].gargalo = INT32_MAX;

    // coloca todos os nos na fila de prioridade
    for(int i = 1; i <= this->N; i++)
    {
        this->pq.push(this->caminhos[i]);
    }

    // enquanto a fila nao estiver vazia
    while(!this->pq.empty())
    {
        // pega o elemento de maior prioridade (maior gargalo)
        No aux = this->pq.top();
        this->pq.pop();

        // se ele nao tiver sido visitado ele se torna visitado e percorre suas arestas incidentes
        if(this->caminhos[aux.no].visitado == 0)
        {
            this->caminhos[aux.no].visitado = 1;
            for(int i = 0; i < (int)this->nos[aux.no].size(); i++)
            {
                Aresta aresta = this->nos[aux.no][i];

                // considerando a aresta como (U,V), se o gargalo encontrado para o no V for menor que o gargalo utilizando a aresta atual com o no atual,
                // o gargalo de V passa a ser esse outro valor (o maior entre o gargalo antigo e o utilizando esta aresta)
                if(this->caminhos[aresta.no].gargalo < menor(this->caminhos[aux.no].gargalo, aresta.custo))
                {
                    this->caminhos[aresta.no].gargalo = menor(this->caminhos[aux.no].gargalo, aresta.custo);
                    this->caminhos[aresta.no].pred = aux.no;
                    
                    // coloca o no V na fila de prioridade com os novos valores, a fila eh refeita
                    No aux2;
                    aux2.no = aresta.no;
                    aux2.gargalo = this->caminhos[aresta.no].gargalo;
                    this->pq.push(aux2);
                }
            }
        }
    }
    // retorna o valor do gargalo do caminho de maior gargalo entre U e V
    return this->caminhos[v].gargalo;
}

void Grafo::realiza_consultas()
// Descricao: realiza o algorimo de dijkstra modificado para cada consulta
// Entrada: void
// Saida: o valor do gargalo do caminho de maior gargalo eh printado na tela
{
    // iteracao pelas consultas para realizacao do algoritmo
    for(int i = 0; i < this->Q; i++)
    {
        // recebimento das entradas de consulta
        int u, v;
        std::cin >> u;
        std::cin >> v;

        // reseta os valores dos nos da lista de caminhos
        for(int j = 1; j <= this->N; j++)
        {
            this->caminhos[j].gargalo = 0;
            this->caminhos[j].pred = 0;
            this->caminhos[j].visitado = 0;
        }

        // realizacao do algoritmo e print do resultado
        std::cout << Dijkstra(u, v) << std::endl;
    }
}

int main()
// Descricao: main
// Entrada: void
// Saida: o resultado das consultas eh printado
{
    Grafo grafo;
    grafo.realiza_consultas();

    return 0;
}
