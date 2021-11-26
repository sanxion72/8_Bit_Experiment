#pragma once
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include "olcPixelGameEngine.h"

class Environment
{
private:
	struct Color {
		unsigned char R;	// RED
		unsigned char G;	// GREEN
		unsigned char B;	// BLUE
		unsigned char A;	// ALPHA
	};

	struct Color Palette[256];
	Color ScreenBackcolor; Color ScreenBordercolor;			// colori iniziali bordo e sfondo

	int nLayerBackground = 0;
	int nLayerBorder = 0;

	struct CharAttrib {
		int		CharCode = 0;							// il numero del carattere all'interno della posizione nel chars fontsheet
		Color	CharForecolor;							// il colore del carattere 
		Color	CharBackcolor;							// il colore dello sfondo del carattere
		BOOL	Inverse = false;						// se il carattere � inverso (in negativo)
		unsigned char	Alpha_BackgroundColor = 255;	// canale alfa dello sfondo (255 pieno)
		unsigned char	Alpha_CharColor = 255;			// canale alfa del carattere (255 pieno)
	};

	struct CharCell {
		int xCoord = 0;	// coordinata X grafica corrispondente
		int yCoord = 0;	// coordinata Y grafica corrispondente
		int row = 0;	// coordinata row char mode
		int col = 0;	// coordinata col char mode
		CharAttrib chars;
	};

	//array di 2400 elementi che mappa in-memory lo schermo (se modo 40 colonne valgono i primi 1200 elementi altrimenti 2400 elementi;  Per 30 righe con carattere 8x8)
	CharCell VirtualScreenMap[2400];

	struct charCoord { int xCoord; int yCoord; };
	struct charCoord charMap[512];				// array contenente tutti i caratteri stampabili

