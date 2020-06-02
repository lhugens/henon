struct Simulation_temp {
  unsigned const      tmin;
  unsigned const      tmax;
  HenonMap            walker;
  HenonMap            proposal;
  std::vector<Float>  HISTO;
  std::vector<Float>  SIG;
  std::vector<Float>  S;
  unsigned            FLAG;
  Float               f;
  Float               ef;
  Float               delta;
  unsigned            count;
  unsigned            steps;
  
  Simulation_temp(const unsigned t0, const unsigned t1 ) :
    tmin(t0), tmax(t1), walker(tmax), proposal(tmax),
    HISTO(tmax + 1), SIG(tmax + 1), S(tmax + 1)  {


    for(auto& x: S     ) x = 0.0;
    for(auto& x: SIG   ) x = 1.0;
    for(auto& x: HISTO ) x = 0.0;
    
    f = 0.01;
    ef = exp(f);
    FLAG = 1;
    count = 0;
    steps = 0;
  };
  
    void PROPOSE()
  {
    delta = 0;
    
    for(unsigned i = 0; i < walker.d; i++)
        proposal.r[i] = walker.r[i] + SIG[walker.t]*mpfr::grandom();

    for(unsigned i = 0; i < walker.d; i++){
	    proposal.r[i] += (proposal.r[i] > proposal.r_max[i] ? - proposal.box_width[i] : 0);
	    proposal.r[i] += (proposal.r[i] < proposal.r_min[i] ? + proposal.box_width[i] : 0);
    }

    proposal.TIME();
  }
  
  Float ACCEPT()
  {
    Float sigw2 = pow(SIG[walker.t],2);   
    Float sigp2 = pow(SIG[proposal.t],2);

    Float dx = pow(walker.r[0]-proposal.r[0],2);
    Float dy = pow(walker.r[1]-proposal.r[1],2);

    Float root_walker   = (dx+dy)/2/sigw2;
    Float root_proposal = (dx+dy)/2/sigp2;

    Float ds =  S[proposal.t] - S[walker.t];

    if(proposal.t > 0)
        return (sigw2 / sigp2) * exp(-root_proposal + root_walker  - ds);
    else
        return 0;
  }
  
  void MonteCarloStep()
  {
    steps++;
    Float Pa;
    
    PROPOSE();
    SIG[walker.t] *= ( proposal.t < walker.t ? 1/ef : (SIG[walker.t] < 1/ef ?  ef : 1 ));

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
    steps = 0;
  }
  
};
