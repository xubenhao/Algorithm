//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef ALLIB_DATASTRUCT_HASH_LISTHASH_H
#define ALLIB_DATASTRUCT_HASH_LISTHASH_H
#include "..\..\stdafx.h"
#include "..\Array\DynArray.h"
#include "..\List\DoubleList.h"
namespace AlLib
{
	namespace DataStruct
	{
		namespace Hash
		{
			template<typename Key, typename Value>
			class ListHash
			{
			public:
				class Pair
				{
				public:
					Pair()
					{
					}

					Pair(const Key& nKey_, const Value& nValue_)
					{
						m_nKey = nKey_;
						m_nValue = nValue_;
					}

					~Pair()
					{
					}
				public:
					Key m_nKey;
					Value m_nValue;
				};

			public:
				ListHash(int nSoltNums_, 
					std::function<int(const Key&, int)> hashFun_ = [](const Key& nKey_, int nSlotsNum_)->int
				{
					return (nKey_ % nSlotsNum_);
				});
				~ListHash();
				ListHash(const ListHash& hash_);
				ListHash& operator=(const ListHash& hash_);

				void Insert(const Pair& nPair_);
				void Delete(const Key& nKey_);
				bool Search(const Key& nKey_, Value& nValue_) const;
			private:
				Array::DynArray<List::DoubleList<Pair>*> m_arrSlots;
				std::function<int(const Key&, int)> m_fHashFun;
			};

			template<typename Key, typename Value>
			ListHash<Key, Value>::ListHash(int nSoltNums_, std::function<int(const Key&, int)> hashFun_)
				:m_arrSlots(nSoltNums_, nullptr), m_fHashFun(hashFun_)
			{
				for (int _i = 0; _i < nSoltNums_; _i++)
				{
					List::DoubleList<Pair>* _pList = nullptr;
					try
					{
						_pList = new List::DoubleList<Pair>();
					}
					catch (...)
					{
						_pList = nullptr;
						throw "out of memory";
					}
					
					m_arrSlots[_i] = _pList;
				}
			}

			template<typename Key, typename Value>
			ListHash<Key, Value>::ListHash(const ListHash& hash_)
				: m_arrSlots(hash_.m_arrSlots.GetSize(), nullptr), m_fHashFun(hash_.m_fHashFun)
			{
				int _nSize = hash_.m_arrSlots.GetSize();
				for (int _i = 0; _i < _nSize; _i++)
				{
					List::DoubleList<Pair>* _pList = nullptr;
					try
					{
						_pList = new List::DoubleList<Pair>(hash_.m_arrSlots[_i]);
					}
					catch (...)
					{
						_pList = nullptr;
						throw "out of memory";
					}

					m_arrSlots[_i] = _pList;
				}
			}

			template<typename Key, typename Value>
			typename ListHash<Key, Value>& ListHash<Key, Value>::operator=(const ListHash& hash_)
			{
				if (this == &hash_)
				{
					return *this;
				}

				this->~ListHash();
				int _nSize = hash_.m_arrSlots.GetSize();
				m_arrSlots = Array::DynArray<List::DoubleList<Pair>*>(_nSize, nullptr);
				for (int _i = 0; _i < _nSize; _i++)
				{
					List::DoubleList<Pair>* _pList = nullptr;
					try
					{
						_pList = new List::DoubleList<Pair>(hash_.m_arrSlots[_i]);
					}
					catch (...)
					{
						_pList = nullptr;
						throw "out of memory";
					}

					m_arrSlots[_i] = _pList;
				}

				m_fHashFun = hash_.m_fHashFun;
				return *this;
			}

			template<typename Key, typename Value>
			ListHash<Key, Value>::~ListHash()
			{
				int _nSize = m_arrSlots.GetSize();
				for (int _i = 0; _i < _nSize; _i++)
				{
					delete m_arrSlots[_i];
					m_arrSlots[_i] = nullptr;
				}
			}

			template<typename Key, typename Value>
			void ListHash<Key, Value>::Insert(const Pair& nPair_)
			{
				int _nSize = m_arrSlots.GetSize();
				int _nIndex = m_fHashFun(nPair_.m_nKey, _nSize);
				List::DoubleList<Pair> *_pList = m_arrSlots[_i];
				_pList->Add(nPair_);
			}

			template<typename Key, typename Value>
			bool ListHash<Key, Value>::Search(const Key& nKey_, Value& nValue_) const
			{
				int _nSize = m_arrSlots.GetSize();
				int _nIndex = m_fHashFun(nKey_, _nSize);
				List::DoubleList<Pair> *_pList = m_arrSlots[_nIndex];
				List::DoubleList<Pair>::Node* _pNode = _pList->Find([nKey_](const Pair& nPair_)->bool
				{
					if (nPair_.m_nKey == nKey_)
					{
						return true;
					}
					else
					{
						return false;
					}
				});

				if (_pNode == nullptr)
				{
					return false;
				}
				else
				{
					Pair _nPair = _pNode->GetValue();
					nValue_ = _nPair.m_nValue;
					return true;
				}
			}

			template<typename Key, typename Value>
			void ListHash<Key, Value>::Delete(const Key& nKey_)
			{
				int _nSize = m_arrSlots.GetSize();
				int _nIndex = m_fHashFun(nKey_, _nSize);
				List::DoubleList<Pair> *_pList = m_arrSlots[_nIndex];
				List::DoubleList<Pair>::Node* _pNode = _pList->Find([nKey_](const Pair& nPair_)->bool
				{
					if (nPair_.m_nKey == nKey_)
					{
						return true;
					}
					else
					{
						return false;
					}
				});

				if (_pNode)
				{
					_pList->Delete(_pNode);
				}
			}
		}
	}
}
#endif
