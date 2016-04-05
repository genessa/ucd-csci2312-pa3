//
// Created by Genessa Moodie on 2/18/16.
// Implementation of Point.h

#include <cmath>
#include "Point.h"
#include "Exceptions.h"

namespace Clustering{
using std::cout;

unsigned int Point::__idGen = 0;

    const char Point::POINT_VALUE_DELIM = ',';

    void Point::rewindIdGen()
    {
        __idGen--;
    }

// Constructor which takes one int argument (how many dimensions the new point will have)
// Problem: this leaves values not initialised..
Point::Point(unsigned int dim)
    {
        if(dim ==0)
            throw ZeroDimensionsEx();
    __dim = dim;
    __id = __idGen;
    __idGen++;
    __values = new double(__dim);
}

// Constructor which takes an int argument of the new Point's dimensions and a
//    pointer to dynamically allocate a double array of the Point's.. points.
Point::Point(unsigned int dim, double *values)
    {
    __dim = dim;
    __values = values;
    __values = new double(__dim);
    __id = __idGen;
    __idGen++;
}

// Copy constructor
Point::Point(const Point &p1)
    {
    // copy p1's __id to calling point's __id
    // assign calling point's arrayptr to p1's
    __id = p1.__id;
    __values = p1.__values;
}

// Overloaded assignment operator
//Point &Point::operator=(const Point &p1)
//    {
//    // recycle copy constructor's code
//    // but I think it will need its own __id rather than a copy
//    __id = __idGen;
//    ++__idGen;
//    __values = p1.__values;
//    return *this;
//    }

    Point &Point::operator=(const Point &rhs) {
        if (this == &rhs) {
            return *this;
        } else {
            delete[] __values;

            if (__dim != rhs.__dim) throw DimensionalityMismatchEx(__dim, rhs.__dim);

            __values = new double[__dim];
            for (int i = 0; i < __dim; i++)
                __values[i] = rhs.__values[i];
        }
        return *this;
    }

// Destructor
Point::~Point()
    {
//    delete []__values;
    }

// ID accessor function
int Point::getId() const { return __id; }

// Dimension accessor function
unsigned int Point::getDims() const { return __dim; }

// Dimension and (double) mutator function
void Point::setValue(unsigned int dim, double d)
    {
    __dim = dim;
    for (int i = 0; i < dim; ++i) {
        __values[i] = d;
    }
    }

// Accessor function which returns   a thing.
double Point::getValue(unsigned int index) const
    {
    return __values[index];
    }


// Finds distance between the point calling it and another point
double Point::distanceTo(const Point &p2) const
    {
    double distance = 0, temp = 0;
    for (int i = 1; i < __dim; i++) { temp += pow(__values[i], p2.__values[i]); }

    distance = sqrt(temp);
    return distance;
    }

Point &Point::operator*=(double d) // p *= 6; p.operator*=(6);
{
    for (int i = 1; i < __dim; i++) { __values[i] = (__values[i] * d); }
    return *this;
}

Point &Point::operator/=(double d)
{
    for (int i = 1; i < __dim; i++)
        __values[i] /= d;
    return *this;
}

const Point Point::operator*(double d) const // prevent (p1 * 2) = p2;
{
    // is returning *this doing the preventing thing?
    for (int i = 0; i < __dim; i++)
        __values[i] = __values[i] * d;
    return *this;

}

const Point Point::operator/(double d) const // p3 = p2 / 2;
{
    Point p1(__dim); // could copy constructor from calling point, but what to name calling point?
    for (int i = 1; i < p1.__dim; i++)
        p1.__values[i] = __values[i] / d;
    return p1;
}

double &Point::operator[](unsigned int index)
{
    return __values[index];
}

    const double &Point::operator[](unsigned int index) const // why are you wandering off into tab-land.
    {
        return __values[index];
    }

    // Friends
Point &operator+=(Point &p1, const Point &p2)
    {
    for (int i = 0; i < p1.getDims(); ++i)
    {
        p1.__values[i] = p1.__values[i] + p2.__values[i];
    }
    return p1;
}

Point &operator-=(Point &p1, const Point &p2)
{
    for (int i = 0; i < p1.__dim; ++i)
    {
        p1.__values[i] = p1.__values[i] - p2.__values[i];
    }
    return p1;
}

    bool operator==(const Point &p1, const Point &p2)
    {
        if (p1.__dim == p2.__dim && p1.__id == p2.__id)
        {
            for (int i = 1; i <= p1.__dim; i++)
            {
                if (p1.__values[i]==p2.__values[i])
                    return true;
            }
        }
            return false;
    }

    bool operator!=(const Point &p1, const Point &p2)
    {
        if (p1.__dim != p2.__dim && p2.__id != p1.__id)
         return true;

        if(p1.__dim == p2.__dim) {
            for (int i = 1; i <= p1.__dim; i++) {
                if (p1.__values[i] != p2.__values[i])
                    return true;
            }
        }
            return false;
    }

    bool operator<(const Point &p1, const Point &p2)
    {
        if (p1.__dim == p2.__dim)
        {
            for (int i = 1; i <= p1.__dim; i++)
            {
                if (p1.__values[i] < p2.__values[i])
                    return true;
            }
        }
            return false;
    }

    bool operator>(const Point &p1, const Point &p2)
    {
        if (p1.__dim == p2.__dim)
        {
            for (int i = 1; i <= p1.__dim; i++)
            {
                if (p1.__values[i] > p2.__values[i])
                    return true;
            }
        }
            return false;
    }

    bool operator<=(const Point &p1, const Point &p2)
    {
        if (p1.__dim == p2.__dim)
        {
            for (int i = 1; i <= p1.__dim; i++)
            {
                if (p1.__values[i] <= p2.__values[i])
                    return true;
            }
        }
            return false;
    }

    bool operator>=(const Point &p1, const Point &p2)
    {
        if (p1.__dim == p2.__dim)
        {
            for (int i = 1; i >= p1.__dim; i++)
            {
                if (p1.__values[i] > p2.__values[i])
                    return true;
            }
        }
        return false; // If this makes the compiler angry, put the else back.
    }

    std::ostream &operator<<(std::ostream &os, const Point &p1)
    {
        for (int i=0; i < p1.__dim; i++)
        {
            os << p1.__values[i] << p1.POINT_VALUE_DELIM;
        }
        return os;
    }

    std::istream &operator>>(std::istream &is, Point &p1)
    {
        for (int i=0; i < p1.__dim; i++)
        {
            is >> p1.__values[i];
        }
        return is;
    }

    const Point operator+(const Point &p1, const Point &p2) // will this need to create a temporary point to hold results & be returned??
    {
        for (int i = 0; i < p1.getDims(); ++i)
        {
            p1.__values[i] = p1.__values[i] + p2.__values[i];
        }
        return p1;
    }

    const Point operator-(const Point &p1, const Point &p2)
    {
        for (int i = 0; i < p1.getDims(); ++i)
        {
            p1.__values[i] = p1.__values[i] - p2.__values[i];
        }
        return p1;
    }

};