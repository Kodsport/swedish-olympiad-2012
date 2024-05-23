#include <iostream>
#include <cstdio>
#include <string>
#include <cassert>

using namespace std;

int grid[10][10];
const int NORMAL = 0;
const int DL = 1;
const int TL = 2;
const int DW = 3;
const int TW = 4;

int max(int a, int b) {
	return (a > b)?a:b;
}

//Returnerar antalet poäng som utdelas om ordet word läggs ut med första bokstaven i rutan på rad row+1 och kolumn col+1.
//Om horiz==true så läggs ordet ut horisontellt, annars vertikalt.
int getPoints(string word, int row, int col, bool horiz) {
	//Om ordet ska läggas ut horisontellt
	if(horiz) {
		//Fortsätt om ordet får plats.
		if(col + word.length() <= 10) {
			
			int points = 0;
			
			//Faktor som den totala bokstavspoängen multipliceras med.
			int factor = 1;
			
			//Summera summan av bokstavspoängerna. Bokstäver som ligger på DL eller TL får sin poäng multiplicerad med 2 respektive 3.
			//factor modifieras för varje DW eller TW som vi stöts på
			for(int i=0; i<word.length(); i++) {
				if(grid[row][col+i] == DL) {
					points += (word[i]-'0')*2;
				} else if(grid[row][col+i] == TL) {
					points += (word[i]-'0')*3;
				} else {
					points += word[i]-'0';
				}
				
				
				if(grid[row][col+i] == DW)
					factor *= 2;
				else if(grid[row][col+i] == TW)
					factor *= 3;
			}
			
			points *= factor;
			
			return points;
			
		} else {  //Om ordet inte får plats returneras 0.
			return 0;
		}
	}
	else {
		//Analogt för vertikala ord.
		
		if(row + word.length() <= 10) {
			
			int points = 0;
			int factor = 1;
			
			for(int i=0; i<word.length(); i++) {
				if(grid[row+i][col] == DL) {
					points += (word[i]-'0')*2;
				} else if(grid[row+i][col] == TL) {
					points += (word[i]-'0')*3;
				} else {
					points += word[i]-'0';
				}
				
				if(grid[row+i][col] == DW)
					factor *= 2;
				else if(grid[row+i][col] == TW)
					factor *= 3;
			}
			
			points *= factor;
			
			return points;
			
		} else {
			return 0;
		}
		
	}
}

int main() {
	int n;
	scanf("%d", &n);
	
	//Inmatning.
	for(int i=0; i<n; i++) {
		int row, col;
		string type;
		
		scanf("%d", &row);
		
		scanf("%d", &col);
		
		cin >> type;
		
		if(type == "DL")
			grid[row-1][col-1] = DL;
		else if(type == "TL")
			grid[row-1][col-1] = TL;
		else if(type == "DW")
			grid[row-1][col-1] = DW;
		else if(type == "TW")
			grid[row-1][col-1] = TW;
		else
			assert(false); //Avslutar programmet om specialrutans typ har inkorrekt format.
		
		
	}
	
	string word;
	cin >> word;
	
	int best = 0;
	
	//Loopar igenom alla möjliga positioner och lagrar den bästa poängen i best.
	for(int i=0; i<10; i++) {
		for(int j=0; j<10; j++) {
			int result = max( getPoints(word, i, j, true), getPoints(word, i, j, false) );
			if(result > best) {
				best = result;
			}
		}
	}
	
	printf("%d\n", best);
}
