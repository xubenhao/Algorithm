//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef ALLIB_DATASTRUCT_HEAP_MINHEAP_H
#define ALLIB_DATASTRUCT_HEAP_MINHEAP_H
#include "..\..\stdafx.h"
#include "..\Array\DynArray.h"

namespace AlLib
{
	namespace DataStruct
	{
		namespace Heap
		{
			// 最小堆定义：
			// 容器
			// 所有元素顺序存储于以1为起始索引的数组中
			// 对任意索引为i的元素A
			// 若索引为2*i, 2*i+1位置元素存在，设为B，C
			// 称，B为A左孩子，C为A右孩子。
			// 设位置k处元素的值为V[k]
			// 有 V[i] <= V[2*i] && V[i] <= V[2*i+1]
			template <typename T>
			class MinHeap
			{
			public:
				MinHeap();
				MinHeap(const Array::DynArray<T>& arrElements_);
				~MinHeap();
				MinHeap(const MinHeap& mhA_);
				MinHeap operator=(const MinHeap& mhA_);

				void Add(const T& nT_);
				void Delete(int nIndex_);
				void Set(int nIndex_, const T& nV_);
				T Get(int nIndex_);
				int Find(std::function<bool(const T& nT_)> fun_);
				int GetSize();
			private:
				void BuildHeap(const Array::DynArray<T>& arrElements_);
				void Adjust(int nIndex_);
				void Smaller(int nPos_);
				void Bigger(int nPos_);

			private:
				Array::DynArray<T> m_arrElements;
			};

			template <typename T>
			MinHeap<T>::MinHeap()
			{
			}

			template <typename T>
			MinHeap<T>::MinHeap(const Array::DynArray<T>& arrElements_)
			{
				BuildHeap(arrElements_);
			}

			template <typename T>
			MinHeap<T>::~MinHeap()
			{
			}

			template <typename T>
			MinHeap<T>::MinHeap(const MinHeap& mhA_)
			{
				m_arrElements = mhA_.m_arrElements;
			}

			template <typename T>
			typename MinHeap<T> MinHeap<T>::operator=(const MinHeap& mhA_)
			{
				if (this == &mhA_)
				{
					return *this;
				}

				m_arrElements = mhA_.m_arrElements;
				return *this;
			}

			// 算法目标
			// 输入：无序的含n个元素的数组
			// 算法目标：
			// 输入数组中n个元素以符合最小堆定义的方式存储于m_arrElements的索引1,...,n处
			template <typename T>
			void MinHeap<T>::BuildHeap(const Array::DynArray<T>& arrElements_)
			{
				m_arrElements.DeleteAll();
				m_arrElements.Add(T());
				int _nSize = arrElements_.GetSize();
				for (int _i = 0; _i < _nSize; _i++)
				{
					m_arrElements.Add(arrElements_[_i]);
				}
				
				// 循环不变式：
				// 区间[_i+1, _nSize]内各个元素均满足，
				// 对区间内任意位置k的元素，有以下位置约束
				// 若2*k位置元素存在，则有V[k] <= V[2*k]
				// 若2*k+1位置元素存在，则有V[k] <= V[2*k+1]

				// 证明：
				// 初始时，区间为[_nSize+1, _nSize]为空 区间，循环不变式成立
				// 对_i = k的迭代
				// 依据循环不变式【本次循环迭代前的各个迭代后，循环不变式均满足】
				// 所有_i > k的迭代处理后，循环不变式均满足

				// 由于Adjust(int nIndex_)满足在保证 [nIndex_+1, nSize]区间内任意元素均满足 位置约束前提下，执行后，可实现
				// [nPos, nSize]区间内任意元素均满足 位置约束的效果。
				// 所以，对_i = k迭代后有
				// [k, _nSize]区间内任意元素均满足 位置约束。
				// 循环不变式成立
				for (int _i = _nSize; _i >= 1; _i--)
				{
					Adjust(_i);
				}
			}

			// 算法输入：位置索引nPos
			// 算法前提：[nPos+1, nSize]区间内任意元素均满足 位置约束
			// 算法目标：
			// 算法通过改变[nPos, nSize]内元素位置，执行后，使[nPos, nSize]区间内任意元素均满足 位置约束

