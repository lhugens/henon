struct Mealder 
{
    static const unsigned int d = 2;
    unsigned const tmax;
    Float alpha = 1;
	Float beta  = 2;
	Float gamma = 0.5;
	Float delta = 0.5;
    std::vector<HenonMap> verts;
    std::vector<HenonMap> props;

    Mealder(const unsigned t1) : tmax(t1), verts(d+1), props(5)
    {
        for(auto& x: verts) x = HenonMap(tmax);
        for(auto& x: props) x = HenonMap(tmax);

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
        unsigned int td = d;
		for(unsigned j = 0; j < d; j++)
		{
			for(unsigned i = 0; i < d; i++)
			{
				props[0].r[j] += verts[i].r[j] / td ;
			}}
	}	


};
