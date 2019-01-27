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
using namespace System::Threading;

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
	private: System::Windows::Forms::TextBox^  txtR1;
	private: System::Windows::Forms::TextBox^  txtR2;
	private: System::Windows::Forms::TextBox^  txtR3;
	private: System::Windows::Forms::TextBox^  txtR4;
	private: System::Windows::Forms::Button^  btnInitialize1;
	private: System::Windows::Forms::Button^  btnInitialize2;
	private: System::Windows::Forms::Button^  btnInitialize4;




	private: System::Windows::Forms::Button^  btnInitialize3;
	private: System::Windows::Forms::Button^  btnInitializeAll;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;








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
			this->txtR1 = (gcnew System::Windows::Forms::TextBox());
			this->txtR2 = (gcnew System::Windows::Forms::TextBox());
			this->txtR3 = (gcnew System::Windows::Forms::TextBox());
			this->txtR4 = (gcnew System::Windows::Forms::TextBox());
			this->btnInitialize1 = (gcnew System::Windows::Forms::Button());
			this->btnInitialize2 = (gcnew System::Windows::Forms::Button());
			this->btnInitialize4 = (gcnew System::Windows::Forms::Button());
			this->btnInitialize3 = (gcnew System::Windows::Forms::Button());
			this->btnInitializeAll = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
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
			this->cmbComPort->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"COM1", L"COM2", L"COM3", L"COM4", L"COM5", L"COM6",
					L"COM7", L"COM8", L"COM9", L"COM10"
			});
			this->cmbComPort->Location = System::Drawing::Point(12, 301);
			this->cmbComPort->Name = L"cmbComPort";
			this->cmbComPort->Size = System::Drawing::Size(100, 21);
			this->cmbComPort->TabIndex = 4;
			this->cmbComPort->Text = L"COM4";
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
			this->timerForNavgation->Interval = 70;
			this->timerForNavgation->Tick += gcnew System::EventHandler(this, &MyForm::timerForNavgation_Tick);
			// 
			// txtR1
			// 
			this->txtR1->Location = System::Drawing::Point(279, 333);
			this->txtR1->Name = L"txtR1";
			this->txtR1->Size = System::Drawing::Size(100, 20);
			this->txtR1->TabIndex = 12;
			// 
			// txtR2
			// 
			this->txtR2->Location = System::Drawing::Point(397, 333);
			this->txtR2->Name = L"txtR2";
			this->txtR2->Size = System::Drawing::Size(100, 20);
			this->txtR2->TabIndex = 12;
			// 
			// txtR3
			// 
			this->txtR3->Location = System::Drawing::Point(517, 333);
			this->txtR3->Name = L"txtR3";
			this->txtR3->Size = System::Drawing::Size(100, 20);
			this->txtR3->TabIndex = 12;
			// 
			// txtR4
			// 
			this->txtR4->Location = System::Drawing::Point(633, 333);
			this->txtR4->Name = L"txtR4";
			this->txtR4->Size = System::Drawing::Size(100, 20);
			this->txtR4->TabIndex = 12;
			// 
			// btnInitialize1
			// 
			this->btnInitialize1->Location = System::Drawing::Point(279, 359);
			this->btnInitialize1->Name = L"btnInitialize1";
			this->btnInitialize1->Size = System::Drawing::Size(100, 23);
			this->btnInitialize1->TabIndex = 13;
			this->btnInitialize1->Text = L"Initialize 1";
			this->btnInitialize1->UseVisualStyleBackColor = true;
			this->btnInitialize1->Click += gcnew System::EventHandler(this, &MyForm::btnInitialize1_Click);
			// 
			// btnInitialize2
			// 
			this->btnInitialize2->Location = System::Drawing::Point(397, 359);
			this->btnInitialize2->Name = L"btnInitialize2";
			this->btnInitialize2->Size = System::Drawing::Size(100, 23);
			this->btnInitialize2->TabIndex = 14;
			this->btnInitialize2->Text = L"Initialize 2";
			this->btnInitialize2->UseVisualStyleBackColor = true;
			this->btnInitialize2->Click += gcnew System::EventHandler(this, &MyForm::btnInitialize2_Click);
			// 
			// btnInitialize4
			// 
			this->btnInitialize4->Location = System::Drawing::Point(633, 359);
			this->btnInitialize4->Name = L"btnInitialize4";
			this->btnInitialize4->Size = System::Drawing::Size(100, 23);
			this->btnInitialize4->TabIndex = 16;
			this->btnInitialize4->Text = L"Initialize 4";
			this->btnInitialize4->UseVisualStyleBackColor = true;
			this->btnInitialize4->Click += gcnew System::EventHandler(this, &MyForm::btnInitialize4_Click);
			// 
			// btnInitialize3
			// 
			this->btnInitialize3->Location = System::Drawing::Point(515, 359);
			this->btnInitialize3->Name = L"btnInitialize3";
			this->btnInitialize3->Size = System::Drawing::Size(100, 23);
			this->btnInitialize3->TabIndex = 15;
			this->btnInitialize3->Text = L"Initialize 3";
			this->btnInitialize3->UseVisualStyleBackColor = true;
			this->btnInitialize3->Click += gcnew System::EventHandler(this, &MyForm::btnInitialize3_Click);
			// 
			// btnInitializeAll
			// 
			this->btnInitializeAll->Location = System::Drawing::Point(279, 388);
			this->btnInitializeAll->Name = L"btnInitializeAll";
			this->btnInitializeAll->Size = System::Drawing::Size(454, 23);
			this->btnInitializeAll->TabIndex = 17;
			this->btnInitializeAll->Text = L"Initialize All";
			this->btnInitializeAll->UseVisualStyleBackColor = true;
			this->btnInitializeAll->Click += gcnew System::EventHandler(this, &MyForm::btnInitializeAll_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(176, 336);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(97, 13);
			this->label1->TabIndex = 18;
			this->label1->Text = L"Virtual values (0..n)";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(295, 317);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(55, 13);
			this->label2->TabIndex = 19;
			this->label2->Text = L"Physical 1";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(414, 317);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(55, 13);
			this->label3->TabIndex = 19;
			this->label3->Text = L"Physical 2";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(651, 317);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(55, 13);
			this->label4->TabIndex = 19;
			this->label4->Text = L"Physical 4";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(535, 317);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(55, 13);
			this->label5->TabIndex = 19;
			this->label5->Text = L"Physical 3";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(857, 423);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btnInitializeAll);
			this->Controls->Add(this->btnInitialize4);
			this->Controls->Add(this->btnInitialize3);
			this->Controls->Add(this->btnInitialize2);
			this->Controls->Add(this->btnInitialize1);
			this->Controls->Add(this->txtR4);
			this->Controls->Add(this->txtR3);
			this->Controls->Add(this->txtR2);
			this->Controls->Add(this->txtR1);
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
					 //PrintMessage2(cmbComPort->Text + " sent: " + cmd);
				 }
				 catch (System::Exception^ e)
				 {
					 PrintMessage2("Greska: " + e->Message);
				 }
			 }
	private: System::Void BtnSendSerial_Click(System::Object^  sender, System::EventArgs^  e) {
		SendSerialCommand(this->txtSerial->Text);
	}

	MyOpenCV* myOpenCV=nullptr;

	
	static void ThreadCall(Object^ o)
	{
		auto me = (MyForm^)o;
		me->startVizijaM(); // Call a method of an instance of the native class
	
	}
	public: void startVizijaM()
	{
		myOpenCV->VisionStart();
	}
	private: System::Void BtnStartVizija_Click(System::Object^  sender, System::EventArgs^  e) {
		if (myOpenCV == nullptr)
		{
			myOpenCV = new MyOpenCV;
		}
		PrintMessage("VizijaStart");

		auto t = gcnew Thread(gcnew ParameterizedThreadStart(ThreadCall));
		t->Start(this);
		
		
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
		/*TxtOutputMessages->Text += DateTime::Now.ToString("HH:mm:ss") + " ---> " + msg + "\r\n";
		TxtOutputMessages->SelectionStart = TxtOutputMessages->TextLength;
		TxtOutputMessages->ScrollToCaret();*/
	}
