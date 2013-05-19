class NeuralNetwork;

class Neuron{

private:
  NeuralNetwork *network;

  double *input_weights;
  int layer;
  int position;

  double net_signal;
  double active_signal;
  double displacement;

  double error;
  double learning_rate;

public:

  Neuron(){};
  Neuron(NeuralNetwork *neural_network, int layer, int pos);

  void setLayer(int layer_number){layer = layer_number;};
  int getLayer(){return layer;};
  void setPosition(int position_number){position = position_number;};
  int getPosition(){return position;};

  void calculate_net();
  void active_function(bool mode);//true - working mode else learn
  void calculate_error();
  void update_weights();

  double getNet(){return net_signal;};
  void setNet(double value){net_signal = value;};
  double getActiveSignal(){return active_signal;};
  double getWeight(int);
  void setError(double e){error = e;};
  double getError(){return error;};

};

class NeuralNetwork{
	private:

  Neuron ***neuro_net_array;
  int n_of_layers;
  int *n_of_neurons_in_layers;

	public:

  NeuralNetwork(int*, int);
  int getNumberOfLayers(){return n_of_layers;};
  int getNumberOfNeuronsInLayer(layer_number){return n_of_neurons_in_layers[layer_number];};

  Neuron* getNeuron(int i,int j){return neuro_net_array[i][j];};

  void LearnEpoch(int *inputdata, double result, TMemo* logMemo);
  double LinearMode(int *inputdata, TMemo* logMemo, bool mode);
};

Neuron::Neuron(NeuralNetwork *neural_network, int lay, int pos){
  net_signal = 0;
  error = 0;
  position = pos;
  layer = lay;
  active_signal = 0;
  displacement = (rand()%100)/100;
  learning_rate = 0.025;
  network = neural_network;

  if (layer > 0) {
	input_weights = new double[network->getNumberOfNeuronsInLayer(layer-1)];
	for (int i = 0; i < network->getNumberOfNeuronsInLayer(layer-1); i++) {
	  input_weights[i] = (rand()%100)/100.0;
	}
  }else{
	input_weights = new double[network->getNumberOfNeuronsInLayer(network->getNumberOfLayers()-2)];
	for (int i = 0; i < network->getNumberOfNeuronsInLayer(network->getNumberOfLayers()-2); i++) {
	  input_weights[i] = (rand()%100)/100.0;
	}
  }

}

void Neuron::calculate_net(){
	if(layer > 0){
		net_signal = 0;
		for (int i=0; i < network->getNumberOfNeuronsInLayer(layer-1); i++) {
			Neuron *neuron = network->getNeuron(layer-1,i);
			net_signal += neuron->getActiveSignal()*(input_weights[i]);
		}
	}else{
		for (int i=0; i < network->getNumberOfNeuronsInLayer(network->getNumberOfLayers()-2); i++) {
			Neuron *neuron = network->getNeuron(network->getNumberOfLayers()-2,i);
			net_signal += neuron->getActiveSignal()*(input_weights[i]);
		}
	}
	net_signal += displacement;
}

void Neuron::active_function(bool mode){
	if(!mode){
		active_signal = 1/(1+exp(-net_signal));
		return;
	}
  if (layer == network->getNumberOfLayers()-1) {
	if(net_signal > 0.5){
	  active_signal = 1;
	}else{
	  active_signal = 0;
	}
  }else{
	active_signal = 1/(1+exp(-net_signal));  //sigmoid
  }
}

void Neuron::calculate_error(){
	double sum = 0;
	for(int i = 0; i < network->getNumberOfNeuronsInLayer(layer+1); i++){
		Neuron *neuron = network->getNeuron(layer+1, i);
		sum += (neuron->getError())*(neuron->getWeight(position));
	}
	error = sum*active_signal*(1-active_signal);
}

void Neuron::update_weights(){
	if(layer != 0){
		for(int i = 0; i < network->getNumberOfNeuronsInLayer(layer-1); i++){
			 input_weights[i] += learning_rate*error*active_signal;
		}
	}else{
		for (int i=0; i < network->getNumberOfNeuronsInLayer(network->getNumberOfLayers()-2); i++) {
			input_weights[i] += learning_rate*error*active_signal;
		}
	}
	displacement -= learning_rate*error;
}

