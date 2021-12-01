//
// Created by eseiler@INTRANET.EPFL.CH on 28.11.21.
//

#ifndef PROJECT_CLASSICCHORD_H
#define PROJECT_CLASSICCHORD_H
#include "AbstractSolver.h"

class ClassicChord : public AbstractSolver{
    public:

    // Generator and Destructor
    ClassicChord();
    ~ClassicChord() override;

    //Solve method
    void SolveEquation() const override;

};


#endif //PROJECT_CLASSICCHORD_H
