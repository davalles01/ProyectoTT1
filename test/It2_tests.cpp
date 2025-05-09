#include "EqnEquinox_test.cpp"
#include "LTC_test.cpp"
#include "NutMatrix_test.cpp"
#include "PoleMatrix_test.cpp"
#include "PrecMatrix_test.cpp"
#include "gmst_test.cpp"
#include "AccelHarmonic_test.cpp"

using namespace std;

int main(){
    
    //EqnEquinox_test();
    //LTC_test();
    //NutMatrix_test();
    //PoleMatrix_test();
    //PrecMatrix_test();
    //gmst_test();
    AccelHarmonic_test();

    cout << "All tests passed successfully.\n";

    return 0;
}