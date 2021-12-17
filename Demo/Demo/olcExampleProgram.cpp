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
			if (GetKey(olc::Key::A).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "A"; }
			else { if (GetKey(olc::Key::A).bHeld) { strAppo = "a"; } }
			if (GetKey(olc::Key::B).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "B"; }
			else { if (GetKey(olc::Key::B).bHeld) { strAppo = "b"; } }
			if (GetKey(olc::Key::C).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "C"; }
			else { if (GetKey(olc::Key::C).bHeld) { strAppo = "c"; } }
			if (GetKey(olc::Key::D).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "D"; }
			else { if (GetKey(olc::Key::D).bHeld) { strAppo = "d"; } }
			if (GetKey(olc::Key::E).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "E"; }
			else { if (GetKey(olc::Key::E).bHeld) { strAppo = "e"; } }
			if (GetKey(olc::Key::F).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "F"; }
			else { if (GetKey(olc::Key::F).bHeld) { strAppo = "f"; } }
			if (GetKey(olc::Key::G).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "G"; }
			else { if (GetKey(olc::Key::G).bHeld) { strAppo = "g"; } }
			if (GetKey(olc::Key::H).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "H"; }
			else { if (GetKey(olc::Key::H).bHeld) { strAppo = "h"; } }
			if (GetKey(olc::Key::I).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "I"; }
			else { if (GetKey(olc::Key::I).bHeld) { strAppo = "i"; } }
			if (GetKey(olc::Key::J).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "J"; }
			else { if (GetKey(olc::Key::J).bHeld) { strAppo = "j"; } }
			if (GetKey(olc::Key::K).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "K"; }
			else { if (GetKey(olc::Key::K).bHeld) { strAppo = "k"; } }
			if (GetKey(olc::Key::L).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "L"; }
			else { if (GetKey(olc::Key::L).bHeld) { strAppo = "l"; } }
			if (GetKey(olc::Key::M).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "M"; }
			else { if (GetKey(olc::Key::M).bHeld) { strAppo = "m"; } }
			if (GetKey(olc::Key::N).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "N"; }
			else { if (GetKey(olc::Key::N).bHeld) { strAppo = "n"; } }
			if (GetKey(olc::Key::O).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "O"; }
			else { if (GetKey(olc::Key::O).bHeld) { strAppo = "o"; } }
			if (GetKey(olc::Key::P).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "P"; }
			else { if (GetKey(olc::Key::P).bHeld) { strAppo = "p"; } }
			if (GetKey(olc::Key::Q).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "Q"; }
			else { if (GetKey(olc::Key::Q).bHeld) { strAppo = "q"; } }
			if (GetKey(olc::Key::R).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "R"; }
			else { if (GetKey(olc::Key::R).bHeld) { strAppo = "r"; } }
			if (GetKey(olc::Key::S).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "S"; }
			else { if (GetKey(olc::Key::S).bHeld) { strAppo = "s"; } }
			if (GetKey(olc::Key::T).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "T"; }
			else { if (GetKey(olc::Key::T).bHeld) { strAppo = "t"; } }
			if (GetKey(olc::Key::U).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "U"; }
			else { if (GetKey(olc::Key::U).bHeld) { strAppo = "u"; } }
			if (GetKey(olc::Key::V).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "V"; }
			else { if (GetKey(olc::Key::V).bHeld) { strAppo = "v"; } }
			if (GetKey(olc::Key::W).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "W"; }
			else { if (GetKey(olc::Key::W).bHeld) { strAppo = "w"; } }
			if (GetKey(olc::Key::X).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "X"; }
			else { if (GetKey(olc::Key::X).bHeld) { strAppo = "x"; } }
			if (GetKey(olc::Key::Y).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "Y"; }
			else { if (GetKey(olc::Key::Y).bHeld) { strAppo = "y"; } }
			if (GetKey(olc::Key::Z).bHeld && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "Z"; }
			else { if (GetKey(olc::Key::Z).bHeld) { strAppo = "z"; } }

			environment.PrintOnScreen(environment.cursorCol,environment.cursorRow,strAppo,)

			if (GetKey(olc::Key::LEFT).bPressed) {
				strAppo = "LEFT";
				// sposta il cursore a sinistra
				if (environment.fTimeChar >= 0.06f) {
					if (environment.screenMemIndex > 0) environment.newScreenMemIndex -= 1;
					environment.fTimeChar = 0;
				}
			}

			if (GetKey(olc::Key::RIGHT).bPressed){
				strAppo = "RIGHT";
				// sposta il cursore a destra
				if (environment.fTimeChar >= 0.06f) {
					if (environment.screenMemIndex < (colMode80 ? 2399 : 1199)) environment.newScreenMemIndex += 1;
					environment.fTimeChar = 0;
				}
			}

			if (GetKey(olc::Key::UP).bPressed) {
				strAppo = "UP";
				if (environment.fTimeChar >= 0.06f) {
					if (environment.screenMemIndex > (colMode80 ? 79 : 39)) environment.newScreenMemIndex -= (colMode80 ? 80 : 40);
					environment.fTimeChar = 0;
				}
			}

			if (GetKey(olc::Key::DOWN).bPressed) {
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
	
	demo.colMode80 = true;

	if (demo.Construct((demo.colMode80 ? 840 : 420), 280, (demo.colMode80 ? 1 : 2), 2))
		demo.Start();

	return 0;
}
