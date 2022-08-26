
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RollerWidget.generated.h"


UCLASS()
class ROLLER_API URollerWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintImplementableEvent)
		void SetItemText(int32 ItemsCollected, int32 ItemsInLevel);
		
};
