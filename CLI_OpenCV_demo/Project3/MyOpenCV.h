#pragma once
#include<opencv2/opencv.hpp>
#include "opencv\highgui.h"
#include "opencv\cv.h"
#include <windows.h>
#include "TackbarValues.h"
#include "FileTools.h"
#include "ATP/Red.h"
#include "ATP/RedSekv.h"


using namespace std;
using namespace cv;


struct Robot
{
	int id;
	Red<Point>* historijaPozicija = new RedSekv<Point>(30);
};

struct MyOpenCV
{
public:
	int prolaz = 1;
	int framePozicija=0;
	int minDifference;
	int brRobotaZaUpdate=0;

	 Robot* roboti = nullptr;

	int dataLocations[12][20] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{},
		{},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{},
		{},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{},
		{},
		{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
		{},
		{}
	};

	void identifikacija(int x, int y, int index)
	{
		if (framePozicija++ <= 120)
		{
			for (int i = 1; i < 12; i++)
			{
				if (i % 3 == 0)
				{
					continue;
				}
				else
				{
					for (int j = 0; j < 19; j++)
					{
						dataLocations[i][j] = dataLocations[i][j + 1];
					}
				}
			}
			switch (prolaz)
			{
			case 1:
				dataLocations[1][19] = x;
				dataLocations[2][19] = y;
				prolaz++;
				break;
			case 2:
				dataLocations[4][19] = x;
				dataLocations[5][19] = y;
				prolaz++;
				break;
			case 3:
				dataLocations[7][19] = x;
				dataLocations[8][19] = y;
				prolaz++;
				break;
			case 4:
				dataLocations[10][19] = x;
				dataLocations[11][19] = y;
				prolaz = 1;
				break;
			default:
				break;
			}
			
		}
		else
		{
			minDifference = abs(dataLocations[1][19] - x) + abs(dataLocations[2][19] - y);
			brRobotaZaUpdate = 1;
			if (minDifference> abs(dataLocations[4][19] - x) + abs(dataLocations[5][19] - y))
			{
				minDifference = abs(dataLocations[4][19] - x) + abs(dataLocations[5][19] - y);
				brRobotaZaUpdate = 2;
				if (minDifference > abs(dataLocations[7][19] - x) + abs(dataLocations[8][19] - y))
				{
					minDifference = abs(dataLocations[7][19] - x) + abs(dataLocations[8][19] - y);
					brRobotaZaUpdate = 3;
					if (minDifference > abs(dataLocations[10][19] - x) + abs(dataLocations[11][19] - y))
					{
						minDifference = abs(dataLocations[10][19] - x) + abs(dataLocations[11][19] - y);
						brRobotaZaUpdate = 4;
					}
				}
			}
			if (minDifference<200)
			{
				switch (brRobotaZaUpdate)
				{
				case 1:
					for (int i = 1; i <= 2; i++)
					{
						for (int j = 0; j < 19; j++)
						{
							dataLocations[i][j] = dataLocations[i][j + 1];
						}
					}
					dataLocations[1][19] = x;
					dataLocations[2][19] = y;
					break;
				case 2:
					for (int i = 4; i <= 5; i++)
					{
						for (int j = 0; j < 19; j++)
						{
							dataLocations[i][j] = dataLocations[i][j + 1];
						}
					}
					dataLocations[4][19] = x;
					dataLocations[5][19] = y;
					break;
				case 3:
					for (int i = 7; i <= 8; i++)
					{
						for (int j = 0; j < 19; j++)
						{
							dataLocations[i][j] = dataLocations[i][j + 1];
						}
					}
					dataLocations[7][19] = x;
					dataLocations[8][19] = y;
					break;
				case 4:
					for (int i = 10; i <= 11; i++)
					{
						for (int j = 0; j < 19; j++)
						{
							dataLocations[i][j] = dataLocations[i][j + 1];
						}
					}
					dataLocations[10][19] = x;
					dataLocations[11][19] = y;
					break;
				default:
					break;
				}
			}

		}


	}

private:
	TrackbarValues bar;

