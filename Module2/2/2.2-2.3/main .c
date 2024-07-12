#include <stdio.h>
#include <stdarg.h>

double Sum(int n, ...){
    double result =0;
    va_list args;
    va_start(args,n);
    for (int i = 0; i < n; i++)
        result+=va_arg(args,double);
    va_end(args);
    return result;
}

double Sub(int n, ...){
    double result =0;
    va_list args;
    va_start(args,n);
    for (int i = 0; i < n; i++)
        result-=va_arg(args,double);
    va_end(args);
    return result;
}
double Mult(int n, ...){
    double result =0;
    va_list args;
    va_start(args,n);
    for (int i = 0; i < n; i++)
        result*=va_arg(args,double);
    va_end(args);
    return result;
}
double Div(int n, ...){
    double result =0;
    va_list args;
    va_start(args,n);
    for (int i = 0; i < n; i++){
        if(va_arg(args,double)==0){
            printf("Делить на ноль нельзя");
        }
        result/=va_arg(args,double);

    }
    va_end(args);
    return result;
}







int main(){
   


    return 0;
}

