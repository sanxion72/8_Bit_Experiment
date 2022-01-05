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
		sAppName = "CommodoreNGNX";
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
		DrawSprite((colMode80 ? 100 : 50), 100, environment.fontSprite);

		SetDrawTarget(nullptr);

		if (IsFocused()) {
			if (GetKey(olc::Key::A).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "A"; }
			else { if (GetKey(olc::Key::A).bPressed) { strAppo = "a"; } }
			if (GetKey(olc::Key::B).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "B"; }
			else { if (GetKey(olc::Key::B).bPressed) { strAppo = "b"; } }
			if (GetKey(olc::Key::C).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "C"; }
			else { if (GetKey(olc::Key::C).bPressed) { strAppo = "c"; } }
			if (GetKey(olc::Key::D).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "D"; }
			else { if (GetKey(olc::Key::D).bPressed) { strAppo = "d"; } }
			if (GetKey(olc::Key::E).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "E"; }
			else { if (GetKey(olc::Key::E).bPressed) { strAppo = "e"; } }
			if (GetKey(olc::Key::F).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "F"; }
			else { if (GetKey(olc::Key::F).bPressed) { strAppo = "f"; } }
			if (GetKey(olc::Key::G).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "G"; }
			else { if (GetKey(olc::Key::G).bPressed) { strAppo = "g"; } }
			if (GetKey(olc::Key::H).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "H"; }
			else { if (GetKey(olc::Key::H).bPressed) { strAppo = "h"; } }
			if (GetKey(olc::Key::I).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "I"; }
			else { if (GetKey(olc::Key::I).bPressed) { strAppo = "i"; } }
			if (GetKey(olc::Key::J).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "J"; }
			else { if (GetKey(olc::Key::J).bPressed) { strAppo = "j"; } }
			if (GetKey(olc::Key::K).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "K"; }
			else { if (GetKey(olc::Key::K).bPressed) { strAppo = "k"; } }
			if (GetKey(olc::Key::L).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "L"; }
			else { if (GetKey(olc::Key::L).bPressed) { strAppo = "l"; } }
			if (GetKey(olc::Key::M).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "M"; }
			else { if (GetKey(olc::Key::M).bPressed) { strAppo = "m"; } }
			if (GetKey(olc::Key::N).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "N"; }
			else { if (GetKey(olc::Key::N).bPressed) { strAppo = "n"; } }
			if (GetKey(olc::Key::O).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "O"; }
			else { if (GetKey(olc::Key::O).bPressed) { strAppo = "o"; } }
			if (GetKey(olc::Key::P).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "P"; }
			else { if (GetKey(olc::Key::P).bPressed) { strAppo = "p"; } }
			if (GetKey(olc::Key::Q).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "Q"; }
			else { if (GetKey(olc::Key::Q).bPressed) { strAppo = "q"; } }
			if (GetKey(olc::Key::R).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "R"; }
			else { if (GetKey(olc::Key::R).bPressed) { strAppo = "r"; } }
			if (GetKey(olc::Key::S).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "S"; }
			else { if (GetKey(olc::Key::S).bPressed) { strAppo = "s"; } }
			if (GetKey(olc::Key::T).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "T"; }
			else { if (GetKey(olc::Key::T).bPressed) { strAppo = "t"; } }
			if (GetKey(olc::Key::U).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "U"; }
			else { if (GetKey(olc::Key::U).bPressed) { strAppo = "u"; } }
			if (GetKey(olc::Key::V).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "V"; }
			else { if (GetKey(olc::Key::V).bPressed) { strAppo = "v"; } }
			if (GetKey(olc::Key::W).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "W"; }
			else { if (GetKey(olc::Key::W).bPressed) { strAppo = "w"; } }
			if (GetKey(olc::Key::X).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "X"; }
			else { if (GetKey(olc::Key::X).bPressed) { strAppo = "x"; } }
			if (GetKey(olc::Key::Y).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "Y"; }
			else { if (GetKey(olc::Key::Y).bPressed) { strAppo = "y"; } }
			if (GetKey(olc::Key::Z).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "Z"; }
			else { if (GetKey(olc::Key::Z).bPressed) { strAppo = "z"; } }
			
			if (GetKey(olc::Key::K1).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "!"; }
			else { if (GetKey(olc::Key::K1).bPressed) { strAppo = "1"; } }
			if (GetKey(olc::Key::K2).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "\""; }
			else { if (GetKey(olc::Key::K2).bPressed) { strAppo = "2"; } }
			if (GetKey(olc::Key::K3).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "£"; }
			else { if (GetKey(olc::Key::K3).bPressed) { strAppo = "3"; } }
			if (GetKey(olc::Key::K4).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "$"; }
			else { if (GetKey(olc::Key::K4).bPressed) { strAppo = "4"; } }
			if (GetKey(olc::Key::K5).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "%"; }
			else { if (GetKey(olc::Key::K5).bPressed) { strAppo = "5"; } }
			if (GetKey(olc::Key::K6).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "&"; }
			else { if (GetKey(olc::Key::K6).bPressed) { strAppo = "6"; } }
			if (GetKey(olc::Key::K7).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "/"; }
			else { if (GetKey(olc::Key::K7).bPressed) { strAppo = "7"; } }
			if (GetKey(olc::Key::K8).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "("; }
			else { if (GetKey(olc::Key::K8).bPressed) { strAppo = "8"; } }
			if (GetKey(olc::Key::K9).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = ")"; }
			else { if (GetKey(olc::Key::K9).bPressed) { strAppo = "9"; } }
			if (GetKey(olc::Key::K0).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = "="; }
			else { if (GetKey(olc::Key::K0).bPressed) { strAppo = "0"; } }
			if (GetKey(olc::Key::COMMA).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = ";"; }
			else { if (GetKey(olc::Key::COMMA).bPressed) { strAppo = ","; } }
			if (GetKey(olc::Key::PERIOD).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = ":"; }
			else { if (GetKey(olc::Key::PERIOD).bPressed) { strAppo = "."; } }
			if (GetKey(olc::Key::MINUS).bPressed && GetKey(olc::Key::SHIFT).bHeld) { strAppo = ">"; }
			else { if (GetKey(olc::Key::MINUS).bPressed) { strAppo = "<"; } }


			if (GetKey(olc::Key::SPACE).bPressed ) { 
				strAppo = " ";
				if (environment.fTimeChar >= 0.06f) {
					if (environment.screenMemIndex < (colMode80 ? 2399 : 1199)) environment.newScreenMemIndex += 1;
					environment.PrintOnScreen(environment.cursorCol, environment.cursorRow, " ");
					environment.fTimeChar = 0;
				}
			}
			
			if (GetKey(olc::Key::BACK).bPressed) { 
				// sposta il cursore a sinistra
				if (environment.fTimeChar >= 0.06f) {
					if (environment.screenMemIndex > 0) environment.newScreenMemIndex -= 1;
					environment.PrintOnScreen(environment.cursorCol-1, environment.cursorRow, " ");
					environment.fTimeChar = 0;
				}

			}


			if (!strAppo.empty()) {
				if (environment.fTimeChar >= 0.06f) {
					environment.PrintOnScreen(environment.cursorCol, environment.cursorRow, strAppo);
					environment.newScreenMemIndex += 1;
					environment.fTimeChar = 0;
				}
			}
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
	
	demo.colMode80 = false;

	if (demo.Construct((demo.colMode80 ? 840 : 420), 280, (demo.colMode80 ? 1 : 2), 2))
		demo.Start();

	return 0;
}
