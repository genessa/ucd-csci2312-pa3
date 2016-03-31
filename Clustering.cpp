//
// Created by Genessa Moodie on 2/18/16.

#include <algorithm>
#include <sstream>
#include <cassert>
#include <cmath>
#include "Cluster.h"
#include "Exceptions.h"

namespace Clustering {

    LNode::LNode(const Point &p, LNodePtr lnp) : point(p)
    {
        next = lnp;
    }

    // default constructor, makes an empty cluster
    // this isn't useful in the kmeans context, so I'm commenting it out, but that might make the compiler yell
    // if so, will have it throw EmptyClusterEx.
//    Cluster::Cluster()
//    {
//        __points = nullptr;
//        __size = 0;
//    }
    Cluster::Cluster(unsigned int d) : centroid(d, *this)
    {
        __id = __idGenerator;
        __idGenerator++;
        __dimensionality = d;
        __size = 0;
        __points = nullptr;

    }

    // copy constructor which uses another Cluster as an argument
    Cluster::Cluster(const Cluster &c1) : Cluster(c1.__dimensionality)
    {
        __size = c1.getSize();
        __cpy(c1.__points);
        Centroid(c1.__dimensionality, c1);
    }

    // assignment operator
    Cluster& Cluster::operator=(const Cluster &c2)
    {
        if(this != &c2)
        {
            __size = c2.__size;
            __del();
            __cpy(c2.__points);
        }
        return *this;
    }

    // dtor
    Cluster::~Cluster(){
        __del();
    }

    unsigned int Cluster::getSize() const
    {
        return __size;
    }

    // optional delete-a-point function
    void Cluster::__del()
    {
        LNodePtr currPtr = __points;
        LNodePtr subsq;

        for(int i = 0; i < __size; ++i){
            if(__points != nullptr){
                subsq = currPtr->next;
                delete currPtr;
                currPtr = subsq;
            }
        }
        __points = nullptr; // just to tidy up anything that might be left
    }

    // optional copying function
    void Cluster::__cpy(LNodePtr pts)
    {
        if(__size != 0)
        {
            LNodePtr emptyPtr = nullptr;
            LNode *head = new LNode(pts->point,emptyPtr);
            LNodePtr currPtr = pts->next;
            __points = head;
            LNodePtr curr = __points;

            while(currPtr != nullptr)
            {
                curr->next = new LNode(currPtr->point,emptyPtr);
                curr = curr->next;
                currPtr = currPtr->next;
            }
        }
    }


    void Cluster::add(const Point &p1)
    {
        if (__points == nullptr)
        {
            LNode *N = new LNode(p1, nullptr);
            __points = N;
            ++__size;
            return;
        }

        if (__points->next == nullptr)
        {
            LNode *N = new LNode(p1, nullptr);
            if(N->point < __points->point)
            {
                N->next = __points;
                __points = N;
                ++__size;
                return;
            }

            else
            {
                __points->next = N;
                ++__size;
                return;
            }
        }

        LNode *N = new LNode(p1, nullptr);
        LNodePtr temp = __points->next;
        LNodePtr prev = __points;

        if(N->point < __points->point){
            __points = N;
            N->next = prev;
            __size++;
            return;
        }

        if(N->point < temp->point){
            prev->next = N;
            N->next = temp;
            ++__size;
            return;
        }

        while (temp->next != nullptr) {
            if(N->point < temp->point){
                prev = N;
                N->next = prev;
                ++__size;
                return;
            }
            temp = temp->next;
            prev = prev->next;
        }
        temp->next = N;
        ++__size;
    }


    const Point &Cluster::remove(const Point &p1)
    {
        // Check to see if p1 is already in the cluster
        LNodePtr temp = __points;

        if (temp->point == p1)
        {
            temp = __points;

            if (__size > 0)
            {
                __points = __points->next;
                --__size;
            }
            delete temp;
        }

        else
        {
            int i = 0;
            LNodePtr prev = temp;
            temp = temp->next;

            for ( ; i < __size; i++)
            {
                if (temp->point == p1)
                {
                    if (temp->next == nullptr)
                    {
                        prev->next = nullptr;
                        delete temp;
                        __size--;
                    }
                    else
                    { prev->next = temp->next;
                    }
                }
                temp = temp->next;
                prev = prev->next;
            }
        }
        return p1;
    }

    const Point &Cluster::operator[](unsigned int index) const
    {
        if( __points == nullptr)
            throw EmptyClusterEx();
        LNodePtr temp;
        temp = __points;

        if(index == 0)
        {
            return __points->point;
        }

        for(int i = 0; i < index; ++i)
        {
            temp = temp->next;
        }
        return temp->point;
    }

