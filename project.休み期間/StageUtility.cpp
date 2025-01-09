#include "StageUtility.h"

namespace StageUtility
{
	static int stageNo;
}

void StageUtility::Init()
{
	StageUtility::stageNo = 0;
}

void StageUtility::SetStageNo(int no)
{
	stageNo = no;
}

int StageUtility::GetStageNo()
{
	return stageNo;
}
