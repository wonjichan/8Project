#include "SpartaCharacter.h"
#include "EnhancedInputComponent.h"
#include "SpartaPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASpartaCharacter::ASpartaCharacter()
{
	//SpringArm , Camera 컴포넌트 생성 + 컴포넌트 주소를 반환 후 포인터에 저장 
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm")); 
	SpringArmComp->SetupAttachment(RootComponent);
	//SpringArm 길이 설정 == 캐릭터(뒤통수)와 카메라 사이의 거리 설정 
	SpringArmComp->TargetArmLength = 300.0f; 
	//Player Controller를 통해 캐릭터를 회전 시 SpringArm도 같이 회전하도록 설정 
	SpringArmComp->bUsePawnControlRotation = true; 

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);
	//캐릭터 회전 시 SpringArm만 회전하니까 Camera는 회전하지 않고 고정시킨다. 
	CameraComp->bUsePawnControlRotation = false; 

	NormalSpeed = 600.0f; 
	SprintSpeedMultiplier = 2.0f; 
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier; 
	//캐릭터 이동 속도를 실시간 반영 
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed; 
}
void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//PlayerInputComponent = 입력 처리 컴포넌트이지만, EnhancedInput Compoennt 뿐만 아니라 다른 방식들도 지원하므로, 명시적으로 형변환 
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Character에 선언된 IA에 바인딩 할 함수 가져오기 
		//GetController() = 현재 Character를 조작하는 Controller를 가져온다.
		//가져온 컨트룰러를 SpartaPlayerController로 캐스팅 <= 우리가 만든 PlayerController를 변수로 사용하기 위해서 
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			//Nullptr 체크 
			if (PlayerController->MoveAction)
			{
				//바인딩
				EnhancedInput->BindAction(
					PlayerController->MoveAction, 
					//Key가 눌려서 이벤트가 발생했을 때 
					ETriggerEvent::Triggered,
					//입력 이벤트가 발생했을 때 호출된 함수의 객체 == Character 
					this,
					//실제로 호출된 함수, MoveAction일 때 Move()를 연결 
					&ASpartaCharacter::Move
				);
			}

			if (PlayerController->JumpAction)
			{
				//바인딩
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered, 
					this,
					&ASpartaCharacter::StartJump
				);
			}

			if (PlayerController->JumpAction)
			{
				//바인딩
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::StopJump
				);
			}

			if (PlayerController->LookAction)
			{
				//바인딩
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::Look
				);
			}

			if (PlayerController->SprintAction)
			{
				//바인딩
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					//Key가 눌려서 이벤트가 발생했을 때 
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::StartSprint
				);
			}

			if (PlayerController->SprintAction)
			{
				//바인딩
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::StopSprint
				);
			}
		}
	}

}
void ASpartaCharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return; 

	const FVector2D MoveInput = value.Get<FVector2D>(); 

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		//캐릭터 정면 방향 벡터를 가져오고, 정면 방향으로 X만큼 이동시키자 
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		//캐릭터 오른쪽 방향 벡터를 가져오고, 오른쪽으로 Y만큼 이동
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void ASpartaCharacter::StartJump(const FInputActionValue& value)
{
	//bool타입 value가 True면 
	if (value.Get<bool>())
	{
		Jump();
	}
}

void ASpartaCharacter::StopJump(const FInputActionValue& value)
{
	//bool타입 value가 False면
	if (!value.Get<bool>())
	{
		StopJumping();
	}
}

void ASpartaCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>(); 
	
	//Yaw(Z축)을 기준으로 좌우 회전 
	AddControllerYawInput(LookInput.X);
	//Pitch(Y축)을 기준으로 상하 회전
	//Look IA Value Type의 Modifier(값 변화)를 Nogate(* -1)을 했었다. 
	AddControllerPitchInput(LookInput.Y); 
}

void ASpartaCharacter::StartSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; 
	}
}

void ASpartaCharacter::StopSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}
