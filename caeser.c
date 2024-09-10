#include <stdio.h>
#include <locale.h>
#include "caeser.h"
#include <wchar.h>
#include <stdlib.h>

int main()
{
    setlocale(LC_ALL, "");
    if (!setlocale(LC_ALL, "da_DK.utf8"))
    {
        wprintf(L"Locale not set\n");
        return 1;
    }


    wchar_t nordicAlphabet[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅabcdefghijklmnopqrstuvwxyzæøå";
    wchar_t text[100];
    int shiftAmount;

    wprintf(L"Enter text to encrypt: ");
    fgetws(text, 100, stdin);

    wprintf(L"Enter shift amount: ");
    wscanf(L"%d", &shiftAmount);

    // Remove newline character from input text
    size_t len = wcslen(text);
    if (len > 0 && text[len - 1] == L'\n')
    {
        text[len - 1] = L'\0';
    }

    wprintf(L"Original text: %ls\n", text);
    wchar_t* encryptedText = encrypt(text, shiftAmount, nordicAlphabet);
    if (encryptedText == NULL) {
        wprintf(L"Encryption failed\n");
        return 1;
    }
    wprintf(L"Encrypted text: %ls\n", encryptedText);

    return 0;
}
/*
int main()
{
    setlocale(LC_ALL, "");
    wchar_t nordicAlphabet[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅabcdefghijklmnopqrstuvwxyzæøå";
   


    printf("%d\n", letterToNumber('A', nordicAlphabet));
    printf("%d\n", letterToNumber('a', nordicAlphabet));
    printf("%d\n", letterToNumber('B', nordicAlphabet));
    wprintf(L"Æ:%d\n", letterToNumber(L'Æ', nordicAlphabet));
    wprintf(L"æ:%d\n", letterToNumber(L'æ', nordicAlphabet));
    wprintf(L"Ø:%d\n", letterToNumber(L'Ø', nordicAlphabet));
    wprintf(L"ø:%d\n", letterToNumber(L'ø', nordicAlphabet));
    wprintf(L"Å:%d\n", letterToNumber(L'Å', nordicAlphabet));
    wprintf(L"å:%d\n", letterToNumber(L'å', nordicAlphabet));
    
    wprintf(L"%c\n", numberToLetter(0, nordicAlphabet));
    wprintf(L"%c\n", numberToLetter(1, nordicAlphabet));
    wprintf(L"%c\n", numberToLetter(2, nordicAlphabet));
    wprintf(L"%c\n", numberToLetter(3, nordicAlphabet));
    wprintf(L"%c\n", numberToLetter(26, nordicAlphabet));
    wprintf(L"%c\n", numberToLetter(27, nordicAlphabet));
    wprintf(L"%c\n", numberToLetter(28, nordicAlphabet));

    printf("Expected 23:%d\n", shift(20, 3));
    printf("Expected 17:%d\n", shift(20, -3));
    printf("Expected 4:%d\n", shift(27, +6));
    printf("Expected 1:%d\n", shift(29, +1));

    wchar_t text[] = L"Hello World";
    encrypt(text, 3, nordicAlphabet);
    wprintf(L"%s\n", text);

    startMenu();
    return 0;
}
*/
int letterToNumber(wchar_t letter, wchar_t nordicAlphabet[])
{
    //Ignore spaces
    if (letter == L' ')
    {
        return -1;
    }
    for (int i = 0; i < 29; i++)
    {
        if (nordicAlphabet[i] == letter || nordicAlphabet[i+29] == letter)
        {
            return i;
        }
    }
    return -1;
}

wchar_t numberToLetter(int number, wchar_t nordicAlphabet[])
{
    if (number >= 0 && number < 61)
    {
        return nordicAlphabet[number];
    }
    return L'\0';
}

int shift(int number, int shift)
{
    //Co-pilot wanted a fancy way, but I did not understand it
    int shiftedValue = number + shift;
    if (shiftedValue < 0)
    {
        return 29 + shiftedValue;
    }
    else if (shiftedValue > 29)
    {
        return shiftedValue - 29;
    }
}

wchar_t * encrypt(wchar_t *text, int shiftAmount, wchar_t nordicAlphabet[])
{
    int size = wcslen(text);
    wchar_t* encryptedText = (wchar_t*)malloc((size + 1) * sizeof(wchar_t));

    if (encryptedText == NULL) {
        wprintf(L"Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        wchar_t* charPos = wcschr(nordicAlphabet, text[i]);
        if (charPos) {
            int pos = charPos - nordicAlphabet;
            int shiftedPos = shift(pos, shiftAmount);
            encryptedText[i] = numberToLetter(shiftedPos, nordicAlphabet);
        } else {
            encryptedText[i] = text[i];
        }
    }
    encryptedText[size] = L'\0';
    return encryptedText;
}

wchar_t * decrypt(wchar_t *text, int shiftAmount, wchar_t nordicAlphabet[])
{
    return encrypt(text, -shiftAmount, nordicAlphabet);
}