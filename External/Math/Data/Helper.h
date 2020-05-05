#ifndef MATH_DATA_HELPER_H
#define MATH_DATA_HELPER_H
#include "..\Stdafx.h"
namespace Math
{
	class Helper
	{
	public:
		template<typename T>
		static T Max(const T& t1_, const T& t2_);
		template<typename T>
		static T Min(const T& t1_, const T& t2_);
	};

	template<typename T>
	typename T Helper::Max(const T& t1_, const T& t2_)
	{
		if (t1_ < t2_)
		{
			return t2_;
		}
		else
		{
			return t1_;
		}
	}

	template<typename T>
	typename T Helper::Min(const T& t1_, const T& t2_)
	{
		if (t1_ < t2_)
		{
			return t1_;
		}
		else
		{
			return t2_;
		}
	}

}
#endif