struct Mealder 
{
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


    Mealder(const unsigned t1) : tmax(t1), verts(d+1), 
    cent(tmax), xr(tmax), xe(tmax), xoc(tmax), xic(tmax)
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
				cent.r[j] += verts[i].r[j] / d ;
			}}
        cent.TIME();
	}	

    void REFLECT(){
        for(unsigned i = 0; i < d; i++)
			xr.r[i] = cent.r[i] + alpha*(cent.r[i]-verts[d].r[i]);
        xr.TIME();
    }

    void EXPAND(){
       	for(unsigned i = 0; i < d; i++)
       		xe.r[i] = cent.r[i] + beta*(xr.r[i]-cent.r[i]);
        xe.TIME();
    }

    void OUT_CONTRACT(){
       	for(unsigned i = 0; i < d; i++)
       		xoc.r[i] = cent.r[i] + gamma*(xr.r[i]-cent.r[i]);
        xoc.TIME();
    }

    void IN_CONTRACT(){
       	for(unsigned i = 0; i < d; i++)
       		xic.r[i] = cent.r[i] - gamma*(xr.r[i]-cent.r[i]);
    }

	void SHRINK(){
	       	for(unsigned j = 0; j < d; j++){
		    	for(unsigned i = 1; i < d+1; i++)
	           			verts[i].r[j] = verts[0].r[j] + delta*(verts[i].r[j]-verts[0].r[j]);}
	}

    void NelderMeadStep(){
        REFLECT();

        if (verts[0].t <= xr.t && xr.t < verts[d].t)
            verts[d].set(xr.r, xr.t);

        else if(xr.t < verts[0].t){
            EXPAND();

            if (xe.t < xr.t)
                verts[d].set(xe.r, xe.t);
            else
                verts[d].set(xr.r, xr.t);
        }

        else if(verts[d-1].t <= xr.t && xr.t < verts[d].t){
            OUT_CONTRACT();

            if (xoc.t <= xr.t)
                verts[d].set(xoc.r, xoc.t);
            else
                SHRINK();
        }

        else if(xr.t >= verts[d].t){
            IN_CONTRACT();

            if (xic.t < verts[d].t)
                verts[d].set(xic.r, xic.t);
            else
                SHRINK();
        }
    }       

};
