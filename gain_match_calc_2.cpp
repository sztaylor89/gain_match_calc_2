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
private:
  double x;//MeV
  double neutron_keVee;//keVee
 public:
    double CSchannel, COchannel;

  //calculates neutron keVee using Madey's/Cecil's formula
  x = (0.95*maxNeutronEnergy)-(8.0*(1-exp(-0.1*pow(maxNeutronEnergy,0.9))));
  neutron_keVee = x*1000;

  //calculates where to put edges
  CSchannel = CSedge * (maxChannel/neutron_keVee);
  COchannel = COedge * (maxChannel/neutron_keVee);
};

//function to calculate Compton Edge
  double Compton (double a)
  {
    double edge;//keV
    double eMass = 511;//keV
    edge = a-(a/(1+(2*a/eMass)));
    return edge;
  }


//calls the class to complete calculations
int main()
{
  //calculates compton edges
  double CSenergy = 662, COenergy = 1333;//keV
  double CSedge, COedge;//keVee
  CSedge = Compton(CSenergy);
  COedge = Compton(COenergy);

  //gathers user input on neutron energy and max channel
  double maxChannel, maxNeutronEnergy;//channels,MeV
  cout << "Enter maximum neutron energy(MeV): " << endl;
  cin >> maxNeutronEnergy;
  cout << "Enter maximum histogram channel(default=8192): " << endl;
  cin >> maxChannel;
  
  Location CS;
  Location CO;

  //Outputs where to place compton edge
  cout << "Place Compton edge in QDC spectrum here: " << endl;
  cout << "137Cs in channel " << Location.CS << ", 60Co in channel " << Location.CO << endl;
  return 0;
}
