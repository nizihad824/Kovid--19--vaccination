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