	//default capture width and height
	const int FRAME_WIDTH = 640;
	const int FRAME_HEIGHT = 480;
	//max number of objects to be detected in frame
	const int MAX_NUM_OBJECTS = 50;
	//minimum and maximum object area

	//names that will appear at the top of each window
	const string winOriginal = "Original Image";
	const string winHsvImage = "HSV Image";
	const string winThreshholdedImage = "Thresholded Image";
	const string winAfterMorphOper = "After Morphological Operations";
	const string winTrackbars = "Trackbars";

	bool calibrationMode;//used for showing debugging windows, trackbars etc.

	bool mouseIsDragging;//used for showing a rectangle on screen as user clicks and drags mouse
	bool mouseMove;
	bool rectangleSelected;


	cv::Point initialClickPoint, currentMousePoint; //keep track of initial point clicked and current position of mouse
	cv::Rect rectangleROI; //this is the ROI that the user has selected
	vector<int> H_ROI, S_ROI, V_ROI;// HSV values from the click/drag ROI region stored in separate vectors so that we can sort them easily

	static void on_trackbar(int, void*)
	{
		
	}

	static void local_clickAndDrag_Rectangle(int event, int x, int y, int flags, void* param) {

		MyOpenCV* p = (MyOpenCV*) param;

		//only if calibration mode is true will we use the mouse to change HSV values
		if (p->calibrationMode == true) {
			//get handle to video feed passed in as "param" and cast as Mat pointer
		

			if (event == CV_EVENT_LBUTTONDOWN && p->mouseIsDragging == false)
			{
				//keep track of initial point clicked
				p->initialClickPoint = cv::Point(x, y);
				//user has begun dragging the mouse
				p->mouseIsDragging = true;
			}
			/* user is dragging the mouse */
			if (event == CV_EVENT_MOUSEMOVE && p->mouseIsDragging == true)
			{
				//keep track of current mouse point
				p->currentMousePoint = cv::Point(x, y);
				//user has moved the mouse while clicking and dragging
				p->mouseMove = true;
			}
			/* user has released left button */
			if (event == CV_EVENT_LBUTTONUP && p->mouseIsDragging == true)
			{
				//set rectangle ROI to the rectangle that the user has selected
				p->rectangleROI = Rect(p->initialClickPoint, p->currentMousePoint);

				//reset boolean variables
				p->mouseIsDragging = false;
				p->mouseMove = false;
				p->rectangleSelected = true;
			}

			if (event == CV_EVENT_RBUTTONDOWN) {
				//user has clicked right mouse button
				//Reset HSV Values
				p->bar.H_MIN = 0;
				p->bar.S_MIN = 0;
				p->bar.V_MIN = 0;
				p->bar.H_MAX = 255;
				p->bar.S_MAX = 255;
				p->bar.V_MAX = 255;

			}
			if (event == CV_EVENT_MBUTTONDOWN) {

				//user has clicked middle mouse button
				//enter code here if needed.
			}
		}

	}

	void read_tackbar_values_from_file()
	{

		ifstream f("aa.txt");
		try
		{
			f_ucitaj(f, bar);
		}
		catch (cv::Exception e)
		{
			cout << e.what() << endl;
		}

		f.close();
	}

	void write_tackbar_values_to_file()
	{
		ofstream f("aa.txt");
		f_snimi(f, bar);
		f.close();
	}

