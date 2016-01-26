#include "coeff_fourier.hpp"
using namespace cv;
using namespace std;



vector<complex<double>> coeff_fourier(vector<Point> z, int cmax, Point centre){


	vector<complex<double>> coeff;
	vector<complex<double>> z_temp;
	vector<complex<double>> z_diff;
	vector<complex<double>> z_coeff;
	complex<double> z_moy;
	double longc = z.size();
	vector<complex<double>> z_comp;

       for( size_t j = 0; j < z.size()  ; j++){  
            complex<double> z_point(z[j].x, z[j].y); 
            z_comp.push_back(z_point);
            } 


	//moyenne (pas besoin la fonction dft la calcule directement)
   for(auto& point: z_comp) {
      z_moy += complex<double>(point.real() , point.imag());
   }
   	z_moy = complex<double>(z_moy.real()/longc, z_moy.imag()/longc);

	//on calcule les coefficients de fourier
	for( int j = 0; j < longc ; j++){
      complex<double> z_point2(z_comp[j].real() - z_moy.real(), z_comp[j].imag() - z_moy.imag());
      z_diff.push_back(z_point2);
   }

	dft(z_diff, z_temp, DFT_SCALE + DFT_COMPLEX_OUTPUT);
	
	for(int j = 0; j< cmax; ++j ){
    coeff.push_back(z_temp[j + longc - cmax]);
    }
    for(int j = 0; j< cmax+1; ++j ){
    coeff.push_back(z_temp[j]);
    }
    
	//invariance vis a vis du sens de parcours
	if(abs(coeff[cmax - 1])<abs(coeff[cmax-1])){
	reverse(coeff.begin(), coeff.end());
	}
	
	//invariance vis a vis de la rotation
	double Phi = arg(coeff[cmax+1]*coeff[cmax-1])/2.0;
	//complex<double> exp_comp = exp(complex<double>(0,-Phi));

	for (auto& complex: coeff){
	complex *= polar(1.0, -Phi);
	}
	
	double theta = arg(coeff[cmax+1]);
	
	for (int i = -cmax; i <= cmax ; ++i){
	coeff[i+cmax] = coeff[i+cmax] * polar(1.0, -i*theta);
	}
		
	double d1 = abs(coeff[cmax+1]);	
	for(auto& comp : coeff){
	comp /= d1;
	}
	
	return (coeff);
}
