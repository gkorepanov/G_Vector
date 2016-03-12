//This is a template class. Thus Implementation is placed in .h

////////////////////////////////////////////////////////////////////////////////////////////////
//DECLARATION
////////////////////////////////////////////////////////////////////////////////////////////////


/* TODO(#1). All errors are leading to exit(1) now.
   Exceptions handling must be implemented.*/

#include <stdio.h>
#include <new>
#include <algorithm>
#include <cmath>
#include <memory>
#include "alerts.h"

using namespace std;

//less writing
typedef unsigned int uint;
typedef unsigned long int luint;
#define TPL template <typename T>

//declaration of class for friends:
template <typename T = int> class CVector; 

//declaration of template friend operators:
TPL CVector<T> operator + (const CVector<T>& lhs, const CVector<T>& rhs);
TPL CVector<T> operator * (const CVector<T>& vec, int num);

//default type is int, look at declaration
TPL
class CVector {
    private:
        static const size_t MAX_SIZE = 10e6;
        static const size_t INIT_SIZE = 10e2;

        shared_ptr<T> data_;
        size_t size_;
        const uint id_;

        static uint counter;
    public:
        explicit CVector(const int init_size = INIT_SIZE);
        CVector(const CVector<T>& that);
        ~CVector();

        int& operator [] (const uint ind) const;
        CVector<T> operator = (const CVector<T>& vec);       
        friend CVector<T> operator + <> (const CVector<T>& lhs, const CVector<T>& rhs);
        friend CVector<T> operator * <> (const CVector<T>& vec, int num);

        void grow(const size_t request_size);
        void push(const T new_elem);

        void dump() const;
        void print_data() const;
};


/*function needed for reallocating to a new size
QUESTION (#2): where do i put it? Another class/another header/here?*/
inline luint floor_power_of_2(luint num);

//a number of function used by print_data. QUESTION(#2)
inline void print_line();

TPL
void print_elem(T elem);

TPL
uint elem_length(T elem);

////////////////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////////////////////

const uint STDOUT_STR_LEN = 100;
void print_line() {
    for (uint i = 0; i < STDOUT_STR_LEN; i++)
        printf("-");

    printf("\n");
}

TPL
void print_elem(T elem) {
    ERR("No printing function for specific type T");
}

template <> void print_elem <int> (int elem) {
    printf("%d", elem);
}

TPL
uint elem_length(T elem) {
    ERR("No function to know length of specific element of type T");
}

template <> uint elem_length <int> (int elem) {
    //printf("\nELEM: %d; ", elem);
    uint i(0);
    do {
        elem /= 10;
        i++;
    } while (elem);
     
    //printf("LENGTH: %d\n", i);
    return i;
}

luint floor_power_of_2(luint num) {
    DBGPRINT("Function floor_power of_2 got %lu", num);
    uint i;
    for (i = 0; num; i++) {
        num >>= 1;
    }

    num = 1;
    for ( ; i > 0; i--) {
        num <<= 1;
    }
    DBGPRINT("And returned %lu", num);
    return num;
}

//shared_ptr for arrays need delete[]
TPL
class smart_ptr_deleter {
    public:
        void operator () (T* ptr) {
            delete[] ptr;
        }
};

TPL
uint CVector<T>::counter(0);

TPL
CVector<T>::CVector(const int init_size)
    try :
        data_(new int(init_size), smart_ptr_deleter<T>()),
        size_(init_size),
        id_(CVector<T>::counter)
    {
        CVector<T>::counter++;

        for (uint i = 0; i < init_size; i++)
            (data_.get())[i] = 0;
    }
    catch (bad_alloc ex) {
        EXERR("Couldn't allocate memory for new CVector copy");
    };

TPL
CVector<T>::CVector(const CVector<T>& that) :
    data_(that.data_),
    size_(that.size_),
    id_(CVector<T>::counter)
{
    CVector<T>::counter++;
}


TPL
CVector<T>::~CVector() {
    CVector<T>::counter--;
}

