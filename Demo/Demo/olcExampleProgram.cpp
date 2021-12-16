#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Environment.h"

class Example : public olc::PixelGameEngine
{
private: 
	std::string strAppo = "";
	
public:

	template <typename T> std::string tostr(const T& t)
	{
		std::ostringstream os;
		os << t;
		return os.str();
	}

	Example() {
		sAppName = "Esempio";
	}

	BOOL colMode80;	// true: 80 coloumn mode; false: 40 coloumn mode;
		
	bool OnUserCreate() override {
		// Called once at the start, so create things here
		
		environment.ScreenMode = colMode80;
		environment.InitScreen(this);

		environment.screenMemIndex = (colMode80 ? 400 : 200);
		environment.newScreenMemIndex = (colMode80 ? 400 : 200);


		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		// called once per frame
		environment.fTimeEl += fElapsedTime;
		environment.fTimeChar += fElapsedTime;

		Clear(olc::BLANK);
		
		strAppo = "";

		environment.SyncVirtualScreenMap(this);

		// visualizza il fontsprite (potrebbe essere il tilemap sprite)
		//DrawSprite((colMode80 ? 100 : 50), 100, environment.fontSprite);

		SetDrawTarget(nullptr);

		if (IsFocused()) {

			if (GetKey(olc::Key::LEFT).bHeld) {
				strAppo = "LEFT";
				// sposta il cursore a sinistra
				if (environment.fTimeChar >= 0.06f) {
					if (environment.screenMemIndex > 0) environment.newScreenMemIndex -= 1;
					environment.fTimeChar = 0;
				}
			}

			if (GetKey(olc::Key::RIGHT).bHeld) {
				strAppo = "RIGHT";
				// sposta il cursore a destra
				if (environment.fTimeChar >= 0.06f) {
					if (environment.screenMemIndex < (colMode80 ? 2399 : 1199)) environment.newScreenMemIndex += 1;
					environment.fTimeChar = 0;
				}
			}

			if (GetKey(olc::Key::UP).bHeld) {
				strAppo = "UP";
				if (environment.fTimeChar >= 0.06f) {
					if (environment.screenMemIndex > (colMode80 ? 79 : 39)) environment.newScreenMemIndex -= (colMode80 ? 80 : 40);
					environment.fTimeChar = 0;
				}
			}

			if (GetKey(olc::Key::DOWN).bHeld) {
				strAppo = "DOWN";
				if (environment.fTimeChar >= 0.06f) {
					if (environment.screenMemIndex < (colMode80 ? 2319 : 1159)) environment.newScreenMemIndex += (colMode80 ? 80 : 40);
					environment.fTimeChar = 0;
				}
			}

			if (GetKey(olc::Key::ENTER).bPressed) {
				strAppo = "ENTER";
				if (environment.fTimeChar >= 0.06f) {
					if (environment.screenMemIndex < (colMode80 ? 2319 : 1159)) environment.newScreenMemIndex = ((environment.cursorRow + 1) * (colMode80 ? 80 : 40));
					environment.fTimeChar = 0;
				}
			}
		}

		environment.SetCursor(this,strAppo);

		// timing di azzeramento per lampeggio cursore
		if (environment.fTimeEl >= 0.6f) environment.fTimeEl = 0.0f;

		DrawString((colMode80 ? 100 : 50), 260, "Tasto : " + strAppo);
		DrawString((colMode80 ? 340 : 170), 260, "Tempo : " + tostr(environment.fTimeEl));
		DrawString((colMode80 ? 100 : 50), 268, "Riga : " + tostr(environment.cursorRow) + "     Colonna : " + tostr(environment.cursorCol) + "        " + tostr(environment.screenMemIndex));

		return true;
	}

protected:
	Environment environment;
};

int main()
{
	Example demo;
	
	demo.colMode80 = false;

	if (demo.Construct((demo.colMode80 ? 840 : 420), 280, (demo.colMode80 ? 1 : 2), 2))
		demo.Start();

	return 0;
}
