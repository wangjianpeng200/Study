//数组表示法  和  邻阶表示法
//有向图，无向图，带权
//邻接矩阵的实现
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
    this->NumEdges=this->NumVertices=0;
    this->VerticesList=new T [MaxVertices];//创建头指针指向的数据链
    assert(VerticesList!=NULL);
    this->Edge=new int* [MaxVertices];//创建边指向的权
    for(int i=0;i<this->MaxVertices;i++)
    {
        this->Edge[i]=new int [MaxVertices];//开辟权值空间
    }
    for(int i=0;i<this->MaxVertices;++i)
    {
        /*
        g->Edge[i] 是一个指向 int 类型的指针，它指向了一个动态分配的内存空间，
        这个空间可以看作是一个一维的 int 数组。
        g->Edge[i][j] 则是访问了这个一维数组中的第 j 个元素，
        即这个动态分配的内存空间中的某个 int 数据。
        */
        for(int j=0;j<MaxVertices;j++)
        {
            this->Edge[i][j]=0;//所有顶点到顶点之间的权
        }
    }
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

void GraphMtx::ShowMtx()
{
    //打印对应的顶点
    cout<<"   ";
    for(int i=0;i<this->NumVertices;i++)
    {
        cout<<"  "<<this->VerticesList[i];
    }
    cout<<endl;
    //打印边对应的矩阵
    for(int i=0;i<this->NumVertices;i++)
    {
        cout<<"  "<<this->VerticesList[i];
        for(int j=0;j<this->NumVertices;j++)
        {
            cout<<"  "<<this->Edge[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}

void GraphMtx::Insert(T v)
{
    if(this->NumVertices>=this->MaxVertices)//判断顶点数量是否超过最大数量
    {
        return;
    }
    this->VerticesList[this->NumVertices++]=v;
}

void GraphMtx::InsertEdge(T v1,T v2)//插入边，先获取图中两个顶点的位置
{
    int p1=GetVertexPos(v1);
    int p2=GetVertexPos(v2);
    if(p1==-1||p2==-1)//判断位置是否存在
    {
        return;
    }
    else{
        if(Edge[p1][p2]!=0)
        {
            return;
        }
        else{
            this->Edge[p1][p2]=this->Edge[p2][p1]=1;//1为有边2
            this->NumEdges++;
        }
    }
}

void GraphMtx::RemoveEdge(T v1,T v2)
{
    int p1=GetVertexPos(v1);
    int p2=GetVertexPos(v2);
    if(p1==-1||p2==-1)//判断位置是否存在
    {
        return;
    }
    else{
        if(Edge[p1][p2]!=1)
        {
            return;
        }
        else{
            this->Edge[p1][p2]=this->Edge[p2][p1]=0;//1为有边
            this->NumEdges--;
        }
    }
}

void GraphMtx::RemoveVertex(T v)
{
    int p=this->GetVertexPos(v);
    if(p==-1)
    {
        cout<<"不存在该位置";
        return;
    }
    int numedges=0;
    //移动顶点
    for(int i=p;i<this->NumVertices-1;i++)
    {
        this->VerticesList[i]=VerticesList[i+1];
    }
    //改变边的数量,应为是无向图，所以不需要遍历两个方向
    for(int i=0;i<this->NumVertices;i++)
    {
        if(this->Edge[p][i]!=0)
        {
            numedges++;
        }
    }
    //移动行
    for(int i=p;i<this->NumVertices-1;i++)
    {
        for(int j=0;j<NumVertices;j++)
        {
            this->Edge[i][j]=this->Edge[i+1][j];
        }
    }
    //移动列    ···············
    for(int i=p;i<this->NumVertices;i++)
    {
        for(int j=0;j<this->NumVertices;j++)
        {
            this->Edge[j][i]=this->Edge[j][i+1];
        }
    }
    delete(this->Edge[NumVertices]);
    this->NumVertices--;
    this->NumEdges-=numedges;
}

void GraphMtx::DestroyGraph()//摧毁图结构
{
    //释放顶点
    delete(this->VerticesList);
    this->VerticesList=NULL;
    //释放边
    for(int i=0;i<this->NumVertices;i++)
    {
        delete(this->Edge[i]);//释放列
    }
    delete(this->Edge);//释放行
    this->Edge=NULL;
    this->MaxVertices=this->NumEdges=this->NumVertices=0;
    cout<<"该图已摧毁-------";
}

int GraphMtx::GetFirstNeighbor(T v)//获取第一个邻阶顶点,在边的矩阵中，找列第一个不为零的
    {
        int p=this->GetVertexPos(v);
        if(p==-1)
        {
            return -1;
        }
        for(int i=0;i<this->NumVertices;i++)
        {
            
            if(this->Edge[p][i]==1)
            {
                return i;
            }
        }
        return -1;
    }

int GraphMtx::GetNextNeighbor(T v,T w)//获取邻接顶点的下一个邻接顶点
    {
        int pv=this->GetVertexPos(v);
        int pw=this->GetVertexPos(w);
        if(pv==-1||pw==-1)
        {
            return -1;
        }
        for(int i=pw+1;i<this->NumVertices;i++)
        {
            if(this->Edge[pv][i]==1)
            {
                return i;
            }
        }
        return -1;
    }

T GraphMtx::GetVertexData(int v)
{
    if(v<this->NumVertices)
    {
        return this->VerticesList[v];
    }
    return -1;
}

void GraphMtx::DFS(T vertex)//递归的算法
{
    int n=this->NumVertices;
    bool *visited=new bool[n];//是否访问过的标志位
    assert(visited!=NULL);
    //先对这个标志位进行初始化
    for(int i=0;i<n;i++)
    {
        visited[i]=false;//都还没有被访问
    }
    int v=this->GetVertexPos(vertex);//获取顶点的位置
    this->DFSTraverse(v,visited);
}

// void GraphMtx::DFSTraverse(int v,bool visited[])
// {
//     T temp_data=this->GetVertexData(v);
//     cout<<"  "<<temp_data;
//     visited[v]=true;
//     int next=this->GetFirstNeighbor(temp_data);
//     while(next!=-1)
//     {
//         if (!visited[next])
//         {
//             this->DFSTraverse(next,visited);
//         }
//         next=this->GetNextNeighbor(temp_data,this->GetVertexPos(next));     
//     }
// }

void GraphMtx::DFSTraverse(int v,bool visited[])
{
    T temp_data=this->GetVertexData(v);
    cout<<"  "<<temp_data;
    visited[v]=true;//处理标志位数组
    int w=this->GetFirstNeighbor(temp_data);//获得邻接顶点的位置，开始递归
    while ((w!=-1))//判断条件是有邻接顶点
    {
        if(!visited[w])
        {
            this->DFSTraverse(w,visited);//在这里面输出该位，并且找邻接顶点
        }
        w=this->GetNextNeighbor(temp_data,GetVertexData(w));
    }
}

// void GraphMtx::BFS(T vertex)
// {
//     int n=this->NumVertices;
//     bool *visited=new bool[n];//是否访问过的标志位
//     assert(visited!=NULL);
//     //先对这个标志位进行初始化
//     for(int i=0;i<n;i++)
//     {
//         visited[i]=false;//都还没有被访问
//     }
//     //-------------------------------------------------
//     cout<<"  "<<vertex;
//     visited[GetVertexPos(vertex)]=true;
//     int v=GetVertexPos(vertex);
//     queue<int> q;
//     q.push(GetVertexPos(vertex));
//     while(!q.empty())
//     {
//         v=q.front();
//         q.pop();
//         int w=this->GetFirstNeighbor(this->GetVertexData(v));
//         while(w!=-1)
//         {
//             if(!visited[w])//该邻接顶点未被访问
//             {
//                 cout<<" "<<this->GetVertexData(w);
//                 visited[w]=true;
//                 q.push(w);
//             }
//             w=GetNextNeighbor(this->GetVertexData(v),this->GetVertexData(w));
//         }
//     }
//     delete(visited);
// }

void GraphMtx::DFS_onconnect()//非联通图的深度优先遍历
{
    int n=this->NumVertices;
    bool *visited=new bool[n];//是否访问过的标志位
    assert(visited!=NULL);
    //先对这个标志位进行初始化
    for(int i=0;i<n;i++)
    {
        visited[i]=false;//都还没有被访问
    }

    //开始遍历
    for(int i=0;i<this->NumVertices;i++)
    {
        if(!visited[i])
        {
            this->DFSTraverse(i,visited);
        }
    }
    delete(visited);
}

void GraphMtx::BFS(T vertex)
{
    //创建一组标志位，并初始化
    bool* visited=new bool [this->NumVertices];
    for(int i=0;i<this->NumVertices;i++)
    {
        visited[i]=false;
    }

    //输出第一个顶点
    cout<<"  "<<vertex;
    visited[this->GetVertexPos(vertex)]=true;

    //初始化一个队列并放入顶点
    queue<int> qu;
    qu.push(this->GetVertexPos(vertex));

    //开始层次遍历每一个顶点
    while(!qu.empty())//这个循环是为了切换层次
    {
        int v=qu.front();//获取队列的第一个顶点(相当于将要遍历层次的父节点)
        qu.pop();//删除队列的第一个元素
        int next=this->GetFirstNeighbor(this->GetVertexData(v));//获取第一个邻接顶点

        //开始遍历该顶点下的邻接顶点
        while(next!=-1)////这一个循环是为了遍历一个顶点下邻接的顶点
        {
            if(!visited[next])
            {
                cout<<"  "<<this->GetVertexData(next);
                visited[next]=true;
                //将他的邻接点入队列，作为以后的遍历层次父节点
                qu.push(next);
            }
            next=this->GetNextNeighbor(GetVertexData(v),GetVertexData(next));//遍历该层次
        }
    }
    delete(visited);
}

void test()
{
    GraphMtx graph;
    graph.InitGraph();
    graph.Insert('A');
    graph.Insert('B');
    graph.Insert('C');
    graph.Insert('D');
    graph.Insert('E');
    graph.InsertEdge('A','B');
    graph.InsertEdge('B','C');
    graph.InsertEdge('D','E');
    graph.ShowMtx();
    // graph.RemoveEdge('A','B');
    // graph.ShowMtx();
    // graph.RemoveVertex('B');
    // graph.ShowMtx();
    // graph.DestroyGraph();
    // graph.ShowMtx();
    int p=graph.GetNextNeighbor('B','A');
    cout<<"   "<<p;
}

void test_DFS()//深度优先遍历
{
    GraphMtx graph;
    graph.InitGraph();
    graph.Insert('A');
    graph.Insert('B');
    graph.Insert('C');
    graph.Insert('D');
    graph.Insert('E');
    graph.Insert('F');
    graph.Insert('G');
    graph.Insert('H');
    graph.InsertEdge('A','B');
    graph.InsertEdge('B','D');
    graph.InsertEdge('B','E');
    graph.InsertEdge('E','H');
    graph.InsertEdge('D','H');
    graph.InsertEdge('A','C');
    graph.InsertEdge('C','F');
    graph.InsertEdge('C','G');
    graph.ShowMtx();
    graph.DFS('B');
}

void test_BFS()//广度优先遍历
{
    GraphMtx graph;
    graph.InitGraph();
    graph.Insert('A');
    graph.Insert('B');
    graph.Insert('C');
    graph.Insert('D');
    graph.Insert('E');
    graph.Insert('F');
    graph.Insert('G');
    graph.Insert('H');
    graph.InsertEdge('A','B');
    graph.InsertEdge('B','D');
    graph.InsertEdge('B','E');
    graph.InsertEdge('E','H');
    graph.InsertEdge('D','H');
    graph.InsertEdge('A','C');
    graph.InsertEdge('C','F');
    graph.InsertEdge('C','G');
    graph.InsertEdge('G','F');
    graph.ShowMtx();
    graph.BFS('A');
}

void test_unconnect()//非联通图的遍历
{
    GraphMtx graph;
    graph.InitGraph();
    graph.Insert('A');
    graph.Insert('B');
    graph.Insert('C');
    graph.Insert('D');
    graph.Insert('E');
    graph.Insert('F');
    graph.Insert('G');
    graph.Insert('H');
    graph.Insert('I');
    graph.Insert('J');
    graph.Insert('K');
    graph.Insert('L');
    graph.Insert('M');
    graph.InsertEdge('A','B');
    graph.InsertEdge('A','L');
    graph.InsertEdge('B','M');
    graph.InsertEdge('M','L');
    graph.InsertEdge('A','C');
    graph.InsertEdge('A','F');
    graph.InsertEdge('D','E');
    graph.InsertEdge('G','H');
    graph.InsertEdge('G','I');
    graph.InsertEdge('G','K');
    graph.InsertEdge('G','I');
    graph.InsertEdge('H','K');
    graph.InsertEdge('J','L');
    graph.InsertEdge('J','M');
    graph.ShowMtx();
    graph.DFS('A');
    cout<<endl;
    graph.DFS_onconnect();
}

int main()
{
    test_unconnect();
    return 0;
}