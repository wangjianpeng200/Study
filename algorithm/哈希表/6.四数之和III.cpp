#include<iostream>
#include<unordered_set>
#include<unordered_map>
#include<vector>
using namespace std;

class Solution {
    public:
        int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
          unordered_map<int, int> umap;
          for(int numA : A) //遍历A
          {
             for(int numB : B) //遍历B
             {
                umap[numA + numB]++; //将遍历后的结果存入hash表
             }
          }
          int count = 0; //记录结果
          for(int numC : C) //遍历C
          {
            for(int numD : D) //遍历D
            {
                count += umap[-(numC + numD)]; //查找hash表中是否有对应的值------------------这一步很关键
            }
          }
          return count; //返回结果
        }
    };
    