//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_ALGORITHM_GRAPH_MINGENERATETREE_H
#define AILIB_ALGORITHM_GRAPH_MINGENERATETREE_H
#include "..\..\stdafx.h"
#include "..\..\DataStruct\Graph\Graph.h"

namespace AlLib
{
	namespace Algorithm
	{
		namespace Graph
		{
			template<typename Key, typename Value>
			class MinGenerateTree
			{
			public:
				class Node;
				typename typedef DataStruct::GraphStruct::Graph<Key, Value> InnerGraph;
				typename typedef DataStruct::Tree::SortedBalanceBinaryTree<Key, Node*> InnerTree;

				class Tree
				{
				public:
					DataStruct::Array::DynArray<Key> GetKeys()
					{
						return m_arrNodeKeys;
					}

					DataStruct::Array::DynArray<typename InnerGraph::EdgeIdentity> GetEdges()
					{
						return m_arrEdgeKeys;
					}

				private:
					Tree()
					{

					}

					~Tree()
					{

					}

				private:
					DataStruct::Array::DynArray<Key> m_arrNodeKeys;
					DataStruct::Array::DynArray<typename InnerGraph::EdgeIdentity> m_arrEdgeKeys;
					friend class MinGenerateTree;
				};

				class Node
				{
				private:
					Node()
					{
						m_pNode = nullptr;
						m_pTree = nullptr;
					}

					Node(typename InnerGraph::Node* pNode_)
					{
						m_pNode = pNode_;
						m_pTree = nullptr;
					}

					~Node()
					{
					}

					void SetTree(Tree* pTree_)
					{
						m_pTree = pTree_;
					}
				private:
					typename InnerGraph::Node* m_pNode;
					Tree* m_pTree;
					friend class MinGenerateTree;
				};

				MinGenerateTree(const InnerGraph& nGraph_);
				~MinGenerateTree();

				Tree* RunForNoDirectionAndConnectedGraph();
			private:
				MinGenerateTree(const MinGenerateTree&) = default;
				MinGenerateTree& operator=(const MinGenerateTree&) = default;
			private:
				const InnerGraph& m_nGraph;
				InnerTree m_nNodeMappingTree;
				DataStruct::Array::DynArray<Tree*> m_arrpTrees;
			};

			template<typename Key, typename Value>
			MinGenerateTree<Key, Value>::MinGenerateTree(const InnerGraph& nGraph_)
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
			MinGenerateTree<Key, Value>::~MinGenerateTree()
			{
				DataStruct::Array::DynArray<InnerTree::Pair> _arrTreePairs = m_nNodeMappingTree.GetArray();
				for (int _i = 0; _i < _arrTreePairs.GetSize(); _i++)
				{
					delete (_arrTreePairs[_i].m_nValue);
					_arrTreePairs[_i].m_nValue = nullptr;
				}

				for (int _i = 0; _i < m_arrpTrees.GetSize(); _i++)
				{
					delete m_arrpTrees[_i];
					m_arrpTrees[_i] = nullptr;
				}
			}

