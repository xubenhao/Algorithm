//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef ALLIB_DATASTRUCT_LIST_DOUBLELIST_H
#define ALLIB_DATASTRUCT_LIST_DOUBLELIST_H
#include "..\..\stdafx.h"

namespace AlLib
{
	namespace DataStruct
	{
		namespace List
		{
			template <typename T>
			class DoubleList
			{
			public:
				class Node
				{
				public:
					T GetValue() const
					{
						return m_nValue;
					}

					void SetValue(const T& nValue_)
					{
						m_nValue = nValue_;
					}

				private:
					Node()
					{
						m_pPre = nullptr;
						m_pNext = nullptr;
					}

					~Node()
					{
					}

					T m_nValue;
					Node *m_pPre;
					Node *m_pNext;

					friend class DoubleList < T >;
				};

				DoubleList();
				// 拷贝构造
				DoubleList(const DoubleList& list_);
				// 赋值
				DoubleList<T>& operator=(const DoubleList& list_);
				virtual ~DoubleList();

				// 判空
				bool IsEmpty() const;
				// 容量
				int GetSize() const;

				// 插入：
				// 插入元素成为首元素
				void InsertFirst(const T& nNewValue_);
				// 插入元素成为尾元素
				void InsertLast(const T& nNewValue_);
				// 插入元素成为尾元素
				void Add(const T& nNewValue_);
				// 在指定元素前面插入
				void InsertBefore(Node* pElement_, const T& nNewValue_);
				// 在指定元素后面插入
				void InsertAfter(Node* pElement_, const T& nNewValue_);

				// 删除
				// 删除首元素
				void DeleteFirst();
				// 删除尾元素
				void DeleteLast();
				// 删除指定位置元素
				void Delete(Node* pElement_);
				// 删除指定值的首个元素
				void Delete(const T& nValue_);

				// 元素访问：
				// 获取首个元素
				Node* GetFirst() const;
				// 获取尾部元素
				Node* GetLast() const;
				// 搜索
				Node* Find(std::function<bool(const T&)> predictFunction_) const;

				// 容器遍历：
				// 获取输入元素下一元素
				Node* GetNext(Node* pElement_) const;
				// 获取输入元素上一元素
				Node* GetPre(Node* pElement_) const;

			private:
				Node *m_pFirst;
				Node *m_pLast;
			};

			template<typename T>
			DoubleList<T>::DoubleList() :
				m_pFirst(nullptr), m_pLast(nullptr)
			{
			}

			template<typename T>
			DoubleList<T>::~DoubleList()
			{
				// 保证：
				// 非空时，尾元素下一元素指针为空。
				// 为空时，m_pBegin,m_pEnd均为null。
				Node *_pCur = m_pFirst;
				while (_pCur)
				{
					Node* _pTemp = _pCur;
					_pCur = _pCur->m_pNext;
					delete _pTemp;
					_pTemp = nullptr;
				}

				m_pFirst = nullptr;
				m_pLast = nullptr;
			}

			template<typename T>
			DoubleList<T>::DoubleList(const DoubleList& list_) :
				m_pFirst(nullptr), m_pLast(nullptr)
			{
				Node *_pCur = list_.m_pFirst;
				while (_pCur)
				{
					Node* _pTemp = _pCur;
					_pCur = _pCur->m_pNext;
					Add(_pTemp->GetValue());
				}
			}

			template<typename T>
			typename DoubleList<T>& DoubleList<T>::operator=(const DoubleList& list_)
			{
				if (this == &list_)
				{
					return *this;
				}

				this->~DoubleList();
				// 假定：
				Node *_pCur = list_.m_pFirst;
				while (_pCur)
				{
					Node* _pTemp = _pCur;
					_pCur = _pCur->m_pNext;
					Add(_pTemp->GetValue());
				}
			}

			template<typename T>
			bool DoubleList<T>::IsEmpty() const
			{
				if (m_pFirst == nullptr)
				{
					assert(m_pLast == nullptr);
					return true;
				}
				else
				{
					return false;
				}
			}

			template<typename T>
			int DoubleList<T>::GetSize() const
			{
				Node *_pCur = m_pFirst;
				int _nSize = 0;
				while (_pCur)
				{
					_nSize++;
					_pCur = _pCur->m_pNext;
				}

				return _nSize;
			}

			template<typename T>
			void DoubleList<T>::InsertFirst(const T& nNewValue_)
			{
				Node *_pElement = nullptr;
				try
				{
					_pElement = new Node();
				}
				catch (...)
				{
					_pElement = nullptr;
					throw "out of memory";
				}

				_pElement->SetValue(nNewValue_);
				if (IsEmpty() == true)
				{
					m_pFirst = _pElement;
					m_pLast = _pElement;
				}
				else
				{
					_pElement->m_pNext = m_pFirst;
					m_pFirst->m_pPre = _pElement;
					m_pFirst = _pElement;
				}
			}

			template<typename T>
			void DoubleList<T>::InsertLast(const T& nNewValue_)
			{
				Node *_pElement = nullptr;
				try
				{
					_pElement = new Node();
				}
				catch (...)
				{
					_pElement = nullptr;
					throw "out of memory";
				}

				_pElement->SetValue(nNewValue_);
				if (IsEmpty() == true)
				{
					m_pFirst = _pElement;
					m_pLast = _pElement;
				}
				else
				{
					m_pLast->m_pNext = _pElement;
					_pElement->m_pPre = m_pLast;
					m_pLast = _pElement;
				}
			}

