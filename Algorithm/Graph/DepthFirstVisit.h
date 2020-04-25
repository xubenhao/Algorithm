//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_ALGORITHM_GRAPH_DEPTHFIRSTVISIT_H
#define AILIB_ALGORITHM_GRAPH_DEPTHFIRSTVISIT_H
#include "..\..\stdafx.h"
#include "..\..\DataStruct\Graph\Graph.h"
#include "..\..\DataStruct\Stack\DynStack.h"

namespace AlLib
{
	namespace Algorithm
	{
		namespace Graph
		{
			template<typename Key, typename Value>
			class DepthFirstVisit
			{
			public:
				enum State
				{
					UnVisit,
					Visiting,
					Visited
				};

				class Node;
				typename typedef DataStruct::GraphStruct::Graph<Key, Value> InnerGraph;
				typename typedef DataStruct::Tree::SortedBalanceBinaryTree<Key, Node*> InnerTree;

				class Node
				{
				public:
					int GetFirstVisitTime()
					{
						return m_nFirstVisitTime;
					}

					int GetLastVisitTime()
					{
						return m_nLastVisitTime;
					}

					typename InnerGraph::Node* GetGraphNode()
					{
						return m_pGraphNode;
					}

					Node* GetPreNode()
					{
						return m_pPreNode;
					}
				private:
					Node()
					{
						m_pGraphNode = nullptr;
						m_pPreNode = nullptr;
						m_nFirstVisitTime = 0;
						m_nLastVisitTime = 0;
						m_nState = State::UnVisit;
					}

					Node(typename InnerGraph::Node* pGraphNode_)
					{
						m_pGraphNode = pGraphNode_;
						m_pPreNode = nullptr;
						m_nFirstVisitTime = 0;
						m_nLastVisitTime = 0;
						m_nState = State::UnVisit;
					}

					~Node()
					{
					}

					void Reset()
					{
						m_pPreNode = nullptr;
						m_nFirstVisitTime = 0;
						m_nLastVisitTime = 0;
						m_nState = State::UnVisit;
					}

				private:
					typename InnerGraph::Node* m_pGraphNode;
					Node* m_pPreNode;
					int m_nFirstVisitTime;
					int m_nLastVisitTime;
					State m_nState;

					friend class DepthFirstVisit;
				};

				DepthFirstVisit(const InnerGraph& nGraph_);
				~DepthFirstVisit();

				DataStruct::Array::DynArray<Node*> Run();
			private:
				DepthFirstVisit(const DepthFirstVisit& nDFV_) = default;
				DepthFirstVisit& operator=(const DepthFirstVisit& nDFV_) = default;
			private:
				void Visit(Node* pNode_, int& nTime_);
			private:
				InnerGraph m_nGraph;
				InnerTree m_nNodeMappingTree;
			};

			template<typename Key, typename Value>
			DepthFirstVisit<Key, Value>::DepthFirstVisit(const InnerGraph& nGraph_)
				: m_nGraph(nGraph_)
			{
				DataStruct::Array::DynArray<InnerGraph::Node*> _arrGraphNodes = m_nGraph.GetNodesArray();
				for (int _i = 0; _i < _arrGraphNodes.GetSize(); _i++)
				{
					if (_arrGraphNodes[_i] == nullptr)
					{
						throw "graph node cannot be null";
					}

					Node* _pNode = nullptr;
					try
					{
						_pNode = new Node(_arrGraphNodes[_i]);
					}
					catch (...)
					{
						_pNode = nullptr;
						throw "out of memory";
					}

					InnerTree::Pair _nPair;
					InnerGraph::Pair _nGraphPair = _arrGraphNodes[_i]->GetPair();
					_nPair.m_nKey = _nGraphPair.m_nKey;
					_nPair.m_nValue = _pNode;
					m_nNodeMappingTree.Add(_nPair);
				}
			}

			template<typename Key, typename Value>
			DepthFirstVisit<Key, Value>::~DepthFirstVisit()
			{
				DataStruct::Array::DynArray<InnerTree::Pair> _arrTreePairs = m_nNodeMappingTree.GetArray();
				for (int _i = 0; _i < _arrTreePairs.GetSize(); _i++)
				{
					delete (_arrTreePairs[_i].m_nValue);
					_arrTreePairs[_i].m_nValue = nullptr;
				}
			}

			template<typename Key, typename Value>
			DataStruct::Array::DynArray<typename DepthFirstVisit<Key, Value>::Node*> DepthFirstVisit<Key, Value>::Run()
			{
				DataStruct::Array::DynArray<Node*> _arrpNodes;
				DataStruct::Array::DynArray<InnerTree::Pair>_arrTreePairs = m_nNodeMappingTree.GetArray();
				for (int _i = 0; _i < _arrTreePairs.GetSize(); _i++)
				{
					_arrpNodes.Add(_arrTreePairs[_i].m_nValue);
					_arrpNodes[_i]->Reset();
				}

				int _nTime = 0;
				for (int _i = 0; _i < _arrTreePairs.GetSize(); _i++)
				{
					Node* _pNode = _arrTreePairs[_i].m_nValue;
					if (_pNode->m_nState == State::UnVisit)
					{
						Visit(_pNode, _nTime);
					}
				}

				return _arrpNodes;
			}

			template<typename Key, typename Value>
			void DepthFirstVisit<Key, Value>::Visit(Node* pNode_, int& nTime_)
			{
				nTime_++;
				pNode_->m_nFirstVisitTime = nTime_;
				pNode_->m_nState = State::Visiting;
				DataStruct::Array::DynArray<Key> _arrDestinations = pNode_->m_pGraphNode->GetDests();
				for (int _k = 0; _k < _arrDestinations.GetSize(); _k++)
				{
					Node* _pDestNode = nullptr;
					bool _bRet = m_nNodeMappingTree.Search(_arrDestinations[_k], _pDestNode);
					if (_bRet == false)
					{
						throw "node key cannot find in graph's nodes";
					}

					if (_pDestNode->m_nState == State::UnVisit)
					{
						_pDestNode->m_pPreNode = pNode_;
						Visit(_pDestNode, nTime_);
					}
				}

				nTime_++;
				pNode_->m_nLastVisitTime = nTime_;
				pNode_->m_nState = State::Visited;
			}
		}
	}
}

#endif
