//
// Created by Genessa Moodie on 3/17/16.
//

#include "KMeans.h"

namespace Clustering {


//    class KMeans {
//        unsigned int __dimensionality;
//        unsigned int __k;
//        Cluster **__clusters;
//        Point **__initCentroids;
//        std::string __iFileName;
//        unsigned int __maxIter;
//        unsigned int __numIter;
//        unsigned int __numNonempty;
//        unsigned int __numMovesLastIter;
//
KMeans::KMeans(unsigned int dim, unsigned int k, std::string filename, unsigned int maxIter)
    {
        __dimensionality = dim;
        __k = k;
        __iFileName = filename;
        __maxIter = maxIter;
    }

        // no copying
        KMeans(const KMeans &) = delete;
        KMeans &operator=(const KMeans &) = delete;

        ~KMeans();

        // accessors
        unsigned int getMaxIter();
        unsigned int getNumIters();
        unsigned int getNumNonemptyClusters();
        unsigned int getNumMovesLastIter();

        // element access (for testing, no bounds checking)
        Cluster &operator[](unsigned int u);
        const Cluster &operator[](unsigned int u) const;

        // write out the results to a file
        friend std::ostream &operator<<(std::ostream &os, const KMeans &kmeans);

        // clustering functions
        void run();
}