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
			// ��С�Ѷ��壺
			// ����
			// ����Ԫ��˳��洢����1Ϊ��ʼ������������
			// ����������Ϊi��Ԫ��A
			// ������Ϊ2*i, 2*i+1λ��Ԫ�ش��ڣ���ΪB��C
			// �ƣ�BΪA���ӣ�CΪA�Һ��ӡ�
			// ��λ��k��Ԫ�ص�ֵΪV[k]
			// �� V[i] <= V[2*i] && V[i] <= V[2*i+1]
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

			// �㷨Ŀ��
			// ���룺����ĺ�n��Ԫ�ص�����
			// �㷨Ŀ�꣺
			// ����������n��Ԫ���Է�����С�Ѷ���ķ�ʽ�洢��m_arrElements������1,...,n��
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
				
				// ѭ������ʽ��
				// ����[_i+1, _nSize]�ڸ���Ԫ�ؾ����㣬
				// ������������λ��k��Ԫ�أ�������λ��Լ��
				// ��2*kλ��Ԫ�ش��ڣ�����V[k] <= V[2*k]
				// ��2*k+1λ��Ԫ�ش��ڣ�����V[k] <= V[2*k+1]

				// ֤����
				// ��ʼʱ������Ϊ[_nSize+1, _nSize]Ϊ�� ���䣬ѭ������ʽ����
				// ��_i = k�ĵ���
				// ����ѭ������ʽ������ѭ������ǰ�ĸ���������ѭ������ʽ�����㡿
				// ����_i > k�ĵ��������ѭ������ʽ������

				// ����Adjust(int nIndex_)�����ڱ�֤ [nIndex_+1, nSize]����������Ԫ�ؾ����� λ��Լ��ǰ���£�ִ�к󣬿�ʵ��
				// [nPos, nSize]����������Ԫ�ؾ����� λ��Լ����Ч����
				// ���ԣ���_i = k��������
				// [k, _nSize]����������Ԫ�ؾ����� λ��Լ����
				// ѭ������ʽ����
				for (int _i = _nSize; _i >= 1; _i--)
				{
					Adjust(_i);
				}
			}

			// �㷨���룺λ������nPos
			// �㷨ǰ�᣺[nPos+1, nSize]����������Ԫ�ؾ����� λ��Լ��
			// �㷨Ŀ�꣺
			// �㷨ͨ���ı�[nPos, nSize]��Ԫ��λ�ã�ִ�к�ʹ[nPos, nSize]����������Ԫ�ؾ����� λ��Լ��

			// ��ȷ��֤������ѧ���ɷ�����
			// ��ʼʱ��
			// nPos == nSize�����Ӳ����ڣ�������⴦����ʱ�㷨������
			// ������nIndex
			// ������ѧ���ɷ���
			// �����н�С��ģִ���㷨�����۾�����
			// 1. ��kλ��Ԫ��С������ܴ��ڵ����ӣ��Һ���Ԫ��
			// ���账��
			// ��ʱ������㷨ǰ�ᣬ��֪���۳�����
			// 2. ��kλ��Ԫ�� �������ӣ����Һ��Ӵ�
			// �ú�������С��Ԫ�� �� kλ��Ԫ�ؽ���λ��
			// �����󣬶�kλ�ã�����λ��Լ��
			// �Ի���kλ��Ԫ�ص�λ��t�� ��λ�õ�Ԫ�����ԭ�������
			// ��tλ�ö��ԣ�
			// [t+1, nSize]����������Ԫ�ؾ����� λ��Լ��
			// ����ϣ��ͨ���ı�[t, nSize]��Ԫ��λ��ʹ[t, nSize]����������Ԫ�ؾ����� λ��Լ��
			// ������ѧ���ɷ������۳�����
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
				// ʵ��Ԫ�ظ���
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

				// ��Ԫ������
				if ((_nSize + 1) % 2 == 0)
				{
					T _nPV = m_arrElements[(_nSize + 1) % 2];
					m_arrElements.Add(_nPV);// ���Ԫ��ȡ�丸��ֵ
				}
				else
				{
					m_arrElements.Add(m_arrElements[_nSize]);// ���Ԫ��ȡ���ֵ�ֵ
				}

				// �����λ��Ԫ������Ϊָ��ֵ
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

			// �㷨ǰ��/������
			// ��������[1, nSize]������λ�þ�����λ��Լ��
			// ����nPosλ��Ԫ�ر�С�ˣ����´�λ�ÿ��ܲ�����λ��Լ��
			// �㷨Ŀ�꣺
			// ͨ����[1, nSize]����Ԫ�ؽ���λ�õ�����ʹ����[1, nSize]������λ�þ�����λ��Լ��
			template <typename T>
			void MinHeap<T>::Smaller(int nPos_)
			{
				// ����nPosΪ���������ԣ�nPos��С�������ƻ����������ڵ�� �Ѿ������λ��Լ����
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
					m_arrElements[_nP] = m_arrElements[nPos_];// ���ڵ��С�ˡ�
					m_arrElements[nPos_] = _nV;// nPosλ����Ȼ����ˡ����µ�ֵ��ȻС�ڸı�ǰ��ֵ������nPosΪ�����������ڵ���Ȼ���� λ��Լ����
					
					// ĿǰҪ������⣺
					// ��������[1, nSize]������λ�þ�����λ��Լ��
					// ����_nPλ��Ԫ�ر�С�ˣ����´�λ�ÿ��ܲ�����λ��Լ��
					// ϣ��ͨ����[1, nSize]����Ԫ�ؽ���λ�õ�����ʹ����[1, nSize]������λ�þ�����λ��Լ��
					// ���Ǻ�ԭ����ͬ���͵�����

					// ������Ϊ��_nP����Smaller�����nPos_����Smaller����һ����С��ģ������
					Smaller(_nP);
				}
			}

			// �㷨ǰ��/������
			// ��������[1, nSize]������λ�þ�����λ��Լ��
			// ����nPosλ��Ԫ�ر���ˣ����´�λ�ÿ��ܲ�����λ��Լ��
			// �㷨Ŀ�꣺
			// ͨ����[1, nSize]����Ԫ�ؽ���λ�õ�����ʹ����[1, nSize]������λ�þ�����λ��Լ��
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
					m_arrElements[nPos_] = _nMin;// nPosλ�û���һ����С��ֵ����ֵ�����ƻ�nPos�������Ƚڵ��λ��Լ����
					m_arrElements[_nMinPos] = _nV;// _nMinPos����һ���ϴ��ֵ
					// ĿǰҪ������⣺
					// ��������[1, nSize]������λ�þ�����λ��Լ��
					// ����_nMinPosλ��Ԫ�ر���ˣ����´�λ�ÿ��ܲ�����λ��Լ��
					// ϣ��ͨ����[1, nSize]����Ԫ�ؽ���λ�õ�����ʹ����[1, nSize]������λ�þ�����λ��Լ��
					// ���Ǻ�ԭ����ͬ���͵�����

					// ������Ϊ��_nMinPos����Bigger�����nPos_����Bigger����һ����С��ģ������
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

				m_arrElements[nIndex_] = m_arrElements[1] - 1;// ��ñ���С��С
				Smaller(nIndex_);// ���ں�ԭnIndexλ��Ԫ�ر�λ������Ϊ1λ��
				m_arrElements[1] = m_arrElements[_nSize];
				m_arrElements.DeleteByIndex(_nSize);
				Bigger(1);
			}

			// ����---��Ҫ����Ƚ�
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
