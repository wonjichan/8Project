#include "HealingItem.h"

AHealingItem::AHealingItem()
{
	Healamount = 20.0f;
	ItemType = "Healing";
}
void AHealingItem::ActivateItem(AActor* Activator)
{
		DestroyItem();
}
