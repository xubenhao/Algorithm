//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_ALGORITHM_GRAPH_REVERSEGRAPH_H
#define AILIB_ALGORITHM_GRAPH_REVERSEGRAPH_H
#include "..\..\stdafx.h"
#include "..\..\DataStruct\Graph\Graph.h"

namespace AlLib
{
	namespace Algorithm
	{
		namespace Graph
		{
			template<typename Key, typename Value>
			class ReverseGraph
			{
			public:
				typename typedef DataStruct::GraphStruct::Graph<Key, Value> InnerGraph;
				ReverseGraph(const InnerGraph& nGraph_);
				~ReverseGraph();

				InnerGraph Run();
			private:
				ReverseGraph(const ReverseGraph& nGraph_) = default;
				ReverseGraph& operator=(const ReverseGraph& nGraph_) = default;

			private:
				const InnerGraph& m_nGraph;
			};

			template<typename Key, typename Value>
			ReverseGraph<Key, Value>::ReverseGraph(const InnerGraph& nGraph_)
				: m_nGraph(nGraph_)
			{

			}

			template<typename Key, typename Value>
			ReverseGraph<Key, Value>::~ReverseGraph()
			{

			}

			template<typename Key, typename Value>
			typename DataStruct::GraphStruct::Graph<Key, Value> ReverseGraph<Key, Value>::Run()
			{
				InnerGraph _nGraph;
				DataStruct::Array::DynArray<typename InnerGraph::Node*> _arrNodes = m_nGraph.GetNodesArray();
				for (int _i = 0; _i < _arrNodes.GetSize(); _i++)
				{
					_nGraph.AddNode(_arrNodes[_i]->GetPair());
				}

				DataStruct::Array::DynArray<typename InnerGraph::Edge*> _arrEdges = m_nGraph.GetEdgesArray();
				for (int _i = 0; _i < _arrEdges.GetSize(); _i++)
				{
					_nGraph.AddEdge(_arrEdges[_i]->GetIdentity().Reverse());
				}

				return _nGraph;
			}
		}
	}
}
#endif
