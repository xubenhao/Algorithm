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
				DataStruct::Array::DynArray<Node*> RunForWeightNoNegtive(const Key& nSourceKey_);
				DataStruct::Array::DynArray<Node*> RunForNoCircle(const Key& nSourceKey_);
			private:
				ShorestPath(const ShorestPath&) = default;
				ShorestPath& operator=(const ShorestPath&) = default;
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
				DataStruct::Array::DynArray<InnerTree::Pair> _arrTreePairs = m_nNodeMappingTree.GetArray();
				for (int _i = 0; _i < _arrTreePairs.GetSize(); _i++)
				{
					delete (_arrTreePairs[_i].m_nValue);
					_arrTreePairs[_i].m_nValue = nullptr;
				}
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

			template<typename Key, typename Value>
			DataStruct::Array::DynArray<typename ShorestPath<Key, Value>::Node*> ShorestPath<Key, Value>::RunForWeightNoNegtive(const Key& nSourceKey_)
			{
				InnerGraph::Node* _pGraphNode = m_nGraph.SearchNode(nSourceKey_);
				if (_pGraphNode == nullptr)
				{
					throw "can not find key in graph";
				}

				DataStruct::Array::DynArray<Node*> _arrpNodes;
				DataStruct::Array::DynArray<Node*> _arrpRetNodes;
				DataStruct::Array::DynArray<InnerTree::Pair>_arrTreePairs = m_nNodeMappingTree.GetArray();
				for (int _i = 0; _i < _arrTreePairs.GetSize(); _i++)
				{
					_arrpNodes.Add(_arrTreePairs[_i].m_nValue);
					_arrpNodes[_i]->Reset();
				}

				DataStruct::Array::DynArray<typename InnerGraph::Node*> _arrGraphNodes = m_nGraph.GetNodesArray();
				DataStruct::Array::DynArray<typename InnerGraph::Edge*> _arrGraphEdges = m_nGraph.GetEdgesArray();
				while (_arrpNodes.GetSize() > 0)
				{
					Node* _pNode = nullptr;
					// 从节点集合1选出距离最短的Node
					for (int _i = 0; _i < _arrpNodes.GetSize(); _i++)
					{
						if (_arrpNodes[_i]->m_pPreNode != nullptr
							|| _arrpNodes[_i]->m_pGraphNode == _pGraphNode)
						{
							if (_pNode == nullptr
								|| _pNode->m_nDistance > _arrpNodes[_i]->m_nDistance)
							{
								_pNode = _arrpNodes[_i];
							}
						}
					}

					
					if (_pNode != nullptr)
					{
						// 选出的Node放入另一Node集合
						_arrpNodes.DeleteByValue(_pNode);
						_arrpRetNodes.Add(_pNode);
						// 对所有该节点可达节点
						DataStruct::Array::DynArray<Key> _arrDestinations = _pNode->m_pGraphNode->GetDests();
						for (int _i = 0; _i < _arrDestinations.GetSize(); _i++)
						{
							Node* _pDestNode = nullptr;
							m_nNodeMappingTree.Search(_arrDestinations[_i], _pDestNode);
							if (_pDestNode == nullptr)
							{
								throw "cannot find dest in graph";
							}

							InnerGraph::EdgeIdentity _nIdentity;
							_nIdentity.m_nStartKey = _pNode->m_pGraphNode->GetPair().m_nKey;
							_nIdentity.m_nEndKey = _arrDestinations[_i];
							InnerGraph::Edge* _pEdge = m_nGraph.SearchEdge(_nIdentity);
							if (_pEdge == nullptr)
							{
								throw "cannot find edge";
							}

							// 对可达节点进行松弛判断
							if ((_pDestNode->m_pPreNode == nullptr && _pDestNode->m_pGraphNode != _pGraphNode)
								|| _pDestNode->m_nDistance > _pNode->m_nDistance + _pEdge->m_nWeight)
							{
								_pDestNode->m_pPreNode = _pNode;
								_pDestNode->m_nDistance = _pNode->m_nDistance + _pEdge->m_nWeight;
							}
						}
					}
					// 选不出来，表示剩余Node均为不可达的
					else
					{
						for (int _i = 0; _i < _arrpNodes.GetSize(); _i++)
						{
							_arrpRetNodes.Add(_arrpNodes[_i]);
						}

						_arrpNodes.DeleteAll();
					}
				}

				return _arrpRetNodes;
			}

			template<typename Key, typename Value>
			DataStruct::Array::DynArray<typename ShorestPath<Key, Value>::Node*> ShorestPath<Key, Value>::RunForNoCircle(const Key& nSourceKey_)
			{
				InnerGraph::Node* _pSourceNode = m_nGraph.SearchNode(nSourceKey_);
				if (_pSourceNode == nullptr)
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

				TopologySort<Key, Value> _alTopologySort(m_nGraph);
				DataStruct::Array::DynArray<typename DepthFirstVisit<Key, Value>::Node*> _arrTempNodes = _alTopologySort.Run();
				DataStruct::Array::DynArray<Key> _arrKeys;
				for (int _i = 0; _i < _arrTempNodes.GetSize(); _i++)
				{
					InnerGraph::Node* _pNode = _arrTempNodes[_i]->GetGraphNode();
					if (_pNode == nullptr)
					{
						throw "graph node not exist";
					}

					_arrKeys.Add(_pNode->GetPair().m_nKey);
				}

				// 对按拓扑排序处理的所有节点
				for (int _i = 0; _i < _arrKeys.GetSize(); _i++)
				{
					int _nKey = _arrKeys[_i];
					Node* _pNode = nullptr;
					m_nNodeMappingTree.Search(_nKey, _pNode);
					if (_pNode == nullptr)
					{
						throw "node not exist";
					}

					InnerGraph::Node* _pGraphNode = _pNode->m_pGraphNode;
					DataStruct::Array::DynArray<Key> _arrDestKeys = _pGraphNode->GetDests();
					// 依次处理每个节点所有可达节点
					for (int _j = 0; _j < _arrDestKeys.GetSize(); _j++)
					{
						if (_pNode->m_pPreNode != nullptr
							|| _pNode->m_pGraphNode == _pSourceNode)
						{
							Node* _pDestNode = nullptr;
							m_nNodeMappingTree.Search(_arrDestKeys[_j], _pDestNode);
							if (_pDestNode == nullptr)
							{
								throw "dest node not exist";
							}

							InnerGraph::EdgeIdentity _nIdentity;
							_nIdentity.m_nStartKey = _pNode->m_pGraphNode->GetPair().m_nKey;
							_nIdentity.m_nEndKey = _pDestNode->m_pGraphNode->GetPair().m_nKey;
							InnerGraph::Edge* _pEdge = nullptr;
							_pEdge = m_nGraph.SearchEdge(_nIdentity);
							if (_pEdge == nullptr)
							{
								throw "edge not exist";
							}

							// 对可达节点进行松弛操作
							if ((_pDestNode->m_pPreNode == nullptr && _pDestNode->m_pGraphNode != _pSourceNode)
								|| (_pDestNode->m_nDistance > _pNode->m_nDistance + _pEdge->m_nWeight))
							{
								_pDestNode->m_pPreNode = _pNode;
								_pDestNode->m_nDistance = _pNode->m_nDistance + _pEdge->m_nWeight;
							}
						}
					}
				}

				return _arrpNodes;
			}

		}
	}
}

#endif
