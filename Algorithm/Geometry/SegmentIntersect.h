//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_ALGORITHM_GEOMETRY_SEGMENTINTERSECT_H
#define AILIB_ALGORITHM_GEOMETRY_SEGMENTINTERSECT_H
#include "..\..\stdafx.h"
#include "..\..\DataStruct\Array\DynArray.h"
#include "Geometry.h"

namespace AlLib
{
	namespace Algorithm
	{
		namespace Geo
		{
			extern "C" class ALGORITHMLIB SegmentIntersection
			{
			public:
				enum POINT_TYPE
				{
					LEFT,
					RIGHT,
				};

				class LinePoint
				{
				public:
					LinePoint();
					LinePoint(Math::Point<2> poP_, POINT_TYPE Type_);
					~LinePoint();

				public:
					Math::Point<2> m_poPos;
					POINT_TYPE m_Type;
				};

				class ComparableLineGeometry
				{
				public:
					ComparableLineGeometry();
					ComparableLineGeometry(const PlaneGeometry::LineGeometry& line_);
					~ComparableLineGeometry();

					bool operator<(const ComparableLineGeometry& cline_);
					bool operator==(const ComparableLineGeometry& cline_);
					bool operator!=(const ComparableLineGeometry& cline_);
					bool operator>(const ComparableLineGeometry& cline_);
				private:
					PlaneGeometry::LineGeometry m_Line;
				};

				SegmentIntersection();
				~SegmentIntersection();

				static bool Run(const PlaneGeometry::LineGeometry& line1_, const PlaneGeometry::LineGeometry& line2_);
				static bool Run(const DataStruct::Array::DynArray<PlaneGeometry::LineGeometry>& arrLines_);
			};
		}
	}
}
#endif
