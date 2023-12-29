#ifndef SIDE_H
#define SIDE_H

#define OTHER_SIDE(x) ((x) == A ? B : A)

typedef enum side_e { A, B } side;

#endif // SIDE_H