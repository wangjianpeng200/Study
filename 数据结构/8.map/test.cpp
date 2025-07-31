#include<iostream>
#include<string>
#include<cassert>
#include<queue>
using namespace std;

#define Default_Vertices_Size 10
using T=char;

class GraphMtx//
{
    private:
    int MaxVertices;//最大顶点容量
    int NumVertices;//当前顶点的数量
    int NumEdges;//边的数量
    T *VerticesList;//存储的数据，顶点的列表指针
    int **Edge;//边的信息,是一个动态的二维数组的开辟
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
    int GetNextNeighbor(T v,T w);//获取邻接顶点的顶点
    T GetVertexData(int v);//获取该位置的的data
    void DFS(T v);//深度优先遍历算法，从哪一个顶点开始访问
    void DFSTraverse(int v,bool visited[]);//深度优先操作，传入顶点位置和标志位数组
    //传入数组实际上是传入数组的首地址
    void BFS(T vertex);//广度优先遍历
    void DFS_onconnect();
};

void GraphMtx::InitGraph()
{
    this->MaxVertices=Default_Vertices_Size;
    this->VerticesList=new T[MaxVertices];
    assert(VerticesList!=NULL);
    this->Edge=new T*[MaxVertices];
    assert(this->Edge!=NULL);
    for(int i=0;i<this->MaxVertices;i++)
    {
        this->Edge[i]=new T[this->MaxVertices];
        assert(Edge[1]!=NULL);
    }
    for(int i=0;1<this->MaxVertices;i++)
    {
        for(int j=0;j<this->MaxVertices;j++)
        {
            Edge[i][j]=0;
        }
    }
    this->NumEdges=0;
    this->NumVertices=0;
}

int GraphMtx::GetVertexPos(T v)
{
    for(int i=0;i<this->NumVertices;i++)
    {
        if(this->VerticesList[i]==v)
        {
            return i;
        }
    }
    return -1;//用于判断其是否合法
}

void GraphMtx::RemoveVertex(T vertex)
{
    int flag=this->GetVertexPos(vertex);
    if(flag==-1)
    {
        cout<<"不纯在该点"<<endl;
    }
    int num_edge=0;
    for(int i=0;i<this-NumEdges;i++)
    {
        if(this->Edge[GetVertexPos(vertex)][i]!=0)
        {
            num_edge++;
        }
    }
    for(int i=flag;i<this->NumVertices-1;i++)
    {
        vertex[i]=vertex[i+1];
    }
    for(int i=flag;i<this->NumVertices-1;i++)
    {
        for(int j=0;j<this->NumVertices,j++)
        {
            this->Edge[i][j]=this->Edge[i+1][j];
        }
    }
    for(int i=flag;i<this->NumVertices;i++)
    {
        for(int j=0;j<this->NumVertices,j++)
        {
            this->Edge[j][i]=this->Edge[j][i+1];
        }
    }
}   