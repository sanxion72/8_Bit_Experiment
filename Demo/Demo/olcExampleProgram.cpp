#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Environment.h"

class Example : public olc::PixelGameEngine
{
private: 
	
public:
	Example()
	{
		sAppName = "Esempio";
	}

	BOOL colMode80 = true;	// true: 80 coloumn mode; false: 40 coloumn mode;

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		environment.ScreenMode = colMode80;
		environment.InitScreen(this);

		// visualizza il fontsprite (potrebbe essere il tilemap sprite)
		//DrawSprite((colMode80 ? 100 : 50), 100, environment.fontSprite);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		Clear(olc::BLANK);

		environment.SyncVirtualScreenMap(this);

		SetDrawTarget(nullptr);

		return true;
	}
protected:
	Environment environment;
};

int main()
{
	Example demo;
	
	if (demo.Construct((demo.colMode80 ? 840 : 420), 280, (demo.colMode80 ? 1 : 2), 2))
		demo.Start();

	return 0;
}
