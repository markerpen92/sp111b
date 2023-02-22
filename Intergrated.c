#include <stdio.h>

double integral(double (*f)(double x) , double t1 , double t2) {
        double sum = 0.0;
        double dx=0.0001;
        for(double x=t1 ; x<t2 ; x+=dx)
        {
            double dArea = f(x)*dx;
            sum += dArea;
        }
        return sum;
}

double square(double x) {
    return x*x;
}

int main() {
    printf("integral(square, 0.0, 2.0)=%f\n", integral(square, 0.0, 2.0));
}