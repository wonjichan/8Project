#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
//���� ���� 
struct FInputActionValue; 
UCLASS()
class SPARTPROJECT_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASpartaCharacter();

protected:	
	//���� �ӵ� == �⺻ �� 
	float NormalSpeed;
	//���� �⺻ �ӵ� ������ �� �� ���� ������ 
	float SprintSpeedMultiplier;
	//NormalSpeed * SprintSpeedMultiplier = ������Ʈ �ӵ� 
	float SprintSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//IA �Ӽ� ���� �� Value Type�� �Ķ���ͷ� ����. 
	//�Է� ���ε� �Լ��� ���÷��� �ý��ۿ� ����� �Ǿ�� �Ѵ�. == FUNCTION 
	//=>Enhanced Input System���� �Է� �ٿ��  �Լ��� �ν� �Ϸ��� ���÷��ǿ� ��ϵǾ�� ��. 
	//BP�� �������� �ʰ�, ���縸 �˸��� �������� ���÷��� �ý��ۿ� ��ϸ� �س���. 
	UFUNCTION()
	void Move(const FInputActionValue& value);
	//Value Type�� Bool ���� ON/OFF�� ������ 
	UFUNCTION()
	void StartJump(const FInputActionValue& value); 
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);
};
