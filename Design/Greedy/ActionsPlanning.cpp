#define ALGORITHMLIB __declspec(dllexport)
#include "ActionsPlanning.h"

Action::Action()
{
	m_nStartTime = 0.0;
	m_nEndTime = 0.0;
}

Action::Action(
	double nStartTime_, 
	double nEndTime_)
{
	m_nStartTime = nStartTime_;
	m_nEndTime = nEndTime_;
}

Action::~Action()
{
}

// 正确性证明
// 活动集合最大兼容子集 = 集合中最先结束活动 + 剩余活动的最大兼容子集
// 给定任意最大兼容活动集合：k1,...,km
// 设a1为最先结束活动。
// 则，a1,k2,...,km易于证明也为其最大兼容活动集合。

// 除a1外剩余活动最大兼容子集设为p1,...,pk
// k+1 <= m-->k<= m - 1
// k2,...,km = m-1
// k2,...,km中的每个均在除a1外剩余活动最大兼容子集中
// k2,...,km是除a1外剩余活动一个最大兼容子集
// 结论：活动集合最大兼容子集 = 集合中最先结束活动 + 剩余活动的最大兼容子集 成立
int CalculateMaxSubArray(
	Action* pActionArrSortedByEndTime_, 
	int nNum_)
{
	if (nNum_ <= 1)
	{
		return nNum_;
	}

	int _nMaxSubArrayNum = 1;
	Action _nAction = *pActionArrSortedByEndTime_;
	double _nStartTime = _nAction.m_nStartTime;
	double _nEndTime = _nAction.m_nEndTime;
	int _nRemainNum = 0;
	for (int _i = 1; _i < nNum_; _i++)
	{
		Action _nTempAction = *(pActionArrSortedByEndTime_ + _i);
		if (_nTempAction.m_nStartTime >= _nEndTime)
		{
			_nRemainNum++;
		}
	}

	Action* _pRemainActions = (Action*)malloc(sizeof(Action) * _nRemainNum);
	int _nCurIndex = 0;
	for (int _i = 1; _i < nNum_; _i++)
	{
		Action _nTempAction = *(pActionArrSortedByEndTime_ + _i);
		if (_nTempAction.m_nStartTime >= _nEndTime)
		{
			*(_pRemainActions + _nCurIndex++) = _nTempAction;
		}
	}

	_nMaxSubArrayNum += CalculateMaxSubArray(_pRemainActions, _nRemainNum);
	free(_pRemainActions);
	return _nMaxSubArrayNum;
}
