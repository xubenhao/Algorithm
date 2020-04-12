//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_DATASTRUCT_TREE_SORTEDBINARYTREE_H
#define AILIB_DATASTRUCT_TREE_SORTEDBINARYTREE_H
#include "..\..\stdafx.h"
#include "..\Array\DynArray.h"
namespace AlLib
{
	namespace DataStruct
	{
		namespace Tree
		{
			template<typename Key, typename Value>
			class SortedBinaryTree
			{
			public:
				class Pair
				{
				public:
					Pair()
					{
					}

					Pair(const Key& key_, const Value& value_)
					{
						m_nKey = key_;
						m_nValue = value_;
					}

					~Pair()
					{
					}

				public:
					Key m_nKey;
					Value m_nValue;
				};

				class Node
				{
				public:
					Value GetValue()
					{
						return m_nPair.m_nValue;
					}

					Key GetKey()
					{
						return m_nPair.m_nKey;
					}

					void SetValue(const Value& nValue_)
					{
						m_nPair.m_nValue = nValue_;
					}

					Pair GetPair()
					{
						return m_nPair;
					}

				private:
					Node()
					{
						m_pParent = nullptr;
						m_pLeftChild = nullptr;
						m_pRightChild = nullptr;
					}

					~Node()
					{
					}

				private:
					Node* m_pParent;
					Node* m_pLeftChild;
					Node* m_pRightChild;
					Pair m_nPair;
					friend class SortedBinaryTree;
				};

				SortedBinaryTree();
				~SortedBinaryTree();

				SortedBinaryTree(const SortedBinaryTree& minTree_);
				SortedBinaryTree& operator=(const SortedBinaryTree& minTree_);

				void PreVisit(std::function<void(Node*)> travelFunction_, Node* pRoot_ = nullptr) const;
				void PostVisit(std::function<void(Node*)> travelFunction_, Node* pRoot_ = nullptr) const;
				void Visit(std::function<void(Node*)> travelFunction_, Node* pRoot_ = nullptr) const;

				Node* Min(Node* pRoot_ = nullptr) const;
				Node* Max(Node* pRoot_ = nullptr) const;

				Node* Pre(Node *pNode_) const;
				Node* Suc(Node *pNode_) const;

				bool Search(const Key& key_, Value& value_, Node* pRoot_ = nullptr) const;
				Node* Search(const Key& key_, Node* pRoot_ = nullptr) const;
				bool Add(const Pair& nPair_);
				void Delete(const Key& key_, Node* pRoot_ = nullptr);
				void DeleteAll();

				Node* GetRoot() const;
				Array::DynArray<Pair> GetArray() const
				{
					Array::DynArray<Pair> _arrContain;
					PreVisit([&_arrContain](Node* pNode_)
					{
						_arrContain.Add(pNode_->m_nPair);
					});

					return _arrContain;
				}

			private:
				Node* m_pRoot;
			};

			template<typename Key, typename Value>
			SortedBinaryTree<Key, Value>::SortedBinaryTree()
			{
				m_pRoot = nullptr;
			}

			template<typename Key, typename Value>
			SortedBinaryTree<Key, Value>::~SortedBinaryTree()
			{
				Array::DynArray<Node*> _arrNodes;
				PreVisit([&_arrNodes](Node* pNode_)
				{
					_arrNodes.Add(pNode_);
				});

				int _nSize = _arrNodes.GetSize();
				for (int _i = 0; _i < _nSize; _i++)
				{
					delete _arrNodes[_i];
					_arrNodes[_i] = nullptr;
				}

				m_pRoot = nullptr;
			}

