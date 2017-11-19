//
// Created by trima on 11/11/17.
//

#ifndef TP1_SEBIRE_FLORIAN_HISTOGRAMME_HPP
#define TP1_SEBIRE_FLORIAN_HISTOGRAMME_HPP


#include "Image2D.hpp"

class Histogramme {
public:
    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef GrayLevelImage2D::Iterator Iterator;

public:
    double histo[256];
    double histoc[256];
public:
    void init( GrayLevelImage2D & img ){
        int size = img.w() * img.h();
        std::cout << size << std::endl;
        /*** Pour @histo :
         * Pour chaque niveau de gris on va compter combien de fois on a de pixels
         * qui sont égales à ce niveau de gris
         */
        for (int i = 0; i < 256; ++i) {
            int cpt=0;

            for ( Iterator it = img.begin(), itE = img.end(); it != itE; ++it ){
                if((int) *it == i){
                    cpt++;
                }
            }
            double prop = (double) cpt/(double)size;
            histo[i] = prop;
            /***
             * Pour @histoc cumulé
             * on fait la somme des proportions de 0 à i
             */
            double propc = 0;
            for (int j = 0; j < i; ++j) {
                propc += histo[j];

            }
            histoc[i] = propc;
        }
    }
    int egalisation( int j ) const {
        return 255 * histoc[j];
    }

    template <typename InputIterator>
    void init( InputIterator it, InputIterator itE ) {
        int size = itE - it ;
        /***
         * init histo
         */
        for (int k = 0; k <256; ++k) {
            histo[k] = 0;
        }
        /***
         * On parcours l'image et on pour chaque valeur de *it on incrémente dans notre histo
         */
        for (; it != itE; ++it ){
            histo[(int) *it]++;
        }
        /***
         * Pour chaque valeur de notre histo, on divise par la taille pour avoir la proportion
         */
        for (int i = 0; i < 256; ++i) {
            histo[i] = ( double) histo[i] / double(size);

            /***
             * On calcul l'histo cumulé en même temps
             */
            double propc = 0;
            for (int j = 0; j < i; ++j) {
                propc += histo[j];

            }
            histoc[i] = propc;
        }

    }

};


#endif //TP1_SEBIRE_FLORIAN_HISTOGRAMME_HPP
