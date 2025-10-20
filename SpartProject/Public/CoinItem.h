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
	//휙득할 점수를 저장할 변수
	//휙득할 점수를 에디터 상에서 수정할 수 있도록 리플렉션 시스템 등록 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 PointValue; 
};
