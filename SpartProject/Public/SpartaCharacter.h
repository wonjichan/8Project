#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
//전방 선언 
struct FInputActionValue; 
UCLASS()
class SPARTPROJECT_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASpartaCharacter();

protected:	
	//현재 속도 == 기본 값 
	float NormalSpeed;
	//현재 기본 속도 값에서 몇 배 곱할 것인지 
	float SprintSpeedMultiplier;
	//NormalSpeed * SprintSpeedMultiplier = 스프린트 속도 
	float SprintSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//IA 속성 설정 시 Value Type을 파라미터로 받음. 
	//입력 바인딩 함수는 리플렉션 시스템에 등록이 되어야 한다. == FUNCTION 
	//=>Enhanced Input System에서 입력 바운딩  함수를 인식 하려면 리플렉션에 등록되어야 함. 
	//BP에 노출하지 않고, 존재만 알리는 차원으로 리플렉션 시스템에 등록만 해놓기. 
	UFUNCTION()
	void Move(const FInputActionValue& value);
	//Value Type이 Bool 값은 ON/OFF를 나누자 
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
