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
	using namespace System::Runtime::InteropServices;
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



	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Timer^  timerForNavgation;
	private: System::Windows::Forms::ComboBox^  cmbSettings;
	private: System::Windows::Forms::TextBox^  txtItemName;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TrackBar^  barSminR;

	private: System::Windows::Forms::TrackBar^  barHminR;



	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TrackBar^  barSmaxR;
	private: System::Windows::Forms::TrackBar^  barErisionR;



	private: System::Windows::Forms::TrackBar^  barDilationR;

	private: System::Windows::Forms::TrackBar^  barVmaxR;

	private: System::Windows::Forms::TrackBar^  barVminR;




	private: System::Windows::Forms::TrackBar^  barHmaxR;
	private: System::Windows::Forms::Label^  lblValueErision;




	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  btnRefreshBarsRear;
	private: System::Windows::Forms::Label^  lblValueVR;

	private: System::Windows::Forms::Label^  lblValueSR;

	private: System::Windows::Forms::Label^  lblValueHR;
	private: System::Windows::Forms::Label^  lblValueErisionR;


	private: System::Windows::Forms::Label^  lblValueDilationR;

	private: System::Windows::Forms::Button^  btnResetBarValues;
	private: System::Windows::Forms::Button^  btnSaveSettings;
	private: System::Windows::Forms::Button^  btnDeleteSettings;
	private: System::Windows::Forms::Label^  lblValueHF;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TrackBar^  barHmaxF;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TrackBar^  barHminF;
	private: System::Windows::Forms::Label^  lblValueErisionF;


	private: System::Windows::Forms::Label^  lblValueDilationF;

	private: System::Windows::Forms::Label^  lblValueVF;

	private: System::Windows::Forms::Label^  lblValueSF;

	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TrackBar^  barErisionF;

	private: System::Windows::Forms::TrackBar^  barDilationF;

	private: System::Windows::Forms::TrackBar^  barVmaxF;

private: System::Windows::Forms::TrackBar^  barVminF;

	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::TrackBar^  barSmaxF;

