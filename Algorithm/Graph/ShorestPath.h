//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_ALGORITHM_GRAPH_SHORESTPATH_H
#define AILIB_ALGORITHM_GRAPH_SHORESTPATH_H
#include "..\..\stdafx.h"
#include "..\..\DataStruct\Graph\Graph.h"
#include "TopologySort.h"

namespace AlLib
{
	namespace Algorithm
	{
		namespace Graph
		{
			template<typename Key, typename Value>
			class ShorestPath
			{
			public:
				class Node;
				typename typedef DataStruct::GraphStruct::Graph<Key, Value> InnerGraph;
				typename typedef DataStruct::Tree::SortedBalanceBinaryTree<Key, Node*> InnerTree;

				class Node
				{
				public:
					double GetDistance()
					{
						return m_nDistance;
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
						m_nDistance = -1.0;
						m_pGraphNode = nullptr;
						m_pPreNode = nullptr;
					}

					Node(typename InnerGraph::Node* pGraphNode_)
					{
						m_nDistance = -1.0;
						m_pGraphNode = pGraphNode_;
						m_pPreNode = nullptr;
					}

					~Node()
					{
					}

					void Reset()
					{
						m_pPreNode = nullptr;
						m_nDistance = 0;
					}

				private:
					double m_nDistance;
					typename InnerGraph::Node* m_pGraphNode;
					Node* m_pPreNode;
					friend class ShorestPath;
				};

				ShorestPath(const InnerGraph& nGraph_);
				~ShorestPath();

				DataStruct::Array::DynArray<Node*> Run(const Key& nSourceKey_);
				/*DataStruct::Array::DynArray<Node*> RunForWeightNoNegtive(const Key& nSourceKey_);
				DataStruct::Array::DynArray<Node*> RunForNoCircle(const Key& nSourceKey_);*/
			private:
				const InnerGraph& m_nGraph;
				InnerTree m_nNodeMappingTree;
			};

			template<typename Key, typename Value>
			ShorestPath<Key, Value>::ShorestPath(const InnerGraph& nGraph_)
				: m_nGraph(nGraph_)
			{
				DataStruct::Array::DynArray<typename InnerGraph::Node*> _arrGraphNodes = m_nGraph.GetNodesArray();
				for (int _i = 0; _i < _arrGraphNodes.GetSize(); _i++)
				{
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
					_nPair.m_nKey = _arrGraphNodes[_i]->GetPair().m_nKey;
					_nPair.m_nValue = _pNode;
					m_nNodeMappingTree.Add(_nPair);
				}
			}

			template<typename Key, typename Value>
			ShorestPath<Key, Value>::~ShorestPath()
			{

			}

			template<typename Key, typename Value>
			DataStruct::Array::DynArray<typename ShorestPath<Key, Value>::Node*> ShorestPath<Key, Value>::Run(const Key& nSourceKey_)
			{
				InnerGraph::Node* _pGraphNode = m_nGraph.SearchNode(nSourceKey_);
				if (_pGraphNode == nullptr)
				{
					throw "can not find key in graph";
				}

				DataStruct::Array::DynArray<Node*> _arrpNodes;
				DataStruct::Array::DynArray<InnerTree::Pair>_arrTreePairs = m_nNodeMappingTree.GetArray();
				for (int _i = 0; _i < _arrTreePairs.GetSize(); _i++)
				{
					_arrpNodes.Add(_arrTreePairs[_i].m_nValue);
					_arrpNodes[_i]->Reset();
				}

				DataStruct::Array::DynArray<typename InnerGraph::Node*> _arrGraphNodes = m_nGraph.GetNodesArray();
				DataStruct::Array::DynArray<typename InnerGraph::Edge*> _arrGraphEdges = m_nGraph.GetEdgesArray();
				for (int _i = 0; _i < _arrGraphNodes.GetSize(); _i++)
				{
					for (int _j = 0; _j < _arrGraphEdges.GetSize(); _j++)
					{
						InnerGraph::EdgeIdentity _nIndentity = _arrGraphEdges[_j]->GetIdentity();
						Node* _pNode = nullptr;
						m_nNodeMappingTree.Search(_nIndentity.m_nStartKey, _pNode);
						if (_pNode == nullptr)
						{
							throw "cannot find key in tree";
						}

						if (_pNode->m_pPreNode == nullptr
							&& _pNode->m_pGraphNode != _pGraphNode)
						{
							continue;
						}

						if (_pNode->m_pGraphNode == _pGraphNode)
						{
							_pNode->m_nDistance = 0;
						}

						Node* _pNode2 = nullptr;
						m_nNodeMappingTree.Search(_nIndentity.m_nEndKey, _pNode2);
						if (_pNode2 == nullptr)
						{
							throw "can not find key in tree";
						}

						if ((_pNode2->m_pPreNode == nullptr
							&& _pNode2->m_pGraphNode != _pGraphNode)
							|| (_pNode->m_nDistance + _arrGraphEdges[_j]->m_nWeight) < _pNode2->m_nDistance)
						{
							_pNode2->m_pPreNode = _pNode;
							_pNode2->m_nDistance = _pNode->m_nDistance + _arrGraphEdges[_j]->m_nWeight;
						}
					}
				}

				bool _bSuccess = true;
				for (int _j = 0; _j < _arrGraphEdges.GetSize(); _j++)
				{
					InnerGraph::EdgeIdentity _nIndentity = _arrGraphEdges[_j]->GetIdentity();
					Node* _pNode = nullptr;
					m_nNodeMappingTree.Search(_nIndentity.m_nStartKey, _pNode);
					if (_pNode->m_pPreNode != nullptr
						|| _pNode->m_pGraphNode == _pGraphNode)
					{
						Node* _pNode2 = nullptr;
						m_nNodeMappingTree.Search(_nIndentity.m_nEndKey, _pNode2);
						if ((_pNode2->m_pPreNode == nullptr && _pNode2->m_pGraphNode != _pGraphNode)
							|| (_pNode->m_nDistance + _arrGraphEdges[_j]->m_nWeight) < _pNode2->m_nDistance)
						{
							_bSuccess = false;
							break;
						}
					}
				}

				if (_bSuccess == false)
				{
					throw "shortest path is not exist";
				}
				
				return _arrpNodes;
			}
		}
	}
}

#endif
