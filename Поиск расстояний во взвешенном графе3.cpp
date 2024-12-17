#include <iostream>
#include <vector>
#include <queue>
#include <climits> 
#include <cstdlib> 
#include <ctime>   
#include <windows.h> 

using namespace std;

// Генерация  матрицы смежности для ориентированного графа
vector<vector<int>> generateAdjMatrixDirected(int n, int maxWeight) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    srand(static_cast<unsigned>(time(0))); // Инициализация генератора случайных чисел

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) { 
                int weight = rand() % (maxWeight + 1);
                if (weight > 0) {
                    matrix[i][j] = weight;
                }
            }
        }
    }
    return matrix;
}

// Функция для генерации  матрицы смежности 
vector<vector<int>> generateAdjMatrixUndirected(int n, int maxWeight) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    srand(static_cast<unsigned>(time(0))); // Инициализация генератора случайных чисел

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int weight = rand() % (maxWeight + 1);
            if (weight > 0) { 
                matrix[i][j] = weight;
                matrix[j][i] = weight; // Симметрия для неориентированного графа
            }
        }
    }

    return matrix;
}

// Функция для вывода матрицы смежности
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            if (val == 0)
                cout << ".\t";
            else
                cout << val << "\t";
        }
        cout << endl;
    }
}

// Алгоритм Флойда-Уоршелла для поиска кратчайших расстояний между всеми парами вершин
vector<vector<int>> floydWarshall(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> dist = graph;

   
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && dist[i][j] == 0) {
                dist[i][j] = INT_MAX;
            }
        }
    }

    // Основной цикл алгоритма
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    return dist;
}

// Вычисление радиуса и диаметра графа
void calculateRadiusAndDiameter(const vector<vector<int>>& dist) {
    int n = dist.size();
    vector<int> eccentricities(n, 0); 

    // Вычисляем эксцентриситет каждой вершины
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] != INT_MAX) {
                eccentricities[i] = max(eccentricities[i], dist[i][j]);
            }
        }
    }

    // Радиус — минимальный эксцентриситет, диаметр — максимальный
    int radius = INT_MAX;
    int diameter = 0;

    for (int ecc : eccentricities) {
        radius = min(radius, ecc);
        diameter = max(diameter, ecc);
    }

    cout << "Радиус графа: " << radius << endl;
    cout << "Диаметр графа: " << diameter << endl;
}

int main() {
    
    SetConsoleOutputCP(1251); 
    SetConsoleCP(1251);      

    int n, maxWeight;
    cout << "Введите количество вершин графа: ";
    cin >> n;
    cout << "Введите ребро: ";
    cin >> maxWeight;

    // Генерация и обработка неориентированного графа
    cout << "\nНеориентированный граф:" << endl;
    vector<vector<int>> undirectedGraph = generateAdjMatrixUndirected(n, maxWeight);
    printMatrix(undirectedGraph);

    vector<vector<int>> undirectedDist = floydWarshall(undirectedGraph);
    cout << "\nМатрица кратчайших расстояний для неориентированного графа:" << endl;
    printMatrix(undirectedDist);
    calculateRadiusAndDiameter(undirectedDist);

    // Генерация и обработка ориентированного графа
    cout << "\nОриентированный граф:" << endl;
    vector<vector<int>> directedGraph = generateAdjMatrixDirected(n, maxWeight);
    printMatrix(directedGraph);

    vector<vector<int>> directedDist = floydWarshall(directedGraph);
    cout << "\nМатрица кратчайших расстояний для ориентированного графа:" << endl;
    printMatrix(directedDist);
    calculateRadiusAndDiameter(directedDist);

    return 0;
}