double Neuron::getWeight(int to_element_position){
  return input_weights[to_element_position];
}

NeuralNetwork::NeuralNetwork(int* n_of_neurons_in_each_layer, int number_of_layers){
  n_of_layers = number_of_layers;
  n_of_neurons_in_layers = new int[n_of_layers];

  for (int i = 0; i < n_of_layers; i++) {
	n_of_neurons_in_layers[i] = n_of_neurons_in_each_layer[i];
  }

  neuro_net_array = new Neuron**[n_of_layers];

  for (int i = 0; i < n_of_layers; i++) {
	neuro_net_array[i] = new Neuron*[n_of_neurons_in_layers[i]];
	for(int j = 0; j < n_of_neurons_in_layers[i]; j++){
		neuro_net_array[i][j] = new Neuron(this, i, j);
	}
  }
}

void NeuralNetwork::LearnEpoch(int* inputdata, double result, TMemo* logMemo){

	//linear mode
	LinearMode(inputdata, logMemo, false);
	double real_result = neuro_net_array[n_of_layers-1][0]->getActiveSignal();
	double error = result - real_result;
	logMemo->Lines->Add("");
	logMemo->Lines->Add("expected result:" + AnsiString(result)+"  "+
						"real result:" + AnsiString(real_result)+"  "+
						"error:" + AnsiString(error)+"  ");
	//backward propagation of errors
	//calculate errors
	logMemo->Lines->Add("");
	logMemo->Lines->Add("calculate errors");
	for(int i = n_of_layers-1 ; i >= 0; i--){
		for (int j = n_of_neurons_in_layers[i] - 1; j >=0; j--) {
			Neuron *neuron = neuro_net_array[i][j];
			logMemo->Lines->Add("Neuron["+AnsiString(i)+"]["+AnsiString(j)+"] ID:"+AnsiString((int)&*neuron));
			if(neuron->getLayer() == n_of_layers-1){
				neuron->setError(error);
			}else{
				neuron->calculate_error();
			}
			logMemo->Lines->Add("   error value -> "+AnsiString(neuron->getError()));
		}
	}
	//update_weights
	logMemo->Lines->Add("");
	logMemo->Lines->Add("update weights");
	for(int i = 1; i < n_of_layers; i++){
		for (int j = 0; j < n_of_neurons_in_layers[i]; j++) {
			Neuron *neuron = neuro_net_array[i][j];
			logMemo->Lines->Add("Neuron["+AnsiString(i)+"]["+AnsiString(j)+"] ID:"+AnsiString((int)&*neuron));
			neuron->update_weights();
			AnsiString weights_string;
			for (int z = 0; z < n_of_neurons_in_layers[i-1]; z++) {
				weights_string += AnsiString(neuron->getWeight(z)) + ", ";
			}
			logMemo->Lines->Add("   input weights -> "+ weights_string);
		}
	}
}

double NeuralNetwork::LinearMode(int *inputdata, TMemo* logMemo, bool mode){
	for(int i = 0; i < n_of_layers; i++){
		for (int j = 0; j < n_of_neurons_in_layers[i]; j++) {
			Neuron *neuron = neuro_net_array[i][j];
			if(!mode){
				logMemo->Lines->Add("Neuron["+AnsiString(i)+"]["+AnsiString(j)+"] ID:"+AnsiString((int)&*neuron));
			}
			AnsiString weights_string;
			if(i == 0){
				neuron->setNet(inputdata[j]);
				neuron->calculate_net();
				if(!mode){
					for (int z = 0; z < n_of_neurons_in_layers[n_of_layers - 2]; z++) {
						weights_string += AnsiString(neuron->getWeight(z)) + ", ";
					}
				}
			}else{
				neuron->calculate_net();
				if(!mode){
					for (int z = 0; z < n_of_neurons_in_layers[i-1]; z++) {
						weights_string += AnsiString(neuron->getWeight(z)) + ", ";
					}
				}
			}
			neuron->active_function(mode);

			if(!mode){
				logMemo->Lines->Add("   network value -> "+AnsiString(neuron->getNet()));
				logMemo->Lines->Add("   active signal -> "+AnsiString(neuron->getActiveSignal()));
			}
		}
	}
	double real_result = neuro_net_array[n_of_layers-1][0]->getActiveSignal();
	return real_result;
}






