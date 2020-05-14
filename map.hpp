struct HenonMap
{
  static const unsigned int d = 2;
  std::vector<Float>        r;
  std::vector<Float>        r1;
  unsigned                  t;
  unsigned                  limit;
  std::vector<Float>        r_min;
  std::vector<Float>        r_max;
  std::vector<Float>        box_width;  
  Float                     k = 6;

  HenonMap(unsigned tt) : r(d), r1(d), limit(tt), r_min(d), r_max(d), box_width(d) 
  {
    for(unsigned i = 0; i < d; i++)
      {
        r_min[i] = -5;
        r_max[i] = 9;
        box_width[i] = r_max[i] - r_min[i];
        r[i] = r_min[i] + mpfr::random() * box_width[i];
      }
    TIME();
  }

  HenonMap(){}
  
  
  bool escaped() const
  {
    for(unsigned i = 0; i < d; i++)
      if(r1[i] < r_min[i]  || r1[i] > r_max[i] )
	      return true;
    return false;
  }
  
  void TIME()
  {	
    t = 0;
    r1 = r;
    Float x;

    while( !escaped() && t < limit )
      {	
        x = r1[0];
        r1[0] = k - pow(x,2) - r1[1];
        r1[1] = x;
        t++;
      }
  }
  
  void set( std::vector<Float> & r1, unsigned t1 )
  {
    t = t1;
    for(unsigned i = 0; i < d; i++)
      r[i] = r1[i];
  }
  
};
