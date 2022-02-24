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

/* class Station   */

class Station{
protected:
    string station;
    Patient *patient;
public:
    Station(string s, Patient *p):
        station(s),
        patient(p)
    {}
    virtual ~Station(){}
    virtual void enter(Patient*)=0;
    virtual Patient* leave() = 0;
    virtual void print() = 0;
};

/* class WaitingArea */

class WaitingArea: public Station{
private:
    class Waiting{
    public:
        Patient *patient;
        Waiting *next;
        Waiting(Patient *p):
            patient(p),
            next(nullptr)
        {}
    };
    int count;
    Waiting *waiting;
public:
    WaitingArea(string s):
        Station(s, patient),
        count(0),
        waiting(nullptr)
    {}
    virtual void enter(Patient *p){

        if (waiting == nullptr){
            waiting->patient = p;
            count++;
        }else{
            waiting->next->patient = p;
            count++;
        }
    }
    virtual Patient* leave(){
        if (count == 0){
            throw SimError("no patient waiting in"+station);
        }else{
            Patient* pt = waiting->patient;
            waiting = waiting->next;
            count--;
            return pt;
        }
    }

    virtual void print(){
        cout<<station<<": "<<count<<" waiting patients: ";
        while(waiting != nullptr){
            cout<<waiting->patient->get_id()<<endl;
            waiting = waiting->next;
        }
    }

};

class Single: public Station{
private:
    int total;
public:
    Single(string s):
        Station(s),
        total(0)
    {}
    int get_total(){
        return total;
    }
    virtual void enter(Patient *p){
        cout<<"enters"<<Station::station;
        total++;
        p->switch_briefed();
    }
    virtual Patient* leave(){
        cout<<"leaves"<<Station::station;
        return Station::patient;
    }
};
