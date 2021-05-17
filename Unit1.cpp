//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include <math.hpp>
#include <jpeg.hpp>
#include <graphics.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
float a, b, c, x, y, imw, imh, imw2, imh2;
int i;
boolean indgrid = false;
TLabel *Lab1[5], *Lab2[5];
AnsiString fname;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
  Image1->Canvas->Brush->Color = clWhite;
  Image1->Canvas->Pen->Color = clBlack;
  imw = Image1->Width;
  imh = Image1->Height;
  Image1->Canvas->Rectangle(0, 0, imw, imh);
  Image2->Canvas->Brush->Color = clWhite;
  Image2->Canvas->Pen->Color = clBlack;
  imw2 = Image2->Width;
  imh2 = Image2->Height;
  Image2->Canvas->Rectangle(0, 0, imw2, imh2);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  Button2Click(Button2);
  Button3Click(Button3);
  Image1->Canvas->Pen->Color = (TColor)RGB(255, 0, 0);
  Image1->Canvas->Pen->Width = 2;
  x = 1e-6;
  switch (ComboBox1->ItemIndex) {
  case 0:
	Image1->Canvas->MoveTo(0, 0);
	while (x < imw) {
		y = imh / 2 * sin(x / 10) / (x / 10);
		Image1->Canvas->LineTo(x, imh / 2 - y);
		x++;
	}
	break;
  case 1:
	Image1->Canvas->MoveTo(x, -0.03 * imh / 2 * cos(x / 10) * (x / 10) + imh / 2);
	while (x < imw) {
		y = 0.03 * imh / 2 * cos(x / 10) * (x / 10);
		Image1->Canvas->LineTo(x, imh / 2 - y);
		x++;
	}
	break;
  default: ;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  Image1->Canvas->FillRect(Rect(0, 0, imw, imh));
  Image1->Canvas->Pen->Color = clBlack;
  Image1->Canvas->Pen->Width = 1;
  Image1->Canvas->Rectangle(0, 0, imw, imh);
  indgrid = !indgrid;
  Button3Click(Button3);
  if (Lab1[0] != 0) {
	for (i = 0; i < 5; i++) {
	  Lab1[i]->Caption = "";
	  Lab2[i]->Caption = "";
	}

  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
  float dx, dy;
  dx = imw / 4;
  dy = imh / 4;
  Image1->Canvas->Pen->Width = 1;
  if (indgrid)
	Image1->Canvas->Pen->Color = clBlack;
  else
	Image1->Canvas->Pen->Color = clWhite;
  indgrid = !indgrid;
  for (i = 1; i < 4; i++) {
	x = 0;
	y = dy * i;
	Image1->Canvas->MoveTo(1, y);
	Image1->Canvas->LineTo(imw, y);
  }
  for (i = 1; i < 4; i++) {
	  y = 1;
	  x = dx * i;
	  Image1->Canvas->MoveTo(x, y);
      Image1->Canvas->LineTo(x, imh);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
  for(i = 0; i < 5; i++){
	Lab1[i] = new TLabel(Form1);
	Lab1[i]->Parent = Form1;
	Lab1[i]->Top = Image1->Top + imh + 5;
	Lab1[i]->Left = Image1->Left + imw / 4 * i -10;
	Lab1[i]->Alignment = taCenter;
	Lab1[i]->Caption = FloatToStrF(imw / 4 * i / 10, ffFixed, 5, 1);
  }
  for (i = 0; i < 5; i++) {
	Lab2[i] = new TLabel(Form1);
	Lab2[i]->Parent = Form1;
	Lab2[i]->Top = Image1->Top + imh - 8 - imh / 4 * i;
	Lab2[i]->Left = Image1->Left - 25;
	Lab2[i]->Caption = FloatToStrF(2. / 4 * i, ffFixed, 5, 1);
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button5Click(TObject *Sender)
{
  if (OpenPictureDialog1->Execute()) {
	  fname = OpenPictureDialog1->FileName;
	  Image2->Picture->LoadFromFile(fname);
      Image2->Proportional = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
  Image2->Picture->Bitmap->FreeImage();
  Image2->Canvas->Brush->Color = clWhite;
  Image2->Canvas->Pen->Color = clBlack;
  Image2->Picture->Graphic->SetSize(imw2, imh2);
  Image2->Canvas->Rectangle(0, 0, imw2, imh2);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender){
  Button1Click(Button1);
}
void __fastcall TForm1::N3Click(TObject *Sender){
  Button2Click(Button2);
}
void __fastcall TForm1::N4Click(TObject *Sender){
  Button3Click(Button3);
}
void __fastcall TForm1::N5Click(TObject *Sender){
  Button4Click(Button4);
}
void __fastcall TForm1::N7Click(TObject *Sender){
  Button5Click(Button5);
}
void __fastcall TForm1::N8Click(TObject *Sender){
  Button6Click(Button6);
}
