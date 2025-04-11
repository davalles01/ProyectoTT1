#include "AccelPointMass_test.cpp"
#include "Cheb3D_test.cpp"
#include "R_x_test.cpp"

using namespace std;

int main(){
    
    AccelPointMass_test();
    //Cheb3D_test();
    R_x_test();

    cout << "All tests passed successfully.\n";

    return 0;
}