private: void PrintMessage2(System::String^ msg) {
	TxtOutputMessages->Text += "frame: " +  myOpenCV->framePozicija.ToString() + "--->" +  DateTime::Now.ToString("HH:mm:ss") + " ---> " + msg + "\r\n";
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

			 void popraviUgao(int& x)
			 {
				 x = x + 360;
				 x = x % 360;
			 }


			 int GetPhysicalRobotId(int virtualId)
			 {
				 if (txtR1->Text == virtualId.ToString())
					 return 1;
				 if (txtR2->Text == virtualId.ToString())
					 return 2;
				 if (txtR3->Text == virtualId.ToString())
					 return 3;
				 if (txtR4->Text == virtualId.ToString())
					 return 4;

				 return -1;
			 }
		

			
void CompileCmdMessage(char * finalnaPoruka, int virtualId, cv::Point currentPoint, int currentAngleOrientation, cv::Point todoTargetPoint) {

	

	int Dx  = MyMath::DeltaX(currentPoint, todoTargetPoint );
	int Dy = MyMath::DeltaY(currentPoint, todoTargetPoint );
	int angleToDestination = MyMath::IzracunajUgao(Dx, Dy);
	popraviUgao(angleToDestination);
	popraviUgao(currentAngleOrientation);

	int physicalRobotId = GetPhysicalRobotId(virtualId);
	auto rID = physicalRobotId.ToString();
	//rID = "1";
	int robotCharsStart = (physicalRobotId -1) * 10;
	int lijevoStart = robotCharsStart + 3;
	int desnoStart = robotCharsStart + 7;

	int angleDifference = angleToDestination - currentAngleOrientation;
	popraviUgao(angleDifference);
	//angleDifference += 360;
	//angleDifference %= 360;
	if (angleDifference > 0 && angleDifference < 170)
	{
		PrintMessage("Idi lijevo za angleDifference = " + rID + " - " + angleDifference.ToString());

	
		finalnaPoruka[lijevoStart+0] = '1';
		finalnaPoruka[lijevoStart+1] = '3';
		finalnaPoruka[lijevoStart+2] = '0';

		finalnaPoruka[desnoStart + 0] = '0';
		finalnaPoruka[desnoStart + 1] = '1';
		finalnaPoruka[desnoStart + 2] = '0';

		//lijevi ide 20
	//desni ide 5
	}
	else if (angleDifference > 190 && angleDifference < 360)
	{
		PrintMessage("Idi desno za angleDifference = " + rID + " - " + angleDifference.ToString());
	
		//lijevi ide 5
		//desni ide 20
		finalnaPoruka[lijevoStart + 0] = '0';
		finalnaPoruka[lijevoStart + 1] = '1';
		finalnaPoruka[lijevoStart + 2] = '0';

		finalnaPoruka[desnoStart + 0] = '1';
		finalnaPoruka[desnoStart + 1] = '3';
		finalnaPoruka[desnoStart + 2] = '0';
		
	}
	else {
		//350 - 370
		PrintMessage("Idi ravno" + rID + " - ");
		finalnaPoruka[lijevoStart + 0] = '1';
		finalnaPoruka[lijevoStart + 1] = '3';	//lijevi 10
		finalnaPoruka[lijevoStart + 2] = '0';	//desni 10

		finalnaPoruka[desnoStart + 0] = '1';
		finalnaPoruka[desnoStart + 1] = '3';
		finalnaPoruka[desnoStart + 2] = '0';
	}
	
			 }
int ciklus = 0;
private: System::Void timerForNavgation_Tick(System::Object^  sender, System::EventArgs^  e) {
	if (myOpenCV == nullptr)
		return;
	ciklus++;
	int ukupnoRobota= myOpenCV->robot_collector.Count();
	
	char* finalnaPorukaChars = new char[50];
	strcpy_s(finalnaPorukaChars, 50, "R1-001-001R2-001-001R3-001-001R4-001-001------");
	

	for (int i = 0; i < ukupnoRobota; i++)
	{
		//if (i == ciklus % ukupnoRobota)
		{
			Robot* robot = myOpenCV->robot_collector.GetRobotByIndex(i);
			int virtualId = robot->GetId();

			int physicalRobotId = GetPhysicalRobotId(virtualId);
		//	auto rID = physicalRobotId.ToString();

			auto queueTargets = robot->todoTargetPoints;
			if (queueTargets->isPrazan())
			{
				//PrintMessage2("Preskoèen robot br. " + physicalRobotId.ToString());
				continue;
				
			}
			MotionStep* pozicija = robot->GetPozicijaNajnovijaFront();
			if (pozicija != nullptr)
			{
				
				cv::Point currentPoint = pozicija->point;
				float currentAngleOrientation = robot->GetUgaoPravcaKretanja();

				cv::Point todoTargetPoint = queueTargets->getSaPozicije(0)->point;
				CompileCmdMessage(finalnaPorukaChars, virtualId, currentPoint, currentAngleOrientation, todoTargetPoint);

				/*timerForNavgation->Stop();
				Sleep(50);
				timerForNavgation->Start();*/
			}
			else
			{
				PrintMessage2("Nema pozicije za robota br. " + physicalRobotId.ToString());
			}
		}
	}

	System::String^ finalnaPorukaStrings = gcnew System::String(finalnaPorukaChars);
	SendSerialCommand(finalnaPorukaStrings);
}
private: System::Void cmbComPort_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

}

		 void pomjeriRobota(System::String^ cmd)
		 {
			 for (int i = 0; i < 7; i++)
			 {
				 SendSerialCommand(cmd);
				 Sleep(100);
			 }
	}

	void identifyRobots(System::String^ robotName, System::String^ msg, TextBox^ txtBox)
	{
		int ukupnoRobota = myOpenCV->robot_collector.Count();

		cv::Point * positions1 = new cv::Point[ukupnoRobota];
		cv::Point * positions2 = new cv::Point[ukupnoRobota];
		double * differences = new double[ukupnoRobota];
		TxtOutputMessages->Text += "---------------------------------\n";
		PrintMessage2(robotName);
		for (int i = 0; i < ukupnoRobota; i++)
		{
			Robot* robot = myOpenCV->robot_collector.GetRobotByIndex(i);
			cv::Point pos1= robot->GetPozicijaNajnovijaFront()->point;
			positions1[i] = pos1;			
		}

		pomjeriRobota(msg);
		
		for (int i = 0; i < ukupnoRobota; i++)
		{
			PrintMessage2("VR:" + i.ToString() + " <<<<<< ");

			Robot* robot = myOpenCV->robot_collector.GetRobotByIndex(i);

			cv::Point pos2 = robot->GetPozicijaNajnovijaFront()->point;
			positions2[i] = pos2;

			double d = MyMath::Udaljenost_DvijeTacke(positions2[i], positions1[i]);
			differences[i] = d;
			auto pos1 = positions1[i];

			PrintMessage2(" pos1=" + pos1.x.ToString() + ", " + pos1.y.ToString() + "), pos2=" + pos2.x.ToString() + ", " + pos2.y.ToString() + ") " + " d=" + d.ToString());

		}

		int detectedVR = MyMath::GetMaxIndex(differences, ukupnoRobota, 5);
		txtBox->Text = detectedVR.ToString();

		Sleep(500);
	}

private: System::Void btnInitializeAll_Click(System::Object^  sender, System::EventArgs^  e) {
	btnInitialize1_Click(nullptr, nullptr);
	btnInitialize2_Click(nullptr, nullptr);
	btnInitialize3_Click(nullptr, nullptr);
	btnInitialize4_Click(nullptr, nullptr);
}

	private: System::Void btnInitialize1_Click(System::Object^  sender, System::EventArgs^  e) {
		identifyRobots("R1x = ", "R1-100-100R2-001-001R3-001-001R4-001-001------", txtR1);
	}

	private: System::Void btnInitialize2_Click(System::Object^  sender, System::EventArgs^  e) {
		identifyRobots("R2 mali = ", "R1-001-001R2-100-100R3-001-001R4-001-001------", txtR2);
	}

	private: System::Void btnInitialize3_Click(System::Object^  sender, System::EventArgs^  e) {
		identifyRobots("R3 veliki = ", "R1-001-001R2-001-001R3-100-100R4-001-001------", txtR3);
	}

	private: System::Void btnInitialize4_Click(System::Object^  sender, System::EventArgs^  e) {
		identifyRobots("R4x =", "R1-001-001R2-001-001R3-001-001R4-100-100------", txtR4);
	}

};
}
