#define ALGORITHMLIB __declspec(dllexport)
#include "SegmentIntersect.h"
#include "..\..\DataStruct\Tree\SortedBalanceBinaryTree.h"

namespace AlLib
{
	namespace Algorithm
	{
		namespace Geo
		{
			SegmentIntersection::LinePoint::LinePoint()
			{
				m_Type = POINT_TYPE::LEFT;
			}

			SegmentIntersection::LinePoint::~LinePoint()
			{

			}

			SegmentIntersection::LinePoint::LinePoint(
				Math::Point<2> poP_, 
				POINT_TYPE Type_)
			{
				m_poPos = poP_;
				m_Type = Type_;
			}

			SegmentIntersection::ComparableLineGeometry::ComparableLineGeometry()
			{

			}

			SegmentIntersection::ComparableLineGeometry::ComparableLineGeometry(
				const PlaneGeometry::LineGeometry& line_)
			{
				m_Line = line_;
			}

			SegmentIntersection::ComparableLineGeometry::~ComparableLineGeometry()
			{

			}

			bool SegmentIntersection::ComparableLineGeometry::operator<(
				const ComparableLineGeometry& cline_)
			{
				// С��
				// ���߶ζ�Ӧ���� �� ���߶���㵽�����߶���� ������������Ҫ ��ʱ����ת����ʱ�����߶� С�� �����߶�
				if (m_Line.m_poStart.m_nPos[0] < cline_.m_Line.m_poEnd.m_nPos[0])
				{
					Math::Vector<2> _vector1(m_Line.m_poStart, m_Line.m_poEnd);
					Math::Vector<2> _vector2(m_Line.m_poStart, cline_.m_Line.m_poStart);
					Geometry::ROTATE_DIRECTION _direc = Geometry::TestDirection(_vector1, _vector2);
					return (_direc == Geometry::ROTATE_DIRECTION::ANTICLOCK);
				}
				else
				{
					assert(m_Line.m_poStart.m_nPos[0] == cline_.m_Line.m_poEnd.m_nPos[0]);
					return m_Line.m_poStart.m_nPos[1] < cline_.m_Line.m_poEnd.m_nPos[1];
				}
			}

			bool SegmentIntersection::ComparableLineGeometry::operator==(const ComparableLineGeometry& cline_)
			{
				if (m_Line.m_poStart.m_nPos[0] < cline_.m_Line.m_poEnd.m_nPos[0])
				{
					Math::Vector<2> _vector1(m_Line.m_poStart, m_Line.m_poEnd);
					Math::Vector<2> _vector2(m_Line.m_poStart, cline_.m_Line.m_poStart);
					Geometry::ROTATE_DIRECTION _direc = Geometry::TestDirection(_vector1, _vector2);
					return (_direc == Geometry::ROTATE_DIRECTION::NO_ROTATE);
				}
				else
				{
					assert(m_Line.m_poStart.m_nPos[0] == cline_.m_Line.m_poEnd.m_nPos[0]);
					return m_Line.m_poStart.m_nPos[1] == cline_.m_Line.m_poEnd.m_nPos[1];
				}
			}

			bool SegmentIntersection::ComparableLineGeometry::operator!=(const ComparableLineGeometry& cline_)
			{
				return !operator==(cline_);
			}

			bool SegmentIntersection::ComparableLineGeometry::operator>(const ComparableLineGeometry& cline_)
			{
				return !(operator<(cline_) || operator==(cline_));
			}

			SegmentIntersection::SegmentIntersection()
			{

			}

			SegmentIntersection::~SegmentIntersection()
			{

			}

