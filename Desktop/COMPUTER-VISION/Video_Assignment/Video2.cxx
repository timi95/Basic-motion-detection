//g++ `pkg-config --cflags opencv` Video2.cxx `pkg-config --libs opencv` -o Video2

#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the camera
    if(!cap.isOpened())  // much success!?
        {return -1;}

	//firstframe, next frame, greyed&blurred, motiondetected
    Mat firstframe, frame, grey, diff;
	//window name
    //namedWindow("gey",1);

    while(1)
    {
		//Get the first frame
		cap>>firstframe;
		cvtColor(firstframe,firstframe,COLOR_BGR2GRAY);
		GaussianBlur(firstframe, firstframe,Size(21,21),0,0);

		//Get the next frame
        cap >> frame; // get next frame from camera
        cvtColor(frame, grey, COLOR_BGR2GRAY);
        GaussianBlur(grey, grey,Size(21,21),0,0); // removes noise because we are finding a general and filtered difference in frames
        //Canny(edges, edges, 0, 30, 3);
        //imshow("gey", grey);

		//Absolute difference between the first frame and the next frame called gey
		absdiff(firstframe, grey, diff);
		//All pixels above the threshold of 22 are set to value 220
        threshold(diff, diff,22, 220, THRESH_BINARY);
		//show the motion capture image
		imshow("W1",diff); 
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor

    return 0;
}

