//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include "NeuralNetwork.h"
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int n_of_layers = 0;
int* neurons_in_layer;
int *learn_data_array = new int[999];

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LearnClick(TObject *Sender){

bool flag = true;

 if (Edit1->Text == "" || Edit1->Text == "0") {
   flag = false;
 }
 for(int i=0; i<n_of_layers;i++){
   if (((TEdit*)ScrollBox1->FindComponent("EditT"+String(i)))->Text == "" || StrToInt(((TEdit*)ScrollBox1->FindComponent("EditT"+String(i)))->Text) == 0){
	 flag = false;
   }
 }

if (!flag) {
	ShowMessage("Значення не можуть бути нульовими!!!");
	return;
}

	AnsiString array_string = AnsiString("");
	for(int i = 0; i < 999; i++){
		array_string += learn_data_array[i];
		array_string += "   ";
	}
	//Memo1->Lines->Add(array_string);

	NeuralNetwork* net = new NeuralNetwork(neurons_in_layer, n_of_layers);

	int package_count = ceil(999.0/net->getNumberOfNeuronsInLayer(0));
	int **packages = new int*[package_count];
	for (int i = 0; i < package_count; i++) {
		packages[i] = new int[net->getNumberOfNeuronsInLayer(0)];
	}
	for(int i = 0; i < package_count; i++){
		AnsiString package_string = AnsiString("");
		for(int j = 0; j < net->getNumberOfNeuronsInLayer(0); j++){
			int index = j + i*net->getNumberOfNeuronsInLayer(0);
			if(index < 999){ 
				package_string += learn_data_array[index];
				packages[i][j] = learn_data_array[index];
			}else{
				package_string += AnsiString("0");
				packages[i][j] = 0;
			}
			package_string += "   ";
		}
		Memo1->Lines->Add("Package# " + AnsiString(i) + ": " + package_string);
	}
	Memo1->Lines->Add("number of layers: " + AnsiString(net->getNumberOfLayers()));
	for(int i = 0 ; i < net->getNumberOfLayers(); i++){
		Memo1->Lines->Add("number of neurons in layer #" + AnsiString(i)+": " + AnsiString(net->getNumberOfNeuronsInLayer(i)));
	}
	
	int package_counter = 0;
	for (int i = 0; i < 10; i++) {
		if(package_counter == package_count){
			package_counter = 0;
		}
		Memo1->Lines->Add("-------------------------------");
		Memo1->Lines->Add("learn epoch #"+AnsiString(i));
		net->LearnEpoch(packages[package_counter], 1, Memo1);

		Memo2->Lines->Clear();
		for(int j = 1; j < net->getNumberOfLayers(); j++){
			Memo2->Lines->Add("Weight matrix between layers #"+AnsiString(j-1)+
			" and #"+AnsiString(j));
			Memo2->Lines->Add("");
			for(int k = 0; k < net->getNumberOfNeuronsInLayer(j-1); k++){
				AnsiString row = "";
				for( int z = 0; z < net->getNumberOfNeuronsInLayer(j); z++){
					AnsiString str;
					double x = floor((net->getNeuron(j, z)->getWeight(k))*1000)/1000;

					row += "   " + AnsiString(x);
				}
				Memo2->Lines->Add(row);
			}
			Memo2->Lines->Add("");
		}
		package_counter++;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edit1Change(TObject *Sender)
{

if((Edit1->Text!="") && (StrToInt(Edit1->Text)>10)){
  Edit1->Text = "10";
}
if (Edit1->Text!="") {
  Edit1->Text = IntToStr(StrToInt(Edit1->Text));
}
for(int i=0;i<n_of_layers;i++){
  delete (TLabel*)ScrollBox1->FindComponent("LabelT"+String(i));
  delete (TEdit*)ScrollBox1->FindComponent("EditT"+String(i));
}

if (Edit1->Text == "") {
  n_of_layers = 0;
}else{
  n_of_layers = StrToInt(Edit1->Text);
}

for(int i=0;i<n_of_layers;i++){
		TLabel* l = new TLabel(ScrollBox1);
		l->Caption = "Кількість нейронів шару №"+String(i);
		l->Parent = ScrollBox1;
		l->Name = "LabelT"+String(i);
		l->Left = 5;
		l->Top = i*20;
		l->Visible = true;
		TEdit* e = new TEdit(ScrollBox1);
		e->Text = "0";
		e->Parent = ScrollBox1;
		e->Name = "EditT"+String(i);
		e->Left = 160;
		e->Top = i*20;
		e->Visible = true;
		e->Width = 40;
		e->OnKeyPress = Edit1->OnKeyPress;
		e->OnChange = Edit2->OnChange;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
	if ((Key >= '0') && (Key <= '9')) {
	}else if (Key == 8) {
	}else{
	  Key=0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
 Image1->Picture = NULL;
 bool flag = true;
 if (Edit1->Text == "" || Edit1->Text == "0") {
   flag = false;
 }
 for(int i=0; i<n_of_layers;i++){
   if (((TEdit*)ScrollBox1->FindComponent("EditT"+String(i)))->Text == "" || StrToInt(((TEdit*)ScrollBox1->FindComponent("EditT"+String(i)))->Text) == 0){
	 flag = false;
   }
 }

if (flag) {

  //GroupBox1->Enabled = false;

  neurons_in_layer = new int[n_of_layers];

  int max = 0;
  for(int i=0; i<n_of_layers;i++){
	neurons_in_layer[i] = StrToInt(((TEdit*)ScrollBox1->FindComponent("EditT"+String(i)))->Text);
   if (neurons_in_layer[i] > max){
	 max = neurons_in_layer[i];
   }
  }

  int min_ver_separator = 40;
  int height = min_ver_separator*(max+1);
  Image1->Height = height;
  int hor_separator = 80;
  Image1->Width = 2*hor_separator*(n_of_layers)+hor_separator;
  int radius = 12;
  //coder
  for(int i=1; i<n_of_layers;i++){
   int x = i*hor_separator;
   int n_of_neuron = neurons_in_layer[i-1];
   int ver_separator = height/(n_of_neuron+1);
   for(int y=1; y<=n_of_neuron; y++){
	 //paint powers
	   int next_x = (i+1)*hor_separator;
	   int next_n_of_neuron = neurons_in_layer[i];
	   int next_ver_separator = height/(next_n_of_neuron+1);
	   for(int j=1; j<=next_n_of_neuron; j++){
		 Image1->Canvas->Brush->Color = RGB(0,0,255);
		 Image1->Canvas->MoveTo(x,y*ver_separator);
		 Image1->Canvas->LineTo(next_x, j*next_ver_separator);
	   }
	 //paint powers
	 if (i == 1) {
	   Image1->Canvas->Brush->Color = RGB(255,0,0);
	 }else{
	   Image1->Canvas->Brush->Color = RGB(255,215,0);
	 }
	 Image1->Canvas->Ellipse(x-radius,y*ver_separator-radius,x+radius,y*ver_separator+radius);
   }
 }
   int x = n_of_layers*hor_separator;
   int n_of_neuron = neurons_in_layer[n_of_layers-1];
   int ver_separator = height/(n_of_neuron+1);
   for(int y=1; y<=n_of_neuron; y++){
	 Image1->Canvas->MoveTo(x,y*ver_separator);
	 Image1->Canvas->LineTo(x+hor_separator, y*ver_separator);
	 Image1->Canvas->Brush->Color = RGB(255,0,0);
	 Image1->Canvas->Ellipse(x-radius,y*ver_separator-radius,x+radius,y*ver_separator+radius);
   }
  //end coder




  //netCompressor = new NeuralNetwork(neurons_in_layer, n_of_layers);

}else{
  ShowMessage("Значення не можуть бути нульовими!!!");
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	TForm2 *form2 = new TForm2(this, Memo1, learn_data_array);
	form2->ShowModal();
}
//---------------------------------------------------------------------------
