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

	//�̺�Ʈ ���ε� 
	
	//������ ������ ������ ��  
	Collision->OnComponentBeginOverlap()
	//������ �������� ���������� �� 
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

