#include "sceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "bootScene.h"
#include "titleScene.h"
#include "playScene.h"
#include "GameOver.h"

#include "GameClear.h"


<<<<<<< HEAD
//<<<<<<< HEAD
                           
//<<<<<< < HEAD
#include "GameClear.h"
	//====== =
	//>>>>>> > ed758e6451ebfd41b311136bd82e9f5c2f3ba03d
//=======

#include "GameClear.h"
//>>>>>>> 14b7e478f85fe04b605a79ca55e94df9108b5eca
=======
>>>>>>> 49c980feb97e41f305e93e61c798674777291dba


SceneBase* SceneFactory::CreateFirst()
{
	return new BootScene();
}

SceneBase * SceneFactory::Create(const std::string & name)
{
	if (name == "GameOver")
	{
		return new GameOver();
	}
	if (name == "TitleScene") {
		return new TitleScene();
	}
	if (name == "PlayScene") {
		return new PlayScene();
	}
	if (name == "CLEAR") {
		return new GameClear();
	}
	MessageBox(NULL, ("éüÇÃÉVÅ[ÉìÇÕÇ†ÇËÇ‹ÇπÇÒ\n" + name).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
