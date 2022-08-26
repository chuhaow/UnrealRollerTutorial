


#include "RollerGameModeBase.h"

#include "RollerWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Roller/Item/Collectible.h"

void ARollerGameModeBase::BeginPlay()
{
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACollectible::StaticClass(), Items);
	ItemsInLevel = Items.Num();
	if(GameWidgetClass)
	{
		GameWidget = Cast<URollerWidget>(CreateWidget(GetWorld(), GameWidgetClass));
		if(GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void ARollerGameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}

void ARollerGameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}