TPL
CVector<T> CVector<T>::operator = (const CVector<T>& vec) {
    try {
        if (size_ != vec.size_) 
            throw;
        for (uint i = 0; i < size_; i++)
            (*this)[i] = vec[i];

        return *this;
    }
    catch(...) {
        EXERR("Trying to asiign Vectors of different size.");
    }
}
    

TPL
int& CVector<T>::operator [] (const uint ind) const {
    try {
        if ((ind < 0) || (ind >= size_))
            throw;
        
        return (data_.get())[ind];
    }
    catch(...) {
        EXERR("Ind = %u is out of bounds. SIZE: %zu", ind, size_);
    }
}

TPL
CVector<T> operator + (const CVector<T>&lhs, const CVector<T>&rhs) {
    try {
        if (lhs.size_ != rhs.size_)
            throw;
        
        CVector<T> res(lhs.size_);

        for (uint i = 0; i < lhs.size_; i++)
            res[i] = lhs[i] + rhs[i];

        return res;
    }
    catch(...) {
        EXERR("Tried to sum Vectors of different size");
    }
}

TPL
CVector<T> operator * (const CVector<T>& vec, int num) {
    CVector<T> res(vec.size_);

    for (uint i = 0; i < vec.size_; i++)
        res[i] = vec[i] * num;

    return res;
}

TPL
void CVector<T>::grow(const size_t request_size) {
    try {
        if ((request_size < 0) || (request_size > MAX_SIZE))
            throw;
        
        const size_t new_size(min(floor_power_of_2(request_size*2), MAX_SIZE));
        
        shared_ptr<T> new_data(new T(new_size), smart_ptr_deleter<T>());
        
        for(uint i = 0; i < size_; i++) 
            (new_data.get())[i] = (data_.get())[i];

        data_.swap(new_data);
    }
    catch(bad_alloc ex) {
        /*TODO: make new allocator that throws an ex with class derived from bad_alloc 
          with info about number of bytes asked*/
        EXERR("Couldn't allocate memory");
    }
    catch(...) {
        EXERR("Requested size is wrong. REQUEST: %zu; MAX_SIZE: %zu", request_size, MAX_SIZE);
    }   
}

TPL
void CVector<T>::dump() const {
    printf("\n");
    print_line();

    printf("VECTOR DUMP\n");
    print_line();
    printf("ID: %u\n"\
           "SIZE: %zu\n"\
           "OBJS COUNTER: %u\n"\
           "NUM OF OBJS SHARING DATA: %lu\n",\
           id_, size_, CVector<T>::counter, data_.use_count());
    print_data();

    printf("\n");
}


//TODO: divide into functions and make it readable, beautiful
TPL
void CVector<T>::print_data() const {
    uint length(5), lengthi, lengthe;

    for (uint i = 0; i < size_; i++) {
        lengthi = elem_length(static_cast<int>(i));
        lengthe = elem_length((*this)[i]);
        length = max(lengthi, max(lengthe, length));
    }

    uint i(0), j(0), k(0);
    uint cur_len(0), spacenum(0);

    print_line();

    while (i < size_) {
        spacenum = length - elem_length(static_cast<int>(i));

        for (k = 0; k < spacenum/2; k++)
            printf(" ");

        printf("%u", i);

        for (k = 0; k < spacenum%2 + spacenum/2; k++)
            printf(" ");
        printf("|");

        if (((cur_len + length + 1) > STDOUT_STR_LEN) || ((i+1) == size_)) {
            printf("\n");
            for ( ; j <= i; j++) {
                spacenum = length - elem_length((*this)[j]);

                for (k = 0; k < spacenum/2; k++)
                    printf(" ");


                print_elem((*this)[j]);

                for (k = 0; k < ((spacenum%2) + (spacenum/2)); k++)
                    printf(" ");

                printf("|");
            }

            printf("\n");
            print_line();
            cur_len = 0;
        }

        i++;
    }
}