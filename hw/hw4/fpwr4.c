float u2f(unsigned int x) {
    union {
        unsigned p;
        float f;
    } u;
    u.p = x;
    return u.p;
}

float fpwr4(int x) {

    unsigned exp, frac;
    unsigned u;

    if (x < -74) {
        exp = 0;
        frac = 0;

    } else if (x < -63) {
        exp = 0;
        frac = 1 << ((2*(x+74))+1);
    } else if (x < 64) {
        exp = 2*(x+63) + 1;
        frac = 0;
    } else {
        exp = 255;
        frac = 0;
    }

    u = exp << 23 | frac;
    return u2f(u);
}

