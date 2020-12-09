#include <bitset>
#include <ostream>

template <std::size_t SIZE>
struct bitmap:public std::bitset<SIZE>
{ 
    int find_zeros(unsigned n) const noexcept {
      if (this->size() < this->count() + n )
        return -1;
      unsigned sum=0, i=0;
      while ( (i<this->size() ) && (sum<n) ){
          sum = this->operator[](i)==true ?  0 : sum+1;
          i++;
      };
      if (sum == n){
          return i-n;   
      } else {
         return -1; 
      };
    }

    void mark_n(unsigned pos, unsigned n, bool val){
        for (unsigned i=pos; i < this->size() && i<pos+n; i++){
            this->operator[](i)=val;
        }
    }
};


template <std::size_t SIZE>
std::ostream& operator<< (std::ostream &os, const bitmap<SIZE> & bmp){
    const unsigned char ch_empty='_';
    const unsigned char ch_full='x';
    os<<'[';
    for (std::size_t i=0; i<SIZE; i++){
        if (bmp[i]==true){
            os<<ch_full;
        } else {
            os<<ch_empty;
        }
    }
    os<<']';
    return os;
}
