//#define USE_PRETTY_LOG

#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#ifdef USE_PRETTY_LOG
    #include <iostream>
    #define PRETTY_LOG std::cout<<__PRETTY_FUNCTION__<<std::endl;
#else
    #define PRETTY_LOG
#endif



