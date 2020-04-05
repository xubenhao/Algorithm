//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef ALLIB_DATASTRUCT_ARRAY_DYNARRAY_H
#define ALLIB_DATASTRUCT_ARRAY_DYNARRAY_H
#include "..\..\stdafx.h"
#include "..\..\Algorithm\Sort\Sort.h"

namespace AlLib
{
	namespace DataStruct
	{
		namespace Array
		{
			// 突破固定容量数组限制
			// 容量可以动态增加和减少的数组
			// 适合作为管理动态元素集合的容器
			template<typename T>
			class DynArray
			{
			public:
				DynArray();
				DynArray(int nInitialSize_, const T& nInitialValue_);
				~DynArray();

				void Add(const T& value_);
				void AddRange(const DynArray& arrItems_);
				void Insert(int nIndex_, const T& value_);
				void DeleteByIndex(int nIndex_ = -1);
				void DeleteByValue(const T& value_);
				void DeleteAll();
				bool SetValue(int nIndex_, const T& value_);
				bool GetValue(int nIndex_, T& value_) const;

				int GetSize() const;
				int GetCapacity() const;
				int Find(std::function<bool(const T&)> fun_) const;

				T& operator[](int nIndex_);
				const T& operator[](int nIndex_) const;
				DynArray(const DynArray<T>& arrElements_);
				DynArray<T>& operator=(const DynArray<T>& arrElements_);
				DynArray Sort(std::function<int(const T&, const T&)> fun_ = [](const T& nT1_, const T& nT2_)->int
				{
					if (nT1_ < nT2_)
					{
						return -1;
					}
					else if (nT1_ > nT2_)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}) const;
				void Sort(std::function<int(const T&, const T&)> fun_ = [](const T& nT1_, const T& nT2_)->int
				{
					if (nT1_ < nT2_)
					{
						return -1;
					}
					else if (nT1_ > nT2_)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				});

				void Reset();
			private:
				void Check(int nSize_);
				void Shrink();

			private:
				T* m_pSource;// 当T为引用类型时，sizeof无法获得其真实大小
				int m_nSize;
				int m_nCapacity;

				std::allocator<T> m_alloc;
			};

			template<typename T>
			DynArray<T>::DynArray(const DynArray<T>& arrElements_)
				: m_pSource(nullptr), m_nSize(0), m_nCapacity(0)
			{
				m_pSource = m_alloc.allocate(arrElements_.m_nCapacity);
				if (m_pSource == nullptr)
				{
					throw "out of memory";
				}
				else
				{
					m_nSize = arrElements_.m_nSize;
					m_nCapacity = arrElements_.m_nCapacity;
					std::uninitialized_copy_n(arrElements_.m_pSource, arrElements_.m_nSize, m_pSource);
				}
			}

			template<typename T>
			DynArray<T>& DynArray<T>::operator=(const DynArray<T>& arrElements_)
			{
				if (&arrElements_ == this)
				{
					return *this;
				}

				this->~DynArray();
				m_pSource = m_alloc.allocate(arrElements_.m_nCapacity);
				if (m_pSource == nullptr)
				{
					throw "out of memory";
				}
				else
				{
					m_nSize = arrElements_.m_nSize;
					m_nCapacity = arrElements_.m_nCapacity;
					std::uninitialized_copy_n(arrElements_.m_pSource, arrElements_.m_nSize, m_pSource);
				}

				return *this;
			}

			template<typename T>
			int DynArray<T>::Find(std::function<bool(const T&)> fun_) const
			{
				int _nPosIndex = -1;
				for (int _i = 0; _i < m_nSize; _i++)
				{
					if (fun_(*(m_pSource + _i)))
					{
						_nPosIndex = _i;
						break;
					}
				}

				return _nPosIndex;
			}

			template<typename T>
			DynArray<T>::DynArray()
				:m_pSource(nullptr), m_nSize(0), m_nCapacity(0)
			{
				m_pSource = m_alloc.allocate(100);
				if (m_pSource == nullptr)
				{
					throw "out of memory";
				}
				else
				{
					m_nSize = 0;
					m_nCapacity = 100;
				}
			}

			template<typename T>
			DynArray<T>::DynArray(int nInitialSize_, const T& nInitialValue_)
				:m_pSource(nullptr), m_nSize(0), m_nCapacity(0)
			{
				m_pSource = m_alloc.allocate(nInitialSize_ * 2);
				if (m_pSource == nullptr)
				{
					throw "out of memory";
				}
				else
				{
					m_nSize = nInitialSize_;
					m_nCapacity = nInitialSize_ * 2;
					std::uninitialized_fill_n(m_pSource, m_nSize, nInitialValue_);
				}
			}

			template<typename T>
			void DynArray<T>::Reset()
			{
				this->~DynArray();
				m_pSource = m_alloc.allocate(100);
				if (m_pSource == nullptr)
				{
					throw "out of memory";
				}
				else
				{
					m_nSize = 0;
					m_nCapacity = 100;
				}
			}

			template<typename T>
			DynArray<T>::~DynArray()
			{
				if (m_pSource == nullptr)
				{
					return;
				}

				T* _pEnd = m_pSource + m_nSize;
				while (_pEnd != m_pSource)
				{
					m_alloc.destroy(--_pEnd);
				}

				// 内存释放
				m_alloc.deallocate(m_pSource, m_nCapacity);
				m_pSource = nullptr;
				m_nSize = 0;
				m_nCapacity = 0;
				m_pSource = m_alloc.allocate(100);
				if (m_pSource == nullptr)
				{
					throw "out of memory";
				}
				else
				{
					m_nSize = 0;
					m_nCapacity = 100;
				}
			}

