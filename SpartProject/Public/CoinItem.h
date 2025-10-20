#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "CoinItem.generated.h"

UCLASS()
class SPARTPROJECT_API ACoinItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ACoinItem(); 
	
protected:
	//�׵��� ������ ������ ����
	//�׵��� ������ ������ �󿡼� ������ �� �ֵ��� ���÷��� �ý��� ��� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 PointValue; 
};
