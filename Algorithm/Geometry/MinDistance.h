//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_ALGORITHM_GEOMETRY_MINDISTANCE_H
#define AILIB_ALGORITHM_GEOMETRY_MINDISTANCE_H
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
			extern "C" class ALGORITHMLIB MinDistance
			{
			public:
				enum Flag
				{
					LEFT,
					RIGHT,
				};

				class FlagPoint
				{
				public:
					FlagPoint();
					FlagPoint(Math::Point<2>* pPo_, Flag nFlag_);
					~FlagPoint();

				public:
					Math::Point<2> m_poP;
					Flag m_nFlag;
				};

				MinDistance();
				~MinDistance();

				double Run(const DataStruct::Array::DynArray<Math::Point<2>>& poArr_);
			private:
				double CalculateMinDistance(
					const DataStruct::Array::DynArray<FlagPoint*>& arrPos_,
					const DataStruct::Array::DynArray<FlagPoint*>& arrSortedByX_,
					const DataStruct::Array::DynArray<FlagPoint*>& arrSortedByY_);
			};
		}
	}
}
#endif