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

// ����������
// ����n�������<a1,a2,...,an>
// ÿ������п�ʼʱ��si������ʱ��ei
// ������Ҫ��n���������ѡ��һ�������ݻ�Ӽ�
extern "C" ALGORITHMLIB int CalculateMaxSubArray(
	Action* pActionArrSortedByEndTime_, 
	int nNum_);
#endif