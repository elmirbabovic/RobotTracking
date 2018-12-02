#pragma once
#include <stdlib.h>		//		rand()
#include "common.h"		//		IplImage * cv_img;
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/opencv.hpp>
#include "opencv\highgui.h"
#include "FormPictureBox.h"
#include "MyOpenCV.h"

#include <string>  
#include <iostream>  
using namespace System;
using namespace std;

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

	private: System::Windows::Forms::Button^  BtnStartVizija;
	private: System::Windows::Forms::Button^  BtnSendSerial;
	private: System::Windows::Forms::TextBox^  txtSerial;
	private: System::Windows::Forms::ComboBox^  cmbComPort;


	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::Button^  BtnShowMat;
	private: System::Windows::Forms::Button^  BtnPictureBox;
	private: System::Windows::Forms::Button^  btnStopVizija;
	private: System::Windows::Forms::TextBox^  TxtOutputMessages;
	private: System::Windows::Forms::Button^  BtnVizijaPause;
	private: System::Windows::Forms::Button^  BtnSeekVideo;

	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Timer^  timerForNavgation;




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
			this->components = (gcnew System::ComponentModel::Container());
			this->BtnStartVizija = (gcnew System::Windows::Forms::Button());
			this->BtnSendSerial = (gcnew System::Windows::Forms::Button());
			this->txtSerial = (gcnew System::Windows::Forms::TextBox());
			this->cmbComPort = (gcnew System::Windows::Forms::ComboBox());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->BtnShowMat = (gcnew System::Windows::Forms::Button());
			this->BtnPictureBox = (gcnew System::Windows::Forms::Button());
			this->btnStopVizija = (gcnew System::Windows::Forms::Button());
			this->TxtOutputMessages = (gcnew System::Windows::Forms::TextBox());
			this->BtnVizijaPause = (gcnew System::Windows::Forms::Button());
			this->BtnSeekVideo = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerForNavgation = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// BtnStartVizija
			// 
			this->BtnStartVizija->Location = System::Drawing::Point(13, 13);
			this->BtnStartVizija->Name = L"BtnStartVizija";
			this->BtnStartVizija->Size = System::Drawing::Size(181, 23);
			this->BtnStartVizija->TabIndex = 1;
			this->BtnStartVizija->Text = L"Start vizija";
			this->BtnStartVizija->UseVisualStyleBackColor = true;
			this->BtnStartVizija->Click += gcnew System::EventHandler(this, &MyForm::BtnStartVizija_Click);
			// 
			// BtnSendSerial
			// 
			this->BtnSendSerial->Location = System::Drawing::Point(118, 300);
			this->BtnSendSerial->Name = L"BtnSendSerial";
			this->BtnSendSerial->Size = System::Drawing::Size(75, 23);
			this->BtnSendSerial->TabIndex = 2;
			this->BtnSendSerial->Text = L"Send Serial";
			this->BtnSendSerial->UseVisualStyleBackColor = true;
			this->BtnSendSerial->Click += gcnew System::EventHandler(this, &MyForm::BtnSendSerial_Click);
			// 
			// txtSerial
			// 
			this->txtSerial->Location = System::Drawing::Point(12, 239);
			this->txtSerial->Multiline = true;
			this->txtSerial->Name = L"txtSerial";
			this->txtSerial->Size = System::Drawing::Size(181, 55);
			this->txtSerial->TabIndex = 3;
			this->txtSerial->Text = L"R1-X523-Y431";
			// 
			// cmbComPort
			// 
			this->cmbComPort->FormattingEnabled = true;
			this->cmbComPort->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"COM1", L"COM2", L"COM3", L"COM4", L"COM5", L"COM6",
					L"COM7"
			});
			this->cmbComPort->Location = System::Drawing::Point(12, 301);
			this->cmbComPort->Name = L"cmbComPort";
			this->cmbComPort->Size = System::Drawing::Size(100, 21);
			this->cmbComPort->TabIndex = 4;
			this->cmbComPort->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::cmbComPort_SelectedIndexChanged);
			// 
			// serialPort1
			// 
			this->serialPort1->BaudRate = 115200;
			// 
			// BtnShowMat
			// 
			this->BtnShowMat->Location = System::Drawing::Point(13, 71);
			this->BtnShowMat->Name = L"BtnShowMat";
			this->BtnShowMat->Size = System::Drawing::Size(182, 23);
			this->BtnShowMat->TabIndex = 5;
			this->BtnShowMat->Text = L"cv:ImgShow (cv::Mat)";
			this->BtnShowMat->UseVisualStyleBackColor = true;
			this->BtnShowMat->Click += gcnew System::EventHandler(this, &MyForm::BtnShowMat_Click);
			// 
			// BtnPictureBox
			// 
			this->BtnPictureBox->Location = System::Drawing::Point(13, 100);
			this->BtnPictureBox->Name = L"BtnPictureBox";
			this->BtnPictureBox->Size = System::Drawing::Size(182, 23);
			this->BtnPictureBox->TabIndex = 6;
			this->BtnPictureBox->Text = L"Forms::PictureBox (IplImage)";
			this->BtnPictureBox->UseVisualStyleBackColor = true;
			this->BtnPictureBox->Click += gcnew System::EventHandler(this, &MyForm::BtnPictureBox_Click);
			// 
			// btnStopVizija
			// 
			this->btnStopVizija->Location = System::Drawing::Point(13, 42);
			this->btnStopVizija->Name = L"btnStopVizija";
			this->btnStopVizija->Size = System::Drawing::Size(181, 23);
			this->btnStopVizija->TabIndex = 7;
			this->btnStopVizija->Text = L"Stop vizija";
			this->btnStopVizija->UseVisualStyleBackColor = true;
			this->btnStopVizija->Click += gcnew System::EventHandler(this, &MyForm::btnStopVizija_Click);
			// 
			// TxtOutputMessages
			// 
			this->TxtOutputMessages->Location = System::Drawing::Point(220, 13);
			this->TxtOutputMessages->Multiline = true;
			this->TxtOutputMessages->Name = L"TxtOutputMessages";
			this->TxtOutputMessages->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->TxtOutputMessages->Size = System::Drawing::Size(599, 298);
			this->TxtOutputMessages->TabIndex = 8;
			// 
			// BtnVizijaPause
			// 
			this->BtnVizijaPause->Location = System::Drawing::Point(13, 130);
			this->BtnVizijaPause->Name = L"BtnVizijaPause";
			this->BtnVizijaPause->Size = System::Drawing::Size(181, 23);
			this->BtnVizijaPause->TabIndex = 9;
			this->BtnVizijaPause->Text = L"Vizija Pause / Resume";
			this->BtnVizijaPause->UseVisualStyleBackColor = true;
			this->BtnVizijaPause->Click += gcnew System::EventHandler(this, &MyForm::BtnVizijaPause_Click);
			// 
			// BtnSeekVideo
			// 
			this->BtnSeekVideo->Enabled = false;
			this->BtnSeekVideo->Location = System::Drawing::Point(13, 210);
			this->BtnSeekVideo->Name = L"BtnSeekVideo";
			this->BtnSeekVideo->Size = System::Drawing::Size(180, 23);
			this->BtnSeekVideo->TabIndex = 10;
			this->BtnSeekVideo->Text = L"Seek video";
			this->BtnSeekVideo->UseVisualStyleBackColor = true;
			this->BtnSeekVideo->Click += gcnew System::EventHandler(this, &MyForm::BtnSeekVideo_Click);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(13, 159);
			this->trackBar1->Maximum = 100;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(180, 45);
			this->trackBar1->TabIndex = 11;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 200;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// timerForNavgation
			// 
			this->timerForNavgation->Enabled = true;
			this->timerForNavgation->Interval = 500;
			this->timerForNavgation->Tick += gcnew System::EventHandler(this, &MyForm::timerForNavgation_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(857, 344);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->BtnSeekVideo);
			this->Controls->Add(this->BtnVizijaPause);
			this->Controls->Add(this->TxtOutputMessages);
			this->Controls->Add(this->btnStopVizija);
			this->Controls->Add(this->BtnPictureBox);
			this->Controls->Add(this->BtnShowMat);
			this->Controls->Add(this->cmbComPort);
			this->Controls->Add(this->txtSerial);
			this->Controls->Add(this->BtnSendSerial);
			this->Controls->Add(this->BtnStartVizija);
			this->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		PrintMessage("MyForm_Load");
	}


	private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (cv_img != nullptr)
			cvReleaseImage(&cv_img);

		if (myOpenCV != nullptr)
		{
			myOpenCV->VisionStop();
			PrintMessage("VizijaStop");
		}
	}

			 private: void SendSerialCommand(System::String^ cmd)
			 {
				 try
				 {
					
					 if (!serialPort1->IsOpen)
					 {
						 this->serialPort1->PortName = cmbComPort->Text;
						 serialPort1->Open();
						 PrintMessage(cmbComPort->Text + " opened");
					 }


					 serialPort1->WriteLine(cmd);
					 //serialPort1->Close();
					 PrintMessage(cmbComPort->Text + " sent: " + cmd);
				 }
				 catch (System::Exception^ e)
				 {
					 PrintMessage("Greska: " + e->Message);
				 }
			 }
	private: System::Void BtnSendSerial_Click(System::Object^  sender, System::EventArgs^  e) {
		SendSerialCommand(this->txtSerial->Text);
	}

	MyOpenCV* myOpenCV=nullptr;

	

	private: System::Void BtnStartVizija_Click(System::Object^  sender, System::EventArgs^  e) {
		if (myOpenCV == nullptr)
		{
			myOpenCV = new MyOpenCV;
		}
		PrintMessage("VizijaStart");
		myOpenCV->VisionStart();
	}
	private: System::Void BtnShowMat_Click(System::Object^  sender, System::EventArgs^  e) {
		cv::Mat matImage = cv::imread("c:\\_robottracking\\slika1.jpg", CV_LOAD_IMAGE_COLOR);
		cv::imshow("slika1.jpg", matImage);
		PrintMessage("BtnShowMat Clicked");
	}


	private: System::Void BtnPictureBox_Click(System::Object^  sender, System::EventArgs^  e) {
		FormPictureBox^ frm = gcnew FormPictureBox;
		frm->Show();
		PrintMessage("BtnPictureBox Clicked");
	}
	private: System::Void btnStopVizija_Click(System::Object^  sender, System::EventArgs^  e) {
		if (myOpenCV != nullptr)
		{
			myOpenCV->VisionStop();
			PrintMessage("Vizija stopped");
		}
	}

		



	private: void PrintMessage(System::String^ msg)	{
		TxtOutputMessages->Text += DateTime::Now.ToString("HH:mm:ss") + " ---> " + msg + "\r\n";
		TxtOutputMessages->SelectionStart = TxtOutputMessages->TextLength;
		TxtOutputMessages->ScrollToCaret();
	}

	

	private: System::Void BtnVizijaPause_Click(System::Object^  sender, System::EventArgs^  e) {
		if (myOpenCV != nullptr)
		{
			myOpenCV->PauseToogle();
			PrintMessage("Pause/Resume clicked");
		}
	}

