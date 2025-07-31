/*
Prim算法是另一种用于求解最小生成树（Minimum Spanning Tree，MST）的贪婪算法。
与Kruskal算法不同，Prim算法是基于顶点展开的，而不是基于边。

Prim算法的基本思想是从一个初始顶点开始，逐步扩展生成树，
每次选择与当前生成树连接的顶点中距离最短的顶点，直到生成树覆盖了图中所有的顶点为止。

Prim算法的具体步骤如下：

1.选择一个初始顶点作为生成树的根节点，并将其加入生成树中。
2.从生成树中的顶点集合中选择一个顶点，该顶点到未加入生成树的顶点的边权重最小，
将该顶点加入生成树中。
3.重复步骤2，直到生成树包含了图中所有的顶点。


与Kruskal算法相比，Prim算法更加适合稠密图（边的数量接近于顶点数量的图），
因为它的时间复杂度与顶点数量相关，为 O(V^2)，其中 V 是图中顶点的数量。
但是，使用适合的数据结构（如优先队列）可以将Prim算法的时间复杂度优化到 O(ElogV)。

下面是Prim算法的伪代码：

Prim(Graph G):
1. 选择一个初始顶点作为生成树的根节点，并将其加入生成树中
2. 初始化一个空的集合M，用于存放已经加入生成树的顶点
3. 初始化一个优先队列Q，用于存放连接M中顶点和未加入生成树的顶点的边，按照边权重排序
4. 当生成树中的顶点数量小于图中的顶点数量时：
     从优先队列Q中取出权重最小的边e，如果e连接的顶点v不在M中：
         将顶点v加入到M中
         将边e加入到最小生成树中
         将与顶点v相连的边加入到优先队列Q中
5. 返回最小生成树

Prim算法通常比Kruskal算法更容易实现，并且对于稠密图有更好的性能。
*/

#include <iostream>
#include <string>
#include <queue>
#include <cassert>

using namespace std;

#define Max_Cost 0x7FFFFFFF // 在计算机中表示最大整数，在初始化时使用
#define Default_Vertices_Size 10
using T = char; // 图中存入的顶点
// 权值的类

struct Edge_kruskal
{
    int start;
    int end;
    int cost;
};

class GraphMtx //
{
private:
    int MaxVertices; // 最大顶点容量
    int NumVertices; // 当前顶点的数量
    int NumEdges;    // 边的数量
    T *VerticesList; // 存储的数据，顶点的列表指针
    int **Edge;      // 边的信息,是一个动态的二维数组的开辟
public:
    void InitGraph();                        // 初始化
    int GetVertexPos(T v);                   // 获取顶点的位置，（在数组中的下标）
    void ShowMtx();                          // 显示
    void Insert(T v);                        // 插入顶点
    void InsertEdge(T v1, T v2, int cost);   // 在哪两个顶点之间插入边
    void RemoveVertex(T v);                  // 删除顶点,在删除顶点时还要删除相关联的边
    void RemoveEdge(T v1, T v2);             // 删除边
    void DestroyGraph();                     // 摧毁图结构
    int GetFirstNeighbor(T v);               // 获取顶点
    int GetNextNeighbor(T v, T w);           // 获取邻接顶点的顶点
    T GetVertexData(int v);                  // 获取该位置的的data
    void DFS(T v);                           // 深度优先遍历算法，从哪一个顶点开始访问
    void DFSTraverse(int v, bool visited[]); // 深度优先操作，传入顶点位置和标志位数组
    // 传入数组实际上是传入数组的首地址
    void BFS(T vertex); // 广度优先遍历
    void DFS_onconnect();
    int GetWeight(int v1, int v2); // 获取权值
    void Prim(T vertex);
    void kruskal();
    void bubbleSort(Edge_kruskal *arr);
    bool Is_same(int *parent,int i,int j);
    void Mark_same(int *parent,int i,int j);
};


void GraphMtx::InitGraph()
{
    this->MaxVertices = Default_Vertices_Size;
    this->NumEdges = this->NumVertices = 0;
    this->VerticesList = new T[MaxVertices]; // 创建头指针指向的数据链
    assert(VerticesList != NULL);
    this->Edge = new int *[MaxVertices]; // 创建边指向的权
    for (int i = 0; i < this->MaxVertices; i++)
    {
        this->Edge[i] = new int[MaxVertices]; // 开辟权值空间
    }
    for (int i = 0; i < this->MaxVertices; ++i)
    {
        /*
        g->Edge[i] 是一个指向 int 类型的指针，它指向了一个动态分配的内存空间，
        这个空间可以看作是一个一维的 int 数组。
        g->Edge[i][j] 则是访问了这个一维数组中的第 j 个元素，
        即这个动态分配的内存空间中的某个 int 数据。
        */
        for (int j = 0; j < MaxVertices; j++)
        {
            this->Edge[i][j] = Max_Cost; // 所有顶点到顶点之间的权
        }
    }
}

