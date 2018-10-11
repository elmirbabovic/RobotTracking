// OpenCVtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

TrackbarValues barV;


//initial min and max HSV filter values.
//these will be changed using trackbars

//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 50;

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

void on_trackbar(int, void*)
{//This function gets called whenever a
 // trackbar position is changed

 //for now, this does nothing.



}
void createTrackbars() {
	//create window for trackbars


	cv::namedWindow(winTrackbars, 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf_s(TrackbarName, "H_MIN", barV.H_MIN);
	sprintf_s(TrackbarName, "H_MAX", barV.H_MAX);
	sprintf_s(TrackbarName, "S_MIN", barV.S_MIN);
	sprintf_s(TrackbarName, "S_MAX", barV.S_MAX);
	sprintf_s(TrackbarName, "V_MIN", barV.V_MIN);
	sprintf_s(TrackbarName, "V_MAX", barV.V_MAX);
	sprintf_s(TrackbarName, "V_DILATION_SIZE", barV.V_DILATION_SIZE);
	sprintf_s(TrackbarName, "V_EROSION_SIZE",  barV.V_EROSION_SIZE);
	sprintf_s(TrackbarName, "MIN_OBJECT_AREA", barV.MIN_OBJECT_AREA);
	sprintf_s(TrackbarName, "MAX_OBJECT_AREA", barV.MAX_OBJECT_AREA);
	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH), 
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->      
	cv::createTrackbar("H_MIN", winTrackbars, &barV.H_MIN, 255, on_trackbar);
	cv::createTrackbar("H_MAX", winTrackbars, &barV.H_MAX, 255, on_trackbar);
	cv::createTrackbar("S_MIN", winTrackbars, &barV.S_MIN, 255, on_trackbar);
	cv::createTrackbar("S_MAX", winTrackbars, &barV.S_MAX, 255, on_trackbar);
	cv::createTrackbar("V_MIN", winTrackbars, &barV.V_MIN, 255, on_trackbar);
	cv::createTrackbar("V_MAX", winTrackbars, &barV.V_MAX, 255, on_trackbar);
	cv::createTrackbar("V_DILATION_SIZE", winTrackbars, &barV.V_DILATION_SIZE, 15, on_trackbar);
	cv::createTrackbar("V_EROSION_SIZE", winTrackbars,  &barV.V_EROSION_SIZE, 15, on_trackbar);
	cv::createTrackbar("MIN_OBJECT_AREA", winTrackbars, &barV.MIN_OBJECT_AREA, 100, on_trackbar);
	cv::createTrackbar("MAX_OBJECT_AREA", winTrackbars, &barV.MAX_OBJECT_AREA, 100, on_trackbar);
}
void clickAndDrag_Rectangle(int event, int x, int y, int flags, void* param) {
	//only if calibration mode is true will we use the mouse to change HSV values
	if (calibrationMode == true) {
		//get handle to video feed passed in as "param" and cast as Mat pointer
		cv::Mat* videoFeed = (cv::Mat*)param;

		if (event == CV_EVENT_LBUTTONDOWN && mouseIsDragging == false)
		{
			//keep track of initial point clicked
			initialClickPoint = cv::Point(x, y);
			//user has begun dragging the mouse
			mouseIsDragging = true;
		}
		/* user is dragging the mouse */
		if (event == CV_EVENT_MOUSEMOVE && mouseIsDragging == true)
		{
			//keep track of current mouse point
			currentMousePoint = cv::Point(x, y);
			//user has moved the mouse while clicking and dragging
			mouseMove = true;
		}
		/* user has released left button */
		if (event == CV_EVENT_LBUTTONUP && mouseIsDragging == true)
		{
			//set rectangle ROI to the rectangle that the user has selected
			rectangleROI = cv::Rect(initialClickPoint, currentMousePoint);

			//reset boolean variables
			mouseIsDragging = false;
			mouseMove = false;
			rectangleSelected = true;
		}

		if (event == CV_EVENT_RBUTTONDOWN) {
			//user has clicked right mouse button
			//Reset HSV Values
			barV.H_MIN = 0;
			barV.S_MIN = 0;
			barV.V_MIN = 0;
			barV.H_MAX = 255;
			barV.S_MAX = 255;
			barV.V_MAX = 255;

		}
		if (event == CV_EVENT_MBUTTONDOWN) {

			//user has clicked middle mouse button
			//enter code here if needed.
		}
	}

}
void recordHSV_Values(cv::Mat frame, cv::Mat hsv_frame) {

	//save HSV values for ROI that user selected to a vector
	if (mouseMove == false && rectangleSelected == true) {

		//clear previous vector values
		if (H_ROI.size()>0) H_ROI.clear();
		if (S_ROI.size()>0) S_ROI.clear();
		if (V_ROI.size()>0)V_ROI.clear();
		//if the rectangle has no width or height (user has only dragged a line) then we don't try to iterate over the width or height
		if (rectangleROI.width<1 || rectangleROI.height<1) cout << "Please drag a rectangle, not a line" << endl;
		else {
			for (int i = rectangleROI.x; i<rectangleROI.x + rectangleROI.width; i++) {
				//iterate through both x and y direction and save HSV values at each and every point
				for (int j = rectangleROI.y; j<rectangleROI.y + rectangleROI.height; j++) {
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

		if (H_ROI.size()>0) {
			//NOTE: min_element and max_element return iterators so we must dereference them with "*"
			barV.H_MIN = *std::min_element(H_ROI.begin(), H_ROI.end());
			barV.H_MAX = *std::max_element(H_ROI.begin(), H_ROI.end());
			cout << "MIN 'H' VALUE: " << barV.H_MIN << endl;
			cout << "MAX 'H' VALUE: " << barV.H_MAX << endl;
		}
		if (S_ROI.size()>0) {
			barV.S_MIN = *std::min_element(S_ROI.begin(), S_ROI.end());
			barV.S_MAX = *std::max_element(S_ROI.begin(), S_ROI.end());
			cout << "MIN 'S' VALUE: " << barV.S_MIN << endl;
			cout << "MAX 'S' VALUE: " << barV.S_MAX << endl;
		}
		if (V_ROI.size()>0) {
			barV.V_MIN = *std::min_element(V_ROI.begin(), V_ROI.end());
			barV.V_MAX = *std::max_element(V_ROI.begin(), V_ROI.end());
			cout << "MIN 'V' VALUE: " << barV.V_MIN << endl;
			cout << "MAX 'V' VALUE: " << barV.V_MAX << endl;
		}

	}

	if (mouseMove == true) {
		//if the mouse is held down, we will draw the click and dragged rectangle to the screen
		rectangle(frame, initialClickPoint, cv::Point(currentMousePoint.x, currentMousePoint.y), cv::Scalar(0, 255, 0), 1, 8, 0);
	}


}
string intToString(int number) {
	std::stringstream ss;
	ss << number;
	return ss.str();
}
void drawObject(int x, int y, cv::Mat &frame) {

	//use some of the openCV drawing functions to draw crosshairs
	//on your tracked image!


	//'if' and 'else' statements to prevent
	//memory errors from writing off the screen (ie. (-25,-25) is not within the window)

	//circle(frame, Point(x, y), 20, Scalar(0, 255, 0), 2);
	if (y - 25>0)
		line(frame, cv::Point(x, y), cv::Point(x, y - 25), cv::Scalar(0, 255, 0), 2);
	else line(frame, cv::Point(x, y), cv::Point(x, 0), cv::Scalar(0, 255, 0), 2);
	if (y + 25<FRAME_HEIGHT)
		line(frame, cv::Point(x, y), cv::Point(x, y + 25), cv::Scalar(0, 255, 0), 2);
	else line(frame, cv::Point(x, y), cv::Point(x, FRAME_HEIGHT), cv::Scalar(0, 255, 0), 2);
	if (x - 25>0)
		line(frame, cv::Point(x, y), cv::Point(x - 25, y), cv::Scalar(0, 255, 0), 2);
	else line(frame, cv::Point(x, y), cv::Point(0, y), cv::Scalar(0, 255, 0), 2);
	if (x + 25<FRAME_WIDTH)
		line(frame, cv::Point(x, y), cv::Point(x + 25, y), cv::Scalar(0, 255, 0), 2);
	else line(frame, cv::Point(x, y), cv::Point(FRAME_WIDTH, y), cv::Scalar(0, 255, 0), 2);

	putText(frame, "Koordinate:" + intToString(x) + "," + intToString(y), cv::Point(x, y + 30), 1, 1, cv::Scalar(0, 255, 0), 2);

}
void morphOps(cv::Mat &thresh) {

	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle

	if (barV.V_EROSION_SIZE < 1)
		barV.V_EROSION_SIZE = 1;

	if (barV.V_DILATION_SIZE < 1)
		barV.V_DILATION_SIZE = 1;

	cv::Mat erodeElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(barV.V_EROSION_SIZE, barV.V_EROSION_SIZE));
	//dilate with larger element so make sure object is nicely visible
	cv::Mat dilateElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(barV.V_DILATION_SIZE, barV.V_DILATION_SIZE));

	erode(thresh, thresh, erodeElement);
	erode(thresh, thresh, erodeElement);


	dilate(thresh, thresh, dilateElement);
	dilate(thresh, thresh, dilateElement);
}
void trackFilteredObject(int &x, int &y, cv::Mat threshold, cv::Mat &cameraFeed) {
	cv::Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<cv::Point> > contours;
	vector<cv::Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;
	int largestIndex = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects<MAX_NUM_OBJECTS) 
		{
			for (int index = 0; index >= 0; index = hierarchy[index][0]) 
			{
				cv::Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we save a reference area each
				//iteration and compare it to the area in the next iteration.

				int min = (barV.MIN_OBJECT_AREA / 100.0) * 10 * 20 * 20;
				int max = (barV.MAX_OBJECT_AREA /100.0)  * 10 * 640 * 480 / 1.5;

				if (area>min&& area<max && area>refArea)
				{
					x = moment.m10 / area;
					y = moment.m01 / area;
					objectFound = true;
					refArea = area;
					//save index of largest contour to use with drawContours
					largestIndex = index;
				}
				else 
				{
					objectFound = false;
				}
				//let user know you found an object
				if (objectFound == true) {
					putText(cameraFeed, "Dinamicka prepreka", cv::Point(x, y), 2, 0.5, cv::Scalar(0, 255, 0), 2);
					//draw object location on screen
					drawObject(x, y, cameraFeed);
					//draw largest contour
					//drawContours(cameraFeed, contours, largestIndex, Scalar(0, 255, 255), 2);
				}
			}
			

		}
		else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", cv::Point(0, 50), 1, 2, cv::Scalar(0, 0, 255), 2);
	}
}

