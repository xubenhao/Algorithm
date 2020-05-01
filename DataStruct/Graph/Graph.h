//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_DATASTRUCT_GRAPH_GRAPH_H
#define AILIB_DATASTRUCT_GRAPH_GRAPH_H
#include "..\..\stdafx.h"
#include "..\Array\DynArray.h"
#include "..\Tree\SortedBalanceBinaryTree.h"

namespace AlLib
{
	namespace DataStruct
	{
		// 更好的设计
		// 对Node
		// 由NodePair和DestNodes，SourNodes构成
		// NodePair来表示Node本身的键-值信息。
		// DestNodes来表示Node所有可达Node集合。
		// SourNodes来表示所有以此Node为目标Node集合。

		// 对Edge
		// 由EdgePair和StartNode, EndNode构成
		// EdgePair来表示Edge本身的键-值信息
		// StartNode来表示边的起点键值
		// EndNode来表示边的终点键值
		namespace GraphStruct
		{
			template<typename Key, typename Value>
			class Graph
			{
			public:
				class Pair
				{
				public:
					Pair()
					{
					}

					Pair(const Key& key_,
						const Value& value_)
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

					Array::DynArray<Key> GetDests()
					{
						Array::DynArray<Tree::SortedBalanceBinaryTree<Key,Key>::Pair> _arrPairs = m_sbbtDests.GetArray();
						Array::DynArray<Key> _arrKeys;
						int _nSize = _arrPairs.GetSize();
						for (int _i = 0; _i < _nSize; _i++)
						{
							_arrKeys.Add(_arrPairs[_i].m_nKey);
						}

						return _arrKeys;
					}

					Array::DynArray<Key> GetSours()
					{
						Array::DynArray<Tree::SortedBalanceBinaryTree<Key, Key>::Pair> _arrPairs = m_sbbtSours.GetArray();
						Array::DynArray<Key> _arrKeys;
						int _nSize = _arrPairs.GetSize();
						for (int _i = 0; _i < _nSize; _i++)
						{
							_arrKeys.Add(_arrPairs[_i].m_nKey);
						}

						return _arrKeys;
					}
				private:
					Node(const Pair& nPair_)
					{
						m_nPair = nPair_;
					}

					Node()
					{
					}

					~Node()
					{
					}

					void AddDestKey(Key nKey_)
					{
						m_sbbtDests.Add(Tree::SortedBalanceBinaryTree<Key, Key>::Pair(nKey_, nKey_));
					}

					void AddSourKey(Key nKey_)
					{
						m_sbbtSours.Add(Tree::SortedBalanceBinaryTree<Key, Key>::Pair(nKey_, nKey_));
					}

					void DeleteDestKey(Key nKey_)
					{
						m_sbbtDests.Delete(nKey_);
					}

					void DeleteSourKey(Key nKey_)
					{
						m_sbbtSours.Delete(nKey_);
					}

				private:
					Pair m_nPair;
					Tree::SortedBalanceBinaryTree<Key, Key> m_sbbtDests;
					Tree::SortedBalanceBinaryTree<Key, Key> m_sbbtSours;
					friend class Graph;
				};

				class EdgeIdentity
				{
				public:
					EdgeIdentity()
					{
					}
					
					EdgeIdentity(const Key& nS_,
						const Key& nE_)
					{
						m_nStartKey = nS_;
						m_nEndKey = nE_;
					}

					~EdgeIdentity()
					{

					}

					EdgeIdentity Reverse()
					{
						EdgeIdentity _nIndentity;
						_nIndentity.m_nStartKey = m_nEndKey;
						_nIndentity.m_nEndKey = m_nStartKey;
						return _nIndentity;
					}

					// 键值比较唯一性的标准定义：
					// A1 < B1 && A2 < B2，则k1 < k2
					// A1 == B1 && A2 < B2,则k1 < k2
					// A1 < B1 && A2== B2,则k1 < k2
					// A1 > B1 && A2 < B2,则k1 < k2

