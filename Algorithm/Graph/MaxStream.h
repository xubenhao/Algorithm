//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_ALGORITHM_GRAPH_MAXSTREAM_H
#define AILIB_ALGORITHM_GRAPH_MAXSTREAM_H
#include "..\..\stdafx.h"
#include "..\..\DataStruct\Graph\Graph.h"
#include "BreadthFirstVisit.h"

namespace AlLib
{
	namespace Algorithm
	{
		namespace Graph
		{
			template<typename Key, typename Value>
			class MaxStream
			{
			public:
				typename typedef DataStruct::GraphStruct::Graph<Key, Value> InnerGraph;

				MaxStream(const InnerGraph& nGraph_);
				~MaxStream();
				typename InnerGraph Run(const Key& nSourceKey_, const Key& nDestKey_);

			private:
				void GetAdjustGraph(const InnerGraph& nStreamGraph_, 
					const InnerGraph& nGraph_,
					InnerGraph& nAdjustGraph_);
			private:
				MaxStream(const MaxStream&) = default;
				MaxStream& operator=(const MaxStream&) = default;
			private:
				const InnerGraph& m_nGraph;
			};

			template<typename Key, typename Value>
			MaxStream<Key, Value>::MaxStream(const InnerGraph& nGraph_)
				: m_nGraph(nGraph_)
			{

			}

			template<typename Key, typename Value>
			MaxStream<Key, Value>::~MaxStream()
			{

			}

			template<typename Key, typename Value>
			typename DataStruct::GraphStruct::Graph<Key, Value> MaxStream<Key, Value>::Run(const Key& nSourceKey_, const Key& nDestKey_)
			{
				// 流图
				InnerGraph _nStreamGraph = m_nGraph;
				DataStruct::Array::DynArray<typename InnerGraph::Edge*> _arrEdges = _nStreamGraph.GetEdgesArray();
				for (int _i = 0; _i < _arrEdges.GetSize(); _i++)
				{
					_arrEdges[_i]->m_nWeight = 0.0;
				}

				while (true)
				{
					// 构造流图相匹配的调节图
					DataStruct::Array::DynArray<typename InnerGraph::Node*> _arrNodes = _nStreamGraph.GetNodesArray();
					InnerGraph _nAdjustGraph;
					for (int _i = 0; _i < _arrNodes.GetSize(); _i++)
					{
						_nAdjustGraph.AddNode(_arrNodes[_i]->GetPair());
					}

					// 基于流图，原始图得到调节图
					GetAdjustGraph(_nStreamGraph, m_nGraph, _nAdjustGraph);
					BreadthFirstVisit<Key, Value> _alBreathFirst(_nAdjustGraph);
					DataStruct::Array::DynArray<typename BreadthFirstVisit<Key, Value>::Node*> _arrBreadthNodes = _alBreathFirst.Run(nSourceKey_);
					BreadthFirstVisit<Key, Value>::Node* _pDest = nullptr;
					for (int _i = 0; _arrBreadthNodes.GetSize(); _i++)
					{
						if (_arrBreadthNodes[_i]->GetGraphNode() == nullptr)
						{
							throw "graph node not exist";
						}

						if (_arrBreadthNodes[_i]->GetGraphNode()->GetPair().m_nKey == nDestKey_)
						{
							_pDest = _arrBreadthNodes[_i];
							break;
						}
					}

					if (_pDest->GetPreNode() == nullptr)
					{
						break;
					}

					DataStruct::Array::DynArray<typename InnerGraph::EdgeIdentity> _arrEdgesOnPath;
					typename InnerGraph::EdgeIdentity _nEdgeIdentity;
					if (_pDest->GetPreNode()->GetGraphNode() == nullptr)
					{
						throw "pre graph node not exist";
					}

					_nEdgeIdentity.m_nStartKey = _pDest->GetPreNode()->GetGraphNode()->GetPair().m_nKey;
					if (_pDest->GetGraphNode() == nullptr)
					{
						throw "graph node not exist";
					}

					_nEdgeIdentity.m_nEndKey = _pDest->GetGraphNode()->GetPair().m_nKey;
					typename InnerGraph::Edge* _pEdge = _nAdjustGraph.SearchEdge(_nEdgeIdentity);
					if (_pEdge == nullptr)
					{
						throw "edge not exist";
					}

					double _nMinWeight = _pEdge->m_nWeight;
					while (_pDest->GetPreNode() != nullptr)
					{
						if (_pDest->GetPreNode()->GetGraphNode() == nullptr)
						{
							throw "pre graph node not exist";
						}

						_nEdgeIdentity.m_nStartKey = _pDest->GetPreNode()->GetGraphNode()->GetPair().m_nKey;
						if (_pDest->GetGraphNode() == nullptr)
						{
							throw "graph node not exist";
						}

						_nEdgeIdentity.m_nEndKey = _pDest->GetGraphNode()->GetPair().m_nKey;
						_arrEdgesOnPath.Add(_nEdgeIdentity);
						_pEdge = _nAdjustGraph.SearchEdge(_nEdgeIdentity);
						if (_pEdge == nullptr)
						{
							throw "edge not exist";
						}

						if (_pEdge->m_nWeight < _nMinWeight)
						{
							_nMinWeight = _pEdge->m_nWeight;
						}

						_pDest = _pDest->GetPreNode();
					}

					for (int _i = 0; _i < _arrEdgesOnPath.GetSize(); _i++)
					{
						_nEdgeIdentity = _arrEdgesOnPath[_i];
						_pEdge = _nStreamGraph.SearchEdge(_nEdgeIdentity);
						if (_pEdge != nullptr)
						{
							_pEdge->m_nWeight += _nMinWeight;
						}
						else
						{
							_pEdge = _nStreamGraph.SearchEdge(_nEdgeIdentity.Reverse());
							if (_pEdge != nullptr)
							{
								_pEdge->m_nWeight -= _nMinWeight;
							}
							else
							{
								throw "unexpected exception";
							}
						}
					}
				}

				return _nStreamGraph;
			}

