#include <iostream>
#include "MyForm.h"

#include<opencv2/opencv.hpp>
#include "opencv\highgui.h"
#include "opencv\cv.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^ args)
{
	
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	CLRSample::MyForm form;
	Application::Run(%form);
}