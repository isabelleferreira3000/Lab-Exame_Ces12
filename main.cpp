//
// PATTERN: VECTOR AND MATRIX STARTS ON 0
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

#define DEBUG
#define INF 1000000000

using namespace std;

int currentInput;

class City {
public:
    int index;
    int fatherIndex;
    int fatherDistance;
    float x;
    float y;
    bool alreadyAnalyzed;

    City();
    ~City();

    void printCity();
};


bool compare(City &city1, City &city2){
    return city1.index < city2.index;
}

class Graph{
public:
    std::vector<vector<int>> adjacencyMatrix;
    std::vector<vector<City>> adjacencyList;
    std::vector<bool> visited;
    std::vector<int> orderToVisit;
    long long int totalSum;

    Graph(std::vector<City> &cities);
    ~Graph();

    void printAdjacencyMatrix();
    void printAdjacencyList();
    void printCitiesXY();
    void printOrderToVisit();
    int distance(City &city1, City &city2);
    void DFS(City &u);
    void travelingSalesMan();
};

class Heap{
public:
    std::vector<City> heap;
    int size;

    Heap(std::vector<City> &cities);
    ~Heap();

    void printHeap();
    void Sift(int i);
    bool compare(City &city1, City &city2);
    City min();
    City extractMin();
    void modify(int k, City &city);
    void modifyWithIndex(City &city);
    int fatherPositionOnHeap(int k);
//    void remove(City &city);
};

int numberOfCities;
std::vector<City> cities;
//std::vector<vector<int>> adjacencyMatrix;

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

    int index;
    float x, y;

    for (int i = 0; i < numberOfCities; i++){
        input >> index;
        input >> x;
        input >> y;

        cities[i].index = index;
        cities[i].fatherIndex = -1;
        cities[i].fatherDistance = INF;
        cities[i].x  = x;
        cities[i].y = y;
        cities[i].alreadyAnalyzed = false;
    }
    if (numberOfCities != 0){
        sort(cities.begin(), cities.end(), compare);
        input.close();
    }
}

ofstream output;
void writeFile(Graph G){
    if (output.is_open()){
        output << G.totalSum << "\n";
    }

}

// Q é um conjunto de pares (peso, vértice)
Heap *Q;
Graph *G;

void prim (){
    if (numberOfCities != 0){
        City v;

        int indexOfFirst = 0;
        cities[indexOfFirst].fatherDistance = 0;
        Q->modifyWithIndex(cities[indexOfFirst]);

        while (Q->size != 0) {
            v = Q->extractMin();
            if (v.index != 1){
                G->adjacencyList[v.fatherIndex-1].push_back(v);
            }
            cities[v.index-1].alreadyAnalyzed = true;
            for (int u = 0; u < numberOfCities; u++){
                if (!cities[u].alreadyAnalyzed) {
                    if (cities[u].fatherDistance > G->adjacencyMatrix[v.index-1][u]){
                        cities[u].fatherIndex = v.index;
                        cities[u].fatherDistance = G->adjacencyMatrix[v.index-1][u];
                        Q->modifyWithIndex(cities[u]);
                    }
                    else if (cities[u].fatherDistance == G->adjacencyMatrix[v.index-1][u]){
                        if (cities[u].fatherIndex > v.index){
                            cities[u].fatherIndex = v.index;
                            Q->modifyWithIndex(cities[u]);
                        }
                    }
                }
            }
        }
        G->DFS(G->adjacencyList[0][0]);
        G->travelingSalesMan();
    }
}

City::City() {
    index = 0;
    x = 0;
    y = 0;
    fatherIndex = 0;
    fatherDistance = INF;
    alreadyAnalyzed = false;
}

void City::printCity() {
    cout << "IMPRESSAO DA CIDADE " << index << endl;
    cout << "Pai atual: " << fatherIndex << endl;
    cout << "Distancia pro pai: " << fatherDistance << endl;
}

City::~City() = default;


Graph::Graph(std::vector<City> &cities) {
    totalSum = 0;

    visited.resize(numberOfCities);
    for (int i = 0; i < numberOfCities; i++){
        visited[i] = false;
    }

    adjacencyMatrix.resize(numberOfCities);
    for (int i = 0; i < numberOfCities; i++){
        adjacencyMatrix[i].resize(numberOfCities);
    }

    for (int i = 0; i < numberOfCities; i++){
        for (int j = 0; j < numberOfCities; j++){
            adjacencyMatrix[i][j] = distance(cities[i], cities[j]);
        }
    }
    adjacencyList.resize(numberOfCities);
    for (int i = 0; i < numberOfCities; i++){
        adjacencyList[i].push_back(cities[i]);
    }
}

Graph::~Graph(){
    for (int i = 0; i < numberOfCities; i++){
        adjacencyMatrix[i].clear();
    }
    adjacencyMatrix.clear();

    for (int i = 0; i < adjacencyList.size(); i++){
        adjacencyList[i].clear();
    }
    adjacencyList.clear();
};

int Graph::distance(City &city1, City &city2) {
    float xd = city2.x - city1.x;
    float yd = city2.y - city1.y;
    int dij;
    dij = int(sqrt(xd * xd + yd * yd) + 0.5);
    return dij;
}

