//GAVIN HORSE PROJECT
//Last Updated: 27.08.2013
#include <iostream>
#include "horse.h"		//custom "horse" header
#include "race.h"		//custom "race" header
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
#include <time.h>
#include <sstream>
#include <iomanip>
#include "tinyxml.h"
#include <windows.h>	//for resizings windows
using namespace std;

const int widtha = 13;	//for string(name, mother, father etc)) in horse details
const int widthb = 12;	//for int's(age, height) in horse details
const int widthc = 12;	//for string(more than one word(markings, notes) in horse details
string const filepath = "horses.dat";
float const CURRENT_VERSION_NUMBER = 1.27f;
vector<horse> horses;
void MainMenu();

void ResizeWindowLarge(){
//Used for resizing console window for the results of the .xml and .dat searches
	system("mode 160,25");					//mode (columns),(lines)
    SMALL_RECT WinRect = {0, 0, 160, 25};  
    SMALL_RECT* WinSize = &WinRect;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);
}
void ResizeWindowSmall(){
//Used to resize console window when coming back from searches to main menu
	system("mode 80,25");
    SMALL_RECT WinRect = {0, 0, 80, 25};
    SMALL_RECT* WinSize = &WinRect;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);
}
void PressEnter(){
//throughout project I contionously use this to prompt user input to keep the project moving
	cout << endl;
	cout << "Press Enter to Continue: " << endl;
	cin.get();
	system("cls");
	}
const char * getIndent( unsigned int numIndents ){
//used for formatting the printed out details in .xml dumptostdout
    static const char * pINDENT = "                                       ";
    static const unsigned int LENGTH = strlen( pINDENT );

    if ( numIndents > LENGTH ) numIndents = LENGTH;

    return &pINDENT[ LENGTH-numIndents ];
}
void ShowHorsesHeader(){
//Formatting to make the text and headers line up neatly setw(widtha) and setw(widthb) using Global constants at the top of project
	cout /*<< left << setw(6) << " "*/
		<< left << setw(widtha) << "Name" 
		<< left << setw(widthb) << "Mother" 
		<< left << setw(widthb) << "Father" 
		<< left << setw(widthc) << "Height" 
		<< left << setw(widtha) << "Owner" 
		<< left << setw(widthc) << "Age" 
		<< left << setw(widthc-1) << "Win's"
		<< left << setw(widthb+1) << "Markings"
		<< left << setw(widtha) << "Notes"
		<< endl;
	}
