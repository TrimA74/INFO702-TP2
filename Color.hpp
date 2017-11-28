//
// Created by trima on 11/11/17.
//

#ifndef TP2_COLOR_HPP
#define TP2_COLOR_HPP

#include <vector>
#include <iostream>
#include <exception>
#include <iterator>
#include <string> // chaînes de caractères
#include <fstream> // flux sur les fichiers
#include <sstream> // flux sur les chaînes de caractères

/**
   Représente une couleur avec un codage RGB. Ce codage utilise 3
   octets, le premier octet code l'intensité du rouge, le deuxième
   l'intensité du vert, le troisième l'intensité du bleu.
*/
struct Color {
    typedef unsigned char Byte;
    /// Code les 3 canaux RGB sur 3 octets.
    Byte red, green, blue;
    Color() {}
    /// Crée la couleur spécifiée par (_red,_green,_blue).
    Color( Byte _red, Byte _green, Byte _blue )
            : red( _red ), green( _green ), blue( _blue ) {}
    /// @return l'intensité de rouge (entre 0.0 et 1.0)
    float r() const { return ( (float) red ) / 255.0; }
    /// @return l'intensité de vert (entre 0.0 et 1.0)
    float g() const { return ( (float) green ) / 255.0; }
    /// @return l'intensité de bleu (entre 0.0 et 1.0)
    float b() const { return ( (float) blue ) / 255.0; }
    /// Sert à désigner un canal.
    enum Channel { Red, Green, Blue };
    /// @return le canal le plus intense.
    Channel argmax() const
    {
        if ( red >= green ) return red >= blue ? Red : Blue;
        else                return green >= blue ? Green : Blue;
    }
    /// @return l'intensité maximale des canaux
    float max() const { return std::max( std::max( r(), g() ), b() ); }
    /// @return l'intensité minimale des canaux
    float min() const { return std::min( std::min( r(), g() ), b() ); }
    /**
       Convertit la couleur RGB en le modèle HSV (TSV en français).
       @param h la teinte de la couleur (entre 0 et 359), hue en anglais.
       @param s la saturation de la couleur (entre 0.0 et 1.0)
       @param v la valeur ou brillance de la couleur (entre 0.0 et 1.0).
    */
    void getHSV( int & h, float & s, float & v ) const
    {
        // Taking care of hue
        if ( max() == min() ) h = 0;
        else {
            switch ( argmax() ) {
                case Red:   h = ( (int) ( 60.0 * ( g() - b() ) / ( max() - min() ) + 360.0 ) ) % 360;
                    break;
                case Green: h = ( (int) ( 60.0 * ( b() - r() ) / ( max() - min() ) + 120.0 ) );
                    break;
                case Blue:  h = ( (int) ( 60.0 * ( r() - g() ) / ( max() - min() ) + 240.0 ) );
                    break;
            }
        }
        // Taking care of saturation
        s = max() == 0.0 ? 0.0 : 1.0 - min() / max();
        // Taking care of value
        v = max();
    }
    /**
       TODO: Convertit la couleur donnée avec le modèle HSV (TSV en
       français) en une couleur RGB.
    */
    void setHSV( int h, float s, float v )
    {

        if( 1.0 < v){
            std::cout << "problem youston" << std::endl;
        }
        int ti =(h/60) % 6;
        float f = (h/60.0f) - ti;
        float l = v * ( 1 - s);
        float m = v * ( 1 - f * s);
        float n = v * (1 - (1 - f) * s);
        v *= 255.0;
        m *= 255.0;
        n *= 255.0;
        l *= 255.0;
        switch(ti){
            case 0:
                red = (Byte) v;
                green = (Byte) n;
                blue = (Byte) l;
                break;
            case 1:
                red = (Byte) m;
                green = (Byte) v;
                blue = (Byte) l;
                break;
            case 2:
                red = (Byte) l;
                green = (Byte) v;
                blue = (Byte) n;
                break;
            case 3:
                red = (Byte) l;
                green = (Byte) m;
                blue = (Byte) v;
                break;
            case 4:
                red = (Byte) n;
                green = (Byte) l;
                blue = (Byte) v;
                break;
            case 5:
                red = (Byte) v;
                green = (Byte) l;
                blue = (Byte) m;
                break;
            default :
                std::cout << "problem youston" << std::endl;
                break;
        }
    }
};


#endif //TP2_COLOR_HPP
