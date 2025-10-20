#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

UCLASS()
class SPARTPROJECT_API AMineItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AMineItem(); 
	void OnItemOverlap(AActor* OverlapActor) override;
	void OnItemEndOverlap(AActor* OverlapActor) override;

	//즉시 발동형이 아니라 당장 재정의할 필요는 없다. 단, 이번엔 사용하겠다. 
	void ActivateItem(AActor* Activator) override; 

	//폭파하는데 걸리는 시간 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionDelay;
	//폭파 범위 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosRadius; 
	//폭파에 입는 데미지 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosDamage;
};
