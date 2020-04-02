//	Author : XuBenHao
//	Version : 1.0.0
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef ALGORITHM_SORT_QUICKSORT_H
#define ALGORITHM_SORT_QUICKSORT_H
#include "..\..\stdafx.h"
namespace Algorithm
{
	namespace Sort
	{
		class Helper
		{
		public:
			template <typename T>
			static void QuickSort(
				T* pS_,// ָ�������׶���ָ��
				T* pE_);// ָ������β������ָ��

		private:
			template <typename T>
			static int Partition(
				T* pS_,
				T* pE_);
		};

		template <typename T>
		void Helper::QuickSort(
			T* pS_,
			T* pE_)
		{
			int _nNum = pE_ - pS_;
			if (_nNum <= 1)
			{
				return;
			}

			T* _pMain = Partition(pS_, pE_);
			QuickSort(pS_, _pMain);
			QuickSort(_pMain + 1, pE_);
		}

		// ����ֵ��
		// ָ����Ԫ����ָ�롾��Ԫ��������Ԫ��С����Ԫ����Ԫ�����ұ�Ԫ�ش�����Ԫ��
		template <typename T>
		T* Helper::Partition(
			T* pS_,// ִ�������׶���ָ��
			T* pE_)// ָ������β������ָ��
		{
			T _nMain = *pS_;
			T* _pL = pE_ - 1;
			T* _pEmpty = pS_;
			while (true)
			{
				// ��ֹ����
				if (_pEmpty == _pL)
				{
					break;
				}

				// ��_pFλ��Ԫ������Ԫ�Ƚ�
				if (*(_pEmpty + 1) <= _nMain)
				{
					*_pEmpty = *(_pEmpty + 1);
					_pEmpty++;
				}
				else
				{
					T _nTemp = *_pL;
					*_pL = *(_pEmpty + 1);
					*(_pEmpty + 1) = _nTemp;
				}
			}

			*_pEmpty = _nMain;
			return _pEmpty;
		}
	}
}
#endif
