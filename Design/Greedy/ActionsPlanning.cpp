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

// ��ȷ��֤��
// ������������Ӽ� = ���������Ƚ���� + ʣ�����������Ӽ�
// �������������ݻ���ϣ�k1,...,km
// ��a1Ϊ���Ƚ������
// ��a1,k2,...,km����֤��ҲΪ�������ݻ���ϡ�

// ��a1��ʣ���������Ӽ���Ϊp1,...,pk
// k+1 <= m-->k<= m - 1
// k2,...,km = m-1
// k2,...,km�е�ÿ�����ڳ�a1��ʣ���������Ӽ���
// k2,...,km�ǳ�a1��ʣ��һ���������Ӽ�
// ���ۣ�������������Ӽ� = ���������Ƚ���� + ʣ�����������Ӽ� ����
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
