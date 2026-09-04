#include <iostream>
#include <string>
#include <vector>
#include "classes.h"
using namespace std;


// Constructor with inputs
DataEntry::DataEntry(string idate, string icountry, int ic_cases, int ic_deaths){
  date = idate;
  country = icountry;
  c_cases = ic_cases;
  c_deaths = ic_deaths;
}
string DataEntry::get_date(){
  return date;
}
string DataEntry::get_country(){
  return country;
}
int DataEntry::get_cases(){
  return c_cases;
}
int DataEntry::get_deaths(){
  return c_deaths;
}
void DataEntry::change_date(string n_date){
  date = n_date;
}
void DataEntry::add_cases(int cases){
  c_cases += cases;
}
void DataEntry::add_deaths(int deaths){
  c_deaths += deaths;
}
void DataEntry::display(){
  cout << country << " on " << date << ": " <<
  c_cases << " cases and " << c_deaths << " deaths." << endl;
}


int CovidDB::hash_country(string country){
  int t_value = 0;
  for (char& c : country){
    int current = c;
    t_value += current;
  }
  return t_value % 17;
}

void CovidDB::remove(string country){
  const int hash_number = hash_country(country);
  string name;
  int vector_number;
  bool found = false;
  for (int i = 0; i < table[hash_number].size() && found == false; i++){
    name = table[hash_number][i].get_country();
    if(name == country){
      vector_number = i;
      found = true;
    }
  }
  if (found){
    table[hash_number].erase(table[hash_number].begin() + vector_number);
    cout << "Entry has been erased." << endl;
  }
}


