struct Mealder 
{
    static const unsigned int d = 2;
    unsigned const tmax;
    Float alpha = 1;
	Float beta  = 2;
	Float gamma = 0.5;
	Float delta = 0.5;
    std::vector<HenonMap> matrix;
    std::vector<int> vals;

    Mealder(const unsigned t1) : tmax(t1), matrix(d+1)
    {
        for(auto& x: matrix) x = HenonMap(tmax);

        for(auto& x: matrix) 
            print(x.t);

        SORT();
    }

    void SORT(){
        HenonMap temp(tmax);

		for(unsigned int i = 0; i < d+1 ; i++)
		{
			for (unsigned int j = i+1; j < d+1; j++)
			{
				if (matrix[i].t > matrix[j].t)
				{
					temp        = matrix[i];
					matrix[i]   = matrix[j];
					matrix[j]   = temp;
				}}}
    }


};