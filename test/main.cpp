#include "../include/matrix.hpp"
#include "../include/global.hpp"
#include "../include/SAT_Const.hpp"
#include "../include/MeasUpdate.hpp"
#include "It1_tests.cpp"
#include "It2_tests.cpp"
#include "It3_tests.cpp"
#include "It4_tests.cpp"
#include <iostream>

using namespace std;
using namespace consts;

int main(){

	int nobs = 46;

	// Carga de archivos
    eop19620101(21413); // Cargar solo las primeras c líneas del archivo eop19620101.txt
	GGM03S(); // Cargamos las matrices Cnm y Snm
	DE430Coeff(); // Cargamos la matriz PC
	GEOS3(nobs);
	
	// AuxParam
	AuxParam.Mjd_UTC = 49746.1163541665;
	AuxParam.Mjd_TT = 49746.1170623147;
	AuxParam.n = 20;
	AuxParam.m = 20;
	AuxParam.sun = 1;
	AuxParam.moon = 1;
	AuxParam.planets = 1;

	//EKF_GEOS3
	
	double sigma_range = 92.5;
	double sigma_az = 0.0224*Rad;
	double sigma_el = 0.0139*Rad;

	double lat = Rad*21.5748;
	double lon = Rad*(-158.2706); 
	double alt = 300.20;

	Matrix rs_aux = Position(lon, lat, alt);
	Matrix Rs = transpose(rs_aux);

	double Mjd1 = obs(1,1);
	double Mjd2 = obs(9,1);
	double Mjd3 = obs(18,1);

	//anglesg
	Matrix r2 = zeros(3), v2 = zeros(3);
	r2(1) = 6221397.62857869; r2(2) = 2867713.77965738; r2(3) = 3006155.98509949;
	v2(1) = 4645.04725161806; v2(2) = -2752.21591588204; v2(3) = -7507.99940987031;

	Matrix Y0_apr = union_vector(r2,v2);
	
	double Mjd0 = Mjday(1995,1,29,02,38,0);

	double Mjd_UTC = obs(9,1);

	int n_eqn  = 6;

	Matrix Y_aux = DEInteg(Accel,0,-(obs(9,1)-Mjd0)*86400.0,1e-13,1e-6,6,transpose(Y0_apr));
	Matrix Y = transpose(Y_aux);

	Matrix P_0 = zeros(6,6);

	for (int i = 1; i <= 3; i++){
		P_0(i,i)=1e8;
	}
	for (int i = 4; i <= 6; i++){
		P_0(i,i)=1e3;
	}
		
	Matrix LT = LTC(lon,lat);

	Matrix yPhi = zeros(42,1);
	Matrix Phi  = zeros(6,6);

	double t = 0;
	double t_old;
	Matrix Y_old;
	double Mjd_TT, Mjd_UT1, Azim, Elev;
	Matrix r(3), s(3,1);
	Matrix dAds(3), dEds(3);
	Matrix K;
	double x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC;
	double UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC;
	double theta;

	for(int i = 1; i <= nobs; i++){    
		
		t_old = t;
		Y_old = Y;
		
		Mjd_UTC = obs(i,1);                      
		t       = (Mjd_UTC-Mjd0)*86400.0;         
		
		tie(x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC) = IERS(eopdata,Mjd_UTC,'l');
		tie(UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC) = timediff(UT1_UTC,TAI_UTC);
		Mjd_TT = Mjd_UTC + TT_UTC/86400.0;
		Mjd_UT1 = Mjd_TT + (UT1_UTC-TT_UTC)/86400.0;
		AuxParam.Mjd_UTC = Mjd_UTC;
		AuxParam.Mjd_TT = Mjd_TT;
			
		for(int ii = 1; ii <= 6; ii++){
			yPhi(ii,1) = Y_old(ii,1);
			for(int j = 1; j <= 6; j++){
				if (ii==j){ 
					yPhi(6*j+ii,1) = 1; 
				}else{
					yPhi(6*j+ii,1) = 0;
				}	
			}
		}
		
		Matrix yPhi_aux = DEInteg(VarEqn,0,t-t_old,1e-13,1e-6,42,yPhi);
		yPhi = transpose(yPhi_aux);
		
		for(int j = 1; j <= 6; j++){
			assign_column(Phi,j,extract_vector(transpose(yPhi),6*j+1,6*j+6));
		}

		Matrix Y_aux1 = DEInteg (Accel,0,t-t_old,1e-13,1e-6,6,Y_old);
		Y = transpose(Y_aux1);

		theta = gmst(Mjd_UT1);                    
		Matrix U = R_z(theta); // 3x3
		r = extract_vector(transpose(Y), 1,3);// 1x3
		s = LT*(U*transpose(r)-Rs);           // 3x1               
		
		Matrix P = TimeUpdate(P_0, Phi);
		
		tie(Azim, Elev, dAds, dEds) = AzElPa(transpose(s));     
		Matrix dAdY = union_vector(dAds*LT*U,zeros(3));
		
		tie(K,Y,P) = MeasUpdate (Y, obs(i,2), Azim, sigma_az, dAdY, P, 6 );
		
		r = extract_vector(transpose(Y), 1,3);
		s = LT*(U*transpose(r)-Rs);                          
		tie(Azim, Elev, dAds, dEds) = AzElPa(transpose(s));      
		Matrix dEdY = union_vector(dEds*LT*U,zeros(3));

		tie(K,Y,P) = MeasUpdate (Y, obs(i,3), Elev, sigma_el, dEdY, P, 6 );
		
		r = extract_vector(transpose(Y), 1,3); // 1x3
		s = LT*(U*transpose(r)-Rs);        // 3x1                 
		double Dist = norm(transpose(s)); 
		Matrix dDds = (transpose(s)/Dist); // 1x3        
		Matrix dDdY = union_vector(dDds*LT*U,zeros(3));
		
		tie(K,Y,P)  = MeasUpdate (Y, obs(i,4), Dist, sigma_range, dDdY, P, 6 );
	}
	
	tie(x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC) = IERS(eopdata,obs(46,1),'l');
	tie(UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC) = timediff(UT1_UTC,TAI_UTC);
	Mjd_TT = Mjd_UTC + TT_UTC/86400.0;
	AuxParam.Mjd_UTC = Mjd_UTC;
	AuxParam.Mjd_TT = Mjd_TT;
	
	Matrix Y0 = DEInteg (Accel,0,-(obs(46,1)-obs(1,1))*86400.0,1e-13,1e-6,6,Y);

	Matrix Y_true(6);
	Y_true(1) = 5753.173e3; Y_true(2) = 2673.361e3; Y_true(3) = 3440.304e3;
	Y_true(4) = 4.324207e3; Y_true(5) = -1.924299e3; Y_true(6) = -5.728216e3;

	printf("\nError of Position Estimation\n");
    printf("dX%10.1f [m]\n", Y0(1) - Y_true(1));
    printf("dY%10.1f [m]\n", Y0(2) - Y_true(2));
    printf("dZ%10.1f [m]\n", Y0(3) - Y_true(3));
    printf("\nError of Velocity Estimation\n");
    printf("dVx%8.1f [m/s]\n", Y0(4) - Y_true(4));
    printf("dVy%8.1f [m/s]\n", Y0(5) - Y_true(5));
    printf("dVz%8.1f [m/s]\n", Y0(6) - Y_true(6));
	
	//It1_tests();
	//It2_tests();
	//It3_tests();
	//It4_tests();
	
	return 0;
}