	// Inizializza la palette
	void InitPalette() {				

		std::string RGB[256];

		// Commodore64 Palette
		RGB[0] = "000000ff";		RGB[1] = "FFFFFFff";		RGB[2] = "68372Bff";		RGB[3] = "70A4B2ff";
		RGB[4] = "6F3D86ff";		RGB[5] = "588D43ff";		RGB[6] = "352879ff";		RGB[7] = "B8C76Fff";
		RGB[8] = "6F4F25ff";		RGB[9] = "433900ff";		RGB[10] = "9A6759ff";		RGB[11] = "444444ff";
		RGB[12] = "6C6C6Cff";		RGB[13] = "9AD284ff";		RGB[14] = "6C5EB5ff";		RGB[15] = "959595ff";

		// Gray Scale Palette
		RGB[16] = "0f0f0fff";		RGB[17] = "1e1e1eff";		RGB[18] = "2d2d2dff";		RGB[19] = "3c3c3cff";
		RGB[20] = "4b4b4bff";		RGB[21] = "5a5a5aff";		RGB[22] = "696969ff";		RGB[23] = "787878ff";
		RGB[24] = "878787ff";		RGB[25] = "969696ff";		RGB[26] = "a5a5a5ff";		RGB[27] = "b4b4b4ff";
		RGB[28] = "c3c3c3ff";		RGB[29] = "d2d2d2ff";		RGB[30] = "e1e1e1ff";		RGB[31] = "f0f0f0ff";

		RGB[32] = "020101FF";		RGB[33] = "040303FF";		RGB[34] = "060404FF";		RGB[35] = "080606FF";
		RGB[36] = "0A0808FF";		RGB[37] = "0C0909FF";		RGB[38] = "0F0B0BFF";		RGB[39] = "020101FF";
		RGB[40] = "040202FF";		RGB[41] = "060303FF";		RGB[42] = "080404FF";		RGB[43] = "0A0505FF";
		RGB[44] = "0C0606FF";		RGB[45] = "0F0707FF";		RGB[46] = "020000FF";		RGB[47] = "040101FF";
		RGB[48] = "060101FF";		RGB[49] = "080202FF";
		RGB[50] = "0A0202FF";		RGB[51] = "0C0303FF";		RGB[52] = "0F0303FF";		RGB[53] = "020000FF";
		RGB[54] = "040000FF";		RGB[55] = "060000FF";		RGB[56] = "080000FF";		RGB[57] = "0A0000FF";
		RGB[58] = "0C0000FF";		RGB[59] = "0F0000FF";
		RGB[60] = "020201FF";		RGB[61] = "040403FF";		RGB[62] = "060604FF";		RGB[63] = "080806FF";
		RGB[64] = "0A0A08FF";		RGB[65] = "0C0C09FF";		RGB[66] = "0F0E0BFF";		RGB[67] = "020101FF";
		RGB[68] = "040302FF";		RGB[69] = "060503FF";
		RGB[70] = "080704FF";		RGB[71] = "0A0905FF";		RGB[72] = "0C0B06FF";		RGB[73] = "0F0E07FF";
		RGB[74] = "020100FF";		RGB[75] = "040301FF";		RGB[76] = "060501FF";		RGB[77] = "080602FF";
		RGB[78] = "0A0802FF";		RGB[79] = "0C0A03FF";
		RGB[80] = "0F0C03FF";		RGB[81] = "020100FF";		RGB[82] = "040300FF";		RGB[83] = "060400FF";
		RGB[84] = "080600FF";		RGB[85] = "0A0800FF";		RGB[86] = "0C0900FF";		RGB[87] = "0F0B00FF";
		RGB[88] = "010201FF";		RGB[89] = "030403FF";
		RGB[90] = "050604FF";		RGB[91] = "070806FF";		RGB[92] = "090A08FF";		RGB[93] = "0B0C09FF";
		RGB[94] = "0E0F0BFF";		RGB[95] = "010201FF";		RGB[96] = "030402FF";		RGB[97] = "040603FF";
		RGB[98] = "060804FF";		RGB[99] = "080A05FF";
		RGB[100] = "090C06FF";		RGB[101] = "0B0F07FF";		RGB[102] = "010200FF";		RGB[103] = "020401FF";
		RGB[104] = "040601FF";		RGB[105] = "050802FF";		RGB[106] = "060A02FF";		RGB[107] = "080C03FF";
		RGB[108] = "090F03FF";		RGB[109] = "010200FF";
		RGB[110] = "020400FF";		RGB[111] = "030600FF";		RGB[112] = "040800FF";		RGB[113] = "050A00FF";
		RGB[114] = "060C00FF";		RGB[115] = "070F00FF";		RGB[116] = "010201FF";		RGB[117] = "030403FF";
		RGB[118] = "040605FF";		RGB[119] = "060806FF";
		RGB[120] = "080A08FF";		RGB[121] = "090C0AFF";		RGB[122] = "0B0F0CFF";		RGB[123] = "010201FF";
		RGB[124] = "020402FF";		RGB[125] = "030604FF";		RGB[126] = "040805FF";		RGB[127] = "050A06FF";
		RGB[128] = "060C08FF";		RGB[129] = "070F09FF";
		RGB[130] = "000200FF";		RGB[131] = "010401FF";		RGB[132] = "010602FF";		RGB[133] = "020803FF";
		RGB[134] = "020A04FF";		RGB[135] = "030C05FF";		RGB[136] = "030F06FF";		RGB[137] = "000200FF";
		RGB[138] = "000401FF";		RGB[139] = "000601FF";
		RGB[140] = "000802FF";		RGB[141] = "000A02FF";		RGB[142] = "000C03FF";		RGB[143] = "000F03FF";
		RGB[144] = "010202FF";		RGB[145] = "030404FF";		RGB[146] = "040606FF";		RGB[147] = "060808FF";
		RGB[148] = "080A0AFF";		RGB[149] = "090C0CFF";
		RGB[150] = "0B0F0FFF";		RGB[151] = "010202FF";		RGB[152] = "020404FF";		RGB[153] = "030606FF";
		RGB[154] = "040808FF";		RGB[155] = "050A0AFF";		RGB[156] = "060C0CFF";		RGB[157] = "070F0FFF";
		RGB[158] = "000202FF";		RGB[159] = "010404FF";
		RGB[160] = "010606FF";		RGB[161] = "020808FF";		RGB[162] = "020A0AFF";		RGB[163] = "030C0CFF";
		RGB[164] = "030F0FFF";		RGB[165] = "000202FF";		RGB[166] = "000404FF";		RGB[167] = "000606FF";
		RGB[168] = "000808FF";		RGB[169] = "000A0AFF";
		RGB[170] = "000C0CFF";		RGB[171] = "000F0FFF";		RGB[172] = "010102FF";		RGB[173] = "030304FF";
		RGB[174] = "040506FF";		RGB[175] = "060608FF";		RGB[176] = "08080AFF";		RGB[177] = "090A0CFF";
		RGB[178] = "0B0C0FFF";		RGB[179] = "010102FF";
		RGB[180] = "020204FF";		RGB[181] = "030406FF";		RGB[182] = "040508FF";		RGB[183] = "05060AFF";
		RGB[184] = "06080CFF";		RGB[185] = "07090FFF";		RGB[186] = "000002FF";		RGB[187] = "010104FF";
		RGB[188] = "010206FF";		RGB[189] = "020308FF";
		RGB[190] = "02040AFF";		RGB[191] = "03050CFF";		RGB[192] = "03060FFF";		RGB[193] = "000002FF";
		RGB[194] = "000104FF";		RGB[195] = "000106FF";		RGB[196] = "000208FF";		RGB[197] = "00020AFF";
		RGB[198] = "00030CFF";		RGB[199] = "00030FFF";
		RGB[200] = "010102FF";		RGB[201] = "030304FF";		RGB[202] = "050406FF";		RGB[203] = "070608FF";
		RGB[204] = "09080AFF";		RGB[205] = "0B090CFF";		RGB[206] = "0E0B0FFF";		RGB[207] = "010102FF";
		RGB[208] = "030204FF";		RGB[209] = "040306FF";
		RGB[210] = "060408FF";		RGB[211] = "08050AFF";		RGB[212] = "09060CFF";		RGB[213] = "0B070FFF";
		RGB[214] = "010002FF";		RGB[215] = "020104FF";		RGB[216] = "040106FF";		RGB[217] = "050208FF";
		RGB[218] = "06020AFF";		RGB[219] = "08030CFF";
		RGB[220] = "09030FFF";		RGB[221] = "010002FF";		RGB[222] = "020004FF";		RGB[223] = "030006FF";
		RGB[224] = "040008FF";		RGB[225] = "05000AFF";		RGB[226] = "06000CFF";		RGB[227] = "07000FFF";
		RGB[228] = "020102FF";		RGB[229] = "040304FF";
		RGB[230] = "060406FF";		RGB[231] = "080608FF";		RGB[232] = "0A080AFF";		RGB[233] = "0C090CFF";
		RGB[234] = "0F0B0EFF";		RGB[235] = "020101FF";		RGB[236] = "040203FF";		RGB[237] = "060305FF";
		RGB[238] = "080407FF";		RGB[239] = "0A0509FF";
		RGB[240] = "0C060BFF";		RGB[241] = "0F070EFF";		RGB[242] = "020001FF";		RGB[243] = "040103FF";
		RGB[244] = "060105FF";		RGB[245] = "080206FF";		RGB[246] = "0A0208FF";		RGB[247] = "0C030AFF";
		RGB[248] = "0F030CFF";		RGB[249] = "020001FF";
		RGB[250] = "040003FF";		RGB[251] = "060004FF";		RGB[252] = "080006FF";		RGB[253] = "0A0008FF";
		RGB[254] = "0C0009FF";		RGB[255] = "0F000BFF";

		std::stringstream str;
		std::string s1;
		int value;

		// carica i primi 32 colori - commodore64 color set + 16 scale di grigio
		for (int pColor = 0; pColor <= 31; pColor++) {

			str.clear();
			s1 = RGB[pColor].substr(0, 2);
			str << s1; str >> std::hex >> value;
			Palette[pColor].R = value;

			str.clear();
			s1 = RGB[pColor].substr(2, 2);
			str << s1; str >> std::hex >> value;
			Palette[pColor].G = value;

			str.clear();
			s1 = RGB[pColor].substr(4, 2);
			str << s1; str >> std::hex >> value;
			Palette[pColor].B = value;

			str.clear();
			s1 = RGB[pColor].substr(6, 2);
			str << s1; str >> std::hex >> value;
			Palette[pColor].A = value;

		}

		// carica i rimenenti colori
		for (int pColor = 32; pColor <= 255; pColor++) {

			str.clear();
			s1 = RGB[pColor].substr(0, 2);
			str << s1; str >> std::hex >> value;
			Palette[pColor].R = value * 17;

			str.clear();
			s1 = RGB[pColor].substr(2, 2);
			str << s1; str >> std::hex >> value;
			Palette[pColor].G = value * 17;

			str.clear();
			s1 = RGB[pColor].substr(4, 2);
			str << s1; str >> std::hex >> value;
			Palette[pColor].B = value * 17;

			str.clear();
			s1 = RGB[pColor].substr(6, 2);
			str << s1; str >> std::hex >> value;
			Palette[pColor].A = value;

		}

	}

