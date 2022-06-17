#ifndef ADJLIST
#define ADJLIST
#include "seqQueue.hpp"
#include "seqStack.hpp"

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph
{
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    void insert(TypeOfVer v1, TypeOfVer v2, TypeOfEdge weight);
    void remove(TypeOfVer v1, TypeOfVer v2);
    bool exist(TypeOfVer v1, TypeOfVer v2) const;
    ~adjListGraph();
    int numOfVer() const { return Vers; }
    int numOfEdge() const { return Edges; }
    void dfs() const;
    void bfs() const;
    void EulerCircuit(TypeOfVer start) const;
    void topSort() const;
    void criticalPath() const;

private:
    int Vers;
    int Edges;
    struct edgeNode
    {
        int end;
        TypeOfEdge weight;
        edgeNode *next;
        edgeNode(int e, TypeOfEdge w, edgeNode *n = nullptr)
        {
            end = e;
            weight = w;
            next = n;
        }
    };
    struct verNode
    {
        TypeOfVer ver;
        edgeNode *head;
        verNode(edgeNode *n = nullptr)
        {
            head = n;
        }
    };
    struct EulerNode
    {
        int NodeNum;
        EulerNode *next;
        EulerNode(int n, EulerNode *nxt = nullptr)
        {
            NodeNum = n;
            next = nxt;
        }
    };
    verNode *Verlist;
    int find(TypeOfVer v) const
    {
        for (int i = 0; i < Vers; ++i)
        {
            if (Verlist[i].ver == v)
                return i;
        }
        return -1;
    }
    void dfs(int start, bool visited[]) const;
    verNode *clone() const;
    void EulerCircuit(int start, EulerNode *&begin, EulerNode *&end);
};

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[])
{
    Vers = vSize;
    Edges = 0;
    Verlist = new verNode[Vers];
    for (int i = 0; i < Vers; ++i)
    {
        Verlist[i].ver = d[i];
        Verlist[i].head = nullptr;
    }
}
template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
    edgeNode *p;
    for (int i = 0; i < Vers; ++i)
        while (!(p = Verlist[i]))
        {
            Verlist[i].head = p->next;
            delete p;
        }
    delete[] Verlist;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer v1, TypeOfVer v2, TypeOfEdge weight)
{
    int i = find(v1), j = find(v2);
    Verlist[i].head = new edgeNode(j, weight, Verlist[i].head);
    ++Edges;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer v1, TypeOfVer v2)
{
    int i = find(v1), j = find(v2);
    edgeNode *p = Verlist[i].head, *q;
    if (!p)
        return;
    if (p->end == v2)
    {
        Verlist[i].head = p->next;
        delete p;
        Edges--;
        return;
    }
    while (p->next != nullptr && p->next->end != j)
        p = p->next;
    if (p->next != nullptr)
    {
        q = p->next;
        p->next = q->next;
        delete q;
        --Edges;
    }
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer v1, TypeOfVer v2) const
{
    int i = find(v1), j = find(v2);
    edgeNode *p = Verlist[i].head;
    while (p != nullptr && p->end != j)
        p = p->next;
    if (p)
        return true;
    return false;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const
{
    bool *visited = new bool[Vers];
    for (auto _ : visited)
        _ = false;
    for (int i = 0; i < Vers; ++i)
    {
        if (visited[i] = true)
            continue;
        dfs(i, visited);
        std::cout << std::endl;
    }
}
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const
{
    edgeNode *p = Verlist[start].head;
    std::cout << Verlist[start].ver << ' ';
    visited[start] = true;
    while (!p)
    {
        if (!visited[p->end])
            def(p->end, visited);
        p = p->next;
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const
{
    int currentNode;
    edgeNode *p;
    bool *visited = new bool[Vers];
    for (auto _ : visited)
        _ = false;
    seqQueue<int> que;
    for (int i < 0; i < Vers; ++i)
    {
        if (visited[i] == true)
            continue;
        que.enQueue(i);
        while (!que.isEmpty())
        {
            currentNode = que.deQueue();
            if (visited[currentNode] == true)
                continue;
            std::cout << Verlist[currentNode].ver << ' ';
            visited[currentNode] = true;
            p = Verlist[currentNode].head;
            while (!p)
            {
                que.enQueue(p->end);
                p = p->next;
            }
        }
        std::cout << std::endl;
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(TypeOfVer start) const
{
    EulerNode *begin, *end, *p, *q, *tb, *te;
    int numOfDegree;
    edgeNode *r;
    verNode *tmp;
    // check whether there exists a Euler circuit
    if (Edges == 0)
        std::cout << "There is no Euler circuit" << std::endl;
    for (int i = 0; i < Vers; ++i)
    {
        numOfDegree = 0;
        r = Verlist[i].head;
        while (r)
        {
            ++numOfDegree;
            r = r->next;
        }
        if (numOfDegree % 2 == 1)
        {
            std::cout << "There is no Euler circuit" << std::endl;
            return;
        }
    }
    // find the first node
    int i = find(start);
    tmp = clone();

    // find a path starting from i, and store it in begin and end
    EulerCircuit(i, begin, end);
    while (true)
    {
        p = begin;
        while (p->next != nullptr)
            if (Verlist[p->next->end].head != nullptr)
                break;
            else
                p = p->next;
        if (p->next == nullptr)
            break;
        q = p->next;
        EulerCircuit(q->NodeNum, tb, te);
        te->next = q->next;
        p->next = tb;
        delete q;
    }
    // rebuild the graph
    delete[] Verlist;
    Verlist = tmp;

    // print the Euler circuit
    while (begin != nullptr)
    {
        std::cout << Verlist[begin->NodeNum].ver << ' ';
        p = begin;
        begin = begin->next;
        delete p;
    }
    std::cout << std::endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(int start, EulerNode *&begin, EulerNode *&end)
{
    int nextNode;
    begin = end = new EulerNode(start);
    while (Verlist[start].head != nullptr)
    {
        nextNode = verlist[start].head->end;
        remove(start, nextNode);
        remove(nextNode, start);
        start = nextNode;
        end->next = new EulerNode(start);
        end = end->next;
    }
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::verNode *adjListGraph<TypeOfVer, TypeOfEdge>::clone() const
{
    verNode *tmp = new verNode[Vers];
    edgeNode *p;
    for (int i = 0; i < Vers; ++i)
    {
        tmp[i].ver = Verlist[i].ver;
        p = Verlist[i].head;
        while (p)
        {
            tmp[i].head = new edgeNode(p->end, p->weight, tmp[i].head);
            p = p->next;
        }
    }
}
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topSort() const
{
    seqQueue<int> que;
    edgeNode *p;
    int current;
    int *inDegree = new int[Vers];

    for (int i = 0; i < Vers; ++i)
        inDegree[i] = 0;
    for (int i = 0; i < Vers; ++i)
    {
        p = Verlist[i].head;
        while (p)
        {
            ++inDegree[p->end];
            p = p->next;
        }
    }
    for (int i = 0; i < Vers; ++i)
    {
        if (inDegree[i] == 0)
            que.enQueue(i);
    }
    while (!que.isEmpty())
    {
        current = que.deQueue();
        std::cout << Verlist[current].ver << ' ';
        p = Verlist[current].head;
        while (p)
        {
            --inDegree[p->end];
            if (inDegree[p->end] == 0)
                que.enQueue(p->end);
            p = p->next;
        }
    }
    std::cout << std::endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::criticalPath() const
{
    TypeOfEdge *EE = new TypeOfEdge[Vers], *le = new TypeOfEdge[Vers];
    int *top = new int[Vers], *inDegree = new int[Vers];
    seqQueue<int> que;
    int i;
    edgeNode *p;

    for (int i = 0; i < Vers; ++i)
        inDegree[i] = 0;
    for (int i = 0; i < Vers; ++i)
    {
        p = Verlist[i].head;
        while (p)
        {
            ++inDegree[p->end];
            p = p->next;
        }
    }
    for (int i = 0; i < Vers; ++i)
    {
        if (inDegree[i] == 0)
            que.enQueue(i);
    }
    i = 0;
    while (!que.isEmpty())
    {
        top[i] = que.deQueue();
        p = Verlist[top[i]].head;
        while (p)
        {
            --inDegree[p->end];
            if (inDegree[p->end] == 0)
                que.enQueue(p->end);
            p = p->next;
        }
        ++i;
    }
    // find the ealiest time
    for (int i = 0; i < Vers; ++i)
        ee[i] = 0;
    for (int i = 0; i < Vers; i++)
    {
        p = Verlist[top[i]].head;
        while (p)
        {
            if (ee[p->end] < ee[top[i]] + p->weight)
                ee[p->end] = ee[top[i]] + p->weight;
            p = p->next;
        }
    }

    // find the latest time
    for (int i = 0; i < Vers; ++i)
        le[i] = ee[top[Vers - 1]];

    for (int i = Vers - 1; i >= 0; --i)
    {
        p = Verlist[top[i]].head;
        while (p)
        {
            if (le[p->end] - p->weight < le[top[i]])
                le[top[i]] = le[p->end] - p->weight;
            p = p->next;
        }
    }

    // find the critical path
    for (int i = 0; i < Vers; ++i)
        if (le[top[i]] == ee[top[i]])
            std::cout << '(' << Verlist[top[i]].ver << ' , ' << ee[top[i]] << ')' << ' ';
}

#endif