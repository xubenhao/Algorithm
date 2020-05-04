//	Author : XuBenHao                                                  
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef AILIB_ALGORITHM_CHAR_CHARMATCH_H
#define AILIB_ALGORITHM_CHAR_CHARMATCH_H
#include "..\..\stdafx.h"
#include "..\..\DataStruct\Array\DynArray.h"

namespace AlLib
{
	namespace Algorithm
	{
		namespace Char
		{
			template<typename T>
			class CharacterMatch
			{
			public:
				CharacterMatch();
				~CharacterMatch();
			public:
				DataStruct::Array::DynArray<int> RunInBasic(
					const DataStruct::Array::DynArray<T>& arrPattern_,
					const DataStruct::Array::DynArray<T>& arrSource_);
				DataStruct::Array::DynArray<int> RunInAutoMachine(
					const DataStruct::Array::DynArray<T>& arrPattern_,
					const DataStruct::Array::DynArray<T>& arrSource_);
				DataStruct::Array::DynArray<int> RunKMP(
					const DataStruct::Array::DynArray<T>& arrPattern_,
					const DataStruct::Array::DynArray<T>& arrSource_);
			private:
				DataStruct::Array::DynArray<int> PatternPreAnalysis(
					const DataStruct::Array::DynArray<T>& arrPattern_);
			};

			template<typename T>
			CharacterMatch<T>::CharacterMatch()
			{

			}

			template<typename T>
			CharacterMatch<T>::~CharacterMatch()
			{

			}

			template<typename T>
			DataStruct::Array::DynArray<int> CharacterMatch<T>::RunInBasic(
				const DataStruct::Array::DynArray<T>& arrPattern_,
				const DataStruct::Array::DynArray<T>& arrSource_)
			{
				// ����&ԭʼ�ⷨ
				// ����S�е�ÿһ��λ��
				// �Ӹ�λ�������ν�����k��Ԫ�طֱ��P�ж�ӦԪ��һһ�Ƚϣ���ȫ�����
				// ���λ�ô���P��
				// ���򣬼���������һλ��
				int _nPatternLen = arrPattern_.GetSize();
				int _nSourceLen = arrSource_.GetSize();
				DataStruct::Array::DynArray<int> _arrRet;
				for (int _i = 0; _i < _nSourceLen; _i++)
				{
					int _k = 0;
					while (_k < _nPatternLen)
					{
						if (arrSource_[_i + _k] == arrPattern_[_k])
						{
							_k++;
						}
						else
						{
							break;
						}
					}

					if (_k == _nPatternLen)
					{
						_arrRet.Add(_i);
					}
				}

				return _arrRet;
			}

			template<typename T>
			DataStruct::Array::DynArray<int> CharacterMatch<T>::RunInAutoMachine(
				const DataStruct::Array::DynArray<T>& arrPattern_,
				const DataStruct::Array::DynArray<T>& arrSource_)
			{
				int _nPatternLen = arrPattern_.GetSize();
				int _nSourceLen = arrSource_.GetSize();
				int _nPreMaxMatchLen = 0;
				int _nCurMaxMatchLen = 0;
				DataStruct::Array::DynArray<int> _arrRet;
				for (int _i = 0; _i < _nSourceLen; _i++)
				{
					if (_nPreMaxMatchLen == _nPatternLen)
					{
						for (int _nCurMayMaxMatchLen = _nPreMaxMatchLen; _nCurMayMaxMatchLen >= 0; _nCurMayMaxMatchLen--)
						{
							bool _bSuccess = true;
							int _k = 0;
							while (_k < _nCurMayMaxMatchLen)
							{
								if (arrSource_[_i - _k] == arrPattern_[_nCurMayMaxMatchLen - 1 - _k])
								{
									_k++;
								}
								else
								{
									break;
								}
							}

							if (_k == _nCurMayMaxMatchLen)
							{
								_bSuccess = true;
							}
							else
							{
								_bSuccess = false;
							}

							if (_bSuccess)
							{
								_nCurMaxMatchLen = _nCurMayMaxMatchLen;
								break;
							}
						}
					}
					else
					{
						if (arrSource_[_i] == arrPattern_[_nPreMaxMatchLen])
						{
							_nCurMaxMatchLen = _nPreMaxMatchLen + 1;
						}
						else
						{
							for (int _nCurMayMaxMatchLen = _nPreMaxMatchLen; _nCurMayMaxMatchLen >= 0; _nCurMayMaxMatchLen--)
							{
								bool _bSuccess = true;
								int _k = 0;
								while (_k < _nCurMayMaxMatchLen)
								{
									if (arrSource_[_i - _k] == arrPattern_[_nCurMayMaxMatchLen - 1 - _k])
									{
										_k++;
									}
									else
									{
										break;
									}
								}

								if (_k == _nCurMayMaxMatchLen)
								{
									_bSuccess = true;
								}
								else
								{
									_bSuccess = false;
								}

								if (_bSuccess)
								{
									_nCurMaxMatchLen = _nCurMayMaxMatchLen;
									break;
								}
							}
						}
					}

					if (_nCurMaxMatchLen == _nPatternLen)
					{
						_arrRet.Add(_i - _nPatternLen + 1);
					}

					_nPreMaxMatchLen = _nCurMaxMatchLen;
				}
			}

