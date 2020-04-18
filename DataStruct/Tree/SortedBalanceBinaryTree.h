//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef ALLIB_DATASTRUCT_TREE_SORTEDBALANCEBINARYTREE_H
#define ALLIB_DATASTRUCT_TREE_SORTEDBALANCEBINARYTREE_H
#include "..\..\stdafx.h"
#include "..\Array\DynArray.h"
namespace AlLib
{
	namespace DataStruct
	{
		namespace Tree
		{
			template<typename Key, typename Value>
			class SortedBalanceBinaryTree
			{
			public:
				enum Color
				{
					BLACK = 1,
					RED,
					BLACKBLACK,
				};

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
						m_nColor = Color::RED;
					}

					Node(const Pair& nPair_)
					{
						m_nPair = nPair_;
						m_pParent = nullptr;
						m_pLeftChild = nullptr;
						m_pRightChild = nullptr;
						m_nColor = Color::RED;
					}

					~Node()
					{
					}

				private:
					Node* m_pParent;
					Node* m_pLeftChild;
					Node* m_pRightChild;
					Pair m_nPair;
					Color m_nColor;
					friend class SortedBalanceBinaryTree;
				};

				SortedBalanceBinaryTree();
				~SortedBalanceBinaryTree();

				SortedBalanceBinaryTree(const SortedBalanceBinaryTree& minTree_);
				SortedBalanceBinaryTree& operator=(const SortedBalanceBinaryTree& minTree_);

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
				void Delete(Node* pNode_);
				bool AdjustForParentColor(Node *pAdjustedNode_);
				Node* LeftRotate(Node *pNode_);
				Node* RightRotate(Node *pNode_);
				void AdjustForBlackBlack(Node *pBlackBlackNode_);
				void AdjustForBlackHeight(Node *pNode_);

				// 正确性测试支持：
				// 检查 红黑树合法性
				// 根黑：
				// 同一节点不同分支黑高一致
				// 父红，则子黑
				// 颜色必须 为 红或黑
				bool CheckValid() const;
				int GetBlackHeight(Node *pNode_) const;
			private:
				Node* m_pRoot;
			};

			template<typename Key, typename Value>
			SortedBalanceBinaryTree<Key, Value>::SortedBalanceBinaryTree()
			{
				m_pRoot = nullptr;
			}

			template<typename Key, typename Value>
			SortedBalanceBinaryTree<Key, Value>::~SortedBalanceBinaryTree()
			{
				Array::DynArray<Node*> _arrNodes;
				PreVisit([&_arrNodes](Node* pNode_)
				{
					_arrNodes.Add(pNode_);
				});

				for (int _i = 0; _i < _arrNodes.GetSize(); _i++)
				{
					delete _arrNodes[_i];
					_arrNodes[_i] = nullptr;
				}

				m_pRoot = nullptr;
			}

