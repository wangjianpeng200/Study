#include<iostream>
#include<string>
#include<cassert>
using namespace std;
using T=char;
#define Default_Vertices_Size 10

//边的结构体
class Edge
{
    public:
    int dest;
    Edge* link;
};
//顶点的结构体
class Vertex
{
    public:
    T data;
    Edge* adj;
};
//顶点数组的头节点

class GraphLnk
{
    private:
    Vertex* NodeTable;
    int MaxVertices=Default_Vertices_Size;
    int NumVertices;//当前顶点的数量
    int NumEdges;//边的数量
    public:
    void InitGraph();//初始化
    int GetVertexPos(T v);//获取顶点的位置，（在数组中的下标）
    void ShowMtx();//显示
    void Insert(T v);//插入顶点
    void InsertEdge(T v1,T v2);//在哪两个顶点之间插入边
    void RemoveVertex(T v);//删除顶点,在删除顶点时还要删除相关联的边
    void RemoveEdge(T v1,T v2);//删除边
    void DestroyGraph();//摧毁图结构
    int GetFirstNeighbor(T v);//获取顶点
    int GetNextNeighbor(T v,T w);//
};

void GraphLnk::InitGraph()
{
    this->NumEdges=NumVertices=0;
    this->NodeTable=new Vertex [MaxVertices];//创建存放顶点的数组空间
    assert(NodeTable!=NULL);
    for(int i=0;i<this->MaxVertices;i++)
    {
        this->NodeTable[i].adj=NULL;//将每一个顶点的指针初始化
    }
}

int GraphLnk::GetVertexPos(T v)//返回位置
{
    if(NumVertices==0)
    {
        cout<<"邻接表为空";
        return -1;
    }
    for(int i=0;i<NumVertices;i++)
    {
        if(this->NodeTable[i].data==v)
        {
            return i;
        }
        
    }
    return -1;
}


void GraphLnk::ShowMtx()//显示
{
    Edge* temp_edge;
    temp_edge=NULL;
    for(int i=0;i<this->NumVertices;i++)
    {
        cout<<" "<<this->NodeTable[i].data<<endl;
        temp_edge=NodeTable[i].adj;
        while(temp_edge!=NULL)
        {
            cout<<"  "<<temp_edge->dest;
            temp_edge=temp_edge->link;
        }
    }
}

void GraphLnk::Insert(T v)//插入顶点
{
    if(this->NumVertices>=MaxVertices)
    {
        cout<<"该邻接表已满";
        return;
    }
    this->NodeTable[NumVertices].data=v;
    NumVertices++;
}

void GraphLnk::InsertEdge(T v1,T v2)//在哪两个顶点之间插入边，且无向图需要插入两次
{
    int p1=this->GetVertexPos(v1);
    int p2=this->GetVertexPos(v2);
    if(v1==-1||v2==-1)
    {
        return;
    }
    //v1-->V2,头插
    Edge* temp1=new(Edge);
    assert(temp1!=NULL);
    temp1->dest=p2;
    temp1->link=this->NodeTable[v1].adj;
    this->NodeTable[v1].adj=temp1;
    // v2-->v1
    Edge* temp2=new(Edge); 
    assert(temp2!=NULL);
    temp2->dest=p1;
    temp2->link=this->NodeTable[v2].adj;
    this->NodeTable[v2].adj=temp2;
    this->NumEdges++;
}

void test01()
{
    GraphLnk g1;
    g1.InitGraph();
    g1.Insert('A');
    g1.Insert('B');
    g1.Insert('C');
    g1.Insert('D');
    g1.Insert('E');
    int i=g1.GetVertexPos('B');
    g1.InsertEdge('A','B');
    g1.InsertEdge('B','C');
    cout<<i<<endl;
    g1.ShowMtx();
}

int main()
{
    test01();
    return 0;
}