			template<typename Key, typename Value>
			void SortedBinaryTree<Key, Value>::PreVisit(
				std::function<void(Node*)> travelFunction_, 
				Node* pRoot_) const
			{
				Node *_pRoot = nullptr;
				if (pRoot_ == nullptr)
				{
					_pRoot = m_pRoot;
				}
				else
				{
					_pRoot = pRoot_;
				}

				if (_pRoot == nullptr)
				{
					return;
				}

				travelFunction_(_pRoot);
				if (_pRoot->m_pLeftChild != nullptr)
				{
					PreVisit(travelFunction_, _pRoot->m_pLeftChild);
				}

				if (_pRoot->m_pRightChild != nullptr)
				{
					PreVisit(travelFunction_, _pRoot->m_pRightChild);
				}
			}

			template<typename Key, typename Value>
			void SortedBinaryTree<Key, Value>::PostVisit(
				std::function<void(Node*)> travelFunction_, 
				Node* pRoot_) const
			{
				Node *_pRoot = nullptr;
				if (pRoot_ == nullptr)
				{
					_pRoot = m_pRoot;
				}
				else
				{
					_pRoot = pRoot_;
				}

				if (_pRoot == nullptr)
				{
					return;
				}

				if (_pRoot->m_pLeftChild != nullptr)
				{
					PostVisit(travelFunction_, _pRoot->m_pLeftChild);
				}

				if (_pRoot->m_pRightChild != nullptr)
				{
					PostVisit(travelFunction_, _pRoot->m_pRightChild);
				}

				travelFunction_(_pRoot);
			}

			template<typename Key, typename Value>
			void SortedBinaryTree<Key, Value>::Visit(
				std::function<void(Node*)> travelFunction_, 
				Node* pRoot_) const
			{
				Node *_pRoot = nullptr;
				if (pRoot_ == nullptr)
				{
					_pRoot = m_pRoot;
				}
				else
				{
					_pRoot = pRoot_;
				}

				if (_pRoot == nullptr)
				{
					return;
				}

				if (_pRoot->m_pLeftChild != nullptr)
				{
					Visit(travelFunction_, _pRoot->m_pLeftChild);
				}

				travelFunction_(_pRoot);
				if (_pRoot->m_pRightChild != nullptr)
				{
					Visit(travelFunction_, _pRoot->m_pRightChild);
				}
			}

			template<typename Key, typename Value>
			typename SortedBinaryTree<Key, Value>::Node* SortedBinaryTree<Key, Value>::Min(Node* pRoot_) const
			{
				Node *_pRoot = nullptr;
				if (pRoot_ == nullptr)
				{
					_pRoot = m_pRoot;
				}
				else
				{
					_pRoot = pRoot_;
				}

				if (_pRoot == nullptr)
				{
					return nullptr;
				}

				if (_pRoot->m_pLeftChild != nullptr)
				{
					return Min(_pRoot->m_pLeftChild);
				}
				else
				{
					return _pRoot;
				}
			}

			template<typename Key, typename Value>
			typename SortedBinaryTree<Key, Value>::Node* SortedBinaryTree<Key, Value>::Max(Node* pRoot_) const
			{
				Node *_pRoot = nullptr;
				if (pRoot_ == nullptr)
				{
					_pRoot = m_pRoot;
				}
				else
				{
					_pRoot = pRoot_;
				}

				if (_pRoot == nullptr)
				{
					return nullptr;
				}

				if (_pRoot->m_pRightChild != nullptr)
				{
					return Max(_pRoot->m_pRightChild);
				}
				else
				{
					return _pRoot;
				}
			}

			template<typename Key, typename Value>
			bool SortedBinaryTree<Key, Value>::Search(const Key& key_, Value& value_, Node* pRoot_) const
			{
				Node *_pRoot = nullptr;
				if (pRoot_ == nullptr)
				{
					_pRoot = m_pRoot;
				}
				else
				{
					_pRoot = pRoot_;
				}

				if (_pRoot == nullptr)
				{
					return false;
				}

				if (_pRoot->m_nPair.m_nKey == key_)
				{
					value_ = _pRoot->m_nPair.m_nValue;
					return true;
				}
				else if (_pRoot->m_nPair.m_nKey < key_)
				{
					if (_pRoot->m_pRightChild != nullptr)
					{
						return Search(key_, value_, _pRoot->m_pRightChild);
					}
					else
					{
						return false;
					}
				}
				else
				{
					if (_pRoot->m_pLeftChild != nullptr)
					{
						return Search(key_, value_, _pRoot->m_pLeftChild);
					}
					else
					{
						return false;
					}
				}
			}

