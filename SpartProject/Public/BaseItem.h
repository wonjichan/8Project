#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "BaseItem.generated.h"

class USphereComponent;

UCLASS()
class SPARTPROJECT_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	ABaseItem();

public:	
	virtual void OnItemOverlap(AActor* OverlapActor) override;
	virtual void OnItemEndOverlap(AActor* OverlapActor) override;
	virtual void ActivateItem(AActor* Activator) override;
	virtual FName GetItemType() const override;
	//��� �������� ������ ������Ƿ�, ���� �޼ҵ� 
	virtual void DestroyItem(); 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Scene")
	USceneComponent* Scene; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scene")
	UStaticMeshComponent* StaticMesh; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scene")
	USphereComponent* Collision;
};
