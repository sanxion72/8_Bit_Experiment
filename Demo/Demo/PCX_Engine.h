#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>  
#include <cstdio>
#include <io.h>            // _filelength()
#include <windows.h>

class PCX_Engine {
protected:

    BITMAPINFO* psBmpInfo;
    BYTE* pabRawBitmap;

    typedef struct BitmapSize_typ {
        short cx;
        short cy;
    } sBitmapSize;

public:

    typedef struct pcx_header_typ {
        // Standard PCX header
        char   ID;              // Always 10
        char   Version;         // 0-Ver 2.5 Paintbrush
        // 1-Ver 2.8 with palette
        // 2-Ver 2.8 with default
        // 5-Ver 3.0 or sup.
        char   Encoding;        // Always 1 : RLE coding
        char   BitPerPixel;     // bit per pixel (8 in that case)
        short  X, Y;             // Top left coords
        short  width, height;    // Image width , height
        short  HRes;            // Number of pixels X
        short  VRes;            // Number of pixels Y
        char   EGA_map[16 * 3]; // EGA palette informations : IGNORE
        char   Reserved1;       // Reserved
        char   NumPlanes;       // Number of image planes
        short  BPL;             // Bytes for every horizontal line
        short  Pal_t;           // Ignore
        char   Filler[58];      // Filler to end of file

    } sPcx_header, * Pcx_header_ptr;

    typedef struct Color_typ {
        unsigned char R;	// RED
        unsigned char G;	// GREEN
        unsigned char B;	// BLUE
        unsigned char A;	// ALPHA
    } sColor, * Color_ptr;

    typedef struct pcx_picture_typ {
        sPcx_header header;
        sColor palette[256];
        BYTE* buffer;
    } sPcx_picture, * Pcx_picture_ptr;


    void PCX_load(LPCSTR filename, sPcx_picture* image)
    {   
        sBitmapSize BitmapSize;
        int iX;
        int iY;

        // Open the file and put its entire content in memory

        FILE* pFile = fopen(filename, "rb");

        const long clFileSize = _filelength(_fileno(pFile));

        BYTE* pabFileData = (BYTE*)new BYTE[clFileSize]; 
        
        fread(pabFileData, clFileSize, 1, pFile);
        fclose(pFile);

        // Get the header
        memcpy(&image->header, pabFileData, sizeof(image->header));

        // Each scan line MUST have a size that can be divided by a 'long' data type
        int iScanLineSize = image->header.NumPlanes * image->header.BPL;
        ldiv_t sDivResult = ldiv(iScanLineSize, sizeof(long));
        if (sDivResult.rem > 0)
            iScanLineSize = (iScanLineSize / sizeof(long) + 1) * sizeof(long);

        BitmapSize.cx = image->header.width - image->header.X + 1;
        BitmapSize.cy = image->header.height - image->header.Y + 1;

        const long clImageSize = iScanLineSize * BitmapSize.cy;

        // Prepare image buffer large enough to hold the image
        //pabRawBitmap = (BYTE*)new BYTE[clImageSize];
        image->buffer = (BYTE*)new BYTE[clImageSize]; 

        // Get the compressed image
        long lDataPos = 0;
        long lPos = 128;     // That's where the data begins

        for (iY = 0; iY < BitmapSize.cy; iY++)
        {
            // Decompress the scan line
            for (iX = 0; iX < image->header.BPL; )
            {
                UINT uiValue = pabFileData[lPos++];
                if (uiValue > 192) {  // Two high bits are set = Repeat
                    uiValue -= 192;                  // Repeat how many times?
                    BYTE Color = pabFileData[lPos++];  // What color?

                    if (iX <= BitmapSize.cx)
                    {  // Image data.  Place in the raw bitmap.
                        for (BYTE bRepeat = 0; bRepeat < uiValue; bRepeat++)
                        {
                            //pabRawBitmap[lDataPos++] = Color;
                            image->buffer[lDataPos++] = Color;
                            iX++;
                        }
                    }
                    else
                        iX += uiValue; // Outside the image.  Skip.
                }
                else
                {
                    if (iX <= BitmapSize.cx)
                        //pabRawBitmap[lDataPos++] = uiValue;
                        image->buffer[lDataPos++] = uiValue;
                    iX++;
                }
            }

            // Pad the rest with zeros
            if (iX < iScanLineSize)
            {
                for (; iX < iScanLineSize; iX++)
                {
                    //pabRawBitmap[lDataPos++] = 0;
                    image->buffer[lDataPos++] = 0;
                    
                }
            }
        }

        if (pabFileData[lPos++] == 12)          // Simple validation
            // Get the palette
            for (short Entry = 0; Entry < 256; Entry++)
            {
                image->palette[Entry].R = pabFileData[lPos++];
                image->palette[Entry].G = pabFileData[lPos++];
                image->palette[Entry].B = pabFileData[lPos++];
                image->palette[Entry].A = 255;
            }

        delete[] pabFileData;
    }
};