			template<typename Key, typename Value>
			typename SortedBinaryTree<Key, Value>::Node* SortedBinaryTree<Key, Value>::Search(const Key& key_, Node* pRoot_) const
			{
				Node *_pRoot = nullptr;
				if (pRoot_ == nullptr)
				{
					_pRoot = m_pRoot;
				}
				else
				{
					_pRoot = pRoot_;
				}

				if (_pRoot == nullptr)
				{
					return nullptr;
				}

				if (_pRoot->m_nPair.m_nKey == key_)
				{
					return _pRoot;
				}
				else if (_pRoot->m_nPair.m_nKey < key_)
				{
					if (_pRoot->m_pRightChild != nullptr)
					{
						return Search(key_, _pRoot->m_pRightChild);
					}
					else
					{
						return nullptr;
					}
				}
				else
				{
					if (_pRoot->m_pLeftChild != nullptr)
					{
						return Search(key_, _pRoot->m_pLeftChild);
					}
					else
					{
						return nullptr;
					}
				}
			}

			template<typename Key, typename Value>
			void SortedBinaryTree<Key, Value>::Delete(const Key& key_, Node* pRoot_)
			{
				Node *_pRoot = nullptr;
				if (pRoot_ == nullptr)
				{
					_pRoot = m_pRoot;
				}
				else
				{
					_pRoot = pRoot_;
				}

				if (_pRoot == nullptr)
				{
					return;
				}

				Node* _pNode = Search(key_, _pRoot);
				if (_pNode == nullptr)
				{
					return;
				}

				if (_pNode->m_pLeftChild == nullptr
					&& _pNode->m_pRightChild == nullptr)
				{
					if (_pNode->m_pParent == nullptr)
					{
						delete _pNode;
						_pNode = nullptr;
						m_pRoot = nullptr;
						return;
					}

					if (_pNode->m_pParent->m_pLeftChild == _pNode)
					{
						_pNode->m_pParent->m_pLeftChild = nullptr;
						delete _pNode;
						_pNode = nullptr;
						return;
					}
					else
					{
						_pNode->m_pParent->m_pRightChild = nullptr;
						delete _pNode;
						_pNode = nullptr;
						return;
					}
				}
				else if (_pNode->m_pLeftChild != nullptr
					&& _pNode->m_pRightChild == nullptr)
				{
					Node *_pMovingNode = Max(_pNode->m_pLeftChild);
					_pNode->m_nPair = _pMovingNode->m_nPair;
					Delete(_pMovingNode->m_nPair.m_nKey, _pNode->m_pLeftChild);
				}
				else if (_pNode->m_pLeftChild == nullptr
					&& _pNode->m_pRightChild != nullptr)
				{
					Node *_pMovingNode = Min(_pNode->m_pRightChild);
					_pNode->m_nPair = _pMovingNode->m_nPair;
					Delete(_pMovingNode->m_nPair.m_nKey, _pNode->m_pRightChild);
				}
				else
				{
					Node *_pMovingNode = Max(_pNode->m_pLeftChild);
					_pNode->m_nPair = _pMovingNode->m_nPair;
					Delete(_pMovingNode->m_nPair.m_nKey, _pNode->m_pLeftChild);
				}

				return;
			}

			template<typename Key, typename Value>
			void SortedBinaryTree<Key, Value>::DeleteAll()
			{
				this->~SortedBinaryTree();
			}

