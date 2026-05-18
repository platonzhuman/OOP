#include <iostream>
#include "moon_data_time.h"
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



// FOR MOON

Datatime::Datatime(int ymd, int hms) {
    int y = ymd / 10000;           
    int m = (ymd / 100) % 100;     
    int d = ymd % 100;             
    
    int hh = hms / 10000;          
    int mm = (hms / 100) % 100;    
    int ss = hms % 100;            
    
    if (is_ok(y, m, d) && is_ok_time(hh, mm, ss)) {
        day = date(y, m, d) + (hh / 24.0 + mm / 1440.0 + ss / 86400.0);
    } else {
        day = -1;
    }
}


// rebreading mon otdelenie

MoonEvents calculateMoonEvents(const Datatime t[3], const double e[3], const bool has[3], MoonEvents currentEvents) {
    if (!has[0] || !has[1]) return currentEvents;

    double p = e[0]; // предыдущая точка
    double c = e[1]; // текущая точка 

    // восход
    if (!currentEvents.hasRise && p < 0 && c >= 0) {
        currentEvents.rise = t[1];
        currentEvents.hasRise = true;
    }
    // заход
    if (!currentEvents.hasSet && p >= 0 && c < 0) {
        currentEvents.set = t[1];
        currentEvents.hasSet = true;
    }
    // пик
    if (has[2] && !currentEvents.hasCulm && p < c && c > e[2] && c > 0) {
        currentEvents.culm = t[1];
        currentEvents.hasCulm = true;
    }

    return currentEvents;
}


void printMoonEvents(FILE* f, const string& dateStr, int y, int m, int d) {
    int targetYmd = y * 10000 + m * 100 + d;  
    
    char buf[256];
    fgets(buf, sizeof(buf), f); // пропуск заголовка
    
    Datatime t[3];      
    double e[3];        
    bool has[3] = {false, false, false};  
    
    int ymd, hms;
    double tm, r, el, az, fi, lg;
    MoonEvents events;
    
    while (fscanf(f, "%d %d %lf %lf %lf %lf %lf %lf", 
                  &ymd, &hms, &tm, &r, &el, &az, &fi, &lg) == 8) {
        
        if (ymd != targetYmd) continue;
        
        
        t[0] = t[1];  e[0] = e[1];  has[0] = has[1];
        t[1] = t[2];  e[1] = e[2];  has[1] = has[2];
        t[2] = Datatime(ymd, hms);  e[2] = el;  has[2] = true;
        
        // вызов функции вычислений
        events = calculateMoonEvents(t, e, has, events);
    }
    
    cout << "дата: " << dateStr << endl;
    cout << "восход луны: " << (events.hasRise ? events.rise : Datatime()) << endl;
    cout << "пик луны: " << (events.hasCulm ? events.culm : Datatime()) << endl;
    cout << "заход Луны: " << (events.hasSet ? events.set : Datatime()) << endl;
}