			template<typename T>
			DataStruct::Array::DynArray<int> CharacterMatch<T>::RunKMP(
				const DataStruct::Array::DynArray<T>& arrPattern_,
				const DataStruct::Array::DynArray<T>& arrSource_)
			{
				DataStruct::Array::DynArray<int> _arrRet;
				DataStruct::Array::DynArray<int> _nPatternRet = PatternPreAnalysis(arrPattern_);
				int _nPreMatchLen = 0;
				int _nCurMatchLen = 0;
				for (int _i = 0; _i < arrSource_.GetSize(); _i++)
				{
					if (_nPreMatchLen == arrPattern_.GetSize())
					{
						_nPreMatchLen = _nPatternRet[_nPreMatchLen - 1];
					}

					if (arrSource_[_i] == arrPattern_[_nPreMatchLen])
					{
						_nCurMatchLen = _nPreMatchLen + 1;
					}
					else
					{
						_nCurMatchLen = 0;
						while (_nPreMatchLen > 0)
						{
							_nPreMatchLen = _nPatternRet[_nPreMatchLen - 1];
							if (arrSource_[_i] == arrPattern_[_nPreMatchLen])
							{
								_nCurMatchLen = _nPreMatchLen + 1;
								break;
							}
						}
					}

					_nPreMatchLen = _nCurMatchLen;
					if (_nCurMatchLen == arrPattern_.GetSize())
					{
						_arrRet.Add(_i - arrPattern_.GetSize() + 1);
					}
				}

				return _arrRet;
			}

			template<typename T>
			DataStruct::Array::DynArray<int> CharacterMatch<T>::PatternPreAnalysis(
				const DataStruct::Array::DynArray<T>& arrPattern_)
			{
				DataStruct::Array::DynArray<int> _nPatternRet;
				int _nSize = arrPattern_.GetSize();
				for (int _i = 0; _i < _nSize; _i++)
				{
					int _nNum = 0;
					int _nMayNum = _i;
					// ��_nNum���п���ȡֵ��_i,...,0���ν�����֤
					for (; _nMayNum > 0; _nMayNum--)
					{
						// ��Ҫ��֤ x0,...,x[MN-1] �� x0 ... xi�ĺ�׺
						int _nStartIndex = _i - _nMayNum + 1;
						bool _bMatch = true;
						for (int _k = 0; _k < _nMayNum; _k++)
						{
							if (arrPattern_[_nStartIndex + _k] != arrPattern_[_k])
							{
								_bMatch = false;
								break;
							}
						}

						if (_bMatch)
						{
							_nNum = _nMayNum;
							break;
						}
					}

					_nPatternRet.Add(_nNum);
				}

				return _nPatternRet;
			}
		}
	}
}
#endif
