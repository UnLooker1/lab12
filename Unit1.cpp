//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GLBaseClasses"
#pragma link "GLCadencer"
#pragma link "GLCoordinates"
#pragma link "GLCrossPlatform"
#pragma link "GLGeomObjects"
#pragma link "GLObjects"
#pragma link "GLScene"
#pragma link "GLVectorFileObjects"
#pragma link "GLWin32Viewer"
#pragma link "GLFile3DS"

#pragma resource "*.dfm"
TForm1 *Form1;

const float
  cSpread = 90.00;
const int
  cNbMushrooms = 10;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  SetGLSceneMediaDir();
  FreeForm1->LoadFromFile("mushroom.3ds");
  Disk1->Material->Texture->Image->LoadFromFile("clover.jpg");
  AddMushRooms();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AddMushRooms()
{
   int i;
   TGLProxyObject *proxy;
   Glvectorgeometry::TVector s;
   float f;

   for (i=0; i < cNbMushrooms-1; i++)
   {
	 proxy  = (TGLProxyObject *)(DummyCube1->AddNewChild(__classid(TGLProxyObject)));
	 proxy->MasterObject = FreeForm1;
	 proxy->ProxyOptions = proxy->ProxyOptions << pooObjects;
	 proxy->Direction = FreeForm1->Direction;
	 proxy->Up = FreeForm1->Up;
	 s = FreeForm1->Scale->AsVector;
	 f = (Random()+0.2);
	 ScaleVector(s, 5*f);
	 proxy->Scale->AsVector = s;
	 proxy->Position->SetPoint(Random(cSpread)-(cSpread/2),
					   f*FreeForm1->Position->Y,
					   Random(cSpread)-(cSpread/2));
	 proxy->RollAngle = Random(360);
	 proxy->PitchAngle = -90;
   }
   MushRoomCounter = MushRoomCounter + cNbMushrooms;
}


void __fastcall TForm1::GLSceneViewer1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   mx = X; my = Y;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GLSceneViewer1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
   if (Shift.Contains(ssLeft))
   {
	  GLCamera1->MoveAroundTarget(my-Y, mx-X);
	  mx = X; my = Y;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   AddMushRooms();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
   Caption = Format("Mushroom Counter : %d (%.1f FPS)",
			 ARRAYOFCONST (( MushRoomCounter, GLSceneViewer1->FramesPerSecond())));
   GLSceneViewer1->ResetPerformanceMonitor();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
   GLCamera1->FocalLength = GLSceneViewer1->Width/8;
   Button1->Left = (Width-Button1->Width)/2;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::GLCadencer1Progress(TObject *Sender, const double deltaTime,
          const double newTime)
{
   GLSceneViewer1->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::About1Click(TObject *Sender)
{
    Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Help1Click(TObject *Sender)
{
	Form3->Show();
}
//---------------------------------------------------------------------------

