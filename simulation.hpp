struct Simulation {
  unsigned const      tmin;
  unsigned const      tmax;
  HenonMap            walker;
  HenonMap            proposal;
  std::vector<Float>  HISTO;
//  std::vector<Float>  SIGX;
//  std::vector<Float>  SIGY;
  std::vector<Float>  S;
  std::array<std::vector<Float>,2> SIG;
  unsigned            FLAG;
  Float               f;
  Float               ef;
  Float               delta;
  unsigned            count;
  unsigned            steps;
  unsigned            dir;
  
  Simulation(const unsigned t0, const unsigned t1 ) :
    tmin(t0), tmax(t1),  walker(tmax), proposal(tmax),
    HISTO(tmax + 1), 
//    SIGX(tmax + 1), SIGY(tmax + 1),
    S(tmax + 1){

    std::vector<Float> sig(tmax + 1);
    for(auto& x: S     ) x = 0.0;
    for(auto& x: sig   ) x = 1.0;
    for(auto& x: HISTO ) x = 0.0;
    
    for(unsigned i = 0; i < 2; i++)
        SIG[i]=sig ;

    f = 0.01;
    ef = exp(f);
    FLAG = 1;
    count = 0;
    steps = 0;
  };
  
  void PROPOSE()
  {
    delta = 0;

	dir = (mpfr::random() < 0.5 ? 0 : 1);

    for(unsigned i = 0; i < walker.d; i++)
        proposal.r[i] = walker.r[i];

    proposal.r[dir] += SIG[dir][walker.t]*mpfr::grandom();

    for(unsigned i = 0; i < walker.d; i++){
	    proposal.r[i] += (proposal.r[i] > proposal.r_max[i] ? - proposal.box_width[i] : 0);
	    proposal.r[i] += (proposal.r[i] < proposal.r_min[i] ? + proposal.box_width[i] : 0);
    }

    proposal.TIME();

    SIG[dir][walker.t] *= ( proposal.t < walker.t ? 1/ef : (SIG[dir][walker.t] < 1/ef ?  ef : 1 ));
  }
  
  Float ACCEPT()
  {
    Float sigw = SIG[dir][walker.t];
    Float sigp = SIG[dir][proposal.t];

    Float dr = pow(walker.r[dir]-proposal.r[dir],2);

    Float pow_walker   = dr/2/pow(sigw, 2);
    Float pow_proposal = dr/2/pow(sigp, 2);

    Float ds =  S[proposal.t] - S[walker.t];

    if(proposal.t > 0)
        return (sigw / sigp) * exp(-pow_proposal + pow_walker  - ds);
    else
        return 0;
  }
  
  void MonteCarloStep()
  {
    steps++;
    Float Pa;
    
    PROPOSE();
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


