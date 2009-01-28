// ==========================================================
// FreeImage.NET 3
//
// Design and implementation by
// - David Boland (davidboland@vodafone.ie)
//
// This file is part of FreeImage 3
//
// COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
// THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
// OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
// CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
// THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
// SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
// PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
// THIS DISCLAIMER.
//
// Use at your own risk!
// ==========================================================

using System;
using System.IO;
using FreeImageAPI;
using System.Runtime.InteropServices;

class FreeImageTest
{
	public static void Main(string[] args)
	{
		FreeImageTest test = new FreeImageTest();
		test.Run();
	}
	
	
	public FreeImageTest()
	{
	}
	
	protected void Run()
	{
		Console.WriteLine("Load");
		int image = FreeImage.FreeImage_Load(FIF.FIF_PPM, @"C:\FreeImage.ppm", 0);
		
		Console.WriteLine("GetColorsUsed " + FreeImage.FreeImage_GetColorsUsed(image).ToString());		
		
		Console.WriteLine("GetBits " + FreeImage.FreeImage_GetBits(image).ToString());
		
		Console.WriteLine("GetScanLine " + FreeImage.FreeImage_GetScanLine(image, 0).ToString());

		Console.WriteLine("GetBPP " + FreeImage.FreeImage_GetBPP(image).ToString());
		
		Console.WriteLine("GetWidth " + FreeImage.FreeImage_GetWidth(image).ToString());

		Console.WriteLine("GetHeight " + FreeImage.FreeImage_GetHeight(image).ToString());

		Console.WriteLine("GetLine " + FreeImage.FreeImage_GetLine(image).ToString());
		
		Console.WriteLine("GetPitch " + FreeImage.FreeImage_GetPitch(image).ToString());
		
		Console.WriteLine("GetDIBSize " + FreeImage.FreeImage_GetDIBSize(image).ToString());

		Console.WriteLine("GetPalette");
		RGBQUAD rgbQuad = FreeImage.FreeImage_GetPalette(image);
		if(rgbQuad!=null)
		{
			Console.WriteLine("    blue=" + rgbQuad.rgbBlue.ToString());
			Console.WriteLine("    green=" + rgbQuad.rgbGreen.ToString());
			Console.WriteLine("    red=" + rgbQuad.rgbRed.ToString());
		}
		else
		{
			Console.WriteLine("    returned null.");			
		}

		Console.WriteLine("GetDotsPerMeterX " + FreeImage.FreeImage_GetDotsPerMeterX(image).ToString());
		
		Console.WriteLine("GetDotsPerMeterY " + FreeImage.FreeImage_GetDotsPerMeterY(image).ToString());
		
		BITMAPINFOHEADER header = FreeImage.FreeImage_GetInfoHeader(image);
		Console.WriteLine("GetInfoHeader");
		Console.WriteLine("    size=" + header.size.ToString());
		Console.WriteLine("    width=" + header.width.ToString()); 
		Console.WriteLine("    height=" + header.height.ToString()); 
		Console.WriteLine("    biPlanes=" + header.biPlanes.ToString()); 
		Console.WriteLine("    biBitCount=" + header.biBitCount.ToString());
		Console.WriteLine("    biCompression=" + header.biCompression.ToString()); 
		Console.WriteLine("    biSizeImage=" + header.biSizeImage.ToString()); 
		Console.WriteLine("    biXPelsPerMeter=" + header.biXPelsPerMeter.ToString()); 
		Console.WriteLine("    biYPelsPerMeter=" + header.biYPelsPerMeter.ToString()); 
		Console.WriteLine("    biClrUsed=" + header.biClrUsed.ToString()); 
		Console.WriteLine("    biClrImportant=" + header.biClrImportant.ToString());
		

		BITMAPINFO info = FreeImage.FreeImage_GetInfo(image);
		Console.WriteLine("GetInfo");
		Console.WriteLine("    InfoHeader");
		Console.WriteLine("        size=" + info.bmiHeader.size.ToString());
		Console.WriteLine("        width=" + info.bmiHeader.width.ToString()); 
		Console.WriteLine("        height=" + info.bmiHeader.height.ToString()); 
		Console.WriteLine("        biPlanes=" + info.bmiHeader.biPlanes.ToString()); 
		Console.WriteLine("        biBitCount=" + info.bmiHeader.biBitCount.ToString());
		Console.WriteLine("        biCompression=" + info.bmiHeader.biCompression.ToString()); 
		Console.WriteLine("        biSizeImage=" + info.bmiHeader.biSizeImage.ToString()); 
		Console.WriteLine("        biXPelsPerMeter=" + info.bmiHeader.biXPelsPerMeter.ToString()); 
		Console.WriteLine("        biYPelsPerMeter=" + info.bmiHeader.biYPelsPerMeter.ToString()); 
		Console.WriteLine("        biClrUsed=" + info.bmiHeader.biClrUsed.ToString()); 
		Console.WriteLine("        biClrImportant=" + info.bmiHeader.biClrImportant.ToString());
		Console.WriteLine("    Palette");
		Console.WriteLine("        blue=" + info.bmiColors.rgbBlue.ToString());
		Console.WriteLine("        green=" + info.bmiColors.rgbGreen.ToString());
		Console.WriteLine("        red=" + info.bmiColors.rgbRed.ToString());
		
		
		Console.WriteLine("GetColorType " + FreeImage.FreeImage_GetColorType(image).ToString());

		Console.WriteLine("GetRedMask " + FreeImage.FreeImage_GetRedMask(image).ToString());

		Console.WriteLine("GetGreenMask " + FreeImage.FreeImage_GetGreenMask(image).ToString());

		Console.WriteLine("GetBlueMask " + FreeImage.FreeImage_GetBlueMask(image).ToString());

		Console.WriteLine("GetTransparencyCount " + FreeImage.FreeImage_GetTransparencyCount(image).ToString());

		Console.WriteLine("GetTransparencyTable " + FreeImage.FreeImage_GetTransparencyTable(image).ToString());

		Console.WriteLine("SetTransparent");
		FreeImage.FreeImage_SetTransparent(image, true);

		Console.WriteLine("IsTransparent " + FreeImage.FreeImage_IsTransparent(image).ToString());

		Console.WriteLine("Unload");
		
		Console.WriteLine("GetFileType " + FreeImage.FreeImage_GetFileType(@"c:\FreeImage.ppm", 0).ToString());
		
		
		Console.WriteLine("ConvertTo8Bits");
		FreeImage.FreeImage_ConvertTo8Bits(image);
		
		Console.WriteLine("ConvertTo16Bits555");
		FreeImage.FreeImage_ConvertTo16Bits555(image);
		
		Console.WriteLine("ConvertTo16Bits565");
		FreeImage.FreeImage_ConvertTo16Bits565(image);
		
		Console.WriteLine("ConvertTo24Bits");
		FreeImage.FreeImage_ConvertTo24Bits(image);
		
		Console.WriteLine("ConvertTo32Bits");
		FreeImage.FreeImage_ConvertTo32Bits(image);
		
		Console.WriteLine("ColorQuantize");
		FreeImage.FreeImage_ColorQuantize(image, FI_QUANTIZE.FIQ_WUQUANT);
		
		byte[] rawBytes = new byte[] {0,1,0,1,1,1,0};
		Console.WriteLine("ConvertFromRawBits");
		FreeImage.FreeImage_ConvertFromRawBits(rawBytes, 16, 16, 1, 1, 1, 1, 1, false);
		
		Console.WriteLine("ConvertToRawBits");
		IntPtr lpBits = IntPtr.Zero;
		FreeImage.FreeImage_ConvertToRawBits(lpBits, image, 1, 1, 1, 1, 1, false);

		Console.WriteLine("GetFIFCount " + FreeImage.FreeImage_GetFIFCount().ToString());

		Console.WriteLine("SetPluginEnabled");
		FreeImage.FreeImage_SetPluginEnabled(FIF.FIF_CUT, false);

		Console.WriteLine("IsPluginEnabled " + FreeImage.FreeImage_IsPluginEnabled(FIF.FIF_PPM).ToString());

		Console.WriteLine("GetFromatFromFIF");
		string fifFormat = FreeImage.FreeImage_GetFormatFromFIF(FIF.FIF_PPM);
		Console.WriteLine("    " + fifFormat);
		
		Console.WriteLine("GetFIFFromFormat " + FreeImage.FreeImage_GetFIFFromFormat(fifFormat).ToString());

		Console.WriteLine("GetFIFFromMime " + FreeImage.FreeImage_GetFIFFromMime(fifFormat).ToString());

		Console.WriteLine("GetFIFExtensionList " + FreeImage.FreeImage_GetFIFExtensionList(FIF.FIF_PPM));
		
		Console.WriteLine("GetFIFDescription " + FreeImage.FreeImage_GetFIFDescription(FIF.FIF_PPM));

		Console.WriteLine("GetFIFRegExpr " + FreeImage.FreeImage_GetFIFRegExpr(FIF.FIF_PPM));
		
		Console.WriteLine("GetFIFFromFilename " + FreeImage.FreeImage_GetFIFFromFilename(@"c:\FreeImage.ppm").ToString());

		Console.WriteLine("FIFSupportsReading " + FreeImage.FreeImage_FIFSupportsReading(FIF.FIF_PPM).ToString());
		
		Console.WriteLine("FIFSupportsWriting " + FreeImage.FreeImage_FIFSupportsWriting(FIF.FIF_PPM).ToString());

		Console.WriteLine("FIFSupportsExportBPP " + FreeImage.FreeImage_FIFSupportsExportBPP(FIF.FIF_PPM, 0).ToString());


		/*Console.WriteLine("OpenMultiBitmap");
		int multiImage = FreeImage.FreeImage_OpenMultiBitmap(FIF.FIF_ICO, @"c:\FreeImage.ico", true, false, true);
		
		Console.WriteLine("GetPageCount " + FreeImage.FreeImage_GetPageCount(multiImage).ToString());
		
		Console.WriteLine("AppendPage");
		FreeImage.FreeImage_AppendPage(multiImage, image);
		
		Console.WriteLine("InsertPage");
		FreeImage.FreeImage_InsertPage(multiImage, 0, image);
		
		Console.WriteLine("GetPageCount " + FreeImage.FreeImage_GetPageCount(multiImage).ToString());

		Console.WriteLine("LockPage");
		FreeImage.FreeImage_LockPage(multiImage, 1);
		
		Console.WriteLine("GetLockedPageNumbers");
		IntPtr pages = IntPtr.Zero;
		IntPtr count = IntPtr.Zero;
		FreeImage.FreeImage_GetLockedPageNumbers(multiImage, pages, count);

		Console.WriteLine("UnlockPage");
		FreeImage.FreeImage_UnlockPage(multiImage, 0, false);
		
		Console.WriteLine("MovePage");
		FreeImage.FreeImage_MovePage(multiImage, 1, 0);
		
		Console.WriteLine("DeletePage");
		FreeImage.FreeImage_DeletePage(multiImage, 0);
		
		int flags = 0;
		Console.WriteLine("CloseMultiBitmap " + FreeImage.FreeImage_CloseMultiBitmap(multiImage, flags).ToString());

		Console.WriteLine("RotateClassic");
		FreeImage.FreeImage_RotateClassic(image, 0.50);
		
		Console.WriteLine("RotateEx");
		FreeImage.FreeImage_RotateEx(image, 0.50, 0.50, 0.50, 0.50, 0.50, 0);

		Console.WriteLine("FlipHorizontal");
		FreeImage.FreeImage_FlipHorizontal(image);
		
		Console.WriteLine("FlipVertical");
		FreeImage.FreeImage_FlipVertical(image);
		
		Console.WriteLine("Rescale");
		FreeImage.FreeImage_Rescale(image, 10, 10, FI_FILTER.FILTER_BOX);
				
		Console.WriteLine("AdjustCurve");
		byte[] lut = new byte[256];
		FreeImage.FreeImage_AdjustCurve(image, lut, FI_COLOR_CHANNEL.FICC_BLACK);
		
		Console.WriteLine("AdjustGamma");
		FreeImage.FreeImage_AdjustGamma(image, 0.50);
		
		Console.WriteLine("AdjustBrightness");
		FreeImage.FreeImage_AdjustBrightness(image, 0.50);
		
		Console.WriteLine("AdjustContrast");
		FreeImage.FreeImage_AdjustContrast(image, 0.50);
		
		Console.WriteLine("Invert");
		FreeImage.FreeImage_Invert(image);
		
		Console.WriteLine("GetHistogram");
		int histo = 0;
		FreeImage.FreeImage_GetHistogram(image, histo, FI_COLOR_CHANNEL.FICC_BLACK);
		
		Console.WriteLine("GetChannel");
		FreeImage.FreeImage_GetChannel(image, FI_COLOR_CHANNEL.FICC_BLACK);
		
		Console.WriteLine("SetChannel");
		int dib8 = FreeImage.FreeImage_ConvertTo8Bits(image);
		FreeImage.FreeImage_SetChannel(image, dib8, FI_COLOR_CHANNEL.FICC_BLACK);
				
		Console.WriteLine("Copy");
		int src = FreeImage.FreeImage_Copy(image, 0, 0, 2, 2);

		Console.WriteLine("Paste");
		FreeImage.FreeImage_Paste(image, src, 0, 0, 100);
*/
		Console.WriteLine("Save");
		FreeImage.FreeImage_Save(FIF.FIF_BMP, image, @"C:\FreeImage.bmp", 0);
		
		Console.WriteLine("Unload");
		FreeImage.FreeImage_Unload(image);
	}
}
