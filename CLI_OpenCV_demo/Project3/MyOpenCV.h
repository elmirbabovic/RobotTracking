#pragma once
#include<opencv2/opencv.hpp>
#include "opencv\highgui.h"
#include "opencv\cv.h"
#include <windows.h>
#include "TackbarValues.h"
#include "FileTools.h"
#include "ATP/Red.h"
#include "ATP/RedSekv.h"
#include "ATP/Lista.h"
#include "ATP/ListaPov.h"
#include <valarray>
#include "SlidingPath.h"
#include "ATP/ListaSekv.h"
#include "MyMath.h"
#include "Robot.h"
#include "RobotCollector.h"
#include "ATP/RedPov.h"

using namespace std;
using namespace cv;






struct MyOpenCV
{
public:
	
	RobotCollector robot_collector;

	Red<std::string>* printer=new RedPov<std::string>;

	Robot* FindByLocation(int x, int y, bool createNewIfNotFound, int maxDisplacement = 20)
	{
			Robot* robot = robot_collector.Find_NajbliziRobot(x, y, maxDisplacement);
			
			if (robot == nullptr)
			{
				if (createNewIfNotFound)
				{
					robot_collector.DodajRobota(framePozicija, x, y);
					printer->dodaj("Dodat novi robot: (" + intToString(x) + ", " + intToString(y) + ")");
				}
			
			}
			else
			{
				robot->DodajPoziciju(framePozicija, x, y);
			}

			return robot;
		
	}
private:
	int framePozicija = 0;
	TrackbarValues bar;

	//video capture object to acquire webcam feed
	VideoCapture capture;

	//default capture width and height
	const int FRAME_WIDTH = 640;
	const int FRAME_HEIGHT = 480;
	//max number of objects to be detected in frame
	const int MAX_NUM_OBJECTS = 50;
	//minimum and maximum object area

	//names that will appear at the top of each window
	const string winOriginal = "Original Image :: This build was compiled at " __DATE__ ", " __TIME__ ".";
	
	const string winHsvImage = "HSV Image";
	const string winThreshholdedImage = "Thresholded Image";
	const string winAfterMorphOper = "After Morphological Operations";
	const string winTrackbars = "Trackbars";

	bool HsvCalibrationMode=false;//used for showing debugging windows, trackbars etc.

	bool mouseIsDragging=false;//used for showing a rectangle on screen as user clicks and drags mouse
	bool mouseMove=false;
	bool rectangleSelected=false;


	cv::Point initialClickPoint;
	cv::Point currentMousePoint; //keep track of initial point clicked and current position of mouse
	cv::Rect rectangleROI; //this is the ROI that the user has selected
	vector<int> H_ROI, S_ROI, V_ROI;// HSV values from the click/drag ROI region stored in separate vectors so that we can sort them easily
									//matrix storage for HSV image
	bool IsVizijaRunning = false;
	bool IsPaused = false;
	Mat MatHSV;
	Mat MatThreshold;
	Mat MatCamera;

	static void on_trackbar(int, void*)
	{
		
	}

	Robot* SelectedRobot  = nullptr;

	void SelectRobot(int x, int y)
	{
		Robot* r = this->FindByLocation(x, y, false, 100);
		this->SelectedRobot = r;
	}