	void LoadCharacterSet(std::string charFileName, BOOL bSkip = true) {

		std::ifstream input(charFileName, std::ios::binary);

		// copies all data into buffer
		std::vector<unsigned char> data(std::istreambuf_iterator<char>(input), {});

		fontSprite = new olc::Sprite(256, 128);

		int px = 0, py = 0, offset_x = 0, offset_y = 0; int k = 0; int Count = 0;

		for (unsigned int b = (bSkip ? 2 : 0); b < data.size(); b += 8) {

			uint32_t sym1 = (uint32_t)data[b + 0];
			uint32_t sym2 = (uint32_t)data[b + 1];
			uint32_t sym3 = (uint32_t)data[b + 2];
			uint32_t sym4 = (uint32_t)data[b + 3];

			uint32_t nHalfChar_1 = sym1 << 24 | sym2 << 16 | sym3 << 8 | sym4;

			uint32_t sym5 = (uint32_t)data[b + 4];
			uint32_t sym6 = (uint32_t)data[b + 5];
			uint32_t sym7 = (uint32_t)data[b + 6];
			uint32_t sym8 = (uint32_t)data[b + 7];

			uint32_t nHalfChar_2 = sym5 << 24 | sym6 << 16 | sym7 << 8 | sym8;

			charMap[Count].xCoord = px + offset_x;
			charMap[Count].yCoord = py + offset_y;

			for (int i = 31; i >= 0; i--) {
				k = nHalfChar_1 & (1 << i) ? 255 : 0;
				fontSprite->SetPixel(px + offset_x, py + offset_y, olc::Pixel(k, k, k, k));

				k = nHalfChar_2 & (1 << i) ? 255 : 0;
				fontSprite->SetPixel(px + offset_x, py + offset_y + 4, olc::Pixel(k, k, k, k));

				if (++px == 8) { px = 0;  py++; }
			}

			offset_x += 8;
			py = 0;

			if (offset_x == 256) { offset_x = 0; px = 0; offset_y += 8; }

			Count++;
		}

	}

