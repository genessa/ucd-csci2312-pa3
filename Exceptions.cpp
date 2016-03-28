// File: Exceptions.cpp
//
// Genessa Moodie
// CSCI 2312
// PA3

#include <iostream>

namespace Clustering {

//    class OutOfBoundsEx {
//        unsigned int __current;
//        int __rhs;
//        std::string __name;

    OutOfBoundsEx::OutOfBoundsEx(unsigned int c, int r)
    {
        __current = c;
        __rhs = r;
    }

    unsigned int OutOfBoundsEx::getCurrent() const { return __current; }

    int OutOfBoundsEx::getRhs() const { return __rhs; }

    std::string OutOfBoundsEx::getName() const { return __name; }

    std::ostream &operator<<(std::ostream &os, const OutOfBoundsEx &ex)
    {
        // send ex to os, return os
        os << ex << endl;
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
        }

    unsigned int DimensionalityMismatchEx::getCurrent() const { return __current; }

    unsigned int DimensionalityMismatchEx::getRhs() const { return  __rhs; }

    std::string DimensionalityMismatchEx::getName() const { return __name; }

    std::ostream &operator<<(std::ostream &os, const DimensionalityMismatchEx &ex)
    {
        // possibly copypasta from OutOfBoundsEx's
        os << ex << endl;
        return os;
    }



//    class ZeroClustersEx {
//        std::string __name;

    ZeroClustersEx()
    {
        // initialise to infinity clusters
    }

    std::string ZeroClustersEx::getName() const { return __name; }

    std::ostream &operator<<(std::ostream &os, const ZeroClustersEx &ex)
    {
        // Not super sure what to put here.
    }



//    class DataFileOpenEx {
//        std::string __name, __filename;
//
    DataFileOpenEx::DataFileOpenEx(std::string filename)
    {
        __filename = filename;
    }

    std::string DataFileOpenEx::getFilename() const { return __filename; }

    std::string DataFileOpenEx::getName() const { return __name; }

    std::ostream &operator<<(std::ostream &os, const DataFileOpenEx &ex);



    class ZeroDimensionsEx {
        std::string __name;

    public:
        ZeroDimensionsEx();
        std::string getName() const;

        friend std::ostream &operator<<(std::ostream &os, const ZeroDimensionsEx &ex);
    };


    class EmptyClusterEx {
        std::string __name;

    public:
        EmptyClusterEx();
        std::string getName() const;

        friend std::ostream &operator<<(std::ostream &os, const EmptyClusterEx &ex);
    };
}


#endif //CLUSTERING_EXCEPTIONS_H
//
// Created by Genessa Moodie on 3/17/16.
//

