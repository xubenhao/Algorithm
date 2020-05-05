#define ALGORITHMLIB __declspec(dllexport)
#include "ConvexHull.h"
namespace AlLib
{
	namespace Algorithm
	{
		namespace Geo
		{
			ConvexHull::ConvexHull()
			{

			}

			ConvexHull::~ConvexHull()
			{

			}

			// 正确性证明：
			// 算法目标：给定点集，求取此点集的凸包。
			// 凸包是
			// 有点集的一个子集围成的封闭区域A
			// 点集内所有点均在围成的封闭区域之上或之内
			// 封闭区域A的任何两条相邻的边满足：
			// 假设以封闭区域 y最小【多个y最小时取x最小者】点p开始以逆时针顺序对n条边进行0,...,n-1编号，
			// 则总是有
			// 对i属于[0,n-1], j=(i+1) % (n)
			// 有
			// i对应的向量 总是以逆时针转动或者不转动的 方式 到达 j对应的向量
			DataStruct::Stack::DynStack<Math::Point<2>> ConvexHull::Run(
				const DataStruct::Array::DynArray<Math::Point<2>>& arrPos_)
			{
				// 寻找起始点s
				// 起始点为n个点中y坐标最小的点，含多个具有最小y坐标的点时，取其中x坐标最小的一个
				// 对剩余的n-1个点，分别计算相对s进行逆时针转动所得的角度，按角度从小到大对剩余n-1个点进行排序
				DataStruct::Stack::DynStack<Math::Point<2>> _sRet;
				int _nSize = arrPos_.GetSize();
				if (_nSize <= 3)
				{
					return _sRet;
				}

				Math::Point<2> _poS = arrPos_[0];
				for (int _i = 1; _i < _nSize; _i++)
				{
					if (arrPos_[_i].m_nPos[1] < _poS.m_nPos[1]
						|| (arrPos_[_i].m_nPos[1] == _poS.m_nPos[1] && arrPos_[_i].m_nPos[0] < _poS.m_nPos[0]))
					{
						_poS = arrPos_[_i];
					}
				}

				// 对n个点，按每个点相对_poS逆时针转动角度由小到大对n个点排序
				DataStruct::Array::DynArray<Math::Point<2>> _arrPos = arrPos_;
				_arrPos.Sort([_poS](const Math::Point<2>& po1_, const Math::Point<2>& po2_)->int
				{
					Math::Vector<2> _vec1(_poS, po1_);
					Math::Vector<2> _vec2(_poS, po2_);
					double _nAngle1 = Geometry::GetAngle(_vec1);
					double _nAngle2 = Geometry::GetAngle(_vec2);
					double _nRet = _nAngle1 - _nAngle2;
					if (_nRet > 0)
					{
						return 1;
					}
					else if (_nRet < 0)
					{
						return -1;
					}
					else
					{
						double _nLen1 = _vec1.GetLength();
						double _nLen2 = _vec2.GetLength();
						_nRet = _nLen1 - _nLen2;
						if (_nRet > 0)
						{
							return 1;
						}
						else if (_nRet < 0)
						{
							return -1;
						}
						else
						{
							return 0;
						}
					}
				});

				// 将s入栈，将排序后首个点p入栈
				_sRet.Push(_poS);
				int _nIndex = 0;
				while (_nIndex < _nSize)
				{
					if (_poS == _arrPos[_nIndex])
					{
						_nIndex++;
					}
					else
					{
						_sRet.Push(_arrPos[_nIndex]);
						_nIndex++;
						break;
					}
				}

				// 目前栈中已经存在两个点
				// 对于后续的每个点

				// 循环不变式：
				// 栈中的点，代表了一个 从封闭区域 y最小【多个y最小时取x最小者】点p开始以逆时针顺序得到的点的集合。
				// 依次连接此集合相邻的点，构成一个首尾相邻的封闭区域。
				// 此封闭区域是从p到上次迭代点q为止的点集的一个凸包。

				// 证明：
				// 初始时，
				// 从p到q是两个点构成的点集，凸包不存在。循环不变式满足。
				// 第k次迭代时
				// 若迭代点t对应于p的旋转角度，大于上次迭代点，则，满足，栈中的点+t，代表了一个 点p开始以逆时针顺序的点的集合。
				// 若迭代点t对应于p的旋转角度 ，等于上次迭代点，则依据排序规则
				// 要么t和上次迭代点重合，此时不处理t
				// 要么t处于p和上次迭代点连线的延长线上，此时从栈删除上次迭代点，加入t构成的集合满足 代表了一个 点p开始以逆时针顺序的点的集合。

				// 1.若迭代点t对应于p的旋转角度，大于上次迭代点时，
				// 以q1代表栈顶点，q2代表次栈顶点
				// 1.1.若q2->q1沿逆时针转动到达q1->t
				// 则，必属于图示1
				// 此时q2->q1,q1->t满足凸包要求
				// q1->t,t->p也满足凸包要求
				// 依据循环不变式，p...q1是已经处理点集的凸包
				// 可以知道 p...q1,t是本次迭代后已经处理点集的凸包。循环不变式满足。
				// 1.2.若q2->q1沿顺时针转动到达q1->t
				// 此时可以删除q1
				// 因为易于知道 p->...->q2->t->p所围成区域包含q1
				// 同理，如此循环迭代，直到栈中q2->q1,q1->t沿逆时针转动到达，或者t在p->q1延长线上时，处理并退出。
				// 易于知道，处理完毕得到的
				// p->...->t满足循环不变式的要求
				// 2.若迭代点t对应于p的旋转角度，等于上次迭代点时，
				// 2.1.要么t和上次迭代点重合，此时不处理t，
				// 可以知道 p...q1是本次迭代后已经处理点集的凸包。循环不变式满足。
				// 2.1. 要么t处于p和上次迭代点连线的延长线上，此时从栈删除上次迭代点，加入本次迭代点
				// 可以知道 p...p2,t是本次迭代后已经处理点集的凸包。循环不变式满足。
				// 综合，
				// k次迭代后循环不变式仍然成立

				// 得证
				// 对排序后的每个点，按顺序依次迭代
				for (int _i = _nIndex; _i < _nSize; _i++)
				{
					// 对迭代的点q
					// 对q，栈顶点，栈次顶点 做判断
					while (true)
					{
						// 若 栈次顶点到栈顶点的向量，沿逆时针转动到达 栈顶点到q的向量，则，将q放入队列，接着进行下一次迭代
						// 若 栈次顶点到栈顶点的向量，沿顺时针或者不转动到达 栈顶点到q的向量，则将栈顶点出栈。
						// 出栈后，再次执行q，栈顶点，栈次顶点 判断
						// 直到判断为 可将q放入栈时，放入并进入下次迭代，否则，一直 将栈顶点出栈。
						if (_sRet.Peek() == _arrPos[_i])
						{
							break;
						}

						Math::Vector<2> _vec1(_sRet.Peek(1), _sRet.Peek());
						Math::Vector<2> _vec2(_sRet.Peek(), _arrPos[_i]);
						Geometry::ROTATE_DIRECTION _dir = Geometry::TestDirection(_vec1, _vec2);
						if (_dir == Geometry::ROTATE_DIRECTION::ANTICLOCK)
						{
							_sRet.Push(_arrPos[_i]);
							break;
						}
						else if (_dir == Geometry::ROTATE_DIRECTION::NO_ROTATE)
						{
							_sRet.Pop();
							_sRet.Push(_arrPos[_i]);
							break;
						}
						else
						{
							_sRet.Pop();
						}
					}
				}

				// 迭代处理完毕，
				// 若栈内顶点个数大于等于3，则返回栈作为处理结果
				// 若栈内顶点个数小于3，返回空栈以表示点集的凸包不存在
				if (_sRet.GetSize() < 3)
				{
					return DataStruct::Stack::DynStack<Math::Point<2>>();
				}
				else
				{
					return _sRet;
				}
			}
		}
	}
}