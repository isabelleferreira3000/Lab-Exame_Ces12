//
// PATTERN: VECTOR AND MATRIX STARTS ON 0
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#define DEBUG

using namespace std;

class City {
public:
    int index;
    int fatherIndex;
    int fatherDistance;
    int x;
    int y;
    bool alreadyAnalyzed;

    City();
    ~City();
};

class Graph{
public:
    std::vector<vector<int>> adjacencyMatrix;

    Graph(std::vector<City> &cities);
    ~Graph();

    void printAdjacencyMatrix();
    void printCitiesXY();
    int distance(City city1, City city2);
};

class Heap{
public:
    std::vector<City> heap;
    int size;

    Heap(std::vector<City> &cities);
    ~Heap();

    void print();
    void Sift(int i);
    bool compare(City city1, City city2);
    City min();
    City extractMin();
    void modify(int k, City city);
    int fatherIndex(int k);
    void insert(City city);
    void remove(City city);
};

int numberOfCities;
std::vector<City> cities;
std::vector<vector<int>> adjacencyMatrix;

// le o arquivo, calcula o vetor de cidades
void readFile (string file)
{
    ifstream input;
    input.open (file);

    if (input.is_open())
    {
        input >> numberOfCities;

        cities.resize((unsigned long)numberOfCities);
    }
    else
        cout << "nao achou o arquivo" << std::endl;

    int index, x, y;

    for (int i = 0; i < numberOfCities; i++){
        input >> index;
        input >> x;
        input >> y;

        cities[i].index = index;
        cities[i].fatherIndex = -1;
        cities[i].x  = x;
        cities[i].y = y;
        cities[i].alreadyAnalyzed = false;
    }

    input.close();
}

//class WeightAndVertice{
//public:
//    int weight;
//    int vertice;
//
//    WeightAndVertice(int weight, int vertice);
//    ~WeightAndVertice();
//};

// Q é um conjunto de pares (peso, vértice)
Heap *Q;
Graph *G;

void prim (){

    City v;

    Q->insert(cities[0]);

    while (Q->size != 0){
        v = Q->extractMin();
        v.alreadyAnalyzed = true;

        for (int u = 0; u < numberOfCities; u++){
            if (u != v.index && !cities[u].alreadyAnalyzed){
                if (cities[u].fatherIndex == -1){
//                    Q->insert(cities[u])
                }
                else{
                    if (G->adjacencyMatrix[cities[u].fatherIndex][u] > G->adjacencyMatrix[v.index][u]){

                    }
                }
            }
        }
    }

}

//
// IMPLEMENTANDO AS CIDADES
//

City::City() {
    index = 0;
    x = 0;
    y = 0;
    fatherIndex = 0;
    fatherDistance = 0;
    alreadyAnalyzed = false;
}

City::~City() = default;

//
// IMPLEMENTANDO O GRAFO
//

Graph::Graph(std::vector<City> &cities) {
    adjacencyMatrix.resize(numberOfCities);
    for (int i = 0; i < numberOfCities; i++){
        adjacencyMatrix[i].resize(numberOfCities);
    }

    for (int i = 0; i < numberOfCities; i++){
        for (int j = 0; j < numberOfCities; j++){
            adjacencyMatrix[i][j] = distance(cities[i], cities[j]);
        }
    }
}

Graph::~Graph(){
    for (int i = 0; i < numberOfCities; i++){
        adjacencyMatrix[i].clear();
    }
    adjacencyMatrix.clear();
};

int Graph::distance(City city1, City city2) {
    int xd = city2.x - city1.x;
    int yd = city2.y - city1.y;
    int dij;
    dij = int(sqrt(xd * xd + yd * yd) + 0.5);
    return dij;
}