void read_tackbar_values_from_file()
{

	ifstream f("aa.txt");
	try
	{
		f_ucitaj(f, barV);
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
	f_snimi(f, barV);
	f.close();
}

void TestZaThread()
{
	int i=0;
	while(1)
	{
		i++;
		cout << "ok: " << intToString(i)<< endl;
		this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main(int argc, char* argv[])
{
	cout << "IZLAZ pomocu tipke 'q' unutar glavom video prozoru \n";
	read_tackbar_values_from_file();
	//some boolean variables for different functionality within this
	//program
	bool trackObjects = true;
	bool useMorphOps = true;
	calibrationMode = true;
	//Matrix to store each frame of the webcam feed
	cv::Mat cameraFeed;
	//matrix storage for HSV image
	cv::Mat HSV;
	//matrix storage for binary threshold image
	cv::Mat threshold;
	//x and y values for the location of the object
	int x = 0, y = 0;
	//video capture object to acquire webcam feed
	cv::VideoCapture capture;
	//open capture object at location zero (default location for webcam)
	capture.open(0);
	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
	//must create a window before setting mouse callback
	cv::namedWindow(winOriginal);
	//set mouse callback function to be active on "Webcam Feed" window
	//we pass the handle to our "frame" matrix so that we can draw a rectangle to it
	//as the user clicks and drags the mouse
	cv::setMouseCallback(winOriginal, clickAndDrag_Rectangle, &cameraFeed);
	//initiate mouse move and drag to false 
	mouseIsDragging = false;
	mouseMove = false;
	rectangleSelected = false;


	//std::thread threadForSerialComm(TestZaThread);

	//start an infinite loop where webcam feed is copied to cameraFeed matrix
	//all of our operations will be performed within this loop
	while (1) {
		//store image to matrix
		capture.read(cameraFeed);
		//convert frame from BGR to HSV colorspace
		cvtColor(cameraFeed, HSV, cv::COLOR_BGR2HSV);
		//set HSV values from user selected region
		recordHSV_Values(cameraFeed, HSV);
		//filter HSV image between values and store filtered image to
		//threshold matrix
		inRange(HSV, cv::Scalar(barV.H_MIN, barV.S_MIN, barV.V_MIN), cv::Scalar(barV.H_MAX, barV.S_MAX, barV.V_MAX), threshold);
		//perform morphological operations on thresholded image to eliminate noise
		//and emphasize the filtered object(s)
		if (useMorphOps)
			morphOps(threshold);
		//pass in thresholded frame to our object tracking function
		//this function will return the x and y coordinates of the
		//filtered object
		if (trackObjects)
			trackFilteredObject(x, y, threshold, cameraFeed);

		//show frames 
		if (calibrationMode == true) {

			//create slider bars for HSV filtering
			createTrackbars();
			imshow(winHsvImage, HSV);
			imshow(winThreshholdedImage, threshold);
		}
		else {

			cv::destroyWindow(winHsvImage);
			cv::destroyWindow(winThreshholdedImage);
			cv::destroyWindow(winTrackbars);
		}
		imshow(winOriginal, cameraFeed);


		int wait_key = cv::waitKey(30);
		//delay 30ms so that screen can refresh.
		//image will not appear without this waitKey() command
		//also use waitKey command to capture keyboard input
		if (wait_key == 99) 
			calibrationMode = !calibrationMode;//if user presses 'c', toggle calibration mode

		if (wait_key == 'p')
			this_thread::sleep_for(std::chrono::milliseconds(1000)); //pauziraj na 1 s

		if (wait_key == 'q')
			break;
	}
	
	write_tackbar_values_to_file();


	return 0;
}

