struct Mealder 
{
    const unsigned int      d = 2; 
    unsigned const          tmax;
    Float                   alpha = 1;
	Float                   beta  = 2;
	Float                   gamma = 0.5;
	Float                   delta = 0.5;
    std::vector<HenonMap>   verts;      

    HenonMap                cent;
    HenonMap                xr;
    HenonMap                xe;
    HenonMap                xoc;
    HenonMap                xic;


    Mealder(const unsigned t1) : tmax(t1), verts(d+1), 
    cent(tmax), xr(tmax), xe(tmax), xoc(tmax), xic(tmax)
    {
        TRIANGLE_GEN();
        verts[0].r[0] = 0.641004 ;
        verts[0].r[1] = 3.67344 ;
        verts[0].TIME();
        
        verts[1].r[0] = 0.591004;
        verts[1].r[1] = 3.72344;
        verts[1].TIME();

        verts[2].r[0] = 0.591004;
        verts[2].r[1] = 3.67344;
        verts[2].TIME();
        
    }

    void TRIANGLE_GEN(){
        for(auto& x: verts){
            x = HenonMap(tmax);
        } 
    }

    void EVAL(){
        for(auto& x: verts){
            x.TIME();
        } 
    }

    void SORT(){
        HenonMap temp(tmax);

		for(unsigned i = 0; i < d+1 ; i++)
		{
			for (unsigned j = i+1; j < d+1; j++)
			{
				if (-verts[i].t > -verts[j].t)
				{
					temp     = verts[i];
					verts[i] = verts[j];
					verts[j] = temp;
				}}}
    }

    void CENTROID(){
		for(unsigned j = 0; j < d; j++)
		{
            cent.r[j] = 0.0;
			for(unsigned i = 0; i < d; i++)
			{
				cent.r[j] += verts[i].r[j] / d ;
			}}
        cent.TIME();
    echo("ce "); print(cent);
	}	

    void REFLECT(){
    echo("ultimo:   "); print(verts[d]);
        for(unsigned i = 0; i < d; i++)
			xr.r[i] = cent.r[i] + alpha*(cent.r[i]-verts[d].r[i]);
        xr.TIME();
    echo("xr "); print(xr);
    }

    void EXPAND(){
       	for(unsigned i = 0; i < d; i++)
       		xe.r[i] = cent.r[i] + beta*(xr.r[i]-cent.r[i]);
        xe.TIME();
    echo("xe "); print(xe);
    }

    void OUT_CONTRACT(){
       	for(unsigned i = 0; i < d; i++)
       		xoc.r[i] = cent.r[i] + gamma*(xr.r[i]-cent.r[i]);
        xoc.TIME();
    echo("xoc "); print(xoc);
    }

    void IN_CONTRACT(){
       	for(unsigned i = 0; i < d; i++)
       		xic.r[i] = cent.r[i] - gamma*(xr.r[i]-cent.r[i]);
    echo("xic "); print(xic);
    }

	void SHRINK(){
	       	for(unsigned j = 0; j < d; j++){
		    	for(unsigned i = 1; i < d+1; i++)
	           			verts[i].r[j] = verts[0].r[j] + delta*(verts[i].r[j]-verts[0].r[j]);}
    echo(" shrink \n");
	}

    void NelderMeadStep(){
        EVAL();
        SORT();
        echo("----\n");
        echo("v0 "); print(verts[0]);
        echo("v1 "); print(verts[1]);
        echo("v2 "); print(verts[2]);
        CENTROID();
        REFLECT();

        if (verts[0].t >= xr.t || xr.t > verts[d-1].t){
            verts[d].set(xr.r, xr.t); echo("hey\n");}

        else if(xr.t > verts[0].t){
            EXPAND();

            if (xe.t > xr.t)
                verts[d].set(xe.r, xe.t);
            else
                verts[d].set(xr.r, xr.t);
        }

        else if(verts[d-1].t >= xr.t || xr.t > verts[d].t){
            OUT_CONTRACT();

            if (xoc.t >= xr.t)
                verts[d].set(xoc.r, xoc.t);
            else
                SHRINK();
        }

        else if(verts[d].t >= xr.t){
            IN_CONTRACT();

            if (xic.t > verts[d].t)
                verts[d].set(xic.r, xic.t);
            else
                SHRINK();
        }
    }       

};  
