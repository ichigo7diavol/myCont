#ifndef CONT_H
#define CONT_H

#include <cstddef>
#include <cmath>
#include <stdexcept>

template <typename T>
class Cont {

    using var_type = T;

public:
    Cont (const size_t &);
    Cont ();

    Cont (const Cont &);
    Cont (Cont &&);

    ~Cont ();

    class iterator {

    public:
        iterator () : value(nullptr) { };
        ~iterator () = default;

        var_type& operator* () {  };
        iterator& operator++ () { ++value; return *this; };
        iterator& operator++ (int) {  };
        iterator& operator-- ();


    private:
        var_type* value;
    };

    iterator begin ();
    iterator end ();

    void push_back (const var_type &);
    void insert (size_t);

    void erase (size_t);

    size_t size () const { return _size; }
    size_t capacity () const { return _capacity; }

    bool empty () { return _size;}

    void clear() { delete [] data; _size = 0; _capacity = 0; back = nullptr; front = nullptr; }

    Cont& operator =(const Cont &);
    Cont& operator = (Cont &&);

    var_type& operator [] (const size_t &);
    var_type& at (const size_t &);

private:
    var_type* data;
    size_t _size;
    size_t _capacity;
    T * back;
    T * front;
};


/* /////////////           IMPL         /////////////// */


template <typename T>
Cont<T>::Cont()
    : data(nullptr), _size(0),
      _capacity(0), front(nullptr),
      back(nullptr)
{
#ifdef DEBUG
    std::cout << "Def cstr\n";
#endif
}

template <typename T>
Cont<T>::Cont(const size_t &cap)
    : data(new Cont::var_type[cap]),
      _size(0),
      _capacity(cap),
      front(data),
      back(data)
{
    #ifdef DEBUG
    std::cout << "Fill cstr for " << cap << " elements\n";
    #endif
}

template <typename T>
Cont<T>::Cont (const Cont & obj)
{
    #ifdef DEBUG
    std::cout << "Copy cstr.\n";
    #endif

    this->data = new var_type [obj._capacity];
    memcpy(this->data, obj.data, obj._size * sizeof(var_type));

    this->_size = obj._size;

    this->_capacity = obj._capacity;

    this->front = this->data;

    this->back = this->data + this->_capacity;
}


template <typename T>
Cont<T>::Cont (Cont && obj)
{
    #ifdef DEBUG
    std::cout << "Move cstr.\n";
    #endif

    this->data = obj.data;
    obj.data = nullptr;

    this->_size = obj._size;
    obj._size = 0;

    this->_capacity = 0;

    this->front = obj.front;
    obj.front = nullptr;

    this->back = obj.back;
    obj.back = nullptr;
}


template <typename T>
Cont<T>& Cont<T>::operator =(const Cont & obj)
{
    #ifdef DEBUG
    std::cout << "Copy assign op.\n";
    #endif

    this->data = new var_type [obj._capacity];
    memcpy(this->data, obj.data, obj._size * sizeof(var_type));

    this->_size = obj._size;

    this->_capacity = obj._capacity;

    this->front = this->data;

    this->back = this->data + this->_capacity;

    return *this;
}

template <typename T>
Cont<T>& Cont<T>::operator = (Cont && obj)
{
    #ifdef DEBUG
    std::cout << "Move assign op.\n";
    #endif

    this->data = obj.data;
    obj.data = nullptr;

    this->_size = obj._size;
    obj._size = 0;

    this->_capacity = 0;

    this->front = obj.front;
    obj.front = nullptr;

    this->back = obj.back;
    obj.back = nullptr;

    return *this;
}


template <typename T>
Cont<T>::~Cont()
{

#ifdef DEBUG
    std::cout << "Def dstr\n";
#endif

    if (data)
        delete [] data;
}

template <typename T>
T& Cont<T>::operator [] (const size_t & i)
{
    return data[i];
}

template <typename T>
T& Cont<T>::at (const size_t & i)
{
    if (i >= _size || i < 0) {
#ifdef DEBUG
        std::cout << "Throwing exception at at() function.\n";
#endif

        throw std::out_of_range("Containter out of range!");
    }

    return data[i];
}

template <typename T>
void Cont<T>::push_back (const var_type & val)
{
    if (_size == _capacity)
    {
#ifdef DEBUG
        std::cout << "Realloc at push back.\n";
#endif
        size_t new_capacity = ceil(((!_capacity) ? 1 : _capacity)  * 1.2);
        var_type * new_data = new var_type [new_capacity];

        memmove(new_data, data, _size * sizeof(T));
        _capacity = new_capacity;
        data = new_data;
        front = data;
        back = data + _size;
    }

    _size++;
    *back = val;
    back++;
}



#endif // CONT_H
