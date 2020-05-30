struct Simulation {
  unsigned const      tmin;
  unsigned const      tmax;
  HenonMap            walker;
  HenonMap            proposal;
  std::vector<Float>  HISTO;
  std::vector<Float>  SIGMA;
  std::vector<Float>  S;
  unsigned            FLAG;
  Float               f;
  Float               ef;
  Float               delta;
  unsigned            count;
  
  Simulation(const unsigned t0, const unsigned t1 ) :
    tmin(t0), tmax(t1), walker(tmax), proposal(tmax),
    HISTO(tmax + 1), SIGMA(tmax + 1), S(tmax + 1)  {


    for(auto& x: S     ) x = 0.0;
    for(auto& x: SIGMA ) x = 1.0;
    for(auto& x: HISTO ) x = 0.0;
    
    f = 0.01;
    ef = exp(f);
    FLAG = 1;
    count = 0;
  };
  
  void Propose()
  {
    Float d;
    delta = 0;
    for(unsigned i = 0; i < walker.d; i++)
      {
	d = - SIGMA[walker.t] * log(mpfr::random());
	proposal.r[i] = walker.r[i] +  (mpfr::random() > 0.5 ? -d : d);
	delta += d;
	proposal.r[i] += (proposal.r[i] > proposal.r_max[i] ? - proposal.box_width[i] : 0);
	proposal.r[i] += (proposal.r[i] < proposal.r_min[i] ? + proposal.box_width[i] : 0);
      }
    proposal.TIME();
  }
  
  Float ACCEPT()
  {
    Float  si = 1/SIGMA[walker.t];
    Float  sp = 1/SIGMA[proposal.t];
    Float ds =  S[proposal.t] - S[walker.t];
    if(proposal.t > 0)
      return (sp/si) * exp(delta * (si - sp )  - ds);
    else
      return 0;
  }
  
  void MonteCarloStep()
  {
    Float Pa, d;
    
    Propose();
    SIGMA[walker.t] *= ( proposal.t < walker.t ? 1/ef : (SIGMA[walker.t] < 1/ef ?  ef : 1 ));
    Pa = ACCEPT();
    if(Pa > 1 or  mpfr::random() < Pa)
      {
	walker.set(proposal.r, proposal.t);
	
	if(walker.t == tmax and FLAG == 1)
	  { 
	    FLAG = 0;
	    count++;
	  }
	
	if(walker.t == tmin and FLAG == 0)
	  FLAG = 1;

      }
//    printf(walker.t);

    S[walker.t] += f;
    HISTO[walker.t] += 1;
  }
  
  void decreasef()
  {
    f = f/2;
    ef = exp(f);
    for(auto& x: HISTO ) x = 0.0;
    count = 0;
  }
  
};


