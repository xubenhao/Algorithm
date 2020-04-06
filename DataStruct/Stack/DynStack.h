//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef ALLIB_DATASTRUCT_STACK_STACK_H
#define ALLIB_DATASTRUCT_STACK_STACK_H
#include "..\..\stdafx.h"
#include "..\Array\DynArray.h"

namespace AlLib
{
	namespace DataStruct
	{
		namespace Stack
		{
			template <typename T>
			class DynStack
			{
			public:
				DynStack();
				DynStack(const DynStack& sA_);
				DynStack operator=(const DynStack& sA_);
				virtual ~DynStack();

				void Push(const T& nNewValue_);
				T Pop();
				void Reset();
				T Peek(unsigned int nReverseIndex_ = 0) const;
				bool IsEmpty() const;
				int GetSize() const;
				Array::DynArray<T> GetArray() const
				{
					return m_arrValues;
				}
			private:
				Array::DynArray<T> m_arrValues;
			};

			template <typename T>
			DynStack<T>::DynStack()
			{

			}

			template <typename T>
			DynStack<T>::DynStack(const DynStack& sA_)
			{
				m_arrValues = sA_.m_arrValues;
			}
			
			template <typename T>
			typename DynStack<T> DynStack<T>::operator=(const DynStack& sA_)
			{
				m_arrValues = sA_.m_arrValues;
				return *this;
			}

			template <typename T>
			DynStack<T>::~DynStack()
			{

			}

			template <typename T>
			void DynStack<T>::Push(const T& nNewValue_)
			{
				m_arrValues.Add(nNewValue_);
			}

			template <typename T>
			T DynStack<T>::Pop()
			{
				if (IsEmpty())
				{
					throw "stack is empty";
				}

				int _nSize = m_arrValues.GetSize();
				T _nTopValue = m_arrValues[_nSize - 1];
				m_arrValues.DeleteByIndex(_nSize - 1);
				return _nTopValue;
			}

			template <typename T>
			void DynStack<T>::Reset()
			{
				m_arrValues.Reset();
			}

			template <typename T>
			T DynStack<T>::Peek(unsigned int nReverseIndex_) const
			{
				if ((unsigned int)m_arrValues.GetSize() < (nReverseIndex_ + 1))
				{
					throw "out of size";
				}

				int _nSize = m_arrValues.GetSize();
				if (nReverseIndex_ >= (unsigned int)_nSize)
				{
					throw "the position to peek is not exist";
				}

				return m_arrValues[_nSize - 1 - nReverseIndex_];
			}

			template <typename T>
			bool DynStack<T>::IsEmpty() const
			{
				return m_arrValues.GetSize() == 0;
			}

			template <typename T>
			int DynStack<T>::GetSize() const
			{
				return m_arrValues.GetSize();
			}
		}
	}
}
#endif


