#pragma once

#include <GameFramework/Level.h>

class TestLevel : public Craft::Level
{
protected:
	// 초기화할 때 사용하는 함수.
	// 액터 생성 처리를 여기에서 해야함.
	virtual void Initialized() override;
};