			template<typename T>
			void DoubleList<T>::Add(const T& nNewValue_)
			{
				InsertLast(nNewValue_);
			}

			template<typename T>
			void DoubleList<T>::InsertBefore(Node* pElement_, const T& nNewValue_)
			{
				if (pElement_ == nullptr)
				{
					return;
				}

				Node* _pPre = pElement_->m_pPre;
				if (_pPre == nullptr)
				{
					InsertFirst(nNewValue_);
				}
				else
				{
					Node *_pNewElement = nullptr;
					try
					{
						_pNewElement = new Node();
					}
					catch (...)
					{
						_pNewElement = nullptr;
						throw "out of memory";
					}

					_pNewElement->SetValue(nNewValue_);
					_pPre->m_pNext = _pNewElement;
					_pNewElement->m_pPre = _pPre;

					pElement_->m_pPre = _pNewElement;
					_pNewElement->m_pNext = pElement_;
				}
			}

			template<typename T>
			void DoubleList<T>::InsertAfter(Node* pElement_, const T& nNewValue_)
			{
				if (pElement_ == nullptr)
				{
					return;
				}

				Node* _pNext = pElement_->m_pNext;
				if (_pNext == nullptr)
				{
					InsertLast(nNewValue_);
				}
				else
				{
					Node *_pNewElement = nullptr;
					try
					{
						_pNewElement = new Node();
					}
					catch (...)
					{
						_pNewElement = nullptr;
						throw "out of memory";
					}

					_pNewElement->SetValue(nNewValue_);
					pElement_->m_pNext = _pNewElement;
					_pNewElement->m_pPre = pElement_;

					_pNext->m_pPre = _pNewElement;
					_pNewElement->m_pNext = _pNext;
				}
			}

			template<typename T>
			void DoubleList<T>::DeleteFirst()
			{
				if (IsEmpty())
				{
					return;
				}
				else if (m_pFirst == m_pLast && m_pFirst != nullptr)
				{
					delete m_pFirst;
					m_pFirst = nullptr;
					m_pLast = nullptr;
				}
				else
				{
					Node* _pDelete = m_pFirst;
					m_pFirst = _pDelete->m_pNext;
					m_pFirst->m_pPre = nullptr;
					delete _pDelete;
					_pDelete = nullptr;
				}
			}

			template<typename T>
			void DoubleList<T>::DeleteLast()
			{
				if (IsEmpty())
				{
					return;
				}
				else if (m_pFirst == m_pLast && m_pFirst != nullptr)
				{
					delete m_pFirst;
					m_pFirst = nullptr;
					m_pLast = nullptr;
				}
				else
				{
					Node* _pDelete = m_pLast;
					m_pLast = m_pLast->m_pPre;
					m_pLast->m_pNext = nullptr;
					delete _pDelete;
					_pDelete = nullptr;
				}
			}

			template<typename T>
			void DoubleList<T>::Delete(Node* pElement_)
			{
				if (pElement_ == nullptr)
				{
					return;
				}

				Node* _pPre = pElement_->m_pPre;
				Node* _pNext = pElement_->m_pNext;
				if (_pPre == nullptr)
				{
					DeleteFirst();
				}
				else if (_pNext == nullptr)
				{
					DeleteLast();
				}
				else
				{
					_pPre->m_pNext = _pNext;
					_pNext->m_pPre = _pPre;
					delete pElement_;
					pElement_ = nullptr;
				}
			}

			template<typename T>
			void DoubleList<T>::Delete(const T& nValue_)
			{
				Node* _pDeletedElement = Find([nValue_](const T& nT_)->bool
				{
					if (nT_ == nValue_)
					{
						return true;
					}
					else
					{
						return false;
					}
				});

				Delete(_pDeletedElement);
			}

			template<typename T>
			typename DoubleList<T>::Node* DoubleList<T>::GetFirst() const
			{
				return m_pFirst;
			}

			template<typename T>
			typename DoubleList<T>::Node* DoubleList<T>::GetLast() const
			{
				return m_pLast;
			}

			template<typename T>
			typename DoubleList<T>::Node* DoubleList<T>::Find(std::function<bool(const T&)> predictFunction_) const
			{
				Node *_pCur = m_pFirst;
				while (_pCur)
				{
					if (predictFunction_(_pCur->GetValue()) == true)
					{
						break;
					}

					_pCur = _pCur->m_pNext;
				}

				return _pCur;
			}

			template<typename T>
			typename DoubleList<T>::Node* DoubleList<T>::GetNext(Node* pElement_) const
			{
				if (pElement_ == nullptr)
				{
					return nullptr;
				}

				return pElement_->m_pNext;
			}

			template<typename T>
			typename DoubleList<T>::Node* DoubleList<T>::GetPre(Node* pElement_) const
			{
				if (pElement_ == nullptr)
				{
					return nullptr;
				}

				return pElement_->m_pPre;
			}
		}
	}
}
#endif