	void createTrackbars() {
		//create window for trackbars


		namedWindow(winTrackbars, 0);
		//create memory to store trackbar name on window
		char TrackbarName[50];
		sprintf_s(TrackbarName, "bar.H_MIN", bar.H_MIN);
		sprintf_s(TrackbarName, "bar.H_MAX", bar.H_MAX);
		sprintf_s(TrackbarName, "bar.S_MIN", bar.S_MIN);
		sprintf_s(TrackbarName, "bar.S_MAX", bar.S_MAX);
		sprintf_s(TrackbarName, "bar.V_MIN", bar.V_MIN);
		sprintf_s(TrackbarName, "bar.V_MAX", bar.V_MAX);
		sprintf_s(TrackbarName, "bar.V_DILATION_SIZE", bar.V_DILATION_SIZE);
		sprintf_s(TrackbarName, "bar.V_EROSION_SIZE", bar.V_EROSION_SIZE);
		sprintf_s(TrackbarName, "bar.MIN_OBJECT_AREA", bar.MIN_OBJECT_AREA);
		sprintf_s(TrackbarName, "bar.MAX_OBJECT_AREA", bar.MAX_OBJECT_AREA);
		//create trackbars and insert them into window
		//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
		//the max value the trackbar can move (eg. H_HIGH), 
		//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
		//                                  ---->    ---->     ---->      
		createTrackbar("bar.H_MIN", winTrackbars, &bar.H_MIN, 255, on_trackbar);
		createTrackbar("bar.H_MAX", winTrackbars, &bar.H_MAX, 255, on_trackbar);
		createTrackbar("bar.S_MIN", winTrackbars, &bar.S_MIN, 255, on_trackbar);
		createTrackbar("bar.S_MAX", winTrackbars, &bar.S_MAX, 255, on_trackbar);
		createTrackbar("bar.V_MIN", winTrackbars, &bar.V_MIN, 255, on_trackbar);
		createTrackbar("bar.V_MAX", winTrackbars, &bar.V_MAX, 255, on_trackbar);
		createTrackbar("bar.V_DILATION_SIZE", winTrackbars, &bar.V_DILATION_SIZE, 15, on_trackbar);
		createTrackbar("bar.V_EROSION_SIZE", winTrackbars, &bar.V_EROSION_SIZE, 15, on_trackbar);
		createTrackbar("bar.MIN_OBJECT_AREA", winTrackbars, &bar.MIN_OBJECT_AREA, 100, on_trackbar);
		createTrackbar("bar.MAX_OBJECT_AREA", winTrackbars, &bar.MAX_OBJECT_AREA, 100, on_trackbar);


	}

