// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameStateBase.h"
#include "GameFrameWork/PlayerState.h"


//�÷��̾� ������Ʈ ����Ʈ�� ������ ���� ������������ �����Ͽ� ��ȯ�ϴ� �Լ�
TArray<class APlayerState*> ABattleGameStateBase::GetPlayerListByScore()
{
	TArray<APlayerState*>playerList = PlayerArray;

	//Sort�� �������� > �տ� �ΰ� �׸��� ������������ �ڸ��� �ٲ�, <��������
	//�����ڷ� �ٲ㼭 ����  �׷��� . ���� �����;���
	PlayerArray.Sort([](const APlayerState& a, const APlayerState& b) { return a.GetScore() > b.GetScore(); }); 
	return playerList;
}
