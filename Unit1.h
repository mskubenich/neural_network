//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TButton *Learn;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *Edit1;
	TScrollBox *ScrollBox1;
	TEdit *Edit2;
	TButton *Button2;
	TGroupBox *GroupBox2;
	TScrollBox *ScrollBox2;
	TImage *Image1;
	TGroupBox *GroupBox3;
	TMemo *Memo2;
	TButton *Button1;
	TButton *Button3;
	TGroupBox *GroupBox4;
	TButton *Button4;
	TGroupBox *GroupBox5;
	TButton *Button5;
	TSaveDialog *SaveDialog1;
	TButton *Button6;
	TOpenDialog *OpenDialog1;
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall LearnClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
