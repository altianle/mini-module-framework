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

int SolutionDynamic::rob(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return nums[0];
    }
    if (n == 2)
    {
        return max(nums[0], nums[1]);
    }
    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    for (int i = 2; i < n; i++)
    {
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    }
    return dp[n - 1];
}

int SolutionDynamic::deleteAndEarn(vector<int> &nums)
{
    // 这里的状态转移方程为dp[i] = max(dp[i - 2] + record[i], dp[i - 1])
    int maxNum = 0;
    for (auto num : nums)
    {
        if (num > maxNum)
            maxNum = num;
    }
    vector<int> record(maxNum + 1);
    for (auto num : nums)
    {
        record[num] += num;
    }
    vector<int> dp(maxNum + 1);
    dp[1] = record[1];
    for (int i = 2; i < dp.size(); i++)
    {
        dp[i] = max(dp[i - 2] + record[i], dp[i - 1]);
    }
    return dp[dp.size() - 1];
}

int SolutionDynamic::uniquePaths(int m, int n)
{
    // map记录法
    if (flag)
    {
        flag = false;
        iiVec = vector<vector<int>>(m + 1, vector<int>(n + 1));
    }
    if (m == 0 || n == 0)
    {
        return 0;
    }
    if (m == 1 || n == 1)
    {
        return 1;
    }
    if (iiVec[m][n] != 0)
    {
        return iiVec[m][n];
    }
    int res = uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
    iiVec[m][n] = res;
    return res;
}

int SolutionDynamic::uniquePaths2(int m, int n)
{
    // 打表法
    vector<vector<int>> dp = vector<vector<int>>(m, vector<int>(n));
    dp[m - 1][n - 1] = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            if (i == n - 1 && j == m - 1)
                continue;
            if (j + 1 == m)
            {
                dp[j][i] = 1;
                continue;
            }
            if (i + 1 == n)
            {
                dp[j][i] = 1;
                continue;
            }
            dp[j][i] = dp[j + 1][i] + dp[j][i + 1];
        }
    }
    return dp[0][0];
}

int SolutionDynamic::minPathSum(vector<vector<int>> &grid)
{
    // 先遍历最下边和最右边
    // 再从右下开始遍历
    int row = grid.size();
    int col = grid[0].size();
    vector<vector<int>> pd = vector<vector<int>>(row, vector<int>(col));
    for (int i = row - 1; i >= 0; i--)
    {
        pd[i][col - 1] = grid[i][col - 1];
        if (i < row - 1)
        {
            pd[i][col - 1] += pd[i + 1][col - 1];
        }
    }
    for (int j = col - 1; j >= 0; j--)
    {
        pd[row - 1][j] = grid[row - 1][j];
        if (j < col - 1)
        {
            pd[row - 1][j] += pd[row - 1][j + 1];
        }
    }
    for (int i = row - 2; i >= 0; i--)
    {
        for (int j = col - 2; j >= 0; j--)
        {
            if (i < 0 || j < 0)
            {
                continue;
            }
            pd[i][j] = min(pd[i + 1][j], pd[i][j + 1]) + grid[i][j];
        }
    }
    return pd[0][0];
}

int SolutionDynamic::uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
{
    // 先遍历最下边和最右边
    // 再从右下开始遍历
    int row = obstacleGrid.size();
    if (row == 0)
    {
        return 0;
    }
    int col = obstacleGrid[0].size();
    if (obstacleGrid[row - 1][col - 1] == 1)
    {
        return 0;
    }
    vector<vector<double>> pd = vector<vector<double>>(row, vector<double>(col));
    pd[row - 1][col - 1] = 1;
    for (int i = row - 2; i >= 0; i--)
    {
        if (obstacleGrid[i][col - 1] == 0)
        {
            pd[i][col - 1] = pd[i + 1][col - 1];
        }
        else
        {
            pd[i][col - 1] = 0;
        }
    }
    for (int j = col - 2; j >= 0; j--)
    {
        if (obstacleGrid[row - 1][j] == 0)
        {
            pd[row - 1][j] = pd[row - 1][j + 1];
        }
        else
        {
            pd[row - 1][j] = 0;
        }
    }
    for (int i = row - 2; i >= 0; i--)
    {
        for (int j = col - 2; j >= 0; j--)
        {
            if (obstacleGrid[i][j] == 1)
            {
                pd[i][j] = 0;
                continue;
            }
            if (pd[i + 1][j] > 0)
            {
                if (pd[i][j + 1] > 0)
                {
                    pd[i][j] = pd[i + 1][j] + pd[i][j + 1];
                }
                else
                {
                    pd[i][j] = pd[i + 1][j];
                }
            }
            else if (pd[i][j + 1] > 0)
            {
                pd[i][j] = pd[i][j + 1];
            }
            else
            {
                pd[i][j] = 0;
            }
        }
    }
    return pd[0][0];
}