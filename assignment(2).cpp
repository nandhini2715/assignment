#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;

void resizeImage(const Mat& src, Mat& dst, int interpolation) {
    Size dsize(src.cols / 2, src.rows / 2);
    resize(src, dst, dsize, 0, 0, interpolation);
}
void measurePerformance(const Mat& src, int interpolation, const string& method) {
    Mat dst;
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        resizeImage(src, dst, interpolation);
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;

    cout << "Time taken for 1000 iterations using " << method << ": " << elapsed.count() << " ms" << endl;
}
int main() {
    // Load the image
    Mat src = imread("G178_2-1080.BMP");
    if (src.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }

    // Measure performance for different interpolation methods
    measurePerformance(src, INTER_NEAREST, "INTER_NEAREST");
    measurePerformance(src, INTER_LINEAR, "INTER_LINEAR");
    measurePerformance(src, INTER_CUBIC, "INTER_CUBIC");

    return 0;
}
