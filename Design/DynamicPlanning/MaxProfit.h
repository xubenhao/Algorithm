//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_DESIGN_DP_MAXPROFIT_H
#define AILIB_DESIGN_DP_MAXPROFIT_H
#include "..\..\stdafx.h"

extern "C" ALGORITHMLIB double CalculateMaxProfit1(int nLength_, const double* pPriceTable_, int nNum_);
extern "C" ALGORITHMLIB double CalculateMaxProfit2(int nLength_, const double* pPriceTable_, double * pMaxProfitTable_, int nNum_);
extern "C" ALGORITHMLIB double CalculateMaxProfitByIterration(int nLength_, const double* pPriceTable_, int nNum_);
#endif