private: System::Windows::Forms::TrackBar^  barSminF;






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
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerForNavgation = (gcnew System::Windows::Forms::Timer(this->components));
			this->cmbSettings = (gcnew System::Windows::Forms::ComboBox());
			this->txtItemName = (gcnew System::Windows::Forms::TextBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->lblValueErisionR = (gcnew System::Windows::Forms::Label());
			this->lblValueDilationR = (gcnew System::Windows::Forms::Label());
			this->lblValueVR = (gcnew System::Windows::Forms::Label());
			this->lblValueSR = (gcnew System::Windows::Forms::Label());
			this->lblValueHR = (gcnew System::Windows::Forms::Label());
			this->btnRefreshBarsRear = (gcnew System::Windows::Forms::Button());
			this->lblValueErision = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->barErisionR = (gcnew System::Windows::Forms::TrackBar());
			this->barDilationR = (gcnew System::Windows::Forms::TrackBar());
			this->barVmaxR = (gcnew System::Windows::Forms::TrackBar());
			this->barVminR = (gcnew System::Windows::Forms::TrackBar());
			this->barHmaxR = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->barSmaxR = (gcnew System::Windows::Forms::TrackBar());
			this->barSminR = (gcnew System::Windows::Forms::TrackBar());
			this->barHminR = (gcnew System::Windows::Forms::TrackBar());
			this->btnResetBarValues = (gcnew System::Windows::Forms::Button());
			this->btnSaveSettings = (gcnew System::Windows::Forms::Button());
			this->btnDeleteSettings = (gcnew System::Windows::Forms::Button());
			this->lblValueHF = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->barHmaxF = (gcnew System::Windows::Forms::TrackBar());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->barHminF = (gcnew System::Windows::Forms::TrackBar());
			this->lblValueErisionF = (gcnew System::Windows::Forms::Label());
			this->lblValueDilationF = (gcnew System::Windows::Forms::Label());
			this->lblValueVF = (gcnew System::Windows::Forms::Label());
			this->lblValueSF = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->barErisionF = (gcnew System::Windows::Forms::TrackBar());
			this->barDilationF = (gcnew System::Windows::Forms::TrackBar());
			this->barVmaxF = (gcnew System::Windows::Forms::TrackBar());
			this->barVminF = (gcnew System::Windows::Forms::TrackBar());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->barSmaxF = (gcnew System::Windows::Forms::TrackBar());
			this->barSminF = (gcnew System::Windows::Forms::TrackBar());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barErisionR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barDilationR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barVmaxR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barVminR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barHmaxR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSmaxR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSminR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barHminR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barHmaxF))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barHminF))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barErisionF))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barDilationF))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barVmaxF))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barVminF))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSmaxF))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSminF))->BeginInit();
			this->SuspendLayout();
			// 
			// BtnStartVizija
			// 
			this->BtnStartVizija->Location = System::Drawing::Point(11, 155);
			this->BtnStartVizija->Name = L"BtnStartVizija";
			this->BtnStartVizija->Size = System::Drawing::Size(181, 23);
			this->BtnStartVizija->TabIndex = 1;
			this->BtnStartVizija->Text = L"Start vizija";
			this->BtnStartVizija->UseVisualStyleBackColor = true;
			this->BtnStartVizija->Click += gcnew System::EventHandler(this, &MyForm::BtnStartVizija_Click);
			// 
			// BtnSendSerial
			// 
			this->BtnSendSerial->Location = System::Drawing::Point(119, 372);
			this->BtnSendSerial->Name = L"BtnSendSerial";
			this->BtnSendSerial->Size = System::Drawing::Size(75, 23);
			this->BtnSendSerial->TabIndex = 2;
			this->BtnSendSerial->Text = L"Send Serial";
			this->BtnSendSerial->UseVisualStyleBackColor = true;
			this->BtnSendSerial->Click += gcnew System::EventHandler(this, &MyForm::BtnSendSerial_Click);
			// 
			// txtSerial
			// 
			this->txtSerial->Location = System::Drawing::Point(12, 307);
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
			this->cmbComPort->Location = System::Drawing::Point(13, 373);
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
			this->BtnShowMat->Location = System::Drawing::Point(12, 214);
			this->BtnShowMat->Name = L"BtnShowMat";
			this->BtnShowMat->Size = System::Drawing::Size(182, 23);
			this->BtnShowMat->TabIndex = 5;
			this->BtnShowMat->Text = L"cv:ImgShow (cv::Mat)";
			this->BtnShowMat->UseVisualStyleBackColor = true;
			this->BtnShowMat->Click += gcnew System::EventHandler(this, &MyForm::BtnShowMat_Click);
			// 
			// BtnPictureBox
			// 
			this->BtnPictureBox->Location = System::Drawing::Point(11, 242);
			this->BtnPictureBox->Name = L"BtnPictureBox";
			this->BtnPictureBox->Size = System::Drawing::Size(182, 23);
			this->BtnPictureBox->TabIndex = 6;
			this->BtnPictureBox->Text = L"Forms::PictureBox (IplImage)";
			this->BtnPictureBox->UseVisualStyleBackColor = true;
			this->BtnPictureBox->Click += gcnew System::EventHandler(this, &MyForm::BtnPictureBox_Click);
			// 
			// btnStopVizija
			// 
			this->btnStopVizija->Location = System::Drawing::Point(11, 184);
			this->btnStopVizija->Name = L"btnStopVizija";
			this->btnStopVizija->Size = System::Drawing::Size(181, 23);
			this->btnStopVizija->TabIndex = 7;
			this->btnStopVizija->Text = L"Stop vizija";
			this->btnStopVizija->UseVisualStyleBackColor = true;
			this->btnStopVizija->Click += gcnew System::EventHandler(this, &MyForm::btnStopVizija_Click);
			// 
			// TxtOutputMessages
			// 
			this->TxtOutputMessages->Location = System::Drawing::Point(0, 0);
			this->TxtOutputMessages->Multiline = true;
			this->TxtOutputMessages->Name = L"TxtOutputMessages";
			this->TxtOutputMessages->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->TxtOutputMessages->Size = System::Drawing::Size(638, 298);
			this->TxtOutputMessages->TabIndex = 8;
			// 
			// BtnVizijaPause
			// 
			this->BtnVizijaPause->Location = System::Drawing::Point(12, 271);
			this->BtnVizijaPause->Name = L"BtnVizijaPause";
			this->BtnVizijaPause->Size = System::Drawing::Size(181, 23);
			this->BtnVizijaPause->TabIndex = 9;
			this->BtnVizijaPause->Text = L"Vizija Pause / Resume";
			this->BtnVizijaPause->UseVisualStyleBackColor = true;
			this->BtnVizijaPause->Click += gcnew System::EventHandler(this, &MyForm::BtnVizijaPause_Click);
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
			// cmbSettings
			// 
			this->cmbSettings->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbSettings->FormattingEnabled = true;
			this->cmbSettings->Location = System::Drawing::Point(12, 13);
			this->cmbSettings->Name = L"cmbSettings";
			this->cmbSettings->Size = System::Drawing::Size(181, 21);
			this->cmbSettings->TabIndex = 10;
			this->cmbSettings->TextChanged += gcnew System::EventHandler(this, &MyForm::cmbSettings_TextChanged);
			// 
			// txtItemName
			// 
			this->txtItemName->Location = System::Drawing::Point(13, 41);
			this->txtItemName->MaxLength = 19;
			this->txtItemName->Name = L"txtItemName";
			this->txtItemName->Size = System::Drawing::Size(180, 20);
			this->txtItemName->TabIndex = 11;
			this->txtItemName->TextChanged += gcnew System::EventHandler(this, &MyForm::txtItemName_TextChanged);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Location = System::Drawing::Point(199, 13);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(646, 522);
			this->tabControl1->TabIndex = 12;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->TxtOutputMessages);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(638, 496);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Output";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->lblValueErisionF);
			this->tabPage2->Controls->Add(this->lblValueDilationF);
			this->tabPage2->Controls->Add(this->lblValueVF);
			this->tabPage2->Controls->Add(this->lblValueSF);
			this->tabPage2->Controls->Add(this->label12);
			this->tabPage2->Controls->Add(this->label13);
			this->tabPage2->Controls->Add(this->barErisionF);
			this->tabPage2->Controls->Add(this->barDilationF);
			this->tabPage2->Controls->Add(this->barVmaxF);
			this->tabPage2->Controls->Add(this->barVminF);
			this->tabPage2->Controls->Add(this->label14);
			this->tabPage2->Controls->Add(this->label15);
			this->tabPage2->Controls->Add(this->barSmaxF);
			this->tabPage2->Controls->Add(this->barSminF);
			this->tabPage2->Controls->Add(this->lblValueHF);
			this->tabPage2->Controls->Add(this->button1);
			this->tabPage2->Controls->Add(this->barHmaxF);
			this->tabPage2->Controls->Add(this->label6);
			this->tabPage2->Controls->Add(this->barHminF);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(638, 496);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Front bars";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->lblValueErisionR);
			this->tabPage3->Controls->Add(this->lblValueDilationR);
			this->tabPage3->Controls->Add(this->lblValueVR);
			this->tabPage3->Controls->Add(this->lblValueSR);
			this->tabPage3->Controls->Add(this->lblValueHR);
			this->tabPage3->Controls->Add(this->btnRefreshBarsRear);
			this->tabPage3->Controls->Add(this->lblValueErision);
			this->tabPage3->Controls->Add(this->label4);
			this->tabPage3->Controls->Add(this->barErisionR);
			this->tabPage3->Controls->Add(this->barDilationR);
			this->tabPage3->Controls->Add(this->barVmaxR);
			this->tabPage3->Controls->Add(this->barVminR);
			this->tabPage3->Controls->Add(this->barHmaxR);
			this->tabPage3->Controls->Add(this->label3);
			this->tabPage3->Controls->Add(this->label2);
			this->tabPage3->Controls->Add(this->label1);
			this->tabPage3->Controls->Add(this->barSmaxR);
			this->tabPage3->Controls->Add(this->barSminR);
			this->tabPage3->Controls->Add(this->barHminR);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(638, 496);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Rear bars";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// lblValueErisionR
			// 
			this->lblValueErisionR->AutoSize = true;
			this->lblValueErisionR->Location = System::Drawing::Point(12, 429);
			this->lblValueErisionR->Name = L"lblValueErisionR";
			this->lblValueErisionR->Size = System::Drawing::Size(16, 13);
			this->lblValueErisionR->TabIndex = 13;
			this->lblValueErisionR->Text = L"...";
			// 
			// lblValueDilationR
			// 
			this->lblValueDilationR->AutoSize = true;
			this->lblValueDilationR->Location = System::Drawing::Point(12, 359);
			this->lblValueDilationR->Name = L"lblValueDilationR";
			this->lblValueDilationR->Size = System::Drawing::Size(16, 13);
			this->lblValueDilationR->TabIndex = 12;
			this->lblValueDilationR->Text = L"...";
			// 
			// lblValueVR
			// 
			this->lblValueVR->AutoSize = true;
			this->lblValueVR->Location = System::Drawing::Point(10, 275);
			this->lblValueVR->Name = L"lblValueVR";
			this->lblValueVR->Size = System::Drawing::Size(16, 13);
			this->lblValueVR->TabIndex = 11;
			this->lblValueVR->Text = L"...";
			// 
			// lblValueSR
			// 
			this->lblValueSR->AutoSize = true;
			this->lblValueSR->Location = System::Drawing::Point(10, 184);
			this->lblValueSR->Name = L"lblValueSR";
			this->lblValueSR->Size = System::Drawing::Size(16, 13);
			this->lblValueSR->TabIndex = 11;
			this->lblValueSR->Text = L"...";
			// 
			// lblValueHR
			// 
			this->lblValueHR->AutoSize = true;
			this->lblValueHR->Location = System::Drawing::Point(9, 91);
			this->lblValueHR->Name = L"lblValueHR";
			this->lblValueHR->Size = System::Drawing::Size(16, 13);
			this->lblValueHR->TabIndex = 11;
			this->lblValueHR->Text = L"...";
			// 
			// btnRefreshBarsRear
			// 
			this->btnRefreshBarsRear->Location = System::Drawing::Point(548, 6);
			this->btnRefreshBarsRear->Name = L"btnRefreshBarsRear";
			this->btnRefreshBarsRear->Size = System::Drawing::Size(75, 23);
			this->btnRefreshBarsRear->TabIndex = 10;
			this->btnRefreshBarsRear->Text = L"Refresh";
			this->btnRefreshBarsRear->UseVisualStyleBackColor = true;
			this->btnRefreshBarsRear->Click += gcnew System::EventHandler(this, &MyForm::btnRefreshBarsRear_Click);
			// 
			// lblValueErision
			// 
			this->lblValueErision->AutoSize = true;
			this->lblValueErision->Location = System::Drawing::Point(12, 407);
			this->lblValueErision->Name = L"lblValueErision";
			this->lblValueErision->Size = System::Drawing::Size(38, 13);
			this->lblValueErision->TabIndex = 9;
			this->lblValueErision->Text = L"Erision";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 346);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(42, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Dilation";
			// 
			// barErisionR
			// 
			this->barErisionR->Location = System::Drawing::Point(54, 407);
			this->barErisionR->Maximum = 255;
			this->barErisionR->Name = L"barErisionR";
			this->barErisionR->Size = System::Drawing::Size(581, 45);
			this->barErisionR->TabIndex = 6;
			this->barErisionR->TickFrequency = 2;
			this->barErisionR->Scroll += gcnew System::EventHandler(this, &MyForm::barErisionR_Scroll);
			// 
			// barDilationR
			// 
			this->barDilationR->Location = System::Drawing::Point(54, 346);
			this->barDilationR->Maximum = 255;
			this->barDilationR->Name = L"barDilationR";
			this->barDilationR->Size = System::Drawing::Size(581, 45);
			this->barDilationR->TabIndex = 7;
			this->barDilationR->TickFrequency = 2;
			this->barDilationR->Scroll += gcnew System::EventHandler(this, &MyForm::barDilationR_Scroll);
			// 
			// barVmaxR
			// 
			this->barVmaxR->Location = System::Drawing::Point(54, 282);
			this->barVmaxR->Maximum = 255;
			this->barVmaxR->Name = L"barVmaxR";
			this->barVmaxR->Size = System::Drawing::Size(581, 45);
			this->barVmaxR->TabIndex = 4;
			this->barVmaxR->TickFrequency = 2;
			this->barVmaxR->Scroll += gcnew System::EventHandler(this, &MyForm::barVmaxR_Scroll);
			// 
			// barVminR
			// 
			this->barVminR->Location = System::Drawing::Point(54, 243);
			this->barVminR->Maximum = 255;
			this->barVminR->Name = L"barVminR";
			this->barVminR->Size = System::Drawing::Size(581, 45);
			this->barVminR->TabIndex = 5;
			this->barVminR->TickFrequency = 2;
			this->barVminR->Scroll += gcnew System::EventHandler(this, &MyForm::barVminR_Scroll);
			// 
			// barHmaxR
			// 
			this->barHmaxR->Location = System::Drawing::Point(54, 91);
			this->barHmaxR->Maximum = 255;
			this->barHmaxR->Name = L"barHmaxR";
			this->barHmaxR->Size = System::Drawing::Size(581, 45);
			this->barHmaxR->TabIndex = 3;
			this->barHmaxR->TickFrequency = 2;
			this->barHmaxR->Scroll += gcnew System::EventHandler(this, &MyForm::barHmaxR_Scroll);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 246);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(14, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"V";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(10, 159);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(14, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"S";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 62);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(15, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"H";
			// 
			// barSmaxR
			// 
			this->barSmaxR->Location = System::Drawing::Point(54, 189);
			this->barSmaxR->Maximum = 255;
			this->barSmaxR->Name = L"barSmaxR";
			this->barSmaxR->Size = System::Drawing::Size(581, 45);
			this->barSmaxR->TabIndex = 0;
			this->barSmaxR->TickFrequency = 2;
			this->barSmaxR->Scroll += gcnew System::EventHandler(this, &MyForm::barSmaxR_Scroll);
			// 
			// barSminR
			// 
			this->barSminR->Location = System::Drawing::Point(54, 152);
			this->barSminR->Maximum = 255;
			this->barSminR->Name = L"barSminR";
			this->barSminR->Size = System::Drawing::Size(581, 45);
			this->barSminR->TabIndex = 0;
			this->barSminR->TickFrequency = 2;
			this->barSminR->Scroll += gcnew System::EventHandler(this, &MyForm::barSminR_Scroll);
			// 
			// barHminR
			// 
			this->barHminR->Location = System::Drawing::Point(54, 50);
			this->barHminR->Maximum = 255;
			this->barHminR->Name = L"barHminR";
			this->barHminR->Size = System::Drawing::Size(581, 45);
			this->barHminR->TabIndex = 0;
			this->barHminR->TickFrequency = 2;
			this->barHminR->Scroll += gcnew System::EventHandler(this, &MyForm::barHminR_Scroll);
			// 
			// btnResetBarValues
			// 
			this->btnResetBarValues->Location = System::Drawing::Point(13, 67);
			this->btnResetBarValues->Name = L"btnResetBarValues";
			this->btnResetBarValues->Size = System::Drawing::Size(89, 23);
			this->btnResetBarValues->TabIndex = 13;
			this->btnResetBarValues->Text = L"Reset settings";
			this->btnResetBarValues->UseVisualStyleBackColor = true;
			this->btnResetBarValues->Click += gcnew System::EventHandler(this, &MyForm::btnResetBarValues_Click);
			// 
			// btnSaveSettings
			// 
			this->btnSaveSettings->Location = System::Drawing::Point(108, 67);
			this->btnSaveSettings->Name = L"btnSaveSettings";
			this->btnSaveSettings->Size = System::Drawing::Size(84, 23);
			this->btnSaveSettings->TabIndex = 14;
			this->btnSaveSettings->Text = L"Save settings";
			this->btnSaveSettings->UseVisualStyleBackColor = true;
			this->btnSaveSettings->Click += gcnew System::EventHandler(this, &MyForm::btnSaveSettings_Click);
			// 
			// btnDeleteSettings
			// 
			this->btnDeleteSettings->Location = System::Drawing::Point(13, 92);
			this->btnDeleteSettings->Name = L"btnDeleteSettings";
			this->btnDeleteSettings->Size = System::Drawing::Size(89, 23);
			this->btnDeleteSettings->TabIndex = 13;
			this->btnDeleteSettings->Text = L"Delete settings";
			this->btnDeleteSettings->UseVisualStyleBackColor = true;
			this->btnDeleteSettings->Click += gcnew System::EventHandler(this, &MyForm::btnDeleteSettings_Click);
			// 
			// lblValueHF
			// 
			this->lblValueHF->AutoSize = true;
			this->lblValueHF->Location = System::Drawing::Point(6, 91);
			this->lblValueHF->Name = L"lblValueHF";
			this->lblValueHF->Size = System::Drawing::Size(16, 13);
			this->lblValueHF->TabIndex = 16;
			this->lblValueHF->Text = L"...";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(545, 6);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 15;
			this->button1->Text = L"Refresh";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// barHmaxF
			// 
			this->barHmaxF->Location = System::Drawing::Point(51, 91);
			this->barHmaxF->Maximum = 255;
			this->barHmaxF->Name = L"barHmaxF";
			this->barHmaxF->Size = System::Drawing::Size(581, 45);
			this->barHmaxF->TabIndex = 14;
			this->barHmaxF->TickFrequency = 2;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 62);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(15, 13);
			this->label6->TabIndex = 13;
			this->label6->Text = L"H";
			// 
			// barHminF
			// 
			this->barHminF->Location = System::Drawing::Point(51, 50);
			this->barHminF->Maximum = 255;
			this->barHminF->Name = L"barHminF";
			this->barHminF->Size = System::Drawing::Size(581, 45);
			this->barHminF->TabIndex = 12;
			this->barHminF->TickFrequency = 2;
			// 
			// lblValueErisionF
			// 
			this->lblValueErisionF->AutoSize = true;
			this->lblValueErisionF->Location = System::Drawing::Point(10, 424);
			this->lblValueErisionF->Name = L"lblValueErisionF";
			this->lblValueErisionF->Size = System::Drawing::Size(16, 13);
			this->lblValueErisionF->TabIndex = 30;
			this->lblValueErisionF->Text = L"...";
			// 
			// lblValueDilationF
			// 
			this->lblValueDilationF->AutoSize = true;
			this->lblValueDilationF->Location = System::Drawing::Point(10, 354);
			this->lblValueDilationF->Name = L"lblValueDilationF";
			this->lblValueDilationF->Size = System::Drawing::Size(16, 13);
			this->lblValueDilationF->TabIndex = 29;
			this->lblValueDilationF->Text = L"...";
			// 
			// lblValueVF
			// 
			this->lblValueVF->AutoSize = true;
			this->lblValueVF->Location = System::Drawing::Point(8, 270);
			this->lblValueVF->Name = L"lblValueVF";
			this->lblValueVF->Size = System::Drawing::Size(16, 13);
			this->lblValueVF->TabIndex = 27;
			this->lblValueVF->Text = L"...";
			// 
			// lblValueSF
			// 
			this->lblValueSF->AutoSize = true;
			this->lblValueSF->Location = System::Drawing::Point(8, 179);
			this->lblValueSF->Name = L"lblValueSF";
			this->lblValueSF->Size = System::Drawing::Size(16, 13);
			this->lblValueSF->TabIndex = 28;
			this->lblValueSF->Text = L"...";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(10, 402);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(38, 13);
			this->label12->TabIndex = 26;
			this->label12->Text = L"Erision";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(10, 341);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(42, 13);
			this->label13->TabIndex = 25;
			this->label13->Text = L"Dilation";
			// 
			// barErisionF
			// 
			this->barErisionF->Location = System::Drawing::Point(52, 402);
			this->barErisionF->Maximum = 255;
			this->barErisionF->Name = L"barErisionF";
			this->barErisionF->Size = System::Drawing::Size(581, 45);
			this->barErisionF->TabIndex = 23;
			this->barErisionF->TickFrequency = 2;
			// 
			// barDilationF
			// 
			this->barDilationF->Location = System::Drawing::Point(52, 341);
			this->barDilationF->Maximum = 255;
			this->barDilationF->Name = L"barDilationF";
			this->barDilationF->Size = System::Drawing::Size(581, 45);
			this->barDilationF->TabIndex = 24;
			this->barDilationF->TickFrequency = 2;
			// 
			// barVmaxF
			// 
			this->barVmaxF->Location = System::Drawing::Point(52, 277);
			this->barVmaxF->Maximum = 255;
			this->barVmaxF->Name = L"barVmaxF";
			this->barVmaxF->Size = System::Drawing::Size(581, 45);
			this->barVmaxF->TabIndex = 21;
			this->barVmaxF->TickFrequency = 2;
			// 
			// barVminF
			// 
			this->barVminF->Location = System::Drawing::Point(52, 238);
			this->barVminF->Maximum = 255;
			this->barVminF->Name = L"barVminF";
			this->barVminF->Size = System::Drawing::Size(581, 45);
			this->barVminF->TabIndex = 22;
			this->barVminF->TickFrequency = 2;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(7, 241);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(14, 13);
			this->label14->TabIndex = 20;
			this->label14->Text = L"V";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(8, 154);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(14, 13);
			this->label15->TabIndex = 19;
			this->label15->Text = L"S";
			// 
			// barSmaxF
			// 
			this->barSmaxF->Location = System::Drawing::Point(52, 184);
			this->barSmaxF->Maximum = 255;
			this->barSmaxF->Name = L"barSmaxF";
			this->barSmaxF->Size = System::Drawing::Size(581, 45);
			this->barSmaxF->TabIndex = 17;
			this->barSmaxF->TickFrequency = 2;
			// 
			// barSminF
			// 
			this->barSminF->Location = System::Drawing::Point(52, 147);
			this->barSminF->Maximum = 255;
			this->barSminF->Name = L"barSminF";
			this->barSminF->Size = System::Drawing::Size(581, 45);
			this->barSminF->TabIndex = 18;
			this->barSminF->TickFrequency = 2;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(857, 558);
			this->Controls->Add(this->btnSaveSettings);
			this->Controls->Add(this->btnDeleteSettings);
			this->Controls->Add(this->btnResetBarValues);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->txtItemName);
			this->Controls->Add(this->cmbSettings);
			this->Controls->Add(this->BtnVizijaPause);
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
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barErisionR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barDilationR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barVmaxR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barVminR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barHmaxR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSmaxR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSminR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barHminR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barHmaxF))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barHminF))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barErisionF))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barDilationF))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barVmaxF))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barVminF))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSmaxF))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSminF))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		PrintMessage("MyForm_Load");	

		loadSettings();
	}

	void loadSettings()
	{
		cmbSettings->Items->Clear();
		for (int i = 0; i<10; i++)
		{
			string s = myOpenCV->settings.GetItem(i).name;
			System::String^ str3 = gcnew System::String(s.c_str());
			
			cmbSettings->Items->Add(str3);
		}
		cmbSettings->SelectedIndex = myOpenCV->settings.defaultSettingsItem;
		barsSet();
	}

	private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (cv_img != nullptr)
			cvReleaseImage(&cv_img);

			myOpenCV->doExit();
			PrintMessage("VizijaStop");
			
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

	MyOpenCV* myOpenCV=new MyOpenCV;

	

	private: System::Void BtnStartVizija_Click(System::Object^  sender, System::EventArgs^  e) {
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
		myOpenCV->VisionStop();
		PrintMessage("Vizija stopped");
	}


	private: void PrintMessage(System::String^ msg)	{
		TxtOutputMessages->Text += DateTime::Now.ToString("HH:mm:ss") + " ---> " + msg + "\r\n";
		TxtOutputMessages->SelectionStart = TxtOutputMessages->TextLength;
		TxtOutputMessages->ScrollToCaret();
	}

	private: System::Void BtnVizijaPause_Click(System::Object^  sender, System::EventArgs^  e) {
		myOpenCV->PauseToogle();
		PrintMessage("Pause/Resume clicked");
	}


	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

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

		void barsSet()
	{
			barHminF->Value = myOpenCV->settings.Bar1().H_MIN;
			barSminF->Value = myOpenCV->settings.Bar1().S_MIN;
			barVminF->Value = myOpenCV->settings.Bar1().V_MIN;

			barHmaxF->Value = myOpenCV->settings.Bar1().H_MAX;
			barSmaxF->Value = myOpenCV->settings.Bar1().S_MAX;
			barVmaxF->Value = myOpenCV->settings.Bar1().V_MAX;

			barDilationF->Value = myOpenCV->settings.Bar1().V_DILATION_SIZE;
			barErisionF->Value = myOpenCV->settings.Bar1().V_EROSION_SIZE;

			lblValueHF->Text = barHminF->Value.ToString() + ".." + barHmaxF->Value.ToString();
			lblValueSF->Text = barSminF->Value.ToString() + ".." + barSmaxF->Value.ToString();
			lblValueVF->Text = barVminF->Value.ToString() + ".." + barVmaxF->Value.ToString();

			lblValueDilationF->Text = barDilationF->Value.ToString();
			lblValueErisionF->Text = barErisionF->Value.ToString();




			barHminR->Value = myOpenCV->settings.Bar2().H_MIN;
			barSminR->Value = myOpenCV->settings.Bar2().S_MIN;
			barVminR->Value = myOpenCV->settings.Bar2().V_MIN;

			barHmaxR->Value = myOpenCV->settings.Bar2().H_MAX;
			barSmaxR->Value = myOpenCV->settings.Bar2().S_MAX;
			barVmaxR->Value = myOpenCV->settings.Bar2().V_MAX;

			barDilationR->Value = myOpenCV->settings.Bar2().V_DILATION_SIZE;
			barErisionR->Value = myOpenCV->settings.Bar2().V_EROSION_SIZE;

			lblValueHR->Text = barHminR->Value.ToString() + ".." + barHmaxR->Value.ToString();
			lblValueSR->Text = barSminR->Value.ToString() + ".." + barSmaxR->Value.ToString();
			lblValueVR->Text = barVminR->Value.ToString() + ".." + barVmaxR->Value.ToString();

			lblValueDilationR->Text = barDilationR->Value.ToString();
			lblValueErisionR->Text = barErisionR->Value.ToString();
	}

		void barsGet()
		{
			myOpenCV->settings.Bar2().H_MIN = barHminR->Value;
			myOpenCV->settings.Bar2().S_MIN = barSminR->Value;
			myOpenCV->settings.Bar2().V_MIN = barVminR->Value;
			
			myOpenCV->settings.Bar2().H_MAX = barHmaxR->Value;
			myOpenCV->settings.Bar2().S_MAX = barSmaxR->Value;
			myOpenCV->settings.Bar2().V_MAX = barVmaxR->Value;

			myOpenCV->settings.Bar2().V_DILATION_SIZE= barDilationR->Value;
			myOpenCV->settings.Bar2().V_EROSION_SIZE = barErisionR->Value;
			
			lblValueHR->Text = barHminR->Value.ToString() + ".." + barHmaxR->Value.ToString();
			lblValueSR->Text = barSminR->Value.ToString() + ".." + barSmaxR->Value.ToString();
			lblValueVR->Text = barVminR->Value.ToString() + ".." + barVmaxR->Value.ToString();
			
			lblValueDilationR->Text = barDilationR->Value.ToString() ;
			lblValueErisionR->Text = barErisionR->Value.ToString() ;




			myOpenCV->settings.Bar1().H_MIN = barHminF->Value;
			myOpenCV->settings.Bar1().S_MIN = barSminF->Value;
			myOpenCV->settings.Bar1().V_MIN = barVminF->Value;
			myOpenCV->settings.Bar1().H_MAX = barHmaxF->Value;
			myOpenCV->settings.Bar1().S_MAX = barSmaxF->Value;
			myOpenCV->settings.Bar1().V_MAX = barVmaxF->Value;
			myOpenCV->settings.Bar1().V_DILATION_SIZE = barDilationF->Value;
			myOpenCV->settings.Bar1().V_EROSION_SIZE = barErisionF->Value;

			lblValueHF->Text = barHminF->Value.ToString() + ".." + barHmaxF->Value.ToString();
			lblValueSF->Text = barSminF->Value.ToString() + ".." + barSmaxF->Value.ToString();
			lblValueVF->Text = barVminF->Value.ToString() + ".." + barVmaxF->Value.ToString();

			lblValueDilationF->Text = barDilationF->Value.ToString();
			lblValueErisionF->Text = barErisionF->Value.ToString();
		}


		void DoNavigation(int IDrobot, cv::Point currentPoint, int currentAngleOrientation, cv::Point todoTargetPoint) {

			int Dx = MyMath::DeltaX(currentPoint, todoTargetPoint);
			int Dy = MyMath::DeltaY(currentPoint, todoTargetPoint);
			int angleToDestination = MyMath::IzracunajUgao(Dx, Dy);
			popraviUgao(angleToDestination);
			popraviUgao(currentAngleOrientation);



			int angleDifference = angleToDestination - currentAngleOrientation;
			popraviUgao(angleDifference);
			//angleDifference += 360;
			//angleDifference %= 360;
			if (angleDifference > 0 && angleDifference < 170)
			{
				SendSerialCommand("R3" + "-120" + "-010");//IDrobot.ToString()
				PrintMessage("Idi lijevo za angleDifference = " + angleDifference.ToString());
				//lijevi ide 20
				//desni ide 5
			}
			else if (angleDifference > 190 && angleDifference < 360)
			{
				SendSerialCommand("R3" + "-010" + "-120");//IDrobot.ToString()
														  //lijevi ide 5
														  //desni ide 20
				PrintMessage("Idi desno za angleDifference = " + angleDifference.ToString());
			}
			else {
				//350 - 370
				SendSerialCommand("R3" + "-100" + "-100");//IDrobot.ToString()
														  //lijevi 10
														  //desni 10
				PrintMessage("Idi ravno");
			}

		}
