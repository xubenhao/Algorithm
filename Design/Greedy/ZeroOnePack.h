//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_DESIGN_GREEDY_ZEROONEPACK_H
#define AILIB_DESIGN_GREEDY_ZEROONEPACK_H
#include "..\..\stdafx.h"

// 0-1��������
// ����������
// n����Ʒ������Ʒi�м�ֵvi������wi��
// ��n����Ʒ��ѡ�����ɼ����������������ɳ����������W��
// ���ѡ��������Ʒ���ϣ���ʹ��ֵ���
// �����û��ֽ�ԭ����ת��Ϊ�����ͬ����������ģ�
// �����õݹ���⣬�������ص��Ŀ��ڵݹ��м��뱸������ʹ���Ե����ϵĵ�����
// �����ص�����ʱ���ɽ�һ����֤�Ƿ������������ѡ�񣬶�������ģ-1������������⡣
// ��̬�滮
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

// ����������
// 0-1���� + ����Ʒ��ѡ����Բ���0-1�ķ�ʽ������ѡȡ����
// ���������
// �������ÿ����Ʒ�ĵ�λ��ֵ
// ���ΰ���λ��ֵ�Ӹߵ��ͷ��뱳��
// ��˵õ��ı�Ȼ�����ŷ���
// ̰���㷨
#endif

