//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#ifndef PROJECT_NEWTON_H
#define PROJECT_NEWTON_H

#include "AbstractSolver.h"

class Newton : public AbstractSolver {
public:

    //Generation and destruction methods
    Newton();
    ~Newton() override;

    // Solve method
    void SolveEquation() const override;

};



#endif //PROJECT_NEWTON_H
