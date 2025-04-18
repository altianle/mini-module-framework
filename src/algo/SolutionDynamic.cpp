#include "SolutionDynamic.h"
#include "Logger.h"

SolutionDynamic::SolutionDynamic(QObject *parent) : QObject(parent)
{
}
int SolutionDynamic::climbStairs1(int n)
{
    // 方法一：记录法
    if (n < 0)
    {
        return 0;
    }
    if (n == 0)
    {
        return 1;
    }
    if (iiMap.find(n) != iiMap.end())
    {
        return iiMap[n];
    }
    int res = climbStairs1(n - 1) + climbStairs1(n - 2);
    iiMap[n] = res;
    return res;
}

int SolutionDynamic::climbStairs2(int n)
{
    // 方法二：滚动数组思想
    // 根据f(x)=f(x−1)+f(x−2)滚动获取f(x)即可
    int p = 0, q = 0, r = 1;
    for (int i = 1; i <= n; ++i)
    {
        p = q;
        q = r;
        r = p + q;
    }
    return r;
}

int SolutionDynamic::fib(int n)
{
    // 滚动数组思想
    if (n < 2)
    {
        return n;
    }
    int p = 0, q = 1, r = 1;
    for (int i = 2; i < n; i++)
    {
        p = q;
        q = r;
        r = p + q;
    }
    return r;
}

int SolutionDynamic::minCostClimbingStairs(std::vector<int> &cost)
{
    return cose(cost, cost.size());
}
int SolutionDynamic::cose(std::vector<int> &cost, int n)
{
    if (n < 0)
    {
        return 0;
    }
    if (iiMap.find(n) != iiMap.end())
    {
        return iiMap[n];
    }
    int res1 = 0, res2 = 0;
    if (n > 0)
        res1 = cost[n - 1] + cose(cost, n - 1);
    if (n > 1)
        res2 = cost[n - 2] + cose(cost, n - 2);
    res1 = res1 > res2 ? res2 : res1;
    iiMap[n] = res1;
    return res1;
}

int SolutionDynamic::minCostClimbingStairs2(std::vector<int> &cost)
{
    // 打表法
    std::vector<int> dp(cost.size() + 1);
    dp[0] = 0;
    dp[1] = 0;
    for (int i = 2; i < dp.size(); i++)
    {
        dp[i] = std::min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    }
    return dp[dp.size() - 1];
}