	void recordHSV_Values(cv::Mat frame, cv::Mat hsv_frame) {

		//save HSV values for ROI that user selected to a vector
		if (mouseMove == false && rectangleSelected == true) {

			//clear previous vector values
			if (H_ROI.size() > 0) H_ROI.clear();
			if (S_ROI.size() > 0) S_ROI.clear();
			if (V_ROI.size() > 0)V_ROI.clear();
			//if the rectangle has no width or height (user has only dragged a line) then we don't try to iterate over the width or height
			if (rectangleROI.width < 1 || rectangleROI.height < 1) cout << "Please drag a rectangle, not a line" << endl;
			else {
				for (int i = rectangleROI.x; i < rectangleROI.x + rectangleROI.width; i++) {
					//iterate through both x and y direction and save HSV values at each and every point
					for (int j = rectangleROI.y; j < rectangleROI.y + rectangleROI.height; j++) {
						//save HSV value at this point
						H_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[0]);
						S_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[1]);
						V_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[2]);
					}
				}
			}
			//reset rectangleSelected so user can select another region if necessary
			rectangleSelected = false;
			//set min and max HSV values from min and max elements of each array

			if (H_ROI.size() > 0) {
				//NOTE: min_element and max_element return iterators so we must dereference them with "*"
				bar.H_MIN = *std::min_element(H_ROI.begin(), H_ROI.end());
				bar.H_MAX = *std::max_element(H_ROI.begin(), H_ROI.end());
				cout << "MIN 'H' VALUE: " << bar.H_MIN << endl;
				cout << "MAX 'H' VALUE: " << bar.H_MAX << endl;
			}
			if (S_ROI.size() > 0) {
				bar.S_MIN = *std::min_element(S_ROI.begin(), S_ROI.end());
				bar.S_MAX = *std::max_element(S_ROI.begin(), S_ROI.end());
				cout << "MIN 'S' VALUE: " << bar.S_MIN << endl;
				cout << "MAX 'S' VALUE: " << bar.S_MAX << endl;
			}
			if (V_ROI.size() > 0) {
				bar.V_MIN = *std::min_element(V_ROI.begin(), V_ROI.end());
				bar.V_MAX = *std::max_element(V_ROI.begin(), V_ROI.end());
				cout << "MIN 'V' VALUE: " << bar.V_MIN << endl;
				cout << "MAX 'V' VALUE: " << bar.V_MAX << endl;
			}

		}

		if (mouseMove == true) {
			//if the mouse is held down, we will draw the click and dragged rectangle to the screen
			rectangle(frame, initialClickPoint, cv::Point(currentMousePoint.x, currentMousePoint.y), cv::Scalar(0, 255, 0), 1, 8, 0);
		}


	}



	static string intToString(int number) {


		std::stringstream ss;
		ss << number;
		return ss.str();
	}
	void drawObject(int x, int y, Mat &frame) {

		//use some of the openCV drawing functions to draw crosshairs
		//on your tracked image!


		//'if' and 'else' statements to prevent
		//memory errors from writing off the screen (ie. (-25,-25) is not within the window)

		//circle(frame, Point(x, y), 20, Scalar(0, 255, 0), 2);
		if (y - 25 > 0)
			line(frame, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
		else line(frame, Point(x, y), Point(x, 0), Scalar(0, 255, 0), 2);
		if (y + 25 < FRAME_HEIGHT)
			line(frame, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
		else line(frame, Point(x, y), Point(x, FRAME_HEIGHT), Scalar(0, 255, 0), 2);
		if (x - 25 > 0)
			line(frame, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
		else line(frame, Point(x, y), Point(0, y), Scalar(0, 255, 0), 2);
		if (x + 25 < FRAME_WIDTH)
			line(frame, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);
		else line(frame, Point(x, y), Point(FRAME_WIDTH, y), Scalar(0, 255, 0), 2);

		putText(frame, "Koordinate:" + intToString(x) + "," + intToString(y), Point(x, y + 30), 1, 1, Scalar(0, 255, 0), 2);
		
	}
	void morphOps(Mat &thresh) {

		//create structuring element that will be used to "dilate" and "erode" image.
		//the element chosen here is a 3px by 3px rectangle

		if (bar.V_EROSION_SIZE < 1)
			bar.V_EROSION_SIZE = 1;

		if (bar.V_DILATION_SIZE < 1)
			bar.V_DILATION_SIZE = 1;

		const Mat erodeElement = getStructuringElement(MORPH_RECT, Size(bar.V_EROSION_SIZE, bar.V_EROSION_SIZE));
		//dilate with larger element so make sure object is nicely visible
		const Mat dilateElement = getStructuringElement(MORPH_RECT, Size(bar.V_DILATION_SIZE, bar.V_DILATION_SIZE));

		erode(thresh, thresh, erodeElement);
		erode(thresh, thresh, erodeElement);


		dilate(thresh, thresh, dilateElement);
		dilate(thresh, thresh, dilateElement);



	}
	void trackFilteredObject(Mat threshold, Mat &cameraFeed) {

		Mat temp;
		threshold.copyTo(temp);
		//these two vectors needed for output of findContours
		vector< vector<Point> > contours;
		vector<Vec4i> hierarchy;
		//find contours of filtered image using openCV findContours function
		findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		const int numObjects = hierarchy.size();

		if (numObjects < 0)
			return;
			
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects > MAX_NUM_OBJECTS)
		{
			putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
			return;
		}

		for (int index = 0; index < numObjects; index++)
		{
			cv::Mat currentContour = (cv::Mat)contours[index];

			cv::Mat contourImage(cameraFeed.size(), CV_8UC3, cv::Scalar(0, 0, 0));
			cv::Scalar colors[3];
			colors[0] = cv::Scalar(255, 0, 0);
			colors[1] = cv::Scalar(0, 255, 0);
			colors[2] = cv::Scalar(0, 0, 255);
			for (size_t idx = 0; idx < contours.size(); idx++) {
				cv::drawContours(cameraFeed, contours, idx, colors[idx % 3]);
			}

			//	imshow("ooo", mm);
			Moments moment = moments(currentContour);
			double area = moment.m00;

			//if the area is less than 20 px by 20px then it is probably just noise
			//if the area is the same as the 3/2 of the image size, probably just a bad filter
			//we only want the object with the largest area so we save a reference area each
			//iteration and compare it to the area in the next iteration.

			int min = (bar.MIN_OBJECT_AREA / 100.0) * 10 * 20 * 20;
			int max = (bar.MAX_OBJECT_AREA / 100.0) * 10 * 640 * 480 / 1.5;

			if (area > min&& area < max)
			{
				int x = moment.m10 / area;
				int y = moment.m01 / area;
				putText(cameraFeed, "D# " + intToString(index), Point(x, y), 2, 0.5, Scalar(0, 255, 0), 2);
				//draw object location on screen
				drawObject(x, y, cameraFeed);
				identifikacija(x, y, index);
			}
		}
	}
	
	//matrix storage for HSV image
	bool IsVizijaRunning = false;
	bool IsPaused = false;
public:  
	void VizijaStop()
	{
		IsVizijaRunning = false;
	}
	void PauseToogle()
	{
		IsPaused = !IsPaused;
	}
	void GoTo(double v)
	{
		capture.set(CV_CAP_PROP_POS_AVI_RATIO, v);
	}

	//video capture object to acquire webcam feed
	VideoCapture capture;

	void VizijaStart()
	{
		if (IsVizijaRunning)
			return;
		IsPaused = false;
		IsVizijaRunning = true;
		cout << "IZLAZ pomocu tipke 'q' u glavom video prozoru \n";
		read_tackbar_values_from_file();

		//some boolean variables for different functionality within this
		//program
		bool trackObjects = true;
		bool useMorphOps = true;
		calibrationMode = true;
		//Matrix to store each frame of the webcam feed
		
	

		
		//open capture object at location zero (default location for webcam)
		//capture.open(0);
		capture.open("C:\\_robottracking\\SimulatorRobota_02.avi");
		//set height and width of capture frame
		capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
		//must create a window before setting mouse callback
		cv::namedWindow(winOriginal);
		//set mouse callback function to be active on "Webcam Feed" window
		//we pass the handle to our "frame" matrix so that we can draw a rectangle to it
		//as the user clicks and drags the mouse
		
	
		cv::setMouseCallback(winOriginal, local_clickAndDrag_Rectangle, this);
		//initiate mouse move and drag to false 
		mouseIsDragging = false;
		mouseMove = false;
		rectangleSelected = false;

		Mat HSV;
		Mat threshold;
		Mat cameraFeed;
		//start an infinite loop where webcam feed is copied to cameraFeed matrix
		//all of our operations will be performed within this loop
		while (IsVizijaRunning) {
			
			if (!IsPaused)
			{
				//store image to matrix
				capture >> cameraFeed;
				
			}
			if (cameraFeed.empty())
			{
				IsVizijaRunning = false;
				break;
			}
			
			//convert frame from BGR to HSV colorspace
			cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
			//set HSV values from user selected region
			recordHSV_Values(cameraFeed, HSV);
			//filter HSV image between values and store filtered image to
			//threshold matrix
			inRange(HSV, Scalar(bar.H_MIN, bar.S_MIN, bar.V_MIN), Scalar(bar.H_MAX, bar.S_MAX, bar.V_MAX), threshold);
			//perform morphological operations on thresholded image to eliminate noise
			//and emphasize the filtered object(s)
			if (useMorphOps)
				morphOps(threshold);
			//pass in thresholded frame to our object tracking function
			//this function will return the x and y coordinates of the
			//filtered object
			if (trackObjects)
				trackFilteredObject(threshold, cameraFeed);

			//show frames 
			if (calibrationMode == true) {

				//create slider bars for HSV filtering
				createTrackbars();
				//imshow(winHsvImage, HSV);
				//imshow(winThreshholdedImage, threshold);
			}
			else {

				//destroyWindow(winHsvImage);
			//	destroyWindow(winThreshholdedImage);
				destroyWindow(winTrackbars);
			}
			imshow(winOriginal, cameraFeed);


			const int wait_key = waitKey(30);
			//delay 30ms so that screen can refresh.
			//image will not appear without this waitKey() command
			//also use waitKey command to capture keyboard input
			if (wait_key == 99)
				calibrationMode = !calibrationMode;//if user presses 'c', toggle calibration mode

			if (wait_key == 'q')
				break;
		}
		write_tackbar_values_to_file();

	}
};