			template<typename Key, typename Value>
			void MaxStream<Key, Value>::GetAdjustGraph(
				const InnerGraph& nStreamGraph_,
				const InnerGraph& nGraph_,
				InnerGraph& nAdjustGraph_)
			{
				DataStruct::Array::DynArray<typename InnerGraph::Edge*> _arrEdges = nStreamGraph_.GetEdgesArray();
				for (int _i = 0; _i < _arrEdges.GetSize(); _i++)
				{
					InnerGraph::EdgeIdentity _nIdentity = _arrEdges[_i]->GetIdentity();
					double _nStream = _arrEdges[_i]->m_nWeight;
					InnerGraph::Edge* _pOriginEdge = nGraph_.SearchEdge(_nIdentity);
					if (_pOriginEdge == nullptr)
					{
						throw "edge not exist";
					}

					double _nWeight = _pOriginEdge->m_nWeight;
					if (_nWeight - _nStream < 0.0)
					{
						throw "unexpected error";
					}

					if (_nWeight - _nStream > 0.0)
					{
						nAdjustGraph_.AddEdge(_nIdentity);
						InnerGraph::Edge* _pEdge = nAdjustGraph_.SearchEdge(_nIdentity);
						if (_pEdge == nullptr)
						{
							throw "edge not exist";
						}

						_pEdge->m_nWeight = _nWeight - _nStream;
					}

					if (_nStream < 0.0)
					{
						throw "unexpected error";
					}

					if (_nStream > 0.0)
					{
						nAdjustGraph_.AddEdge(_nIdentity.Reverse());
						InnerGraph::Edge* _pEdge = nAdjustGraph_.SearchEdge(_nIdentity.Reverse());
						if (_pEdge == nullptr)
						{
							throw "edge not exist";
						}

						_pEdge->m_nWeight = _nStream;
					}
				}
			}

		}
	}
}
#endif
