#include<string>
#include<vector>
#include<iostream>
using namespace std; 

vector<vector<int>> result;
vector<int> path;

void DFS(vector<vector<int>> &graph,int x,int n)
{
    if(x==n)
    {
        result.push_back(path);
        return;
    }
    for(int i=1;i<=n;i++)//为了找到与x相连的点
    {
        if(graph[x][i]==1)
        {
            path.push_back(i);
            DFS(graph,i,n);
            path.pop_back();
        }
    }
}
 
int main()
{
    int n,m,s,t;
    cin>>n>>m;
    vector<vector<int>> graph(n+1,vector<int>(n+1,0));
    while(m--)
    {
        cin>>s>>t;
        graph[s][t]=1;
    }
    path.push_back(1);
    DFS(graph,1,n);

    if(result.empty()) 
    {
        cout<<-1<<endl;
        return 0;
    }
    for(vector<int> v:result)
    {
        auto begin=v.begin();
        for(;begin!=v.end()-1;begin++)
        {
            cout<<*begin<<" ";
        }
        cout<<*begin<<endl;
    }

}