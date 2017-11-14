//
// Created by trima on 11/11/17.
//

#include "Histogramme.hpp"

void Histogramme::init(GrayLevelImage2D &img) {
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

int Histogramme::egalisation(int j) const {
    return 255 * histoc[j];
}
