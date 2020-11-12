  
#pragma once

#include <iostream>
#include <list>
#include <algorithm>
#include "bitmap.h"

// Параметры аллокатора
// elements_on_arena  - память выделяется "аренами" в которой могут разместиться указанное количество элементов (чанков)
// verbose - вывод отладочной информации, 0 to 3
template< int elements_on_arena, int verbose >
struct OptParameters{
    static const int chanks_total = elements_on_arena;
    static const int verb = verbose;
};

using optParamDefaults = OptParameters<1024, 0>;

template <typename T, typename P = optParamDefaults>
struct OptAllocator {
    using value_type = T;
    using params = P;
    
    // Здесь размер чанка равен размеру элементу - как требуется по заданию.
    // Можно увеличить, чтобы получить "разреженное" хранение элементов или для других идей
    static const int chank_sz = sizeof(T);  
    static const int arena_sz = P::chanks_total*chank_sz;
    
    OptAllocator() noexcept;
    template <typename U> OptAllocator (const OptAllocator<U>&) noexcept;
    T* allocate (std::size_t n);
    void deallocate (T* p, std::size_t n);
   
    template<typename U>
    struct rebind {
        using other = OptAllocator<U,P>;
    };

    struct Arena {
        void* base;
        bitmap<P::chanks_total> bmp;
        Arena():base(nullptr){}
    } ar;

    
    std::list<Arena> arenas;

    // Простой логгер в стиле "<<" с фильтрацией вывода по уровню сообщения
    template <int verbLevel, int MsgLevel> 
    struct optlog{
        template <typename ValType>
        const optlog& operator<<(const ValType& val) const {
            if (verbLevel>=MsgLevel)
                std::cout<<val;
            return *this;
        }   
        // to support << std::endl
        const optlog& operator<<(std::basic_ostream<char>& (*manip)(std::basic_ostream<char>&)) const {
            return operator<< <>(manip);
        }   
    };
    optlog<P::verb, 0> LOG_0;
    optlog<P::verb, 1> LOG_1;
    optlog<P::verb, 2> LOG_2;
    optlog<P::verb, 3> LOG_3;
};


template <typename T, typename P>
OptAllocator<T, P>::OptAllocator() noexcept {
    LOG_3 << __PRETTY_FUNCTION__ << std::endl;
}


template <typename T, typename P>
template <typename U> 
OptAllocator<T, P>::OptAllocator (const OptAllocator<U>&) noexcept {
       LOG_3 << __PRETTY_FUNCTION__ << std::endl; 
}      


template <class T, class U>
constexpr bool operator== (const OptAllocator<T>& lhs, const OptAllocator<U>& rhs) noexcept {
    lhs.LOG_3 << __PRETTY_FUNCTION__ << std::endl; 
    return true;
}


template <class T, class U>
constexpr bool operator!= (const OptAllocator<T>& lhs, const OptAllocator<U>& rhs) noexcept {
    lhs.LOG_3 << __PRETTY_FUNCTION__ << std::endl;
    return false; 
}


template <typename T, typename P>
T * OptAllocator<T, P>::allocate(std::size_t n) {
    LOG_3 << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl; 
    int chunks_need = sizeof(T) * n / chank_sz;
    if (sizeof(T) * n % chank_sz > 0) {
        chunks_need+=1;
    }

    // Поиск арены со свободными чанками и позиции в ней
    int pos=-1;
    auto res=std::find_if(arenas.begin(),arenas.end(), 
        [&pos, chunks_need](const Arena &a){
            pos = a.bmp.find_zeros(chunks_need);
            return  (pos>=0);
    });

    // Если нет подходящей арены - создаем новую
    if (res == arenas.end() || pos ==-1 ){
        Arena ar;
        ar.base = std::malloc(arena_sz);
	    if (!ar.base)
		    throw std::bad_alloc();
        int sz=arena_sz; // Code 'LOG_1<<arena_sz' makes LD error. ?!  
        LOG_1<<"Created new arena with address "<<std::hex<<ar.base<<", size="<<sz<<std::endl;
        arenas.push_back(ar);
        res = std::prev(arenas.end());
        pos=0;
    }

    Arena &ar = *res;
    ar.bmp.mark_n(pos, chunks_need, true);

    LOG_1<<"Allocated "<<chunks_need<<" chunk on pos="<<pos<<" for {size="<<sizeof(T) * n
         <<", n="<<n<<", type="<<typeid(T).name()<<"}"<<std::endl;
    for (const auto& a:arenas){
        LOG_2<<a.bmp<<std::endl;
    }
  
	return reinterpret_cast<T*>(reinterpret_cast<char*>(ar.base) + pos * chank_sz);
}


template <typename T, typename P>
void OptAllocator<T, P>::deallocate (T* p, std::size_t n) {
    LOG_3 << __PRETTY_FUNCTION__ << std::endl; 

    int chunks_need = sizeof(T) * n / chank_sz;
    if (sizeof(T) * n % chank_sz > 0) {
        chunks_need+=1;
    }

    // Поиск арены, где расположен элемент 
    auto res=std::find_if(arenas.begin(), arenas.end(), 
        [ptr=reinterpret_cast<char*>(p)](const Arena &a){
            return (ptr >= reinterpret_cast<char*>(a.base) && 
                    ptr <  reinterpret_cast<char*>(a.base)+arena_sz);
            }
    );

    if (res == arenas.end()){
        LOG_0<<"Deallocate error: can't find arena!"<<std::endl;
        return;
    }
    
    Arena &ar = *res;
    int pos = (reinterpret_cast<char*>(p)-reinterpret_cast<char*>(ar.base))/chank_sz;
    ar.bmp.mark_n(pos, chunks_need, false);    

    LOG_1<<"Deallocated "<<chunks_need<<" chunk on pos="<<pos<<" for {size="<<sizeof(T) * n
         <<", n="<<n<<", type="<<typeid(T).name()<<"}"<<std::endl;
    if (ar.bmp.none()){
        LOG_1<<"Free arena  "<<std::hex<<ar.base<<std::endl;
        std::free(ar.base);
        ar.base=nullptr;
        arenas.erase(res);
    }  
    for (const auto& a:arenas){
        LOG_2<<a.bmp<<std::endl;
    }
}