					// A1 < B1 && A2 > B2,则k1 > k2
					// A1 == B1 && A2 > B2,则k1 > k2
					// A1 > B1 && A2 == B2,则k1 > k2
					// A1 > B1 && A2 > B2,则k1 > k2

					// A1 == B1 && A2 == B2,则k1 == k2
					bool operator==(const EdgeIdentity& nIdentity_)
					{
						return (m_nStartKey == nIdentity_.m_nStartKey)
							&& (m_nEndKey == nIdentity_.m_nEndKey);
					}

					bool operator!=(const EdgeIdentity& nIdentity_)
					{
						return operator==(nIdentity_) == false;
					}

					bool operator<(const EdgeIdentity& nIdentity_)
					{
						if ((m_nStartKey < nIdentity_.m_nStartKey && m_nEndKey < nIdentity_.m_nEndKey)
							|| (m_nStartKey == nIdentity_.m_nStartKey && m_nEndKey < nIdentity_.m_nEndKey)
							|| (m_nStartKey < nIdentity_.m_nStartKey && m_nEndKey == nIdentity_.m_nEndKey)
							|| (m_nStartKey > nIdentity_.m_nStartKey && m_nEndKey < nIdentity_.m_nEndKey))
						{
							return true;
						}
						else
						{
							return false;
						}
					}

					bool operator>(const EdgeIdentity& nIdentity_)
					{
						return (operator==(nIdentity_) == false)
							&& (operator<(nIdentity_) == false);
					}

					bool operator>=(const EdgeIdentity& nIdentity_)
					{
						return operator<(nIdentity_) == false;
					}

					bool operator<=(const EdgeIdentity& nIdentity_)
					{
						return operator>(nIdentity_) == false;
					}

				public:
					Key m_nStartKey;
					Key m_nEndKey;
					friend class Graph;
				};

				class Edge
				{
				public:
					EdgeIdentity GetIdentity()
					{
						return m_nIdentity;
					}

				private:
					Edge()
					{
						m_nWeight = 1.0;
						m_nStream = 1.0;
					}

					Edge(const EdgeIdentity& nIdentity_)
					{
						m_nIdentity = nIdentity_;
						m_nWeight = 1.0;
						m_nStream = 1.0;
					}

					~Edge()
					{
					}

				public:
					double m_nWeight;
					double m_nStream;
				private:
					EdgeIdentity m_nIdentity;
					friend class Graph;
				};

			public:
				typename typedef  Tree::SortedBalanceBinaryTree<Key, Node*> NodeTree;
				typename typedef NodeTree::Node NodeTreeNode;
				typename typedef NodeTree::Pair NodeTreePair;
				typename typedef  Tree::SortedBalanceBinaryTree<EdgeIdentity, Edge*> EdgeTree;
				typename typedef EdgeTree::Node EdgeTreeNode;
				typename typedef EdgeTree::Pair EdgeTreePair;

				Graph();
				~Graph();

				Graph(const Graph& nGraph_);
				Graph& operator=(const Graph& nGraph_);

				Array::DynArray<Node*> GetNodesArray() const
				{
					Array::DynArray<NodeTreePair> _arrPairs = m_NodesTree.GetArray();
					Array::DynArray<Node*> _arrNodes;
					for (int _i = 0; _i < _arrPairs.GetSize(); _i++)
					{
						_arrNodes.Add(_arrPairs[_i].m_nValue);
					}

					return _arrNodes;
				}

				Array::DynArray<Edge*> GetEdgesArray() const
				{
					Array::DynArray<EdgeTreePair> _arrPairs = m_EdgesTree.GetArray();
					Array::DynArray<Edge*> _arrEdges;
					int _nEdgeSize = _arrPairs.GetSize();
					for (int _i = 0; _i < _nEdgeSize; _i++)
					{
						_arrEdges.Add(_arrPairs[_i].m_nValue);
					}

					return _arrEdges;
				}

				Node* SearchNode(const Key& key_) const;
				Edge* SearchEdge(const EdgeIdentity& nIdentity_) const;