			template<typename Key, typename Value>
			void SortedBalanceBinaryTree<Key, Value>::PreVisit(
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
			void SortedBalanceBinaryTree<Key, Value>::PostVisit(
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
			void SortedBalanceBinaryTree<Key, Value>::Visit(
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
			typename SortedBalanceBinaryTree<Key, Value>::Node* SortedBalanceBinaryTree<Key, Value>::Min(
				Node* pRoot_) const
			{
				Node *_pRoot = pRoot_;
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
			typename SortedBalanceBinaryTree<Key, Value>::Node* SortedBalanceBinaryTree<Key, Value>::Max(
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
			bool SortedBalanceBinaryTree<Key, Value>::Search(
				const Key& key_, 
				Value& value_, 
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
			typename SortedBalanceBinaryTree<Key, Value>::Node* SortedBalanceBinaryTree<Key, Value>::Search(
				const Key& key_, 
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
			typename SortedBalanceBinaryTree<Key, Value>::Node* SortedBalanceBinaryTree<Key, Value>::Pre(
				Node *pNode_) const
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
			typename SortedBalanceBinaryTree<Key, Value>::Node* SortedBalanceBinaryTree<Key, Value>::Suc(
				Node *pNode_) const
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
			typename SortedBalanceBinaryTree<Key, Value>::Node* SortedBalanceBinaryTree<Key, Value>::GetRoot() const
			{
				return m_pRoot;
			}

			template<typename Key, typename Value>
			SortedBalanceBinaryTree<Key, Value>::SortedBalanceBinaryTree(
				const SortedBalanceBinaryTree& minTree_)
			{
				Array::DynArray<Pair> _arrPairs = minTree_.GetArray();
				for (int _i = 0; _i < _arrPairs.GetSize(); _i++)
				{
					Add(_arrPairs[_i]);
				}
			}

			template<typename Key, typename Value>
			typename SortedBalanceBinaryTree<Key, Value>& SortedBalanceBinaryTree<Key, Value>::operator=(
				const SortedBalanceBinaryTree& minTree_)
			{
				if (this == &minTree_)
				{
					return *this;
				}

				this->~SortedBalanceBinaryTree();
				Array::DynArray<Pair> _arrPairs = minTree_.GetArray();
				for (int _i = 0; _i < _arrPairs.GetSize(); _i++)
				{
					Add(_arrPairs[_i]);
				}

				return *this;
			}

			template<typename Key, typename Value>
			bool SortedBalanceBinaryTree<Key, Value>::Add(const Pair& nPair_)
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
					m_pRoot->m_nColor = Color::BLACK;
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
							break;
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
							break;
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

				if (_pNewNode->m_pParent->m_nColor == Color::RED)
				{
					AdjustForParentColor(_pNewNode);
				}

				return true;
			}

			template<typename Key, typename Value>
			void SortedBalanceBinaryTree<Key, Value>::Delete(Node* pNode_)
			{
				Node* _pNode = pNode_;
				if (_pNode == nullptr)
				{
					throw "input error";
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
						bool _bNeedAdjust = _pNode->m_nColor == Color::BLACK;
						Node* _pParent = _pNode->m_pParent;
						delete _pNode;
						_pNode = nullptr;
						if (_bNeedAdjust)
						{
							AdjustForBlackHeight(_pParent);
						}
						return;
					}
					else
					{
						_pNode->m_pParent->m_pRightChild = nullptr;
						bool _bNeedAdjust = _pNode->m_nColor == Color::BLACK;
						Node* _pParent = _pNode->m_pParent;
						delete _pNode;
						_pNode = nullptr;
						if (_bNeedAdjust)
						{
							AdjustForBlackHeight(_pParent);
						}
						return;
					}
				}
				else if (_pNode->m_pLeftChild != nullptr
					&& _pNode->m_pRightChild == nullptr)
				{
					Node *_pMovingNode = Max(_pNode->m_pLeftChild);
					_pNode->m_nPair = _pMovingNode->m_nPair;
					Delete(_pMovingNode);
				}
				else if (_pNode->m_pLeftChild == nullptr
					&& _pNode->m_pRightChild != nullptr)
				{
					Node *_pMovingNode = Min(_pNode->m_pRightChild);
					_pNode->m_nPair = _pMovingNode->m_nPair;
					Delete(_pMovingNode);
				}
				else
				{
					Node *_pMovingNode = Max(_pNode->m_pLeftChild);
					_pNode->m_nPair = _pMovingNode->m_nPair;
					Delete(_pMovingNode);
				}

				return;
			}

			template<typename Key, typename Value>
			void SortedBalanceBinaryTree<Key, Value>::Delete(
				const Key& key_, 
				Node* pRoot_)
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

				Delete(_pNode);
			}

			template<typename Key, typename Value>
			void SortedBalanceBinaryTree<Key, Value>::DeleteAll()
			{
				this->~SortedBalanceBinaryTree();
			}

			template<typename Key, typename Value>
			typename SortedBalanceBinaryTree<Key, Value>::Node* SortedBalanceBinaryTree<Key, Value>::LeftRotate(
				Node *pNode_)
			{
				if (pNode_ == nullptr
					|| pNode_->m_pRightChild == nullptr)
				{
					throw "input error";
				}

				Node *_pRight = pNode_->m_pRightChild;
				Node *_pLeft = pNode_->m_pLeftChild;
				Node *_pRightLeft = _pRight->m_pLeftChild;
				Node *_pRightRight = _pRight->m_pRightChild;
				Node *_pParent = pNode_->m_pParent;
				if (_pParent == nullptr)
				{
					m_pRoot = _pRight;
				}
				else if (_pParent->m_pLeftChild == pNode_)
				{
					_pParent->m_pLeftChild = _pRight;
				}
				else
				{
					_pParent->m_pRightChild = _pRight;
				}

				_pRight->m_pParent = _pParent;
				_pRight->m_pLeftChild = pNode_;
				_pRight->m_pRightChild = _pRightRight;

				pNode_->m_pParent = _pRight;
				pNode_->m_pLeftChild = _pLeft;
				pNode_->m_pRightChild = _pRightLeft;

				if (_pRightLeft != nullptr)
				{
					_pRightLeft->m_pParent = pNode_;
				}

				return _pRight;
			}

			template<typename Key, typename Value>
			typename SortedBalanceBinaryTree<Key, Value>::Node * SortedBalanceBinaryTree<Key, Value>::RightRotate(
				Node *pNode_)
			{
				if (pNode_ == nullptr
					|| pNode_->m_pLeftChild == nullptr)
				{
					throw "input error";
				}

				Node *_pLeft = pNode_->m_pLeftChild;
				Node *_pRight = pNode_->m_pRightChild;
				Node *_pLeftLeft = _pLeft->m_pLeftChild;
				Node *_pLeftRight = _pLeft->m_pRightChild;
				Node *_pParent = pNode_->m_pParent;
				if (_pParent == nullptr)
				{
					m_pRoot = _pLeft;
				}
				else if (_pParent->m_pLeftChild == pNode_)
				{
					_pParent->m_pLeftChild = _pLeft;
				}
				else
				{
					_pParent->m_pRightChild = _pLeft;
				}

				_pLeft->m_pParent = _pParent;
				_pLeft->m_pLeftChild = _pLeftLeft;
				_pLeft->m_pRightChild = pNode_;

				pNode_->m_pParent = _pLeft;
				pNode_->m_pLeftChild = _pLeftRight;
				pNode_->m_pRightChild = _pRight;

				if (_pLeftRight != nullptr)
				{
					_pLeftRight->m_pParent = pNode_;
				}

				return _pLeft;
			}

			template<typename Key, typename Value>
			bool SortedBalanceBinaryTree<Key, Value>::AdjustForParentColor(
				Node *pNode_)
			{
				if (pNode_ == nullptr
					|| pNode_->m_nColor != Color::RED
					|| pNode_->m_pParent == nullptr
					|| pNode_->m_pParent->m_nColor != Color::RED)
				{
					throw "input error";
				}
				
				Node *_pNode = pNode_;
				Node *_pParent = nullptr;
				Node *_pGrandFather = nullptr;
				Color _nColor = Color::RED;
				while (true)
				{
					_pParent = nullptr;
					if (_pNode != nullptr)
					{
						_pParent = _pNode->m_pParent;
					}

					if (_pParent != nullptr)
					{
						_pGrandFather = _pParent->m_pParent;
					}

					if (_pNode == nullptr
						|| _pParent == nullptr
						|| _pParent->m_nColor == Color::BLACK
						|| _pGrandFather == nullptr)
					{
						break;
					}

					if (_pNode == _pParent->m_pLeftChild
						&& _pParent == _pGrandFather->m_pLeftChild)
					{
						_pNode = RightRotate(_pGrandFather);
						_pNode->m_pLeftChild->m_nColor = (Color::BLACK);
					}
					else if (_pNode == _pParent->m_pLeftChild
						&& _pParent == _pGrandFather->m_pRightChild
						&& _pGrandFather->m_pLeftChild == nullptr)
					{
						_pGrandFather = LeftRotate(_pGrandFather);
						LeftRotate(_pGrandFather->m_pLeftChild);
						_pGrandFather = RightRotate(_pGrandFather);
						_pGrandFather->m_nColor = Color::BLACK;
						_pGrandFather->m_pLeftChild->m_nColor = Color::RED;
						break;
					}
					else if (_pNode == _pParent->m_pLeftChild
						&& _pParent == _pGrandFather->m_pRightChild
						&& _pGrandFather->m_pLeftChild)
					{
						RightRotate(_pParent);
						_pNode = LeftRotate(_pGrandFather);
						_pNode->m_pRightChild->m_nColor = (Color::BLACK);
					}
					else if (_pNode == _pParent->m_pRightChild
						&& _pParent == _pGrandFather->m_pLeftChild
						&& _pGrandFather->m_pRightChild == nullptr)
					{
						LeftRotate(_pParent);
						_pNode = RightRotate(_pGrandFather);
						_pNode->m_nColor = Color::BLACK;
						_pNode->m_pRightChild->m_nColor = Color::RED;
						break;
					}
					else if (_pNode == _pParent->m_pRightChild
						&& _pParent == _pGrandFather->m_pLeftChild
						&& _pGrandFather->m_pRightChild)
					{
						LeftRotate(_pParent);
						_pNode = RightRotate(_pGrandFather);
						_pNode->m_pLeftChild->m_nColor = (Color::BLACK);
					}
					else if (_pNode == _pParent->m_pRightChild
						&& _pGrandFather->m_pRightChild == _pParent)
					{
						_pNode = LeftRotate(_pGrandFather);
						_pNode->m_pRightChild->m_nColor = (Color::BLACK);
					}
					else
					{
						assert(false);
					}
				}

				m_pRoot->m_nColor = Color::BLACK;
				return true;
			}

			template<typename Key, typename Value>
			void SortedBalanceBinaryTree<Key, Value>::AdjustForBlackBlack(
				Node *pNode_)
			{
				if (pNode_ == nullptr
					|| pNode_->m_nColor != Color::BLACKBLACK)
				{
					throw "input error";
				}
			
				Node *_pParent = nullptr;
				bool _bFirst = true;
				while (true)
				{
					_pParent = nullptr;
					if (pNode_)
					{
						_pParent = pNode_->m_pParent;
					}

					if (pNode_ == nullptr
						|| _pParent == nullptr
						|| pNode_->m_nColor != Color::BLACKBLACK)
					{
						break;
					}

					if (pNode_ == _pParent->m_pLeftChild
						&& _pParent->m_nColor == Color::BLACK
						&& _pParent->m_pRightChild->m_nColor == Color::BLACK)
					{
						if (_pParent->m_pRightChild->m_pLeftChild->m_nColor == Color::BLACK)
						{
							_pParent = LeftRotate(_pParent);
							_pParent->m_nColor = Color::BLACKBLACK;
							_pParent->m_pLeftChild->m_pLeftChild->m_nColor = Color::BLACK;
							_pParent->m_pLeftChild->m_nColor = Color::RED;
							pNode_ = _pParent;
						}
						else if (_pParent->m_pRightChild->m_pLeftChild->m_nColor == Color::RED
							&& _pParent->m_pRightChild->m_pRightChild->m_nColor == Color::RED)
						{
							_pParent = LeftRotate(_pParent);
							LeftRotate(_pParent->m_pLeftChild);
							_pParent->m_pLeftChild->m_pLeftChild->m_pLeftChild->m_nColor = Color::BLACK;
							_pParent->m_pLeftChild->m_pLeftChild->m_nColor = Color::RED;
							_pParent->m_pLeftChild->m_nColor = Color::BLACK;
							_pParent->m_pRightChild->m_nColor = Color::BLACK;
							break;
						}
						else if (_pParent->m_pRightChild->m_pLeftChild->m_nColor == Color::RED
							&& _pParent->m_pRightChild->m_pRightChild->m_nColor == Color::BLACK)
						{
							RightRotate(_pParent->m_pRightChild);
							_pParent = LeftRotate(_pParent);
							_pParent->m_pLeftChild->m_pLeftChild->m_nColor = Color::BLACK;
							_pParent->m_nColor = Color::BLACK;
							break;
						}
						else
						{
							assert(false);
							throw "unexpected action";
						}
					}
					else if (pNode_ == _pParent->m_pLeftChild
						&& _pParent->m_nColor == Color::BLACK
						&& _pParent->m_pRightChild->m_nColor == Color::RED)
					{
						if (_pParent->m_pRightChild->m_pLeftChild->m_pLeftChild->m_nColor == Color::BLACK)
						{
							_pParent = LeftRotate(_pParent);
							_pParent->m_nColor = Color::BLACK;
							LeftRotate(_pParent->m_pLeftChild);
							_pParent->m_pLeftChild->m_pLeftChild->m_pLeftChild->m_nColor = Color::BLACK;
							_pParent->m_pLeftChild->m_pLeftChild->m_nColor = Color::RED;
							break;
						}
						else
						{
							_pParent = LeftRotate(_pParent);
							RightRotate(_pParent->m_pLeftChild->m_pRightChild);
							LeftRotate(_pParent->m_pLeftChild);
							_pParent->m_nColor = Color::BLACK;
							_pParent->m_pLeftChild->m_pLeftChild->m_pLeftChild->m_nColor = Color::BLACK;
							break;
						}
					}
					else if (pNode_ == _pParent->m_pLeftChild
						&& _pParent->m_nColor == Color::RED)
					{
						_pParent = LeftRotate(_pParent);
						_pParent->m_nColor = Color::BLACK;
						_pParent->m_pLeftChild->m_nColor = Color::RED;
						_pParent->m_pLeftChild->m_pLeftChild->m_nColor = Color::BLACK;
						if (_pParent->m_pLeftChild->m_pRightChild->m_nColor == Color::RED)
						{
							AdjustForParentColor(_pParent->m_pLeftChild->m_pRightChild);
						}

						break;
					}
					else if (pNode_ == _pParent->m_pRightChild
						&& _pParent->m_nColor == Color::BLACK
						&& _pParent->m_pLeftChild->m_nColor == Color::BLACK)
					{
						if (_pParent->m_pLeftChild->m_pRightChild->m_nColor == Color::BLACK)
						{
							_pParent = RightRotate(_pParent);
							_pParent->m_pRightChild->m_pRightChild->m_nColor = Color::BLACK;
							_pParent->m_pRightChild->m_nColor = Color::RED;
							_pParent->m_nColor = Color::BLACKBLACK;
							pNode_ = _pParent;
						}
						else if (_pParent->m_pLeftChild->m_pRightChild->m_nColor == Color::RED)
						{
							LeftRotate(_pParent->m_pLeftChild);
							_pParent = RightRotate(_pParent);
							_pParent->m_nColor = Color::BLACK;
							_pParent->m_pRightChild->m_pRightChild->m_nColor = Color::BLACK;
							break;
						}
						else
						{
							assert(false);
							throw "unexpected situation";
						}
					}
					else if (pNode_ == _pParent->m_pRightChild
						&& _pParent->m_nColor == Color::BLACK
						&& _pParent->m_pLeftChild->m_nColor == Color::RED)
					{
						if (_pParent->m_pLeftChild->m_pRightChild->m_pRightChild->m_nColor == Color::BLACK)
						{
							_pParent = RightRotate(_pParent);
							RightRotate(_pParent->m_pRightChild);
							_pParent->m_pRightChild->m_pRightChild->m_pRightChild->m_nColor = Color::BLACK;
							_pParent->m_pRightChild->m_pRightChild->m_nColor = Color::RED;
							_pParent->m_nColor = Color::BLACK;
							break;
						}
						else
						{
							_pParent = RightRotate(_pParent);
							LeftRotate(_pParent->m_pRightChild->m_pLeftChild);
							RightRotate(_pParent->m_pRightChild);
							_pParent->m_nColor = Color::BLACK;
							_pParent->m_pRightChild->m_pRightChild->m_pRightChild->m_nColor = Color::BLACK;
							break;
						}
					}
					else if (pNode_ == _pParent->m_pRightChild
						&& _pParent->m_nColor == Color::RED)
					{
						_pParent = RightRotate(_pParent);
						_pParent->m_pRightChild->m_pRightChild->m_nColor = Color::BLACK;
						if (_pParent->m_pRightChild->m_pLeftChild->m_nColor == Color::RED)
						{
							AdjustForParentColor(_pParent->m_pRightChild->m_pLeftChild);
						}

						break;
					}
					else
					{
						assert(false);
						throw "unexpected situation";
					}
				}

				m_pRoot->m_nColor = Color::BLACK;
				assert(CheckValid());
			}

			template<typename Key, typename Value>
			void SortedBalanceBinaryTree<Key, Value>::AdjustForBlackHeight(
				Node *pNode_)
			{
				if (pNode_ == nullptr)
				{
					throw "input error";
				}

				if (pNode_->m_pLeftChild == nullptr
					&& pNode_->m_pRightChild != nullptr)
				{
					if (pNode_->m_nColor == Color::RED)
					{
						Node *_pTemp = LeftRotate(pNode_);
						if (_pTemp->m_pLeftChild->m_pRightChild != nullptr)
						{
							AdjustForParentColor(_pTemp->m_pLeftChild->m_pRightChild);
						}

						assert(CheckValid());
					}
					else if (pNode_->m_nColor == Color::BLACK)
					{
						if (pNode_->m_pRightChild->m_nColor == Color::RED)
						{
							Node *_pTemp = LeftRotate(pNode_);
							LeftRotate(_pTemp->m_pLeftChild);
							_pTemp->m_nColor = Color::BLACK;
							_pTemp->m_pLeftChild->m_pLeftChild->m_nColor = Color::RED;
							if (_pTemp->m_pLeftChild->m_pLeftChild->m_pRightChild != nullptr)
							{
								assert(_pTemp->m_pLeftChild->m_pLeftChild->m_pRightChild->m_nColor == Color::RED);
								AdjustForParentColor(_pTemp->m_pLeftChild->m_pLeftChild->m_pRightChild);
								assert(CheckValid());
							}
							else
							{
								assert(CheckValid());
							}
						}
						else if (pNode_->m_pRightChild->m_nColor == Color::BLACK)
						{
							Node *_pTemp = LeftRotate(pNode_);
							if (_pTemp->m_pRightChild != nullptr)
							{
								assert(_pTemp->m_pRightChild->m_nColor == Color::RED);
								_pTemp->m_pRightChild->m_nColor = Color::BLACK;
								assert(CheckValid());
							}
							else
							{
								if (_pTemp->m_pLeftChild->m_pRightChild != nullptr)
								{
									assert(_pTemp->m_pLeftChild->m_pRightChild->m_nColor == Color::RED);
									LeftRotate(_pTemp->m_pLeftChild);
									_pTemp = RightRotate(_pTemp);
									_pTemp->m_nColor = Color::BLACK;
									assert(_pTemp->m_pLeftChild->m_nColor == Color::BLACK);
									assert(_pTemp->m_pRightChild->m_nColor == Color::BLACK);
									assert(CheckValid());
								}
								else
								{
									_pTemp->m_pLeftChild->m_nColor = Color::RED;
									_pTemp->m_nColor = Color::BLACKBLACK;
									AdjustForBlackBlack(_pTemp);
									assert(CheckValid());
								}
							}
						}
						else
						{
							assert(false);
							throw "The right child of the adjust node not has a right color";
						}
					}
					else
					{
						assert(false);
						throw "The adjust node not has a right color";
					}
				}
				else if (pNode_->m_pLeftChild != nullptr
					&& pNode_->m_pRightChild == nullptr)
				{
					if (pNode_->m_nColor == Color::RED)
					{
						Node *_pTemp = RightRotate(pNode_);
						if (_pTemp->m_pRightChild->m_pLeftChild != nullptr)
						{
							AdjustForParentColor(_pTemp->m_pRightChild->m_pLeftChild);
						}

						assert(CheckValid());
					}
					else if (pNode_->m_nColor == Color::BLACK)
					{
						if (pNode_->m_pLeftChild->m_nColor == Color::RED)
						{
							Node *_pTemp = RightRotate(pNode_);
							RightRotate(_pTemp->m_pRightChild);
							_pTemp->m_nColor = Color::BLACK;
							_pTemp->m_pRightChild->m_pRightChild->m_nColor = Color::RED;
							if (_pTemp->m_pRightChild->m_pRightChild->m_pLeftChild != nullptr)
							{
								AdjustForParentColor(_pTemp->m_pRightChild->m_pRightChild->m_pLeftChild);
								assert(CheckValid());
							}
							else
							{
								assert(CheckValid());
							}
						}
						else if (pNode_->m_pLeftChild->m_nColor == Color::BLACK)
						{
							Node *_pTemp = RightRotate(pNode_);
							if (_pTemp->m_pLeftChild)
							{
								assert(_pTemp->m_pLeftChild->m_nColor == Color::RED);
								_pTemp->m_pLeftChild->m_nColor = Color::BLACK;
								assert(CheckValid());
							}
							else
							{
								if (_pTemp->m_pRightChild->m_pLeftChild)
								{
									assert(_pTemp->m_pRightChild->m_pLeftChild->m_nColor == Color::RED);
									RightRotate(_pTemp->m_pRightChild);
									_pTemp = LeftRotate(_pTemp);
									_pTemp->m_nColor = Color::BLACK;
									assert(_pTemp->m_pLeftChild->m_nColor == Color::BLACK);
									assert(_pTemp->m_pRightChild->m_nColor == Color::BLACK);
									assert(CheckValid());
								}
								else
								{
									_pTemp->m_pRightChild->m_nColor = Color::RED;
									_pTemp->m_nColor = Color::BLACKBLACK;
									AdjustForBlackBlack(_pTemp);
									assert(CheckValid());
								}
							}
						}
						else
						{
							assert(false);
							throw "The left child of the adjust node not has a right color";
						}
					}
					else
					{
						assert(false);
						throw "The adjust node not has a right color";
					}
				}
				else
				{
					assert(false);
					throw "The adjust node has no child";
				}

				assert(CheckValid());
			}

			template<typename Key, typename Value>
			bool SortedBalanceBinaryTree<Key, Value>::CheckValid() const
			{
				bool _bValid = true;
				if (m_pRoot == nullptr)
				{
					return true;
				}

				// 根黑
				if (m_pRoot
					&& m_pRoot->m_nColor != Color::BLACK)
				{
					assert(false);
					_bValid = false;
					return false;
				}

				// 父红，则子黑
				// 颜色须为红或黑
				// 黑高一致
				PreVisit([&_bValid, this](Node* pNode_)->void
				{
					if (pNode_ == nullptr
						|| _bValid == false)
					{
						return;
					}

					if (pNode_->m_nColor != Color::RED
						&& pNode_->m_nColor != Color::BLACK)
					{
						_bValid = false;
						return;
					}

					if (pNode_->m_nColor == Color::RED)
					{
						if (pNode_->m_pLeftChild != nullptr
							&& pNode_->m_pLeftChild->m_nColor != Color::BLACK)
						{
							_bValid = false;
							return;
						}

						if (pNode_->m_pRightChild != nullptr
							&& pNode_->m_pRightChild->m_nColor != Color::BLACK)
						{
							_bValid = false;
							return;
						}
					}

					int _nLeftChildTreeBlackHeight = this->GetBlackHeight(pNode_->m_pLeftChild);
					int _nRightChildTreeBlackHeight = this->GetBlackHeight(pNode_->m_pRightChild);
					if (_nLeftChildTreeBlackHeight != _nRightChildTreeBlackHeight
						|| _nLeftChildTreeBlackHeight == -1)
					{
						_bValid = false;
						return;
					}
				}, m_pRoot);

				return _bValid;
			}

			template<typename Key, typename Value>
			int SortedBalanceBinaryTree<Key, Value>::GetBlackHeight(Node *pNode_) const
			{
				int _nBlackHeight = 0;
				if (pNode_ == nullptr)
				{
					return _nBlackHeight;
				}

				if (pNode_->m_nColor == Color::BLACK)
				{
					_nBlackHeight = 1;
				}

				int _nLeft = GetBlackHeight(pNode_->m_pLeftChild);
				int _nRight = GetBlackHeight(pNode_->m_pRightChild);
				if (_nLeft != _nRight
					|| _nLeft == -1
					|| _nRight == -1)
				{
					return -1;
				}
				else
				{
					return _nLeft + _nBlackHeight;
				}
			}
		}
	}
}

#endif
