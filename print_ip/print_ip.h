/**
 * @file print_ip.h
 * @author Ampermetr123 (sb.simonov@gmail.com)
 * @brief Template functions for printing ipv4 like address
 * @version 0.1
 * @date 2020-11-23
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
#include <list>
#include <tuple>

/**
 * @brief Print ipv4 style address like x.x.x.x from integral value
 * @note Template version for integral types
 * 
 * @tparam T - integral type 
 * @tparam SFINAE - filter to pass only integral types 
 * @param ip_num - ip address value to print
 */
template <typename T, 
typename SFINAE = typename std::enable_if< std::is_integral<typename std::remove_reference<T>::type >::value, void>::type >
void print_ip(const T& ip_num){
    for (int i=sizeof(T)-1; i>=0; i--){
        std::cout<<(ip_num>>8*i & 0xFF);
        i = (i>0) ? (std::cout<<".", i) : (std::cout<<std::endl, i);
    }
}

/**
 * @brief Print ipv4 style adress like x.x.x.x from container elements
 * @note Template version for std::list and std::vector input parameter
 * 
 * @tparam T - std::vector or std::list
 * @tparam SFINAE - filter to pass only std::vector or std::list
 * @param ip_num - ip adressvalue to print
 */
template<class T, class A, template<class,class> class Cont ,   
typename SFINAE = typename std::enable_if<
        std::is_same< Cont<T, A>, std::vector<T, A> >::value || 
        std::is_same< Cont<T, A>, std::list<T, A> >::value, void>::type >  
void print_ip(const Cont<T,A>& ip_num){
    auto it = ip_num.cbegin();
    while (it != ip_num.cend()){
        std::cout << *it;
        ++it;
        if (it == ip_num.cend()){ 
            std::cout << std::endl;
        } else {
            std::cout << '.';
        }
    }
}


/**
 * @brief Print ipv4 style adress like x.x.x.x from std::string
 * @note Just output string value
 * 
 * @tparam T - std::string
 * @param  ip_str - string that contains ip adress
 */
template <typename U, typename A> 
void print_ip(const std::basic_string<U,A>& ip_str){
    std::cout << ip_str << std::endl;
}
    

/**
 * @brief End of recursion for variadic template for print_ip(std::tuple<Tp...>& t)
*/
template<std::size_t I = 0, typename... Tp>
typename std::enable_if<I == sizeof...(Tp), void>::type
print_ip([[maybe_unused]] std::tuple<Tp...>& t){ 
    std::cout << std::endl; 
}


/**
 * @brief Print ipv4 style adress like x.x.x.x from std::tuple 
 * @note Template version for std::tuple input parameter
 * 
 * @tparam I - index of element in tuple to start print; 
 * @tparam Tp - tuple types
 * 
 * @param t - tuple to print
 */
template<std::size_t I = 0, typename... Tp>
typename std::enable_if<I<sizeof...(Tp), void>::type
print_ip(std::tuple<Tp...>& t)
{
    static_assert(std::is_same< decltype(std::get<I>(t)),  decltype(std::get<0>(t))>::value, "All elements of tuple must be the same type!");
    if constexpr (I>0) {
        std::cout << ".";
    }
    std::cout << std::get<I>(t);
    
    // std::cout <<"["<<I<<","<<sizeof...(Tp)<<"]";
    if constexpr (I < sizeof...(Tp)){ //Не пойму почему не работает. Все равно инстанцирует шаблон c I==sizeof...(Tp) !!
        print_ip<I + 1, Tp...>(t);
    }
    
 }
