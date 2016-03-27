#include <iostream>
#include <cmath>
#include <opencv2\opencv.hpp>

#define PI 3.141592654

using namespace std;
using namespace cv;


int main()
{
	Mat input = imread("input.jpg");
	Mat output(input.size(), CV_8UC3, cvScalar(0, 0, 0));
	int d0 = max(input.cols, input.rows) / 2;
	int p0 = min(output.cols, output.rows) / 2;
	for (int i = 0; i < output.rows; i++)
	{
		int r_out = i - output.rows / 2;
		for (int j = 0; j < output.cols; j++)
		{
			int c_out = j - output.cols / 2;
			double p = sqrt(r_out * r_out + c_out * c_out);
			double theta = atan(double(r_out) / c_out);
			double phi = asin(p / p0);
			double d = (d0 * phi * 2) / PI;
			int r_in = d * sin(theta);
			int c_in = d * cos(theta);
			if (c_out < 0)
			{
				r_in = -r_in;
				c_in = -c_in;
			}
			r_in += input.rows / 2;
			c_in += input.cols / 2;
			if (r_in >= 0 && r_in < input.rows && c_in >= 0 && c_in < input.cols)
			{
				output.at<Vec3b>(i, j) = input.at<Vec3b>(r_in, c_in);
			}
		}
	}

	imshow("output", output);
	cvWaitKey(0);
	destroyWindow("output");
	return 0;
}