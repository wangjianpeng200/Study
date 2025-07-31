#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int dir[4][2]={0,1,0,-1,1,0,-1,0};

void BFS(vector<vector<int>>& grid, vector<vector<int>>& visited, int x, int y)
{
    queue<pair<int,int>> que;
    que.push({x,y});
    visited[x][y]=true;
    while(!que.empty())
    {
        auto [x,y]=que.front();
        que.pop();
        for(int i=0;i<4;i++)
        {
            int nx=x+dir[i][0];
            int ny=y+dir[i][1];
            if(nx<0 || nx>=grid.size() || ny<0 || ny>=grid[0].size() ||visited[nx][ny]) continue;
            if(grid[nx][ny]==1)
            {
                que.push({nx,ny});
                visited[nx][ny]=true;
            }
        }
    }     
}


int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>> grid(n,vector<int>(m,0));
    vector<vector<bool>> visited(n,vector<bool>(m,false));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>grid[i][j];
        }
    }


}