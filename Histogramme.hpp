//
// Created by trima on 11/11/17.
//

#ifndef TP1_SEBIRE_FLORIAN_HISTOGRAMME_HPP
#define TP1_SEBIRE_FLORIAN_HISTOGRAMME_HPP


#include "GrayLevelImage2D.hpp"

class Histogramme {
public:
    typedef GrayLevelImage2D::Iterator Iterator;

private:
    double histo[256];
    double histoc[256];
public:
    void init( GrayLevelImage2D & img );
    int egalisation( int j ) const;

};


#endif //TP1_SEBIRE_FLORIAN_HISTOGRAMME_HPP
