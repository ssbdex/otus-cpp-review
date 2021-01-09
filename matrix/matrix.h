#include "pretty.h"

#include <unordered_map>
#include <tuple>
#include <utility>

namespace mymatrix {

    template<typename T, T defaultValue>
    class MatrixIterator;


    template <typename T, T defaultValue>
    struct Matrix {

        using Key = size_t;
        typedef MatrixIterator<T, defaultValue > iterator;
        typedef MatrixIterator<const T, defaultValue> const_iterator;
        friend iterator;
        friend const_iterator;

        iterator begin() {
            return iterator(data.begin());
        }

        iterator end() {
            return iterator(data.end());
        }

        const_iterator begin() const {
            return MatrixIterator<const T, defaultValue>(data.end());
        }
        const_iterator end() const {
            return MatrixIterator<const T, defaultValue>(data.end());
        }

        struct Value {
            Value(Matrix* m, Key index) : pMatrix(m), idx(index) {
                PRETTY_LOG;
                auto it = m->data.find(index);
                val = it != m->data.end() ? it->second : defaultValue;
            };

            operator T() const {
                PRETTY_LOG;
                return val;
            }

            operator T& () {
                PRETTY_LOG;
                return val;
            }

            Value& operator=(const T& newVal) {
                PRETTY_LOG;
                if (newVal == defaultValue) {
                    pMatrix->data.erase(idx);
                    val = defaultValue;
                }
                else {
                    pMatrix->data.insert_or_assign(idx, newVal);
                    val = newVal;
                }
                return *this;
            }

            Value& operator=(const T&& newVal) {
                PRETTY_LOG;
                if (newVal == defaultValue) {
                    pMatrix->data.erase(idx);
                }
                else {
                    pMatrix->data.insert_or_assign(idx, newVal);
                }
                val = std::move(newVal);
                return *this;
            }
        private:
            Value& operator=(const Value& rv) = delete;
            Value& operator=(Value&& rv) = delete;
            Matrix* pMatrix;
            Key idx;
            T val;
        };
        friend Value;

        struct Row {
            Row(Matrix* m, unsigned i) :pMatrix(m), row(i) {}
            Value operator[](unsigned j) {
                PRETTY_LOG;
                return Value(pMatrix, Matrix::key(row, j));
            }
        private:
            Matrix* pMatrix;
            unsigned row;
        };
        friend Row;

        Matrix() = default;
        size_t size() const {
            return data.size();
        }
        Row operator[] (unsigned i) {
            return Row(this, i);
        }

    private:
        static Key key(unsigned i, unsigned j) {
            return static_cast<Key>(i) << 32 | j;
        }

        static std::pair<unsigned, unsigned> index(Key key) {
            return std::make_pair<unsigned, unsigned>((key >> 32) & 0xFFFFFFFF, key & 0xFFFFFFFF);
        }

        std::unordered_map<Key, T> data;

    };


    ////////////////////////////// Iterator ////////////////////////////////////////////


    template<typename T, T defaultValue>
    class MatrixIterator {
    public:
        using map_iterator = typename std::unordered_map<typename Matrix<T, defaultValue>::Key, T>::iterator;

        using reference = typename std::tuple<unsigned, unsigned, T&>; //typename map_iterator::reference;
        using value_type = T;


        MatrixIterator(const map_iterator& iter) :it(iter) {}

        bool operator!=(MatrixIterator const& other) const {
            return (it != other.it);
        }

        bool operator==(MatrixIterator const& other) const { //need for BOOST_FOREACH
            return !(it != other.it);
        }

        typename MatrixIterator::reference operator*() const {
            auto ij = Matrix<T, defaultValue>::index(it->first);
            typename MatrixIterator::reference  tpl(ij.first, ij.second, it->second);
            return tpl;
        }

        MatrixIterator& operator++() {
            ++it;
            return *this;
        }
    private:
        map_iterator it;
    };



}