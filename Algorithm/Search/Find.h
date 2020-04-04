//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030                                                                             *

#ifndef ALLIB_ALGORITHM_SEARCH_FIND_H
#define ALLIB_ALGORITHM_SEARCH_FIND_H
#include "..\..\stdafx.h"
namespace AlLib
{
	namespace Algorithm
	{
		namespace Search
		{
			class Helper
			{
			public:
				enum FINDTYPE
				{
					SEQUENCE = 0,
					BINARY,
				};

				enum SORTTYPE
				{
					DESCENDING = 0,
					ASCENDING,
				};

				// ����ֵ��
				// �ɹ���
				// ָ�����ֵָ��
				// ʧ�ܣ�
				// null
				template <typename T,
					FINDTYPE FindType = FINDTYPE::SEQUENCE,
					SORTTYPE SortType = SORTTYPE::ASCENDING>
					static T* Find(
					T* pStart_, // ָ����Ԫ��
					T* pEnd_, // ָ��β��Ԫ��
					const T &value_);// ����ֵ

				// ����ֵ��
				// �ɹ���
				// ����Ԫ������
				// ʧ�ܣ�
				// -1
				template <typename T,
					FINDTYPE FindAlgorithmType = FINDTYPE::SEQUENCE,
					SORTTYPE FindSortType = SORTTYPE::ASCENDING>
					static int Find(
					T* pStart_,
					int nStartIndex_, // ������ʼԪ������
					int nEndIndex_,  // ����β��Ԫ������
					const T& value_);// ����ֵ

			private:
				template <typename T>
				static  T* SequenceFind(
					T* pStart_,
					T* pEnd_,
					const T &value_);
				template <typename T,
					SORTTYPE FindSortType>
					static  T* BinaryFind(
					T* pStart_,
					T* pEnd_,
					const T &value_);
			};

			// ����ֵ��
			// �ɹ���
			// ָ�����ֵָ��
			// ʧ�ܣ�
			// null
			template <typename T,
				Helper::FINDTYPE FindAlgorithmType,
				Helper::SORTTYPE FindSortType>
				T* Helper::Find(
				T* pStart_, // ָ����Ԫ��
				T* pEnd_, // ָ��β��Ԫ��
				const T &value_)// ����ֵ
			{
				if (FindAlgorithmType == FINDTYPE::SEQUENCE)
				{
					return SequenceFind(pStart_, pEnd_, value_);
				}
				else if (FindAlgorithmType == FINDTYPE::BINARY)
				{
					return BinaryFind<T, FindSortType>(pStart_, pEnd_, value_);
				}
				else
				{
					return nullptr;
				}
			}

			template <typename T>
			T* Helper::SequenceFind(
				T* pStart_,
				T* pEnd_,
				const T &value_)
			{
				T* _pTemp = pStart_;
				while (_pTemp != pEnd_)
				{
					if (*_pTemp == value_)
					{
						return _pTemp;
					}

					_pTemp++;
				}

				return nullptr;
			}

			template <typename T,
				Helper::SORTTYPE FindSortType>
				T* Helper::BinaryFind(
				T* pStart_,
				T* pEnd_,
				const T &value_)
			{
				int _nNum = (pEnd_ - pStart_);
				if (_nNum < 1)
				{
					return nullptr;
				}

				if (_nNum == 1)
				{
					if (*pStart_ == value_)
					{
						return pStart_;
					}
					else
					{
						return nullptr;
					}
				}

				T* _pMid = pStart_ + _nNum / 2;
				if (*_pMid == value_)
				{
					return _pMid;
				}
				else if (*_pMid < value_)
				{
					if (FindSortType == SORTTYPE::ASCENDING)
					{
						return BinaryFind<T, FindSortType>(_pMid + 1, pEnd_, value_);
					}
					else
					{
						return BinaryFind<T, FindSortType>(pStart_, _pMid, value_);
					}
				}
				else
				{
					if (FindSortType == SORTTYPE::ASCENDING)
					{
						return BinaryFind<T, FindSortType>(pStart_, _pMid, value_);
					}
					else
					{
						return BinaryFind<T, FindSortType>(_pMid + 1, pEnd_, value_);
					}
				}
			}

			// �ɹ���
			// ����Ԫ������
			// ʧ�ܣ�
			// -1
			template <typename T,
				Helper::FINDTYPE FindAlgorithmType,
				Helper::SORTTYPE FindSortType>
				int Helper::Find(
				T* pStart_,
				int nStartIndex_, // ������ʼԪ������
				int nEndIndex_,  // ����β��Ԫ������
				const T& value_)// ����ֵ
			{
				T* _pActualStart = pStart_ + nStartIndex_;
				T* _pActualEnd = pStart_ + nEndIndex_ + 1;
				T* _pRet = Find<T, FindAlgorithmType, FindSortType>(_pActualStart, _pActualEnd);
				if (_pRet == nullptr)
				{
					return -1;
				}
				else
				{
					value_ = *_pRet;
					return _pRet - pStart_;
				}
			}
		}
	}
}

#endif

