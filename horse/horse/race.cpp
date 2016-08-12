#include "race.h"

race::race(void)
{
}

race::race(int id) {
    race::id = id;
}

race::race(int id, char* Name, char* Date, char* Length, char* RaceClass, char* HorsesBeaten, char* Position) {
	race::id = id;

	setName(Name);
	setDate(Date);
	setLength(Length);
	setRaceClass(RaceClass);
	setHorsesBeaten(HorsesBeaten);
	setPosition(Position);
}

race::~race(void)
{
}

void race::setName(char* newName) {
	strcpy(race::Name, newName);
}

char* race::getName() {
	return race::Name;
}

void race::setDate(char* newDate) {
	strcpy(race::Date, newDate);
}

char* race::getDate() {
	return race::Date;
}

void race::setLength(char* newLength) {
	strcpy(race::Length, newLength);
}

char* race::getLength() {
	return race::Length;
}

void race::setRaceClass(char* newRaceClass) {
	strcpy(race::RaceClass, newRaceClass);
}

char* race::getRaceClass() {
	return race::RaceClass;
}

void race::setHorsesBeaten(char* newHorsesBeaten) {
	strcpy(race::HorsesBeaten, newHorsesBeaten);
}

char* race::getHorsesBeaten() {
	return race::HorsesBeaten;
}

void race::setPosition(char* newPosition) {
	strcpy(race::Position, newPosition);
}

char* race::getPosition() {
	return race::Position;
}

int race::getID() {
	return race::id;
}