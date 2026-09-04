#include <iostream>
#include <string>
#include <vector>
using namespace std;


class DataEntry{
  private:
    string date;
    string country;
    int c_cases;
    int c_deaths;
  public:
    DataEntry(string idate, string icountry, int ic_cases, int ic_deaths);
    string get_date();
    string get_country();
    int get_cases();
    int get_deaths();
    void change_date(string n_date);
    void add_cases(int cases);
    void add_deaths(int deaths);
    void display();

};

class CovidDB{
  private:
    vector<DataEntry> table[17];
    int hash_country(string country);
  public:
    bool add(DataEntry entry);
    DataEntry get(string country);
    void remove(string country);
    void display_hash();

};