	// inizializza la virtualscreen map con il carattere ' ' spazio
	void InitVirtualScreenMap()
	{
		int offsetColonna = 0; int offsetRiga = 0; int index = 0;

		for (int riga = 0; riga <= 29; riga++)
		{
			for (int colonna = 0; colonna <= (ScreenMode ? 79 : 39); colonna++)
			{
				VirtualScreenMap[index].row = riga;
				VirtualScreenMap[index].col = colonna;
				VirtualScreenMap[index].xCoord = (ScreenMode ? 100 : 50) + offsetColonna;
				VirtualScreenMap[index].yCoord = 20 + offsetRiga;
				VirtualScreenMap[index].chars.CharCode = 32; // il carattere ' ' spazio
				VirtualScreenMap[index].chars.CharForecolor = ScreenBackcolor;
				VirtualScreenMap[index].chars.CharBackcolor = ScreenBordercolor;

				offsetColonna += 8;
				index++;
			}
			offsetColonna = 0;
			offsetRiga += 8;
		}
	}

	void SetCharOnScreen(CharCell CharAttrib, olc::PixelGameEngine* pge) {

		int32_t x;
		int32_t y;
		int32_t sx = 0;
		int32_t sy = 0;
		int ox = 0;
		int oy = 0;

		BOOL inverse;

		BYTE colIndex = 0;

		x = CharAttrib.xCoord;
		y = CharAttrib.yCoord;

		inverse = CharAttrib.chars.Inverse;

		olc::Pixel foregroundColor;	olc::Pixel backgroundColor;

		foregroundColor.r = CharAttrib.chars.CharForecolor.R;
		foregroundColor.g = CharAttrib.chars.CharForecolor.G;
		foregroundColor.b = CharAttrib.chars.CharForecolor.B;
		foregroundColor.a = CharAttrib.chars.Alpha_CharColor;

		backgroundColor.r = CharAttrib.chars.CharBackcolor.R;
		backgroundColor.g = CharAttrib.chars.CharBackcolor.G;
		backgroundColor.b = CharAttrib.chars.CharBackcolor.B;
		backgroundColor.a = CharAttrib.chars.Alpha_BackgroundColor;

		//olc::Pixel::Mode m = olc::Pixel::NORMAL;
		
		if (CharAttrib.chars.CharCode == '\n') {
			sx = 0; sy += 8;
		}
		else {

			// da @,A,B,C ... a ... ]
			if (CharAttrib.chars.CharCode >= 64 && CharAttrib.chars.CharCode <= 93) {
				ox = charMap[CharAttrib.chars.CharCode - 64 + (inverse ? 128 : 0)].xCoord;
				oy = charMap[CharAttrib.chars.CharCode - 64 + (inverse ? 128 : 0)].yCoord;
			}

			// da {SPACE} a ?
			if (CharAttrib.chars.CharCode >= 32 && CharAttrib.chars.CharCode <= 63) {
				ox = charMap[CharAttrib.chars.CharCode + (inverse ? 128 : 0)].xCoord;
				oy = charMap[CharAttrib.chars.CharCode + (inverse ? 128 : 0)].yCoord;
			}

			// da a,b,c,d ... a ... z
			if (CharAttrib.chars.CharCode >= 97 && CharAttrib.chars.CharCode <= 122) {
				ox = charMap[CharAttrib.chars.CharCode + 160 + (inverse ? 128 : 0)].xCoord;
				oy = charMap[CharAttrib.chars.CharCode + 160 + (inverse ? 128 : 0)].yCoord;
			}

			if (CharAttrib.chars.CharCode == 219) {
				ox = charMap[CharAttrib.chars.CharCode + 59].xCoord;
				oy = charMap[CharAttrib.chars.CharCode + 59].yCoord;
			}

			for (uint32_t i = 0; i < 8; i++)
				for (uint32_t j = 0; j < 8; j++)
					if (fontSprite->GetPixel(i + ox, j + oy).r > 0) {
						pge->Draw(x + sx + i, y + sy + j, foregroundColor);
					}
					else {
						pge->Draw(x + sx + i, y + sy + j, backgroundColor);
					}

			sx += 8;
		}

		pge->SetPixelMode(olc::Pixel::NORMAL);

	}

