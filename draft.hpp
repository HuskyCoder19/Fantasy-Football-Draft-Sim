/*
* All draft functionality & file parsing done in here
*/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include "players.hpp"

using namespace std;

vector<Player> wr;
vector<Player> rb;
vector<Player> qb;
vector<Player> te;
vector<Player> k;
vector<Player> def;

vector<vector<Player>> teams;

//create string vector from read in csv string [ADP, Player, Team, Position]
vector<string> lineParser(string buf){

  vector<string> vars;

  int ind = 0;
  int count = 0;
  int addCount = 0;
  bool inQuote = false;
  
  for(int i = 0 ; i < buf.length() ; i++){

    if((int)buf[i] == 34 && !inQuote){
      inQuote = true;
    }
    else if((int)buf[i] == 34){
      ind = i - count;
      string var = buf.substr(ind, count); //get substring
      vars.push_back(var); //push to variable vector
      addCount++;
      inQuote = false;
      count = 0;
      ind = 0;
    }
    else if((int)buf[i] != 44){
      count++;
    }

    //stop after adding first for variables - don't need the others
    if(addCount >= 4){
      break;
    }
    
  }

  return vars;  
}

//remove dashes & numbers from position
string getPos(string p){

  string pos;

  for(int i = 0 ; i < p.length() ; i++){
    if((int)p[i] == 45){
      pos = p.substr(0, i);
    }
  }

  return pos;
  
}

//push player to correct position vector
void pushToPosVec(Player p){

  string pos = p.pos;
  
  if(pos == "WR"){
    wr.push_back(p);
    return;
  }
  if(pos == "RB"){
    rb.push_back(p);
    return;
  }
  if(pos == "QB"){
    qb.push_back(p);
    return;
  }
  if(pos == "TE"){
    te.push_back(p);
    return;
  }
  if(pos == "K"){
    k.push_back(p);
    return;
  }
  if(pos == "DEF"){
    def.push_back(p);
    return;
  }
  
}

//initialize position vectors from csv
void vectorInit(){

  fstream file;
  file.open("adp.txt", ios::in);

  if(!file.is_open()){
    cout << "ERROR: Failed to open file" << endl;
    return;
  }

  string buf;
  getline(file, buf);

  while(getline(file, buf)){

    vector<string> vars = lineParser(buf); //parse to variable vector
    vars[3] = getPos(vars[3]);

    Player p = Player(stoi(vars[0]), vars[1], vars[2], vars[3]);

    //push to position vector
    pushToPosVec(p);
    
  }
  
  file.close();
}

//allocate enough team vectors
void teamVecInit(int count){
  for(int i = 0 ; i < count ; i++){
    vector<Player> v;
    teams.push_back(v);
  }
}

//display highest adp players at each position
void viewTopPlayers(){

  cout << "WRs: " << endl;
  for(int i = 0 ; i < 5 ; i++){
    if(i >= wr.size()){
      break;
    }
    wr[i].printPlayer();
  }
  cout << endl;

  cout << "RBs: " << endl;
  for(int i = 0 ; i < 5 ; i++){
    if(i >= rb.size()){
      break;
    }
    rb[i].printPlayer();
  }
  cout << endl;

  cout << "QBs: " << endl;
  for(int i = 0 ; i < 5 ; i++){
    if(i >= qb.size()){
      break;
    }
    qb[i].printPlayer();
  }
  cout << endl;

  cout << "TEs: " << endl;
  for(int i = 0 ; i < 5 ; i++){
    if(i >= te.size()){
      break;
    }
    te[i].printPlayer();
  }
  cout << endl;

  cout << "Ks: " << endl;
  for(int i = 0 ; i < 5 ; i++){
    if(i >= k.size()){
      break;
    }
    k[i].printPlayer();
  }
  cout << endl;

  cout << "DEFs: " << endl;
  for(int i = 0 ; i < 5 ; i++){
    if(i >= def.size()){
      break;
    }
    def[i].printPlayer();
  }
  
}

//remove player, save to myTeam vector if myPick == true
bool removePlayer(int adp, int p){

  if(adp <= 0 || adp > 300){
    cout << "ERROR: ADP out of bounds." << endl;
    return false;
  }

  for(int i = 0 ; i < wr.size() ; i++){
    if(adp == wr[i].adp){
      cout << "Drafting: ";
      wr[i].printPlayer();
      teams[p].push_back(wr[i]);
      wr.erase(wr.begin() + i);
      return true;
    }
  }

  for(int i = 0 ; i < rb.size() ; i++){
    if(adp == rb[i].adp){
      cout << "Drafting: ";
      rb[i].printPlayer();
      teams[p].push_back(rb[i]);
      rb.erase(rb.begin() + i);
      return true;
    }
  }

  for(int i = 0 ; i < qb.size() ; i++){
    if(adp == qb[i].adp){
      cout << "Drafting: ";
      qb[i].printPlayer();
      teams[p].push_back(qb[i]);
      qb.erase(qb.begin() + i);
      return true;
    }
  }

  for(int i = 0 ; i < te.size() ; i++){
    if(adp == te[i].adp){
      cout << "Drafting: ";
      te[i].printPlayer();
      teams[p].push_back(te[i]);
      te.erase(te.begin() + i);
      return true;
    }
  }

  for(int i = 0 ; i < k.size() ; i++){
    if(adp == k[i].adp){
      cout << "Drafting: ";
      k[i].printPlayer();
      teams[p].push_back(k[i]);
      k.erase(k.begin() + i);
      return true;
    }
  }

  for(int i = 0 ; i < def.size() ; i++){
    if(adp == def[i].adp){
      cout << "Drafting: ";
      def[i].printPlayer();
      teams[p].push_back(def[i]);
      def.erase(def.begin() + i);
      return true;
    }
  }

  cout << "ERROR: failed to find player with ADP: " << adp;
  cout << endl;
  return false;
  
}

