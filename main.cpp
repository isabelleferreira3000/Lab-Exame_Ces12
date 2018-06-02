#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

class Coordinates {
public:
    int index;
    int x;
    int y;
    int paiIndex;

    Coordinates();
    ~Coordinates();
};

int distance(Coordinates city1, Coordinates city2){
    int xd = city2.x - city1.x;
    int yd = city2.y - city1.y;
    int dij;
    dij = int(sqrt(xd * xd + yd * yd) + 0.5);
    return dij;
}

int numberOfCities;
std::vector<Coordinates> coordinates;
std::vector<vector<int>> adjacencyMatrix;
std::vector<int> smallerDistanceToSubGraph;

class Heap{
    std::vector<Coordinates> heap;
    Heap(std::vector<Coordinates> coordinates);
    ~Heap();
    void Sift(int i, int sizeOfVector);
    bool compare(Coordinates city1, Coordinates city2);
};

// le o arquivo, calcula o vetor de coordenadas, a matriz de adjacencias e retorna o numero de cidades
void readFile (string file)
{
    ifstream input;
    input.open (file);

    if (input.is_open())
    {
        input >> numberOfCities;
        coordinates.resize(numberOfCities+1);
    }
    else
        cout << "nao achou o arquivo";

    int index, x, y;

    for (int i = 1; i <= numberOfCities; i++){
        input >> index;
        input >> x;
        input >> y;

        coordinates[i].index = index;
        coordinates[i].x  = x;
        coordinates[i].y = y;
    }

    adjacencyMatrix.resize(numberOfCities+1);
    for (int i = 1; i <= numberOfCities; i++){
        adjacencyMatrix[i].resize(numberOfCities+1);
    }

    for (int i = 1; i <= numberOfCities; i++){
        for (int j = 1; j <= numberOfCities; j++){
            adjacencyMatrix[i][j] = distance(coordinates[i], coordinates[j]);
        }
    }

    input.close();
}

struct weightAndVertice{
    int weight;
    int vertice;
};

std::vector<weightAndVertice> Q;

void prim (){
    int firstVertice = 1;
    smallerDistanceToSubGraph.resize(numberOfCities+1);
    smallerDistanceToSubGraph[1] = 0;

    for (int i = 1; i <= numberOfCities; i++){
        coordinates[i].paiIndex = 0;

    }
}

int main() {
     readFile("../entrada.txt");

//    for (int i = 1; i <= numberOfCities; i++){
//        cout << coordinates[i].index << " " << coordinates[i].x << " " << coordinates[i].y << endl;
//    }
//    for (int i = 1; i <= numberOfCities; i++){
//        for (int j = 1; j <= numberOfCities; j++){
//            cout << adjacencyMatrix[i][j] << " ";
//        }
//        cout << endl;
//    }

    return 0;
}


Coordinates::Coordinates() {
    this->index = 0;
    this->x = 0;
    this->y = 0;
    this->paiIndex = 0;
}

Coordinates::~Coordinates() = default;

Heap::Heap(std::vector<Coordinates> coordinates) {
    int sizeOfVector = (int) coordinates.size() - 1;

    for (int i = 1; i < sizeOfVector; i++){
        this->heap[i] = coordinates[i];
    }

    int halfSizeOfVector = int(coordinates.size()/2);
    for (int i = halfSizeOfVector; i > 0; i--){
        Sift(i, sizeOfVector);
    }
}

Heap::~Heap() = default;

void Heap::Sift(int i, int sizeOfVector) {
    int left = 2i;
    int right = 2i+1;
    int smaller = i;
    Coordinates aux;
    if (left <= sizeOfVector && compare(this->heap[left], this->heap[i]))
        smaller = left;
    if (right <= sizeOfVector && compare(this->heap[right], this->heap[smaller]))
        smaller = right;
    if (smaller != i) {
        aux = this->heap[i];coordinates.size();
        this->heap[i] = this->heap[smaller];
        this->heap[smaller] = aux;
        Sift(smaller, sizeOfVector);
    }
}

bool Heap::compare(Coordinates city1, Coordinates city2) {
    if (smallerDistanceToSubGraph[city1.index] < smallerDistanceToSubGraph[city2.index]){
        return true;
    }
    else if (smallerDistanceToSubGraph[city1.index] == smallerDistanceToSubGraph[city2.index]){
        if (city1.paiIndex < city2.paiIndex){
            return true;
        }
        else if (city1.paiIndex == city2.paiIndex){
            return city1.index < city2.index;
        }
    }
    else
        return false;
}