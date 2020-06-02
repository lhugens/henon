template <typename T>
void printf(T t){ std::cout << t << std::endl; }
 
template <typename T, typename... Args>
void printf(T t, Args... args){
    std::cout << t << std::endl;
    printf(args...);
}

void filePutContents(const std::string& name, Float content, bool append = false)
{
    std::ofstream outfile;
    if (append)
            outfile.open(name, std::ios_base::app);
    else
            outfile.open(name);
    outfile << content << '\n';
}

template <typename T>
void print_point(T &point){
    std::cout <<
        " " << std::setw(5)  << point.t    <<
        " " << std::setw(15) << point.r[0] <<
        " " << std::setw(15) << point.r[1] <<
        " " << std::endl;
}

template <typename T>
void print_simul(T &simul){
    for(unsigned t = 0; t < simul.tmax; t++)
        std::cout << std::setw(5)  << t              <<
            " "   << std::setw(7)  << simul.HISTO[t] <<
            " "   << std::setw(15) << simul.SIG[0][t]  <<
            " "   << std::setw(15) << simul.SIG[1][t]  <<
            " "   << std::endl;
}

template <typename T>
void print_simul_temp(T &simul){
    for(unsigned t = 0; t < simul.tmax; t++)
        std::cout << std::setw(5)  << t              <<
            " "   << std::setw(7)  << simul.HISTO[t] <<
            " "   << std::setw(15) << simul.SIG[t]  <<
            " "   << std::setw(15) << simul.SIG[t]  <<
            " "   << std::endl;
}

template <typename T, typename K>
void print_comparison(T &simul, K &simul1){
    std::cout << simul.steps << " " << simul1.steps << std::endl;
    for(unsigned t = 0; t < simul.tmax; t++)
        std::cout << std::setw(5)  << t              <<
            " "   << std::setw(7)  << simul.HISTO[t] <<
            " "   << std::setw(15) << simul.SIG[0][t]  <<
            " "   << std::setw(15) << simul.SIG[1][t]  <<
            " "   << std::setw(5)  << t              <<
            " "   << std::setw(7)  << simul1.HISTO[t] <<
            " "   << std::setw(15) << simul1.SIG[t]  <<
            " "   << std::setw(15) << simul1.SIG[t]  <<
            " "   << std::endl;
}

template <typename T>
void echo(T s){
    std::cout << s ; 
}
