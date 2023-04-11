// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameStateBase.h"
#include "GameFrameWork/PlayerState.h"


//플레이어 스테이트 리스트를 점수에 따라서 내림차순으로 정렬하여 변환하는 함수
TArray<class APlayerState*> ABattleGameStateBase::GetPlayerListByScore()
{
	TArray<APlayerState*>playerList = PlayerArray;

	//Sort는 내림차순 > 앞에 두개 그리고 다음다음으로 자리를 바꿈, <오름차순
	//참조자로 바꿔서 직접  그러면 . 으로 가져와야함
	PlayerArray.Sort([](const APlayerState& a, const APlayerState& b) { return a.GetScore() > b.GetScore(); }); 
	return playerList;
}
