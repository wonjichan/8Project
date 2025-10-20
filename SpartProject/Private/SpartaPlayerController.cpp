#include "SpartaPlayerController.h"
#include "EnhancedInputSubsystems.h"
ASpartaPlayerController::ASpartaPlayerController() 
	: InputMappingContext(nullptr), 
	MoveAction(nullptr),JumpAction(nullptr),
	LookAction(nullptr),SprintAction(nullptr)
{

}
void ASpartaPlayerController::BeginPlay()
{
	Super::BeginPlay();                                                         
	//플레이어의 입력,화면 뷰를 관리하는 객체를 가져와 
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		//UEn	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())hancedInputLocalPlayerSubsystem 
		// = 입력 시스템을 관리 , IMC를 추가, 또는 삭제하는 역할 
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			//할당이 되있다면 , IMC 객체가 있다면 
			if (InputMappingContext)
			{
				//AddMappingContext()함수로 활성화를 시키라. 0은 우선순위가 가장 높음. 
				//IMC가 겹치는 특수한 상황에서는 우선순위에 따라 활성화 
				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}
