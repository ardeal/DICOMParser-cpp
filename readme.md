
DICOMParser

+ The open source code was downloaded from: https://sourceforge.net/projects/dicomparser/. DICOMParser is a small, lightweight C++ toolkit for reading DICOM format medical image files. It builds on several platforms including Linux, AIX, HP-UX, IRIX, SunOS, Visual C++, Borland C++, and Cygwin. DICOMParser is used in VTK and ITK.
+ To compile lib:
    - on VS, DICOM_EXPORT_SYMBOLS;DICOM_DLL; macro are needed. 
    - on Linux, some small modification in code is needed to make sure strcmp could be correctly used. 
+ To compile exe on VS:
    - the mainloop.cpp file is needed.
    - the The following code is an example about how to use DICOMParser.

```C
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
```
































