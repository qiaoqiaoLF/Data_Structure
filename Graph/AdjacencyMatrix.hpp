#ifndef ADJLIST
#define ADJLIST
template <class TypeOfVer, class TypeOfEdge>
class adjMatrixGraph
{
public:
    adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag);
    void insert(TypeOfVer v1, TypeOfVer v2, TypeOfEdge weight);
    void remove(TypeOfVer v1, TypeOfVer v2);
    bool exist(TypeOfVer v1, TypeOfVer v2) const;
    ~adjMatrixGraph();
    int numOfVer() const { return Vers; }
    int numOfEdge() const { return Edges; }

private:
    TypeOfEdge **edge;
    TypeOfVer *Ver;
    TypeOfEdge noEdge;
    int Vers;
    int Edges;
    int find(TypeOfVer v) const
    {
        for (int i = 0; i < Vers; ++i)
            if (Ver[i] == v)
                return i;
        return -1;
    }
};

template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag)
{
    Vers = vSize;
    Edges = 0;
    Ver = new TypeOfVer[Vers];
    edge = new TypeOfEdge *[Vers];
    noEdge = noEdgeFlag;
    for (int i = 0; i < Vers; ++i)
    {
        Ver[i] = d[i];
        edge[i] = new TypeOfEdge[Vers];
        for (int j = 0; j < Vers; ++j)
            edge[i][j] = noEdge;
    }
}
template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::~adjMatrixGraph()
{
    for (int i = 0; i < Vers; ++i)
        delete[] edge[i];
    delete[] edge;
    delete[] Ver;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer v1, TypeOfVer v2, TypeOfEdge weight)
{
    int i = find(v1);
    int j = find(v2);
    if (i == -1 || j == -1)
        throw 1;
    if (edge[i][j] != noEdge)
        throw 2;
    edge[i][j] = weight;
    Edges++;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer v1, TypeOfVer v2)
{
    int i = find(v1);
    int j = find(v2);
    if (i == -1 || j == -1)
        throw 1;
    if (edge[i][j] == noEdge)
        throw 2;
    edge[i][j] = noEdge;
    Edges--;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer v1, TypeOfVer v2) const
{
    int i = find(v1);
    int j = find(v2);
    if (i == -1 || j == -1)
        throw 1;
    if (edge[i][j] == noEdge)
        return false;
    return true;
}
#endif