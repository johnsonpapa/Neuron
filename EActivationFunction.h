#ifndef EACTIVATIONFUNCTION_H_INCLUDED
#define EACTIVATIONFUNCTION_H_INCLUDED

enum EActivationFunction
{
    // 0
    LINEAR, // Identity

    // 1
    HEAVISIDE, // Binary step

    // 2
    LOGISTIC,

    // 3
    SOFTMAX,

    // 4
    TANH, // Hyperbolic tangent

    // 5
    TANH01, // Hyperbolic tangent but limited within the range of 0 and 1

    // 6
    RECTIFIED_LINEAR_UNIT,

    // 7
    ARCTAN,

    // 8
    ARCTAN01, // arctan 0 to 1

    // 9
    SYMMETRICAL_HARD_LIMIT,

    // 10
    SINUSOID, // sin

    // 11
    SINUSOID01, // sin 0 to 1

    // 12
    GAUSSIAN, // A Radial Basis Function in RBF networks

    // 13
    NOT_SPECIFIED
};

#endif // EACTIVATIONFUNCTION_H_INCLUDED
