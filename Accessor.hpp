//
// Created by trima on 11/11/17.
//

#ifndef TP2_ACCESSOR_HPP
#define TP2_ACCESSOR_HPP


#include "Color.hpp"
/// Accesseur trivial générique
template <typename TValue>
struct TrivialAccessor {
    typedef TValue Value;
    typedef Value Argument;
    typedef Value& Reference;
    // Acces en lecture.
    static Value access( const Argument & arg )
    { return arg; }
    // Acces en écriture.
    static Reference access( Argument & arg )
    { return arg; }
};

// Accesseur trivial pour une image en niveaux de gris
typedef TrivialAccessor<unsigned char> GrayLevelTrivialAccessor;
// Accesseur trivial pour une image en couleur.
typedef TrivialAccessor<Color> ColorTrivialAccessor;
/// Accesseur à la composante verte.
struct ColorGreenAccessor {
    typedef unsigned char Value;
    typedef Color Argument;
    /// Même astuce que pour les références à un bit dans un tableau de bool.
    struct ColorGreenReference {
        Argument & arg;
        ColorGreenReference( Argument & someArg ) : arg( someArg ) {}
        // Accesseur lvalue (écriture)
        // permet d'écrire *it = 120 pour changer l'intensité du vert
        ColorGreenReference& operator=( Value val )
        {
            arg.green = val;
            return *this;
        }
        // Accesseur rvalue (lecture)
        // permet d'écrire *it pour récupérer l'intensité du vert
        operator Value() const
        {
            return arg.green;  // arg.green est de type Value.
        }
    };
    typedef ColorGreenReference Reference;
    // Acces en lecture.
    static Value access( const Argument & arg )
    { return arg.green; }
    // Acces en écriture.
    static Reference access( Argument & arg )
    { return ColorGreenReference( arg ); }
};

#endif //TP2_ACCESSOR_HPP
