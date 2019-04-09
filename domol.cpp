#include <iostream>
#include <vector>
#include <string>
using namespace std;

int getNextState(char, int);

int main() {
  int currentState = 1;
  string input;
  getline(cin,input);
  // "123 := azon { komi } (* ez is komment *)"
  string output = "";

  for(int i = 0; i<input.length();) {
    cout << currentState << "("<< input.at(i) <<") -> " ;
    currentState = getNextState(input.at(i),currentState);
    cout << currentState << endl;

    if(currentState == 3) output += "azonosító ";
    else if(currentState == 5) output += "szám ";
    else if(currentState == 7) output += "{ komment } ";
    else if(currentState == 11) output += "(* komment *) ";
    else if(currentState == 13) output += ":= ";
    else if(currentState == 15) output += "<= ";
    else if(currentState == 16) output += "<> ";
    else if(currentState == 18) output += ">= ";

    if(currentState == 3 ||
      currentState == 5 ||
      currentState == 20) i--;
    else if(currentState == 7 ||
      currentState == 11 ||
      currentState == 13 ||
      currentState == 15 ||
      currentState == 16 ||
      currentState == 18 ||
      currentState == 19) i=i;
    else i++;

  }
  cout << input << endl;
  cout << output << endl;
  return 0;
}

/* int getNextState(char input, int currentState) {
  char in_varies[11] = {'{','}','(','*',')',':','=','<','>',' '};
  if(currentState == 1)
  {
    if(isalpha(input)) return 2;
    else if(isdigit(input)) return 4;
    else if(input == '(') return 8;
    else if(input == '{') return 6;
    else if(input == ':') return 12;
    else if(input == '<') return 14;
    else if(input == '>') return 17;
    else if(input == ' ') return 1;

    return 19;
  } else if(currentState == 2)
  {
    if(isalpha(input)) return 2;
    else if(isdigit(input)) return 2;
    else return 3;
  } else if(currentState == 3)
  {
    if(isalpha(input)) return 1;
    else if(isalpha(input)) return 1;
    else return 1;
  } else if(currentState == 4)
  {
    if(isalpha(input)) return 5;
    else if(isdigit(input)) return 4;
    else if(input == ' ') return 5;
    else return 5;
  } else if(currentState == 5)
  {
    return 1;
  } else if(currentState == 6)
  {
    if(input == '}') return 7;
    return 6;
  }else if(currentState == 7)
  {
    return 1;
  } else if(currentState == 8)
  {
    if(input == '*') return 9;
    return 9;
  } else if(currentState == 9)
  {
    if(input == '*') return 10;
    return 9;
  } else if(currentState == 10)
  {
    if(input == '*') return 10;
    else if(input == ')') return 11;
    return 9;
  } else if(currentState == 11) {
    return 1;
  } else if(currentState == 12)
  {
    if(input == '=') return 13;
    else if(input == ' ') return 20;
    return 20;
  } else if(currentState == 13)
  {
    return 1;
  } else if(currentState == 14)
  {
    if(input == '=') return 15;
    else if(input == '>') return 16;
    return 20;
  } else if(currentState == 15)
  {
    return 1;
  } else if(currentState == 16)
  {
    return 1;
  } else if(currentState == 17)
  {
    if(input == '=') return 18;
    return 20;
  } else if(currentState == 18 || currentState == 19 || currentState == 20)
  {
    return 1;
  }
  return 0;
}  Egyik megoldás, de ez nagyon hardcode */

int getNextState(char input, int currentState) {
  int jel = -1;
  char inputs[11] = {'{','}','(','*',')',':','=','<','>',' '};
  int table[20][14] = {{2,4,6,19,8,19,19,12,19,14,17,1,19,21},
                       {2,2,3,3,3,3,3,3,3,3,3,3,3,3},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       {5,4,5,5,5,5,5,5,5,5,5,5,5,5},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       {6,6,6,7,6,6,6,6,6,6,6,6,6,19},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       {20,20,20,20,20,9,20,20,20,20,20,20,20,19},
                       {9,9,9,9,9,10,9,9,9,9,9,9,9,19},
                       {9,9,9,9,9,10,11,9,9,9,9,9,9,19},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       {20,20,20,20,20,20,20,20,13,20,20,20,20,19},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       {20,20,20,20,20,20,20,20,15,20,16,20,20,19},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       {20,20,20,20,20,20,20,20,18,20,20,20,20,19},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                       {1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  if(isdigit(input)) jel = 1; //ha szám
  else if(isalpha(input)) jel = 0; //ha betű
  else {
    for(int i = 0; i<(sizeof(inputs)/sizeof(char)); i++) {
      if(inputs[i] == input) jel = i+2; // +2, mivel a szám, és a betű előtte van.
    }
  }
  if(jel == -1) jel = 12;
  //Ha az előző feltételek nem teljesültek egyikre sem, akkor átkell menni "egyéb" jelre, aminek
  //12-es az idje

  return table[currentState-1][jel]; // -1 azért, mert 0-tól indexelünk és mainen belül pedig 1-től.
}
