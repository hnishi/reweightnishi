#include"nlib.h"

// constant values
#define GAS_CONST 8.31451  // gas constant, R ( joule/mol*k )
//#define BOLTZMAN_CONST 1.380658e-23  // Boltzman constant, kb ( joule/k )
#define BOLTZMAN_CONST 8.3144621  // Boltzman constant, kb ( joule/k*mol )
// kb = R / Na, where Na is Avogadro constant (6.02214129e-23)
#define JOULE_CALORIE 4.184 // joule-calorie conversion unit


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
  Inp_nishi inp1( argv[1] );

// ############# READ INPUT  ########################################
/* (1) 
 * 
 */
   cout<<endl<<"------- (1) load --------- \n";

   string infile = inp1.read("INFILE"); 
   string inprob = inp1.read("INPROB");  

   cout<<"# output"<<endl;
   string outpmf = inp1.read("OUTPMF");

   cout<<"#  settings"<<endl;
   int frame = atoi( inp1.read("NUMSTRUCTURE").c_str() );


/*  OPEN FILE  
*/
  float tmp;

  ifstream ifs1(infile.c_str(),ifstream::in);
  if(ifs1.fail()){
    cerr<<"cannot open file "<<infile<<endl;
    //exit(1);
    return 1;
  }

  vector<float> c1, c2, pote;
  //while(!ifs.eof()){
  //while(ifs.good()){
  for(int ii=0;ii<frame;ii++){
    ifs1 >> tmp;
    c1.push_back(tmp);
    ifs1 >> tmp;
    c2.push_back(tmp);
    ifs1 >> tmp;
    pote.push_back(tmp);
  }

  ifs1.close();

  cout<<"DEBUG: pote.size() = "<<pote.size()<<endl;
  cout<<"DEBUG: pote[pote.size() -1] = "<<pote[pote.size() -1]<<endl;


  ifstream ifs2(inprob.c_str(),ifstream::in);
  if(ifs2.fail()){
    cerr<<"cannot open file "<<inprob<<endl;
    //exit(1);
    return 1;
  }

  vector<float> ene_prob, prob;
    ifs2 >> tmp;  //why outside of while-loop? because of ifs.eof 
  while(!ifs2.eof()){
  //while(ifs2.good()){
    ene_prob.push_back(tmp);
    ifs2 >> tmp;
    prob.push_back(tmp);
    ifs2 >> tmp;
  }

  ifs2.close();

  //cout<<"DEBUG: prob.size() = "<<prob.size()<<endl;
  //cout<<"DEBUG: prob[prob.size() -1] = "<<prob[prob.size() -1]<<endl;
  //cout<<"DEBUG: ene_prob.size() = "<<ene_prob.size()<<endl;
  //cout<<"DEBUG: ene_prob[ene_prob.size() -1] = "<<ene_prob[prob.size() -1]<<endl;

/* (2)  assignment of probability
 *
 * */
   cout<<endl<<"------- (2) assignment of probability --------- \n";
   
   int check_flat[ene_prob.size()];
   for(unsigned int i=0;i<ene_prob.size();i++){
      check_flat[i] = 0; //initializing by zero
   }
   vector<float> prob2;
   for(int ii=0;ii<frame;ii++){
      for(unsigned int jj=0;jj<ene_prob.size();jj++){
         if( pote[ii] < ene_prob[jj] ){
	    prob2.push_back( prob[jj] );
	    check_flat[jj] ++ ;
	    break;
	 }
      }
   }
   if( prob2.size() != frame ){
      cout<<"WARNING: assignment of probability failed \n";
      cout<<"num of assigned = "<<prob2.size()<<endl;
   }
   else{
      cout<<"assignment of probability was ended successfully"<<endl;
   }
/*  OUTPUT FILE
*/
  ofstream ofs1;
  ofs1.open( inp1.read("OUTPROB").c_str() );
  for(unsigned int i = 0;i<prob2.size();i++){
     ofs1<<prob2[i]<<"\n";
  }
  ofs1.close();