			template<typename T>
			void DynArray<T>::Add(const T& value_)
			{
				Check(m_nSize + 1);
				T* _pEnd = m_pSource + m_nSize;
				m_alloc.construct(_pEnd, value_);
				m_nSize++;
			}

			template<typename T>
			void DynArray<T>::AddRange(const DynArray& arrItems_)
			{
				Check(m_nSize + arrItems_.GetSize());
				for (int _i = 0; _i < arrItems_.m_nSize; _i++)
				{
					m_alloc.construct(m_pSource + m_nSize + _i, *(arrItems_.m_pSource + _i));
				}

				m_nSize += arrItems_.m_nSize;
			}

			template<typename T>
			void DynArray<T>::Check(int nSize_)
			{
				if (m_nCapacity >= nSize_)
				{
					return;
				}

				int _nSize = m_nSize;
				int _nCapacity = nSize_ * 2;
				T* _pSource = m_alloc.allocate(_nCapacity);
				if (_pSource == nullptr)
				{
					throw "out of memory";
				}
				else
				{
					std::uninitialized_copy_n(m_pSource, m_nSize, _pSource);
					this->~DynArray();
					m_pSource = _pSource;
					m_nSize = _nSize;
					m_nCapacity = _nCapacity;
				}
			}

			template<typename T>
			void DynArray<T>::Insert(int nIndex_, const T& value_)
			{
				if (nIndex_ > m_nSize)
				{
					throw "Insert position error";
				}

				Check(m_nSize + 1);
				m_alloc.construct(m_pSource + m_nSize, value_);
				m_nSize++;

				for (int _i = m_nSize - 1; _i >= nIndex_; _i--)
				{
					*(m_pSource + _i + 1) = *(m_pSource + _i);
				}

				*(m_pSource + nIndex_) = value_;
			}

			template<typename T>
			void DynArray<T>::DeleteByIndex(int nIndex_)
			{
				if (nIndex_ < 0
					|| nIndex_ >= m_nSize)
				{
					return;
				}

				// 前移
				for (int _i = nIndex_ + 1; _i < m_nSize; _i++)
				{
					*(m_pSource + _i - 1) = *(m_pSource + _i);
				}

				m_alloc.destroy(m_pSource + m_nSize);
				m_nSize--;
				if (m_nSize <= m_nCapacity / 4)
				{
					Shrink();
				}
			}

			template<typename T>
			void DynArray<T>::DeleteByValue(const T& value_)
			{
				int _nIndex = Find([value_](const T& nT_)->bool
				{
					if (nT_ == value_)
					{
						return true;
					}
					else
					{
						return false;
					}
				});

				if (_nIndex == -1)
				{
					return;
				}

				DeleteByIndex(_nIndex);
			}

			template<typename T>
			void DynArray<T>::Shrink()
			{
				int _nSize = m_nSize;
				int _nCapacity = (m_nCapacity / 2) > 100 ? (m_nCapacity / 2) : 100;
				T* _pSource = m_alloc.allocate(_nCapacity);
				if (_pSource == nullptr)
				{
					throw "out of memory";
				}
				else
				{
					std::uninitialized_copy_n(m_pSource, m_nSize, _pSource);
					this->~DynArray();
					m_pSource = _pSource;
					m_nSize = _nSize;
					m_nCapacity = _nCapacity;
				}
			}

			template<typename T>
			void DynArray<T>::DeleteAll()
			{
				Reset();
			}

			template<typename T>
			bool DynArray<T>::SetValue(int nIndex_, const T& value_)
			{
				if (nIndex_ < 0
					|| nIndex_ >= m_nSize)
				{
					return false;
				}

				*(m_pSource + nIndex_) = value_;
				return true;
			}

			template<typename T>
			bool DynArray<T>::GetValue(int nIndex_, T& value_) const
			{
				if (nIndex_ < 0
					|| nIndex_ >= m_nSize)
				{
					return false;
				}

				value_ = *(m_pSource + nIndex_);
				return true;
			}

			template<typename T>
			int DynArray<T>::GetSize() const
			{
				return m_nSize;
			}

			template<typename T>
			int DynArray<T>::GetCapacity() const
			{
				return m_nCapacity;
			}

			template<typename T>
			T& DynArray<T>::operator[](int nIndex_)
			{
				if (nIndex_ < 0
					|| nIndex_ >= m_nSize)
				{
					throw "index is error";
				}

				return *(m_pSource + nIndex_);
			}

			template<typename T>
			const T& DynArray<T>::operator[](int nIndex_) const
			{
				if (nIndex_ < 0
					|| nIndex_ >= m_nSize)
				{
					throw "index is error";
				}

				return *(m_pSource + nIndex_);
			}

			template<typename T>
			typename DynArray<T> DynArray<T>::Sort(std::function<int(const T&, const T&)> fun_) const
			{
				DynArray _arr = *this;
				if (m_nSize <= 1)
				{
					return _arr;
				}

				Algorithm::Sort::Helper::QuickSort<T>(_arr.m_pSource,
					_arr.m_pSource + m_nSize,
					fun_)
					return _arr;
			}

			template<typename T>
			void DynArray<T>::Sort(std::function<int(const T&, const T&)> fun_)
			{
				if (m_nSize <= 1)
				{
					return;
				}

				Algorithm::Sort::Helper::QuickSort<T>(m_pSource,
					m_pSource + m_nSize,
					fun_);
					return;
			}
		}
	}
}
#endif



