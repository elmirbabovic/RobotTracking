#pragma once
#include <datetimeapi.h>
#include <string>
#include <core/cvstd.hpp>
#include "common.h"		//		IplImage * cv_img;


std::string MarshalToStdString(System::String^ s)
{
	using namespace System::Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	std::string os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
	return os;
}
