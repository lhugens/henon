template <typename T>
void prinft(T t){ std::cout << t << std::endl; }
 
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
void print(T &point){
    std::cout <<
        " [ " << std::setw(5) << point.t    <<
        ", "  << std::setw(15) << point.r[0] << 
        ", "  << std::setw(15) << point.r[1] <<
        " ]"  << std::setw(15) << std::endl;
}
template <typename T>
void echo(T s){
    std::cout << s ; 
}

