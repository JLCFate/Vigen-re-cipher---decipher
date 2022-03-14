#include <iostream>
#include <string>

#define LETTERS 26  //definiowanie wartości
#define ASCII_A 65
#define ASCII_Z 90

using namespace std;

int searchMainArr(char letter, int row, char** mainArr) //funkcja przeszukująca główną tablicę
{
	for (int i = 0; i < LETTERS; i++)
	{
		if (mainArr[row][i] == letter)
			return i;							
	}
}

void generateAlphabet(char arr[LETTERS])  //generowanie alfabetu
{
	for (int i = 0; i < LETTERS; i++)
	{
		arr[i] = ASCII_A + i;
	}
}

void generateArray(char** arr, char alphabet[LETTERS])  // tworzenie gównej tablicy
{
	int letterShift = 0;
	for (int i = 0; i < LETTERS; i++)
	{
		for (int j = 0; j < LETTERS; j++)
		{
			arr[i][j] = alphabet[(j + letterShift) % LETTERS];
		}
		letterShift++;
	}
}

string generateCipher(string cipherText, string cipherKey, char** mainArr) //szyfrowanie tekstu
{
	string ciphered;

	int delay = 0;

	for (int i = 0; i < cipherText.size(); i++)
	{
		if (cipherText[i] == 32)
		{
			ciphered += 32;

			delay++;
		}
		else
		{
			ciphered += mainArr[cipherKey[(i - delay) % cipherKey.size()] - ASCII_A][cipherText[i] - ASCII_A];
		}

	}
	return ciphered;
}

string decipher(string ciphered, string cipherKey, char** mainArr, char* alphabet) // deszyfrowanie tekstu 
{
	string deciphered;
	int delay = 0;
	for (int i = 0; i < ciphered.size(); i++)
	{
		if (ciphered[i] == 32)
		{
			deciphered += 32;

			delay++;
		}
		else
		{
			char letterToSearch = ciphered[i];
			int rowToSearch = cipherKey[(i - delay) % cipherKey.size()] - ASCII_A;
			int alphabetInd = searchMainArr(letterToSearch, rowToSearch, mainArr);
			deciphered += alphabet[alphabetInd];
		}

	}
	return deciphered;
}

int main()
{
	char alphabet[LETTERS];
	string cipherText;
	string cipherKey;
	string ciphered;
	string deciphered;

	//Alokacja pamięci na główną tablicę
	char** mainArr = new char* [LETTERS];
	for (int i = 0; i < LETTERS; i++)
	{
		mainArr[i] = new char[LETTERS];
	}

	//Tworzenie głównej tablicy i jej populacja
	generateAlphabet(alphabet);
	generateArray(mainArr, alphabet);

	/*for (int i = 0; i < LETTERS; i++)    //wyświetlanie gównej tablicy (w razie potrzeby sprawdzenia)
	{
		for (int j = 0; j < LETTERS; j++)
		{
			cout << mainArr[i][j];
		}
		cout << endl;
	}*/

	cout << "Szyfrowany tekst: ";
	getline(cin, cipherText);
	cout << endl;
	cout << "Klucz: ";
	cin >> cipherKey;
	cout << endl;
	cout << "Szyfrogram:";
	ciphered = generateCipher(cipherText, cipherKey, mainArr);
	cout << ciphered << endl;

	cout << "Klucz: ";
	cout << cipherKey << endl;
	cout << "Szyfrogram: ";
	cout << ciphered << endl;
	cout << "Tekst jawny: ";
	deciphered = decipher(ciphered, cipherKey, mainArr, alphabet);
	cout << deciphered;





	//Dealokacja pamięci po głównej tablicy
	for (int i = 0; i < LETTERS; i++) {
		delete[] mainArr[i];
	}
	delete[] mainArr;

	return 0;
}