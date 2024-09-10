int letterToNumber(wchar_t letter, wchar_t nordicAlphabet[]);
wchar_t numberToLetter(int number, wchar_t nordicAlphabet[]);
int shift(int number, int shift);
wchar_t * encrypt(wchar_t *text, int shiftAmount, wchar_t nordicAlphabet[]);
wchar_t * decrypt(wchar_t *text, int shiftAmount, wchar_t nordicAlphabet[]);