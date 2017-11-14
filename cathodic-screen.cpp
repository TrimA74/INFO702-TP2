//
// Created by trima on 14/11/17.
//
#include <cmath>
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2DReader.hpp"
#include "Image2DWriter.hpp"
#include "Accessor.hpp"
int main( int argc, char** argv ) {
    typedef Image2D<Color> ColorImage2D;
    typedef Image2DReader<Color> ColorImage2DReader;
    typedef Image2DWriter<Color> ColorImage2DWriter;
    typedef ColorImage2D::Iterator ColorIterator;
    if (argc < 3) {
        std::cerr << "Usage: cathodic-screen <input.ppm> <output.ppm>" << std::endl;
        return 0;
    }
    ColorImage2D img;
    std::ifstream input(argv[1]); // récupère le 1er argument.
    bool ok = ColorImage2DReader::read(img, input);
    if (!ok) {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();

    typedef ColorImage2D::GenericIterator< ColorRedAccessor >   ColorRedConstIterator;
    typedef ColorImage2D::GenericIterator< ColorGreenAccessor > ColorGreenConstIterator;
    typedef ColorImage2D::GenericIterator< ColorBlueAccessor >  ColorBlueConstIterator;
    ColorRedConstIterator   itRed   = img.begin< ColorRedAccessor >();
    ColorGreenConstIterator itGreen = img.begin< ColorGreenAccessor >();
    ColorBlueConstIterator  itBlue  = img.begin< ColorBlueAccessor >();
    // On écrit la composante verte dans l'image en niveaux de gris.
    int x = 0;
    for ( ColorIterator it = img.begin(), itE = img.end();
          it != itE; ++it )
    {
        switch ( x % 3 ) {
            case 0: *itGreen = *itBlue  = 0; break;
            case 1: *itRed   = *itBlue  = 0; break;
            case 2: *itRed   = *itGreen = 0; break;
        }
        ++itRed; ++itGreen; ++itBlue;
        x = ( x+1 ) % img.w();
    }
    std::ofstream output2(argv[2]);
    bool ok2 = ColorImage2DWriter::write( img, output2, false );
    if ( !ok2 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output2.close();


}
