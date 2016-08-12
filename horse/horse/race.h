#pragma once
#include <iostream>
#include <string>
using namespace std;

class race
{

private:
    int id;									//backing field for id
	char Name[50];							//backing field for name
	char Date[50];							//backing field for date
	char Length[50];						//backing field for length
	char RaceClass[50];						//backing field for raceclass
	char HorsesBeaten[256];					//backing field for horsesbeaten
	char Position[256];						//backing field for position

	void setID();

public:
	race(void);								//constructor
	race(int id);							//overloaded constructor
	race(int id, char* name, char* Date, char* Length, char* RaceClass, char* HorsesBeaten, char* Position);													//overloaded constructor

	~race(void);							//destructor

	void setName(char* newName);			//set name
	char* getName();						//get name

	void setDate(char* newDate);			//set Date
	char* getDate();						//get Date

	void setLength(char* newLength);		//set Length
	char* getLength();						//get Length

	void setRaceClass(char* newRaceClass);	//set RaceClass
	char* getRaceClass();						//get RaceClass

	void setHorsesBeaten(char* newHorsesBeaten);	//set owner
	char* getHorsesBeaten();					//get owner

	void setPosition(char* newPosition);	//set Position
	char* getPosition();					//get Position

	int getID();							//get ID
};