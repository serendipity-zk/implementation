#include<vector>
template<typename cost_t>
class AdjacentList
{


    public:
    struct Edge;
    friend Edge;
    struct Edge
    {
    public:
        size_t u;
        size_t v;
        cost_t cost;
        size_t next;
        bool isEmpty(){return u==0||v==0;};
        operator bool()
        {
            return !isEmpty();
        }
        Edge operator++ (int)
        {
            *this=this->list->nextEdge(*this);
            return *this;
        }
        Edge(size_t start, size_t end,cost_t cost1, size_t next1,AdjacentList* list1 ):u(start),v(end),cost(cost1),next(next1),list(list1){};
    private:
        AdjacentList* list;
    };
    private:
    size_t m_numEdge;
    size_t m_numVertex;
    std::vector<size_t> m_head;
    std::vector<Edge> m_edge;
    Edge nextEdge(const Edge& prevEdge)
    {
        if(prevEdge.next>0) return m_edge[prevEdge.next];
        return {0,0,cost_t(),0,this};
    }
    public:
    
    explicit AdjacentList(size_t numVertex)
        :m_numEdge(0), m_numVertex(numVertex), m_edge(1, {0,0,cost_t(),0,this}), m_head(numVertex + 1, 0)
    {}
    AdjacentList(size_t numVertex,size_t numEdge)
    :m_numEdge(0),m_numVertex(numVertex),m_edge(),m_head(numVertex+1,-1)
    {
        m_edge.reserve(numEdge);
    }
    void add (size_t u, size_t v, cost_t cost)
    {
        m_edge.push_back(Edge{u,v,cost,m_head[u],this});
        m_head[u]=m_edge.size()-1;
    }
    Edge firstEdge(size_t vertexIndex)
    {
        return m_edge [m_head[vertexIndex]];
    }

};