//get count of drafted players for a position on a team
int getCount(int p, string pos){
  
  int count = 0;
  for(int i = 0 ; i < teams[p].size() ; i++){
    if(teams[p][i].pos == pos){
      count++;
    }
  }

  return count;

}

//get the next lowest adp available to draft and mathematically possible for teams
Player getNextADP(vector<int> maxed){

  vector<Player> v;
  //check wr
  if(!count(maxed.begin(), maxed.end(), 1) && wr.size()){
    v.push_back(wr[0]);
  }
  //check rb
  if(!count(maxed.begin(), maxed.end(), 2) && rb.size()){
    v.push_back(rb[0]);
  }
  //check qb
  if(!count(maxed.begin(), maxed.end(), 3) && qb.size()){
    v.push_back(qb[0]);
  }
  //check te
  if(!count(maxed.begin(), maxed.end(), 4) && te.size()){
    v.push_back(te[0]);
  }
  //check k
  if(!count(maxed.begin(), maxed.end(), 5) && k.size()){
    v.push_back(k[0]);
  }
  //check def
  if(!count(maxed.begin(), maxed.end(), 6) && def.size()){
    v.push_back(def[0]);
  }

  //get lowest adp in vector v
  int low = v[0].adp;
  int ind = 0;
  for(int i = 0 ; i < v.size() ; i++){
    if(v[i].adp < low){
      low = v[i].adp;
      ind = i;
    }
  }

  return v[ind];
}

//auto drafter for other players
void autoDraft(int p){

  //take highest available ADP
  //don't exceed max posioton count
  //wr = 5, rb = 5, qb = 2, te = 2, k = 1, def = 1

  vector<int> v;
  //blacklist positions
  if(getCount(p, "WR") >= 5){
    v.push_back(1);
  }
  if(getCount(p, "RB") >= 5){
    v.push_back(2);
  }
  if(getCount(p, "QB") >= 2){
    v.push_back(3);
  }
  if(getCount(p, "TE") >= 2){
    v.push_back(4);
  }
  if(getCount(p, "K") >= 1){
    v.push_back(5);
  }
  if(getCount(p, "DEF") >= 1){
    v.push_back(6);
  }

  Player player = getNextADP(v);
  removePlayer(player.adp, p);
}

void viewADP(int p){

  int totADP = 0;
  for(int i = 0 ; i < teams[p].size() ; i++){
    totADP += teams[p][i].adp;
  }

  cout << "Total ADP: " << totADP << endl;
}

void viewLineup(int p){

    vector<int> indexes;

    cout << "Lineup: " << endl;

    //print qb
    for(int i = 0 ; i < teams[p].size() ; i++){
        if(teams[p][i].pos == "QB"){
            cout << "QB:    ";
            teams[p][i].printPlayer();
            indexes.push_back(i);
            break;
        }
    }

    //print top two RBs
    int rbCount = 0;
    for(int i = 0 ; i < teams[p].size() ; i++){
        if(teams[p][i].pos == "RB"){
            cout << "RB:    ";
            teams[p][i].printPlayer();
            indexes.push_back(i);
            rbCount++;
        }
        if(rbCount == 2){
            break;
        }
    }

    //print top two WRs
    int wrCount = 0;
    for(int i = 0 ; i < teams[p].size() ; i++){
        if(teams[p][i].pos == "WR"){
            cout << "WR:    ";
            teams[p][i].printPlayer();
            indexes.push_back(i);
            wrCount++;
        }
        if(wrCount == 2){
            break;
        }
    }

    //print TE
    for(int i = 0 ; i < teams[p].size() ; i++){
        if(teams[p][i].pos == "TE"){
            cout << "TE:    ";
            teams[p][i].printPlayer();
            indexes.push_back(i);
            break;
        }
    }

    //print FLX
    bool found = false;
    for(int i = 0 ; i < teams[p].size() ; i++){
        if(teams[p][i].pos == "RB" || teams[p][i].pos == "WR" || teams[p][i].pos == "TE"){
            if(!count(indexes.begin(), indexes.end(), i)){
                found = true;
                cout << "FLX:   ";
                teams[p][i].printPlayer();
                indexes.push_back(i);
            }
        }
        if(found){
            break;
        }
    }

    //print DEF
    for(int i = 0 ; i < teams[p].size() ; i++){
        if(teams[p][i].pos == "DEF"){
            cout << "DEF:   ";
            teams[p][i].printPlayer();
            indexes.push_back(i);
            break;
        }
    }

    //print K
    for(int i = 0 ; i < teams[p].size() ; i++){
        if(teams[p][i].pos == "K"){
            cout << "K:    ";
            teams[p][i].printPlayer();
            indexes.push_back(i);
            break;
        }
    }

    //print bench
    for(int i = 0 ; i < teams[p].size() ; i++){
        if(!count(indexes.begin(), indexes.end(), i)){
            cout << "B:    ";
            teams[p][i].printPlayer();
        }
    }

    viewADP(p);
}

void printPosCount(int p){

  cout << "Position count: ";
  cout << "WR-" << getCount(p, "WR") << ", ";
  cout << "RB-" << getCount(p, "RB") << ", ";
  cout << "QB-" << getCount(p, "QB") << ", ";
  cout << "TE-" << getCount(p, "TE") << ", ";
  cout << "K-" << getCount(p, "K") << ", ";
  cout << "DEF-" << getCount(p, "DEF");
  cout << endl;

}