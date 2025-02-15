class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int result = 0;
        int j = s.size() - 1;
        for (int i = g.size() - 1; i >= 0; i--)
        {
            if (j >= 0 && s[j] >= g[i])
            {
                result++;
                j--;
            }
        }
        return result;
    }
};