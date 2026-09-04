#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "classes.h"
using namespace std;

void prompt_user();
string get_country();
string get_date();
int get_cases();
int get_deaths();
DataEntry disect(string line);


int hash_f(string country_name);

int main(){

  //Initial declarations
  CovidDB hash_table;
  int input = 1;

  // Interactive loop
  while (input != 0){
    prompt_user();
    cin >> input;

    // Create initial hash table
    if (input == 1){
      string line;
      int i = 0;
      ifstream file("WHO-COVID-Data.csv");
      while (getline(file, line)){
        while (!line.empty() && (unsigned char)line[0] > 127){
          line.erase(0,1);
        }
        // Windows csv files leave a \r at the end of every line, get rid of it
        if (!line.empty() && line[line.size()-1] == '\r'){
          line.erase(line.size()-1,1);
        }
        i++;
        cout << "Starting" << endl;
        DataEntry entry = disect(line);
          entry.display();
          hash_table.add(entry);
          cout << "Ended" << endl;
        }
    }

    //Add a new data entry
    if (input == 2){
      string country_name = get_country();
      string date = get_date();
      int c_cases = get_cases();
      int c_deaths = get_deaths();
      DataEntry entry(date, country_name, c_cases, c_deaths);
      hash_table.add(entry);
    }
    if (input == 3){
      string country_name;
      cout << "What countries data would you like? ";
      cin >> country_name;
      cout << endl;
      try{
        hash_table.get(country_name).display();
      }
      catch (runtime_error& e){
        cout << e.what() << endl;
      }
    }
    if (input == 4){
      string country_name;
      cout << "What country would you like to delete?  ";
      cin >> country_name;
      hash_table.remove(country_name);
    }
    if (input == 5){
      hash_table.display_hash();
    }
  }
}



void prompt_user(){
  cout << "Please choose the operation you want:" << endl;
  cout << "1. Create the initial hash table" << endl;
  cout << "2. Add a new data entry" << endl;
  cout << "3. Get a data entry" << endl;
  cout << "4. Remove a data entry" << endl;
  cout << "5. Display hash table" << endl;
  cout << "0. Quit the system" << endl;
}

string get_country(){
  string country_name;
  cout << "Enter country name: ";
  cin >> country_name;
  return country_name;
}

string get_date(){
  string date;
  cout << "What date are you entering data for? ";
  cin >> date;
  return date;
}

int get_cases(){
  int c_cases;
  cout << "How how many new cases would you like to report? ";
  cin >> c_cases;
  return c_cases;
}

int get_deaths(){
  int c_deaths;
  cout << "How many new deaths would you like to report? ";
  cin >> c_deaths;
  return c_deaths;
}

DataEntry disect(string line){ // 1/3/2020,Afghanistan,0,0
  string date;
  date.clear();
    while (line[0] != ','){
      date.push_back(line[0]);
      line.erase(0,1);
  }
  line.erase(0,1);
  //cout << date << endl;


  string country;
  country.clear();
  // Antigua and Barbuda,AMRO,7,1275,0,42 - COUNTRY
  while (line[0] != ','){
    country.push_back(line[0]);
    line.erase(0,1);
  }
  line.erase(0, 1);
  //cout << country << endl;


  //1275,0,42 - CASES
  string cases;
  cases.clear();
  while (line[0] != ','){
    cases.push_back(line[0]);
    line.erase(0,1);
  }
  line.erase(0,1);
  int icases = stoi(cases);
  //cout << icases << endl;

  //42 - DEATHS
  string deaths;
  deaths.clear();
  while (!line.empty()){
    deaths.push_back(line[0]);
    line.erase(0,1);
  }
  int ideaths = stoi(deaths);
  //cout << ideaths << endl;


  // Have all the data now make a data entry and return it
  DataEntry entry(date, country,  icases, ideaths);
  return entry;

}