			template<typename Key, typename Value>
			typename MinGenerateTree<Key, Value>::Tree* MinGenerateTree<Key, Value>::RunForNoDirectionAndConnectedGraph()
			{
				for (int _i = 0; _i < m_arrpTrees.GetSize(); _i++)
				{
					delete m_arrpTrees[_i];
					m_arrpTrees[_i] = nullptr;
				}

				m_arrpTrees.DeleteAll();
				DataStruct::Array::DynArray<InnerTree::Pair> _arrPairs = m_nNodeMappingTree.GetArray();
				for (int _i = 0; _i < _arrPairs.GetSize(); _i++)
				{
					Tree* _pTree = nullptr;
					try
					{
						_pTree = new Tree();
					}
					catch (...)
					{
						_pTree = nullptr;
						throw "out of memory";
					}

					_arrPairs[_i].m_nValue->SetTree(_pTree);
					_pTree->m_arrNodeKeys.Add(_arrPairs[_i].m_nKey);
					m_arrpTrees.Add(_pTree);
				}

				// �㷨���룺
				// ͼG
				// ����Ҫ��
				// ͼG���κα߾����ڷ����
				// ͼG������ڵ�p,q������p~q��q~p
				// �߰�Ȩ�����򡾱ߺ��䷴���ֻ��һ��������
				DataStruct::Array::DynArray<typename InnerGraph::Edge*> _arrEdges = m_nGraph.GetEdgesArray();
				_arrEdges.Sort(
					[](typename InnerGraph::Edge* pEdgeAddrA_, typename InnerGraph::Edge* pEdgeAddrB_)->int
				{
					double _nRet = (pEdgeAddrA_)->m_nWeight - (pEdgeAddrB_)->m_nWeight;
					if (_nRet > 0.0)
					{
						return 1;
					}
					else if (_nRet < 0.0)
					{
						return -1;
					}
					else
					{
						return 0;
					}
				});

				for (int _i = 0; _i < _arrEdges.GetSize(); _i++)
				{
					// ����Ͻڵ�p,q�ֱ����ڲ�ͬ��tree1,tree2��������tree1,tree2������tree1,tree2�ϲ�������tree12
					InnerGraph::EdgeIdentity _nEdgeIdentity = _arrEdges[_i]->GetIdentity();
					Node* _pNodeA = nullptr;
					Node* _pNodeB = nullptr;
					m_nNodeMappingTree.Search(_nEdgeIdentity.m_nStartKey, _pNodeA);
					if (_pNodeA == nullptr)
					{
						throw "cannot find node";
					}

					m_nNodeMappingTree.Search(_nEdgeIdentity.m_nEndKey, _pNodeB);
					if (_pNodeB == nullptr)
					{
						throw "cannot find node";
					}

					if (_pNodeA->m_pTree != _pNodeB->m_pTree)
					{
						Tree* _pUnionTree = nullptr;
						try
						{
							_pUnionTree = new Tree();
						}
						catch (...)
						{
							_pUnionTree = nullptr;
							throw "out of memory";
						}

						_pUnionTree->m_arrNodeKeys.AddRange(_pNodeA->m_pTree->m_arrNodeKeys);
						_pUnionTree->m_arrNodeKeys.AddRange(_pNodeB->m_pTree->m_arrNodeKeys);
						_pUnionTree->m_arrEdgeKeys.AddRange(_pNodeA->m_pTree->m_arrEdgeKeys);
						_pUnionTree->m_arrEdgeKeys.AddRange(_pNodeB->m_pTree->m_arrEdgeKeys);
						_pUnionTree->m_arrEdgeKeys.Add(_nEdgeIdentity);
						_pUnionTree->m_arrEdgeKeys.Add(_nEdgeIdentity.Reverse());
						m_arrpTrees.DeleteByValue(_pNodeA->m_pTree);
						m_arrpTrees.DeleteByValue(_pNodeB->m_pTree);
						delete _pNodeA->m_pTree;
						_pNodeA->m_pTree = nullptr;
						delete _pNodeB->m_pTree;
						_pNodeB->m_pTree = nullptr;

						for (int _k = 0; _k < _pUnionTree->m_arrNodeKeys.GetSize(); _k++)
						{
							Node* _pNode = nullptr;
							m_nNodeMappingTree.Search(_pUnionTree->m_arrNodeKeys[_k], _pNode);
							if (_pNode == nullptr)
							{
								throw "cannot find node";
							}

							_pNode->SetTree(_pUnionTree);
						}

						m_arrpTrees.Add(_pUnionTree);
					}
				}

				if (m_arrpTrees.GetSize() != 1)
				{
					throw "The input error,cannot calculate minimum generate tree";
				}

				return m_arrpTrees[0];
			}

			//template<typename Key, typename Value>
			//typename MinGenerateTree<Key, Value>::Tree* MinGenerateTree<Key, Value>::RunForNoDirectionAndConnectedGraph(const Key& nSourceKey_)
			//{
			//	Tree* _pTree = nullptr;
			//	DataStruct::Array::DynArray<Node*> _arrNodes;
			//	// ָ��һ����ʼ�Ľڵ�
			//	InnerGraph::Node* _pSourceNode = nullptr;
			//	_pSourceNode = m_nGraph.SearchNode(nSourceKey_);
			//	if (_pSourceNode == nullptr)
			//	{
			//		throw "source node is not exist";
			//	}

			//	DataStruct::Array::DynArray<typename InnerGraph::Node*> _arrGraphNodes = m_nGraph.GetNodesArray();
			//	InnerTree _nNodeMappingTree;
			//	// �Դ˽ڵ㹹��һ��������ʼʱ�����������С��������һ���Ӽ���
			//	for (int _i = 0; _i < _arrGraphNodes.GetSize(); _i++)
			//	{
			//		Node* _pNode = nullptr;
			//		try
			//		{
			//			_pNode = new Node();
			//		}
			//		catch (...)
			//		{
			//			_pNode = nullptr;
			//			throw "out of memory";
			//		}

			//		_pNode->m_pNode = _arrGraphNodes[_i];
			//		if (_pNode->m_pNode == _pSourceNode)
			//		{
			//			_pTree = nullptr;
			//			try
			//			{
			//				_pTree = new Tree();
			//			}
			//			catch (...)
			//			{
			//				_pTree = nullptr;
			//				throw "out of memory";
			//			}

			//			_pNode->m_pTree = _pTree;
			//			InnerGraph::Pair _nTempGraphPair = _pNode->m_pNode->GetPair();
			//			_pTree->m_arrNodeKeys.Add(_nTempGraphPair.m_nKey);
			//		}