			// 正确性证明【数学归纳法】：
			// 初始时，
			// nPos == nSize，孩子不存在，无需额外处理，此时算法成立。
			// 对输入nIndex
			// 依据数学归纳法，
			// 对所有较小规模执行算法，结论均成立
			// 1. 若k位置元素小于其可能存在的左孩子，右孩子元素
			// 无需处理。
			// 此时，结合算法前提，可知结论成立。
			// 2. 若k位置元素 比起左孩子，或右孩子大
			// 让孩子中最小的元素 和 k位置元素交换位置
			// 交换后，对k位置，满足位置约束
			// 对换入k位置元素的位置t， 该位置的元素相比原来变大了
			// 对t位置而言，
			// [t+1, nSize]区间内任意元素均满足 位置约束
			// 我们希望通过改变[t, nSize]内元素位置使[t, nSize]区间内任意元素均满足 位置约束
			// 依据数学归纳法，结论成立。
			template <typename T>
			void MinHeap<T>::Adjust(int nIndex_)
			{
				T _nV = m_arrElements[nIndex_];
				int _nL = nIndex_ * 2;
				int _nR = _nL + 1;
				T _nMin = m_arrElements[nIndex_];
				int _nMinPos = nIndex_;
				if (_nL < m_arrElements.GetSize()
					&& m_arrElements[_nL] < _nMin)
				{
					_nMin = m_arrElements[_nL];
					_nMinPos = _nL;
				}

				if (_nR < m_arrElements.GetSize()
					&& m_arrElements[_nR] < _nMin)
				{
					_nMin = m_arrElements[_nR];
					_nMinPos = _nR;
				}

				if (_nMinPos == nIndex_)
				{
					// do nothing
				}
				else
				{
					m_arrElements[nIndex_] = _nMin;
					m_arrElements[_nMinPos] = _nV;
					Adjust(_nMinPos);
				}
			}

			template <typename T>
			void MinHeap<T>::Add(const T& nT_)
			{
				// 实际元素个数
				int _nSize = m_arrElements.GetSize() - 1;
				if (_nSize < 0)
				{
					m_arrElements.Add(T());
					m_arrElements.Add(nT_);
					return;
				}

				if (_nSize == 0)
				{
					m_arrElements.Add(nT_);
					return;
				}

				// 新元素索引
				if ((_nSize + 1) % 2 == 0)
				{
					T _nPV = m_arrElements[(_nSize + 1) % 2];
					m_arrElements.Add(_nPV);// 添加元素取其父亲值
				}
				else
				{
					m_arrElements.Add(m_arrElements[_nSize]);// 添加元素取其兄弟值
				}

				// 将添加位置元素设置为指定值
				if (nT_ < m_arrElements[_nSize + 1])
				{
					m_arrElements[_nSize + 1] = nT_;
					Smaller(_nSize + 1);
				}
				else if (nT_ > m_arrElements[_nSize + 1])
				{
					m_arrElements[_nSize + 1] = nT_;
					Bigger(_nSize + 1);
				}
				else
				{
					// do nothing
				}
			}

			// 算法前提/背景：
			// 本来区间[1, nSize]内所有位置均满足位置约束
			// 现在nPos位置元素变小了，导致此位置可能不满足位置约束
			// 算法目标：
			// 通过对[1, nSize]各个元素进行位置调整，使区间[1, nSize]内所有位置均满足位置约束
			template <typename T>
			void MinHeap<T>::Smaller(int nPos_)
			{
				// 对以nPos为根子树而言，nPos变小，不会破坏子树各个节点的 已经满足的位置约束。
				if (nPos_ == 1)
				{
					return;
				}

				int _nP = nPos_ / 2;
				if (m_arrElements[_nP] <= m_arrElements[nPos_])
				{
					return;
				}
				else
				{
					T _nV = m_arrElements[_nP];
					m_arrElements[_nP] = m_arrElements[nPos_];// 父节点变小了。
					m_arrElements[nPos_] = _nV;// nPos位置虽然变大了。但新的值仍然小于改变前的值。故意nPos为根子树各个节点仍然满足 位置约束。
					
					// 目前要求解问题：
					// 本来区间[1, nSize]内所有位置均满足位置约束
					// 现在_nP位置元素变小了，导致此位置可能不满足位置约束
					// 希望通过对[1, nSize]各个元素进行位置调整，使区间[1, nSize]内所有位置均满足位置约束
					// 这是和原问题同类型的问题

					// 我们认为以_nP调用Smaller相比以nPos_调用Smaller，是一个更小规模的问题
					Smaller(_nP);
				}
			}