bool CovidDB::add(DataEntry entry){

  string country = entry.get_country(); // country: Zimbabwe << date: 10/14/2021 << c_cases: 92 << c_deaths: 3
  const int hash_number = hash_country(country);
  string name;
  int vector_number;
  bool found = false;
  vector_number = 0;

  for (int i = 0; i < table[hash_number].size() && found == false; i++){
    name = table[hash_number][i].get_country();
    if(name == country){
      vector_number = i;
      found = true;
    }
  }
  cout << "Hash_number, Vector_number: (" << hash_number << "," << vector_number << ")" << endl;

  if (found){

    cout << "Found" << endl;
    // Get dates of current existing_entry and new_entry
    // If current existing_entry is of newer date, ignore new_entry
    // If new_entry is of newer date, add new_entry's values to existing_entry and replace existing_entry's date with new_entry's
    string new_entry_date = entry.get_date();
    string existing_entry_date = table[hash_number][vector_number].get_date();
    cout << "New entry's date is: " << new_entry_date << " and existing entry's date is: " << existing_entry_date << endl; //10/14/2021

    // Get month

    string new_month_str, existing_month_str;
    while (new_entry_date[0] != '/'){ // Gets the digits before the '/' into new_month_str
      new_month_str.push_back(new_entry_date[0]);
      new_entry_date.erase(0,1);
    }
    while (existing_entry_date[0] != '/'){ // Gets the digits before the '/' into existing_month_str
      existing_month_str.push_back(existing_entry_date[0]);
      existing_entry_date.erase(0,1);
    }
    existing_entry_date.erase(0,1);  // Deletes the '/'  Now: 14/2021
    new_entry_date.erase(0,1); // Deletes the '/'  Now: 14/2021
    cout << "The month of new entry is: " << new_month_str << endl;
    cout << "The month of existing entry is: " << existing_month_str << endl;

    // Get day

    string new_day_str, existing_day_str;
    while (new_entry_date[0] != '/'){ // Gets the digits before the '/' into new_day_str
      new_day_str.push_back(new_entry_date[0]);
      new_entry_date.erase(0,1);
    }
    while (existing_entry_date[0] != '/'){ // Gets the digits before the '/' into existing_day_str
      existing_day_str.push_back(existing_entry_date[0]);
      existing_entry_date.erase(0,1);
    }
    existing_entry_date.erase(0,1);  // Deletes the '/'  Now: 2021
    new_entry_date.erase(0,1); // Deletes the '/'  Now: 2021
    cout << "The day of new entry is: " << new_day_str << endl;
    cout << "The day of existing entry is: " << existing_day_str << endl;

    // Get year

    string new_year_str, existing_year_str;
    for (int i = 0; i < 4; i++){ // Puts remaining digits into new_year_str
      new_year_str.push_back(new_entry_date[0]);
      new_entry_date.erase(0,1);
    }
    for (int i = 0; i < 4; i++){ // Puts remaining digits into existing_year_str
      existing_year_str.push_back(existing_entry_date[0]);
      existing_entry_date.erase(0,1);
    }
    cout << "The year of new entry is:" << new_year_str << "." <<endl;
    cout << "The year of existing entry is:" << existing_year_str << "." << endl;

    // Convert strings to ints
    // Make sure everything is actually a digit before we try to convert it, otherwise stoi blows up
    bool parsed_ok = !new_year_str.empty() && !new_month_str.empty() && !new_day_str.empty() &&
                     !existing_year_str.empty() && !existing_month_str.empty() && !existing_day_str.empty();
    for (int i = 0; i < new_year_str.size() && parsed_ok; i++){ if(!isdigit(new_year_str[i])) parsed_ok = false; }
    for (int i = 0; i < new_month_str.size() && parsed_ok; i++){ if(!isdigit(new_month_str[i])) parsed_ok = false; }
    for (int i = 0; i < new_day_str.size() && parsed_ok; i++){ if(!isdigit(new_day_str[i])) parsed_ok = false; }
    for (int i = 0; i < existing_year_str.size() && parsed_ok; i++){ if(!isdigit(existing_year_str[i])) parsed_ok = false; }
    for (int i = 0; i < existing_month_str.size() && parsed_ok; i++){ if(!isdigit(existing_month_str[i])) parsed_ok = false; }
    for (int i = 0; i < existing_day_str.size() && parsed_ok; i++){ if(!isdigit(existing_day_str[i])) parsed_ok = false; }

    if (!parsed_ok){
      cout << "Date came back weird, skipping the update." << endl;
      return true;
    }

    int new_year = stoi(new_year_str);
    int existing_year = stoi(existing_year_str);
    int new_month = stoi(new_month_str);
    int existing_month = stoi(existing_month_str);
    int new_day = stoi(new_day_str);
    int existing_day = stoi(existing_day_str);

    bool update = false;

    if (new_year > existing_year){
      update = true;
      cout << "Update = true." << endl;
    }
    else if (new_year == existing_year){
      cout << "Years are equal." << endl;
      if (new_month > existing_month){
        cout << "Update = true." << endl;
        update = true;
      }
      else if (new_month == existing_month){
        cout << "Months are equal." << endl;
        if (new_day > existing_day){
          update = true;
          cout << "Update = true." << endl;
        }
      }
    }

    if (update == true){
      cout << "Entry updated." << endl;
      table[hash_number][vector_number].change_date(entry.get_date());
      table[hash_number][vector_number].add_cases(entry.get_cases());
      table[hash_number][vector_number].add_deaths(entry.get_deaths());
    }

    return true;
  }
  // If is not there, get to hash number array and add in entry at end of vector
  table[hash_number].push_back(entry);
  cout << entry.get_country() << " has been added." << endl;
  return true;
}

void CovidDB::display_hash(){
  for (int i = 0; i < 17; i++){
    int vector_size = table[i].size();
    for (int j = 0; j < vector_size; j++)
      table[i][j].display();
  }
}

DataEntry CovidDB::get(string country){

  const int hash_number = hash_country(country);
  string name;
  int vector_number;
  bool found = false;

  for (int i = 0; i < table[hash_number].size() && found == false; i++){
    name = table[hash_number][i].get_country();
    if(name == country){
      vector_number = i;
      found = true;
    }
  }

  if (found){
    return table[hash_number][vector_number];
  }
  else{
    throw runtime_error("Country not found: " + country);
  }
}
