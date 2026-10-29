#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToboOnlineGameMode.generated.h"

class AGameStateBase;

UCLASS()
class TOBOONLINE_API AToboOnlineGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AToboOnlineGameMode();

	UFUNCTION(BlueprintCallable, Category="Lobby", meta=(DevelopmentOnly))
	static bool SetBlueprintGameStateClass(UObject* GameModeBlueprint, TSubclassOf<AGameStateBase> NewGameStateClass);
};