				bool AddNode(const Pair& nPair_);
				void DeleteNode(const Key& nKey_);
				bool AddEdge(const EdgeIdentity& nIdentity_);
				void DeleteEdge(const EdgeIdentity& nIdentity_);
			private:
				NodeTree m_NodesTree;
				EdgeTree m_EdgesTree;
			};

			template<typename Key, typename Value>
			Graph<Key, Value>::Graph()
			{
			}

			template<typename Key, typename Value>
			Graph<Key, Value>::~Graph()
			{
				Array::DynArray<Node*> _arrNodes = GetNodesArray();
				int _nNodeSize = _arrNodes.GetSize();
				for (int _i = 0; _i < _nNodeSize; _i++)
				{
					delete _arrNodes[_i];
					_arrNodes[_i] = nullptr;
				}

				Array::DynArray<Edge*> _arrEdges = GetEdgesArray();
				int _nEdgeSize = _arrEdges.GetSize();
				for (int _i = 0; _i < _nEdgeSize; _i++)
				{
					delete _arrEdges[_i];
					_arrEdges[_i] = nullptr;
				}

				m_NodesTree.DeleteAll();
				m_EdgesTree.DeleteAll();
			}

			template<typename Key, typename Value>
			Graph<Key, Value>::Graph(const Graph& nGraph_)
			{
				Array::DynArray<Node*> _arrNodes = nGraph_.GetNodesArray();
				int _nNodeSize = _arrNodes.GetSize();
				for (int _i = 0; _i < _nNodeSize; _i++)
				{
					AddNode(_arrNodes[_i]->m_nPair);
				}

				Array::DynArray<Edge*> _arrEdges = nGraph_.GetEdgesArray();
				int _nEdgeSize = _arrEdges.GetSize();
				for (int _i = 0; _i < _nEdgeSize; _i++)
				{
					AddEdge(_arrEdges[_i]->m_nIdentity);
					Edge* _pEdge = SearchEdge(_arrEdges[_i]->m_nIdentity);
					if (_pEdge == nullptr)
					{
						throw "unexpected error";
					}

					_pEdge->m_nWeight = _arrEdges[_i]->m_nWeight;
					_pEdge->m_nStream = _arrEdges[_i]->m_nStream;
				}
			}

			template<typename Key, typename Value>
			typename Graph<Key, Value>& Graph<Key, Value>::operator=(const Graph& nGraph_)
			{
				if (this == &nGraph_)
				{
					return *this;
				}

				this->~Graph();
				Array::DynArray<Node*> _arrNodes = nGraph_.GetNodesArray();
				int _nNodeSize = _arrNodes.GetSize();
				for (int _i = 0; _i < _nNodeSize; _i++)
				{
					AddNode(_arrNodes[_i]->m_nPair);
				}

				Array::DynArray<Edge*> _arrEdges = nGraph_.GetEdgesArray();
				int _nEdgeSize = _arrEdges.GetSize();
				for (int _i = 0; _i < _nEdgeSize; _i++)
				{
					AddEdge(_arrEdges[_i]->m_nIdentity);
					Edge* _pEdge = SearchEdge(_arrEdges[_i]->m_nIdentity);
					if (_pEdge == nullptr)
					{
						throw "unexpected error";
					}

					_pEdge->m_nWeight = _arrEdges[_i]->m_nWeight;
					_pEdge->m_nStream = _arrEdges[_i]->m_nStream;
				}

				return *this;
			}

			template<typename Key, typename Value>
			typename Graph<Key, Value>::Node* Graph<Key, Value>::SearchNode(const Key& key_) const
			{
				NodeTreeNode* _pTreeNode = m_NodesTree.Search(key_);
				if (_pTreeNode != nullptr)
				{
					NodeTreePair _nPair = _pTreeNode->GetPair();
					return _nPair.m_nValue;
				}
				else
				{
					return nullptr;
				}
			}

			template<typename Key, typename Value>
			typename Graph<Key, Value>::Edge* Graph<Key, Value>::SearchEdge(const EdgeIdentity& key_) const
			{
				EdgeTreeNode* _pTreeNode = m_EdgesTree.Search(key_);
				if (_pTreeNode != nullptr)
				{
					EdgeTreePair _nPair = _pTreeNode->GetPair();
					return _nPair.m_nValue;
				}
				else
				{
					return nullptr;
				}
			}

