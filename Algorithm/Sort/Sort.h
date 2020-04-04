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
		// todo
		// ���ǿɵ��ö��󣬿ɵ��ö�����ֵ����ֵ�ж�
		class Helper
		{
		public:
			template <typename T>
			static void QuickSort(
				T* pS_,// ָ�������׶���ָ��
				T* pE_,
				std::function<int(const T&, const T&)> compareFun_ 
				= [](const T& nT1_, const T& nT2_)->int
				{
					if (nT1_ > nT2_)
					{
						return 1;
					}
					else if (nT1_ < nT2_)
					{
						return -1;
					}
					else
					{
						return 0;
					}
				});// ָ������β�����ָ��

			// ����˼�룺
			// �Ѵ󼯺ϻ���Ϊ����С���ϣ���С��������
			// ������С���Ͻ��кϲ�
			// �õ�����Ĵ󼯺�
			template <typename T>
			static void MergeSort(
				T* pS_,
				T* pE_,
				std::function<int(const T&, const T&)> compareFun_
				= [](const T& nT1_, const T& nT2_)->int
				{
					if (nT1_ > nT2_)
					{
						return 1;
					}
					else if (nT1_ < nT2_)
					{
						return -1;
					}
					else
					{
						return 0;
					}
				});
		private:
			template <typename T>
			static T* Partition(
				T* pS_,
				T* pE_,
				std::function<int(const T&, const T&)> compareFun_);

			template <typename T>
			static void Merge(
				T* pStart_,
				T* pMid_,
				T* pEnd_,
				std::function<int(const T&, const T&)> compareFun_);
		};
		
		template <typename T>
		void Helper::QuickSort(
			T* pS_,
			T* pE_,
			std::function<int(const T&, const T&)> compareFun_)
		{
			int _nNum = pE_ - pS_;
			if (_nNum <= 1)
			{
				return;
			}

			T* _pMain = Partition(pS_, pE_, compareFun_);
			QuickSort(pS_, _pMain, compareFun_);
			QuickSort(_pMain + 1, pE_, compareFun_);
		}

		// ����ֵ��
		// ָ����Ԫ����ָ�롾��Ԫ�������Ԫ��С����Ԫ����Ԫ�����ұ�Ԫ�ش�����Ԫ��
		template <typename T>
		T* Helper::Partition(
			T* pS_,// ִ�������׶���ָ��
			T* pE_,
			std::function<int(const T&, const T&)> compareFun_)// ָ������β�����ָ��
		{
			T _nMain = *pS_;
			T* _pL = pE_ - 1;
			T* _pEmpty = pS_;
			while (true)
			{
				// ��ֹ���
				if (_pEmpty == _pL)
				{
					break;
				}

				// ��_pFλ��Ԫ������Ԫ�Ƚ�
				int _nRet = compareFun_(*(_pEmpty + 1), _nMain);
				if (_nRet <= 0)
				{
					*_pEmpty = *(_pEmpty + 1);
					_pEmpty++;
				}
				else
				{
					T _nTemp = *_pL;
					*_pL = *(_pEmpty + 1);
					*(_pEmpty + 1) = _nTemp;
					_pL--;
				}
			}

			*_pEmpty = _nMain;
			return _pEmpty;
		}


		template <typename T>
		void Helper::MergeSort(
			T* pS_,
			T* pE_,
			std::function<int(const T&, const T&)> compareFun_)
		{
			int _nNum = pE_ - pS_;
			if (_nNum <= 1)
			{
				return;
			}

			T* _pMiddle = pS_ + _nNum / 2;
			MergeSort(pS_, _pMiddle, compareFun_);
			MergeSort(_pMiddle, pE_, compareFun_);
			Merge(pS_, _pMiddle, pE_, compareFun_);
		}

		template <typename T>
		void Helper::Merge(
			T* pStart_,
			T* pMid_,
			T* pEnd_,
			std::function<int(const T&, const T&)> compareFun_)
		{
			int _nNum1 = (pMid_ - pStart_);
			int _nNum2 = (pEnd_ - pMid_);
			T* _arr1 = nullptr;
			T* _arr2 = nullptr;
			try
			{
				_arr1 = new T[_nNum1];
			}
			catch (...)
			{
				_arr1 = nullptr;
				throw "out of memory";
			}

			try
			{
				_arr2 = new T[_nNum2];
			}
			catch (...)
			{
				_arr2 = nullptr;
				throw "out of memory";
			}

			for (int _i = 0; _i < _nNum1; _i++)
			{
				_arr1[_i] = *(pStart_ + _i);
			}

			for (int _i = 0; _i < _nNum2; _i++)
			{
				_arr2[_i] = *(pMid_ + _i);
			}

			int _i = 0;
			int _j = 0;
			T* _pTemp = pStart_;
			while (_i < _nNum1 && _j < _nNum2)
			{
				int _nRet = compareFun_(_arr1[_i], _arr2[_j]);
				if (_nRet <= 0)
				{
					*_pTemp = _arr1[_i++];
				}
				else
				{
					*_pTemp = _arr2[_j++];
				}

				_pTemp++;
			}

			if (_i == _nNum1)
			{
				for (int _k = _j; _k < _nNum2; _k++)
				{
					*_pTemp = _arr2[_k];
					_pTemp++;
				}
			}
			else
			{
				for (int _k = _i; _k < _nNum1; _k++)
				{
					*_pTemp = _arr1[_k];
					_pTemp++;
				}
			}

			delete[] _arr1;
			_arr1 = nullptr;
			delete[] _arr2;
			_arr2 = nullptr;
		}
	}
}
#endif
