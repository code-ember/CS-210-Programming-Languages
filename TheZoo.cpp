//============================================================================
// Name        : TheZoo.cpp
// Author      : Amber Foster
// Date        : October 22, 2020
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <jni.h>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<string>animalData;
string trackNumber;
string animalName;
string animalType;
string animalSubType;
int eggs;
int nurse;
int data;
ifstream zooData;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=U:/ZooFileWriter/bin";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

void AddAnimal() {
	cout << "Track Number: ";
	cin >> trackNumber;
	trackNumber.insert(trackNumber.begin(), 7 - trackNumber.length(), '0');

	cout << endl << "Animal Name: ";
	cin >> animalName;
	animalName.append(16 - animalName.length(), ' ');

	cout << endl << "Animal Type: ";
	cin >> animalType;
	animalType.append(16 - animalType.length(), ' ');

	cout << endl << "Animal Sub-Type: ";
	cin >> animalSubType;
	animalSubType.append(16 - animalSubType.length(), ' ');

	cout << endl << "Number of Eggs: ";
	cin >> eggs;

	cout << endl << "Nursing (0 for no 1 for yes): ";
	cin >> nurse;
	cout << endl;
}


void RemoveAnimal() {
	string item = "";
	cout << "Enter Track Number (with zeros): ";
	cin >> item;
	std::vector<string>::iterator it;

	if (it != animalData.end())
		animalData.erase(it);

	else {
		cout << "Track Number not found or entered incorrectly.." << endl;
		RemoveAnimal();
	}
}


void LoadDataFromFile() {
	while (!zooData.eof()){
		zooData.open("zoodata.txt");
		zooData >> trackNumber;
		zooData >> animalName;
		zooData >> animalType;
		zooData >> animalSubType;
		zooData >> eggs;
		zooData >> nurse;
	}
}

void SaveDataToFile() {
	fstream file;
	string fileName = "zoodata.txt";
	file.open(fileName);

	if(file.fail())
		cout << "File Opening Failed";
	    else {
	    	int i = 0;
	        int as = animalData.size();

	        while(as <=i) {
	            file << animalData[as];
	            as--;
	        }
	    }
}

void DisplayMenu() {
	cout << "--------------MENU--------------" << endl;
	cout << "(1)Load Animal Data"              << endl;
	cout << "(2)Generate Data"                 << endl;
	cout << "(3)Display Animal Data"           << endl;
	cout << "(4)Add Record"                    << endl;
	cout << "(5)Delete Record"                 << endl;
	cout << "(6)Save Animal Data"              << endl;
	cout << "(0)End Session"                   << endl;
	cout << "--------------------------------" << endl;
}

int main() {
	int userInput = -1;
	DisplayMenu();

	while(userInput != 0){
		cin >> userInput;
		if(userInput == 1){
			LoadDataFromFile();
			DisplayMenu();
		}
		if(userInput == 2){
			GenerateData();
			DisplayMenu();
		}
		if(userInput == 3){
			DisplayMenu();
			DisplayMenu();
		}
		if(userInput == 4){
			AddAnimal();
			DisplayMenu();
		}
		if(userInput == 5){
			RemoveAnimal();
			DisplayMenu();
		}
		if(userInput == 6){
			SaveDataToFile();
			DisplayMenu();
		}
	}
	cout << "Good Bye";
	return 1;
}
