#include "priorityQ.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

// custom mercenary struct
struct mercType
{
    // tracks how many of each monsters is
    // defeated and civilian saved for a
    // mercenary
    int zombies = 0;
    int spiders = 0;
    int drainDeimos = 0;
    int zombieDogs = 0;
    int hunters = 0;
    int nemesis = 0;
    int civilians = 0;
    // default constructor , optional but can
    // be helpful
    mercType ()
    {
    }

    // helper function ~ return mercenary score
    float getScore(){
      float score = this->zombies * 1.0;
      score += this->spiders * 1.1;
      score += this->drainDeimos * 1.2;
      score += this->zombieDogs * 1.3;
      score += this->hunters * 1.4;
      score += this->nemesis * 1.5;
      score += this->civilians * 2.0;
      return score;
    }

    // helper function ~ update mercenary counts 
    void updateMercCounts(string type, int count){
       if(type == "zombies"){
        this->zombies += count;
      } else if(type == "spiders"){
        this->spiders += count;
      } else if(type == "drainDeimos"){
        this->drainDeimos += count;
      } else if(type == "zombieDogs"){
        this->zombieDogs += count;
      } else if(type == "hunters"){
        this->hunters += count;
      } else if(type == "nemesis"){
        this->nemesis += count;
      } else if(type == "civilians"){
        this->civilians += count;
      }
    }

    // return true if lhs score is greater than rhs score
    bool operator > (const mercType & rhs) const
    {
      // left operator score
      float lhsScore = this->zombies * 1.0;
      lhsScore += this->spiders * 1.1;
      lhsScore += this->drainDeimos * 1.2;
      lhsScore += this->zombieDogs * 1.3;
      lhsScore += this->hunters * 1.4;
      lhsScore += this->nemesis * 1.5;
      lhsScore += this->civilians * 2.0;

      // right operator score
      float rhsScore = rhs.zombies * 1.0;
      rhsScore += rhs.spiders * 1.1;
      rhsScore += rhs.drainDeimos * 1.2;
      rhsScore += rhs.zombieDogs * 1.3;
      rhsScore += rhs.hunters * 1.4;
      rhsScore += rhs.nemesis * 1.5;
      rhsScore += rhs.civilians * 2.0;

      // return true or false based on scores
      return lhsScore > rhsScore;
    }

    // add score of rhs to score of lhs
    mercType& operator += (const mercType & rhs)
    {
      this->zombies += rhs.zombies;
      this->spiders += rhs.spiders;
      this->drainDeimos += rhs.drainDeimos;
      this->zombieDogs += rhs.zombieDogs;
      this->hunters += rhs.hunters;
      this->nemesis += rhs.nemesis;
      this->civilians += rhs.civilians;
      return *this;
    }
   

};

int main(int argc, char *argv[]){

    // each element contains merc name and priority
    priorityQ<string, mercType> mercenaries;
    ifstream reader;
  
    // mercenary names file
    string mercFile = "";
    cout << "Enter mercenaries file: ";
    cin >> mercFile;
    cout << endl;

    reader.open(mercFile);
    if(!reader){
      cout << "Invalid file name" << endl;
      return 0;
    }

    string name;
    while(getline(reader, name)){
      if(name.empty()){
        break;
      } else {
        mercenaries.push_back(name, mercType());
      }
    }
    reader.close();

    // game simulation file
    string simFile = "";
    cout << "Enter simulation file: ";
    cin >> simFile;
    cout << endl;

    reader.open(simFile);
    if(!reader){
      cout << "Invalid file name" << endl;
      return 0;
    }

    string line;
    float prevScore = -1;
    string prevLeader = "";
    while(getline(reader, line)){
      string name, monster;
      int count;

      if(line.empty()){
        break;  
      }

      stringstream ss(line);
      ss >> name >> monster >> count;
      mercType temp;

      // update mercenary counts and priority
      temp.updateMercCounts(monster, count);
      mercenaries.increaseKey(name, temp);

      // output if new leader
      if(mercenaries.get_front_priority().getScore() > prevScore){
        if (mercenaries.get_front_key() != prevLeader) {
          cout << "We have a new leader: " << name << " Score: " << fixed << setprecision(1) << mercenaries.get_front_priority().getScore() << endl;
        }
        prevScore = mercenaries.get_front_priority().getScore();
        prevLeader = mercenaries.get_front_key();
      }
    }
    cout << endl;

    // output mercenary leaderboard by rank
    int rank = 1;
    while(!mercenaries.isEmpty()){
      // output rank, mercenary name, and score
      cout << "Rank " << rank << endl;
      cout << "Name: " << mercenaries.get_front_key() << " Score: " << mercenaries.get_front_priority().getScore() << endl;
      
      // prepare next iteration
      mercenaries.pop_front();
      rank++; 
    }

    return 0;
}