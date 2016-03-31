//
// Created by Genessa Moodie on 3/17/16.
//

#include <cassert>
#include "KMeans.h"
#include "Exceptions.h"

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
        if (k==0)
        { throw ZeroClustersEx(); }

        std::ifstream inFile;
        inFile.open("filename");
        if (!inFile)
        { throw DataFileOpenEx(filename); }

        __dimensionality = dim;
        __k = k;
        __iFileName = filename;
        __maxIter = maxIter;
        __numNonempty = 1;
        __numIter = 0;
    }

        KMeans::~KMeans()
        {
            for (int i = 0; i < __k; ++i)
            {
                delete(__clusters[i]);
                delete(__initCentroids[i]);
            }
            delete [] __clusters;
            delete [] __initCentroids;
        }

        // accessors
        unsigned int KMeans::getMaxIter() { return __maxIter; }
        unsigned int KMeans::getNumIters() { return __numIter; }
        unsigned int KMeans::getNumNonemptyClusters() { return __numNonempty; } // numpty.
        unsigned int KMeans::getNumMovesLastIter() { return __numMovesLastIter; }

        // element access (for testing, no bounds checking)
        Cluster &KMeans::operator[](unsigned int u) // can copypasta?
        {
            return *__clusters[u];
        }
        const Cluster &KMeans::operator[](unsigned int u) const
        {
            return *__clusters[u];
        }


        // write out the results to a file
        std::ostream &operator<<(std::ostream &os, const KMeans &kmeans)
        {
            for (int i = 0; i < kmeans.__k; i++ )
                os << kmeans[i];

            return os;
        }

        // clustering functions
        void KMeans::run()
        {
            assert(__initCentroids != nullptr);
            unsigned int moves = 100;
            while (moves > 0 && __numIter < __maxIter)
            {
                moves = 0;
                for (int c = 0; c < __k; ++c)
                {
                    for (int p = 0; p < __clusters[c]->getSize(); p++)
                    {
                        int closeCentr;
                        closeCentr = (*(__clusters[c]))[p].distanceTo(__clusters[c]->centroid.get());
                        if (closeCentr != c)
                        {
                            Clustering::Cluster::Move *temp = new Clustering::Cluster::Move( ((*__clusters)[c])[p], (*__clusters[c]), (*__clusters[closeCentr]) );
                            temp->perform();
                                    moves++;
                        }
                    }
                }
                __numIter++;
            }

             //something about move.perform() goes in here
        }
}