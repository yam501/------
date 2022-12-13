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

// DFS
bool *visited = new bool[n];   //динамически массив посещенных


void visitedFalse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        visited[i] = false;
    }
}

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


int main(){
 
    int i, j, start;

    visitedFalse();

    int selection = 1, command = 0;
    while (selection == 1)
    {
        cout << "Select:\n1 - Print graph\n2 - Max cycle\n3 - DFS" << endl;


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

        }

        cout << "1 - continue" << endl;
        cin >> selection;
        cout << "---------------------" << endl;

    }

    delete[] visited;

    return 0;
}