int GraphMtx::GetVertexPos(T v)
{
    for (int i = 0; i < this->NumVertices; i++)
    {
        if (this->VerticesList[i] == v)
        {
            return i;
        }
    }
    return -1; // 用于判断其是否合法
}

void GraphMtx::ShowMtx()
{
    // 打印对应的顶点
    cout << "   ";
    for (int i = 0; i < this->NumVertices; i++)
    {
        cout << "  " << this->VerticesList[i];
    }
    cout << endl;
    // 打印边对应的矩阵
    for (int i = 0; i < this->NumVertices; i++)
    {

        cout << "  " << this->VerticesList[i];

        for (int j = 0; j < this->NumVertices; j++)
        {
            if (this->Edge[i][j] != 0x7FFFFFFF)
            {
                cout << "  " << this->Edge[i][j];
            }
            else
            {
                cout << "  "
                     << "@";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void GraphMtx::Insert(T v)
{
    if (this->NumVertices >= this->MaxVertices) // 判断顶点数量是否超过最大数量
    {
        return;
    }
    this->VerticesList[this->NumVertices++] = v;
}

void GraphMtx::InsertEdge(T v1, T v2, int cost) // 插入边，先获取图中两个顶点的位置
{
    int p1 = GetVertexPos(v1);
    int p2 = GetVertexPos(v2);
    if (p1 == -1 || p2 == -1) // 判断位置是否存在
    {
        return;
    }
    else
    {
        if (Edge[p1][p2] != 0x7FFFFFFF)
        {
            return;
        }
        else
        {
            this->Edge[p1][p2] = this->Edge[p2][p1] = cost; // 1为有边2
            this->NumEdges++;
        }
    }
}

void GraphMtx::RemoveEdge(T v1, T v2)
{
    int p1 = GetVertexPos(v1);
    int p2 = GetVertexPos(v2);
    if (p1 == -1 || p2 == -1) // 判断位置是否存在
    {
        return;
    }
    else
    {
        if (Edge[p1][p2] != 1)
        {
            return;
        }
        else
        {
            this->Edge[p1][p2] = this->Edge[p2][p1] = 0; // 1为有边
            this->NumEdges--;
        }
    }
}

void GraphMtx::RemoveVertex(T v)
{
    int p = this->GetVertexPos(v);
    if (p == -1)
    {
        cout << "不存在该位置";
        return;
    }
    int numedges = 0;
    // 移动顶点
    for (int i = p; i < this->NumVertices - 1; i++)
    {
        this->VerticesList[i] = VerticesList[i + 1];
    }
    // 改变边的数量
    for (int i = 0; i < this->NumVertices; i++)
    {
        if (this->Edge[p][i] != 0)
        {
            numedges++;
        }
    }
    // 移动行
    for (int i = p; i < this->NumVertices - 1; i++)
    {
        for (int j = 0; j < NumVertices; j++)
        {
            this->Edge[i][j] = this->Edge[i + 1][j];
        }
    }
    // 移动列    ···············
    for (int i = p; i < this->NumVertices; i++)
    {
        for (int j = 0; j < this->NumVertices; j++)
        {
            this->Edge[j][i] = this->Edge[j][i + 1];
        }
    }
    delete (this->Edge[NumVertices]);
    this->NumVertices--;
    this->NumEdges -= numedges;
}

void GraphMtx::DestroyGraph() // 摧毁图结构
{
    // 释放顶点
    delete (this->VerticesList);
    this->VerticesList = NULL;
    // 释放边
    for (int i = 0; i < this->NumVertices; i++)
    {
        delete (this->Edge[i]); // 释放列
    }
    delete (this->Edge); // 释放行
    this->Edge = NULL;
    this->MaxVertices = this->NumEdges = this->NumVertices = 0;
    cout << "该图已摧毁-------";
}

int GraphMtx::GetFirstNeighbor(T v) // 获取第一个邻阶顶点,在边的矩阵中，找列第一个不为零的
{
    int p = this->GetVertexPos(v);
    if (p == -1)
    {
        return -1;
    }
    for (int i = 0; i < this->NumVertices; i++)
    {

        if (this->Edge[p][i] == 1)
        {
            return i;
        }
    }
    return -1;
}

int GraphMtx::GetNextNeighbor(T v, T w) // 获取邻接顶点的下一个邻接顶点
{
    int pv = this->GetVertexPos(v);
    int pw = this->GetVertexPos(w);
    if (pv == -1 || pw == -1)
    {
        return -1;
    }
    for (int i = pw + 1; i < this->NumVertices; i++)
    {
        if (this->Edge[pv][i] == 1)
        {
            return i;
        }
    }
    return -1;
}

T GraphMtx::GetVertexData(int v)
{
    if (v < this->NumVertices)
    {
        return this->VerticesList[v];
    }
    return -1;
}

void GraphMtx::DFS(T vertex) // 递归的算法
{
    int n = this->NumVertices;
    bool *visited = new bool[n]; // 是否访问过的标志位
    assert(visited != NULL);
    // 先对这个标志位进行初始化
    for (int i = 0; i < n; i++)
    {
        visited[i] = false; // 都还没有被访问
    }
    int v = this->GetVertexPos(vertex); // 获取顶点的位置
    this->DFSTraverse(v, visited);
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

void GraphMtx::DFSTraverse(int v, bool visited[])
{
    T temp_data = this->GetVertexData(v);
    cout << "  " << temp_data;
    visited[v] = true;                         // 处理标志位数组
    int w = this->GetFirstNeighbor(temp_data); // 获得邻接顶点的位置，开始递归
    while ((w != -1))                          // 判断条件是有邻接顶点
    {
        if (!visited[w])
        {
            this->DFSTraverse(w, visited);
        }
        w = this->GetNextNeighbor(temp_data, GetVertexData(w));
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

// void GraphMtx::BFS(T vertex)
// {
//     //-------------初始化
//     bool* arry=new bool [NumVertices];
//     assert(arry!=NULL);
//     for(int i=0;i<this->NumVertices;i++)
//     {
//         arry[i]=false;
//     }
//     //----------------头顶点&&队列
//     cout<<"  "<<T;
//     arry(this->GetVertexPos)=true;
//     queue<int>  q;
//     q.push(GetVertexPos(vertex));
//     //----------------循环遍历
//     while(!q.empty)
//     {
//         int temp=q.front();
//         q.pop();
//         next=this->GetFirstNeighbor(this->GetVertexData(temp));
//         while()
//         if(!arry[next])
//         {
//             cout<<"  "<<this->GetVertexData(next);
//             arry[next]=true;
//         }
//         next=this->GetNextNeighbor(GetVertexData(temp),GetVertexData(next));
//     }
// }

void GraphMtx::DFS_onconnect() // 非联通图的深度优先遍历
{
    int n = this->NumVertices;
    bool *visited = new bool[n]; // 是否访问过的标志位
    assert(visited != NULL);
    // 先对这个标志位进行初始化
    for (int i = 0; i < n; i++)
    {
        visited[i] = false; // 都还没有被访问
    }

    // 开始遍历
    for (int i = 0; i < this->NumVertices; i++)
    {
        if (!visited[i])
        {
            this->DFSTraverse(i, visited);
        }
    }
    delete (visited);
}

int GraphMtx::GetWeight(int v1, int v2)
{
    if (v1==-1 || v2==-1)
        return Max_Cost;
    return this->Edge[v1][v2];
}

void GraphMtx::Prim(T vertex)
{
    int begin;
    int end;
    int cost;

    int n = this->NumVertices;
    int *lowcost = new int[n]; // 以i为终点的边的最小的权值
    int *mst = new int[n];      // 对应的lowcost[i] 的起点
    assert(lowcost != NULL && mst != NULL);
    int k = this->GetVertexPos(vertex); // 传入顶点的位置

    for (int i = 0; i < n; i++)
    {
        if (i != k)
        {
            //其他点到联通集的权值
            lowcost[i] = this->GetWeight(k, i); // 将k到其他顶点的权值存入
            mst[i] = k;                         // 此时i对应的联通体内的顶点是k
        }
        else
        {
            lowcost[i] = 0;
        }
    }

    int min, min_index; // 最小花费和他的点
    for (int i=0; i< n-1; i++)//有n-1个顶点所以寻找n-1个边
    {
        //初始化边的权重和顶点信息
        min = Max_Cost;
        min_index = -1;

        //寻找和此时的连通体联通的最小权以及对应的顶点
        for (int j=0; j<n;j++)
        {
            if(lowcost[j]!=0&&lowcost[j]<min)//该边存在且小于边的min
            {
                min=lowcost[j];//最小花费代价
                min_index=j;//最小花费代价的顶点
            }
        }

        //输出
        begin=mst[min_index];
        end=min_index;
        //cout<<begin<<"   "<<end<<endl;
        cout<<this->VerticesList[begin]<<"-->"<<this->VerticesList[end]<<" : "<<min<<endl;
       
        //将刚才的输出的顶点边改为0       
        lowcost[min_index]=0;

        //更改新的联通体的lowcost表，和mst
        for(int j=0;j<n;j++)
        {
            cost=this->GetWeight(min_index,j);//另一个顶点加入联通集，所以如果新的连接该顶点的边权值小于旧的就更新
            if(cost<lowcost[j])
            {
                lowcost[j]=cost;
                mst[j]=min_index;
            }
        }
    }
    delete(lowcost);
    delete(mst);
}

void GraphMtx::bubbleSort(Edge_kruskal *arr) 
{
   int Long=this->NumEdges;//元素个数
   cout<<"排序前的数组为："<<endl;
    for(int q=0;q<Long;q++)
    {
        cout<<arr[q].cost<<"    ";
    }
   cout<<endl;//原数组输出
   Edge_kruskal temp;
   for (int s=Long;s>0;s--)//外循环
   {
        for(int i=0;i<s-1;i++)//内循环
        {
            temp=arr[i];//临时变量
            if(arr[i].cost>arr[i+1].cost)
            {
                arr[i].start=arr[i+1].start;
                arr[i].end=arr[i+1].end;
                arr[i].cost=arr[i+1].cost;
                arr[i+1].start=temp.start;//相邻元素交换
                arr[i+1].end=temp.end;
                arr[i+1].cost=temp.cost;
            }
        }
    }
   cout<<"排序后的数组为："<<endl;
   for(int j=0;j<Long;j++)
   {
    cout<<arr[j].cost<<"    ";//排序后数组输出
   }
}

bool GraphMtx::Is_same(int *parent,int i,int j)
{
    while(parent[i]!=i)//父节点不等于自己，就说明自己不是孤立节点
    {
        i=parent[i];//起点
    }
    while(parent[j]!=j)
    {
        j=parent[j];//终点
    }
    return i==j;
}

void GraphMtx::Mark_same(int *parent,int i,int j)
{
    while(parent[i]!=i)
    {
        i=parent[i];
    }
    while(parent[j]!=j)
    {
        j=parent[j];
    }
    parent[j]=i;
}

void GraphMtx::kruskal()
{
    int i,n,m;
    Edge_kruskal edges[this->NumEdges];
    int parent[this->NumVertices];
    int num=0;
    for(int i=1;i<this->NumVertices;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if(GetWeight(i,j)!=0x7FFFFFFF)
            {
                edges[num].start=i;
                edges[num].end=j;
                edges[num].cost=this->GetWeight(i,j);
                num++;
            }
        }
    }
    bubbleSort(edges);//排序
    for(int i=0;i<this->NumVertices;i++)//初始化，自己的父节点就是自己
    {
        parent[i]=i;
    }
    cout<<endl;
    //然后遍历最小的边，并且还要判断是否同一个联通图里
    for(int i=0;i<this->NumEdges;i++)
    {
        if(!Is_same(parent,edges[i].start,edges[i].end))
        {
            n=edges[i].start;
            m=edges[i].end;
            cout<<this->VerticesList[n]<<"-->"<<this->VerticesList[m]<<" :"<<edges[i].cost<<endl;
            Mark_same(parent,edges[i].start,edges[i].end);
        }
    }
}


void test_prim()
{
    GraphMtx graph;
    graph.InitGraph();
    graph.Insert('A');
    graph.Insert('B');
    graph.Insert('C');
    graph.Insert('D');
    graph.Insert('E');
    graph.Insert('F');
    graph.InsertEdge('A', 'B', 6);
    graph.InsertEdge('B', 'E', 3);
    graph.InsertEdge('E', 'F', 6);
    graph.InsertEdge('F', 'D', 2);
    graph.InsertEdge('D', 'A', 5);
    graph.InsertEdge('A', 'C', 1);
    graph.InsertEdge('B', 'C', 5);
    graph.InsertEdge('E', 'C', 6);
    graph.InsertEdge('F', 'C', 4);
    graph.InsertEdge('D', 'C', 5);
    graph.ShowMtx();
    graph.Prim('A');
}


void test_kruskal()
{
    GraphMtx graph;
    graph.InitGraph();
    graph.Insert('A');
    graph.Insert('B');
    graph.Insert('C');
    graph.Insert('D');
    graph.Insert('E');
    graph.Insert('F');
    graph.InsertEdge('A', 'B', 6);
    graph.InsertEdge('B', 'E', 3);
    graph.InsertEdge('E', 'F', 6);
    graph.InsertEdge('F', 'D', 2);
    graph.InsertEdge('D', 'A', 5);
    graph.InsertEdge('A', 'C', 1);
    graph.InsertEdge('B', 'C', 5);
    graph.InsertEdge('E', 'C', 6);
    graph.InsertEdge('F', 'C', 4);
    graph.InsertEdge('D', 'C', 5);
    graph.ShowMtx();
    graph.kruskal();
}

int main()
{
    test_kruskal();
    return 0;
}