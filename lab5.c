#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

using namespace std;

class Signal{
	private:
		//private data
		double length;
		double maximumValue;
                double max;
		double average;
		double* data;
		//private functions
		double getAverage();
		double getMax();
	public:
		//constructors
		Signal();
		Signal(int);
		Signal(const char*);
                ~Signal();      //destructor
		//public functions
		void offset(double);
		void scale(double);
		void center();
		void normalize();
		void statistics();
		void saveSignal(char*);
                void sigInfo();
};

//available constructors
Signal::Signal(){
	int i,size;
        //default constructor opens file number 1
	const char* fileName = "Raw_data_01.txt";
        
        //opens file using file stream
        ifstream fileIn(fileName);
        //checks if file exists
        if(fileIn.fail()){
            cout << "That file could not be found!" << endl;
            exit(0);
        }
        //gets first two values from file
        fileIn >> length >> maximumValue;
        
        //temporarily converts length to an int so data can be allocated
        size = (int)length;
	data = new double[size];
         
        //populates the data field
        for(i = 0; i < length; i++){
            fileIn >> data[i];
	 }
}

Signal::Signal(int fileNum){
	int i,size;
	char fileName[50];

	sprintf(fileName, "Raw_data_%02d.txt", fileNum);

	ifstream fileIn(fileName);
        if(fileIn.fail()){
            cout << "That file could not be found!" << endl;
            exit(0);
        }
        
        fileIn >> length >> maximumValue;
        
        size = (int)length;
	data = new double[size];
         
        for(i = 0; i < length; i++){
            fileIn >> data[i];
	 }
}

Signal::Signal(const char* fileName){
	int i,size;

	ifstream fileIn(fileName);
        if(fileIn.fail()){
            cout << "That file could not be found!" << endl;
            exit(0);
        }
        
        fileIn >> length >> maximumValue;
        
        size = (int)length;
	data = new double[size];
         
        for(i = 0; i < length; i++){
            fileIn >> data[i];
	 }
}

Signal::~Signal(){
    //cleans up the data
    delete[] data;
}

void Signal::saveSignal(char* fileName){
    int i;
    
    //creates or opens a file of specified fileName
    ofstream fileOut;
    fileOut.open(fileName);
    
    //fills the file with data
    fileOut << length << " " << maximumValue << endl;
    for(i = 0; i < length; i++){
	fileOut << data[i] << endl;
    }
}

void Signal::sigInfo(){
    //auto runs statistics to get necessary info
    statistics();
    //prints out acquired info
    cout << "Length of data set: " << length << endl;
    cout << "Current maximum value: " << max << endl;
    cout << "Current average of the signal: " << average << endl;
    
}

void Signal::offset(double off){
	 int i;
         //offsets the data by off amount
        for(i = 0; i < length; i++){
	     data[i] = (double)data[i] + off;
	 }
}

void Signal::scale(double scal){
	 int i;
         //scales the data by scal amount
	 for(i = 0; i < length; i++){
	     data[i] = (double)data[i] * scal;
	 }
}

double Signal::getAverage(){
	int i;
	double sum = 0;
	double avg = 0;

        //sums all the data
	for(i=0; i < length; i++){
	    sum = sum + data[i];
	}
      //divide by size for average
	avg = sum / length;

	return avg;
}

double Signal::getMax(){
	int i;
	double max = 0;

        //sorts data for largest present value
	for(i=0; i < length; i++){
	   if(max < data[i])
	        max = data[i];
	}

	return max;
}

void Signal::center(){
    //auto calls statistics to make sure average is populated
    statistics();
    //offsets data by its average to center it
    offset(average);
}

void Signal::normalize(){
    //scales data by the inverse of its largest possible value to center it
	scale((1.0/maximumValue));
}

void Signal::statistics(){
    //uses functions to get the average and max values;
    average = getAverage();
    max = getMax();
}

int main(int argc, char* argv[]){
    int choice,myNum,fileNum = 0;
    double scal,off;
    string input,fileNumber,fileName,select = "";
    char newFileName[50] = "";
    Signal *signal1;
    
    //will not run if command line arguments are present
    if(argc <= 2){
        while(true){
            //displays file loading options
        cout << "Please Select a menu option from below: " << endl;
        cout << "1. Load Default Signal File" << endl;
        cout << "2. Load Signal File Using File Number" << endl;
        cout << "3. Load Signal File Using Full File Name" << endl;
        cout << "4. Quit Without Loading a File" << endl;
        cout << "> ";
        
        //gets the user input
        getline(cin,input);
        cout << endl;
        //uses bit shifting to safely convert to an integer
        stringstream myStream(input);
        if(myStream >> myNum)
            break;
        else
            cout << "That input was not valid, please input a valid number" << endl;            
        }
        
        if(myNum == 1){
            //calls the default constructor
            signal1 = new Signal;
        }else
        if(myNum == 2){
            //offers the user the ability to enter the file number
            cout << "Please input a valid file number: ";
            //safely takes user input and converts to integer
            while(true){
                getline(cin,fileNumber);
                stringstream numStream(fileNumber);
                if(numStream >> fileNum)
                    break;
                cout << "That input was not valid, please input a valid number" << endl;
                }
                
            //calls a parametric constructor
            signal1 = new Signal(fileNum);
        }else
        if(myNum == 3){
            //offers the user the ability to enter the file name
            cout << "Please input a valid file name: ";
            //gets user input
            getline(cin,fileName);
            //converts string to constant character pointer
            const char* name = fileName.c_str();
            //calls a parametric constructor
            signal1 = new Signal(name);
        }else
            return 1;
        
        while(choice =! 0){
            //displays operations that the user can perform on the data
            cout << "Please Select an Option From Below:" << endl;
            cout << "0. Quit this program" <<endl;
            cout << "1. Offset Current Data" << endl;
            cout << "2. Scale Current Data" << endl;
            cout << "3. Center the Current Data" << endl;
            cout << "4. Normalize the Current Data" << endl;
            cout << "5. Get the Statistics of the Current Data" << endl;
            cout << "6. Display Info on the Current Data" << endl;
            cout << "7. Save the Current Data" << endl;
            cout << "> ";
            
            //gets user input and converts to integer
            while(true){
                fflush(stdin);
                getline(cin,select);
                cout << endl;
                stringstream numStream(select);
                if(numStream >> choice)
                    break;
                cout << "That input was not valid, please select a valid option" << endl;
            }
            
            //handles various input cases
            switch(choice){
                case 1:
                    cout << "What offset value would you like to use?" << endl << "> ";
                    cin >> off;
                    cout << endl;
                    signal1->offset(off);
                    cout << "The data has now been offset!" << endl;
                    break;
                    
                case 2:
                    cout <<"What scalar value would you like to use?" << endl << "> ";
                    cin >> scal;
                    cout << endl;
                    signal1->scale(scal);
                    cout << "The data has now been scaled!" << endl;
                    break;
                    
                case 3:
                    signal1->center();
                    cout << "The data has now been centered!" << endl;
                    break;
                    
                case 4:
                    signal1->normalize();
                    cout << "The data has now been normalized!" << endl;   
                    
                case 5:
                    signal1->statistics();
                    cout << "The data has had it's statistics calculated!" << endl;
                    break;
                    
                case 6:
                    signal1->sigInfo();
                    break;
                    
                case 7:
                    cout << "Please enter a name for the save file." << endl << "This should included the file extension and will overwrite an existing file if necessary" << endl << "> ";
                    cin >> newFileName;
                    signal1->saveSignal(newFileName);
                    break;
                default:
                    return 0;
                    break;
            }
        }
                    
    }

    return 0;
}
