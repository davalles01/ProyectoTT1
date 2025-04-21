#include "AccelPointMass_test.cpp"
#include "Cheb3D_test.cpp"
#include "EccAnom_test.cpp"
#include "Frac_test.cpp"
#include "MeanObliquity_test.cpp"
#include "Mjday_test.cpp"
#include "Mjday_TDB_test.cpp"
#include "Position_test.cpp"
#include "R_x_test.cpp"
#include "R_y_test.cpp"
#include "R_z_test.cpp"
#include "sign__test.cpp"
#include "timediff_test.cpp"
#include "AzElPa_test.cpp"

using namespace std;

int main(){
    
    //AccelPointMass_test();
    //Cheb3D_test();
    //EccAnom_test();
    //Frac_test();
    //MeanObliquity_test();
    //Mjday_test();
    //Mjday_TDB_test();
    //Position_test();
    //R_x_test();
    //R_y_test();
    //R_z_test();
    //sign__test();
    //timediff_test();
    AzElPa_test();

    cout << "All tests passed successfully.\n";

    return 0;
}