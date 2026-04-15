#include <iostream>
#include "data_time.h"
#include <cmath>
using namespace std;

Datatime::Datatime()
{
    day = 0;
}

// prov on vis year
bool Datatime::prov_god(int y) const
{
    return (y % 4 == 0 && y % 100 !=0) || (y % 400 == 0);
}

// preob in one num (ul day)
double Datatime::date(int y, int m, int d) const 
{
    int a = (14 - m) / 12;
    int y_gen = y + 4800 - a;
    int m_gen = m + 12 * a - 3;

    long jd = d + (153 * m_gen + 2) / 5 + 365 * y_gen + y_gen / 4 - y_gen / 100 + y_gen / 400 - 32045;
    return (double)jd;
}

//days of week ...
int Datatime::week() const
{
    return (int(day) + 1) % 7;
}



// reliz konstr 
Datatime::Datatime(string s) {
    day = 0; 
    int y = 1, m = 1, d = 1, hh = 0, mm = 0, ss = 0;

    try {
        if (s.length() >= 10 && s[4] == '-') {
            y = stoi(s.substr(0, 4));
            m = stoi(s.substr(5, 2));
            d = stoi(s.substr(8, 2));
            if (s.length() >= 19 && s[10] == 'T') {
                hh = stoi(s.substr(11, 2));
                mm = stoi(s.substr(14, 2));
                ss = stoi(s.substr(17, 2));
            }
        } 
        else if (s.length() == 8) {
            y = stoi(s.substr(0, 4));
            m = stoi(s.substr(4, 2));
            d = stoi(s.substr(6, 2));
        }
        else if (s.find(':') != string::npos) {
            hh = stoi(s.substr(0, 2));
            mm = stoi(s.substr(3, 2));
            ss = stoi(s.substr(6, 2));
        }

        if (is_ok(y, m, d)) {
            day = date(y, m, d) + (hh / 24.0 + mm / 1440.0 + ss / 86400.0);
        } else {
            day = -1;
        }
    } catch (...) {
        day = -1;
    }
}
bool Datatime::is_ok_time(int h, int m, int s) const {
    return (h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60);
}

// is okey
bool Datatime::is_ok(int y, int m, int d) const {
    if (y < 1 || m < 1 || m > 12 || d < 1) return false;
    int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && prov_god(y)) months[1] = 29;
    return d <= months[m - 1];
}


//operator srav
double Datatime::operator-(const Datatime& sprav_day) const 
{
    return this->day - sprav_day.day;
}

Datatime Datatime::operator+(int add_days) const
{
    Datatime res;
    res.day = this->day + add_days;
    return res;
}


bool Datatime::operator>(const Datatime& srav_day) const 
{ 
    return day > srav_day.day; 
}
bool Datatime::operator<(const Datatime& srav_day) const 
{ 
    return day < srav_day.day;
 }
bool Datatime::operator>=(const Datatime& srav_day) const 
{ 
    return day >= srav_day.day; 
}
bool Datatime::operator<=(const Datatime& srav_day) const 
{ 
    return day <= srav_day.day;
}
bool Datatime::operator==(const Datatime& srav_day) const 
{
    return day == srav_day.day; 
}

// outpute console
ostream& operator<<(ostream& out, const Datatime& dt) {
    if (dt.day < 0) { out << "incorrect data"; return out; }

    double d_int = floor(dt.day);
    long L = (long)d_int + 68569;
    long N = (4 * L) / 146097;
    L = L - (146097 * N + 3) / 4;
    long I = (4000 * (L + 1)) / 1461001;
    L = L - (1461 * I) / 4 + 31;
    long J = (80 * L) / 2447;
    int d = L - (2447 * J) / 80;
    int m = J + 2 - (12 * (J / 11));
    int year = 100 * (N - 49) + I + (J / 11);

 
    double frac = dt.day - d_int;
    int total_s = (int)(frac * 86400 + 0.5);
    int hh = total_s / 3600;
    int mm = (total_s % 3600) / 60;
    int ss = total_s % 60;

    auto p2 = [&](int n) { if (n < 10) out << "0"; out << n; };
    out << year << "-" << (m < 10 ? "0" : "") << m << "-" << (d < 10 ? "0" : "") << d;
    out << " T"; p2(hh); out << ":"; p2(mm); out << ":"; p2(ss);

    return out;
}

