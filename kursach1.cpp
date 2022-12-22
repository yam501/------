#include <iostream>
#include <stack> // стек
#include <vector>
#define INF 5000

using namespace std;

// Количество вершин
const int n = 6;

// Граф через матрицу смежности
int graph[n][n] = {
    {0, 10, 1, 5, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {1, 0, 0, 3, 2, 4},
    {5, 0, 3, 0, 0, 1},
    {0, 0, 2, 0, 0, 1},
    {0, 0, 4, 1, 1, 0}};

// Поиск в глубину - DFS
bool *visited = new bool[n]; // динамически массив посещенных

//
void DFS(int st)
{
    int i;
    cout << st + 1 << " ";
    visited[st] = true;
    for (i = 0; i < n; i++)
    {
        if ((graph[st][i] != 0) && (!visited[i]))
            DFS(i);
    }
    for (i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            DFS(i);
        }
    }
}

// Метод для обозначения непосещенной вершины
void visitedFalse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        visited[i] = false;
    }
}

// Методы для вывода графов
void printGraph()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%4d", graph[i][j]);
        }
        cout << endl;
    }
}
void printMatrix(int matrix[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            if (matrix[i][j] == INF)
                printf("%4s", "INF");
            else
                printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

// FW
int Next[n][n];
int floydGraph[n][n];
void toFloyd();
void floydWarshall();

void toFloyd()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                floydGraph[i][i] = 0;
            }

            else if (graph[i][j] == 0)
            {
                floydGraph[i][j] = INF;
                Next[i][j] = -1;
            }

            else
            {
                floydGraph[i][j] = graph[i][j];
                Next[i][j] = j;
            }
        }
    }
}

void floydWarshall()
{
    int matrix[n][n], i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            matrix[i][j] = floydGraph[i][j];
        }
    }

    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j])
                {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    Next[i][j] = Next[i][k];
                }
            }
        }
    }
    printMatrix(matrix);
    cout << endl;
}

vector<int> Path(int u, int v)
{
    if (Next[u][v] == -1)
        return {};
    vector<int> path = {u};
    while (u != v)
    {
        u = Next[u][v];
        path.push_back(u);
    }
    return path;
}

void printPath()
{
    vector<int> spath;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << "|" << i + 1 << " -> " << j + 1 << " : ";
            spath = Path(i, j);
            for (int i : spath)
            {
                cout << i + 1 << " ";
            }
            cout << endl;
        }
        cout << "|--------------------|" << endl;
    }
}

// FW max cycle
int floydGraphCycle[n][n];
vector<int> tempPath, path;
int maxcycle = 0;
void toFloydCycle();
void floydWarshallCycle();

void toFloydCycle()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] == 0)
                floydGraphCycle[i][j] = INF;
            else
                floydGraphCycle[i][j] = graph[i][j];
        }
    }
}

void floydWarshallCycle()
{
    int matrix[n][n], i, j, k;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            matrix[i][j] = floydGraphCycle[i][j];
    for (k = 0; k < n; k++)
    {

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j] && matrix[i][j] > maxcycle)
                {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    if (i == j)
                    {
                        tempPath.push_back(i + 1);
                        tempPath.push_back(k + 1);
                        tempPath.push_back(j + 1);
                        if (matrix[i][j] > maxcycle)
                        {
                            path = tempPath;
                            maxcycle = matrix[i][j];
                        }
                    }
                    tempPath.clear();
                }
            }
        }
    }
    printMatrix(matrix);
    cout << "Max cycle length: " << maxcycle << endl;
    cout << "Path: ";
    for (auto i : path)
    {
        cout << i << " ";
    }
    cout << endl;
}
int parent[n];

// Find set of vertex i
int find(int i)
{
    while (parent[i] != i)
        i = parent[i];
    return i;
}

// Does union of i and j. It returns
// false if i and j are already in same
// set.
void union1(int i, int j)
{
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

// Finds MST using Kruskal's algorithm
void kruskalMST()
{
    int mincost = 0; // Cost of min MST.

    // Initialize sets of disjoint sets.
    for (int i = 0; i < n; i++)
        parent[i] = i;

    // Include minimum weight edges one by one
    int edge_count = 0;
    while (edge_count < n - 1)
    {
        int min = INF, a = -1, b = -1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (find(i) != find(j) && floydGraph[i][j] < min)
                {
                    min = floydGraph[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        union1(a, b);
        cout << "Edge "<< edge_count+++1 <<" (" <<a+1 << ","<<b+1<<")"<<" cost: "<<min<< endl;
        mincost += min;
    }
    cout << "Minimum cost: " <<  mincost << endl;
}
int main()
{

    int i, j, start;

    visitedFalse();

    int selection = 1, command = 0;
    while (selection == 1)
    {
        cout << "Select:\n1 - Print graph\n2 - Max cycle\n3 - DFS\n4 - FW\n5 - Kruskala " << endl;

        cin >> command;

        switch (command)
        {
        case 1:
            printGraph();
            break;
        case 2:
            cout << "Matrix: " << endl;
            toFloydCycle();
            floydWarshallCycle();
            break;
        case 3:
            cout << "Start point: >> ";
            cin >> start;
            cout << "DFS " << start << ": ";
            DFS(start - 1);
            cout << endl;
            visitedFalse();
            break;
        case 4:
            toFloyd();
            floydWarshall();
            printPath();
            break;
            break;
        case 5:
            toFloyd();
            kruskalMST();
            break;
        }

        cout << "1 - continue" << endl;
        cin >> selection;
        cout << "---------------------" << endl;
    }

    delete[] visited;

    return 0;
}