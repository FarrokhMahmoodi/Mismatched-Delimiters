#include<iostream>
#include <fstream>
#include <string>
#define SIZE 1000 //static stack max size
using namespace std;
class DelimiterStack 
{ 
 private:
 	
  struct DelimiterNode 
  {
   char character;
   int lineNumber;
   int charCount;
    
    DelimiterNode(char a, int x, int y)  //individual node storage for each character
    {
    character=a;
    lineNumber=x;
    charCount=y;
    }
    DelimiterNode() 
	{

	}
   //...
  };

  // Define stack top
	
  int top;

  DelimiterNode stack[SIZE];  //full stack
 public:
  //Constructor
  
  DelimiterStack () 
    {
  	top =-1; //global value of top, as stack is empty
    }
  
  //...
  //Destructor
  //...
  //Stack Operations

  bool isEmpty() //correct match for every left bracket to right bracket after scanning all lines of text
 {
	return top == -1; //stack is empty
 }

bool push(char ch, int ln, int chn)   //adds left bracket to stack
 {
	DelimiterNode node(ch,ln,chn);
	if (top == SIZE-1)               //if top position is the last of position of stack, means stack is full .
	{
		cout <<"Stack is full\n";
		return false;
	}
	top++;
	stack[top] = node;
	return true;
 }

void popDelimiter(char& ch, int& ln , int& chn)  //removes left bracket from stack if matching right bracket
 {  
	if (top == -1) 
	{
		cout<<"Stack is Empty\n";
	}
	ch = stack[top].character;
	ln = stack[top].lineNumber;
	chn = stack[top].charCount;
	top--;
	return;
 }
 
  // reference variables because three variables cannot be 
  //returned through return statement

};


int main() {
 // variable declarations and initializations
 DelimiterStack myStack;

 ifstream myfile;  //read in text file
 myfile.open("text.txt"); 
 string currentLine = ""; //white space adds new line
 getline(myfile, currentLine);
 int lineNumber = 1; //Line count for text file starting at the top

 while (currentLine != "DONE") //SCANS TEXT FILE FOR BRACKETS
{
  int charCount = 0;
  
  for (char c: currentLine) {
  	charCount++;
  	if (c == '(' || c == '{' || c == '[')         //adds every left bracket scanned in text file to stack
	{      
  	   	myStack.push(c, lineNumber, charCount);
	}
	else if (c == ')' || c == '}' || c == ']')    //If right bracket scanned first, prints no matching left bracket for right bracket.
	{    
		if (myStack.isEmpty()) 
		{
			string str = "Right delimiter " + to_string(c) + " had no left delimiter found at line " + to_string(lineNumber) + ", char " + to_string(charCount);
			break; 
		}
		char ch;int ln,chn;
		myStack.popDelimiter(ch, ln, chn);
		string temp(1,ch);
		if ( (c ==')' && ch != '(' ) || (c==']' && ch != '[' ) || (c=='}' && ch != '{' ))       //Scans through text matching left to right bracket with character count, line number and character count
		{
			string str = "Mismatched delimiter " + temp + " found at line " + to_string(ln) + ", char " + to_string(chn) + " does not match " + c + " found at line " + to_string(lineNumber) + ", char " + to_string(charCount);
			cout<<str<<endl;
			return 0;
		}
	}
  }
  getline(myfile, currentLine);
  lineNumber++;
 }
 
 if (!myStack.isEmpty()) //If text does not have correct matching left-to-right brackets
 {  
 	while (!myStack.isEmpty()) 
	{
 		char ch;int ln,chn;
		myStack.popDelimiter(ch, ln, chn);
		string temp(1,ch);
		string str = "Left delimiter " + temp + + " found at line " + to_string(ln) + ", char " + to_string(chn) + " had no right delimiter.";
		cout<<str<<endl;
	}
 }

 // rest of the logic
 //...

 return 0;
}



