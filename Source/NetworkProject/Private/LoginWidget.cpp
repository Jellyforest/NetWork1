// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/Slider.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ScrollBox.h"
#include "ServerGameInstance.h"
#include "SessionSlotWidget.h"


void ULoginWidget::NativeConstruct()
{
	// Ȥ�� �� �Է� �ʵ��� ���� �� ĭ���� �ʱ�ȭ�Ѵ�.
	editText_id->SetText(FText::FromString(""));
	editText_roomName->SetText(FText::FromString(""));
	sl_playerCount->SetValue(2.0f);
	text_playerCount->SetText(FText::FromString("2"));

	// ��ư Ŭ�� �̺�Ʈ�� �Լ� ���ε��ϱ�
	btn_Start->OnClicked.AddDynamic(this, &ULoginWidget::ClickStart);
	btn_CreateSession->OnClicked.AddDynamic(this, &ULoginWidget::CreateServer);
	sl_playerCount->OnValueChanged.AddDynamic(this, &ULoginWidget::OnMoveSlider);
	btn_GoCreate->OnClicked.AddDynamic(this, &ULoginWidget::GoCreate);
	btn_GoFind->OnClicked.AddDynamic(this, &ULoginWidget::GoFind);
	btn_CreateBack->OnClicked.AddDynamic(this, &ULoginWidget::GoBack);
	btn_FindBack->OnClicked.AddDynamic(this, &ULoginWidget::GoBack);
	btn_Refresh->OnClicked.AddDynamic(this, &ULoginWidget::RefreshList);

	gameInstance = Cast<UServerGameInstance>(GetGameInstance());

	if (gameInstance != nullptr)
	{
		gameInstance->searchResultDele.AddDynamic(this, &ULoginWidget::AddNewSlot);
		gameInstance->searchFinishedDele.AddDynamic(this, &ULoginWidget::RefreshEnabled);
	}
}

void ULoginWidget::ClickStart()
{
	// ����, ID�� �� ĭ�� �ƴ϶�� 0�� -> 1�� ĵ������ �����Ѵ�.
	if (!editText_id->GetText().IsEmpty())
	{
		widgetSwitcher->SetActiveWidgetIndex(1);
		gameInstance->sessionID = FName(*editText_id->GetText().ToString());
	}
}

void ULoginWidget::CreateServer()
{
	int32 playerCnt = FMath::RoundHalfFromZero(sl_playerCount->GetValue());

	gameInstance->CreateMySession(editText_roomName->GetText().ToString(), playerCnt);
}

// �����̴� ���� ����� �� ȣ��Ǵ� �Լ�
void ULoginWidget::OnMoveSlider(float Value)
{
	int32 newVal = FMath::RoundHalfFromZero(Value);
	text_playerCount->SetText(FText::AsNumber(newVal));
}

void ULoginWidget::GoCreate()
{
	widgetSwitcher->SetActiveWidgetIndex(2);
}

void ULoginWidget::GoFind()
{
	widgetSwitcher->SetActiveWidgetIndex(3);
	RefreshList();
}

void ULoginWidget::GoBack()
{
	widgetSwitcher->SetActiveWidgetIndex(1);
}

// ���� �ν��Ͻ��κ��� �˻� �Ϸ� �̺�Ʈ�� �޾��� �� ����� �Լ�
void ULoginWidget::AddNewSlot(FSessionInfo sessionInfo)
{
	USessionSlotWidget* slotWidget = CreateWidget<USessionSlotWidget>(this, sessionSlot);
	
	if (slotWidget != nullptr)
	{
		slotWidget->text_roomName->SetText(FText::FromString(sessionInfo.roomName));
		slotWidget->text_playerInfo->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), sessionInfo.currentPlayers, sessionInfo.maxPlayers)));
		slotWidget->text_ping->SetText(FText::FromString(FString::Printf(TEXT("%d ms"), sessionInfo.ping)));
		slotWidget->index = sessionInfo.idx;

		sbox_RoomList->AddChild(slotWidget);
	}
}

// ���� ����Ʈ ���ΰ�ħ �Լ�
void ULoginWidget::RefreshList()
{
	sbox_RoomList->ClearChildren();
	gameInstance->FindMySession();
	btn_Refresh->SetIsEnabled(false);
}

void ULoginWidget::RefreshEnabled()
{
	btn_Refresh->SetIsEnabled(true);
}