void Graph::printAdjacencyMatrix() {
    cout << endl << "IMPRESSAO DA MATRIZ DE ADJACENCIAS:"<< endl;
    for (int i = 0; i < numberOfCities; i++){
        for (int j = 0; j < numberOfCities; j++){
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Graph::printCitiesXY() {
    cout << endl << "IMPRESSAO DO VETOR GLOBAL DE CIDADES X E Y:"<< endl;
    for (int i = 0; i < numberOfCities; i++){
        cout << cities[i].index << " " << cities[i].x << " " << cities[i].y << endl;
    }
    cout << endl << endl;
}

//
// IMPLEMENTANDO A HEAP
//

Heap::Heap(std::vector<City> &cities) {
    this->size = (int) cities.size();
    heap.resize(size);

    for (int i = 0; i < this->size; i++){
        cities[i].fatherDistance = i;
        this->heap[i] = cities[i];
    }

    int halfSizeOfVector = this->size/2 - 1;
    for (int i = halfSizeOfVector; i >= 0; i--){
        Sift(i);
    }
}

Heap::~Heap() {
    heap.clear();
}

void Heap::Sift(int i) {
    int left = 2*i + 1;
    int right = 2*i + 2;
    int smaller = i;
    City aux;

    if (left < this->size && compare(this->heap[left], this->heap[i]))
        smaller = left;
    if (right < this->size && compare(this->heap[right], this->heap[smaller]))
        smaller = right;
    if (smaller != i) {
        aux = this->heap[i];
        this->heap[i] = this->heap[smaller];
        this->heap[smaller] = aux;
        Sift(smaller);
    }
}

bool Heap::compare(City city1, City city2) {
    if (city1.fatherDistance < city2.fatherDistance){
        return true;
    }
    return false;
//
//    else if (smallerDistanceToSubGraph[city1.index] == smallerDistanceToSubGraph[city2.index]){
//        if (city1.fatherIndex < city2.fatherIndex){
//            return true;
//        }
//        else if (city1.fatherIndex == city2.fatherIndex){
//            return city1.index < city2.index;
//        }
//    }
//    else
//        return false;
}

City Heap::min() {
    return this->heap[0];
}

City Heap::extractMin() {
    if (this->size < 1)
        cout << "Heap underflow" << std::endl;
    else {
        City min = this->heap[0];
        this->heap[0] = this->heap[this->size-1];
        this->size--;
        Sift(0);
        return min;
    }
}

void Heap::modify(int k, City city) {
    City aux;
    if (k >= this->size || k < 0)
        cout << "Index error" << std::endl;
    else {
        this->heap[k] = city;

        while (k > 0 && compare(this->heap[fatherIndex(k)], this->heap[k])) { //conserta para cima
            aux = this->heap[k];
            this->heap[k] = this->heap[fatherIndex(k)];
            this->heap[fatherIndex(k)] = aux;
            k = fatherIndex(k);
        }
        Sift(k); // ou conserta para baixo
    }
}

int Heap::fatherIndex(int k) {
    if (k % 2 == 0){
        return k/2-1;
    }
    else
        return k/2;
}

void Heap::insert(City city) {
    this->size++;
    modify(this->size-1, city);
}

void Heap::remove(City city) {
    int i;
    bool find = false;
    for (i = 0; i < size && !find; i++) {
        if (cities[i].index == city.index) {
            find = true;
        }
    }
    i--;
    City aux = heap[size-1];
    size--;
    modify(i, aux);
}

void Heap::print() {
    cout << endl << "IMPRESSAO DA HEAP:"<< endl;
    for (int i = 0; i < size; i++){
        cout << "indice da cidade: " << heap[i].index <<
             ", distancia pro pai: " << heap[i].fatherDistance << endl;
    }
    cout << endl << endl;

}

int main() {
    int numberFiles = 1;

    for (int i = 1; i <= numberFiles; i++){
        readFile("../entrada.txt");

        G = new Graph(cities);
        Q = new Heap(cities);

#ifdef DEBUG
        G->printCitiesXY();
        G->printAdjacencyMatrix();
        Q->print();
#endif

        delete G;
        delete Q;
    }

    return 0;
}