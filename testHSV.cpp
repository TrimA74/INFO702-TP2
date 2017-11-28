//
// Created by trima on 28/11/17.
//
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"
#include "Accessor.hpp"
#include "Histogramme.hpp"
int main(int argc, char** argv )
{
    typedef Image2D<Color> ColorImage2D;
    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;
    typedef GrayLevelImage2D::Iterator GrayLevelIterator;

    if ( argc < 3 )
    {
        std::cerr << "Usage: egaliseur-couleur <input.pgm> <output.pgm>" << std::endl;
        return 0;
    }
    ColorImage2D img2;

    std::ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = Image2DReader<Color>::read( img2, input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();
    std::cout << "import sucessed" << std::endl;


    for ( ColorImage2D::GenericIterator<ColorValueAccessor> it = img2.begin< ColorValueAccessor >(), itE = img2.end< ColorValueAccessor >(); it != itE; ++it )
    {
        float s,v;
        int h;
        //float newval = (float) val / 255.0;
        (*it).arg.getHSV(h,s,v);
        (*it).arg.setHSV(h,s,v);
    }

    std::ofstream output( argv[2]);
    bool ok2 = Image2DWriter<Color>::write( img2, output, false );
    if ( !ok2 ) {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}
