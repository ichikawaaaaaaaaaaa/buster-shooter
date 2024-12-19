#pragma once
#include <string>
#include <vector>

/// <summary>
/// CSV�t�@�C����ǂ݁A�Z�����ƂɃf�[�^��Ԃ��܂�
/// �f�[�^�́Astring�^�Aint�^�Afloat�^�ŕԂ��܂�
/// 3�̉����т̃Z���ŁAVECTOR�^��Ԃ����Ƃ��ł��܂�
/// �͈͊O���w�肵���ꍇ�́Aassert���܂�
/// </summary>
class CsvReader {
public:
	CsvReader(std::string filename);
	~CsvReader();
	int GetLines();
	int GetColumns(int line);
	std::string GetString(int line, int column);
	int GetInt(int line, int column);
	float GetFloat(int line, int column);
private:
	struct LINEREC {
		std::vector<std::string> record;
	};
	std::vector<LINEREC> all;
};