	static void local_clickAndDrag_Rectangle(int eventType, int x, int y, int flags, void* param) {

		MyOpenCV* p = (MyOpenCV*)param;

		if (p->HsvCalibrationMode == false)
		{
			if (eventType == CV_EVENT_LBUTTONDOWN)
			{
				p->SelectRobot(x, y);
			}
		}

		//only if calibration mode is true will we use the mouse to change HSV values
		if (p->HsvCalibrationMode == true) {
			//get handle to video feed passed in as "param" and cast as Mat pointer

			if (p->mouseMove == true) {
				//if the mouse is held down, we will draw the click and dragged rectangle to the screen
				rectangle(p->MatCamera, p->initialClickPoint, cv::Point(p->currentMousePoint.x, p->currentMousePoint.y), cv::Scalar(0, 255, 0), 1, 8, 0);
			}


			if (eventType == CV_EVENT_LBUTTONDOWN && p->mouseIsDragging == false)
			{
				//keep track of initial point clicked
				p->initialClickPoint = cv::Point(x, y);
				//user has begun dragging the mouse
				p->mouseIsDragging = true;
			}
			/* user is dragging the mouse */
			if (eventType == CV_EVENT_MOUSEMOVE && p->mouseIsDragging == true)
			{
				//keep track of current mouse point
				p->currentMousePoint = cv::Point(x, y);
				//user has moved the mouse while clicking and dragging
				p->mouseMove = true;
			}
			/* user has released left button */
			if (eventType == CV_EVENT_LBUTTONUP && p->mouseIsDragging == true)
			{
				//set rectangle ROI to the rectangle that the user has selected
				p->rectangleROI = Rect(p->initialClickPoint, p->currentMousePoint);

				//reset boolean variables
				p->mouseIsDragging = false;
				p->mouseMove = false;
				p->rectangleSelected = true;
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

	void recordHSV_Values() {

		//save HSV values for ROI that user selected to a vector
		if (mouseMove == false && rectangleSelected == true) {

			//clear previous vector values
			if (H_ROI.size() > 0) H_ROI.clear();
			if (S_ROI.size() > 0) S_ROI.clear();
			if (V_ROI.size() > 0)V_ROI.clear();
			//if the rectangle has no width or height (user has only dragged a line) then we don't try to iterate over the width or height
			if (rectangleROI.width < 1 || rectangleROI.height < 1) printer->dodaj("Please drag a rectangle, not a line");
			else {
				for (int i = rectangleROI.x; i < rectangleROI.x + rectangleROI.width; i++) {
					//iterate through both x and y direction and save HSV values at each and every point
					for (int j = rectangleROI.y; j < rectangleROI.y + rectangleROI.height; j++) {
						//save HSV value at this point
						H_ROI.push_back((int)MatHSV.at<cv::Vec3b>(j, i)[0]);
						S_ROI.push_back((int)MatHSV.at<cv::Vec3b>(j, i)[1]);
						V_ROI.push_back((int)MatHSV.at<cv::Vec3b>(j, i)[2]);
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

	


	}




	void drawCenterLines(int x, int y) {

		//'if' and 'else' statements to prevent
		//memory errors from writing off the screen (ie. (-25,-25) is not within the window)

		//circle(frame, Point(x, y), 20, Scalar(0, 255, 0), 2);
		if (y - 25 > 0)
			line(MatCamera, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
		else line(MatCamera, Point(x, y), Point(x, 0), Scalar(0, 255, 0), 2);
		if (y + 25 < FRAME_HEIGHT)
			line(MatCamera, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
		else line(MatCamera, Point(x, y), Point(x, FRAME_HEIGHT), Scalar(0, 255, 0), 2);
		if (x - 25 > 0)
			line(MatCamera, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
		else line(MatCamera, Point(x, y), Point(0, y), Scalar(0, 255, 0), 2);
		if (x + 25 < FRAME_WIDTH)
			line(MatCamera, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);
		else line(MatCamera, Point(x, y), Point(FRAME_WIDTH, y), Scalar(0, 255, 0), 2);

		putText(MatCamera, "Koordinate:" + intToString(x) + "," + intToString(y), Point(x, y + 30), 1, 1, Scalar(0, 255, 0), 2);
		
	}
	void morphOps() {

		//create structuring element that will be used to "dilate" and "erode" image.
		//the element chosen here is a 3px by 3px rectangle

		if (bar.V_EROSION_SIZE < 1)
			bar.V_EROSION_SIZE = 1;

		if (bar.V_DILATION_SIZE < 1)
			bar.V_DILATION_SIZE = 1;

		const Mat erodeElement = getStructuringElement(MORPH_RECT, Size(bar.V_EROSION_SIZE, bar.V_EROSION_SIZE));
		//dilate with larger element so make sure object is nicely visible
		const Mat dilateElement = getStructuringElement(MORPH_RECT, Size(bar.V_DILATION_SIZE, bar.V_DILATION_SIZE));

		erode(MatThreshold, MatThreshold, erodeElement);
		erode(MatThreshold, MatThreshold, erodeElement);


		dilate(MatThreshold, MatThreshold, dilateElement);
		dilate(MatThreshold, MatThreshold, dilateElement);



	}
	void trackFilteredObject() {

		Mat temp;
		MatThreshold.copyTo(temp);
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
			putText(MatCamera, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
			return;
		}

		for (int index = 0; index < numObjects; index++)
		{
			cv::Mat currentContour = (cv::Mat)contours[index];

			cv::Mat contourImage(MatCamera.size(), CV_8UC3, cv::Scalar(0, 0, 0));
			cv::Scalar colors[3];
			colors[0] = cv::Scalar(255, 0, 0);
			colors[1] = cv::Scalar(0, 255, 0);
			colors[2] = cv::Scalar(0, 0, 255);
			for (size_t idx = 0; idx < contours.size(); idx++) {
				cv::drawContours(MatCamera, contours, idx, colors[idx % 3]);
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

				Robot* r = FindByLocation(x, y, true);
				//draw object location on screen
				if (r != nullptr)
				{
					if (SelectedRobot == r)
						putText(MatCamera, "SELECTED", Point(x, y), 2, 1, Scalar(255, 255, 0), 2);
					drawCenterLines(x, y);
					
				}
				
			}
		}
	
	}
	


	void drawIdentifikacijaRobota()
	{
		for (int i = 0; i < robot_collector.Count(); ++i)
		{
			Robot* r = robot_collector.GetRobot(i);
			MotionStep* p = r->GetPozicijaNajnovija();
			if (p == nullptr)
				return;

			if (r->isRemoved)
			{
				//putText(frame, "id" + intToString(r->GetId()) + " @" + intToString(p->versionNumber), Point(p->item.x, p->item.y - 50), 1, 1, Scalar(255, 0, 0), 2);
			}
			else
			{
				int x1 = p->point.x;
				int y1 = p->point.y;

				putText(MatCamera, "id" + intToString(r->GetId()) + " @" + intToString(p->versionNumber), Point(x1, y1 - 50), 1, 1, Scalar(255, 255, 0), 2);

				NullableType<float> ugao = r->ugaoPravcaKretanja;

				if (ugao != nullptr)
				{

					float z = IzracunajOdnos(ugao);
					int c = 100;
					float b = c / sqrt((z*z) + 1);
					float a = z *b;

					if (r->PravacDeltaY > 0)
						a = abs(a);
					else
						a = -abs(a);

					if (r->PravacDeltaX > 0)
						b = abs(b);
					else
						b = -abs(b);

					float x2 = x1 + b;
					float y2 = y1 + a;

					line(MatCamera, Point(x1, y1), Point(x2, y2), Scalar(255, 0, 0), 2);
				}
			}
			

	
		}
		putText(MatCamera, "frame: " + intToString((framePozicija / 1)*1), Point(50, 50), 2, 1, Scalar(0, 255, 255), 2);

	}
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


	

	void VizijaStart()
	{
		if (IsVizijaRunning)
			return;
		IsPaused = false;
		IsVizijaRunning = true;
		cout << "IZLAZ pomocu tipke 'q' u glavom video prozoru \n";
		read_tackbar_values_from_file();

		HsvCalibrationMode = false;
		
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


		//start an infinite loop where webcam feed is copied to cameraFeed matrix
		//all of our operations will be performed within this loop
		while (IsVizijaRunning) {
			
			if (!IsPaused)
			{
				//store image to matrix
				capture >> MatCamera;
				this->framePozicija++;
			}
			if (MatCamera.empty())
			{
				IsVizijaRunning = false;
				break;
			}
			robot_collector.RemovedOldRobots(framePozicija);
			//convert frame from BGR to HSV colorspace
			cv::cvtColor(MatCamera, MatHSV, COLOR_BGR2HSV);
			//set HSV values from user selected region
			recordHSV_Values();
			//filter HSV image between values and store filtered image to
			//threshold matrix
			cv::inRange(MatHSV, Scalar(bar.H_MIN, bar.S_MIN, bar.V_MIN), Scalar(bar.H_MAX, bar.S_MAX, bar.V_MAX), MatThreshold);
			//perform morphological operations on thresholded image to eliminate noise
			//and emphasize the filtered object(s)
			morphOps();
			trackFilteredObject();
			drawIdentifikacijaRobota();
			

			//show frames 
			if (HsvCalibrationMode == true) {

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
			imshow(winOriginal, MatCamera);


			const int wait_key = waitKey(30);
			//delay 30ms so that screen can refresh.
			//image will not appear without this waitKey() command
			//also use waitKey command to capture keyboard input
			if (wait_key == 99)
				HsvCalibrationMode = !HsvCalibrationMode;//if user presses 'c', toggle calibration mode

			if (wait_key == 'q')
				break;
		}
		write_tackbar_values_to_file();

	}
};