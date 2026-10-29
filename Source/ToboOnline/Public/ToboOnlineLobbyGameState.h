#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ToboOnlineLobbyGameState.generated.h"

UCLASS()
class TOBOONLINE_API AToboOnlineLobbyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AToboOnlineLobbyGameState();

	UPROPERTY(ReplicatedUsing=OnRep_TotalPlayerNumber, BlueprintReadOnly, Category="Lobby")
	int32 TotalPlayerNumber = 0;

	UFUNCTION(BlueprintCallable, Category="Lobby")
	void RefreshTotalPlayerNumber();

protected:
	UFUNCTION()
	void OnRep_TotalPlayerNumber();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	void RefreshLobbyState();
	void NotifyLobbyControllers();
	FTimerHandle RefreshTimerHandle;
};
