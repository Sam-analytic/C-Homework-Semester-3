#include<cstddef>
#include<iostream>
#include<fstream>

using namespace std;

template <typename T>
class Grid {
private:
    T* memory;
    size_t x_size;
    const size_t y_size; // C++ standard does not allow second dimension to be non constant for 2d arrays

public:
    Grid(size_t x_size, size_t y_size);

    T operator()(size_t x_idx, size_t y_idx) const;
    T& operator()(size_t x_idx, size_t y_idx);

    size_t get_xsize() const;
    size_t get_ysize() const;

    Grid& operator=(T a);

    friend ostream& operator<<(std::ostream&, Grid const&);
    friend istream& operator>>(std::istream&, Grid&);

    Grid& make_subgrid(
        size_t x_idx, size_t y_idx,
        size_t x_sub_size, size_t y_sub_size);

    Grid& collapse_subgrid(
        size_t x_idx, size_t y_idx,
        size_t x_sub_size, size_t y_sub_size);

    Grid& get_subgrid(size_t x_idx, size_t y_idx);
    Grid const& get_subgrid(size_t x_idx, size_t y_idx);

    bool is_subgrid(size_t x_idx, size_t y_idx) const;
};

template <typename T> Grid<T>::Grid(size_t x_size, const size_t y_size) : memory{ new float[x_size][y_size] }, x_size{ x_size }, y_size{ y_size } {}; // constructor definition

template <typename T> T Grid<T>::operator()(size_t x_idx, size_t y_idx) const
{
    return buffer[x_idx][y_idx];
}

template<typename T> T& Grid<T>::operator()(size_t x_idx, size_t y_idx)
{
    return &buffer[x_idx][y_idx];
}

template <typename T> size_t Grid<T>::get_xsize() const
{
    return x_size;
}

template <typename T> size_t Grid<T>::get_ysize() const
{
    return y_size;
}

template <typename T> Grid<T>& Grid<T>::operator=(T a)
{
    new_mem = new T[x_size][y_size];
    delete memory;
    memory = new_mem;
    return &this;
}

template <typename T> ostream& operator<<(std::ostream& ostr, Grid<T> const& g)
{
    for (auto i = 0; i != g.get_xsize; ++i)
    {
        for (auto j = 0; j != g.get_ysize(); ++j)
        {
            ostr << g(i, j) << ', ';
        }
    }
    ostr.flush();
    return ostr; // ostr is a refrence to ostream
}

template <typename T> istream& operator>>(std::istream& istr, Grid<T>& g)
{
    for (auto i = 0; i != g.get_xsize; ++i)
    {
        for (auto j = 0; j != g.get_ysize(); ++j)
        {
            istr >> g(i, j) ;
        }
    }
    return istr;
}

template<typename T> Grid<T>& Grid<T>::make_subgrid(size_t x_idx, size_t y_idx, size_t x_sub_size, size_t y_sub_size)
{
    buffer[x_idx][y_idx] = new T[x_sub_size][y_sub_size];
    return this;
}

template <typename T> Grid<T>& Grid<T>::collapse_subgrid(size_t x_idx, size_t y_idx, size_t x_sub_size, size_t y_sub_size)
{
    int num_elems = x_sub_size * y_sub_size;
    float summa = 0;
    for (auto i = 0; i != x_sub_size; ++i)
    {
        for (auto j = 0; j != y_sub_size; ++j)
        {
            summa += buffer[x_idx][y_idx][i][j];
        }
    }
    float avg = summa / num_elems;
    delete buffer[x_idx][y_idx];
    buffer[x_idx][y_idx] = static_cast<T>(avg);
    return &this;
}

template <typename T> bool Grid<T>::is_subgrid(size_t x_idx, size_t y_idx) const
{
    if (buffer[x_idx][y_idx] == Grid<T>)
    {
        return True;
    }
    else
    {
        return False;
    }
}

template <typename T> Grid<T>& Grid<T>::get_subgrid(size_t x_idx, size_t y_idx)
{
    if (template <typename T> bool Grid<T>::is_subgrid(size_t x_idx, size_t y_idx))
    {
        return &buffer[x_idx][y_idx];
    }
    else
    {
        throw (&buffer[x_idx][y_idx])
    }
    catch
    {
        cout << "The given element is not a subarray."
    }
}
