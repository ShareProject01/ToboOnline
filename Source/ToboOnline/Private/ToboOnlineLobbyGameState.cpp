#include "ToboOnlineLobbyGameState.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"

AToboOnlineLobbyGameState::AToboOnlineLobbyGameState()
{
	bReplicates = true;
}

void AToboOnlineLobbyGameState::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		RefreshTimerHandle,
		this,
		&AToboOnlineLobbyGameState::RefreshLobbyState,
		0.25f,
		true);
}

void AToboOnlineLobbyGameState::RefreshLobbyState()
{
	if (HasAuthority())
	{
		const int32 NewTotal = PlayerArray.Num();
		if (TotalPlayerNumber != NewTotal)
		{
			TotalPlayerNumber = NewTotal;
		}
	}

	// Also refresh on clients so a UI created after replication receives the current value.
	NotifyLobbyControllers();
}

void AToboOnlineLobbyGameState::RefreshTotalPlayerNumber()
{
	if (!HasAuthority())
	{
		return;
	}

	const int32 NewTotal = PlayerArray.Num();
	if (TotalPlayerNumber != NewTotal)
	{
		TotalPlayerNumber = NewTotal;
		NotifyLobbyControllers();
	}
}

void AToboOnlineLobbyGameState::OnRep_TotalPlayerNumber()
{
	NotifyLobbyControllers();
}

void AToboOnlineLobbyGameState::NotifyLobbyControllers()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PlayerController = It->Get();
		if (!PlayerController || !PlayerController->IsLocalController())
		{
			continue;
		}

		// Keep the existing Blueprint controller/UI contract intact.
		if (FIntProperty* TotalProperty = FindFProperty<FIntProperty>(PlayerController->GetClass(), TEXT("TotalPlayerNumber")))
		{
			TotalProperty->SetPropertyValue_InContainer(PlayerController, TotalPlayerNumber);
		}

		if (UFunction* UpdateFunction = PlayerController->FindFunction(TEXT("OnRep_TotalPlayerNumber")))
		{
			PlayerController->ProcessEvent(UpdateFunction, nullptr);
		}
	}
}

void AToboOnlineLobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AToboOnlineLobbyGameState, TotalPlayerNumber);
}
