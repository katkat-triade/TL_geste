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
#include "detection.hpp"
//#include "compare_prototype.hpp"
#include "coeff_fourier.hpp"
#include "coeff_fourier_inverse.hpp"

using namespace std;
using namespace cv;


int  main(int argc, char** argv){

        Mat frame;
        vector<vector<Point> > contour;
        vector<vector<Point>> drawReconstructedContour;
        vector<complex<double>> prototypes;
        vector<complex<double> > coeffs;
        Scalar color(255,255,255);
        vector<Vec4i> hierarchy;
        int cmax(30), N(200);  
        int w,l;
        //clock_t t1 = clock();

        //extraction des prototypes des fichiers sources
        //prototypes = lire_prototypes(FICHIER_R , FICHIER_I , N_COEFF_FOUR*2+1);

        VideoCapture cap(0); // open the default camera
        if(!cap.isOpened()){  // check if we succeeded
                return -1;
        }
        //recuperation des informations de la camera
        w = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        l = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        Point centre(w/2,l/2);
        double ech = 50; //Mise à l'échelle
        
        for(;;)
        {
                Mat frame;
                cap >> frame;
                //récupérer le plus long contour
                contour = detection(frame, w, l);
                coeffs = coeff_fourier(contour[0], cmax, centre);
                drawReconstructedContour = coeff_fourier_inverse(coeffs, centre, cmax, N, ech);

                //Mat myFrame2 = Mat::zeros(canny_output.rows, canny_output.cols, CV_8UC3);
                Mat myFrame = Mat::zeros(frame.rows, frame.cols, CV_8UC3);
                drawContours(myFrame,drawReconstructedContour,0,color,2, 8, hierarchy, 0, Point());
                add(frame, myFrame, frame);
                //imwrite( "contourReconstruit"+ to_string(n) +".png", myFrame2 );
                namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
                imshow( "Display window", frame); 

                if(waitKey(30) >= 0) break;

        }
        return 0;
}
