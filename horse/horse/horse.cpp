#include "horse.h"

horse::horse(void)
{
}

horse::horse(int id) {
    horse::id = id;
}

horse::horse(int id, char* name, char* mother, char* father, 
			 char* Height, char* age, char* win, char* owner, char* markings, char* notes) {
	horse::id		= id;
	//horse::age		= age;
	//horse::win		= win;
	//horse::height	= Height;

	setName(name);
	setMother(mother);
	setFather(father);
	setOwner(owner);
	setMarkings(markings);
	setNotes(notes);
	setHeight(Height);
	setAge(age);
	setWin(win);
}

horse::~horse(void)
{
}

void horse::setName(char* newName) {
	strcpy(horse::name, newName);
}

char* horse::getName() {
	return horse::name;
}

void horse::setMother(char* newMother) {
	strcpy(horse::mother, newMother);
}

char* horse::getMother() {
	return horse::mother;
}

void horse::setFather(char* newFather) {
	strcpy(horse::father, newFather);
}

char* horse::getFather() {
	return horse::father;
}

void horse::setHeight(char* newHeight) {
	strcpy(horse::height, newHeight);
}

char* horse::getHeight() {
	return horse::height;
}

void horse::setOwner(char* newOwner) {
	strcpy(horse::owner, newOwner);
}

char* horse::getOwner() {
	return horse::owner;
}

void horse::setAge(char* newAge) {
	strcpy(horse::age, newAge);
}

char* horse::getAge() {
	return horse::age;
}

void horse::setWin(char* newWin) {
	strcpy(horse::win, newWin);
}

char* horse::getWin() {
	return horse::win;
}

void horse::setMarkings(char newMarkings[]) {
	strcpy(markings, newMarkings);
}

char* horse::getMarkings() {
	return horse::markings;
}

void horse::setNotes(char newNotes[]) {
	strcpy(notes, newNotes);
}

char* horse::getNotes() {
	return horse::notes;
}

int horse::getID() {
	return horse::id;
}