#include<iostream>
#include<vector>
using namespace std;

void solution(vector<int>& coins, int amount)
{
	vector<int> dp(amount + 1, INT_MAX);
	dp[0] = 0;
	if (amount == 0)
	{
		return 0;
	}
	for (int i = 1; i < coins.size(); i++)
	{
		for (int j = coins[i]; j <= amount; j++)
		{
			if(dp[j-coins]!=INT_MAX)
			dp[j] = min(dp[j], dp[j - coins[i]] + 1);
		}
	}
	if (dp[amount] == INT_MAX) return -1;
	return dp[amount];
}




class Solution
{
public:
	int coinChange(vector<int>& coins, int amount)
	{
		vector<int> dp(amount + 1, INT_MAX);
		dp[0] = 0;
		if (amount == 0)
		{
			return 0;
		}
		for (int i = 1; i < coins.size(); i++)
		{
			for (int j = coins[i]; j <= amount; j++)
			{
				if (dp[j - coins] != INT_MAX)
					dp[j] = min(dp[j], dp[j - coins[i]] + 1);
			}
		}
		if (dp[amount] == INT_MAX) return -1;
		return dp[amount];
	}
}