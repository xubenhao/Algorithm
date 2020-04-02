//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef ALGORITHM_SORT_QUICKSORT_H
#define ALGORITHM_SORT_QUICKSORT_H
#include "..\..\stdafx.h"
namespace Algorithm
{
	namespace Sort
	{
		class Helper
		{
		public:
			// 快速排序的思想
			// 给定待排序集合
			// 从集合中任意选取一个主元
			// 将待排序集合以主元为标尺进行划分
			// 上述操作后，只要保证两个更小集合为有序即可保证大集合为有序
			// 则，符合分治思想，将大问题分解为同等类型的小问题
			// 综合，也即主元，加两边有序的子集合构成了最后的有序集合
			template <typename T>
			static void QuickSort(
				T* pS_,// 指向排序首对象指针
				T* pE_);// 指向排序尾后对象指针

		private:
			template <typename T>
			static int Partition(
				T* pS_,
				T* pE_);
		};
		
		template <typename T>
		void Helper::QuickSort(
			T* pS_,
			T* pE_)
		{
			int _nNum = pE_ - pS_;
			if (_nNum <= 1)
			{
				return;
			}

			T* _pMain = Partition(pS_, pE_);
			QuickSort(pS_, _pMain);
			QuickSort(_pMain + 1, pE_);
		}

		// 返回值：
		// 指针主元对象指针【主元对象左边元素小于主元，主元对象右边元素大于主元】
		template <typename T>
		T* Helper::Partition(
			T* pS_,// 执行排序首对象指针
			T* pE_)// 指向排序尾后对象指针
		{
			// 算法描述：
			// 选定首元素为主元
			// 提取主元值，存储于临时变量
			// 维护一个 可插入元素起始地址F，可插入元素尾部地址L
			// 维持以下循环不变式：
			// E后元素均大于主元
			// Empty是空白位置
			// Empty前元素均小于或等于主元
			// Empty + 1 = F
			// 区间[S,E)内除Empty外始终存储初始进入时除主元外的 元素集合
			// [Empty + 1, L]区间内元素和主元关系未知
			T _nMain = *pS_;
			T* _pL = pE_ - 1;
			T* _pEmpty = pS_;
			while (true)
			{
				// 终止检测
				if (_pEmpty == _pL)
				{
					break;
				}

				// 将_pF位置元素与主元比较
				if (*(_pEmpty + 1) <= _nMain)
				{
					*_pEmpty = *(_pEmpty + 1);
					_pEmpty++;
				}
				else
				{
					T _nTemp = *_pL;
					*_pL = *(_pEmpty + 1);
					*(_pEmpty + 1) = _nTemp;
				}
			}

			*_pEmpty = _nMain;
			return _pEmpty;
		}
	}
}
#endif
