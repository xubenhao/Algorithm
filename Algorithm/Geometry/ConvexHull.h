//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_ALGORITHM_GEOMETRY_CONVEXHULL_H
#define AILIB_ALGORITHM_GEOMETRY_CONVEXHULL_H
#include "..\..\stdafx.h"
#include "..\..\DataStruct\Array\DynArray.h"
#include "..\..\DataStruct\Stack\DynStack.h"
#include "Geometry.h"

namespace AlLib
{
	namespace Algorithm
	{
		namespace Geo
		{
			extern "C" class ALGORITHMLIB ConvexHull
			{
			public:
				ConvexHull();
				~ConvexHull();

				DataStruct::Stack::DynStack<Math::Point<2>> Run(const DataStruct::Array::DynArray<Math::Point<2>>& poArr_);
			};
		}
	}
}
#endif