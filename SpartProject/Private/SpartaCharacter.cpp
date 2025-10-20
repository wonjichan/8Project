#include "SpartaCharacter.h"
#include "EnhancedInputComponent.h"
#include "SpartaPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASpartaCharacter::ASpartaCharacter()
{
	//SpringArm , Camera ������Ʈ ���� + ������Ʈ �ּҸ� ��ȯ �� �����Ϳ� ���� 
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm")); 
	SpringArmComp->SetupAttachment(RootComponent);
	//SpringArm ���� ���� == ĳ����(�����)�� ī�޶� ������ �Ÿ� ���� 
	SpringArmComp->TargetArmLength = 300.0f; 
	//Player Controller�� ���� ĳ���͸� ȸ�� �� SpringArm�� ���� ȸ���ϵ��� ���� 
	SpringArmComp->bUsePawnControlRotation = true; 

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);
	//ĳ���� ȸ�� �� SpringArm�� ȸ���ϴϱ� Camera�� ȸ������ �ʰ� ������Ų��. 
	CameraComp->bUsePawnControlRotation = false; 

	NormalSpeed = 600.0f; 
	SprintSpeedMultiplier = 2.0f; 
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier; 
	//ĳ���� �̵� �ӵ��� �ǽð� �ݿ� 
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed; 
}
void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//PlayerInputComponent = �Է� ó�� ������Ʈ������, EnhancedInput Compoennt �Ӹ� �ƴ϶� �ٸ� ��ĵ鵵 �����ϹǷ�, ��������� ����ȯ 
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Character�� ����� IA�� ���ε� �� �Լ� �������� 
		//GetController() = ���� Character�� �����ϴ� Controller�� �����´�.
		//������ ��Ʈ�귯�� SpartaPlayerController�� ĳ���� <= �츮�� ���� PlayerController�� ������ ����ϱ� ���ؼ� 
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			//Nullptr üũ 
			if (PlayerController->MoveAction)
			{
				//���ε�
				EnhancedInput->BindAction(
					PlayerController->MoveAction, 
					//Key�� ������ �̺�Ʈ�� �߻����� �� 
					ETriggerEvent::Triggered,
					//�Է� �̺�Ʈ�� �߻����� �� ȣ��� �Լ��� ��ü == Character 
					this,
					//������ ȣ��� �Լ�, MoveAction�� �� Move()�� ���� 
					&ASpartaCharacter::Move
				);
			}

			if (PlayerController->JumpAction)
			{
				//���ε�
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered, 
					this,
					&ASpartaCharacter::StartJump
				);
			}

			if (PlayerController->JumpAction)
			{
				//���ε�
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::StopJump
				);
			}

			if (PlayerController->LookAction)
			{
				//���ε�
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::Look
				);
			}

			if (PlayerController->SprintAction)
			{
				//���ε�
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					//Key�� ������ �̺�Ʈ�� �߻����� �� 
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::StartSprint
				);
			}

			if (PlayerController->SprintAction)
			{
				//���ε�
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
		//ĳ���� ���� ���� ���͸� ��������, ���� �������� X��ŭ �̵���Ű�� 
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		//ĳ���� ������ ���� ���͸� ��������, ���������� Y��ŭ �̵�
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void ASpartaCharacter::StartJump(const FInputActionValue& value)
{
	//boolŸ�� value�� True�� 
	if (value.Get<bool>())
	{
		Jump();
	}
}

void ASpartaCharacter::StopJump(const FInputActionValue& value)
{
	//boolŸ�� value�� False��
	if (!value.Get<bool>())
	{
		StopJumping();
	}
}

void ASpartaCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>(); 
	
	//Yaw(Z��)�� �������� �¿� ȸ�� 
	AddControllerYawInput(LookInput.X);
	//Pitch(Y��)�� �������� ���� ȸ��
	//Look IA Value Type�� Modifier(�� ��ȭ)�� Nogate(* -1)�� �߾���. 
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
