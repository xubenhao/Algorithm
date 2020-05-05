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

		bool operator==(const Point& po_);
		bool operator!=(const Point& po_);
		Point operator+(const Point& po_);
		Point operator-(const Point& po_);
		Point operator*(double nRatio_);
		Point operator/(double nDivide_);

	public:
		double m_nPos[N];
	};

	template<unsigned N>
	Point<N>::Point()
	{
		for (int _i = 0; _i < N; _i++)
		{
			m_nPos[_i] = 0.0;
 		}
	}

	template<unsigned N>
	Point<N>::~Point()
	{

	}

	template<unsigned N>
	bool Point<N>::operator==(const Point& po_)
	{
		bool _bIdentity = true;
		for (int _i = 0; _i < N; _i++)
		{
			if (m_nPos[_i] != po_.m_nPos[_i])
			{
				_bIdentity = false;
				break;
			}
		}

		return _bIdentity;
	}

	template<unsigned N>
	bool Point<N>::operator!=(const Point& po_)
	{
		return !operator==(po_);
	}

	template<unsigned N>
	Point Point<N>::operator+(const Point& po_)
	{
		Point _poP;
		for (int _i = 0; _i < N; _i++)
		{
			_poP.m_nPos[_i] = m_nPos[_i] + po_.m_nPos[_i];
		}

		return _poP;
	}

	template<unsigned N>
	Point Point<N>::operator-(const Point& po_)
	{
		Point _poP;
		for (int _i = 0; _i < N; _i++)
		{
			_poP.m_nPos[_i] = m_nPos[_i] - po_.m_nPos[_i];
		}

		return _poP;
	}

	template<unsigned N>
	Point Point<N>::operator*(double nRatio_)
	{
		Point _poP;
		for (int _i = 0; _i < N; _i++)
		{
			_poP.m_nPos[_i] = m_nPos[_i] * nRatio_;
		}

		return _poP;
	}

	template<unsigned N>
	Point Point<N>::operator/(double nDivide_)
	{
		if (nDivide_ == 0.0)
		{
			throw "cannot be divided by zero";
		}

		Point _poP;
		for (int _i = 0; _i < N; _i++)
		{
			_poP.m_nPos[_i] = m_nPos[_i] / nDivide_;
		}

		return _poP;
	}
}
#endif
