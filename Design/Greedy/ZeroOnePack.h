//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_DESIGN_GREEDY_ZEROONEPACK_H
#define AILIB_DESIGN_GREEDY_ZEROONEPACK_H
#include "..\..\stdafx.h"

// 0-1背包问题
// 问题描述：
// n个物品，对物品i有价值vi，重量wi。
// 从n个物品中选择若干件放入容器，容器可承载最大重量W。
// 如何选择放入的物品集合，以使价值最大。
// 可以用划分将原问题转化为求解相同类型子问题的，
// 定可用递归求解，子问题重叠的可在递归中加入备忘或者使用自底向上的迭代，
// 满足特点性质时，可进一步验证是否可以做出最优选择，而后求解规模-1的子问题来求解。
// 动态规划
extern "C" ALGORITHMLIB int CalculateMaxValue1(
	int* nValueArr_, 
	int* nWeightArr_, 
	int nStartPos_, 
	int nEndPos_, 
	int nCapcity_);
extern "C" ALGORITHMLIB int CalculateMaxValue2(
	int* nValueArr_, 
	int* nWeightArr_, 
	int nStartPos_, 
	int nEndPos_, 
	int nCapcity_, 
	int* pResult_, 
	int nMaxNum_);

// 分数背包：
// 0-1背包 + 对物品的选择可以不用0-1的方式，可以选取部分
// 解决方法：
// 依次算出每个物品的单位价值
// 依次按单位价值从高到低放入背包
// 如此得到的必然是最优方案
// 贪心算法
#endif

