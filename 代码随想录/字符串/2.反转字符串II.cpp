#include<iostream>
#include<unordered_set>
#include<unordered_map>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;


class Solution {
public:
    void trans(string&s,int start,int end){
        while(start<end){
            swap(s[start],s[end]);
            start++;
            end--;
        }
    }
    string reverseStr(string s, int k) {
       for(int i=0;i<s.size();i+=2*k)
       {
        if(i+k<=s.size())
        {
            trans(s,i,i+k-1);
            continue;
        }
        else{
            trans(s,i,s.size()-1); 
        }
       }
    }
};