    bool operator==(const Cluster & c1, const Cluster &c2)
    {
        if(c1.__size != c2.__size)
        {
            return false;
        }

        for(int i = 0; i < c2.__size; i++)
        {
            if(c1[i] != c2[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Cluster & c1, const Cluster & c2)
    {
        return !(c1 == c2); // Rewrote to use == operator instead of copypastaing and reversing its contents
    }

    // using add function
    Cluster &Cluster::operator+=(const Point & p1)
    {
        this->add(p1);
        return *this;
    }

    // using remove function
    Cluster &Cluster::operator-=(const Point & p1){
        this->remove(p1);
        return *this;
    }

    // Members: Compound assignment (Cluster argument)
    Cluster &Cluster::operator+=(const Cluster & c2) // union of two clusters
    {
        for(int i = 0; i < c2.getSize(); i++)
        {
            if(!(this->contains(c2[i]))){
                this->add(c2[i]);
            }
        }

        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster & c2) // (asymmetric) difference aka intersection
    {
        for(int i = 0; i < c2.getSize(); i++)
        {
            if(this->contains(c2[i]))
            {
                this->remove(c2[i]);
            }
        }
        return *this;
    }

    // Friends: Arithmetic (Cluster and Point)
    const Cluster operator+(const Cluster &c1, const Point &p1)
    {
        Cluster *c2 = new Cluster(c1);

        if(!(c2->contains(p1)))
        { c2->add(p1); }

        else
        { return c1; }

        return *c2;
    }

    const Cluster operator-(const Cluster &c1, const Point &p1)
    {
        Cluster *c2 = new Cluster(c1);

        if(c2->contains(p1))
        { c2->remove(p1); }

        else
        { return c1; }

        return *c2;
    }

    // Friends: Arithmetic (two Clusters)
    const Cluster operator+(const Cluster &c1, const Cluster &c2)
    {
        Cluster *c3 = new Cluster(c1);
        Cluster *c4 = new Cluster(c2);

        for(int i = 0; i < c4->getSize(); i++)
        {
            if(!(c3->contains(c2[i])))
            { c3->add(c2[i]); }
        }

        delete c4;
        return *c3;
    }

    const Cluster operator-(const Cluster &c1, const Cluster &c2)
    {
        Cluster *c3 = new Cluster(c1);
        Cluster *c4 = new Cluster(c2);

        for(int i = 0; i < c3->getSize(); i++)
        {
            if(c3->contains(c2[i]))
            { c3->remove(c2[i]); }
        }
        delete c4;
        return *c3; // this one won't let me return by value
    }

    std::ostream &operator<<(std::ostream &os, const Cluster & c1)
    {
        LNodePtr temp = c1.__points;
        for(int i = 0; i < c1.__size; i++)
        {
            os << temp->point << std::endl;
            temp = temp->next;
        }
        return os;
    }

    // Function is messy, and probably has a lot of unnecessary stuff, but works.
    std::istream &operator>>(std::istream &is, Cluster& c1)
    {
        std::string temp;
        std::getline(is, temp);
        std::stringstream ss_temp(temp);

        int dim = 0;
        double temp_d = 0;

        while (!is.eof())
        {
            dim = temp.length()/24; // 24 is what this system allocates for string; length function returns size in bytes
            ss_temp.ignore(',');
            temp = ss_temp.str();
            temp_d = stod(temp);
        }

        bool run = false;
        int index = 0;
        while (is.peek() != EOF)
        {
            Point *nPoint = new Clustering::Point(dim);
            if (run)
            {
                temp = "";
                std::getline(is, temp);
                temp.erase(remove_if(temp.begin(), temp.end(), isspace), temp.end());
            }


            while ((ss_temp.peek() != '\n') || (ss_temp.peek() != '\r') || (ss_temp.peek() != EOF)) {
                ss_temp >> temp_d;
                nPoint->setValue(index, temp_d);
                if ((ss_temp.peek() == '\n') || (ss_temp.peek() == '\r') || (ss_temp.peek() == EOF)) {
                    run = true;
                    c1.add(*nPoint);
                    index = 0;
                    delete nPoint;
                    break;
                } else {
                    ss_temp.ignore();
                    index++;
                }
            }
        }
        return is;
    }



// pretty sure this is the same as old clustering's contains function..
bool Cluster::__in(const Point &p) const
{
    LNodePtr temp;

    if(p == __points->point)
    { return true; }

    if(__points->next == nullptr)
    { return false; }

    temp = __points->next;

    for(int i = 1; i < __size; i++)
    {
        if(temp->point == p)
        { return true; }
        temp = temp->next;
    }
    return false;
}

    Cluster::Centroid::Centroid(unsigned int d, const Cluster &c) : __c(c), __p(d)
    {
        if (c.__size == 0)
        {
            __valid = false;
            toInfinity();
        }

        __dimensions = d;
        __valid = true;
    }


    // getters/setters
    const Point Cluster::Centroid::get() const // doesn't check for validity
    {
        return __p;
    }

    void Cluster::Centroid::set(const Point &p) // sets to valid
    {
        __p = p;
        __valid = true;
    }

    bool Cluster::Centroid::isValid() const
    {
        return __valid;
    }

    void Cluster::Centroid::setValid(bool valid)
    {
        __valid = valid;
    }

    // functions
    void Cluster::Centroid::compute()
    {
        // first check if centroid is empty
        if (__c.__points == nullptr)
        {
            assert(__c.__size == 0);
            toInfinity();
            return;
        }

        LNodePtr curr = __c.__points;
        int sizecheck = 0;

        while (curr != nullptr)
        {
            __p += curr->point / __c.getSize();
            curr = curr->next;
            sizecheck++;
        }
        assert(sizecheck == curr->point); // I don't think that point is right...
    }


    bool Cluster::Centroid::equal(const Point &p1) const
    {
        bool isEqual = false;
        for (int i = 0; i < __dimensions; i++)
        {
            if (__p[i]==p1[i])
                isEqual = true;
        }
        return isEqual;
    }

    void Cluster::Centroid::toInfinity() // and beyond.. har har
    {
        for (int i = 0; i < __dimensions; i++)
        {
            __p[i] = INFINITY;
        }
    }

//    class Move {
//        const Point &__p;
//        Cluster &__from, &__to;

        Cluster::Move::Move(const Point &p, Cluster &from, Cluster &to) : __p(p), __from(from), __to(to)
        { }

        void Cluster::Move::perform()
        {
            // first check if there's anything to move in either from or to
            if (__from.__size == 0)
                __from.centroid.toInfinity();
            if (__to.__size == 0)
                __to.centroid.toInfinity();

            // use add on the remove, since we want the thing completely moved source -> destination
            if (__from.contains(__p))
                __to.add(__from.remove(__p));


        }

};
