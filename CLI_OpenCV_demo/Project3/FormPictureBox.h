#pragma once
#include <stdlib.h>		//		rand()
#include "common.h"		//		IplImage * cv_img;
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/opencv.hpp>
#include "opencv\highgui.h"


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
	public ref class FormPictureBox : public System::Windows::Forms::Form
	{

	public:
		FormPictureBox(void)
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
		~FormPictureBox()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;








	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


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
			this->pictureBox1->Location = System::Drawing::Point(13, 78);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(75, 43);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &FormPictureBox::pictureBox1_MouseClick);
			// 
			// FormPictureBox
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(416, 357);
			this->Controls->Add(this->pictureBox1);
			this->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->Name = L"FormPictureBox";
			this->Text = L"MyForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormPictureBox::MyForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &FormPictureBox::MyForm_Load);
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




	}
	};
}
