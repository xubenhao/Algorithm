//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_DATASTRUCT_QUEUE_PRIORITYQUEUE_H
#define AILIB_DATASTRUCT_QUEUE_PRIORITYQUEUE_H
#include "..\..\stdafx.h"
#include "..\Heap\MinHeap.h"

namespace AlLib
{
	namespace DataStruct
	{
		namespace Queue
		{
			template <typename T>
			class MinPriorityQueue
			{
			public:
				MinPriorityQueue();
				virtual ~MinPriorityQueue();

				MinPriorityQueue(const MinPriorityQueue& dqA_);
				MinPriorityQueue operator=(const MinPriorityQueue& dqA_);

				void In(const T& nValue_);
				T Out();
				T Peek() const;
				bool IsEmpty() const;
				Heap::MinHeap<T> GetHeap() const
				{
					return m_mhHeap;
				}
			private:
				Heap::MinHeap<T> m_mhHeap;
			};

			template <typename T>
			MinPriorityQueue<T>::MinPriorityQueue()
			{
			}

			template <typename T>
			MinPriorityQueue<T>::~MinPriorityQueue()
			{
			}

			template <typename T>
			MinPriorityQueue<T>::MinPriorityQueue(const MinPriorityQueue& mpqA_)
			{
				m_mhHeap = mpqA_.m_mhHeap;
			}

			template <typename T>
			typename MinPriorityQueue<T> MinPriorityQueue<T>::operator=(const MinPriorityQueue& mpqA_)
			{
				if (this == &mpqA_)
				{
					return *this;
				}

				m_mhHeap = mpqA_.m_mhHeap;
				return *this;
			}

			template <typename T>
			void MinPriorityQueue<T>::In(const T& nValue_)
			{
				m_mhHeap.Add(nValue_);
			}

			template <typename T>
			typename T MinPriorityQueue<T>::Out()
			{
				if (IsEmpty())
				{
					throw "queue is empty";
				}

				T _nValue = m_mhHeap.Get(1);
				m_mhHeap.Delete(1);
				return _nValue;
			}

			template <typename T>
			typename T MinPriorityQueue<T>::Peek() const
			{
				if (IsEmpty())
				{
					throw "queue is empty";
				}

				return m_mhHeap.Get(1);
			}

			template <typename T>
			bool MinPriorityQueue<T>::IsEmpty() const
			{
				return m_mhHeap.GetSize() <= 1;
			}
		}
	}
}
#endif

