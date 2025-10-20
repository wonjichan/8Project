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

	//��� �ߵ����� �ƴ϶� ���� �������� �ʿ�� ����. ��, �̹��� ����ϰڴ�. 
	void ActivateItem(AActor* Activator) override; 

	//�����ϴµ� �ɸ��� �ð� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionDelay;
	//���� ���� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosRadius; 
	//���Ŀ� �Դ� ������ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosDamage;
};
