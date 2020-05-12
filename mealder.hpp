struct Mealder {
    unsigned const tmax;
    std::vector<HenonMap> matrix;

    Mealder(const unsigned t1) :
        tmax(t1), matrix(3)
    {
        for(auto& x: matrix) x = HenonMap(tmax);

    };

};