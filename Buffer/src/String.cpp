
#include <iostream>
using namespace std;

#include "String.h"

/**
	"leeres" String erstellen (mit Terminatorsymbol erstellen)
*/
String::String() { 
    size = 0;
    str = new char[1];
    str[0] = '\0';
}

/**
	str initialisieren für size = 1.
*/
String::String(char c) {
    size = 1;
    str = new char[2];
    str[0] = c;
    str[1] = '\0';
}

/**
	str erstellen für den Fall dass es mehr als ein Zeichen ist.
*/
String::String(const char *s) {
  int res = 0;
  while(s[res] != '\0'){ //Zeichen zählen.
	  res++;
  }
  size = res; 
  str = new char[size+1];// Größe des Strings erstellen +1 wegen terminator symbol
  for(int i = 0;i<=res;i++){ // in String kopieren
	  str[i]=s[i];
  }

}

/**
	String in einen neuen String kopieren.
*/
String::String(const String& s) {
	size = s.size; // größe in neue Stringklasse kopieren.
	str = new char[size+1]; // neuen String erstellen mit größe +1 wegen Terminatorsymbole
	for(int i = 0;i<=size;i++){ // alten String in neuen rüberkopieren
		str[i]=s.str[i];
	}
}

String::~String() { delete[] str; }

/**
	Index aus einem String zurückgeben.
*/
char& String::operator[](int index) {
	if(index >=0 && index<size){
		return str[index];
	}
	else{
		return str[size];
	}
	
}

String& String::operator=(String& s) {
  /*int res = 0;
  while(s[res] != '\0'){ //Zeichen zählen von s
	  res++;
  }
  size = res;// größe verändern*/
  size = s.size;
  delete[] str;
  str = new char[size+1];// String neu erstellen mit der gewünschten größe
  for(int i = 0;i<size;i++){//zeichen von s nach str kopieren
	  str[i] = s[i];
  }
  str[size] = '\0'; // terminatorsymbol dazu fügen
  return *this;
}

String& String::operator+=(String& s) {
  int nVonS = s.size;
  int nVonStr = size;
  /*while(s[nVonS] != '\0'){ //Zeichen zählen von s
	  nVonS++;
  }
  while(str[nVonStr] != '\0'){ //Zeichen zählen von str
	  nVonStr++;
  }*/
  char* temp = new char[(nVonStr+nVonS+1)]; // neues Array mit gewünschter grösse erstellen. welches als zwischenspeicher dient
  size = (nVonS+nVonStr); // größe ändern

  for(int i = 0;i<nVonStr;i++) // str in temp kopieren
  {
	  temp[i] = str[i];
  }

  for(int j = nVonStr;j<nVonS+nVonStr;j++){ // s danach in temp kopieren
	  temp[j] = s[j-nVonStr];
  }

  temp[nVonStr+nVonS] = '\0'; // terminatorsymbol dazu fügen

  delete[] str;// altes str löschen damit der Speicher nicht unnötig verbraucht wird

  str = temp ; // temp übergeben

  return *this;
}


