//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_ALGORITHM_GEOMETRY_GEOMETRY_H
#define AILIB_ALGORITHM_GEOMETRY_GEOMETRY_H
#include "..\..\stdafx.h"
#include "..\..\DataStruct\Array\DynArray.h"

namespace AlLib
{
	namespace Algorithm
	{
		namespace Geo
		{
			extern "C" class ALGORITHMLIB Geometry
			{
			public:
				enum ROTATE_DIRECTION
				{
					NO_ROTATE,
					CLOCK,
					ANTICLOCK,
				};

				Geometry();
				~Geometry();
				static ROTATE_DIRECTION TestDirection(const Math::Vector<2>& vector1_, const Math::Vector<2>& vector2_);
				static bool IsPointOnLine(const PlaneGeometry::LineGeometry& line_, const Math::Point<2> po_);
				static double GetAngle(const Math::Vector<2>& vec_);
				static double GetDistance(const Math::Point<2>& po1_, const Math::Point<2>& po2_);
			};
		}
	}
}
#endif