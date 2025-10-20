#include "BaseItem.h"
#include "Components/SphereComponent.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene); 

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(Scene);
 
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision); 

	//이벤트 바인딩 
	
	//오버랩 영역에 들어왔을 때  
	Collision->OnComponentBeginOverlap()
	//오버랩 영역에서 빠져나왔을 때 
	Collision->OnComponentEndOverlap()
}
void ABaseItem::OnItemOverlap(AActor* OverlapActor)
{

}
void ABaseItem::OnItemEndOverlap(AActor* OverlapActor)
{

}
void ABaseItem::ActivateItem(AActor* Activator)
{

}
FName ABaseItem::GetItemType() const
{
	return ItemType;
}
void ABaseItem::DestroyItem()
{
	Destroy(); 
}