			template<typename Key, typename Value>
			bool Graph<Key, Value>::AddNode(const Pair& nPair_)
			{
				NodeTreeNode* _pNodeTreeNode = m_NodesTree.Search(nPair_.m_nKey);
				if (_pNodeTreeNode)
				{
					return false;
				}

				NodeTreePair _nNodeTreePair;
				_nNodeTreePair.m_nKey = nPair_.m_nKey;
				Node* _pNode = nullptr;
				try
				{
					_pNode = new Node(nPair_);
				}
				catch (...)
				{
					_pNode = nullptr;
					throw "out of memory";
				}

				_nNodeTreePair.m_nValue = _pNode;
				// 需要知道添加成功与否
				bool _bSuccess = m_NodesTree.Add(_nNodeTreePair);
				if (_bSuccess == false)
				{
					throw "unexpected error";
				}

				return _bSuccess;
			}

			template<typename Key, typename Value>
			void Graph<Key, Value>::DeleteNode(const Key& nKey_)
			{
				Node* _pNode = SearchNode(nKey_);
				if (_pNode == nullptr)
				{
					return;
				}

				DataStruct::Array::DynArray<Key> _arrKeys = _pNode->GetDests();
				for (int _i = 0; _i < _arrKeys.GetSize(); _i++)
				{
					DeleteEdge(EdgeIdentity(nKey_, _arrKeys[_i]));
				}
				
				_arrKeys = _pNode->GetSours();
				for (int _i = 0; _i < _arrKeys.GetSize(); _i++)
				{
					DeleteEdge(EdgeIdentity(_arrKeys[_i], nKey_));
				}
				
				m_NodesTree.Delete(nKey_);
				delete _pNode;
				_pNode = nullptr;
			}

			template<typename Key, typename Value>
			bool Graph<Key, Value>::AddEdge(const EdgeIdentity& nIdentity_)
			{
				Node* _pNodeS = SearchNode(nIdentity_.m_nStartKey);
				Node* _pNodeE = SearchNode(nIdentity_.m_nEndKey);
				if (_pNodeS == nullptr
					|| _pNodeE == nullptr)
				{
					return false;
				}

				EdgeTreeNode* _pEdgeTreeNode = m_EdgesTree.Search(nIdentity_);
				if (_pEdgeTreeNode)
				{
					return false;
				}

				EdgeTreePair _nEdgeTreePair;
				_nEdgeTreePair.m_nKey = nIdentity_;
				Edge* _pEdge = nullptr;
				try
				{
					_pEdge = new Edge(nIdentity_);
				}
				catch (...)
				{
					_pEdge = nullptr;
					throw "out of memory";
				}

				_nEdgeTreePair.m_nValue = _pEdge;
				bool _bSucces = m_EdgesTree.Add(_nEdgeTreePair);
				if (_bSucces == false)
				{
					throw "unexpected error";
				}
				else
				{
					_pNodeS->AddDestKey(nIdentity_.m_nEndKey);
					_pNodeE->AddSourKey(nIdentity_.m_nStartKey);
					return true;
				}
			}

			template<typename Key, typename Value>
			void Graph<Key, Value>::DeleteEdge(const EdgeIdentity& nIdentity_)
			{
				Edge* _pEdge = SearchEdge(nIdentity_);
				if (_pEdge == nullptr)
				{
					return;
				}

				Node* _pNodeS = SearchNode(nIdentity_.m_nStartKey);
				Node* _pNodeE = SearchNode(nIdentity_.m_nEndKey);
				if (_pNodeS == nullptr
					|| _pNodeE == nullptr)
				{
					throw "unexpected error";
				}

				_pNodeS->DeleteDestKey(nIdentity_.m_nEndKey);
				_pNodeE->DeleteSourKey(nIdentity_.m_nStartKey);
				m_EdgesTree.Delete(nIdentity_);
				delete _pEdge;
				_pEdge = nullptr;
			}
		}
	}
}
#endif