void ShowRacesHeader(){
	cout<< left << setw(9) << " "
		<< left << setw(widtha) << "Name" 
		<< left << setw(widthb) << "Date"
		<< left << setw(widthb) << "Length"
		<< left << setw(widthc) << "Class"
		<< left << setw(widtha) << "Horses Beaten"
		<< left << setw(widthc) << "Position";
}
void DumpToStdout( TiXmlNode * pParent, unsigned int indent = 0 ){
//prints out details from .xml
    if ( !pParent ) return;

    TiXmlText *pText;
    int t = pParent->Type();
	cout << getIndent( indent);

    switch ( t ){
        case TiXmlNode::TINYXML_DOCUMENT:
		cout << "Document";
        break;

        case TiXmlNode::TINYXML_ELEMENT:
        //cout << pParent->Value();
        break;

        case TiXmlNode::TINYXML_COMMENT:
		cout << pParent->Value();
        break;

        case TiXmlNode::TINYXML_UNKNOWN:
		cout << "Unknown";
        break;

        case TiXmlNode::TINYXML_TEXT:
        pText = pParent->ToText();
		cout << pParent->Value();
        break;

        case TiXmlNode::TINYXML_DECLARATION:
		cout << "Declaration";
        break;
    
		default:
        break;
    }

    TiXmlNode * pChild;

    for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
        DumpToStdout( pChild, indent+1 );
    }
}
void ReadHorsesFromXMLFile(){
//option 4 in main menu, verifying names being looked for in .xml(view horses in file)
	ResizeWindowLarge();

	TiXmlDocument doc;
	doc.LoadFile ("horses.xml");
	TiXmlHandle docHandle( &doc );

	TiXmlElement* root = doc.FirstChildElement( "Horses" );
	if (root == NULL){
		cout << "Root Was Null" << endl;
		return;
	}

	TiXmlElement* child = root->FirstChildElement("Name");
	if (child == NULL){
		cout << "Child Was Null" << endl;
		return;
	}

	//for(root; root; root=root->NextSiblingElement())
	ShowHorsesHeader();
	for(child; child; child=child->NextSiblingElement()){
		if (child){
			cout << endl;
			DumpToStdout(child, 2);
		}
		else{
			cout << "Something Went Wrong\n";
		}
	}
	PressEnter();
}
class FileHeader {
//using this as a file check at beginning
public:
    float VersionNumber;
    //other fields required in file header
};
bool FileExists(std::string filePath){
//Checks if the .dat file exists
	bool doesFileExist = false;
	fstream fin(filePath.c_str(), ios::in);
	doesFileExist = fin.is_open();
	fin.close();

	return doesFileExist;
}
void SetupDataFile(std::string filePath) {
//writes details of file number out, was used for checking/verification purposes
	FileHeader headerToWriteToFile;
	headerToWriteToFile.VersionNumber = CURRENT_VERSION_NUMBER;
	ofstream ofs (filepath.c_str(), ios::out|ios::binary);
	ofs.write(( char *) &headerToWriteToFile, sizeof(headerToWriteToFile));
	ofs.close();
}
void WriteThisHorseToFile(char* horseName, char* horseMother, char* horseFather, char* horseHeight, char* horseOwner, char* horseAge, char* horseWins, char* horseMarkings, char* horseNotes) {
//retrieving details of horses to be saved to const at top of page(horses.dat), gets details passed from WriteHorseToFile()
	horse myHorseToWriteToFile;
	myHorseToWriteToFile.setName	(horseName);
	myHorseToWriteToFile.setMother	(horseMother);
	myHorseToWriteToFile.setFather	(horseFather);
	myHorseToWriteToFile.setHeight	(horseHeight);
	myHorseToWriteToFile.setOwner	(horseOwner);
	myHorseToWriteToFile.setAge		(horseAge);
	myHorseToWriteToFile.setWin		(horseWins);
	myHorseToWriteToFile.setMarkings(horseMarkings);
	myHorseToWriteToFile.setNotes	(horseNotes);

	if (! FileExists( filepath.c_str() ) ) {
	  SetupDataFile( filepath.c_str() );
	}

	ofstream ofs (filepath.c_str(), ios::out|ios::app|ios::binary);
	ofs.write(( char *) &myHorseToWriteToFile, sizeof(myHorseToWriteToFile));
	ofs.close();
}
void WriteHorsesToXML(char* horseName, char* horseMother, char* horseFather, char* horseHeight, char* horseOwner, char* horseAge, char* horseWins, char* horseMarkings, char* horseNotes){  
//retrieving details of horses to be saved to horses.xml file, gets details passed from WriteHorseToFile()
	TiXmlDocument doc;
    doc.LoadFile ("horses.xml");

    TiXmlElement* root = doc.FirstChildElement( "Horses" );
    if ( root ){
		TiXmlElement * element2 = new TiXmlElement( "Name" );  
		root->LinkEndChild( element2 );  
	 
		TiXmlText * text2 = new TiXmlText(horseName);  
		element2->LinkEndChild( text2 );  
	 
		TiXmlElement * element3 = new TiXmlElement( "Mother" );  
		element2->LinkEndChild( element3 );  
	 
		TiXmlText * text3 = new TiXmlText(horseMother);  
		element2->LinkEndChild( text3 );  
	 
		TiXmlElement * element4 = new TiXmlElement( "Father" );  
		element2->LinkEndChild( element4 );  
	 
		TiXmlText * text4 = new TiXmlText(horseFather);  
		element2->LinkEndChild( text4 );  

		TiXmlElement * element5 = new TiXmlElement( "Height" );  
		element2->LinkEndChild( element5 );  
	 
		TiXmlText * text5 = new TiXmlText(horseHeight);  
		element2->LinkEndChild( text5 ); 

		TiXmlElement * element6 = new TiXmlElement( "Owner" );  
		element2->LinkEndChild( element6 );  
	 
		TiXmlText * text6 = new TiXmlText(horseOwner);  
		element2->LinkEndChild( text6 );
	 
		TiXmlElement * element7 = new TiXmlElement( "Age" );  
		element2->LinkEndChild( element7 );  
	 
		TiXmlText * text7 = new TiXmlText(horseAge);  
		element2->LinkEndChild( text7 );

		TiXmlElement * element8 = new TiXmlElement( "Wins" );  
		element2->LinkEndChild( element8 );  
	 
		TiXmlText * text8 = new TiXmlText(horseWins);  
		element2->LinkEndChild( text8 );

		TiXmlElement * element9 = new TiXmlElement( "Markings" );  
		element2->LinkEndChild( element9 );  
	 
		TiXmlText * text9 = new TiXmlText(horseMarkings);  
		element2->LinkEndChild( text9 );

		TiXmlElement * element10 = new TiXmlElement( "Notes" );  
		element2->LinkEndChild( element10 );  
	 
		TiXmlText * text10 = new TiXmlText(horseNotes);  
		element2->LinkEndChild( text10 );
	}
    else{
		TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );  
		doc.LinkEndChild( decl );  

		TiXmlElement * root = new TiXmlElement( "Horses" );  
		doc.LinkEndChild( root );

		TiXmlElement * element2 = new TiXmlElement( "Name" );  
		root->LinkEndChild( element2 );  
	 
		TiXmlText * text2 = new TiXmlText(horseName);  
		element2->LinkEndChild( text2 );  
	 
		TiXmlElement * element3 = new TiXmlElement( "Mother" );  
		element2->LinkEndChild( element3 );  
	 
		TiXmlText * text3 = new TiXmlText(horseMother);  
		element2->LinkEndChild( text3 );  
	 
		TiXmlElement * element4 = new TiXmlElement( "Father" );  
		element2->LinkEndChild( element4 );  
	 
		TiXmlText * text4 = new TiXmlText(horseFather);  
		element2->LinkEndChild( text4 );  

		TiXmlElement * element5 = new TiXmlElement( "Height" );  
		element2->LinkEndChild( element5 );  
	 
		TiXmlText * text5 = new TiXmlText(horseHeight);  
		element2->LinkEndChild( text5 ); 

		TiXmlElement * element6 = new TiXmlElement( "Owner" );  
		element2->LinkEndChild( element6 );  
	 
		TiXmlText * text6 = new TiXmlText(horseOwner);  
		element2->LinkEndChild( text6 );
	 
		TiXmlElement * element7 = new TiXmlElement( "Age" );  
		element2->LinkEndChild( element7 );  
	 
		TiXmlText * text7 = new TiXmlText(horseAge);  
		element2->LinkEndChild( text7 );

		TiXmlElement * element8 = new TiXmlElement( "Wins" );  
		element2->LinkEndChild( element8 );  
	 
		TiXmlText * text8 = new TiXmlText(horseWins);  
		element2->LinkEndChild( text8 );

		TiXmlElement * element9 = new TiXmlElement( "Markings" );  
		element2->LinkEndChild( element9 );  
	 
		TiXmlText * text9 = new TiXmlText(horseMarkings);  
		element2->LinkEndChild( text9 );

		TiXmlElement * element10 = new TiXmlElement( "Notes" );  
		element2->LinkEndChild( element10 );  
	 
		TiXmlText * text10 = new TiXmlText(horseNotes);  
		element2->LinkEndChild( text10 );
	}

	//ReadHorsesFromXMLFile();
 
    doc.SaveFile("horses.xml");
}
void WriteHorseToFile(){
//gets horse details and sends them to be saved in WriteHorsesToXML and WriteThisHorseToFile
	system("cls");
	cout << endl;

	cout << "Enter Horse's Name : ";
	char horseName[40];
	cin.getline (horseName, 40);

	cout <<"Enter Mother's Name : ";
	char horseMother[40];
	cin.getline (horseMother, 40);

	cout << "Enter Father's Name : ";
	char horseFather[40];
	cin.getline (horseFather, 40);

	cout << "Enter the Horse's Height : ";
	char horseHeight[5];
	cin.getline (horseHeight, 5);

	cout << "Enter Owner's Name : ";
	char horseOwner[50];
	cin.getline (horseOwner, 40);

	cout << "Enter the Horse's Age : ";
	char horseAge[5];
	cin.getline (horseAge, 5);

	cout << "Races Won : ";
	char horsewin[5];
	cin.getline (horsewin, 5);

	char horseMarkings[256];
	cout << "Markings on Horse : ";
	cin.getline( horseMarkings, 256);

	char horseNotes[256];
	cout << "Notes About the Horse : ";
	cin.getline( horseNotes, 256);

	WriteHorsesToXML(horseName, horseMother, horseFather, horseHeight, horseOwner,
		horseAge, horsewin, horseMarkings, horseNotes);
	WriteThisHorseToFile(horseName, horseMother, horseFather, horseHeight, horseOwner,
		horseAge, horsewin, horseMarkings, horseNotes);

	system("cls");
	cout << "\nHorse Entered To Stables\n";
	PressEnter();
	}
