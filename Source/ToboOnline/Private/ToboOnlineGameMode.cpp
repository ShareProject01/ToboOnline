#include "ToboOnlineGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/Blueprint.h"
#include "UObject/Class.h"

AToboOnlineGameMode::AToboOnlineGameMode()
{
	static ConstructorHelpers::FClassFinder<ACharacter> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	if (PlayerPawnClassFinder.Succeeded())
	{
		DefaultPawnClass = PlayerPawnClassFinder.Class;
	}
}

bool AToboOnlineGameMode::SetBlueprintGameStateClass(UObject* GameModeBlueprint, TSubclassOf<AGameStateBase> NewGameStateClass)
{
	UBlueprint* Blueprint = Cast<UBlueprint>(GameModeBlueprint);
	if (!Blueprint || !Blueprint->GeneratedClass || !NewGameStateClass)
	{
		return false;
	}

	FClassProperty* GameStateProperty = FindFProperty<FClassProperty>(AGameModeBase::StaticClass(), TEXT("GameStateClass"));
	if (!GameStateProperty)
	{
		return false;
	}

	GameStateProperty->SetPropertyValue_InContainer(Blueprint->GeneratedClass->GetDefaultObject(), NewGameStateClass);
	return true;
}
