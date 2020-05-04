#define ALGORITHMLIB __declspec(dllexport)
#include "MaxProfit.h"

// �㷨���룺
// nLength_ �ܵĳ���
// pPriceTable_ һ�����顣����ÿ������len�ʹ˳��ȶ�Ӧ�ļ۸�price
// �������ƣ�
// ���ڼ۸������У�����һ�飬���� len > 0, price >= 0
// ���ֱ��밴�������Ƚ���
// �㷨Ŀ�꣺
// ��ȡ��������nLength_�£�
// һ����nLength_�Ŀ�ȡ�����۸�Ļ��ַ��������û��ַ����µļ۸�
double CalculateMaxProfit1(
	int nLength_, 
	const double* pPriceTable_, 
	int nNum_)
{
	if (nLength_ == 0)
	{
		return 0;
	}

	if (nLength_ == 1)
	{
		return pPriceTable_[1];
	}

	double _nMaxProfit = 0;
	for (int _i = 1; _i <= nLength_; _i++)
	{
		double _nTempMax = pPriceTable_[_i] + CalculateMaxProfit1(nLength_ - _i, pPriceTable_, nNum_);
		if (_nTempMax > _nMaxProfit)
		{
			_nMaxProfit = _nTempMax;
		}
	}

	return _nMaxProfit;
}

// �㷨���룺
// nLength_ �ܵĳ���
// pPriceTable_ һ�����顣����ÿ������len�ʹ˳��ȶ�Ӧ�ļ۸�price
// pMaxProfitTable_ һ�����顣�洢�Ѿ�֪����len�ʹ�len�����Ż��ַ����ļ۸�
// �������ƣ�
// ���ڼ۸������У�����һ�飬���� len > 0, price >= 0
// ���ֱ��밴�������Ƚ���
// �㷨Ŀ�꣺
// ��ȡ��������nLength_�£�һ����nLength_�Ŀ�ȡ�����۸�Ļ��ַ��������û��ַ����µļ۸�
double CalculateMaxProfit2(
	int nLength_, 
	const double* pPriceTable_, 
	double * pMaxProfitTable_, 
	int nNum_)
{
	// ����ȡ�� ���������Ż��ַ����µļ۸��Ѿ�֪��ֱ�ӷ���
	if (pMaxProfitTable_[nLength_] > 0)
	{
		return pMaxProfitTable_[nLength_];
	}

	if (nLength_ == 0)
	{
		pMaxProfitTable_[0] = 0;
		return pMaxProfitTable_[0];
	}

	if (nLength_ == 1)
	{
		pMaxProfitTable_[1] = pPriceTable_[1];
		return pMaxProfitTable_[1];
	}

	double _nMaxProfit = 0;
	for (int _i = 1; _i <= nLength_; _i++)
	{
		double _nTempMax = pPriceTable_[_i] + CalculateMaxProfit2(nLength_ - _i, pPriceTable_, pMaxProfitTable_, nNum_);
		if (_nTempMax > _nMaxProfit)
		{
			_nMaxProfit = _nTempMax;
		}
	}

	pMaxProfitTable_[nLength_] = _nMaxProfit;
	return pMaxProfitTable_[nLength_];
}

// �㷨���룺
// nLength_ �ܵĳ���
// pPriceTable_ һ�����顣����ÿ������len�ʹ˳��ȶ�Ӧ�ļ۸�price
// �������ƣ�
// ���ڼ۸������У�����һ�飬���� len > 0, price >= 0
// ���ֱ��밴�������Ƚ���
// �㷨Ŀ�꣺
// ��ȡ��������nLength_�£�һ����nLength_�Ŀ�ȡ�����۸�Ļ��ַ��������û��ַ����µļ۸�
double CalculateMaxProfitByIterration(
	int nLength_, 
	const double* pPriceTable_, 
	int nNum_)
{
	// �����ڴ����ڴ洢��len��len�����ŷ����¼۸�
	double* _nMaxProfit = (double*)malloc(sizeof(double) * (nNum_ + 1));
	// ����
	// ѭ������ʽ��
	// _nMaxProfit�洢���ϴ�len�����Ż����µļ۸�
	// ��ʼʱ��
	// _nMaxProfitΪ�գ��ϴ�len�����ڡ����ϡ�
	// ��0/1�ε�����_nMaxProfit�ֱ�洢0/1���������ŷ����¼۸�

	// ĳ�ε���_i = len
	// ����ѭ������ʽ��0,1,...,len-1�����ŷ��������¼۸���Ѿ��洢��_nMaxProfit
	// ����
	// ����Ϊn�����Ż��� = max
	// (
	//		1 + ����Ϊn-1�����Ż���
	//		2 + ����Ϊn-2�����Ż���
	//		...
	//		n + ����Ϊ0�����Ż���
	// )
	// ����ֱ���������н���õ�len�����ŷ��������¼۸�
	// �ۺϣ�ѭ������ʽ����
	for (int _i = 0; _i <= nLength_; _i++)
	{
		// �ӵ͵���
		if (_i == 0)
		{
			_nMaxProfit[0] = 0;
		}
		else if (_i == 1)
		{
			_nMaxProfit[1] = pPriceTable_[1];
		}
		else
		{
			_nMaxProfit[_i] = -1;
			double _nTempMaxProfit = -1;
			for (int _j = 1; _j <= _i; _j++)
			{
				_nTempMaxProfit = pPriceTable_[_j] + _nMaxProfit[_i - _j];
				if (_nTempMaxProfit > _nMaxProfit[_i])
				{
					_nMaxProfit[_i] = _nTempMaxProfit;
				}
			}
		}
	}

	return _nMaxProfit[nLength_];
}