/* (7) PMF calculation
 *
 * */
   cout<<endl<<"REPORT> (7) PMF calculation \n";
   //string pmfcalculation  = inp1.read("PMFCALCULATION");
   string pmfcalculation  = "YES";
   if( pmfcalculation == "YES"){

   double length_bin = atof(inp1.read("BINSIZE").c_str());
   float emin = atof(inp1.read("MINCOORD").c_str());
   float temperature = atof(inp1.read("TEMPERATURE").c_str());
   int num_bin = atoi(inp1.read("NUMBIN").c_str());
   
   cout<<"Range: "<<emin<<" to "<<emin+length_bin*num_bin<<endl;
   cout<<"Num of Partitions = NUMBIN*NUMBIN = "<<num_bin*num_bin<<endl;

   double pmf[num_bin][num_bin];
   for(int i=0;i<num_bin;i++){  //initialize array
      for(int j=0;j<num_bin;j++){
         pmf[j][i] = 0;
      }
   }
   int count_pmf = 0; float normcons = 0;
   for(unsigned int n=0;n<frame;n++){ //count
      for(int i=0;i<num_bin;i++){
         for(int j=0;j<num_bin;j++){
            if(c1[n] > emin + length_bin * j 
 	    && c1[n] <= emin + length_bin * (j + 1) 
	    && c2[n] > emin + length_bin * i
	    && c2[n] <= emin + length_bin * (i + 1)     ){
	       //pmf[j][i] ++ ;
	       pmf[j][i] = pmf[j][i] + prob2[n] ;
	       count_pmf ++ ;
	       normcons = normcons + prob2[n];
	       //goto NEXT_PMF;
	    }
         }
      }

//NEXT_PMF:
   //continue;
   }
   cout<<"count_pmf / frame = "<<count_pmf<<" / "<<frame<<endl;
   if( count_pmf != (int)frame )cout<<"WARNING: count_pmf != frame; "<<count_pmf<<" != "<<frame<<endl;
   double min_pmf = 999999, max_pmf = -999999; 
   for(int i=0;i<num_bin;i++){ //normalization
      for(int j=0;j<num_bin;j++){
         //pmf[j][i] = pmf[j][i] / frame;
         pmf[j][i] = pmf[j][i] / normcons;
         if( pmf[j][i] <= min_pmf ){
            min_pmf = pmf[j][i];
         }
         if( pmf[j][i] >= max_pmf ){
            max_pmf = pmf[j][i];
         }
      }
   }
   cout<<"Maximum Probability = "<<max_pmf<<endl;
   cout<<"Minimum Probability = "<<min_pmf<<endl;

   //double const_boltz = 1.380658e-23, pmf_temp = 300;
   min_pmf = 999999, max_pmf = -999999; 
   int min_pmf_n[2]; double min_pmf_c[2];
   min_pmf_n[0] = 0; min_pmf_n[1] = 0;
   int max_pmf_n[2]; double max_pmf_c[2];
   max_pmf_n[0] = 0; max_pmf_n[1] = 0;
   for(int i=0;i<num_bin;i++){ //PMF calculation
      for(int j=0;j<num_bin;j++){
         if( pmf[j][i] == 0 ){
	    //pmf[j][i] = 100;  
	    continue;
	 }
         pmf[j][i] = -1 * BOLTZMAN_CONST * temperature * log( pmf[j][i] );
         if( pmf[j][i] < min_pmf ){
            min_pmf = pmf[j][i];
            min_pmf_n[0] = j; min_pmf_n[1] = i;
         }
         if( pmf[j][i] > max_pmf ){
            max_pmf = pmf[j][i];
            max_pmf_n[0] = j; max_pmf_n[1] = i;
            //cout<<"DEBUG> max_pmf = "<<max_pmf<<", max_pmf_n[0], max_pmf_n[1] = "<<max_pmf_n[0]<<", "<<max_pmf_n[1]<<endl;
         }
      }
   }
   min_pmf_c[0] = emin + min_pmf_n[0] * length_bin + length_bin / 2;
   min_pmf_c[1] = emin + min_pmf_n[1] * length_bin + length_bin / 2;
   max_pmf_c[0] = emin + max_pmf_n[0] * length_bin + length_bin / 2;
   max_pmf_c[1] = emin + max_pmf_n[1] * length_bin + length_bin / 2;
   
   cout<<"Maximum PMF = "<<max_pmf-min_pmf<<" (J/mol) = "<<(max_pmf-min_pmf)/JOULE_CALORIE/1000<<" (kcal/mol)\n";
   cout<<"Minimum PMF = "<<min_pmf-min_pmf<<" (J/mol) = "<<(min_pmf-min_pmf)/JOULE_CALORIE/1000<<" (kcal/mol)\n";
   cout<<"(c1, c2) of Maximum PMF = ("<<max_pmf_c[0]<<", "<<max_pmf_c[1]<<")\n"; 
   cout<<"(c1, c2) of Minimum PMF = ("<<min_pmf_c[0]<<", "<<min_pmf_c[1]<<")\n"; 
   
   FILE *fout;
   
   string outpmf = inp1.read("OUTPMF");
   if((fout = fopen( outpmf.c_str(),"w" )) == NULL ){
      printf("cannot open output file: %s\n", outpmf.c_str() );
      return 1;
   }
   for(int i=0;i<num_bin;i++){
      for(int j=0;j<num_bin;j++){
         if( pmf[j][i] == 0 ){
         //fprintf(fout,"%12.3f%12.3f%12.3f \n", emin + length_bin * j + length_bin / 2, emin + length_bin * i + length_bin / 2, 0.0 );}else{
         fprintf(fout,"%12.3f%12.3f%12.3f \n", emin + length_bin * j + length_bin / 2, emin + length_bin * i + length_bin / 2, 100.0 );
         }
         else{
         //fprintf(fout,"%12.3f%12.3f%12.3f \n", emin + length_bin * j + length_bin / 2, emin + length_bin * i + length_bin / 2, (pmf[j][i] - max_pmf) / JOULE_CALORIE /1000 );
         fprintf(fout,"%12.3f%12.3f%12.3f \n", emin + length_bin * j + length_bin / 2, emin + length_bin * i + length_bin / 2, (pmf[j][i] - min_pmf) / JOULE_CALORIE /1000 );
         }
      }
      fprintf(fout,"\n");
   }
   fclose( fout );
   cout<<"output "<<outpmf<<endl;
   }
//end:

// END
        return 0;
}
