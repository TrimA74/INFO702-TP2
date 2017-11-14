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
int main( int argc, char** argv )
{
    typedef Image2D<Color> ColorImage2D;
    typedef Image2DReader<Color> ColorImage2DReader;
    typedef ColorImage2D::Iterator ColorIterator;
    if ( argc < 2 )
    {
        std::cerr << "Usage: save-channels <input.ppm>" << std::endl;
        return 0;
    }
    ColorImage2D img;
    std::ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = ColorImage2DReader::read( img, input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();
    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef Image2DWriter<unsigned char> GrayLevelImage2DWriter;
    typedef GrayLevelImage2D::Iterator GrayLevelIterator;
    GrayLevelImage2D img2( img.w(), img.h() );
    GrayLevelImage2D img3( img.w(), img.h() );
    GrayLevelImage2D img4( img.w(), img.h() );

    //---------------------------BLUE-------------------------------
    // vvvvvvvvv Toute la transformation couleur -> canal blue est ici vvvvvvvvvvvv
    //
    // Servira à parcourir la composante verte de l'image couleur.
    typedef ColorImage2D::GenericConstIterator< ColorBlueAccessor > ColorBlueConstIterator;
    // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
    ColorBlueConstIterator itBlue = img.begin< ColorBlueAccessor >();
    // On écrit la composante verte dans l'image en niveaux de gris.
    for ( GrayLevelIterator it = img3.begin(), itE = img3.end();
          it != itE; ++it )
    {
        *it = *itBlue;
        ++itBlue;
        // NB: si on veut faire *itGreen++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }
    //-----------------------------------------------------------------------------
    std::ofstream output( "papillon_blue.ppm" ); // récupère le 2eme argument.
    bool ok2 = GrayLevelImage2DWriter::write( img3, output, false );
    if ( !ok2 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();


    //----------------------------GREEN----------------------------------------
    // vvvvvvvvv Toute la transformation couleur -> canal vert est ici vvvvvvvvvvvv
    //
    // Servira à parcourir la composante verte de l'image couleur.
    typedef ColorImage2D::GenericConstIterator< ColorGreenAccessor > ColorGreenConstIterator;
    // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
    ColorGreenConstIterator itGreen = img.begin< ColorGreenAccessor >();
    // On écrit la composante verte dans l'image en niveaux de gris.
    for ( GrayLevelIterator it = img2.begin(), itE = img2.end();
          it != itE; ++it )
    {
        *it = *itGreen;
        ++itGreen;
        // NB: si on veut faire *itGreen++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }
    //-----------------------------------------------------------------------------
    std::ofstream output2( "papillon_vert.ppm" );
    ok2 = GrayLevelImage2DWriter::write( img2, output2, false );
    if ( !ok2 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();


    //---------------------------RED-------------------------------
    // vvvvvvvvv Toute la transformation couleur -> canal blue est ici vvvvvvvvvvvv
    //
    // Servira à parcourir la composante verte de l'image couleur.
    typedef ColorImage2D::GenericConstIterator< ColorRedAccessor > ColorRedConstIterator;
    // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
    ColorRedConstIterator itRed = img.begin< ColorRedAccessor >();
    // On écrit la composante verte dans l'image en niveaux de gris.
    for ( GrayLevelIterator it = img4.begin(), itE = img4.end();
          it != itE; ++it )
    {
        *it = *itRed;
        ++itRed;
        // NB: si on veut faire *itGreen++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }
    //----------------------------------------------------------------------------
    std::ofstream output3( "papillon_red.ppm" );
    ok2 = GrayLevelImage2DWriter::write( img4, output3, false );
    if ( !ok2 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();


    return 0;
}
