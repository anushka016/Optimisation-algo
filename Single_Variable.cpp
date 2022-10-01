#include<iostream>
#include<bits/stdc++.h>
using namespace std;

/********
 * This is Phase 1 of ME609 project prepared by Anushka Anand(190103016) and Richa Kumari(190103074).
 * The following code contains the Bounding Phase method and the Golden Section Search method.
 * Both maximisation and minimisation can be performed by the code.
 * Currently, only one objective function is in the code, but for data plotting, the function can be changed.
********/

//the answer class is to store and pass the range from one function to another
class answer {
    public:
    double a; //lower bound
    double b; //upper bound
};

double objective(double x);
answer bounding_phase(double lo, double up, double xo, double delta, int n);
answer golden_section_search(double a, double b, double eps, int n);
double modified_objective(double omega, double a, double b);



int main() {

    //take input
    double l, u, delta, lo,up, eps,xo;
    int choice;
    
    //Choose to maximise or minimise
    cout<<"To minimise, enter 0"<<endl;
    cout<<"OR"<<endl;
    cout<<"To maximise, enter 1"<<endl;
    cin>>choice;

    cout<<"Enter lower bound: ";
    cin>>lo;
    
     cout<<"Enter upper bound: ";
    cin>>up;
    
    

    cout<<"Enter delta: ";
    cin>>delta;
    delta = abs(delta);
    srand(time(NULL));
       double f = (double)rand() / RAND_MAX;
    xo= lo + f * (up - lo);
cout<<" initial guess: "<<xo<<endl;
    //call Bounding Phase Method
    
    answer range = bounding_phase(lo, up, xo, delta, choice);

    //set values of l and u for the Golden Section Search method
    l = range.a;
    u = range.b;
    cout<<"\nEnter epsilon: ";
    cin>>eps;
    //call Golden Section Search Method
    answer result = golden_section_search(l, u, eps, choice);

    cout<<"\nThe optima lies in ("<< result.a <<", " << result.b <<")";
    return 0;

}


answer bounding_phase(double lo, double up, double xo, double delta, int n) {
    
    double f1, f2, f3;

    f1 = objective(xo - delta);
    f2 = objective(xo);
    f3 = objective(xo + delta);

    if(f1>=f2 && f2>=f3) {
        if(n==0)        //n denotes choice of minimisation or maximisation
        delta = delta;
        else
        delta *=(-1);
    }

    else if(f1<=f2 && f2<=f3) {
        if(n==0)
        delta *=(-1);
        else
        delta = delta;
    }

    double array[500];  //to store x values of all iterations
    array[0] = xo;
    int k = 0;
    for(k;;k++) {
        double xn = xo + pow(2,k)*delta;
        array[k+1] = xn;
        
        if(n == 0 && objective(xn) > objective(xo)) {
            break;
        }

        if(n == 1 && objective(xn) < objective(xo)) {
            break;
        }
        
        if(xn<lo || xn>up) break;

        xo = xn;
        
    }
    
    answer a1;
    if(delta >= 0) {
        a1.a = array[k-1];
        a1.b = array[k+1];
    }
    else{
        a1.a = array[k+1];
        a1.b = array[k-1];
    }
    /*for(int i =0;i<=k+1;i++){
        cout<<array[i]<<" func val "<<objective(array[i]) <<endl;
        
    }*/
    cout<<"\nUsing the bounding phase method, the new range is ("<< a1.a <<", "<< a1.b<<")"<<endl;
    cout<<"No. of iterations (Bounding Phase method) = "<<k+1<<endl;
    cout<<"No. of function evaluations (Bounding Phase method) = "<<k+3<<endl;
    return a1;
}

answer golden_section_search(double a, double b, double eps, int n) {

    double a_omega = 0;
    double b_omega = 1;
    double L = b_omega - a_omega;
    double x1, x2;

    answer array[500];  //store ranges of every iteration
    array[0].a = a_omega;
    array[0].b = b_omega;

    int k = 0;
    for(k;;k++) {
        
        x1 = a_omega + 0.618*L;
        x2 = b_omega - 0.618*L;
        if(modified_objective(x1, a, b) <= modified_objective(x2, a, b)) {
            if(n == 0)
            a_omega = x2;
            else
            b_omega = x1;
        }

        else if(modified_objective(x1, a, b) >= modified_objective(x2, a, b)) {
            if(n == 0)
            b_omega = x1;
            else
            a_omega = x2;
        }
        array[k+1].a = a_omega;
        array[k+1].b = b_omega;

        L = b_omega - a_omega;
        if(abs(L) <= eps) {
            break;
        }
    
    }

    answer a2;
    a2.a = a_omega*(b-a) + a;
    a2.b = b_omega*(b-a) + a;
  /*for(int i=0;i<=k+1;i++){
      cout<<array[i].a*(b-a) + a<<" "<<array[i].b*(b-a) + a<<endl;
  }*/
    cout<<"\nUsing the Golden Section Search method, the range is ("<<a2.a<<", "<<a2.b<<")"<<endl;
    cout<<"No. of iterations (Golden Section Search method) ="<<k+1<<endl;
    cout<<"No. of function evaluations (Golden Section Search method) ="<<k+2<<endl;
    return a2;
    
}

double objective(double x) {
    return 8 + x*x*x -2*x -2*exp(x);
}

double modified_objective(double omega, double a, double b) {
        return objective((b-a)*omega + a);
}