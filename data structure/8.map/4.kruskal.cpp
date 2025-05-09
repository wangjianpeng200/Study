/*
Kruskal算法是一种用于求解最小生成树（Minimum Spanning Tree，MST）的贪婪算法。
最小生成树是一棵包含图中所有顶点的树，并且边的权重之和最小。

Kruskal算法的基本思想是按照边的权重从小到大的顺序，逐渐选取边加入到最小生成树中，
直到生成树中包含了图中所有的顶点为止。在添加边的过程中，需要确保所选取的边不会形成环路，
否则会破坏树的结构。

Kruskal算法的具体步骤如下：

1.将图中的所有边按照权重进行升序排序。
2.初始化一个空的最小生成树。
3.依次从排序后的边中选取权重最小的边，如果这条边连接的两个顶点不在同一个连通分量中
（即不会形成环路），则将这条边加入最小生成树中。
4.重复步骤3，直到最小生成树包含了图中所有的顶点。

Kruskal算法的时间复杂度主要取决于对边进行排序的时间复杂度，通常为 O(ElogE)，
其中 E 是图中边的数量。

下面是Kruskal算法的伪代码：

Kruskal(Graph G):
1. 将图中的所有边按照权重进行升序排序
2. 初始化一个空的最小生成树 T
3. 对于图中的每条边 e，按照排序后的顺序：
     如果将 e 加入到 T 中不会形成环路：
         将 e 加入到 T 中
4. 返回最小生成树 T
Kruskal算法适用于稀疏图（边的数量相对于顶点数量较少的图），并且能够在实际应用中取得较好的效果。
*/