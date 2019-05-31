//Tyler Price
//ITEC 360 Project 2
//editdis.cpp
//main Driver at bottom

#include<bits/stdc++.h>
#include <vector>
using namespace std; 
  
//minOf3 : int int int -> int
//takes in 3 integers and returns the minimum of the 3 numbers
int minOf3(int x, int y, int z) { 
   return min(min(x, y), z); //return the minimum of 3 numbers
} 

//applyWeight : int int int int int int -> int
//takes in 3 integers representing operations and the values that apply to them
//returns the weight of the operation
int applyWeight(int x, int y, int z, int insertion,int  deletion, int substitution) { 
	if(minOf3(x+insertion,y+deletion,z+substitution) == x+insertion){ //return  the correct weight of each operation to add to the table
		return x+insertion;
	}else if(minOf3(x+insertion,y+deletion,z+substitution) == y+deletion){
		return y+deletion;
	}else
		return z+substitution; 
} 
 

//EditDist : string string int int int int int int -> int
//takes in two words, their lengths, and the weights of the operations
//returns the edit distance between the two words with the weights applied
int EditDist(string a, string b, int aLength ,int bLength,int copy, int insertion,int  deletion, int substitution){
	
	int bt[aLength + 1][bLength + 1];// make table
		
	
	for (int i = 0; i <= aLength; ++i) {
		for (int j = 0; j <= bLength; ++j){
			if (i==0){
            	//assign first row of table
				bt[i][j] = j;
			}else if (j==0){ 
            	//assign first column of table
				bt[i][j] = i;
			}else if (tolower(a[i - 1]) == tolower(b[j - 1])) {//tolower to make calculation case insinsitive
				//if a copy happened
				bt[i][j] = bt[i-1][j-1] + copy;

			} else {
				bt[i][j] = applyWeight(
						bt[i][j - 1], // insertion 
						bt[i - 1][j], // deletion
						bt[i - 1][j - 1]// substitution
						,insertion,deletion,substitution);
			}
			
		}
		
	}
	return bt[aLength][bLength];
	
}
//replaceInPlace : string string -> string
//takes in a string of the text to be modified, and a string that is within the edit distance
//returns the modified text with parens around all instances of the word
string replaceInPlace(string input, string word){
	string half1;
	string half2;
	string middle;
	int length = word.length();
	for(int i = 0; i < input.length(); i++){//look for a matching first letter
						
				if( input.at(i) == word.at(0)	//if the first letter is there
					&& input.at(i-1) != '(' // and hasn't been changed
					&& !isalpha(input.at(i-1))// not the middle of a word
					&& i + length < input.length() // isn't to far towards the end
					&& !isalpha(input.at(i+length)) // not the middle of a word
					&& input.substr(i,(length)) == word){ //is equal to the word
					
				half1 = input.substr(0,i); // take first half the input
				half2 = input.substr(i+length);//take second half of input 
				middle = '(' + word + ')';//  make word with parens
				
				input = half1 + middle + half2;	//put the word in the middle of the two halves
				
				i += length;//skip remaining letters of the word
			}
	
		}
	return input;
}

//getAndProcessInput : void -> string
//gets input from std::in
//processes input according to input
//returns a string of the modified input
string getAndProcessInput(){

    string str1;
    string str2;
	string input;
	vector<string> alreadyUsed;

	int minDist;//variable initializing
	int copy;
	int deletion;
	int substitution;
	int insertion;
	int cWordED;

	cin >> str1;//reading in and assigning first lines of file
	cin >> minDist;
	cin >> copy;
	cin >> deletion;
	cin >> insertion;
	cin >> substitution;
	
	string line;
	
	while (getline(cin, line))//read in the file with whitespace adding linebreaka
	{	
		input += line + '\n';
	}
	stringstream s(input);//stringstream splits the input into words

	while( s >> str2){ //while there are still words

		if(!isalpha(str2.at(str2.length()-1))) //ignore special characters on either end of the word
			str2 = str2.substr(0,str2.length()-1);
		if(!isalpha(str2.at(0)))
			str2 = str2.substr(1,str2.length());

			if(find(alreadyUsed.begin() , alreadyUsed.end() , str2) == alreadyUsed.end()){ //only find edistdist for new words
	
			cWordED = EditDist//check the edit distance of the current word
				(str1 , str2 , str1.length(), str2.length(), copy, insertion, deletion, substitution);
			
			if(cWordED <= minDist){// if the editdistance is less than the input amount
				input = replaceInPlace(input,str2);
				alreadyUsed.push_back(str2);
			}
		}
	}
		cout << '\n' << str1 << '\n' << minDist << '\n'
			<< copy << ' ' << deletion << ' ' << substitution  << ' ' << insertion << endl;	
	
		return  input;//return modified input

}


// Driver program
// ---------------------compilation and running instructions--------------------------
// program can be compiled into an executable "ed" by running the "make" command
// then "ed" can be ran with the command : ./ed < [inputfile.txt] 
// alternatively program can be compiled using the command : g++ -o ed editdis.cpp
// and ran the same way as above
//----------------------reccurence relation------------------------------------------
//base cases : bt[i][j] = j for  i = 0 
//			 : bt[i][j] = i for  j = 0
//			
//
//			     { bt[i][j - 1] + insertion							}
//	bt(i,j) = min{ bt[i - 1][j] + deletion 							}
//			     { if(bt[i-1][j-1] = bt[i][j]) bt[i-1][j-1] + copy  }
//			     { 	else bt[i-1][j-1] + substitution 				}
//
// used  https://www.geeksforgeeks.org/edit-distance-dp-5/ for creation of the DP algorithm   
int main(){
	cout << getAndProcessInput() << endl; // prints modified input
	
}
