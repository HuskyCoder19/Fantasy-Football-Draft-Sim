#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include "draft.hpp"

using namespace std;

int main(){

  //get players & draft position
  int playCount, draftPos;
  cout << "Players in the draft: ";
  cin >> playCount;
  cout << "Draft position: ";
  cin >> draftPos;

  cout << "Starting draft simulation..." << endl;
  vectorInit(); //create position vectors from file
  teamVecInit(playCount);
  
  int round = 1;
  bool fromStart = true;

  while(round <= 16){
    
    if(fromStart){

      //iterate through players from start
      for(int i = 0 ; i < playCount ; i++){

	      cout << endl;
	      cout << "Round " << round << endl;

	      if(i == draftPos-1){
      	  cout << "It is your pick!" << endl;
	        cout << "----------------" << endl;
      	  cout << "Top ranked available players for each position:" << endl;
		  cout << endl;

          viewTopPlayers();
	        cout << endl;
	  
	        if(teams[i].size()){
	          cout << "Your previous pick: ";
	          teams[i][teams[i].size()-1].printPlayer();

			  printPosCount(i);
			  cout << endl;
	        }

          while(1){
	
	          int adp;
	          cout << "ADP of your pick: ";
	          cin >> adp;

			  if(adp <= 0 || adp >= 300){
				return 0;
			  }

	          if(removePlayer(adp, i)){
	            break;
	          }
          }
	      }
	      else{
	        cout << "Player #" << i+1;
          cout << endl;

          autoDraft(i);
          
	      }
      }
      fromStart = false;
    }
    else{

      //iterate through players from end
      for(int i = playCount-1 ; i >= 0 ; i--){

	      cout << endl;
	      cout << "Round " << round << endl;
	
	      cout << endl;
	      if(i == draftPos-1){
      	  cout << "It is your pick!" << endl;
      	  cout << "Top ranked available player for each position:" << endl;
		  cout << endl;

          viewTopPlayers();
          cout << endl;

	        if(teams[i].size()){
	          cout << "Your previous pick: ";
	          teams[i][teams[i].size()-1].printPlayer();

			  printPosCount(i);
			  cout << endl;
	        }

          while(1){
	
	          int adp;
	          cout << "ADP of your pick: ";
	          cin >> adp;

			  if(adp <= 0 || adp >= 300){
				return 0;
			  }

	          if(removePlayer(adp, i)){
	            break;
	          }
          }
	      }
	      else{
	        cout << "Player #" << i+1;
          cout << endl;

          autoDraft(i);
	      }
      }
      fromStart = true;
    }
    round++;
  }

  cout << endl;
  viewLineup(draftPos-1);
  cout << endl;

  while(1){

	int n;
	cout << "Type team number to view team (1 - " << playCount;
	cout << "): ";
	cin >> n;

	if(n>= 1 && n <= playCount){
		viewLineup(n-1);
	}
	else{
		break;
	}
  }

  return 0;
}
