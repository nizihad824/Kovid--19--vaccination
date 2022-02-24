#include<bits/stdc++.h>
using namespace std;
enum Vaccine {astra,biontech,moderna,none};
// output operator 
ostream& operator <<(ostream& out ,Vaccine& v){
   switch(v)
    {
    case astra:
        return out<<"AstraZeneca";
    case biontech:
        return out<<"BioNTech";

    case moderna:
        return out<<"Moderna";
    case none:
        return out<<"none";
    }
}

//  class SimError 
class SimError:public exception {
public:
    string reason;
    SimError(string r):
        reason(r)
    {}
};
// class Patient
class Patient{
private:
    int no;
    const int id;
    bool briefed;
    Vaccine vaccine;

public:
    Patient();
    int get_id();
    bool is_briefed();
    void switch_briefed();
    void set_vaccinated(Vaccine);
    friend ostream& operator<<(ostream&, Patient&);
};

//  class and member function defination outside the class
Patient::Patient():
    id(no++),
    briefed(!briefed),
    vaccine(Vaccine::none)
{}

int Patient::get_id(){
    return id;
}

bool Patient::is_briefed(){
    return briefed;
}

void Patient::switch_briefed(){
    briefed =!briefed;
}

void Patient::set_vaccinated(Vaccine v){
    vaccine = v;
}

ostream& operator<<(ostream& out, Patient& p){
    out<<"patient "<<p.get_id();
    if (p.is_briefed() == false){
        out<<" vaccinated with "<<p.vaccine;
    }else{
        out<<" briefed";
    }
    return out;
}