private: System::Void BtnSeekVideo_Click(System::Object^  sender, System::EventArgs^  e) {
	auto v = trackBar1->Value ;
	if (myOpenCV != nullptr)
	{
		myOpenCV->GoTo(v / 100.0);
		PrintMessage("Seek to " + System::Convert::ToString(v) + " %");
	}
}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		if (myOpenCV == nullptr)
			return;

		if (!myOpenCV->printer->isPrazan())
		{
			string s = myOpenCV->printer->ukloni();
			System::String^ ms = gcnew System::String(s.c_str());
			PrintMessage(ms);
		}
	}
void DoNavigation(int IDrobot, cv::Point currentPoint, float currentAngleOrientation, cv::Point todoTargetPoint) {

	int Dx  = MyMath::DeltaX(currentPoint, todoTargetPoint );
	int Dy = MyMath::DeltaY(currentPoint, todoTargetPoint );
	float angleToDestination = MyMath::IzracunajUgao(Dx, Dy);
	float angleDifference = angleToDestination - currentAngleOrientation;
	if (angleDifference > 2)
	{
		SendSerialCommand("R3" + "-100" + "-200");//IDrobot.ToString()
		//lijevi ide 5
		//desni ide 20

	}
	else if (angleDifference < -2)
	{
		SendSerialCommand( "R3"+ "-200" + "-100");//IDrobot.ToString()

		//lijevi ide 20
	//desni ide 5
	}
	else {
		SendSerialCommand("R3" + "-100" + "-100");//IDrobot.ToString()
		//lijevi 10
		//desni 10
	}

			 }
private: System::Void timerForNavgation_Tick(System::Object^  sender, System::EventArgs^  e) {
	if (myOpenCV == nullptr)
		return;

	for (int i = 0; i < myOpenCV->robot_collector.Count(); i++)
	{
		Robot* robot = myOpenCV->robot_collector.GetRobotByIndex(i);
		auto queueTargets = robot->todoTargetPoints;
		if (queueTargets->isPrazan())
		{
			continue;
		}
		MotionStep* pozicija = robot->GetPozicijaNajnovija();
		if (pozicija != nullptr)
		{
			int IDrobot = robot->GetId();
			cv::Point currentPoint = pozicija->point;
			float currentAngleOrientation = robot->GetUgaoPravcaKretanja();
			
			cv::Point todoTargetPoint = queueTargets->getSaPozicije(0)->point;
			DoNavigation(IDrobot, currentPoint, currentAngleOrientation, todoTargetPoint);
		}

	}
}
private: System::Void cmbComPort_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

}
};
}
