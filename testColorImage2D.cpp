//
// Created by trima on 11/11/17.
//
// file testColorImage2D.cpp
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"

int main(int argc, char** argv )
{
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;
    /*
    ColorImage2D img( 256, 256, Color( 0, 0, 0 ) );
    Iterator it = img.begin();

    for ( int y = 0; y < 256; ++y )
        for ( int x = 0; x < 256; ++x )
        {
            *it++ = Color( y, x, (2*x+2*y) % 256 );
        }
    */
    if ( argc < 3 )
    {
        std::cerr << "Usage: testColor <input.pgm> <output.pgm>" << std::endl;
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
    std::cout << "import sucessed" << std::endl;

    std::ofstream output( argv[2] );
    bool ok2 = Image2DWriter<Color>::write( img, output, false );
    if ( !ok2 ) {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}
