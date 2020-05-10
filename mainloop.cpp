#include <stdio.h>
#include <stdlib.h>
#include "DICOMParser.h"
//#include "DICOMAppHelper.h"
#include "DICOMAppHelper.h"
int read_dicom();

int main(int argc, char ** argv)
{
	read_dicom();

	return 1;
}

int read_dicom()
{
	DICOMAppHelper AppHelper;
	DICOMParser Parser;

	const std::string FileName = "0006.dcm";

	Parser.ClearAllDICOMTagCallbacks();
	Parser.OpenFile(FileName);
	AppHelper.Clear();
	AppHelper.RegisterCallbacks(&Parser);
	AppHelper.RegisterPixelDataCallback(&Parser);
		
	Parser.ReadHeader();

	void* imgData = nullptr;
	DICOMParser::VRTypes dataType;
	unsigned long imageDataLength;

	AppHelper.GetImageData(imgData, dataType, imageDataLength);
	if (!imageDataLength)
	{
		printf("XXXXXXXXXXXXXX\n");
		return -1;
	}

	short aa = *((short *)imgData); // the image data from dcm file

	return 1;
}




