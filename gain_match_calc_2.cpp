//Program for calculating where to put the gamma peak
//to gain match VANDLE bars.
//
//Written by S. Taylor, 2/23/16

#include <iostream>
#include <cmath>

using namespace std;


//Class for calculating peak location
class Location
{
public:
    Location();//constructor
    ~Location();//destructor
    double x;//MeV, placeholder for neutron electron equivalent info
    double neutron_keVee;//keVee
    double channel;//Channels
    double edge;//keVee
    double Compton(double gamma_energy);
    double Madey(double maxNeutronEnergy, double maxChannel, double edge);
};
//Constructor and Destructor
Location::Location(){}
Location::~Location(){}

//function to calculate Compton Edge
double Location::Compton (double gamma_energy)
{
    double eMass = 511;//keV
    edge = gamma_energy-(gamma_energy/(1+(2*gamma_energy/eMass)));
    return edge;
}

//calculates neutron keVee using Madey's/Cecil's formula and computes final channel
double Location::Madey(double maxNeutronEnergy, double maxChannel, double edge)
{
  x = (0.95*maxNeutronEnergy)-(8.0*(1-exp(-0.1*pow(maxNeutronEnergy,0.9))));
  neutron_keVee = x*1000;
  channel = edge * (maxChannel/neutron_keVee);
  return channel;
}

//calls the class to complete calculations
int main()
{
    double CSenergy = 662, COenergy = 1333;//keV
    double CSedge, COedge, CSchannel, COchannel;//keVee
    //gathers user input on neutron energy and max channel
    double maxChannel=8192.0, maxNeutronEnergy;//channels,MeV
    cout << "Enter maximum neutron energy(MeV): " << endl;
    cin >> maxNeutronEnergy;
    cout << "Enter maximum histogram channel(default: enter 8192): " << endl;
    cin >> maxChannel;

    Location CS, CO;
    CSedge=CS.Compton(CSenergy);
    COedge=CO.Compton(COenergy);
    CSchannel=CS.Madey(maxNeutronEnergy,maxChannel,CSedge);
    COchannel=CO.Madey(maxNeutronEnergy,maxChannel,COedge);

    //Outputs where to place compton edge
    cout << "Place Compton edge in QDC spectrum here: " << endl;
    cout << "137Cs in channel " << CSchannel << ", 60Co in channel " << COchannel << endl;
    cout << "keVee/Ch = " << CSedge/CSchannel << endl;
    return 0;
}
