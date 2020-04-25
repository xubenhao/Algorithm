//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_ALGORITHM_GRAPH_TOPOLOGYSORT_H
#define AILIB_ALGORITHM_GRAPH_TOPOLOGYSORT_H
#include "..\..\stdafx.h"
#include "..\..\DataStruct\Graph\Graph.h"
#include "DepthFirstVisit.h"
#include "..\Sort\Sort.h"

namespace AlLib
{
	namespace Algorithm
	{
		namespace Graph
		{
			template<typename Key, typename Value>
			class TopologySort
			{
			public:
				typename typedef DataStruct::GraphStruct::Graph<Key, Value> InnerGraph;
				TopologySort(const InnerGraph& nGraph_);
				~TopologySort();

				DataStruct::Array::DynArray<typename DepthFirstVisit<Key, Value>::Node*> Run();
			private:
				TopologySort(const TopologySort& nTopoAl_) = default;
				TopologySort& operator=(const TopologySort& nTopoAl_) = default;

			private:
				typename DepthFirstVisit<Key, Value> m_alDepthFirstVisit;
			};

			template<typename Key, typename Value>
			TopologySort<Key, Value>::TopologySort(const InnerGraph& nGraph_)
				: m_alDepthFirstVisit(nGraph_)
			{

			}

			template<typename Key, typename Value>
			TopologySort<Key, Value>::~TopologySort()
			{

			}

			template<typename Key, typename Value>
			DataStruct::Array::DynArray<typename DepthFirstVisit<Key, Value>::Node*> TopologySort<Key, Value>::Run()
			{
				DataStruct::Array::DynArray<typename DepthFirstVisit<Key, Value>::Node*> _arrNodes = m_alDepthFirstVisit.Run();
				_arrNodes.Sort([](DepthFirstVisit<Key, Value>::Node* pNode1_, DepthFirstVisit<Key, Value>::Node* pNode2_)
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

				return _arrNodes;
			}
		}
	}
}

#endif