void Graph::printAdjacencyMatrix() {
    cout << endl << "IMPRESSAO DA MATRIZ DE ADJACENCIAS:"<< endl;
    cout << "  ";
    for (int i = 0; i < numberOfCities; i++){
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < numberOfCities; i++){
        for (int j = 0; j < numberOfCities; j++){
            if (j == 0)
                cout << i << " ";
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Graph::printCitiesXY() {
    cout << endl << "IMPRESSAO DO VETOR GLOBAL DE CIDADES X E Y:"<< endl;
    cout << numberOfCities << endl;
    for (int i = 0; i < numberOfCities; i++){
        cout << cities[i].index << " " << cities[i].x << " " << cities[i].y << endl;
    }
    cout << endl << endl;
}

void Graph::printAdjacencyList() {
    cout << endl << "IMPRESSAO DA LISTA DE ADJACENCIA:"<< endl;
    for (int i = 0; i < numberOfCities; i++){
        for (int j = 0; j < adjacencyList[i].size(); j++){
            cout << adjacencyList[i][j].index << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Graph::DFS(City &u) {
    visited[u.index-1] = true;
    orderToVisit.push_back(u.index);

    for (int j = 0; j < adjacencyList[u.index-1].size(); j++){
        City v = adjacencyList[u.index-1][j];
        if(!visited[v.index-1]) {
            DFS(v);
        }
    }
}

void Graph::travelingSalesMan() {
    totalSum += adjacencyMatrix[orderToVisit[0]-1][orderToVisit[numberOfCities-1]-1];
    for (int i = 1; i < numberOfCities; i++){
        totalSum += adjacencyMatrix[orderToVisit[i]-1][orderToVisit[i-1]-1];
    }
}

void Graph::printOrderToVisit() {
    cout << endl << "IMPRESSAO DO ORDER TO VISIT:"<< endl;
    for (int i = 0; i < numberOfCities; i++){
        cout << orderToVisit[i] << " ";
    }
    cout << endl << endl;
}

Heap::Heap(std::vector<City> &cities) {
    size = numberOfCities;
    heap.resize(size);

    for (int i = 0; i < size; i++){
        heap[i] = cities[i];
    }
    if (size != 0){
        int halfSizeOfVector = size/2 - 1;
        for (int i = halfSizeOfVector; i >= 0; i--){
            Sift(i);
        }
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

    if (left < size && compare(heap[left], heap[i]))
        smaller = left;
    if (right < size && compare(heap[right], heap[smaller]))
        smaller = right;
    if (smaller != i) {
        aux = heap[i];
        heap[i] = heap[smaller];
        heap[smaller] = aux;
        Sift(smaller);
    }
}

bool Heap::compare(City &city1, City &city2) {
    if (city1.fatherDistance < city2.fatherDistance){
        return true;
    }
    else if (city1.fatherDistance == city2.fatherDistance) {
        if (city1.fatherIndex < city2.fatherIndex) {
            return true;
        } else if (city1.fatherIndex == city2.fatherIndex) {
            if (city1.index < city2.index)
                return true;
        }
    }
    return false;
}

City Heap::min() {
    return this->heap[0];
}

City Heap::extractMin() {
    if (size < 1)
        cout << "Heap underflow" << std::endl;
    else {
        City min = heap[0];
        heap[0] = heap[size-1];
        size--;
        Sift(0);
        return min;
    }
}


void Heap::modify(int k, City &city) {
    City aux;
    if (k >= size || k < 0){
        cout << "current input: " << currentInput << endl;
        cout << "Index error" << std::endl;
    }
    else {
        heap[k] = city;

        while (k > 0 && compare(heap[k], heap[fatherPositionOnHeap(k)])) { //conserta para cima
            aux = heap[k];
            heap[k] = heap[fatherPositionOnHeap(k)];
            heap[fatherPositionOnHeap(k)] = aux;
            k = fatherPositionOnHeap(k);
        }
        Sift(k); // ou conserta para baixo
    }
}

int Heap::fatherPositionOnHeap(int k) {
    if (k % 2 == 0){
        return k/2-1;
    }
    else
        return k/2;
}

void Heap::printHeap() {
    cout << endl << "IMPRESSAO DA HEAP:"<< endl;
    for (int i = 0; i < size; i++){
        cout << "indice da cidade: " << heap[i].index <<
             ", distancia pro pai: " << heap[i].fatherDistance << endl;
    }
    cout << endl << endl;

}

void Heap::modifyWithIndex(City &city) {
    // CRIAR UM VETOR QUE GUARDA A POSICAO DA CIDADE NA HEAP ANTES DE ENTREGAR
    int k = -1; // k é a posição da cidade na heap
    for (int i = 0; i < numberOfCities && k == -1; i++){
        if (heap[i].index == city.index){
            k = i;
        }
    }
    modify(k, city);
}

int main() {
    int numberFiles;

    cin >> numberFiles;
    string nameInputFile;

    if (numberFiles < 1){
        cout << "numero de arquivos menor que 1" << endl;
    }
    else if (numberFiles > 99){
        cout << "numero de arquivos maior que 99" << endl;
    }
    output.open ("saida.txt");

    for (currentInput = 1; currentInput <= numberFiles; currentInput++){
        nameInputFile = "ent";

        if (currentInput >= 1 && currentInput <= 9){
            nameInputFile += '0';
            nameInputFile += std::to_string(currentInput);
            nameInputFile += ".txt";
        }
        else if (currentInput >= 10 && currentInput <= 99){
            nameInputFile += std::to_string(currentInput);
            nameInputFile += ".txt";
        }
//        nameInputFile = "../ent07.txt";
        readFile(nameInputFile);

        G = new Graph(cities);
//        G->printCitiesXY();
//        G->printAdjacencyMatrix();
        Q = new Heap(cities);
        prim();
//        cout << "current input terminou o prim: " << currentInput << endl;
        writeFile(*G);

#ifdef DEBUG
        G->printCitiesXY();
        G->printAdjacencyMatrix();
        G->printAdjacencyList();
        G->printOrderToVisit();
#endif

        delete G;
        delete Q;
    }
    output.close();

    return 0;
}