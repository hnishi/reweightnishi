#include"nlib.h"
#include"math_nishi.h"

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
   Inp_nishi inp1( argv[1] );

// ############# READ INPUT  ########################################
/* (1) 
 * 
 */
   //cout<<endl<<"REPORT> (1) load trajectory \n";


/* (7) PMF calculation
 *
 * */
   cout<<endl<<"REPORT> (7) PMF calculation \n";
   string pmfcalculation  = inp1.read("PMFCALCULATION");
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
   int count_pmf = 0;
   for(unsigned int n=0;n<frame;n++){ //count
      for(int i=0;i<num_bin;i++){
         for(int j=0;j<num_bin;j++){
            if(c1[n] > emin + length_bin * j 
 	    && c1[n] <= emin + length_bin * (j + 1) 
	    && c2[n] > emin + length_bin * i
	    && c2[n] <= emin + length_bin * (i + 1)     ){
	       pmf[j][i] ++ ;
	       count_pmf ++ ;
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
         pmf[j][i] = pmf[j][i] / frame;
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
