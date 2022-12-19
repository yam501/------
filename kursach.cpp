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
bool *visited = new bool[n];   //динамически массив посещенных


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

int main(){
 
    int i, j, start;

    visitedFalse();

    int selection = 1, command = 0;
    while (selection == 1)
    {
        cout << "Select:\n1 - Print graph\n2 - Max cycle\n3 - DFS\n4 - FW " << endl;


        cin >> command;

        switch (command)
        {
        case 1:
            printGraph();
            break;
        case 2:
            
            visitedFalse();
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
        }

        cout << "1 - continue" << endl;
        cin >> selection;
        cout << "---------------------" << endl;

    }

    delete[] visited;

    return 0;
}