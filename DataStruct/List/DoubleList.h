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
				// ��������
				DoubleList(const DoubleList& list_);
				// ��ֵ
				DoubleList<T>& operator=(const DoubleList& list_);
				virtual ~DoubleList();

				// �п�
				bool IsEmpty() const;
				// ����
				int GetSize() const;

				// ���룺
				// ����Ԫ�س�Ϊ��Ԫ��
				void InsertFirst(const T& nNewValue_);
				// ����Ԫ�س�ΪβԪ��
				void InsertLast(const T& nNewValue_);
				// ����Ԫ�س�ΪβԪ��
				void Add(const T& nNewValue_);
				// ��ָ��Ԫ��ǰ�����
				void InsertBefore(Node* pElement_, const T& nNewValue_);
				// ��ָ��Ԫ�غ������
				void InsertAfter(Node* pElement_, const T& nNewValue_);

				// ɾ��
				// ɾ����Ԫ��
				void DeleteFirst();
				// ɾ��βԪ��
				void DeleteLast();
				// ɾ��ָ��λ��Ԫ��
				void Delete(Node* pElement_);
				// ɾ��ָ��ֵ���׸�Ԫ��
				void Delete(const T& nValue_);

				// Ԫ�ط��ʣ�
				// ��ȡ�׸�Ԫ��
				Node* GetFirst() const;
				// ��ȡβ��Ԫ��
				Node* GetLast() const;
				// ����
				Node* Find(std::function<bool(const T&)> predictFunction_) const;

				// ����������
				// ��ȡ����Ԫ����һԪ��
				Node* GetNext(Node* pElement_) const;
				// ��ȡ����Ԫ����һԪ��
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
				// ��֤��
				// �ǿ�ʱ��βԪ����һԪ��ָ��Ϊ�ա�
				// Ϊ��ʱ��m_pBegin,m_pEnd��Ϊnull��
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
				// �ٶ���
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