			// 算法前提/背景：
			// 本来区间[1, nSize]内所有位置均满足位置约束
			// 现在nPos位置元素变大了，导致此位置可能不满足位置约束
			// 算法目标：
			// 通过对[1, nSize]各个元素进行位置调整，使区间[1, nSize]内所有位置均满足位置约束
			template <typename T>
			void MinHeap<T>::Bigger(int nPos_)
			{
				int _nL = 2 * nPos_;
				int _nR = _nL + 1;
				T _nV = m_arrElements[nPos_];
				T _nMin = m_arrElements[nPos_];
				int _nMinPos = nPos_;
				if (_nL < m_arrElements.GetSize()
					&& m_arrElements[_nL] < _nMin)
				{
					_nMin = m_arrElements[_nL];
					_nMinPos = _nL;
				}

				if (_nR < m_arrElements.GetSize()
					&& m_arrElements[_nR] < _nMin)
				{
					_nMin = m_arrElements[_nR];
					_nMinPos = _nR;
				}

				if (_nMinPos == nPos_)
				{
					return;
				}
				else
				{
					m_arrElements[nPos_] = _nMin;// nPos位置换入一个较小的值。此值不会破坏nPos所有祖先节点的位置约束。
					m_arrElements[_nMinPos] = _nV;// _nMinPos换入一个较大的值
					// 目前要求解问题：
					// 本来区间[1, nSize]内所有位置均满足位置约束
					// 现在_nMinPos位置元素变大了，导致此位置可能不满足位置约束
					// 希望通过对[1, nSize]各个元素进行位置调整，使区间[1, nSize]内所有位置均满足位置约束
					// 这是和原问题同类型的问题

					// 我们认为以_nMinPos调用Bigger相比以nPos_调用Bigger，是一个更小规模的问题
					Bigger(_nMinPos);
				}
			}

			template <typename T>
			void MinHeap<T>::Delete(int nIndex_)
			{
				int _nSize = m_arrElements.GetSize() - 1;
				if (nIndex_ > _nSize
					|| nIndex_ < 1)
				{
					return;
				}

				if (_nSize == 1)
				{
					m_arrElements.DeleteByIndex(nIndex_);
					return;
				}

				m_arrElements[nIndex_] = m_arrElements[1] - 1;// 变得比最小还小
				Smaller(nIndex_);// 调节后，原nIndex位置元素必位于索引为1位置
				m_arrElements[1] = m_arrElements[_nSize];
				m_arrElements.DeleteByIndex(_nSize);
				Bigger(1);
			}

			// 查找---需要逐个比较
			template <typename T>
			void MinHeap<T>::Set(int nIndex_, const T& nV_)
			{
				if (nIndex_ < 1
					|| nIndex_ >= m_arrElements.GetSize())
				{
					return;
				}

				if (m_arrElements[nIndex_] < nV_)
				{
					m_arrElements[nIndex_] = nV_;
					Bigger(nIndex_);
				}
				else if (m_arrElements[nIndex_] > nV_)
				{
					m_arrElements[nIndex_] = nV_;
					Smaller(nIndex_);
				}
				else
				{
					// do nothing
				}
			}

			template <typename T>
			T MinHeap<T>::Get(int nIndex_)
			{
				return m_arrElements[nIndex_];
			}

			template <typename T>
			int MinHeap<T>::Find(std::function<bool(const T& nT_)> fun_)
			{
				int _nSize = m_arrElements.GetSize();
				for (int _i = 1; _i < _nSize; _i++)
				{
					if (fun_(m_arrElements[_i]))
					{
						return _i;
					}
				}

				return -1;
			}

			template <typename T>
			int MinHeap<T>::GetSize()
			{
				return m_arrElements.GetSize();
			}
		}
	}
}
#endif
