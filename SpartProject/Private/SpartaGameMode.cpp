#include "SpartaGameMode.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
ASpartaGameMode::ASpartaGameMode()
{
	//StaticClass() => 객체를 생성하지 않고, 정적인 메소스 StaticClass() 통해 클래스를 반환해준다. 
	//UCLASS 형태의 타입을 반환 즉, 클래스 정보를 관리하는 타입 
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
}