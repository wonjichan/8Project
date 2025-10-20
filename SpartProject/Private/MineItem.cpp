#include "MineItem.h"

AMineItem::AMineItem()
{
	ExplosionDelay = 5.0f; 
	ExplosRadius = 300.0f; 
	ExplosDamage = 30.0f; 
	ItemType = "Mine";
}
void AMineItem::OnItemOverlap(AActor* OverlapActor)
{

}
void AMineItem::OnItemEndOverlap(AActor* OverlapActor)
{

}
void AMineItem::ActivateItem(AActor* Actor)
{
	DestroyItem(); 
}