private: System::Void timerForNavgation_Tick(System::Object^  sender, System::EventArgs^  e) {

	for (int i = 0; i < myOpenCV->robot_collector.Count(); i++)
	{
		Robot* robot = myOpenCV->robot_collector.GetRobotByIndex(i);
		auto queueTargets = robot->todoTargetPoints;
		if (queueTargets->isPrazan())
		{
			continue;
		}
		MotionStep* pozicija = robot->GetPozicijaNajnovijaFront();
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
private: System::Void cmbSettings_TextChanged(System::Object^  sender, System::EventArgs^  e) {

			int i = cmbSettings->SelectedIndex;
			myOpenCV->settings.defaultSettingsItem = i;
			char* s = myOpenCV->settings.GetItem(i).name;
			System::String^ ms = gcnew  System::String(s);
			txtItemName->Text = ms;
			barsSet();
	
		}




private: System::Void btnRefreshBarsRear_Click(System::Object^  sender, System::EventArgs^  e) {
	barsSet();
}

private: System::Void txtItemName_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	int i = cmbSettings->SelectedIndex;
			System::String^ s = txtItemName->Text->ToString();

			IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(s);
			char* nativeString = static_cast<char*>(ptrToNativeString.ToPointer());

strcpy_s(myOpenCV->settings.GetItem(i).name, nativeString);
}
private: System::Void barHminR_Scroll(System::Object^  sender, System::EventArgs^  e) {
	barsSet();
}
private: System::Void barHmaxR_Scroll(System::Object^  sender, System::EventArgs^  e) {
	barsSet();
}
private: System::Void barSminR_Scroll(System::Object^  sender, System::EventArgs^  e) {
	barsSet();
}
private: System::Void barSmaxR_Scroll(System::Object^  sender, System::EventArgs^  e) {
	barsSet();
}
private: System::Void barVminR_Scroll(System::Object^  sender, System::EventArgs^  e) {
	barsSet();
}
private: System::Void barVmaxR_Scroll(System::Object^  sender, System::EventArgs^  e) {
	barsSet();
}
private: System::Void barDilationR_Scroll(System::Object^  sender, System::EventArgs^  e) {
	barsSet();
}
private: System::Void barErisionR_Scroll(System::Object^  sender, System::EventArgs^  e) {
	barsSet();
}
private: System::Void btnSaveSettings_Click(System::Object^  sender, System::EventArgs^  e) {
	myOpenCV->writeSettingsFile();
}
private: System::Void btnDeleteSettings_Click(System::Object^  sender, System::EventArgs^  e) {
	myOpenCV->settings.ResetValues();
	loadSettings();
}
private: System::Void btnResetBarValues_Click(System::Object^  sender, System::EventArgs^  e) {
	loadSettings();
}

};
}
