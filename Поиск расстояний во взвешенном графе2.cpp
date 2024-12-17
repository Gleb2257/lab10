#include <iostream>
#include <vector>
#include <queue>
#include <climits> 
#include <cstdlib> 
#include <ctime>   
#include <windows.h> 

using namespace std;

// Функция для генерации матрицы смежности 
vector<vector<int>> generateAdjMatrixUndirected(int n, int maxWeight) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    srand(static_cast<unsigned>(time(0))); 

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
            if (val == 0) // 0 означает отсутствие ребра
                cout << ".\t";
            else
                cout << val << "\t";
        }
        cout << endl;
    }
}

// Реализация поиска кратчайших расстояний
void bfsDistances(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> distances(n, INT_MAX);
    distances[start] = 0; // Расстояние до стартовой вершины равно 0

    queue<int> q; // Очередь для хранения вершин
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        
        for (int i = 0; i < n; ++i) {
            if (graph[current][i] > 0) { // Если есть ребро
                int newDist = distances[current] + graph[current][i];
                if (newDist < distances[i]) { 
                    distances[i] = newDist;
                    q.push(i);
                }
            }
        }
    }

    // Вывод результатов
    cout << "Кратчайшие расстояния от вершины " << start << ":" << endl;
    for (int i = 0; i < n; ++i) {
        if (distances[i] == INT_MAX)
            cout << "Вершина " << i << ": недостижима" << endl;
        else
            cout << "Вершина " << i << ": " << distances[i] << endl;
    }
}

int main() {
    
    SetConsoleOutputCP(1251); 
    SetConsoleCP(1251);       

    int n, maxWeight, start;
    cout << "Введите количество вершин графа: ";
    cin >> n;
    cout << "Введите ребро: ";
    cin >> maxWeight;
    cout << "Введите начальную вершину для поиска расстояний: ";
    cin >> start;

    
    vector<vector<int>> graph = generateAdjMatrixUndirected(n, maxWeight);

    // Вывод матрицы смежности
    cout << "Матрица смежности графа:" << endl;
    printMatrix(graph);

    // Поиск кратчайших расстояний
    bfsDistances(graph, start);

    return 0;
}
