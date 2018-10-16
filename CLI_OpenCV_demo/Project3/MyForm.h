#pragma once
#include <stdlib.h>		//		rand()
#include "common.h"		//		IplImage * cv_img;
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/opencv.hpp>
#include "opencv\highgui.h"
#include "opencv\cv.h"
#include <windows.h>
#include "TackbarValues.h"
#include "FileTools.h"





namespace CLRSample {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(53, 79);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(100, 50);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseClick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		const char* filename = "c:\\_robottracking\\slika1.jpg";
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {

		cv_img = cvLoadImage(filename, CV_LOAD_IMAGE_COLOR);
		if (cv_img == NULL) {
			MessageBox::Show("cvLoadImage error !");
			return;
		}

		//cv::Mat matImage = cv::imread("TestImg.bmp", CV_LOAD_IMAGE_COLOR);
		//cv::cvtColor(matImage, matImage, CV_BGRA2RGBA);

		//auto hBitmap = cv::CreateBitmap(matImage.cols, matImage.rows, 1, 32, matImage.data);
	
		//Bitmap^ bm = Bitmap::FromHbitmap((IntPtr)hBitmap);
		
		Bitmap ^ bm = gcnew Bitmap(cv_img->width, cv_img->height, cv_img->widthStep, Imaging::PixelFormat::Format24bppRgb, IntPtr(cv_img->imageData));
		pictureBox1->Left = 0;
		pictureBox1->Top = 0;
		pictureBox1->Width = bm->Width;
		pictureBox1->Height = bm->Height;
		pictureBox1->Image = bm;
		this->AutoSize = true;

		srand(0);
	}

	 double urand() {
		 return rand() / double(RAND_MAX);
	 }


	private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (cv_img != NULL)
			cvReleaseImage(&cv_img);
	}
	private: System::Void pictureBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		int r = int(50.0 + 100.0 * urand());
		int cr = int(255.0 * urand()), cg = int(255.0 * urand()), cb = int(255.0 * urand());
		cvCircle(cv_img, cvPoint(e->X, e->Y), r, CV_RGB(cr, cg, cb), CV_FILLED, 8);
		Bitmap ^ bm = gcnew Bitmap(cv_img->width, cv_img->height, cv_img->widthStep, Imaging::PixelFormat::Format24bppRgb, IntPtr(cv_img->imageData));
		pictureBox1->Image = bm;

		cv::Mat matImage = cv::imread("c:\\_robottracking\\slika1.jpg", CV_LOAD_IMAGE_COLOR);
			cv::imshow("opis", matImage);


			using namespace std;
			using namespace cv;

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

	}
	};
}
