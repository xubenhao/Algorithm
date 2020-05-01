//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_ALGORITHM_GRAPH_BREADTHFIRSTVISIT_H
#define AILIB_ALGORITHM_GRAPH_BREADTHFIRSTVISIT_H
#include "..\..\stdafx.h"
#include "..\..\DataStruct\Graph\Graph.h"
#include "..\..\DataStruct\Queue\DynQueue.h"

namespace AlLib
{
	namespace Algorithm
	{
		namespace Graph
		{
			template<typename Key, typename Value>
			class BreadthFirstVisit
			{
			public:
				class Node;
				typename typedef DataStruct::GraphStruct::Graph<Key, Value> InnerGraph;
				typename typedef InnerGraph::Node InnerGraphNode;
				typename typedef InnerGraph::Pair InnerGraphPair;
				typename typedef DataStruct::Tree::SortedBalanceBinaryTree<Key, Node*> InnerTree;
				class Node
				{
				public:
					Node* GetPreNode()
					{
						return m_pBfvPathNode;
					}

					typename InnerGraph::Node* GetGraphNode()
					{
						return m_pGraphNode;
					}
					
					int GetDistance()
					{
						return m_nBfvPathDistance;
					}
				private:
					Node()
					{
						m_nBfvPathDistance = -1;
						m_pGraphNode = nullptr;
						m_pBfvPathNode = nullptr;
					}

					Node(InnerGraphNode* pGraphNode_)
					{
						m_pGraphNode = pGraphNode_;
						m_nBfvPathDistance = -1;
						m_pBfvPathNode = nullptr;
					}

					~Node()
					{
					}

					void Reset()
					{
						m_pBfvPathNode = nullptr;
						m_nBfvPathDistance = -1;
					}
				private:
					InnerGraphNode* m_pGraphNode;
					Node* m_pBfvPathNode;
					int m_nBfvPathDistance;

					friend class BreadthFirstVisit;
				};

				BreadthFirstVisit(const InnerGraph& nGraph_);
				~BreadthFirstVisit();

				DataStruct::Array::DynArray<Node*> Run(const Key& nSourceKey_);
			private:
				BreadthFirstVisit(const BreadthFirstVisit& nBFV_) = default;
				BreadthFirstVisit& operator=(const BreadthFirstVisit& nBFV_) = default;
			private:
				InnerGraph m_nGraph;
				InnerTree m_tKeyToNodeMap;
			};

			template<typename Key, typename Value>
			BreadthFirstVisit<Key, Value>::BreadthFirstVisit(const InnerGraph& nGraph_)
				: m_nGraph(nGraph_)
			{
				DataStruct::Array::DynArray<InnerGraphNode*> _arrpGraphNodes = m_nGraph.GetNodesArray();
				for (int _i = 0; _i < _arrpGraphNodes.GetSize(); _i++)
				{
					Node* _pNode = nullptr;
					if (_arrpGraphNodes[_i] == nullptr)
					{
						throw "graph node exception";
					}

					try
					{
						_pNode = new Node(_arrpGraphNodes[_i]);
					}
					catch (...)
					{
						_pNode = nullptr;
						throw "out of memory";
					}

					InnerTree::Pair _nPair;
					InnerGraphPair _nGraphPair = _arrpGraphNodes[_i]->GetPair();
					_nPair.m_nKey = _nGraphPair.m_nKey;
					_nPair.m_nValue = _pNode;
					m_tKeyToNodeMap.Add(_nPair);
				}
			}

			template<typename Key, typename Value>
			BreadthFirstVisit<Key, Value>::~BreadthFirstVisit()
			{
				DataStruct::Array::DynArray<InnerTree::Pair> _arrPairs = m_tKeyToNodeMap.GetArray();
				int _nSize = _arrPairs.GetSize();
				for (int _i = 0; _i < _nSize; _i++)
				{
					delete _arrPairs[_i].m_nValue;
					_arrPairs[_i].m_nValue = nullptr;
				}
			}

			template<typename Key, typename Value>
			DataStruct::Array::DynArray<typename BreadthFirstVisit<Key, Value>::Node*> BreadthFirstVisit<Key, Value>::Run(const Key& nSourceKey_)
			{
				// 数据重置
				DataStruct::Array::DynArray<InnerTree::Pair> _arrPairs = m_tKeyToNodeMap.GetArray();
				for (int _i = 0; _i < _arrPairs.GetSize(); _i++)
				{
					if (_arrPairs[_i].m_nValue == nullptr)
					{
						throw "unexpected error";
					}

					_arrPairs[_i].m_nValue->Reset();
				}
				// 1.算法目标
				// 2.正确性证明
				// 3.效率分析
				DataStruct::Queue::DynQueue<Node*> _qpNodes;
				InnerTree::Node* _pSourceNode = m_tKeyToNodeMap.Search(nSourceKey_);
				if (_pSourceNode == nullptr
					|| _pSourceNode->GetPair().m_nValue == nullptr
					|| _pSourceNode->GetPair().m_nValue->m_pGraphNode == nullptr)
				{
					throw "source node is not exist";
				}

				Node* _pNode = _pSourceNode->GetPair().m_nValue;
				_pNode->m_nBfvPathDistance = 0;
				_qpNodes.In(_pNode);
				while (_qpNodes.IsEmpty() == false)
				{
					Node* _pNode = _qpNodes.Out();
					DataStruct::Array::DynArray<Key> _arrDestinations = _pNode->m_pGraphNode->GetDests();
					int _nSize = _arrDestinations.GetSize();
					for (int _i = 0; _i < _nSize; _i++)
					{
						Node* _pRelatedNode = nullptr;
						m_tKeyToNodeMap.Search(_arrDestinations[_i], _pRelatedNode);
						if (_pRelatedNode == nullptr)
						{
							throw "unexpected error";
						}

						if (_pRelatedNode->m_nBfvPathDistance == -1)
						{
							_pRelatedNode->m_pBfvPathNode = _pNode;
							_pRelatedNode->m_nBfvPathDistance = _pNode->m_nBfvPathDistance + 1;
							_qpNodes.In(_pRelatedNode);
						}
					}
				}

				_arrPairs = m_tKeyToNodeMap.GetArray();
				DataStruct::Array::DynArray<Node*> _arrpNodes;
				for (int _i = 0; _i < _arrPairs.GetSize(); _i++)
				{
					_arrpNodes.Add(_arrPairs[_i].m_nValue);
				}

				return _arrpNodes;
			}
		}
	}
}

#endif

