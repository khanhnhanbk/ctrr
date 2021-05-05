#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
using namespace std;
const double _oo = std::numeric_limits<double>::infinity();
struct edges
{
    int VerticeBegin;
    int VerticeEnd;
    double weight;
};
void initGraph(vector<vector<double>> &array)
{
    ifstream ifs("data.txt");
    ofstream ofs("edges.txt");
    if (ifs.is_open() && ofs.is_open())
    {
        int numberVertices;
        ifs >> numberVertices;

        array.resize(numberVertices);

        for (int i = 0; i < numberVertices; i++)
        {
            array[i].resize(numberVertices);
            for (int j = 0; j < numberVertices; j++)
            {
                ifs >> array[i][j];
                if (i != j && array[i][j] == 0)
                {
                    array[i][j] = _oo;
                }
                else if (i != j)
                {
                    ofs << i << ' ' << j << ' ' << array[i][j] << '\n';
                }
            }
        }
        ifs.close();
        ofs.close();
    }
}
void readMatrixEdges(vector<edges> &MatrixEdges)
{
    ifstream ifs("edges.txt");
    if (ifs.is_open())
    {
        while (!ifs.eof())
        {
            edges temp;
            ifs >> temp.VerticeBegin >> temp.VerticeEnd >> temp.weight;
            MatrixEdges.push_back(temp);
        }
        ifs.close();
    }
}
void printGraph(vector<vector<double>> &array)
{
    ofstream ifs("outputData.txt");
    if (ifs.is_open())
    {
        int numberVertices = array.size();
        ifs << numberVertices << '\n';

        for (int i = 0; i < numberVertices; i++)
        {
            for (int j = 0; j < numberVertices; j++)
            {
                ifs << array[i][j];
                if (j < numberVertices - 1)
                    ifs << ' ';
            }
            if (i < numberVertices - 1)
                ifs << '\n';
        }
        ifs.close();
    }
}

void dijkstra(vector<vector<double>> &array, int vertice)
{
    int numberVertices = array.size();
    vector<double> res(numberVertices + 1, _oo);
    res[vertice] = 0;
    vector<bool> isDone(numberVertices, false);
    vector<int> prev(numberVertices, -1);
    vector<char> name = {'A', 'B', 'C', 'D', 'E', 'z'};
    int count = 0;
    while (count < numberVertices)
    {
        int u = numberVertices;
        for (int i = 0; i < numberVertices; i++)
        {
            if (!isDone[i])
            {
                if (res[i] < res[u])
                {
                    u = i;
                }
            }
        }
        isDone[u] = true;
        for (int i = 0; i < numberVertices; i++)
        {
            if (!isDone[i])
            {
                if (res[u] + array[u][i] < res[i])
                {
                    res[i] = res[u] + array[u][i];
                    prev[i] = u;
                }
            }
        }
        count++;
    }
    ofstream ifs("dijkstra.txt");
    if (ifs.is_open())
    {
        ifs << numberVertices << '\n';
        for (int i = 0; i < numberVertices; i++)
        {
            ifs << res[i];
            if (i < numberVertices - 1)
            {
                ifs << ' ';
            }
        }
        ifs << '\n';
        for (int i = 0; i < numberVertices; i++)
        {
            ifs << prev[i];
            if (i < numberVertices - 1)
            {
                ifs << ' ';
            }
        }
        ifs << '\n';
        for (int i = 0; i < numberVertices; i++)
        {
            if (prev[i] == -1)
                ifs << "NULL";
            else
                ifs << name[prev[i]];
            if (i < numberVertices - 1)
            {
                ifs << ' ';
            }
        }

        ifs.close();
    }
}
void Bellman_Fold(vector<edges> &matrix, int vertice, int numberVertice)
{
    vector<double> res(numberVertice, _oo);
    res[vertice] = 0;
    vector<int> preV(numberVertice, -1);
    bool isNegative = false;
    bool isChange = true;
    int count = 0;
    while (count < numberVertice && isChange)
    {
        count++;
        isChange = false;
        for (int i = 0; i < matrix.size(); i++)
        {
            if (res[matrix[i].VerticeBegin] + matrix[i].weight < res[matrix[i].VerticeEnd])
            {
                isChange = true;
                res[matrix[i].VerticeEnd] = res[matrix[i].VerticeBegin] + matrix[i].weight;
                preV[i] = matrix[i].VerticeBegin;
            }
        }
        // for (int i = 0; i < matrix.size(); i++)
        // {
        //     if (res[matrix[i].VerticeBegin] + matrix[i].weight < res[matrix[i].VerticeEnd])
        //         isNegative = true;
        // }
    }
    //     ofstream ofs("BellmainFold.txt");
    //     if (ofs.is_open())
    //     {
    //         ofs << numberVertice;
    //         for (int i = 0; i < numberVertice; i++)
    //             ofs << res[i] << ' ';
    //         ofs.close();
    //     }
}
int main()
{
    vector<vector<double>> graph;

    initGraph(graph);

    vector<edges> matrixEdges;
    readMatrixEdges(matrixEdges);
    // printGraph(graph);

    // dijkstra(graph, 0);
    Bellman_Fold(matrixEdges, 0, 6);
    return 0;
}