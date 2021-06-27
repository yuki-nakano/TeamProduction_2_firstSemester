#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "DxLib.h"
#include "../Definition.h"
#include "../Singleton.h"

class InputManager : public Singleton<InputManager>
{
public:
	//毎フレーム呼び出す
	void UpdateKeyStatus();

	//押した瞬間
	bool IsKeyPushed(int key);

	//押している
	bool IsKeyHeld(int key);

	//離した
	bool IsKeyRelesed(int key);

private:
	char keyStatus[256];
	char previousKeyStatus[256];
};

#endif // !INPUT_MANAGER_H
