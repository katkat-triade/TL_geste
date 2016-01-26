#include "coeff_fourier_inverse.hpp"
using namespace cv;
using namespace std;

vector<vector<Point>> coeff_fourier_inverse(vector<complex<double> > coeffs, Point centre, int cmax, int N, double ech){
				vector<Point> z_reconstructed;
				vector<vector<Point>> reconstructedContour;
                vector<complex<double>> coeffs2(N); 
                vector<complex<double>> coeffs3; 
                
                int begin = coeffs.size() - cmax - 1;

                for(size_t j = begin; j< coeffs.size() ; ++j ){
                  coeffs2[j- begin] = (double)N * coeffs[j];
                }
                 for(int j = 0; j<cmax; j++ ){
                   coeffs2[N - cmax + j] = (double)N * coeffs[j];
                }                
                
              
                
               dft(coeffs2, coeffs3, DFT_INVERSE + DFT_SCALE);
               coeffs3.push_back(coeffs3[0]);

                for( auto& comp : coeffs3){
                Point z_point(comp.real()*ech + centre.x, comp.imag()*ech + centre.y);
                z_reconstructed.push_back(z_point);
               
                  }
                reconstructedContour.push_back(z_reconstructed);

	return(reconstructedContour);
}
