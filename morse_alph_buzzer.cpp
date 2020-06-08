/**
 * This program is translating String to Morse code,
 * and send signals to gpio.
 * for me to buzzer and LED
 * @author Jakub Plinta
 * @version 1.00 2020/06/08
 */

#include <iostream>
#include <string>
#include <wiringPi.h>
#define LED 29  //setting gpio number of pin
#define BUZZER 22
using namespace std;

int main()
{
	if(wiringPiSetup() == -1) return 1;  //setting up wiringPi
	pinMode(LED, OUTPUT); //setting up pin
	pinMode(BUZZER, OUTPUT);
	
	//basic alphbet with numbers
	char basicAlph[] =
	{
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
		'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
		't', 'u', 'v', 'w', 'x', 'y', 'z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '
		
	};

	//morse alphabet with numbers
	string morseAlph[] =
	{
		".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
		".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...",
		"-", "..-", "...-", ".--", "-..-", "-.--", "--..",
		"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", " "
	};

	// initial variable
	int len, codelen = 0;
	int dot = 50;
	string text;
	//geting text to translate
	getline (cin, text);
	
	len = text.length();
	for (int k = 0; k < len; k++)
	{
		for(int j = 0; j < 37; j++)
		{
			if( text.at(k) == basicAlph[j] )
			{
				codelen = morseAlph[j].length();
				for (int i = 0; i < codelen; i++)
				{
					// translating '.' and '-' to gpio signal
					if(morseAlph[j].at(i) == '.')
					{
						digitalWrite(LED, HIGH); //On
						digitalWrite(BUZZER, HIGH); //On
						delay(dot); //dot 
						digitalWrite(LED, LOW); //Off
						digitalWrite(BUZZER, LOW); //off
					} else if(morseAlph[j].at(i) == '-')
					{
						digitalWrite(LED, HIGH); //On
						digitalWrite(BUZZER, HIGH); //On
						delay(dot*3); //line
						digitalWrite(LED, LOW); //Off
						digitalWrite(BUZZER, LOW); //Off
					}
					else delay(dot * 4);
					delay(dot*3);
				}
			}
			
			
		}
	}
	return 0;
}