void ReadHorsesFromFile(){
//Option 3 in main menu(search function), gets the horse details that are in .dat file
	ResizeWindowLarge(); //resize window for easier reading

	system("cls");

	ifstream ifs (filepath.c_str(), ios::in|ios::binary);
	FileHeader head;
	ifs.read(( char *)&head, sizeof(head));

	cout << "File head information:" << endl;
	cout << '\t' << "Running: " << CURRENT_VERSION_NUMBER << endl;
	cout << '\t' << "File : " << head.VersionNumber << endl << endl;

	if (head.VersionNumber > CURRENT_VERSION_NUMBER){
		cout << "Data file saved using newer version of application" << endl;
		ifs.close();
	}

	else {
		horses.clear();
		while (true) {
			horse myHorseReadFromFile;
			if (ifs.read(( char *)&myHorseReadFromFile, sizeof(myHorseReadFromFile))) {
				// add this horse to the list of horses

				horses.push_back(myHorseReadFromFile);
			}

			else {
				// no (more) horses
				break;
			}
		}
		ifs.close();
	}
	cout << endl << "Currently There Is " << horses.size() << " Horse(s) Within Our Stables:" << endl << endl;
}
void ShowHorse(horse horseToDisplay) { 
//formatting to make the text and headers line up neatly setw(widtha), setw(widthb) and setw(widthb) use global constants at the top
	cout << left << setw(widtha) << horseToDisplay.getName() 
		<< left << setw(widtha) <<horseToDisplay.getMother()
		<< left << setw(widtha) <<horseToDisplay.getFather()
		<< left << setw(widthb) <<horseToDisplay.getHeight()
		<< left << setw(widtha) <<horseToDisplay.getOwner()
		<< left << setw(widthb) <<horseToDisplay.getAge()
		<< left << setw(widthb) <<horseToDisplay.getWin()
		<< left << setw(widthc) <<horseToDisplay.getMarkings()
		<< left << setw(widthc) <<horseToDisplay.getNotes()
		<< endl;
}
void ShowHorse(horse horseToDisplay, bool showHeader){
//displaying horses with header above details
	if (showHeader) {
		ShowHorsesHeader();
	}
	ShowHorse(horseToDisplay);
}
void PrintHorsesToScreen() {
//Option 2 on main menu, after it retrieves details using ReadHorsesFromFile this then sends them to screen
	if (horses.size() > 0) {
		ShowHorsesHeader();

		for each (horse thisHorse in horses) {
			ShowHorse(thisHorse,false);
		}
	}

	else {
		cout << "No horses.";
	}
	
PressEnter();
}
void FindHorse(){
//Option 3 in main menu, searching for horse within the .dat file
	cout << "Name Of Horse To Find: " << endl;
	string nameToFind;
	cin >> nameToFind;

	horse horseToFind;

	bool found=false;

	for (unsigned int i = 0; i < horses.size(); i++) {
		horse thisHorse = horses[i];

		if (thisHorse.getName() == nameToFind) {
			horseToFind = thisHorse;
			found=true;
			break;
		}
	}

	if (found){
		cout << "\nFound Horse Called " << "'" << nameToFind << "'\n" << endl;
		ShowHorse(horseToFind,true);
	}

	else{
		cout << "\nCouldn't find horse with name '" << nameToFind << "'\n" << endl;
	}

	while (true){

		cout << endl;
		cout << "1) Back To Main Menu" << endl;
		cout << "2) Search For Another Horse" << endl;

		cout << endl << "Choose an Option" << endl;

		int option;
		cin >> option;
		cout << endl;

		switch (option){

			case 1: {
			cin.ignore();
			MainMenu();
			break;
			}

			case 2:{
			ReadHorsesFromFile();
			FindHorse();
			break;
			}
		}
	}
}
void SearchXML(){
//Option 5 in our main menu, searching the XML doc for a horse
	ResizeWindowLarge();

	TiXmlDocument doc;
    doc.LoadFile ("horses.xml");
	TiXmlHandle docHandle(&doc);

	TiXmlElement* horses = docHandle.FirstChild("Horses").ToElement(); //Error checking to make sure it reads the Element correctly
	if (horses == NULL){
		cout << "Horse Not Found" << endl;
		return;
	}
	TiXmlElement* child = horses->FirstChildElement("Name"); //Error checking to make sure it reads the Child Element correctly
	if (child == NULL){
		cout << "Child Not Found" << endl;
	}
		//cout << horses; //to check that horses is read corectly if all 0's = failed
	//cout << child->GetText(); //to check that Child is read corectly should print out horse name

	cout << "Name Of Horse To Find: ";
	char nameToFind[20];
	cin.getline (nameToFind, 20); // cout <<endl << "Looking for " << nameToFind <<endl <<endl; //another check to make sure it takes in the name I want to search for
	
	bool found = false;
	for(child; child; child=child->NextSiblingElement()){
		if (!strcmp(nameToFind, child->GetText())){ //cout << nameToFind <<  " == " << child->GetText()<<endl; // this is to see the horse name is checked agenst each horse name line for testing
			cout << "\nFound Horse Called '" << nameToFind << "'\n" << endl;
			ShowHorsesHeader();
			DumpToStdout(child, 4); // child in brackets is to send the child node name to the screen including other child nodes of that horse name the number after child is to add to indent for formatting 
			found = true;
		break;
		}
	}
	if (found == false){
		cout << "No Horse Called '" << nameToFind << "'" << endl;
	}

	while (true){
		cout << endl;
		cout << "\n1) Back To Main Menu" << endl;
		cout << "2) Search For Another Horse" << endl;

		cout << endl << "Choose an Option" << endl;

		int option;
		cin >> option;
		cout << endl;

		switch (option){

			case 1:{
				cin.ignore();
				MainMenu();
				break;
			}

			case 2:{
				cin.ignore();
				SearchXML();
				break;
			}
		}
	}
}
void HorsesInRace(){
//before race begins within option 6 it will tell you which horses are to run in that race and this displays them(UNCOMPLETE)
    TiXmlDocument doc;
    doc.LoadFile ("list.xml");
    TiXmlHandle docHandle( &doc );

	TiXmlElement* child = docHandle.FirstChild( "List" ).FirstChild( "Names" ).ToElement();
	TiXmlElement* child2 = docHandle.FirstChild( "List" ).FirstChild( "Names" ).ToElement();
	TiXmlElement* child3 = docHandle.FirstChild( "List" ).FirstChild( "Names" ).ToElement();

	child->GetText();
	child2=child2->NextSiblingElement();
	child3=child2->NextSiblingElement();{

	cout << "\n\nNo. 1 - " << child->GetText();
	cout << "\nNo. 2 - "  << child2->GetText();
	cout << "\nNo. 3 - "  << child3->GetText();
	}
}
void ReadFromRaceXML(){
//formats details/headers from .xml file and displays them, this is within ReadRaceXML which is option 7 on main menu
	cout /*<< left << setw(6) << " "*/
		/*<< left*/ << setw(10) << "Date"					//can setw within the brackets manually
		/*<< left*/ << setw(widthb) << "Length" 
		/*<< left*/ << setw(widthb) << "RaceClass" 
		/*<< left*/ << setw(widthc-6) << "Names" << endl;	//just showing that it is possible to do 'math' using widthc
}
void RaceToXML(char* Date, char* Length, char* RaceClass, char* Names/*, char* HorsesBeaten, char* Position*/){ //this creates my race.xml, the nodes etc....
//saves all input details to race.xml through function WriteRaceToXML which is option 6 on main menu
	TiXmlDocument doc;
    doc.LoadFile ("race.xml");

    TiXmlElement* root = doc.FirstChildElement( "Races" );
    if ( root ){
		TiXmlElement * element2 = new TiXmlElement( "Date" );  
		root->LinkEndChild( element2 );  
	 
		TiXmlText * text2 = new TiXmlText(Date);  
		element2->LinkEndChild( text2 );  
	 
		TiXmlElement * element3 = new TiXmlElement( "Length" );  
		element2->LinkEndChild( element3 );  
	 
		TiXmlText * text3 = new TiXmlText(Length);  
		element2->LinkEndChild( text3 );  
	 
		TiXmlElement * element4 = new TiXmlElement( "Class" );  
		element2->LinkEndChild( element4 );  
	 
		TiXmlText * text4 = new TiXmlText(RaceClass);  
		element2->LinkEndChild( text4 );
		
		TiXmlElement * element5 = new TiXmlElement( "Names" );  
		element2->LinkEndChild( element5 );  
	 
		TiXmlText * text5 = new TiXmlText(Names);
		element2->LinkEndChild( text5 );

		//TiXmlElement * element6 = new TiXmlElement( "HorsesBeaten" );  
		//element2->LinkEndChild( element6 );  
	 //
		//TiXmlText * text6 = new TiXmlText(HorsesBeaten);
		//element2->LinkEndChild( text6 );

		//TiXmlElement * element7 = new TiXmlElement( "Position" );  
		//element2->LinkEndChild( element7 );  
	 //
		//TiXmlText * text7 = new TiXmlText(Position);
		//element2->LinkEndChild( text7 );
	}
    else{
		TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );  
		doc.LinkEndChild( decl );  

		TiXmlElement * root = new TiXmlElement( "Races" );  
		doc.LinkEndChild( root );

		TiXmlElement * element2 = new TiXmlElement( "Date" );  
		root->LinkEndChild( element2 );  
	 
		TiXmlText * text2 = new TiXmlText(Date);  
		element2->LinkEndChild( text2 );  
	 
		TiXmlElement * element3 = new TiXmlElement( "Length" );  
		element2->LinkEndChild( element3 );  
	 
		TiXmlText * text3 = new TiXmlText(Length);  
		element2->LinkEndChild( text3 );  
	 
		TiXmlElement * element4 = new TiXmlElement( "Class" );  
		element2->LinkEndChild( element4 );
	 
		TiXmlText * text4 = new TiXmlText(RaceClass);  
		element2->LinkEndChild( text4 );

		TiXmlElement * element5 = new TiXmlElement( "Names" );
		element2->LinkEndChild( element5 );
	 
		TiXmlText * text5 = new TiXmlText(Names);
		element2->LinkEndChild( text5 );

	/*	TiXmlElement * element6 = new TiXmlElement( "HorsesBeaten" );  
		element2->LinkEndChild( element6 );  
	 
		TiXmlText * text6 = new TiXmlText(HorsesBeaten);
		element2->LinkEndChild( text6 );

		TiXmlElement * element7 = new TiXmlElement( "Position" );  
		element2->LinkEndChild( element7 );  
	 
		TiXmlText * text7 = new TiXmlText(Position);
		element2->LinkEndChild( text7 );*/
	}
    doc.SaveFile("race.xml");
}
void ListHorses(){
//this reads horses within horses.xml and displays them to screen before user inputs which ones will run in race
    TiXmlDocument doc;
    doc.LoadFile ("horses.xml");
    TiXmlHandle docHandle( &doc );

	cout << "Horses Available To Run:\n\n" ;

    TiXmlElement* child = docHandle.FirstChild( "Horses" ).FirstChild( "Name" ).ToElement();

    for( child; child; child=child->NextSiblingElement()){
		if ("Name")
			cout << child->GetText() << endl;
		else
			cout << "Something Went Wrong" << endl;
	}
}
void LoadingPage(){
//used as my race, with no graphics I use this as the actual race
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\t\t/ \\\n";
    cout << "\t\t| |\n";
    cout << "\t\t| |\n";
    cout << "\t\t| |\n";

	for (int num = 0; num >= 0; --num){
		for (int c = 0; c < 10000000; ++c);
	}
	
	cout <<("\t   And There Off! !\n");	
	
	for (int num = 0; num < 23; ++num){
		for (int c = 0; c < 10000000; ++c);
            cout << "\n";
	}
}
void RaceResults(){
//after the race is over this is the winner annoucncement page(UNCOMPLETE......)
    TiXmlDocument doc;
    doc.LoadFile ("list.xml");
    TiXmlHandle docHandle( &doc );

	TiXmlElement* horse = docHandle.FirstChild( "List" ).FirstChild( "Names" ).ToElement();

	TiXmlElement* child = docHandle.FirstChild( "List" ).FirstChild( "Names" ).ToElement();
	TiXmlElement* child2 = docHandle.FirstChild( "List" ).FirstChild( "Names" ).ToElement();
	TiXmlElement* child3 = docHandle.FirstChild( "List" ).FirstChild( "Names" ).ToElement();

	cout << "Horses In This Race:\n\n" ;
	for( horse; horse; horse=horse->NextSiblingElement()){
		if ("Name")
			cout << horse->GetText() << endl;
		else
			cout << "Something Went Wrong" << endl;
	}

	LoadingPage();
	
	system("cls");
	cout << endl;
	cout << "Press Enter To Get Race Results: " << endl;
	cin.get();
	system("cls");

	child->GetText();
	child2=child2->NextSiblingElement();
	child3=child2->NextSiblingElement();{

	
		system("cls");

		cout << "\n\t      WINNER ! ! ! \n";
		cout << "\t**********************";
		cout << "\n1ST -\t\t" << child->GetText();
		cout << "\n\t**********************";
		
		cout << "\n\n\n\n";
		cout << "\t      Second \n";
		cout << "\t* * * * * * * * * * *";
		cout << "\n2ND -\t\t" << child2->GetText();
		cout << "\n\t* * * * * * * * * * *";

		cout << "\n\n\n\n";
		cout << "\t      Third \n";
		cout << "\t+ + + + + + + + + + +";
		cout << "\n3RD -\t\t" << child3->GetText();
		cout << "\n\t+ + + + + + + + + + +";
		cout << "\n\n";

		PressEnter();
	}
}
void SaveToXML(char* Names){
//creates list.xml to store Only the names of the horses which the user said would be in the race
	TiXmlDocument doc;
    doc.LoadFile ("list.xml");

    TiXmlElement* root = doc.FirstChildElement( "List" );
    if ( root ){
		TiXmlElement * element2 = new TiXmlElement( "Names" );  
		root->LinkEndChild( element2 );

		TiXmlText * text2 = new TiXmlText(Names);  
		element2->LinkEndChild( text2 );  
		}

	else{
		TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );  
		doc.LinkEndChild( decl );  

		TiXmlElement * root = new TiXmlElement( "List" );  
		doc.LinkEndChild( root );

		TiXmlElement * element2 = new TiXmlElement( "Names" );  
		root->LinkEndChild( element2 );  

		TiXmlText * text2 = new TiXmlText(Names);  
		element2->LinkEndChild( text2 );

	}
	 doc.SaveFile("list.xml");

}
void WriteRaceToXML(){
//writes all race details to race.xml, links with RaceToXML() to save
	remove( "list.xml" );

	system("cls");
	cout << endl;

	cout <<"Enter Date Of Race: ";
	char Date[20];
	cin.getline (Date, 20);

	cout << "Enter Race Length: ";
	char Length[20];
	cin.getline (Length, 20);
	
	cout << "Enter Class Of Race: ";
	char RaceClass[40];
	cin.getline (RaceClass, 40);

	cout << "How Many Horses Are Running(Must be 3+ To Race): ";
	int numberOfHorses = 0;
	cin >> numberOfHorses;
	cin.ignore();

	system("cls");
	cout << "There Will Be " << numberOfHorses << " Horse(s) Running Today\n" << endl;
	
	ListHorses();
	
	int list = numberOfHorses;

	while(list > 0){
		cout << "\nEnter Horse's To Race : ";
		char Names[100];
		cin.getline (Names, 100);

		TiXmlDocument doc;
		doc.LoadFile ("horses.xml");
		TiXmlHandle docHandle(&doc);

		TiXmlElement* horses = docHandle.FirstChild("Horses").ToElement(); //Error checking to make sure it reads the Element correctly
		if (horses == NULL){
			cout << "Horse Not Found" << endl;
			return;
		}
	
		TiXmlElement* child = horses->FirstChildElement("Name"); //Error checking to make sure it reads the Child Element correctly
		if (child == NULL){
			cout << "Child Not Found" << endl;
		}
		//cout << horses; //to check that horses is read corectly if all 0's = failed
		//cout << child->GetText(); //to check that Child is read corectly
		bool found = false;
		
		for(child; child; child=child->NextSiblingElement()){
			if (!strcmp(Names, child->GetText())){ // this is to see the horse names are checked agenst each 'horse name line' for testing
				found = true;
				break;
			}
		}
	
		if (found == false){
			cout << "No Horse Called '" << Names << "'" << endl;
		}
		else {
			cout << "'" << Names << "'" << " Is At The Starting Post ! ! !" << endl; 
			--list;
		}
		RaceToXML(Date, Length, RaceClass, Names);
		SaveToXML(Names);
	}
	PressEnter();

	system("cls");
	cout << "\nHorses Running:\n";
	HorsesInRace();
	cout << "\n\nAll Horses Are Ready, So Lets Get Started. . . . . . . . . .\n";
		
	cout << endl;
	cout << "\nPress Enter To Begin Race: \n" << endl;
	cin.get();
	system("cls");

	RaceResults();
}
void ReadRaceXML(){
//option 7 on main menu, reads details from race.xml and displays
	ResizeWindowLarge();

	TiXmlDocument doc;
	doc.LoadFile ("race.xml");
	TiXmlHandle docHandle( &doc );

	TiXmlElement* root = doc.FirstChildElement( "Races" );
	if (root == NULL){
		cout << "Root Was Null" << endl;
		return;
	}

	TiXmlElement* child = root->FirstChildElement("Date");
	if (child == NULL){
		cout << "Child Was Null" << endl;
		return;
	}

	//for(root; root; root=root->NextSiblingElement())
	ReadFromRaceXML();
	for(child; child; child=child->NextSiblingElement()){
		if (child){
			cout << endl;
			DumpToStdout(child, 2);
		}
		else{
			cout << "Something Went Wrong\n";
		}
	}
	PressEnter();
}
void MainMenu(){
//Main menu
	system("cls");

	while (true) {
		
		ResizeWindowSmall();

		cout << "\n\n\n" << "\t\t" << "Welcome To The Stables" << endl;

		cout << endl;
		cout << "1) New Horse Entry To Stables" << endl;
		cout << "2) View Horses Currently Within Our Stables" << endl;
		cout << "3) Search (by Horse Name) For A Horse In This Stable" << endl;
		cout << "\n" << "\t" << "XML Section" << endl;
		
		cout << "4) View Horses Currently Within Our Stables(XML Format)" << endl;
		cout << "5) Search (by Horse Name) For A Horse In This Stable(XML Format)" << endl;
		cout << "6) Write Race To XML" << endl;
		cout << "7) Read Race XML" << endl;
		cout << endl;
		cout << "8) Leave Stables" << endl;	

		cout << endl << "Choose an Option" << endl;

		int choice;
		cin >> choice;
		cout << endl;

		switch (choice) {

			case 1: {
				cin.ignore();
				WriteHorseToFile();
				break;
			}

			case 2: {
				cin.ignore();
				ReadHorsesFromFile();
				PrintHorsesToScreen();
				break;
			}

			case 3: {
				ReadHorsesFromFile();
				FindHorse();
				break;
			}

			case 4: {
				cin.ignore();
				ReadHorsesFromXMLFile();
				break;
			}

			case 5: {
				cin.ignore();
				SearchXML();
				break;
			}

			case 6: {
				cin.ignore();
				WriteRaceToXML();
				break;
			}		
			case 7: {
				cin.ignore();
				ReadRaceXML();
				break;
			}		
			case 8:{
				exit (1);
				break;
			}
		}
	}
}
int main(){

	MainMenu(); //reads straight to the function Main Menu()
}