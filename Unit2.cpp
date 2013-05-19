//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

using namespace std;

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
TMemo *logMemo;
float n_of_needed_symvols = 99;

int key_down_time, key_up_time, last_key_up_time = 0, counter = 0;  // 999%3=0
int *learn_data_array;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner, TMemo *memo, int* array)
	: TForm(Owner)
{
	logMemo = memo;
	learn_data_array = array;
	counter = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Memo1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(counter > n_of_needed_symvols-4){
		ShowMessage("Ви ввели достатньо даних для навчання");
		while(counter < n_of_needed_symvols){
			learn_data_array[counter] = 0;
			counter++;
		}
		return;
	}
	key_up_time = GetTickCount();
	logMemo->Lines->Add("Time shift between keys: " + AnsiString(key_up_time - last_key_up_time));
	learn_data_array[counter] = key_up_time - last_key_up_time;
	counter++;
	last_key_up_time = key_up_time;
	logMemo->Lines->Add("Time shift between down and up: " + AnsiString(key_up_time - key_down_time));
	logMemo->Lines->Add("key id: " + AnsiString(Key));
	learn_data_array[counter] = key_up_time - last_key_up_time;
	counter++;
	learn_data_array[counter] = Key;
	counter++;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Memo1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	key_down_time = GetTickCount();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
		while(counter < n_of_needed_symvols){
			learn_data_array[counter] = 0;
			counter++;
		}
}
//---------------------------------------------------------------------------