	void Init() {
		InitPalette();

		ScreenBackcolor = Palette[14];
		ScreenBordercolor = Palette[6];
		
		LoadCharacterSet(".\\charset.bin", false);

	}

	void Visualizza_Palette()
	{
		// visualizza la palette su schermo come carattere spazio inverse con il colore uguale foregroud e background
		for (int nColor = 0; nColor <= 255; nColor++) {
			VirtualScreenMap[nColor].chars.CharCode = 32; // il carattere ' ' spazio
			VirtualScreenMap[nColor].chars.CharForecolor = Palette[nColor];
			VirtualScreenMap[nColor].chars.CharBackcolor = Palette[nColor];
		}
	}

public:
	olc::Sprite* fontSprite = nullptr;

	Environment() {
		Init();
	}

	BOOL ScreenMode;

	void InitScreen(olc::PixelGameEngine* pge) {
		
		InitVirtualScreenMap();

		pge->Clear(olc::Pixel::MASK);

		nLayerBorder = pge->CreateLayer();
		pge->SetDrawTarget(nLayerBorder);

		pge->FillRect(0, 0, (ScreenMode ? 840 : 420), 280, olc::Pixel(ScreenBackcolor.R, ScreenBackcolor.G, ScreenBackcolor.B));
		pge->FillRect((ScreenMode ? 100 : 50), 20, (ScreenMode ? 640 : 320), 240, olc::Pixel::MASK);

		pge->EnableLayer(nLayerBorder, true);
		pge->SetDrawTarget(nullptr);

		nLayerBackground = pge->CreateLayer();
		pge->SetDrawTarget(nLayerBackground);
		pge->FillRect((ScreenMode ? 100 : 50), 20, (ScreenMode ? 640 : 320), 240, olc::Pixel(ScreenBordercolor.R, ScreenBordercolor.G, ScreenBordercolor.B));

		Visualizza_Palette();

		pge->EnableLayer(nLayerBackground, true);
		pge->SetDrawTarget(nullptr);

		pge->SetPixelMode(olc::Pixel::NORMAL);

	}

	void SyncVirtualScreenMap(olc::PixelGameEngine* pge) {

		for (int t = 0; t <= (ScreenMode ? 2399 : 1199); t++) {
			SetCharOnScreen(VirtualScreenMap[t], pge);
		}

	}

};
