#define ALGORITHMLIB __declspec(dllexport)
#include "MinDistance.h"
namespace AlLib
{
	namespace Algorithm
	{
		namespace Geo
		{
			MinDistance::FlagPoint::FlagPoint()
			{
				m_nFlag = Flag::LEFT;
			}

			MinDistance::FlagPoint::FlagPoint(Math::Point<2>* pPo_, Flag nFlag_)
			{
				m_nFlag = nFlag_;
			}

			MinDistance::FlagPoint::~FlagPoint()
			{

			}

			MinDistance::MinDistance()
			{

			}

			MinDistance::~MinDistance()
			{

			}

			double MinDistance::Run(const DataStruct::Array::DynArray<Math::Point<2>>& arrPos_)
			{
				// �㷨˼�룺
				// �㷨����ȡ����㼯A��С����
				// ���㼯A�У���ĸ���С�ڻ����3��ֱ�Ӹ��������
				// �Ե㼯Aһ��Ϊ����AL��AR
				// ��AL��AR�ֱ����㷨��ȡAL��AR��С����d_al,d_ar
				// ��d = min(d_al, d_ar)
				// ������С��������һ��λ��AL��һ��λ��AR������
				// �������������߾������߾���Ϊd����d�ĵ㹹�ɵĵ㼯P
				// �Ե㼯P�е㰴Y��������
				// �Ե㼯P��ÿ���㣬���������7����Ƚϡ�
				// ��ˣ��õ�һ��P�е����С����d_p
				// ����min(d, d_p)
				DataStruct::Array::DynArray<FlagPoint*> _parrFPo;
				int _nSize = arrPos_.GetSize();
				for (int _i = 0; _i < _nSize; _i++)
				{
					FlagPoint* _pFPo = new FlagPoint();
					_pFPo->m_poP = arrPos_[_i];
					_parrFPo.Add(_pFPo);
				}

				DataStruct::Array::DynArray<FlagPoint*> _parrFPosSortedByX = _parrFPo;
				_parrFPosSortedByX.Sort(
					[](const FlagPoint*& po1_, const FlagPoint*& po2_)
				{
					double _nRet = po1_->m_poP.m_nPos[0] - po2_->m_poP.m_nPos[0];
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

				DataStruct::Array::DynArray<FlagPoint*> _parrFPosSortedByY = _parrFPo;
				_parrFPosSortedByY.Sort(
					[](const FlagPoint*& po1_, const FlagPoint*& po2_)
				{
					double _nRet = po1_->m_poP.m_nPos[1] - po2_->m_poP.m_nPos[1];
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

				double _nMin = CalculateMinDistance(
					_parrFPo, 
					_parrFPosSortedByX, 
					_parrFPosSortedByY);
				for (int _i = 0; _i < _nSize; _i++)
				{
					delete _parrFPo[_i];
					_parrFPo[_i] = nullptr;
				}
			}

			double MinDistance::CalculateMinDistance(
				const DataStruct::Array::DynArray<FlagPoint*>& parrFPos_,
				const DataStruct::Array::DynArray<FlagPoint*>& parrFPosSortedByX_,
				const DataStruct::Array::DynArray<FlagPoint*>& parrFPosSortedByY_)
			{
				double _nMinDistance = 0.0;
				int _nSize = parrFPos_.GetSize();
				if (_nSize <= 3)
				{
					_nMinDistance = Geometry::GetDistance(parrFPos_[0]->m_poP, parrFPos_[1]->m_poP);
					for (int _i = 0; _i < _nSize; _i++)
					{
						for (int _j = 0; _j < _nSize; _j++)
						{
							if (_j == _i)
							{
								continue;
							}

							double _nD = Geometry::GetDistance(parrFPos_[_i]->m_poP, parrFPos_[_j]->m_poP);
							if (_nMinDistance < _nD)
							{
								_nMinDistance = _nD;
							}
						}
					}

					return _nMinDistance;
				}

				// ��n���ڵ������ͻ���
				for (int _i = 0; _i < _nSize; _i++)
				{
					if (_i < _nSize / 2)
					{
						parrFPosSortedByX_[_i]->m_nFlag = Flag::LEFT;
					}
					else
					{
						parrFPosSortedByX_[_i]->m_nFlag = Flag::RIGHT;
					}
				}

				// ����Ϊ��������
				DataStruct::Array::DynArray<FlagPoint*> _parrPosLeft;
				DataStruct::Array::DynArray<FlagPoint*> _parrLeftSortedByX;
				DataStruct::Array::DynArray<FlagPoint*> _parrLeftSortedByY;

				DataStruct::Array::DynArray<FlagPoint*> _parrPosRight;
				DataStruct::Array::DynArray<FlagPoint*> _parrRightSortedByX;
				DataStruct::Array::DynArray<FlagPoint*> _parrRightSortedByY;
				for (int _i = 0; _i < _nSize; _i++)
				{
					if (parrFPos_[_i]->m_nFlag == Flag::LEFT)
					{
						_parrPosLeft.Add(parrFPos_[_i]);
					}
					else
					{
						_parrPosRight.Add(parrFPos_[_i]);
					}

					if (parrFPosSortedByX_[_i]->m_nFlag == Flag::LEFT)
					{
						_parrLeftSortedByX.Add(parrFPosSortedByX_[_i]);
					}
					else
					{
						_parrRightSortedByX.Add(parrFPosSortedByX_[_i]);
					}

					if (parrFPosSortedByY_[_i]->m_nFlag == Flag::LEFT)
					{
						_parrLeftSortedByY.Add(parrFPosSortedByY_[_i]);
					}
					else
					{
						_parrRightSortedByY.Add(parrFPosSortedByY_[_i]);
					}
				}

				double _nMinDLeft = CalculateMinDistance(_parrPosLeft, _parrLeftSortedByX, _parrLeftSortedByY);
				double _nMinDRight = CalculateMinDistance(_parrPosRight, _parrRightSortedByX, _parrRightSortedByY);

				double _nMin = std::fmin(_nMinDLeft, _nMinDRight);
				DataStruct::Array::DynArray<FlagPoint*> _parrMidAreaSortedByY;
				double _nMiddleX = parrFPosSortedByX_[_nSize / 2]->m_poP.m_nPos[0];
				for (int _i = 0; _i < _nSize; _i++)
				{
					if (parrFPosSortedByY_[_i]->m_poP.m_nPos[0] >= (_nMiddleX - _nMin)
						&& parrFPosSortedByY_[_i]->m_poP.m_nPos[0] <= (_nMiddleX + _nMin))
					{
						_parrMidAreaSortedByY.Add(parrFPosSortedByY_[_i]);
					}
				}

				int _nMiddleAreaSize = _parrMidAreaSortedByY.GetSize();
				for (int _i = 0; _i < _nMiddleAreaSize; _i++)
				{
					int _nCount = 1;
					while (_nCount <= 7 && (_i + _nCount) < _nMiddleAreaSize)
					{
						double _nD = Geometry::GetDistance(_parrMidAreaSortedByY[_i]->m_poP, _parrMidAreaSortedByY[_i + _nCount]->m_poP);
						_nMin = std::fmin(_nMin, _nD);
						_nCount++;
					}
				}

				return _nMin;
			}
		}
	}
}