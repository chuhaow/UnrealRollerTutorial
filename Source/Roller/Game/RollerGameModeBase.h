

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollerGameModeBase.generated.h"

class URollerWidget;
/**
 * 
 */
UCLASS()
class ROLLER_API ARollerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	protected:
	    int32 ItemsCollected = 0;
	    int32 ItemsInLevel = 0;

		UPROPERTY(EditAnywhere, Category="Widgets")
	    TSubclassOf<class UUserWidget> GameWidgetClass;

		UPROPERTY()
		URollerWidget* GameWidget;
	
	    virtual void BeginPlay() override;
	
	    void UpdateItemText();
	    
	public:
		void ItemCollected();
	
	
	
};