			template<typename Key, typename Value>
			typename SortedBinaryTree<Key, Value>::Node* SortedBinaryTree<Key, Value>::Pre(Node *pNode_) const
			{
				if (pNode_ == nullptr)
				{
					return nullptr;
				}

				if (pNode_->m_pLeftChild != nullptr)
				{
					return Max(pNode_->m_pLeftChild);
				}
				else
				{
					while (true)
					{
						if (pNode_->m_pParent == nullptr)
						{
							return nullptr;
						}
						else if (pNode_->m_pParent->m_pLeftChild == pNode_)
						{
							pNode_ = pNode_->m_pParent;
						}
						else
						{
							return pNode_->m_pParent;
						}
					}
				}
			}

			template<typename Key, typename Value>
			typename SortedBinaryTree<Key, Value>::Node* SortedBinaryTree<Key, Value>::Suc(Node *pNode_) const
			{
				if (pNode_ == nullptr)
				{
					return nullptr;
				}

				if (pNode_->m_pRightChild != nullptr)
				{
					return Min(pNode_->m_pRightChild);
				}
				else
				{
					while (true)
					{
						if (pNode_->m_pParent == nullptr)
						{
							return nullptr;
						}
						else if (pNode_->m_pParent->m_pRightChild == pNode_)
						{
							pNode_ = pNode_->m_pParent;
						}
						else
						{
							return pNode_->m_pParent;
						}
					}
				}
			}

			template<typename Key, typename Value>
			bool SortedBinaryTree<Key, Value>::Add(const Pair& nPair_)
			{
				Node *_pNewNode = nullptr;
				try
				{
					_pNewNode = new Node();
				}
				catch (...)
				{
					_pNewNode = nullptr;
					throw "out of memory";
				}

				_pNewNode->m_nPair = nPair_;
				if (m_pRoot == nullptr)
				{
					m_pRoot = _pNewNode;
					return true;
				}

				Node* _pNode = m_pRoot;
				while (true)
				{
					if (_pNode->m_nPair.m_nKey > _pNewNode->m_nPair.m_nKey)
					{
						if (_pNode->m_pLeftChild == nullptr)
						{
							_pNode->m_pLeftChild = _pNewNode;
							_pNewNode->m_pParent = _pNode;
							return true;
						}
						else
						{
							_pNode = _pNode->m_pLeftChild;
						}
					}
					else if (_pNode->m_nPair.m_nKey < _pNewNode->m_nPair.m_nKey)
					{
						if (_pNode->m_pRightChild == nullptr)
						{
							_pNode->m_pRightChild = _pNewNode;
							_pNewNode->m_pParent = _pNode;
							return true;
						}
						else
						{
							_pNode = _pNode->m_pRightChild;
						}
					}
					else
					{
						if (_pNewNode)
						{
							delete _pNewNode;
							_pNewNode = nullptr;
						}

						return false;
					}
				}
			}

			template<typename Key, typename Value>
			typename SortedBinaryTree<Key, Value>::Node* SortedBinaryTree<Key, Value>::GetRoot() const
			{
				return m_pRoot;
			}

			template<typename Key, typename Value>
			SortedBinaryTree<Key, Value>::SortedBinaryTree(const SortedBinaryTree& minTree_)
				:m_pRoot(nullptr)
			{
				Array::DynArray<Pair> _arrPairs = minTree_.GetArray();
				int _nSize = _arrPairs.GetSize();
				for (int _i = 0; _i < _nSize; _i++)
				{
					Add(_arrPairs[_i]);
				}
			}

			template<typename Key, typename Value>
			typename SortedBinaryTree<Key, Value>& SortedBinaryTree<Key, Value>::operator=(const SortedBinaryTree& minTree_)
			{
				if (this == &minTree_)
				{
					return *this;
				}

				this->~SortedBinaryTree();
				Array::DynArray<Pair> _arrPairs = minTree_.GetArray();
				int _nSize = _arrPairs.GetSize();
				for (int _i = 0; _i < _nSize; _i++)
				{
					Add(_arrPairs[_i]);
				}

				return *this;
			}
		}
	}
}

#endif
