//
// Created by Konstantin Moskalenko on 23.11.2021.
//

#ifndef RIBBON_MATRIX_H
#define RIBBON_MATRIX_H


namespace pdb {
    struct Matrix {
        double value[4][4];
    };
}

#define identity() ((Matrix) { \
    .value = {                 \
        {1, 0, 0, 0},          \
        {0, 1, 0, 0},          \
        {0, 0, 1, 0},          \
        {0, 0, 0, 1},          \
    }                          \
})


#endif //RIBBON_MATRIX_H
