//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_ALGORITHM_GRAPH_STRONGCONNECTGRAPH_H
#define AILIB_ALGORITHM_GRAPH_STRONGCONNECTGRAPH_H
#include "..\..\stdafx.h"
#include "..\..\DataStruct\Graph\Graph.h"
#include "DepthFirstVisit.h"
#include "ReverseGraph.h"

namespace AlLib
{
	namespace Algorithm
	{
		namespace Graph
		{
			template<typename Key, typename Value>
			class StrongConnectGraph
			{
			public:
				typename typedef DataStruct::GraphStruct::Graph<Key, Value> InnerGraph;
				StrongConnectGraph(const InnerGraph& nGraph_);
				~StrongConnectGraph();

				DataStruct::Array::DynArray<typename DepthFirstVisit<Key, Value>::Node*> Run();
			private:
				StrongConnectGraph(const StrongConnectGraph& nSCG_) = default;
				StrongConnectGraph& operator=(const StrongConnectGraph& nSCG_) = default;
			private:
				const InnerGraph& m_nGraph;
				InnerGraph* m_pReverseGraph;
				typename DepthFirstVisit<Key, Value>* m_pDepthFirstVisit;
			};

			template<typename Key, typename Value>
			StrongConnectGraph<Key, Value>::StrongConnectGraph(const InnerGraph& nGraph_)
				: m_nGraph(nGraph_), m_pReverseGraph(nullptr), m_pDepthFirstVisit(nullptr)
			{

			}

			template<typename Key, typename Value>
			StrongConnectGraph<Key, Value>::~StrongConnectGraph()
			{
				if (m_pReverseGraph != nullptr)
				{
					delete m_pReverseGraph;
					m_pReverseGraph = nullptr;
				}

				if (m_pDepthFirstVisit == nullptr)
				{
					delete m_pDepthFirstVisit;
					m_pDepthFirstVisit = nullptr;
				}
			}

			template<typename Key, typename Value>
			DataStruct::Array::DynArray<typename DepthFirstVisit<Key, Value>::Node*> StrongConnectGraph<Key, Value>::Run()
			{
				DepthFirstVisit<Key, Value> _alDepthFirstVisit(m_nGraph);
				DataStruct::Array::DynArray<typename DepthFirstVisit<Key, Value>::Node*> _arrNodes = _alDepthFirstVisit.Run();
				_arrNodes.Sort([](typename DepthFirstVisit<Key, Value>::Node* pNode1_, typename DepthFirstVisit<Key, Value>::Node* pNode2_)->int
				{
					int _nRet = pNode1_->GetLastVisitTime() - pNode2_->GetLastVisitTime();
					if (_nRet > 0)
					{
						return -1;
					}
					else if (_nRet < 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				});

				DataStruct::Array::DynArray<Key> _arrKeys;
				for (int _i = 0; _i < _arrNodes.GetSize(); _i++)
				{
					typename InnerGraph::Pair _nPair = _arrNodes[_i]->GetGraphNode()->GetPair();
					_arrKeys.Add(_nPair.m_nKey);
				}

				ReverseGraph<Key, Value> _alReverseGraph(m_nGraph);
				if (m_pReverseGraph != nullptr)
				{
					delete m_pReverseGraph;
					m_pReverseGraph = nullptr;
				}

				if (m_pDepthFirstVisit == nullptr)
				{
					delete m_pDepthFirstVisit;
					m_pDepthFirstVisit = nullptr;
				}

				try
				{
					m_pReverseGraph = new InnerGraph(_alReverseGraph.Run());
					m_pDepthFirstVisit = new DepthFirstVisit<Key, Value>(*m_pReverseGraph);
				}
				catch (...)
				{
					throw "out of memory";
					m_pReverseGraph = nullptr;
					m_pDepthFirstVisit = nullptr;
				}
				
				return m_pDepthFirstVisit->Run(_arrKeys);
			}
		}
	}
}

#endif
