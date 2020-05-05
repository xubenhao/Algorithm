#ifndef MATH_DATA_VECTOR_H
#define MATH_DATA_VECTOR_H
#include "..\Stdafx.h"
namespace Math
{
	// 2维向量
	// 3维向量
	template<unsigned N>
	class Vector
	{
	public:
		Vector();
		Vector(const Point<N>& po1_, const Point<N>& po2_);
		
		~Vector();

		double GetLength() const;
		void Normalize();
	public:
		double m_nValues[N];
	};

	template<unsigned N>
	Vector<N>::Vector()
	{
		for (int _i = 0; _i < N; _i++)
		{
			m_nValues[_i] = 0.0;
		}
	}

	template<unsigned N>
	Vector<N>::Vector(const Point<N>& po1_, const Point<N>& po2_)
	{
		for (int _i = 0; _i < N; _i++)
		{
			m_nValues[_i] = po2_.m_nPos[_i] - po1_.m_nPos[_i];
		}
	}

	template<unsigned N>
	double Vector<N>::GetLength() const
	{
		double _nLen = 0.0;
		for (int _i = 0; _i < N; _i++)
		{
			_nLen += m_nValues[_i] * m_nValues[_i];
		}

		return std::sqrt(_nLen);
	}

	template<unsigned N>
	void Vector<N>::Normalize()
	{
		double _nLen = GetLength();
		if (_nLen == 0.0)
		{
			return;
		}

		for (int _i = 0; _i < N; _i++)
		{
			m_nValues[_i] /= _nLen;
		}
	}

	template<unsigned N>
	Vector<N>::~Vector()
	{

	}
}
#endif
