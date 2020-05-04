//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_DESIGN_GREEDY_ACTIONSPLANNING_H
#define AILIB_DESIGN_GREEDY_ACTIONSPLANNING_H
#include "..\..\stdafx.h"

extern "C" ALGORITHMLIB class Action
{
public:
	Action();
	Action(double nStartTime_, double nEndTime_);
	~Action();
public:
	double m_nStartTime;
	double m_nEndTime;
};

// 问题描述：
// 给定n个活动集合<a1,a2,...,an>
// 每个活动具有开始时间si，结束时间ei
// 现在需要从n个活动集合中选出一个最大兼容活动子集
extern "C" ALGORITHMLIB int CalculateMaxSubArray(
	Action* pActionArrSortedByEndTime_, 
	int nNum_);
#endif