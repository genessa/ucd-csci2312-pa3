// File: Exceptions.cpp
//
// Genessa Moodie
// CSCI 2312
// PA3

#include <iostream>
#include "Exceptions.h"

namespace Clustering {

    using std::endl;

//    class OutOfBoundsEx {
//        unsigned int __current;
//        int __rhs;
//        std::string __name;

    OutOfBoundsEx::OutOfBoundsEx(unsigned int c, int r)
    {
        __current = c;
        __rhs = r;
        __name = "Out of bounds exception";
    }

    unsigned int OutOfBoundsEx::getCurrent() const { return __current; }

    int OutOfBoundsEx::getRhs() const { return __rhs; }

    std::string OutOfBoundsEx::getName() const { return __name; }

    std::ostream &operator<<(std::ostream &os, const OutOfBoundsEx &ex)
    {
        // send ex's details to os in proper format, return os
        os << ex.__name << " : " << ex.__current << ex.__rhs << endl;
        return os;
    }




//    class DimensionalityMismatchEx {
//        unsigned int __current, __rhs;
//        std::string __name;
//

    DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned int c, unsigned int r)
        {
            __current = c;
            __rhs = r;
            __name = "Dimensionality mismatch exception";
        }

    unsigned int DimensionalityMismatchEx::getCurrent() const { return __current; }

    unsigned int DimensionalityMismatchEx::getRhs() const { return  __rhs; }

    std::string DimensionalityMismatchEx::getName() const { return __name; }

    std::ostream &operator<<(std::ostream &os, const DimensionalityMismatchEx &ex)
    {
        // possibly copypasta from OutOfBoundsEx's
        os << ex.__name << " : " << ex.current << ex.rhs << endl;
        return os;
    }



//    class ZeroClustersEx {
//        std::string __name;

    ZeroClustersEx()
    {
        // nothing to initialise but name. whee.
        __name = "Zero clusters exception";
    }

    std::string ZeroClustersEx::getName() const { return __name; }

    std::ostream &operator<<(std::ostream &os, const ZeroClustersEx &ex)
    {
        // Just name to send out here.
        os << ex.__name << endl;
    }



//    class DataFileOpenEx {
//        std::string __name, __filename;
//
    DataFileOpenEx::DataFileOpenEx(std::string filename)
    {
        __filename = filename;
        __name = "Data file open exception";
    }

    std::string DataFileOpenEx::getFilename() const { return __filename; }

    std::string DataFileOpenEx::getName() const { return __name; }

    std::ostream &operator<<(std::ostream &os, const DataFileOpenEx &ex)
    {   // Also just a name to print out
        os << ex.__name << endl;
        return os;
    }



//    class ZeroDimensionsEx {
//        std::string __name;
//
//
    ZeroDimensionsEx::ZeroDimensionsEx()
    {
        __name = "Zero dimensions exception";
    }

        std::string ZeroDimensionsEx::getName() const { return __name; }

        std::ostream &operator<<(std::ostream &os, const ZeroDimensionsEx &ex)
        {
            os << ex.__name << endl;
            return os;
        }



//    class EmptyClusterEx {
//        std::string __name;

        EmptyClusterEx::EmptyClusterEx()
        {
            __name = "Empty cluster exception";
        }
        std::string EmptyClusterEx::getName() const { return __name; }

        std::ostream &operator<<(std::ostream &os, const EmptyClusterEx &ex)
        {
            os << ex.__name << endl;
            return os;
        }

};


#endif //CLUSTERING_EXCEPTIONS_H
//
// Created by Genessa Moodie on 3/17/16.
//

