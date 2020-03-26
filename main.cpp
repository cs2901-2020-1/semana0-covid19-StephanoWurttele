#include <iostream>
#include <thread>
#include <fstream>
#include <vector>

using namespace std;

void read_file(string &dir){

  ifstream input1;
  string a = "";
  string temp = "";
  input1.open(dir);
  dir = "";
  getline(input1, a);
  while(input1 >> a){
    temp += a;  
  }
  dir = temp;
}

void compare(string s1, string s2, int &final){
    int count = 0;
    for (int i = 0; i < s1.size() ; ++i){
      if (s1[i] == s2[i]){
        count++;
      }
    }
    final += count;
}

int main(){
  string input1 = "AY278488.2.txt";
  string input2 = "AY274119.txt";
  int equal = 0;
  thread first_file {read_file, ref(input1)};
  thread second_file {read_file, ref(input2)};
  first_file.join();
  second_file.join();
  int smaller = input1.size() < input2.size() ? input1.size() : input2.size();
  int length = smaller/3000;
  vector<thread> pedazos;
  for( int i = 0; i < length ; ++i ){
    pedazos.emplace_back(compare, input1.substr(i*3000, 3000), input2.substr(i*3000, 3000), ref(equal));
  }
  pedazos.emplace_back(compare, input1.substr(length*3000, smaller%3000), input2.substr(length*3000, smaller%3000), ref(equal));
  for( int i = 0; i <= length ; ++i ){
    pedazos[i].join();
  }
  cout << equal*100.0/input1.size() << "%";
  return 0;
}
