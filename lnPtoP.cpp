#include<iostream>
#include<vector> 
#include<string> // for vector<string>
//#include<stdlib.h> // for exit(1); error end
//#include<stdio.h>
//#include<string.h>
#include<fstream>
#include<cmath> // for sqrt(); square root

using namespace std;

int main(int argc,char *argv[]){
/*  ARGUMENTS  
  argv[1] : input file name
*/

/*  VARIABLES  
*/
  vector<double> ene,lnPin,Pout;
  double tmp;
  int numDat;
  const double e= 2.71828182845904524;

/*  OPEN FILE  
*/
  ifstream ifs(argv[1],ifstream::in);

  if(ifs.fail()){
    cerr<<"cannot open file "<<argv[1]<<endl;
    //exit(1);
    return 1;
  }

  int i = 0;
  //while(!ifs.eof()){
  while(ifs.good()){
    ifs >> tmp;
    ene.push_back(tmp);
    ifs >> tmp;
    lnPin.push_back(tmp);
    if(ene[i]==999999&&lnPin[i]==999999){break;}
    cout<<ene[i]<<"  "<<lnPin[i]<<endl;
    tmp = 999999;
    i++;
  }
  numDat = i;
  cout<<"Number of Data = "<<numDat<<endl;

  ifs.close();

/*  CALCULATE  Pc = exp(ln(Pc))
*/
  for(i = 0;i<numDat;i++){
    Pout.push_back( pow(e,lnPin[i]) );
  }

/*  OUTPUT FILE
*/
  ofstream ofs;
  ofs.open(argv[2]);

  for(i = 0;i<numDat;i++){
  ofs<<ene[i]<<"  "<<Pout[i]<<"\n";
  }

  ofs.close();

/* END
*/
	cout<<"\nit took "<<(float)clock()/CLOCKS_PER_SEC<<" sec of CPU to execute this program"<<endl;
	return 0;
}
