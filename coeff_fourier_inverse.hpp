#include "opencv2/opencv.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include <time.h>
#include <sstream>
#include <complex>
#include <math.h>
#include <cmath>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <string>


std::vector<std::vector<cv::Point>> coeff_fourier_inverse(std::vector<std::complex<double> > coeffs, cv::Point centre, int cmax, int N, double ech);

