# reweightnishi
reweighting from pcanishi

(1) How to use

1_lnPtoP.bash
	input: 
	 P_E_T300.dat (derived from gen_p_cano_McMD/ programs made by Higo-san)
	   including ln(P(E,T=300)), logarithm of probability
	output:
	 Potential energy vs Probability data
   exchange lnP to P

2_exPotEne.bash
	input:
	 inp_exPotEne.inp
	output:
	 Potential energy of each structures
   extract potential energy from trajectory file
   and marge it with corrdinates that derived from principal component analysis

3_do_pmfnishi.bash
	input:
	 inp_pmf.inp
	   results of 1_bash and 2_bash
	output:
	 out_pmf.dat
	   free energy landscape
   calculate potential of mean force, considering porobability destribution at arbitrary temperature.

