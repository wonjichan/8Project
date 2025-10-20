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
	//�÷��̾��� �Է�,ȭ�� �並 �����ϴ� ��ü�� ������ 
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		//UEn	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())hancedInputLocalPlayerSubsystem 
		// = �Է� �ý����� ���� , IMC�� �߰�, �Ǵ� �����ϴ� ���� 
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			//�Ҵ��� ���ִٸ� , IMC ��ü�� �ִٸ� 
			if (InputMappingContext)
			{
				//AddMappingContext()�Լ��� Ȱ��ȭ�� ��Ű��. 0�� �켱������ ���� ����. 
				//IMC�� ��ġ�� Ư���� ��Ȳ������ �켱������ ���� Ȱ��ȭ 
				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}
