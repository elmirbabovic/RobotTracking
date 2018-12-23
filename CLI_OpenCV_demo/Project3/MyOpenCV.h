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
#include "MotionHistory.h"
#include "ATP/ListaSekv.h"
#include "MyMath.h"
#include "Robot.h"
#include "RobotCollector.h"
#include "ATP/RedPov.h"
#include <random>


using namespace std;
using namespace cv;

enum calibrationMode
{
	calibrationFront, calibrationRear, no_calibration
};



struct MyOpenCV
{
public:

	RobotCollector robot_collector;
	Red<std::string>* printer = new RedPov<std::string>;

	Robot* FindByLocation(int x, int y, int maxDisplacement=20)
	{
		Robot* robot = robot_collector.Find_NajbliziRobot(x, y, maxDisplacement);


		return robot;
	}

	Robot* FindAndRecordPosition(int x, int y, int addNewIfNotExists, PointType pointType, int maxDisplacement = 50)
	{
		Robot* robot = robot_collector.Find_NajbliziRobot(x, y, maxDisplacement);

		if (robot == nullptr)
		{
			if (addNewIfNotExists && pointType == frontPoint)
			{
				std::random_device rd;     // only used once to initialise (seed) engine
				std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
				uniform_int_distribution<int> uni(0, 255); // guaranteed unbiased

				int r = uni(rng);
				int g = uni(rng);
				int b = uni(rng);
				Scalar color = Scalar(r, g, b);

				robot_collector.DodajRobota(framePozicija, x, y, color, pointType);
			}
		}
		else
		{
			robot->SaveNewPosition(framePozicija, x, y, pointType);
		}

		return robot;
	}

private:
	//video capture object to acquire webcam feed
	VideoCapture capture;
	Mat matHSV1;
	Mat matHSV2;
	Mat matThreshold1;
	Mat matThreshold2;
	Mat matCamera;
	int framePozicija = 0;
	TrackbarValues bar1;
	TrackbarValues bar2;
	bool IsVizijaRunning = false;
	bool IsPaused = false;
	//default capture width and height
	const int FRAME_WIDTH = 640;
	const int FRAME_HEIGHT = 480;
	//max number of objects to be detected in frame
	const int MAX_NUM_OBJECTS = 50;
	//minimum and maximum object area

	//names that will appear at the top of each window
	const string winOriginal = "Original Image :: This build was compiled at " __DATE__ ", " __TIME__ ".";
	const string winHsvImage1 = "HSV Image1";
	const string winHsvImage2 = "HSV Image2";
	const string winThreshholdedImage1 = "Thresholded Image1";
	const string winThreshholdedImage2 = "Thresholded Image2";
	const string winAfterMorphOper = "After Morphological Operations";
	const string winTrackbars = "Trackbars";

	calibrationMode calibrationMode=no_calibration;//used for showing debugging windows, trackbars etc.

	bool mouseIsDragging = false;//used for showing a rectangle on screen as user clicks and drags mouse
	bool mouseMove = false;
	bool rectangleSelected = false;
	Robot* SelectedRobot = nullptr;

	cv::Point initialClickPoint, currentMousePoint; //keep track of initial point clicked and current position of mouse
	cv::Rect rectangleROI; //this is the ROI that the user has selected
	vector<int> H_ROI, S_ROI, V_ROI;// HSV values from the click/drag ROI region stored in separate vectors so that we can sort them easily

	void SelectRobot(int x, int y)
	{
		Robot* r = this->FindByLocation(x, y, 35);
		this->SelectedRobot = r;
	}

	static void on_trackbar(int, void*)
	{

	}


	void PrintMessage(const string& msg)
	{
		printer->dodaj(msg);
	}