			bool SegmentIntersection::Run(
				const PlaneGeometry::LineGeometry& line1_, 
				const PlaneGeometry::LineGeometry& line2_)
			{
				Math::Vector<2> _vec1S2S(line1_.m_poStart, line2_.m_poStart);
				Math::Vector<2> _vec1S2E(line1_.m_poStart, line2_.m_poEnd);
				Math::Vector<2> _vec2S1S(line2_.m_poStart, line1_.m_poStart);
				Math::Vector<2> _vec2S1E(line2_.m_poStart, line1_.m_poEnd);
				Math::Vector<2> _vecLine1(line1_.m_poStart, line1_.m_poEnd);
				Math::Vector<2> _vecLine2(line2_.m_poStart, line2_.m_poEnd);

				// ���߶�2
				// ���� �߶�2��㵽�߶�1��㹹�ɵ����� �����ת�Ե��� �߶�2���������
				// ���� �߶�2��㵽�߶�1�յ㹹�ɵ����� �����ת�Ե��� �߶�2���������
				Geometry::ROTATE_DIRECTION _dir1 = Geometry::TestDirection(_vec2S1S, _vecLine2);
				Geometry::ROTATE_DIRECTION _dir2 = Geometry::TestDirection(_vec2S1E, _vecLine2);

				// ���߶�1
				// ���� �߶�1��㵽�߶�2��㹹�ɵ����� �����ת�Ե��� �߶�1���������
				// ���� �߶�1��㵽�߶�2�յ㹹�ɵ����� �����ת�Ե��� �߶�1���������
				Geometry::ROTATE_DIRECTION _dir3 = Geometry::TestDirection(_vec1S2S, _vecLine1);
				Geometry::ROTATE_DIRECTION _dir4 = Geometry::TestDirection(_vec1S2E, _vecLine1);

				bool _bSect = false;
				if (_dir1 == Geometry::ROTATE_DIRECTION::ANTICLOCK
					&& _dir2 == Geometry::ROTATE_DIRECTION::CLOCK)
				{
					_bSect = true;
				}
				else if (_dir1 == Geometry::ROTATE_DIRECTION::CLOCK
					&& _dir2 == Geometry::ROTATE_DIRECTION::ANTICLOCK)
				{
					_bSect = true;
				}
				else if (_dir3 == Geometry::ROTATE_DIRECTION::ANTICLOCK
					&& _dir4 == Geometry::ROTATE_DIRECTION::CLOCK)
				{
					_bSect = true;
				}
				else if (_dir3 == Geometry::ROTATE_DIRECTION::CLOCK
					&& _dir4 == Geometry::ROTATE_DIRECTION::ANTICLOCK)
				{
					_bSect = true;
				}

				if (_bSect)
				{
					return _bSect;
				}

				if (_dir1 == Geometry::NO_ROTATE 
					&& Geometry::IsPointOnLine(line2_, line1_.m_poStart))
				{
					_bSect = true;
				}
				else if (_dir2 == Geometry::ROTATE_DIRECTION::NO_ROTATE 
					&& Geometry::IsPointOnLine(line2_, line1_.m_poEnd))
				{
					_bSect = true;
				}
				else if (_dir3 == Geometry::ROTATE_DIRECTION::NO_ROTATE 
					&& Geometry::IsPointOnLine(line1_, line2_.m_poStart))
				{
					_bSect = true;
				}
				else if (_dir4 == Geometry::ROTATE_DIRECTION::NO_ROTATE 
					&& Geometry::IsPointOnLine(line1_, line2_.m_poEnd))
				{
					_bSect = true;
				}

				return _bSect;
			}

