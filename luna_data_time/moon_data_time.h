#include <iostream>
#include <string>
using namespace std;


class Datatime {

    double day;
    bool prov_god(int y) const;
    //preob **.**.**** in JD
    double date(int y, int m, int d) const;
public: 
    // stok_sost
    Datatime();
    Datatime(string s);

    //for read line in moon
    Datatime(int ymd, int hms);

    //proverki
    bool is_ok(int y, int m, int d) const;
    bool is_ok_time(int h, int m, int s) const;

    // vich...day of week
    int week() const;
    

    // ---
    double operator-(const Datatime& srav_day) const;

    // +++
    Datatime operator+(int add_days) const;


    bool operator>(const Datatime& srav_day) const;
    bool operator<(const  Datatime& srav_day) const;
    bool operator>=(const Datatime& srav_day) const;
    bool operator<=(const Datatime& srav_day) const;
    bool operator==(const Datatime& srav_day ) const;
    
    friend ostream& operator<<(ostream& out, const Datatime& dt); 
};


void printMoonEvents(FILE* f, const string& dateStr, int y, int m, int d);