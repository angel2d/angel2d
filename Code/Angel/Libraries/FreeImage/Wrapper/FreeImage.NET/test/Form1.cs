using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Runtime.InteropServices;

using FreeImageAPI;


namespace FI
{

	public class Form1 : System.Windows.Forms.Form
	{
		private UInt32 fi;

		private System.ComponentModel.Container components = null;

		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(624, 450);
			this.Name = "Form1";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}

		private void Form1_Load(object sender, System.EventArgs e)
		{
			string img = @"C:\Temp\kodim22.png";

			this.fi = FreeImage.Load(FREE_IMAGE_FORMAT.FIF_PNG, img, 0);
		}

		[DllImport("Gdi32.dll")]
		private static extern int SetStretchBltMode(IntPtr HDC, int iStretchMode);

		[DllImport("Gdi32.dll")]
		private static extern int StretchDIBits(
			IntPtr HDC,
			int XDest,                    // x-coord of destination upper-left corner
			int YDest,                    // y-coord of destination upper-left corner
			int nDestWidth,               // width of destination rectangle
			int nDestHeight,              // height of destination rectangle
			int XSrc,                     // x-coord of source upper-left corner
			int YSrc,                     // y-coord of source upper-left corner
			int nSrcWidth,                // width of source rectangle
			int nSrcHeight,               // height of source rectangle
			IntPtr lpBits,								// bitmap bits
			BITMAPINFO lpBitsInfo,				// bitmap data
			uint iUsage,                  // usage options
			int dwRop											// raster operation code
			);


		private void Form1_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
		{
			IntPtr hdc = e.Graphics.GetHdc();

			int r = SetStretchBltMode(hdc, 3 /* COLORONCOLOR */);
			r = StretchDIBits(hdc,
				0, 0, this.ClientSize.Width, this.ClientSize.Height,
				0, 0, (int)FreeImage.GetWidth(this.fi), (int)FreeImage.GetHeight(this.fi),
				FreeImage.GetBits(this.fi),
				FreeImage.GetInfo(this.fi),
				0 /* DIB_RGB_COLORS */, 0x00CC0020 /* SRCCOPY */);

			e.Graphics.ReleaseHdc(hdc);
		}
	}

}