			bool SegmentIntersection::Run(
				const DataStruct::Array::DynArray<PlaneGeometry::LineGeometry>& arrLines_)
			{
				// ����n���߶Σ��õ�2n�����������ԵĶ˵�
				DataStruct::Array::DynArray<LinePoint*> _arrCritialPoint;
				typedef DataStruct::Tree::SortedBalanceBinaryTree<LinePoint*, PlaneGeometry::LineGeometry> Map;
				typedef DataStruct::Tree::SortedBalanceBinaryTree<LinePoint*, PlaneGeometry::LineGeometry>::Pair MapPair;
				typedef DataStruct::Tree::SortedBalanceBinaryTree<LinePoint*, PlaneGeometry::LineGeometry>::Node MapNode;
				Map _mapPointToLine;
				// ͨ��n���߶εõ�2n���¼���
				// �����¼��㵽�߶ε�ӳ��
				for (int _i = 0; _i < arrLines_.GetSize(); _i++)
				{
					if (arrLines_[_i].m_poStart.m_nPos[0] < arrLines_[_i].m_poEnd.m_nPos[0])
					{
						LinePoint* _pLPo = new LinePoint(arrLines_[_i].m_poStart, POINT_TYPE::LEFT);
						_arrCritialPoint.Add(_pLPo);
						MapPair _nPair1(_pLPo, arrLines_[_i]);
						_mapPointToLine.Add(_nPair1);
						_pLPo = new LinePoint(arrLines_[_i].m_poEnd, POINT_TYPE::RIGHT);
						_arrCritialPoint.Add(_pLPo);
						MapPair _nPair2(_pLPo, arrLines_[_i]);
						_mapPointToLine.Add(_nPair2);
					}
					else
					{
						LinePoint* _pLPo = new LinePoint(arrLines_[_i].m_poStart, POINT_TYPE::RIGHT);
						_arrCritialPoint.Add(_pLPo);
						MapPair _nPair1(_pLPo, arrLines_[_i]);
						_mapPointToLine.Add(_nPair1);
						_pLPo = new LinePoint(arrLines_[_i].m_poEnd, POINT_TYPE::LEFT);
						_arrCritialPoint.Add(_pLPo);
						MapPair _nPair2(_pLPo, arrLines_[_i]);
						_mapPointToLine.Add(_nPair2);
					}
				}

				// ��2n���¼���
				// �����ȼ�
				// Xλ�ô�С����
				// ����˵㵽�Ҷ˵�
				// Yλ�ô�С����
				// ����
				_arrCritialPoint.Sort(
					[](const LinePoint*& lpo1_, const LinePoint*& lpo2_)->int
				{
					double _nDeltaX = lpo1_->m_poPos.m_nPos[0] - lpo2_->m_poPos.m_nPos[0];
					if (_nDeltaX != 0.0)
					{
						if (_nDeltaX > 0.0)
						{
							return 1;
						}
						else
						{
							return -1;
						}
					}

					if (lpo1_->m_Type != lpo2_->m_Type)
					{
						if (lpo1_->m_Type == POINT_TYPE::LEFT)
						{
							return -1;
						}
						else
						{
							return 1;
						}
					}

					double _nDeltaY = lpo1_->m_poPos.m_nPos[1] - lpo2_->m_poPos.m_nPos[1];
					if (_nDeltaY > 0.0)
					{
						return 1;
					}
					else if (_nDeltaY < 0.0)
					{
						return -1;
					}
					else
					{
						return 0;
					}
				}
				);

				typedef DataStruct::Tree::SortedBalanceBinaryTree<ComparableLineGeometry, PlaneGeometry::LineGeometry> LineMap;
				typedef DataStruct::Tree::SortedBalanceBinaryTree<ComparableLineGeometry, PlaneGeometry::LineGeometry>::Pair LineMapPair;
				typedef DataStruct::Tree::SortedBalanceBinaryTree<ComparableLineGeometry, PlaneGeometry::LineGeometry>::Node LineMapNode;
				LineMap _lineMap;
				for (int _i = 0; _i < _arrCritialPoint.GetSize(); _i++)
				{
					if (_arrCritialPoint[_i]->m_Type == POINT_TYPE::LEFT)
					{
						MapNode* _pNode = _mapPointToLine.Search(_arrCritialPoint[_i]);
						LineMapPair _nPair(ComparableLineGeometry(_pNode->GetPair().m_nValue), _pNode->GetPair().m_nValue);
						if (_lineMap.Add(_nPair))
						{
							return true;
						}

						LineMapNode* _pLineNode = _lineMap.Search(ComparableLineGeometry(_pNode->GetPair().m_nValue));
						LineMapNode* _pPreLineNode = _lineMap.Pre(_pLineNode);
						LineMapNode* _pSucLineNode = _lineMap.Suc(_pLineNode);
						if (_pPreLineNode 
							&& SegmentIntersection::Run(_pPreLineNode->GetPair().m_nValue, _pLineNode->GetPair().m_nValue))
						{
							return true;
						}
						else if (_pSucLineNode 
							&& SegmentIntersection::Run(_pSucLineNode->GetPair().m_nValue, _pLineNode->GetPair().m_nValue))
						{
							return true;
						}
					}
					else
					{
						MapNode* _pNode = _mapPointToLine.Search(_arrCritialPoint[_i]);
						LineMapNode* _pLineNode = _lineMap.Search(ComparableLineGeometry(_pNode->GetPair().m_nValue));
						LineMapNode* _pPreLineNode = _lineMap.Pre(_pLineNode);
						LineMapNode* _pSucLineNode = _lineMap.Suc(_pLineNode);
						if (_pPreLineNode
							&& _pSucLineNode
							&& SegmentIntersection::Run(_pPreLineNode->GetPair().m_nValue, _pSucLineNode->GetPair().m_nValue))
						{
							return true;
						}

						_lineMap.Delete(_pLineNode->GetPair().m_nKey);
					}
				}

				for (int _i = 0; _arrCritialPoint.GetSize(); _i++)
				{
					delete _arrCritialPoint[_i];
					_arrCritialPoint[_i] = nullptr;
				}

				return false;
			}
		}
	}
}