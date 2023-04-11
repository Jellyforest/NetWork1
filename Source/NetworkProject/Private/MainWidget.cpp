// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/TextBlock.h"
#include "../NetworkProjectCharacter.h"
#include "GameFramework/PlayerState.h"
#include "Components/Button.h"


void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	player = Cast<ANetworkProjectCharacter>(GetOwningPlayerPawn());
	btn_Exit->OnClicked.AddDynamic(this, &UMainWidget::ExitSession);

}

void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	text_Health->SetText(FText::AsNumber(player->GetHealth()));
	text_Ammo->SetText(FText::AsNumber(player->GetAmmo()));

	FString playerList;
	
	if (GetWorld()->GetGameState() != nullptr)
	{
		//ABattlePlayerController* gs = Cast<ABattlePlayerController>(GetWorld()->GetGameState());
		//for (const auto& ps : gs->GetPlayerListByScore())
	//	{
		//	FString playerName = ps->GetPlayerName();
		//	int32 playerScore = ps->GetScore();
		//	//playerList.Append(String::Printf(TEXT({ " % s : % d\n"})))
		//}

	}

	//for ()
	//GetWorld()->GetGameState()
}

void UMainWidget::ExitSession()
{
	if (player != nullptr)
	{
		player->EndSession();
	}

}

