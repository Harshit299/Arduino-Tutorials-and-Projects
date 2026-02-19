/* Program to display letter, digit and emoji */

#include <LedControl.h>

// DIN, CLK, CS, number of led matrix
LedControl lc = LedControl(7, 5, 6, 1);

byte letterT[8] = {
  B11111111,
  B11111111,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000
};

byte smiley[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

byte digit6[8] = {
  B01111111,
  B10000000,
  B10000000,
  B10000000,
  B11111110,
  B10000001,
  B10000001,
  B01111110
};

void setup() {
  lc.shutdown(0, false);      // Wake up MAX7219
  lc.setIntensity(0, 8);      // Brightness (0–15)
  lc.clearDisplay(0);         // Clear display
}

void loop() {
  for (int row = 0; row < 8; row++) {
    // lc.setRow(0, row, letterT[row]);
    lc.setRow(0, row, digit6[row]);
    lc.setRow(0, row, smiley[row]);
  }
}


/* Program to display scrolling text */

// #include <LedControl.h>

// LedControl lc = LedControl(7, 5, 6, 1);

// // 5x7 font - each byte is one column, LSB = top row
// byte font[][5] = {
//   {0x00,0x00,0x00,0x00,0x00}, // Space (0)
//   {0x01,0x01,0x7F,0x01,0x01}, // T (1)
//   {0x7F,0x08,0x08,0x08,0x70}, // h (2)
//   {0x38,0x54,0x54,0x54,0x18}, // e (3)
//   {0x3E,0x41,0x41,0x41,0x3E}, // O (4)
//   {0x7F,0x08,0x08,0x08,0x7F}, // H (5)
//   {0x7F,0x02,0x04,0x02,0x7F}, // M (6)
//   {0x7F,0x40,0x40,0x40,0x40}, // L (7)
//   {0x20,0x54,0x54,0x54,0x78}, // a (8)
//   {0x7F,0x48,0x48,0x48,0x30}, // b (9)
// };

// int getCharIndex(char c) {
//   switch(c) {
//     case ' ': return 0;
//     case 'T': return 1;
//     case 'h': return 2;
//     case 'e': return 3;
//     case 'O': return 4;
//     case 'H': return 5;
//     case 'M': return 6;
//     case 'L': return 7;
//     case 'a': return 8;
//     case 'b': return 9;
//     default:  return 0;
//   }
// }

// String message = "The OHM Lab ";  // trailing space clears display at end

// byte reverseBits(byte b) {
//   byte result = 0;
//   for (int i = 0; i < 8; i++) {
//     result = (result << 1) | (b & 1);
//     b >>= 1;
//   }
//   return result;
// }

// // Get the byte for a specific column of a character (col 5 = blank spacer)
// byte getColumn(char c, int col) {
//   if (col >= 5) return 0x00;
//   return reverseBits(font[getCharIndex(c)][col]);
// }

// void setup() {
//   lc.shutdown(0, false);
//   lc.setIntensity(0, 8);
//   lc.clearDisplay(0);
// }

// void loop() {
//   scrollText(message);
// }

// void scrollText(String text) {
//   int totalCols = text.length() * 6;  // each char = 5 cols + 1 space

//   for (int offset = 0; offset < totalCols; offset++) {
//     // For each of the 8 display columns, finding which column to show
//     for (int dispCol = 0; dispCol < 8; dispCol++) {
//       int srcCol = offset + dispCol;  // which column of the full message

//       byte colData = 0x00;
//       if (srcCol < totalCols) {
//         int charIndex  = srcCol / 6;   // which character
//         int charCol    = srcCol % 6;   // which column within that character
//         if (charIndex < text.length()) {
//           colData = getColumn(text[charIndex], charCol);
//         }
//       }

//       lc.setColumn(0, dispCol, colData);
//     }

//     delay(80);  // scroll speed — lower = faster
//   }
// }