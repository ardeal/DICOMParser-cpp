/*=========================================================================

  Program:   DICOMParser
  Module:    $RCSfile: DICOMFile.h,v $
  Language:  C++
  Date:      $Date: 2003/10/23 19:13:34 $
  Version:   $Revision: 1.1.1.1 $

  Copyright (c) 2003 Matt Turek
  All rights reserved.
  See Copyright.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __DICOMFILE_H_
#define __DICOMFILE_H_

#ifdef _MSC_VER
#pragma warning ( disable : 4514 )
#pragma warning ( push, 3 )
#endif 

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "DICOMTypes.h"
#include "DICOMConfig.h"

//
// Abstraction of a file used by the DICOMParser.
// This should probably be cleaned up so that it
// can be used to abstract a stream.
//
class DICOM_EXPORT DICOMFile 
{
 public:
  DICOMFile();
  virtual ~DICOMFile();
  
  //
  // Open a file with filename.  Returns a bool
  // that is true if the file is successfully
  // opened.
  //
  bool Open(const dicom_stl::string& filename);
  
  //
  // Close a file.
  //
  void Close();
  
  //
  // Return the position in the file.
  //
  long Tell();
  
  // 
  // Move to a particular position in the file.
  //
  void SkipToPos(long);
  
  //
  // Return the size of the file.
  //
  long GetSize();
  
  //
  // Skip a number of bytes.
  // 
  void Skip(long);
  
  //
  // Skip to the beginning of the file.
  //
  void SkipToStart();
  
  //
  // Read data of length len.
  //
  void Read(void* data, long len);
  
  //
  // Read a double byte of data.
  //
  doublebyte ReadDoubleByte();

  
  doublebyte ReadDoubleByteAsLittleEndian();

  //
  // Read a quadbyte of data.
  //
  quadbyte   ReadQuadByte();
  
  //
  // Read nbytes of data up to 4 bytes.
  //
  quadbyte   ReadNBytes(int len);
  
  // 
  // Read a float an ascii.
  //
  float      ReadAsciiFloat(int len);
  
  //
  // Read an int as ascii.
  //
  int        ReadAsciiInt(int len);
  
  //
  // Read an array of ascii characters.
  //
  char*      ReadAsciiCharArray(int len);
  
  //
  // Convert the data to signed long.
  //
  static long ReturnAsSignedLong(unsigned char* data, bool )
  {
    unsigned char* data2 = data;
    return *((quadbyte*) data2);
  }
  
  
  //
  // Convert the data to unsigned long.
  //
  static ulong ReturnAsUnsignedLong(unsigned char* data, bool )
  {
    unsigned char* data2 = data;
    return *((ulong*) data2);
  }
  
  //
  // Convert data to unsigned short.
  //
  static ushort ReturnAsUnsignedShort(unsigned char* data, bool )
  {
    unsigned char* data2 = data;
    return *((doublebyte*)data2);
  }
  
  //
  // Convert data to signed short.
  // 
  static short int ReturnAsSignedShort(unsigned char* data, bool )
  {
    unsigned char* data2 = data;
    return *((short int*)data2);
  }

  //
  // Convert data to int.
  //
  static int ReturnAsInteger(unsigned char* data, bool)
  {
    return static_cast<int> (atoi((const char*) data));
  }
  
  static float ReturnAsFloat(unsigned char* data, bool)
    {
    return static_cast<float> (atof((const char*) data));
    }

  bool GetPlatformIsBigEndian()
    {
    return PlatformIsBigEndian;
    }

  void SetPlatformIsBigEndian(bool v)
    {
    this->PlatformIsBigEndian = v;
    }

  //
  // Swap the bytes in an array of unsigned shorts.
  //
  static void swapShorts(ushort *ip, ushort *op, int count)
  {
    while (count)
      {
      *op++ = swapShort(*ip++);
      count--;
      }
  }
  
  //
  // Swap the bytes in an array of unsigned longs.
  //
  static void swapLongs(ulong *ip, ulong *op, int count)
  {
    while (count)
      {
      *op++ = swapLong(*ip++);
      count--;
      }
  }
  
  
  //
  // Swap the bytes in an unsigned short.
  //
  static ushort swapShort(ushort v)
  {
    return ushort((v << 8)
      | (v >> 8));
  }
  
  // 
  // Swap the bytes in an unsigned long.
  //
  static ulong swapLong(ulong v)
    {
    return ulong((v << 24) 
      | (v << 8) & 0x00ff0000
      | (v >> 8) & 0x0000ff00
      | (v >> 24));
    }

 const char* GetPlatformEndian() {return this->PlatformEndian;}

 protected:
  //
  // Internal storage for the filename.
  //
  // char* Filename;
  
  //
  // Internal storage for the file pointer.
  //
  // FILE* Fptr;
  
  dicom_stream::ifstream InputStream;
  
  //
  // Flag for swaping bytes.
  //
  bool PlatformIsBigEndian;

  //
  // Platform endianness
  //
  const char* PlatformEndian;

 private:
  DICOMFile(const DICOMFile&);
  void operator=(const DICOMFile&);  

};

#ifdef _MSC_VER
#pragma warning ( pop )
#endif

#endif // __DICOMFILE_H_


