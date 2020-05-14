//template <typename T>
//void print(T t){ std::cout << t << std::endl; }
// 
//template <typename T, typename... Args>
//void print(T t, Args... args){
//    std::cout << t << std::endl;
//    print(args...);
//}

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
