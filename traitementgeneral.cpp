#include <iostream>
#include <sstream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <cmath>
#include <algorithm>
#include <string>
#include <array>
#include <fstream>
#include <complex>
#include "coeff_fourier.hpp"
#include "coeff_fourier_inverse.hpp"
//#include "compare_prototype.hpp"


using namespace std;
using namespace cv;

Mat src_gray;
int thresh =63 ;
//int max_thresh = 255;
RNG rng(12345);
Scalar color(255,255,255);
vector<Vec4i> hierarchy;
/// Function header
void thresh_callback(int, void* );


int main( int argc, char** argv )
{
        //Declaration des variables
        //int cmax(30);
        int  N(200), cmax(30);
        int Nomb = 20;
        vector<Mat> liste_image;
        /*
        //Chargement des prototypes
        vector<vector<complex<double>>> dico_prototypes;
        vector<complex<double>> prototype_avance_1;
        vector<complex<double>> prototype_avance_2;
        prototype_avance_1 = lire_prototypes("prototype_avance_1_real.tex","prototype_avance_1_imag.tex", 2*cmax+1);
        prototype_avance_2 = lire_prototypes("prototype_avance_2_real.tex","prototype_avance_2_imag.tex", 2*cmax+1);
        dico_prototypes.push_back(prototype_avance_2);
        dico_prototypes.push_back(prototype_avance_1);
        */
        //Création de la liste d'images
        for ( int d=1; d<Nomb+1;d++){
                Mat image;
                string filename = "resultat2_avance" + to_string(d) +".pgm";
                //string filename = "hand" + to_string(d) +".png";
                image = imread(filename.c_str(),1);   // Read the file
                liste_image.push_back(image);
                //liste=dir('*.pgm');
        }

        
    
        //Initialisation pour findContours
        Mat canny_output, frame;
        vector<vector<Point>> contours;
        vector<vector<Point>> tabcontfil;

        for  (int n=1 ; n<Nomb;++n){
                //Find Contours instead of bwboundaries
                //zliste=bwboundaries(BW,8,'noholes');
                // Convert image to gray and blur it
                cvtColor( liste_image.at(n), src_gray, CV_BGR2GRAY );
                blur( src_gray, src_gray, Size(3,3) );
                /// Detect edges using canny
                Canny( src_gray, canny_output, thresh, thresh*2, 3 );
                /// Find contours
                findContours( canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0) );
                /// Draw contours
                Mat zliste = Mat::zeros( canny_output.size(), CV_8UC3 );	

                for( size_t j = 0; j< contours.size(); j++ )
                {
                        //	Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                        drawContours( zliste, contours, j, color, 2, 8, hierarchy, 0, Point() );
                }

                //namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
                //imshow( "Contours", zliste );

                //imwrite( "contour_"+filename.c_str(), zliste );
                //imwrite( "contour.png", zliste );
                //Fin findContours


                



                //vector<vector<Point>> tabcontfil;
                // On itère sur l'ensemble des contours
                int index = 1;
                int longueur = 0;
                int longmax = 0;
                const int nb_contours = contours.size(); 
                for(int i  = 0; i< nb_contours; i++ )
                {
                        vector<Point> contourj = contours.at(i);
                        longueur = contourj.size();
                        if (longueur>longmax){
                                longmax = longueur;
                                index = i;
                        }


                }	
                //z is the biggest contour
                vector<Point> z;
                z = contours.at(index); 

                //draw this contour
                vector<vector<Point>> drawBiggestContour;
                drawBiggestContour.push_back(z);
                Mat myFrame = Mat::zeros(canny_output.rows, canny_output.cols, CV_8UC3);
                drawContours(myFrame,drawBiggestContour,0,color,2, 8, hierarchy, 0, Point() );
                imwrite( "../test/contourLePlusLong"+ to_string(n) +".png", myFrame );


                // z_comp is the complex representation of z
                //:::::::::::::DANS LE MAIN
                Point centre((double)canny_output.cols/2, (double)canny_output.rows/2);
                double ech = 50;        
                //:::::::::::::::

                vector<complex<double>> coeffs; 
                coeffs = coeff_fourier(z, cmax, centre);

                vector<vector<Point>> drawReconstructedContour;
 
                drawReconstructedContour = coeff_fourier_inverse(coeffs, centre, cmax, N, ech);
               
                Mat myFrame2 = Mat::zeros(canny_output.rows, canny_output.cols, CV_8UC3);
                drawContours(myFrame2,drawReconstructedContour,0,color,2, 8, hierarchy, 0, Point());
                imwrite( "contourReconstruit"+ to_string(n) +".png", myFrame2 );
                namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
                imshow( "Display window", myFrame2 );   
  
                }
                


return 0;
}	

