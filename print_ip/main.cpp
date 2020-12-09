/**
 * @file main.cpp
 * @author Ampermetr123 (sb.simonov@gmail.com)
 * @brief Demonstration of ip_print() usage 
 * @version 0.1
 * @date 2020-11-23
 * 
 * @copyright Copyright (c) 2020
 */
#include "print_ip.h"

int main(int, char**) {
       
    char ch(-1);
    print_ip(ch);
    
    short sh(0);
    print_ip(sh);   

    int i(2130706433);
    print_ip(i);

    long long l=8875824491850138409LL;
    print_ip(l);
    
    std::string str("10.10.23.30");

    std::vector vect{1,2,3,4};
    print_ip(vect);

    std::list<int> lst{5,6,7,8};
    print_ip(lst);

    auto t1 = std::make_tuple(9,10,11,12);
    print_ip(t1);
   
  //  Uncomment to check error when types are different
  //  auto t2 = std::make_tuple(9,10,11LL,12);
  //  print_ip(t2);

}
