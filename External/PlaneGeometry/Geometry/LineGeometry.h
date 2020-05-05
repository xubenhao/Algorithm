#ifndef PLANEGEOMETRY_GEOMETRY_LINEGEOMETRY_H
#define PLANEGEOMETRY_GEOMETRY_LINEGEOMETRY_H
#include "..\Stdafx.h"
#include "Geometry.h"
namespace PlaneGeometry
{
	extern "C" class PLANEGEOMETRYLIB LineGeometry : Geometry
	{
	public:
		LineGeometry();
		~LineGeometry();
		Math::Vector<2> GetVector() const;
	public:
		Math::Point<2> m_poStart;
		Math::Point<2> m_poEnd;
	};
}
#endif
