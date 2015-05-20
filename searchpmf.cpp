#include"nlib.h"


/* ********************************************
 *  reweighting and pmf calculation at room temperature  
 * ********************************************/
int main(int argc, char *argv[]){
// INPUT_PARAMETERS
// argv[1]: input parameter file
  if( argv[1]==NULL ){
    puts("No ARGUMEMTS");
    puts("USAGE: ./a.out (argv[1]: input parameter file)" );
    return 1;
  }
  cout<<"Your input-parameter file: "<<argv[1]<<endl;
  Inp_nishi inp01( argv[1] ); //added 2015.05.20
  Inp_nishi inp1( inp01.read("INPPMF").c_str() );

// ############# READ INPUT  ########################################
/* (1) 
 * 
 */
   cout<<endl<<"------- (1) load --------- \n";

   string infile = inp1.read("INFILE"); 
   //string inprob = inp1.read("INPROB");  

   cout<<"# output"<<endl;
   string outfile = inp01.read("OUTFILE");

   cout<<"#  settings"<<endl;
   int frame = atoi( inp1.read("NUMSTRUCTURE").c_str() );
   float coordc1 = atof( inp01.read("COORDC1").c_str() );
   float coordc2 = atof( inp01.read("COORDC2").c_str() );


/*  OPEN FILE  
*/
  //float tmp;
  long double tmp;

  ifstream ifs1(infile.c_str());
  //ifstream ifs1(infile.c_str(),ifstream::in);
  if(ifs1.fail()){
    cerr<<"cannot open file "<<infile<<endl;
    //exit(1);
    return 1;
  }

  vector<float> c1, c2;//, pote;
  //while(!ifs.eof()){
  //while(ifs.good()){
  for(int ii=0;ii<frame;ii++){
    ifs1 >> tmp;
    c1.push_back(tmp);
    ifs1 >> tmp;
    c2.push_back(tmp);
    ifs1 >> tmp;
    //pote.push_back(tmp);
  }

  ifs1.close();

  cout<<"DEBUG: c1.size() = "<<c1.size()<<endl;
  cout<<"DEBUG: c1[c1.size() -1] = "<<c1[c1.size() -1]<<endl;


   cout<<endl<<"REPORT> search \n";


   double length_bin = atof(inp1.read("BINSIZE").c_str());
   float emin = atof(inp1.read("MINCOORD").c_str());
   int num_bin = atoi(inp1.read("NUMBIN").c_str());
   
   cout<<"Range: "<<emin<<" to "<<emin+length_bin*num_bin<<endl;
   cout<<"Num of Partitions = NUMBIN*NUMBIN = "<<num_bin*num_bin<<endl;

/*  structure list
*/
   cout<<"\n\nWrite structure-number of the bin \n";
   cout<<"information of bin to search"<<endl;
   cout<<"bin center: "<<coordc1<<", "<<coordc2<<endl;
   cout<<"c1 range: "<<coordc1 - length_bin/2<<" - "<<coordc1 + length_bin/2<<endl;
   cout<<"c2 range: "<<coordc2 - length_bin/2<<" - "<<coordc2 + length_bin/2<<endl;

   vector<int> stru;
   for(unsigned int n=0;n<frame;n++){ //count
            if(c1[n] >  coordc1 - length_bin / 2 
 	    && c1[n] <= coordc1 + length_bin / 2 
	    && c2[n] > coordc2 - length_bin / 2
	    && c2[n] <= coordc2 + length_bin / 2    ){
	       cout<<n+1<<endl;
               stru.push_back(n+1);
            }
   }
   cout<<"\nthe number of found structures = "<<stru.size()<<endl;

/* output
*/
  ofstream ofs1;
  ofs1.open( outfile.c_str() );
  for(unsigned int i = 0;i<stru.size();i++){
     ofs1<<stru[i]<<"\n";
  }
  ofs1.close();

// END
   cout<<"\n\nit took "<<(float)clock()/CLOCKS_PER_SEC<<" sec of CPU to execute this program"<<endl;
   return 0;
        return 0;
}
