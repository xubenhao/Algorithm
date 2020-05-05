#define ALGORITHMLIB __declspec(dllexport)
#include "Geometry.h"
namespace AlLib
{
	namespace Algorithm
	{
		namespace Geo
		{
			Geometry::Geometry()
			{

			}

			Geometry::~Geometry()
			{

			}

			Geometry::ROTATE_DIRECTION Geometry::TestDirection(
				const Math::Vector<2>& vector1_, 
				const Math::Vector<2>& vector2_)
			{
				double _nRet = vector1_.m_nValues[0] * vector2_.m_nValues[1] - vector2_.m_nValues[0] * vector1_.m_nValues[1];
				if (_nRet > 0.0)
				{
					return ROTATE_DIRECTION::ANTICLOCK;
				}
				else if (_nRet < 0.0)
				{
					return ROTATE_DIRECTION::CLOCK;
				}
				else
				{
					return ROTATE_DIRECTION::NO_ROTATE;
				}
			}

			bool Geometry::IsPointOnLine(
				const PlaneGeometry::LineGeometry& line_, 
				const Math::Point<2> po_)
			{
				double _nMinX = Math::Helper::Min(line_.m_poStart.m_nPos[0], line_.m_poEnd.m_nPos[0]);
				double _nMaxX = Math::Helper::Max(line_.m_poStart.m_nPos[0], line_.m_poEnd.m_nPos[0]);
				double _nMinY = Math::Helper::Min(line_.m_poStart.m_nPos[1], line_.m_poEnd.m_nPos[1]);
				double _nMaxY = Math::Helper::Max(line_.m_poStart.m_nPos[1], line_.m_poEnd.m_nPos[1]);
				bool _bOn = true;
				if (!(po_.m_nPos[0] >= _nMinX
					&& po_.m_nPos[0] <= _nMaxX))
				{
					_bOn = false;
				}
				else if (!(po_.m_nPos[1] >= _nMinY
					&& po_.m_nPos[1] <= _nMaxY))
				{
					_bOn = false;
				}

				return _bOn;
			}

			double Geometry::GetAngle(const Math::Vector<2>& vec_)
			{
				Math::Vector<2> _vecV = vec_;
				if (_vecV.GetLength() == 0.0)
				{
					throw "0 vector has no angle";
				}

				_vecV.Normalize();
				double _nAngle = std::asin(_vecV.m_nValues[1]);
				if (_vecV.m_nValues[0] >= 0.0 && _vecV.m_nValues[1] >= 0.0)
				{
					return _nAngle;
				}
				else if (_vecV.m_nValues[0] <= 0.0 && _vecV.m_nValues[1] >= 0.0)
				{
					assert(_nAngle >= 0.0 && _nAngle <= PI / 2.0);
					return (PI - _nAngle);
				}
				else if (_vecV.m_nValues[0] <= 0.0 && _vecV.m_nValues[1] <= 0.0)
				{
					assert(_nAngle >= -(PI / 2.0) && _nAngle <= 0.0);
					return (PI - _nAngle);
				}
				else
				{
					assert(_nAngle >= -(PI / 2.0) && _nAngle <= 0.0);
					return (2 * PI + _nAngle);
				}
			}

			double Geometry::GetDistance(
				const Math::Point<2>& po1_, 
				const Math::Point<2>& po2_)
			{
				Math::Vector<2> _vecV(po1_, po2_);
				return _vecV.GetLength();
			}
		}
	}
}