	static void local_clickAndDrag_Rectangle(int eventType, int x, int y, int flags, void* param) {

		MyOpenCV* p = (MyOpenCV*)param;

		if (p->calibrationMode == no_calibration)
		{
			if (eventType == CV_EVENT_LBUTTONDOWN)
			{
				p->SelectRobot(x, y);
			}
			
			if (eventType == CV_EVENT_RBUTTONDOWN)
			{
				if(p->SelectedRobot != nullptr)
				{
					p->SelectedRobot->AddMovementPoint(x, y);
					p->PrintMessage("Robot " + intToString(p->SelectedRobot->GetId()) + " goto: (" + intToString(x) + ", " + intToString(y) + ")");

					
				}
				
			}
		}

		//only if calibration mode is true will we use the mouse to change HSV values
		if (p->calibrationMode != no_calibration) {
			//get handle to video feed passed in as "param" and cast as Mat pointer

			if (p->mouseMove == true) {
				//if the mouse is held down, we will draw the click and dragged rectangle to the screen
				rectangle(p->matCamera, p->initialClickPoint, cv::Point(p->currentMousePoint.x, p->currentMousePoint.y), cv::Scalar(0, 255, 0), 1, 8, 0);
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

			if (eventType == CV_EVENT_RBUTTONDOWN) {
				//user has clicked right mouse button
				//Reset HSV Values
				p->bar1.H_MIN = 0;
				p->bar1.S_MIN = 0;
				p->bar1.V_MIN = 0;
				p->bar1.H_MAX = 255;
				p->bar1.S_MAX = 255;
				p->bar1.V_MAX = 255;

				p->bar2.H_MIN = 0;
				p->bar2.S_MIN = 0;
				p->bar2.V_MIN = 0;
				p->bar2.H_MAX = 255;
				p->bar2.S_MAX = 255;
				p->bar2.V_MAX = 255;


			}
			if (eventType == CV_EVENT_MBUTTONDOWN) {

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
			f_ucitaj(f, bar1);
			f_ucitaj(f, bar2);
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
		f_snimi(f, bar1);
		f_snimi(f, bar2);
		f.close();
	}

	void createTrackbars() {
		//create window for trackbars


		namedWindow(winTrackbars, 0);
		//create memory to store trackbar name on window
		char TrackbarName[70];
		sprintf_s(TrackbarName, "bar.H_MIN", bar1.H_MIN);
		sprintf_s(TrackbarName, "bar.H_MAX", bar1.H_MAX);
		sprintf_s(TrackbarName, "bar.S_MIN", bar1.S_MIN);
		sprintf_s(TrackbarName, "bar.S_MAX", bar1.S_MAX);
		sprintf_s(TrackbarName, "bar.V_MIN", bar1.V_MIN);
		sprintf_s(TrackbarName, "bar.V_MAX", bar1.V_MAX);
		sprintf_s(TrackbarName, "bar.V_DILATION_SIZE", bar1.V_DILATION_SIZE);
		sprintf_s(TrackbarName, "bar.V_EROSION_SIZE", bar1.V_EROSION_SIZE);
		sprintf_s(TrackbarName, "bar.MIN_OBJECT_AREA", bar1.MIN_OBJECT_AREA);
		sprintf_s(TrackbarName, "bar.MAX_OBJECT_AREA", bar1.MAX_OBJECT_AREA);
		//create trackbars and insert them into window
		//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
		//the max value the trackbar can move (eg. H_HIGH), 
		//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
		//                                  ---->    ---->     ---->      

		if (calibrationMode == calibrationFront)
		{
			createTrackbar("bar.H_MIN", winTrackbars, &bar1.H_MIN, 255, on_trackbar);
			createTrackbar("bar.H_MAX", winTrackbars, &bar1.H_MAX, 255, on_trackbar);
			createTrackbar("bar.S_MIN", winTrackbars, &bar1.S_MIN, 255, on_trackbar);
			createTrackbar("bar.S_MAX", winTrackbars, &bar1.S_MAX, 255, on_trackbar);
			createTrackbar("bar.V_MIN", winTrackbars, &bar1.V_MIN, 255, on_trackbar);
			createTrackbar("bar.V_MAX", winTrackbars, &bar1.V_MAX, 255, on_trackbar);
			createTrackbar("bar.V_DILATION_SIZE", winTrackbars, &bar1.V_DILATION_SIZE, 10, on_trackbar);
			createTrackbar("bar.V_EROSION_SIZE", winTrackbars, &bar1.V_EROSION_SIZE, 10, on_trackbar);
			createTrackbar("bar.MIN_OBJECT_AREA", winTrackbars, &bar1.MIN_OBJECT_AREA, 100, on_trackbar);
			createTrackbar("bar.MAX_OBJECT_AREA", winTrackbars, &bar1.MAX_OBJECT_AREA, 100, on_trackbar);
		}
		if (calibrationMode == calibrationRear)
		{
			createTrackbar("bar.H_MIN", winTrackbars, &bar2.H_MIN, 255, on_trackbar);
			createTrackbar("bar.H_MAX", winTrackbars, &bar2.H_MAX, 255, on_trackbar);
			createTrackbar("bar.S_MIN", winTrackbars, &bar2.S_MIN, 255, on_trackbar);
			createTrackbar("bar.S_MAX", winTrackbars, &bar2.S_MAX, 255, on_trackbar);
			createTrackbar("bar.V_MIN", winTrackbars, &bar2.V_MIN, 255, on_trackbar);
			createTrackbar("bar.V_MAX", winTrackbars, &bar2.V_MAX, 255, on_trackbar);
			createTrackbar("bar.V_DILATION_SIZE", winTrackbars, &bar2.V_DILATION_SIZE, 10, on_trackbar);
			createTrackbar("bar.V_EROSION_SIZE", winTrackbars,  &bar2.V_EROSION_SIZE, 10, on_trackbar);
			createTrackbar("bar.MIN_OBJECT_AREA", winTrackbars, &bar2.MIN_OBJECT_AREA, 100, on_trackbar);
			createTrackbar("bar.MAX_OBJECT_AREA", winTrackbars, &bar2.MAX_OBJECT_AREA, 100, on_trackbar);
		}
	

	}

	TrackbarValues& GetBar()
	{
		if (calibrationMode == calibrationFront)
		{
			return bar1;
		}
		if (calibrationMode == calibrationRear)
		{
			return bar2;
		}
		throw exception("GetBar::nesto nije uredu");
	}

	Mat& GetMatHsv()
	{
		if (calibrationMode == calibrationFront)
		{
			return matHSV1;
		}
		if (calibrationMode == calibrationRear)
		{
			return matHSV2;
		}
		throw exception("GetMatHsv::nesto nije uredu");
	}


	void recordHSV_Values() {

		if (calibrationMode == no_calibration)
			return;

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
							H_ROI.push_back((int)GetMatHsv().at<cv::Vec3b>(j, i)[0]);
							S_ROI.push_back((int)GetMatHsv().at<cv::Vec3b>(j, i)[1]);
							V_ROI.push_back((int)GetMatHsv().at<cv::Vec3b>(j, i)[2]);
					}
				}
			}
			//reset rectangleSelected so user can select another region if necessary
			rectangleSelected = false;
			//set min and max HSV values from min and max elements of each array

			if (H_ROI.size() > 0) {
				//NOTE: min_element and max_element return iterators so we must dereference them with "*"
				GetBar().H_MIN = *std::min_element(H_ROI.begin(), H_ROI.end());
				GetBar().H_MAX = *std::max_element(H_ROI.begin(), H_ROI.end());
				cout << "MIN 'H' VALUE: " << GetBar().H_MIN << endl;
				cout << "MAX 'H' VALUE: " << GetBar().H_MAX << endl;
			}
			if (S_ROI.size() > 0) {
				GetBar().S_MIN = *std::min_element(S_ROI.begin(), S_ROI.end());
				GetBar().S_MAX = *std::max_element(S_ROI.begin(), S_ROI.end());
				cout << "MIN 'S' VALUE: " << GetBar().S_MIN << endl;
				cout << "MAX 'S' VALUE: " << GetBar().S_MAX << endl;
			}
			if (V_ROI.size() > 0) {
				GetBar().V_MIN = *std::min_element(V_ROI.begin(), V_ROI.end());
				GetBar().V_MAX = *std::max_element(V_ROI.begin(), V_ROI.end());
				cout << "MIN 'V' VALUE: " << GetBar().V_MIN << endl;
				cout << "MAX 'V' VALUE: " << GetBar().V_MAX << endl;
			}

		}

		


	}



	static string intToString(int number) {


		std::stringstream ss;
		ss << number;
		return ss.str();
	}
	void drawCenterLines(int x, int y, Scalar textColor, std::string msg, int fontSize=2) {

		//use some of the openCV drawing functions to draw crosshairs
		//on your tracked image!


		//'if' and 'else' statements to prevent
		//memory errors from writing off the screen (ie. (-25,-25) is not within the window)

		//circle(frame, Point(x, y), 20, Scalar(0, 255, 0), 2);
		if (y - 25 > 0)
			line(matCamera, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
		else line(matCamera, Point(x, y), Point(x, 0), Scalar(0, 255, 0), 2);
		if (y + 25 < FRAME_HEIGHT)
			line(matCamera, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
		else line(matCamera, Point(x, y), Point(x, FRAME_HEIGHT), Scalar(0, 255, 0), 2);
		if (x - 25 > 0)
			line(matCamera, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
		else line(matCamera, Point(x, y), Point(0, y), Scalar(0, 255, 0), 2);
		if (x + 25 < FRAME_WIDTH)
			line(matCamera, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);
		else line(matCamera, Point(x, y), Point(FRAME_WIDTH, y), Scalar(0, 255, 0), 2);

		putText(matCamera, msg +" (" + intToString(x) + "," + intToString(y) + ")", Point(x, y + 30), 1, 1, textColor, fontSize) ;
	}


	void morphOps(TrackbarValues& bar, Mat& matThreshold) {

		//create structuring element that will be used to "dilate" and "erode" image.
		//the element chosen here is a 3px by 3px rectangle

		if (bar.V_EROSION_SIZE < 1)
			bar.V_EROSION_SIZE = 1;

		if (bar.V_DILATION_SIZE < 1)
			bar.V_DILATION_SIZE = 1;

		const Mat erodeElement = getStructuringElement(MORPH_RECT, Size(bar.V_EROSION_SIZE, bar.V_EROSION_SIZE));
		//dilate with larger element so make sure object is nicely visible
		const Mat dilateElement = getStructuringElement(MORPH_RECT, Size(bar.V_DILATION_SIZE, bar.V_DILATION_SIZE));

		erode(matThreshold, matThreshold, erodeElement);
		erode(matThreshold, matThreshold, erodeElement);


		dilate(matThreshold, matThreshold, dilateElement);
		dilate(matThreshold, matThreshold, dilateElement);


	}
	void trackFilteredObject(TrackbarValues& bar, Mat& matThreshold, PointType pointType) {

		Mat temp;
		matThreshold.copyTo(temp);
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
			putText(matCamera, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
			return;
		}


		for (int index = 0; index < contours.size(); index++)
		{
		
			vector<Point> current_contour = contours[index];
			
			cv::Mat mat_current_contour = (cv::Mat)current_contour;

			cv::Mat contourImage(matCamera.size(), CV_8UC3, cv::Scalar(0, 0, 0));

			Moments moment = moments(mat_current_contour);
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

				Robot* robot = FindAndRecordPosition(x, y, true, pointType);
				//draw object location on screen
				if (robot != nullptr)
				{
					if (SelectedRobot == robot)
					{
						//putText(matCamera, "SELECTED", Point(x, y), 2, 1, Scalar(255, 255, 0), 2);
						cv::drawContours(matCamera, contours, index, robot->GetColor(), 4);
					}
					else
					{
						cv::drawContours(matCamera, contours, index, robot->GetColor());
					}
					drawCenterLines(x, y, Scalar(0, 255,0), "R");
	
					if (robot->todoTargetPoints->getVelicina() > 0)
					{
						for (int i = 0; i < robot->todoTargetPoints->getVelicina(); i++)
						{
							auto movement = robot->todoTargetPoints->getSaPozicije(i);
							string msg = "R-" + intToString(robot->GetId()) + "-Goto-" + intToString(movement->versionNumber);
							drawCenterLines(movement->point.x, movement->point.y, Scalar(0, 0, 255), msg);
						}
					}
				}

			}
		}
	}

	void drawIdentifikacijaRobota()
	{
		for (int i = 0; i < robot_collector.Count(); ++i)
		{
			Robot* r = robot_collector.GetRobotByIndex(i);
			MotionStep* positionFront = r->GetPozicijaNajnovijaFront();
			MotionStep* positionRear = r->GetPozicijaNajnovijaRear();
			if (positionFront == nullptr || positionRear ==nullptr)
				return;

			if (r->GetIsRemoved())
			{
				//putText(frame, "id" + intToString(r->GetId()) + " @" + intToString(p->versionNumber), Point(p->item.x, p->item.y - 50), 1, 1, Scalar(255, 0, 0), 2);
			}
			else
			{

				int frontX = positionFront->point.x;
				int frontY = positionFront->point.y;

				int rearX = positionRear->point.x;
				int rearY = positionRear->point.y;

				putText(matCamera, "Front-" + intToString(r->GetId()) + " @" + intToString(positionFront->versionNumber), Point(frontX, frontY - 50), 1, 1, Scalar(255, 255, 0), 2);
				putText(matCamera, "Rear-" + intToString(r->GetId()) + " @" + intToString(positionRear->versionNumber), Point(rearX, rearY - 50), 1, 1, Scalar(255, 255, 0), 2);

				line(matCamera, Point(frontX, frontY), Point(rearX, rearY), Scalar(255, 0, 0), 2);

				/*NullableType<float> ugao = r->GetUgaoPravcaKretanja();

				if (ugao != nullptr)
				{
					float z = MyMath::IzracunajOdnos(ugao);
					int c = 100;
					float b = c / sqrt((z*z) + 1);
					float a = z * b;

					if (r->GetPravacDeltaY() > 0)
						a = abs(a);
					else
						a = -abs(a);

					if (r->GetPravacDeltaX() > 0)
						b = abs(b);
					else
						b = -abs(b);

					float x2 = frontX + b;
					float y2 = frontY + a;

				
				}*/
			}
		}
		putText(matCamera, "frame: " + intToString((framePozicija / 1) * 1), Point(50, 50), 2, 1, Scalar(0, 255, 255), 2);
	}
	void do_abort() {
		for (int i = 0; i < robot_collector.Count(); i++)
		{
			Robot* robot = robot_collector.GetRobotByIndex(i);
			robot->todoTargetPoints->clear();
		}
	}
public:
	void VisionStop()
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
	void VisionStart()
	{
		if (IsVizijaRunning)
			return;
		IsPaused = false;
		IsVizijaRunning = true;
		cout << "IZLAZ pomocu tipke 'q' u glavom video prozoru \n";
		read_tackbar_values_from_file();

		//some boolean variables for different functionality within this
		//program
		calibrationMode = no_calibration;

		//open capture object at location zero (default location for webcam)
		capture.open(1);
		//capture.open("C:\\_robottracking\\SimulatorRobota_02.avi");
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
		while (IsVizijaRunning) 
		{
			if (!IsPaused)
			{
				//store image to matrix
				capture >> matCamera;
				this->framePozicija++;

				if (matCamera.empty())
				{
					IsVizijaRunning = false;
					break;
				}

				robot_collector.RemovedOldRobots(framePozicija);
				//convert frame from BGR to HSV colorspace
				cvtColor(matCamera, matHSV1, COLOR_BGR2HSV);
				cvtColor(matCamera, matHSV2, COLOR_BGR2HSV);
				//set HSV values from user selected region
				recordHSV_Values();
				//filter HSV image between values and store filtered image to
				//threshold matrix
				inRange(matHSV1, Scalar(bar1.H_MIN, bar1.S_MIN, bar1.V_MIN), Scalar(bar1.H_MAX, bar1.S_MAX, bar1.V_MAX), matThreshold1);
				inRange(matHSV2, Scalar(bar2.H_MIN, bar2.S_MIN, bar2.V_MIN), Scalar(bar2.H_MAX, bar2.S_MAX, bar2.V_MAX), matThreshold2);
				//perform morphological operations on thresholded image to eliminate noise
				//and emphasize the filtered object(s)
				morphOps(bar1, matThreshold1);
				morphOps(bar2, matThreshold2);
				//pass in thresholded frame to our object tracking function
				//this function will return the x and y coordinates of the
				//filtered object
				trackFilteredObject(bar1, matThreshold1, frontPoint);
				trackFilteredObject(bar2, matThreshold2, rearPoint);

				drawIdentifikacijaRobota();

			}
			//show frames 
			if (calibrationMode == calibrationFront) {

				//create slider bars for HSV filtering
				createTrackbars();
			///	imshow(winHsvImage1, matHSV1);
				imshow(winThreshholdedImage1, matThreshold1);

				destroyWindow(winHsvImage2);
				destroyWindow(winThreshholdedImage2);
			}
			else if (calibrationMode == calibrationRear) {

				//create slider bars for HSV filtering
				createTrackbars();
				imshow(winHsvImage2, matHSV2);
				imshow(winThreshholdedImage2, matThreshold2);

				destroyWindow(winHsvImage1);
				destroyWindow(winThreshholdedImage1);
			}
			else {

				destroyWindow(winHsvImage1);
				destroyWindow(winHsvImage2);
				destroyWindow(winThreshholdedImage1);
				destroyWindow(winThreshholdedImage2);
				destroyWindow(winTrackbars);
			}
			imshow(winOriginal, matCamera);


			const int wait_key = waitKey(30);
			//delay 30ms so that screen can refresh.
			//image will not appear without this waitKey() command
			//also use waitKey command to capture keyboard input
			if (wait_key == 'f')
				calibrationMode = calibrationFront;//if user presses 'c', toggle calibration mode

			if (wait_key == 'r')
				calibrationMode = calibrationRear;//if user presses 'c', toggle calibration mode

			if (wait_key == 'c')
				calibrationMode = no_calibration;

			if (wait_key == 'a')
			{
				do_abort();
			}


			if (wait_key == 'q')
				break;
		}
		write_tackbar_values_to_file();

	}
};