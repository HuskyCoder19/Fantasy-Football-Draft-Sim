#include <string>
#include <vector>

using namespace std;

class Player{

public:
  
  int adp;
  string name;
  string team;
  string pos;

  Player(int r, string n, string t, string p) : adp(r), name(n), team(t), pos(p) {}

  void printPlayer();
  
};

void Player::printPlayer(){

  cout << name << " --- ";
  cout << "ADP: " << adp << ", ";
  cout << "Position: " << pos << ", ";
  cout << "Team: " << team << endl;
  
}


