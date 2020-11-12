#include "config.h"
#include <cstdlib>
#include <iostream>
#include <map>
#include "optalloc.h"
#include "mycont.h"

constexpr int VERBOSE_LEVEL=2;

int main(int, char**){

    std::cout<<"Homework #2: "<<PROJECT_NAME<<" "<<PROJECT_VERSION<<std::endl;

    {    
        // - создание экземпляра std::map<int, int>
        std::map<int,int> fact_map_default;
        
        // - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
        for (int i=0, fact=1; i<10; i++, fact*=i){
            fact_map_default[i]=fact;
        }
            
        // - создание экземпляра std::map<int, int> с новым аллокатором
        std::map<int,int, 
                std::less<int>,
                OptAllocator<std::pair<const int, float>, OptParameters<10, VERBOSE_LEVEL>> 
                > fact_map_opt;
        
        // - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
        for (int i=0, fact=1; i<10; i++, fact*=i){
            fact_map_opt[i]=fact;
        }

        // вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
        std::cout<<"fact_map_opt:"<<std::endl;
        for (const auto& p : fact_map_opt){
            std::cout<<p.first<<" "<<p.second<<std::endl;
        }
    }

    {
        // создание экземпляра своего контейнера для хранения значений типа int
        // заполнение 10 элементами от 0 до 9
        MyCont<int> cont_std;
        for (int i=0; i<10; i++){
            cont_std.push(i);
        }

        // создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,
        // ограниченным 10 элементами
        // заполнение 10 элементами от 0 до 9
        MyCont<int, OptAllocator<int, OptParameters<10, VERBOSE_LEVEL> > > cont_opt;
        for (int i=0; i<10; i++){
            cont_opt.push(i);
        }

        // вывод на экран всех значений, хранящихся в контейнере
        for (auto x=cont_opt.begin(); x!=cont_opt.end(); ++x){
            std::cout<<*x<<" ";
        }
        std::cout<<std::endl;
    }

    return EXIT_SUCCESS;
}