//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_DESIGN_GREEDY_CHARENCODE_H
#define AILIB_DESIGN_GREEDY_CHARENCODE_H
#include "..\..\stdafx.h"

// ���⣺
// �����ַ���&�����ַ���ÿ���ַ�����Ƶ��

// Ŀ�꣺
// ���һ���ʺϴ��ַ�����ǰ׺��
// Ҫ������Ƶ�ǰ׺�������п���ǰ׺���о߱���ǰ׺��洢�����ַ�ռ�ÿռ���С���ص㡣

// ��θ��ַ�����ƿ���ǰ׺��
// ������ÿ��Ҷ�ӽڵ�p
// ���������ڵ�r��p�γ�һ��·��r->x1->...->xk->p
// ��·����ÿ������ߴ���0������ߴ���1
// ��r->x1->...->xk->p�������ɸ�0/1��ɵ�һ������
// ��������������Ҷ�ڵ�p1,p2
// ����������ȷ��p1,p2�ı���
// ����Ա�֤p1,p2�������ǰ�����ص����֡�
// �����������ȫ�ص�������һ��������һ�������⡣

// ������ַ�����n���ַ�
// ����ѡ��һ��n��Ҷ�ӽڵ�Ķ�������
// �����������ÿ��Ҷ�ӽڵ���룬���ɵõ�һ��ǰ׺�롣

// ������
// ��������һ�׿��е�ǰ׺��
// �����Դ�ǰ׺����Թ����һ�ö���������������Ҷ�ӽڵ����һ���ַ���
// ��������һ��Ҷ�ӽڵ����Ϊn�Ķ����������ǰ����Ϊ0���ұ�Ϊ1��ʽ��
// ÿ��Ҷ�ӽڵ�õ�һ�����롣
// �Ҵ˱����£����б�������ص����֣����໥�䲻�Ḳ�ǻ���ȫ�ص���
// �ʣ������õ�����һ��ǰ׺�롣

// �ۺϣ�ǰ׺��Ͷ���������һһ��Ӧ�Ĺ�ϵ��
// ����������ǰ׺��
// Ҳ�����Ӧ�����Ŷ�����

// ��ÿ��Ҷ�ӽڵ�����ַ����ִ�����ΪҶ�ӽڵ�Ȩ��
// ÿ��Ҷ�ӽڵ�����ַ����볤��Ϊ�Ӹ����ýڵ�·���ϱߵĸ���
// ���Ŷ���������
// �߱�n��Ҷ�ӽڵ�Ķ���������n��Ҷ�ӽڵ�� Ȩ��*������Ҷ�ӽڵ��·������ �ܺ���С��

// �κξ߱�n��Ҷ�ӽڵ�Ķ���������������һ�׿��е�������n���ַ�����ǰ׺��
// �����Ķ�������������

// ��ֻ�迼��
// [��n����ѡ0������n����ѡ��������n����ѡn3����..., ��n����ѡn/2��]
// ��ʹ��ˣ�����ѡ�������ý�С��ģ���ķ�ʽ��������Ϊѡ��̫�࣬����ɣ��㷨ִ��Ч�ʲ��ߡ�

// ��������Ƶ�� = ���� ��������Ҷ�ӽڵ�Ƶ�� * Ҷ�ӽڵ������и߶� ֮��
// ���մ˶���
// ��ֻ��Ҷ�ӽڵ����������Ƶ��Ϊ0
// ��ĳһʱ�̣��������ɻ����ཻ������k1,...,km����
// ���������������������ظ���Ҷ�ӽڵ㣬����m������Ҷ�ӽڵ㲢�����ڶ������Ľڵ㼯�ϡ������������ٺ�һ��Ҷ�ӽڵ㡣
// ��������Ƶ�� = ���� ����Ƶ��+������Ҷ�ӽڵ�Ƶ�Ⱥ� * �������ڵ��ڶ������ĸ߶� ֮��

// ��ʼʱ��
// n��Ҷ�ӽڵ㣬����n������
// ����֤��������Ƶ����С�����ϲ��ǹ������Ŷ�������Ȼѡ��

// �������������Ŷ�������n��Ҷ�ӽڵ�߶ȷֱ�Ϊh1,...,hn
// ������Ҫ֤����Ƶ����С����Ҷ�ӽڵ�ӵ�����߶�
// ��ӵ�����߶Ƚڵ�Ϊx1,x2,��߶�Ϊh1,h2
// ��Ƶ����С�ڵ�Ϊy1,y2,��߶�Ϊh3,h4
// ��x1,x2������y1,y2
// ������y1,y2���滻x1,x2�����������������õ�һ�����ŵĶ�������
// �����Ŷ�������Ȼy1,y2Ϊ��߶�������ڵ㡣

// ����ĳ��ѡ��ǰ��
// �������Ѿ��γɵ���������Ϊk1,...,km
// ������Ҫ֤����Ƶ����С�������������������������߶�
// ��ӵ�����߶������ڵ�Ϊx1,x2,��߶�Ϊh1,h2
// ��Ƶ����С�����ڵ�Ϊy1,y2,��߶�Ϊh3,h4
// ��x1,x2������y1,y2
// ������y1,y2���滻x1,x2�����������������õ�һ�����ŵĶ�������
// �����Ŷ�������Ȼy1,y2Ϊ��߶�������ڵ㡣

// ��֤
#endif


