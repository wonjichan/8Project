#include "SpartaGameMode.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
ASpartaGameMode::ASpartaGameMode()
{
	//StaticClass() => ��ü�� �������� �ʰ�, ������ �޼ҽ� StaticClass() ���� Ŭ������ ��ȯ���ش�. 
	//UCLASS ������ Ÿ���� ��ȯ ��, Ŭ���� ������ �����ϴ� Ÿ�� 
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
}