#include <iostream>
#include <algorithm>
#include <fstream> //Biblioteca pra trabalhar com arquivos
#include <vector>
#include <list>

using namespace std;
vector<vector<int>> LerGrafo(const string &nomeArquivo, int &numVertices);
vector<int> EncontrarCliqueMaximo(vector<vector<int>> &grafo, int numVertices);
void EncontraClique(vector<vector<int>> &grafo, vector<int> &P, vector<int> &X, vector<int> &R);

int main()
{
  int numVertices = 0;
  string nomeArquivo;

  vector<vector<int>> grafo = LerGrafo(nomeArquivo, numVertices);
  
  vector<int> cliqueMaxima = EncontrarCliqueMaximo(grafo, numVertices);
  
  cout << "[";
  for (auto elemento : cliqueMaxima)
  {
    cout << elemento << " ";
  }
  cout << "]" << endl;
  return 0;
}

// Função para ler o grafo a partir do arquivo de entrada
vector<vector<int>> LerGrafo(const string &nomeArquivo, int &numVertices)
{
  // ifstream arquivo(nomeArquivo);
  int numArestas;
  // arquivo >> numVertices >> numArestas;

  cin >> numVertices >> numArestas;
  cout << "Num Arestas: " << numArestas << endl;
  vector<vector<int>> grafo(numVertices, vector<int>(numVertices, 0));
  cout << "Li grafo \n";
  for (int i = 0; i < (numArestas - 1); ++i)
  {
    int u, v;
    cin >> u >> v;
    grafo[u - 1][v - 1] = 1;
    grafo[v - 1][u - 1] = 1; // O grafo é não direcionado
  }

  // arquivo.close();
  cout << "Cosntrui a matriz \n";
  return grafo;
}

vector<int> EncontrarCliqueMaximo(vector<vector<int>>& grafo, int numVertices)
{
  cout << "Entrei em 'EncontrarCliqueMaximo' \n";
  vector<int> P; // Conjunto dos candidatos
  vector<int> X; // COnjunto do Não Candidatos
  vector<int> R; // Conjunto resposta

  for (int i = 0; i < numVertices; i++)
  {
    P.push_back(i); // Preenche a lista de candidatos
  }
  cout << "Preenchi candidatos  - Tamanho: " << P.size() << endl;
  EncontraClique(grafo, P, X, R);
  return R;
}
void EncontraClique(vector<vector<int>>& grafo, vector<int> &P, vector<int> &X, vector<int> &R)
{
  if (P.empty())
  {
    return;
  }

  int v = P.back(); // Vértice de referência
  P.pop_back();
  cout << "Numero de candidatos: " << P.size() << endl;
  for (int i = 0; i < P.size() - 1; i++)
  {
    int u = P[i]; // Vértice Candidato
    if (grafo[v][u] == 1)
    {
      R.push_back(u);         // Adiciona o candidato ao conjunto solução
      cout << "Tamanho R: " << R.size() << endl;
      P.erase(P.begin() + i); // Remove o candidato da lista de candidatos
      /*
        Utilizando a estratégia do algoritmo Bron-Kerbosch, chama-se recursivamente a
        fução EncontraClique afim de percorrere todos os vértices candidatos.
      */
      EncontraClique(grafo, P, X, R);

      /*
        Ao fim da recurção, um clique estará formado, então deve-se analisar novamente
        o gráfo afim de eoncontrar outros cliques. Portanto:
      */

      R.pop_back();               // Remove o vértice de referência da co conjunto solução
      P.insert(P.begin() + i, u); // Adiciona de volta o vértice candidato.
    }
    else
    {                         // Caso o vértice candidato não seja adjacente ao vértice de referência
      X.push_back(u);         // Adiciona o candidato ao conjunto dos Não Adjacentes
      P.erase(P.begin() + i); // Remove o candidato da lita de candidatos.
    }
  }
}
