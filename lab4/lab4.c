#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>
using namespace cv;
using namespace std;
//Binary threshold variable
int threshold = 70;

//Polynomial regression function
vector<double> fitPoly(vector<Point> points, int n)
{
  //Number of points
  int nPoints = points.size();

  //Vectors for all the points' xs and ys
  vector<float> xValues = vector<float>();
  vector<float> yValues = vector<float>();

  //Split the points into two vectors for x and y values
  for(int i = 0; i < nPoints; i++)
  {
    xValues.push_back(points[i].x);
    yValues.push_back(points[i].y);
  }

  //Augmented matrix
  double matrixSystem[n+1][n+2];
  for(int row = 0; row < n+1; row++)
  {
    for(int col = 0; col < n+1; col++)
    {
      matrixSystem[row][col] = 0;
      for(int i = 0; i < nPoints; i++)
        matrixSystem[row][col] += pow(xValues[i], row + col);
    }

    matrixSystem[row][n+1] = 0;
    for(int i = 0; i < nPoints; i++)
      matrixSystem[row][n+1] += pow(xValues[i], row) * yValues[i];

  }

  //Array that holds all the coefficients
  double coeffVec[n+2] = {};  // the "= {}" is needed in visual studio, but not in Linux

  //Gauss reduction
  for(int i = 0; i <= n-1; i++)
    for (int k=i+1; k <= n; k++)
    {
      double t=matrixSystem[k][i]/matrixSystem[i][i];

      for (int j=0;j<=n+1;j++)
        matrixSystem[k][j]=matrixSystem[k][j]-t*matrixSystem[i][j];

    }

  //Back-substitution
  for (int i=n;i>=0;i--)
  {
    coeffVec[i]=matrixSystem[i][n+1];
    for (int j=0;j<=n+1;j++)
      if (j!=i)
        coeffVec[i]=coeffVec[i]-matrixSystem[i][j]*coeffVec[j];

    coeffVec[i]=coeffVec[i]/matrixSystem[i][i];
  }

  //Construct the cv vector and return it
  vector<double> result = vector<double>();
  for(int i = 0; i < n+1; i++)
    result.push_back(coeffVec[i]);
  return result;
}

//Returns the point for the equation determined
//by a vector of coefficents, at a certain x location
Point pointAtX(vector<double> coeff, double x)
{
  double y = 0;
  for(int i = 0; i < coeff.size(); i++)
  y += pow(x, i) * coeff[i];
  return Point(x, y);
}
int cannyLower = 100;
int cannyUpper = 200;
int rho = 1;
int thetaNum = 1; // opencv doesnt support trackbars with floating points
int minLength = 50;
int maxGap = 10;
vector<Vec4i> destVec;
Mat bwImage, cannyImage, imageCopy;
static void cannyChanger(int, void*){
  Canny(bwImage, cannyImage, cannyLower, cannyUpper, 5);
  imshow("Canny image", cannyImage);
}

static void houghChanger(int, void*){
  imageCopy = bwImage.clone();
  if(rho <= 0){
    rho = 1;
  }
  if(thetaNum <= 0){
    thetaNum = 1;
  }
  HoughLinesP(cannyImage, destVec, rho, CV_PI/180 * thetaNum, 50, minLength, maxGap);
  for(size_t i=0; i < destVec.size(); i++){
    Vec4i l = destVec[i];
    line(imageCopy, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
  }
  imshow("Detected lines", imageCopy);
}


int main(int argc, char *argv[]){
  Mat greyScale;
  Mat cannyCopy, imageCopy2;
  vector<Point> points;
  vector<double> coeffs;
  if(argc < 2){
    printf("image path required\n");
    return 0;
  }
    Mat image = imread(argv[1], IMREAD_UNCHANGED);
  if(image.empty()){
    printf("Something went wrong\n");
    return -1;
  }

  cvtColor(image, bwImage, COLOR_BGR2GRAY, 0);

  //Canny(bwImage, cannyImage, cannyLower, cannyLower);
  cannyImage = bwImage.clone();
  imageCopy = bwImage.clone();
  imageCopy2 = bwImage.clone();
  imshow("Canny image",cannyImage);
  createTrackbar("Lower Canny threshold", "Canny image", &cannyLower, 10000, cannyChanger);
  createTrackbar("Upper Canny threshold", "Canny image", &cannyUpper, 10000, cannyChanger);
  cannyCopy = cannyImage.clone();
  waitKey(0);
  Canny(bwImage, cannyImage, cannyLower, cannyUpper, 5);
  imwrite("imgout/out_canny.png",cannyImage);
  HoughLinesP(cannyImage, destVec, rho, CV_PI/180 * thetaNum, 50, minLength, maxGap);
  for(size_t i=0; i < destVec.size(); i++){
    Vec4i l = destVec[i];
    line(imageCopy, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
  }
  imshow("Detected lines", imageCopy);
  createTrackbar("HoughRho", "Detected lines", &rho, 255, houghChanger);
  createTrackbar("HoughTheta", "Detected lines", &thetaNum, 10, houghChanger);
  createTrackbar("HoughMinLength", "Detected lines", &minLength, 255, houghChanger);
  createTrackbar("HoughMaxGap", "Detected lines", &maxGap, 255, houghChanger);
  waitKey(0);
  imageCopy = bwImage.clone();
  HoughLinesP(cannyImage, destVec, rho, CV_PI/180 * thetaNum, 50, minLength, maxGap);
  for(size_t i=0; i < destVec.size(); i++){
    Vec4i l = destVec[i];
    line(imageCopy, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
  }
  imwrite("imgout/out_phough.png", imageCopy);
  for(size_t i=0; i < destVec.size(); i++){
    Vec4i l = destVec[i];
    int xdif = l[0] - l[2];
    int ydif = l[1] - l[3];
    int length = sqrt(pow(abs(xdif),2) + pow(abs(ydif),2));

    //length used to be used here, but HoughLinesP filters out short lines
    //I also used to calculate the angle to filter vertical lines, but I realised
    //Its easiser to check if they are more horizontal than vertical.
    if(abs(ydif) < abs(xdif)){
      line(imageCopy2, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
      points.push_back(Point(l[0], l[1]));
      points.push_back(Point(l[2], l[3]));
    }
  }
  imshow("Canny image with filtered lines", imageCopy2);
  waitKey(0);
  imwrite("imgout/out_filtered.png", imageCopy2);


  if(points.size() > 1){
    coeffs = fitPoly(points, 2);
    double x;
    Point y1, y;
    y1 = pointAtX(coeffs, 0);
    for(x = 1; x < image.size().width; x++){
      y = pointAtX(coeffs, x);
      line(image, y1, y, Scalar(0, 0, 255), 3, LINE_AA);
      y1 = y;
    }
  }
  imshow("image", image);
  imwrite("imgout/out_curve.png", image);
  waitKey(0);
  return 0;
}
