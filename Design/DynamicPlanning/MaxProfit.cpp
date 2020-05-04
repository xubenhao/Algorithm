#define ALGORITHMLIB __declspec(dllexport)
#include "MaxProfit.h"

// 算法输入：
// nLength_ 总的长度
// pPriceTable_ 一个数组。给出每个长度len和此长度对应的价格price
// 输入限制：
// 对于价格数组中，任意一组，满足 len > 0, price >= 0
// 划分必须按整数长度进行
// 算法目标：
// 求取给定输入nLength_下，
// 一个对nLength_的可取得最大价格的划分方案，及该划分方案下的价格
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

// 算法输入：
// nLength_ 总的长度
// pPriceTable_ 一个数组。给出每个长度len和此长度对应的价格price
// pMaxProfitTable_ 一个数组。存储已经知道的len和此len下最优划分方案的价格。
// 输入限制：
// 对于价格数组中，任意一组，满足 len > 0, price >= 0
// 划分必须按整数长度进行
// 算法目标：
// 求取给定输入nLength_下，一个对nLength_的可取得最大价格的划分方案，及该划分方案下的价格
double CalculateMaxProfit2(
	int nLength_, 
	const double* pPriceTable_, 
	double * pMaxProfitTable_, 
	int nNum_)
{
	// 所求取的 长度下最优划分方案下的价格，已经知道直接返回
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

// 算法输入：
// nLength_ 总的长度
// pPriceTable_ 一个数组。给出每个长度len和此长度对应的价格price
// 输入限制：
// 对于价格数组中，任意一组，满足 len > 0, price >= 0
// 划分必须按整数长度进行
// 算法目标：
// 求取给定输入nLength_下，一个对nLength_的可取得最大价格的划分方案，及该划分方案下的价格
double CalculateMaxProfitByIterration(
	int nLength_, 
	const double* pPriceTable_, 
	int nNum_)
{
	// 分配内存用于存储，len及len下最优方案下价格
	double* _nMaxProfit = (double*)malloc(sizeof(double) * (nNum_ + 1));
	// 迭代
	// 循环不变式：
	// _nMaxProfit存储了上次len下最优划分下的价格
	// 初始时：
	// _nMaxProfit为空，上次len不存在。符合。
	// 第0/1次迭代后，_nMaxProfit分别存储0/1长度下最优方案下价格

	// 某次迭代_i = len
	// 依据循环不变式，0,1,...,len-1下最优方案及其下价格均已经存储于_nMaxProfit
	// 依据
	// 长度为n的最优划分 = max
	// (
	//		1 + 长度为n-1的最优划分
	//		2 + 长度为n-2的最优划分
	//		...
	//		n + 长度为0的最优划分
	// )
	// 可以直接利用已有结果得到len下最优方案及其下价格
	// 综合，循环不变式成立
	for (int _i = 0; _i <= nLength_; _i++)
	{
		// 从低到高
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

