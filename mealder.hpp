struct Mealder 
{
    static const unsigned int sd = 2;
    const unsigned int d = 2; 
    unsigned const tmax;
    Float alpha = 1;
	Float beta  = 2;
	Float gamma = 0.5;
	Float delta = 0.5;
    std::vector<HenonMap> verts;
    
    HenonMap cent;
    HenonMap xr;
    HenonMap xe;
    HenonMap xoc;
    HenonMap xic;


    Mealder(const unsigned t1) : tmax(t1), verts(d+1) 
    {
        for(auto& x: verts) x = HenonMap(tmax);

        SORT();
        CENTROID();
    }

//vector verts: [x1, x2, x3]
//vector props: [centroid, xr, xe, xoc, xic]


    void SORT(){
        HenonMap temp(tmax);

		for(unsigned i = 0; i < d+1 ; i++)
		{
			for (unsigned j = i+1; j < d+1; j++)
			{
				if (verts[i].t > verts[j].t)
				{
					temp    = verts[i];
					verts[i]= verts[j];
					verts[j]= temp;
				}}}
    }

    void CENTROID(){
		for(unsigned j = 0; j < d; j++)
		{
			for(unsigned i = 0; i < d; i++)
			{
				props[0].r[j] += verts[i].r[j] / d ;
			}}
        props[0].TIME();
	}	

    void REFLECT(){
        for(unsigned i = 0; i < d; i++)
			props[1].r[i] = props[0].r[i] + alpha*(props[0].r[i]-verts[d].r[i]);
        props[1].TIME();
    }

    void EXPAND(){
       	for(unsigned i = 0; i < d; i++)
       		props[2].r[i] = props[0].r[i] + beta*(props[1].r[i]-props[0].r[i]);
        props[2].TIME();
    }

    void OUT_CONTRACT(){
       	for(unsigned i = 0; i < d; i++)
       		props[3].r[i] = props[0].r[i] + gamma*(props[1].r[i]-props[0].r[i]);
        props[3].TIME();
    }

    void IN_CONTRACT(){
       	for(unsigned i = 0; i < d; i++)
       		props[4].r[i] = props[0].r[i] - gamma*(props[1].r[i]-props[0].r[i]);
    }

	void SHRINK(){
	       	for(unsigned j = 0; j < d; j++){
		    	for(unsigned i = 1; i < d+1; i++)
	           			verts[i].r[j] = verts[0].r[j] + delta*(verts[i].r[j]-verts[0].r[j]);}
	}

    void NelderMeadStep(){
        REFLECT();

        if (verts[0].t <= props[1].t && props[1].t < )
            verts[d].set(props[1].r, props[1].t)

        else if(props[1].t)
    }       

};
