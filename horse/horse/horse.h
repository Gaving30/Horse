#pragma once
#include <iostream>
#include <string>
using namespace std;

class horse
{

private:
    int id;									//backing field for ID
	char name[50];							//backing field for Name
	char mother[50];						//backing field for Mother
	char father[50];						//backing field for Father
	char owner[50];							//backing field for Owner
	char markings[256];						//backing field for notes
	char notes[256];						//backing field for notes
	
	char height[5];								//backing field for Height
	char age[5];								//backing field for age
	char win[5];								//backing field for Races won

	void setID();

public:

	horse(void);																		//constructor
	horse(int id);																		//overloaded constructor
	horse(int id, char* name, char* mother, char* father, char* height, char* age, char* win,
		char* owner, char* markings, char* notes);													//overloaded constructor

	


	~horse(void);							//destructor

	void setName(char* newName);			//set name
	char* getName();						//get name

	void setMother(char* newMother);		//set mother
	char* getMother();						//get mother

	void setFather(char* newFather);		//set father
	char* getFather();						//get father

	void setHeight(char* newHeight);		//set Height
	char* getHeight();						//get Height

	void setOwner(char* newOwner);			//set owner
	char* getOwner();						//get owner

	void setAge(char* newAge);				//set age
	char* getAge();							//get age

	void setWin(char* newWin);				//set win
	char* getWin();							//get win

	void setMarkings(char* newMarkings);	//set Markings
	char* getMarkings();					//get Markings

	void setNotes(char* newNotes);			//set notes
	char* getNotes();						//get notes

	int getID();							//get ID
};