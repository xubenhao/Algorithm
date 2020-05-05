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

			// ��ȷ��֤����
			// �㷨Ŀ�꣺�����㼯����ȡ�˵㼯��͹����
			// ͹����
			// �е㼯��һ���Ӽ�Χ�ɵķ������A
			// �㼯�����е����Χ�ɵķ������֮�ϻ�֮��
			// �������A���κ��������ڵı����㣺
			// �����Է������ y��С�����y��Сʱȡx��С�ߡ���p��ʼ����ʱ��˳���n���߽���0,...,n-1��ţ�
			// ��������
			// ��i����[0,n-1], j=(i+1) % (n)
			// ��
			// i��Ӧ������ ��������ʱ��ת�����߲�ת���� ��ʽ ���� j��Ӧ������
			DataStruct::Stack::DynStack<Math::Point<2>> ConvexHull::Run(
				const DataStruct::Array::DynArray<Math::Point<2>>& arrPos_)
			{
				// Ѱ����ʼ��s
				// ��ʼ��Ϊn������y������С�ĵ㣬�����������Сy����ĵ�ʱ��ȡ����x������С��һ��
				// ��ʣ���n-1���㣬�ֱ�������s������ʱ��ת�����õĽǶȣ����Ƕȴ�С�����ʣ��n-1�����������
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

				// ��n���㣬��ÿ�������_poS��ʱ��ת���Ƕ���С�����n��������
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

				// ��s��ջ����������׸���p��ջ
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

				// Ŀǰջ���Ѿ�����������
				// ���ں�����ÿ����

				// ѭ������ʽ��
				// ջ�еĵ㣬������һ�� �ӷ������ y��С�����y��Сʱȡx��С�ߡ���p��ʼ����ʱ��˳��õ��ĵ�ļ��ϡ�
				// �������Ӵ˼������ڵĵ㣬����һ����β���ڵķ������
				// �˷�������Ǵ�p���ϴε�����qΪֹ�ĵ㼯��һ��͹����

				// ֤����
				// ��ʼʱ��
				// ��p��q�������㹹�ɵĵ㼯��͹�������ڡ�ѭ������ʽ���㡣
				// ��k�ε���ʱ
				// ��������t��Ӧ��p����ת�Ƕȣ������ϴε����㣬�����㣬ջ�еĵ�+t��������һ�� ��p��ʼ����ʱ��˳��ĵ�ļ��ϡ�
				// ��������t��Ӧ��p����ת�Ƕ� �������ϴε����㣬�������������
				// Ҫôt���ϴε������غϣ���ʱ������t
				// Ҫôt����p���ϴε��������ߵ��ӳ����ϣ���ʱ��ջɾ���ϴε����㣬����t���ɵļ������� ������һ�� ��p��ʼ����ʱ��˳��ĵ�ļ��ϡ�

				// 1.��������t��Ӧ��p����ת�Ƕȣ������ϴε�����ʱ��
				// ��q1����ջ���㣬q2�����ջ����
				// 1.1.��q2->q1����ʱ��ת������q1->t
				// �򣬱�����ͼʾ1
				// ��ʱq2->q1,q1->t����͹��Ҫ��
				// q1->t,t->pҲ����͹��Ҫ��
				// ����ѭ������ʽ��p...q1���Ѿ�����㼯��͹��
				// ����֪�� p...q1,t�Ǳ��ε������Ѿ�����㼯��͹����ѭ������ʽ���㡣
				// 1.2.��q2->q1��˳ʱ��ת������q1->t
				// ��ʱ����ɾ��q1
				// ��Ϊ����֪�� p->...->q2->t->p��Χ���������q1
				// ͬ�����ѭ��������ֱ��ջ��q2->q1,q1->t����ʱ��ת���������t��p->q1�ӳ�����ʱ�������˳���
				// ����֪����������ϵõ���
				// p->...->t����ѭ������ʽ��Ҫ��
				// 2.��������t��Ӧ��p����ת�Ƕȣ������ϴε�����ʱ��
				// 2.1.Ҫôt���ϴε������غϣ���ʱ������t��
				// ����֪�� p...q1�Ǳ��ε������Ѿ�����㼯��͹����ѭ������ʽ���㡣
				// 2.1. Ҫôt����p���ϴε��������ߵ��ӳ����ϣ���ʱ��ջɾ���ϴε����㣬���뱾�ε�����
				// ����֪�� p...p2,t�Ǳ��ε������Ѿ�����㼯��͹����ѭ������ʽ���㡣
				// �ۺϣ�
				// k�ε�����ѭ������ʽ��Ȼ����

				// ��֤
				// ��������ÿ���㣬��˳�����ε���
				for (int _i = _nIndex; _i < _nSize; _i++)
				{
					// �Ե����ĵ�q
					// ��q��ջ���㣬ջ�ζ��� ���ж�
					while (true)
					{
						// �� ջ�ζ��㵽ջ���������������ʱ��ת������ ջ���㵽q���������򣬽�q������У����Ž�����һ�ε���
						// �� ջ�ζ��㵽ջ�������������˳ʱ����߲�ת������ ջ���㵽q����������ջ�����ջ��
						// ��ջ���ٴ�ִ��q��ջ���㣬ջ�ζ��� �ж�
						// ֱ���ж�Ϊ �ɽ�q����ջʱ�����벢�����´ε���������һֱ ��ջ�����ջ��
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

				// ����������ϣ�
				// ��ջ�ڶ���������ڵ���3���򷵻�ջ��Ϊ������
				// ��ջ�ڶ������С��3�����ؿ�ջ�Ա�ʾ�㼯��͹��������
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