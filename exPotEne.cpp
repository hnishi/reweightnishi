#include"nlib.h"
//#include"math_nishi.h"

// constant values
#define GAS_CONST 8.31451  // gas constant, R ( joule/mol*k )
//#define BOLTZMAN_CONST 1.380658e-23  // Boltzman constant, kb ( joule/k )
#define BOLTZMAN_CONST 8.3144621  // Boltzman constant, kb ( joule/k*mol )
// kb = R / Na, where Na is Avogadro constant (6.02214129e-23)
#define JOULE_CALORIE 4.184 // joule-calorie conversion unit


/* ********************************************
 *  extract potential energy from trajectory 
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
   Inp_nishi inp1( argv[1] );
   
/* (1) load trajectory by tra_nishi
 * 
 */
   //cout<<endl<<"REPORT> (1) load trajectory \n";
   cout<<endl<<"--- TRAJECTORY INFORMATION --- \n";
   string pdbname = inp1.read("REFPDBNAME");
   string pcaatom = inp1.read("PCAATOM") ;
   int stride = atoi(inp1.read("STRIDE").c_str());
   int startframe = atoi( inp1.read("STARTFRAME").c_str() ) - 1 ;
   string superpbase = inp1.read("SUPERPBASE");   //v.1.1.0

   if(stride <= 0){
      return -1;
   }

   
   cout<<"\n--- LOADING STRUCTURE ENSEMBLES --- \n";
   cout<<"Reading COD "<<endl;
   tra_nishi* tra1;
   vector<double> potent;
   string cod_num, codname;  char buf[32];
   int cod_num_i=1;
   codname = inp1.read( "COD1" );

   while( codname != "nothing" ){
      cout<<"\nReading "<<codname<<endl;
      tra1 = new tra_nishi(codname.c_str(), pdbname.c_str(), stride, pcaatom);

      cout<<"TOTAL FRAME = "<<tra1->total_step<<endl;
      cout<<"TOTAL ATOM = "<<tra1->pdb1->total_atom<<endl;
      cout<<"TOTAL SELECTED ATOM = "<<tra1->total_sel<<endl;
   
      cout<<"initial potential = "<<tra1->potent[0]<<endl;
      for(unsigned int n=startframe;n<tra1->total_step;n++){
         potent.push_back( tra1->potent[n] );
      }
      cout<<"initial potent 2 = "<<potent[0]<<endl;

      delete tra1;
      cod_num_i++;
      sprintf(buf,"COD%d",cod_num_i);  //itoa()
      cod_num = buf;
      codname = inp1.read(cod_num);
   }
   cout<<"Section of reading trajectories was ended normaly\n";
   cout<<"\nTOTAL STRUCTURE = "<<potent.size()<<endl;

   cout<<"\n--- WRITING POTENTIAL ENERGIES --- \n";
/*  OUTPUT FILE
*/
   ofstream ofs;
   ofs.open( inp1.read("OUTFILE").c_str() );

   for(unsigned  int i = 0;i<potent.size();i++){
      ofs<<potent[i]<<"\n";
   }

   ofs.close();


// END
   cout<<"\n\nit took "<<(float)clock()/CLOCKS_PER_SEC<<" sec of CPU to execute this program"<<endl;
   return 0;
}
