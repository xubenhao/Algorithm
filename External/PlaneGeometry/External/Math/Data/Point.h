#ifndef MATH_DATA_POINT_H
#define MATH_DATA_POINT_H
#include "..\Stdafx.h"
namespace Math
{
	template<unsigned N>
	class Point
	{
	public:
		Point();
		~Point();

	public:
		double m_nPos[N];
	};
}
#endif
