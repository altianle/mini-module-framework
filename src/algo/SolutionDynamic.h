#pragma once
#include "map"
#include <qobject.h>

using std::max;
using std::min;
using std::vector;

class SolutionDynamic : public QObject
{
    Q_OBJECT
  public:
    explicit SolutionDynamic(QObject *parent = nullptr);
    /*
    假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
    每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
    */
    int climbStairs1(int n);
    int climbStairs2(int n);

    /*
    斐波那契数 （通常用 F(n) 表示）形成的序列称为 斐波那契数列 。该数列由 0 和
    1 开始，后面的每一项数字都是前面两项数字的和。也就是：
    F(0) = 0，F(1) = 1 F(n) = F(n - 1) + F(n - 2)，其中 n > 1 给定 n ，请计算 F(n) 。
    */
    int fib(int n);

    /*
    给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i
    个台阶向上爬需要支付的费用。一旦你支付此费用，即可选择向上爬一个或者两个台阶。
    你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。
    请你计算并返回达到楼梯顶部的最低花费。
    */
    int cose(std::vector<int> &cost, int n);
    int minCostClimbingStairs(std::vector<int> &cost);
    int minCostClimbingStairs2(std::vector<int> &cost);

    /*
    打家劫舍
    你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
    影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
    如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
    给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
    */
    int rob(vector<int> &nums);

    /*
    删除并获得点数
    给你一个整数数组 nums ，你可以对它进行一些操作。
    每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。
    之后，你必须删除 所有 等于 nums[i] - 1 和 nums[i] + 1的元素。
    开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。
    */
    int deleteAndEarn(vector<int> &nums);

    /*
    不同路径
    一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
    机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
    问总共有多少条不同的路径？
    */
    int uniquePaths(int m, int n);
    int uniquePaths2(int m, int n);

    /*
    最小路径和
    给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
    说明：每次只能向下或者向右移动一步。
    */
    int minPathSum(vector<vector<int>> &grid);

    /*
    不同路径 II
    给定一个 m x n 的整数数组 grid。一个机器人初始位于 左上角（即 grid[0][0]）。
    机器人尝试移动到 右下角（即 grid[m - 1][n - 1]）。机器人每次只能向下或者向右移动一步。
    网格中的障碍物和空位置分别用 1 和 0 来表示。机器人的移动路径中不能包含 任何 有障碍物的方格。
    返回机器人能够到达右下角的不同路径数量。
    */
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid);

  private:
    std::map<int, int> iiMap;
    vector<vector<int>> iiVec;
    bool flag = true;
};