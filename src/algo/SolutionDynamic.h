#pragma once
#include "map"
#include <qobject.h>

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

  private:
    std::map<int, int> iiMap;
};