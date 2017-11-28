//
// Created by antoine on 27/11/17.
//

#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWriter.hpp"
#include "Accessor.hpp"
#include "Histogramme.hpp"
#include "Image2DReader.hpp"

int main(int argc, char** argv )
{
    typedef unsigned char Byte;
    typedef Image2D<Color> ColorImage2D;
    typedef Image2D<Byte> GrayLevelImage2D;
    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;
    typedef GrayLevelImage2D::Iterator GrayLevelIterator;

    if ( argc < 3 )
    {
        std::cerr << "Usage: sepia <input.pgm> <output.pgm>" << std::endl;
        return 0;
    }
    ColorImage2D img;

    std::ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = Image2DReader<Color>::read( img, input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();
    //std::cout << "import sucessed" << std::endl;

    for ( ColorImage2D::GenericIterator<ColorValueAccessor> it = img.begin< ColorValueAccessor >(), itE = img.end< ColorValueAccessor >(); it != itE; ++it )
    {
        Color c = (*it).arg;
        //int average = (c.red + c.green + c.blue)/3;
        double red = (c.red * .393) + (c.green *.769) + (c.blue * .189);
        red = std::min(255.0,red);
        red = std::max(0.0,red);

        double green = (c.red * .349) + (c.green *.686) + (c.blue * .168);
        green = std::min(255.0,green);
        green = std::max(0.0,green);

        double blue = (c.red * .272) + (c.green *.534) + (c.blue * .131);
        blue = std::min(255.0,blue);
        blue = std::max(0.0,blue);
        (*it).arg = Color((Byte)red,(Byte)green,(Byte)blue);
    }

    std::ofstream output( argv[2]);
    bool ok2 = Image2DWriter<Color>::write( img, output, false );
    if ( !ok2 ) {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}

