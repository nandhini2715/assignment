 #include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
using namespace cv;
using namespace std;
using namespace std::chrono;
void resizeImage(const Mat& src, Mat& dst, int interpolation) {
    Size dsize(src.cols / 2, src.rows / 2);
    resize(src, dst, dsize, 0, 0, interpolation);
}
int main() {
    // Load the image
    Mat src = imread("G178_2-1080.BMP");
    if (src.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }
 // Create destination matrices
    Mat dst_nearest, dst_linear, dst_cubic;
// Resize using different interpolation methods and measure time
    auto start = high_resolution_clock::now();
    resizeImage(src, dst_nearest, INTER_NEAREST);
    auto end = high_resolution_clock::now();
    auto duration_nearest = duration_cast<milliseconds>(end - start).count();
    cout << "Time taken for INTER_NEAREST: " << duration_nearest << " ms" << endl;
    start = high_resolution_clock::now();
    resizeImage(src, dst_linear, INTER_LINEAR);
    end = high_resolution_clock::now();
    auto duration_linear = duration_cast<milliseconds>(end - start).count();
    cout << "Time taken for INTER_LINEAR: " << duration_linear << " ms" << endl;

    start = high_resolution_clock::now();
    resizeImage(src, dst_cubic, INTER_CUBIC);
    end = high_resolution_clock::now();
    auto duration_cubic = duration_cast<milliseconds>(end - start).count();
    cout << "Time taken for INTER_CUBIC: " << duration_cubic << " ms" << endl;
    // Save the results
    imwrite("output_nearest.bmp", dst_nearest);
    imwrite("output_linear.bmp", dst_linear);
    imwrite("output_cubic.bmp", dst_cubic);
    return 0;
}