			//		_arrNodes.Add(_pNode);
			//		InnerTree::Pair _nPair;
			//		InnerGraph::Pair _nGraphPair = _arrGraphNodes[_i]->GetPair();
			//		_nPair.m_nKey = _nGraphPair.m_nKey;
			//		_nPair.m_nValue = _pNode;
			//		_nNodeMappingTree.Add(_nPair);
			//	}

			//	// �߰�Ȩ�����򡾱ߺ��䷴���ֻ��һ��������
			//	DataStruct::Array::DynArray<typename InnerGraph::Edge*> _arrEdges = m_nGraph.GetEdgesArray();
			//	_arrEdges.Sort(
			//		[](typename InnerGraph::Edge* pEdgeAddrA_, typename InnerGraph::Edge* pEdgeAddrB_)->int
			//	{
			//		double _nRet = (pEdgeAddrA_)->m_nWeight - (pEdgeAddrB_)->m_nWeight;
			//		if (_nRet > 0.0)
			//		{
			//			return 1;
			//		}
			//		else if (_nRet < 0.0)
			//		{
			//			return -1;
			//		}
			//		else
			//		{
			//			return 0;
			//		}
			//	});

			//	// ѭ������ʽ��
			//	// _pTreeʼ����G��ĳ��С������T��һ����С��������

			//	// ��ʼʱ��
			//	// _pTree������һ���ڵ㣬�������ߣ�����ѭ������ʽ

			//	// ��k�ε���ʱ��
			//	// ǰk-1�ε�����ѭ������ʽ������
			//	// ��edgek������ʼ�ڵ�s,��ֹ�ڵ�e������_pTree�����β�����ѭ������ʽ�ڵ�������Ȼ����
			//	// ��edgek������ʼ�ڵ�s,��ֹ�ڵ�e��������_pTree�����β�����ѭ������ʽ�ڵ�������Ȼ����
			//	// ��edgek������ʼ�ڵ�s����_pTree����ֹ�ڵ�e������_pTree
			//	// ���÷�֤��֤��T�ı߼����б�Ȼ����(s,e)
			//	// ���ڴ�ʱ_pTree�нڵ㼯������һ��p
			//	// T�д���p~e��һ��·��
			//	// ·���ϱ�Ȼ����һ����(x,e) ���  {��ʱ_pTree�нڵ㼯��}��{e}�����ڵ㼯��

			//	// ������С����������
			//	// _pTree�б߼���+(x,e) �ǽڵ㼯��{��ʱ_pTree�нڵ㼯��+e}��һ����С������T'
			//	// ����
			//	// _pTree�б߼���+edgek�������ǽڵ㼯��{��ʱ_pTree�нڵ㼯��+e}��һ��������T''
			//	// ��weight(edgek) < weight(x,e)��T'����С����������T''Ҳ����С������

			//	// �ʵ��������
			//	// �õ���_pTree��Ȼ��ĳ��G��С������T��һ����������
			//	// ��֤

			//	// ��ֹ��
			//	// G����ͨͼ������ֹʱ��_pTree����T
			//	for (int _i = 0; _i < _arrEdges.GetSize(); _i++)
			//	{
			//		InnerGraph::Edge* _pEdge = _arrEdges[_i];
			//		InnerGraph::EdgeIdentity _nIdentity = _pEdge->GetIdentity();
			//		Node* _pStartNode = nullptr;
			//		Node* _pEndNode = nullptr;
			//		_nNodeMappingTree.Search(_nIdentity.m_nStartKey, _pStartNode);
			//		_nNodeMappingTree.Search(_nIdentity.m_nEndKey, _pEndNode);
			//		if ((_pStartNode->m_pTree == nullptr
			//			&& _pEndNode->m_pTree == _pTree))
			//		{
			//			_pTree->m_arrNodeKeys.Add(_nIdentity.m_nStartKey);
			//			_pTree->m_arrEdgeKeys.Add(_nIdentity);
			//			_pTree->m_arrEdgeKeys.Add(_nIdentity.Reverse());
			//		}
			//		else if ((_pStartNode->m_pTree == _pTree
			//			&& _pEndNode->m_pTree == nullptr))
			//		{
			//			_pTree->m_arrNodeKeys.Add(_nIdentity.m_nEndKey);
			//			_pTree->m_arrEdgeKeys.Add(_nIdentity);
			//			_pTree->m_arrEdgeKeys.Add(_nIdentity.Reverse());
			//		}
			//	}

			//	for (int _i = 0; _i < _arrNodes.GetSize(); _i++)
			//	{
			//		delete _arrNodes[_i];
			//		_arrNodes[_i] = nullptr;
			//	}

			//	return _pTree;
			//}
		}
	}
}

#endif
