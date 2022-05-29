# This is a small scale NN for one situation developed by KDNuggets, adjusted for RSSI (-26-100)
import numpy as np

#Mapping RSSI to normalized range for sigmoid fx
rssi = np.linspace(-110,-26,num = 85)
normalized = np.linspace(0,1,num = 85)

mapping = np.vstack((rssi, normalized)).T

class NeuralNetwork():
    
    def __init__(self):
        # seeding for random number generation
        np.random.seed(1)
        
        #converting weights to a 3 by 1 matrix with values from 0 to 1 and mean of 1 (range could also be -1 to 1 with mean 0)
        self.synaptic_weights =  np.random.random((3, 1)) 

    def sigmoid(self, x):
        #applying the sigmoid function
        sig = 1 / (1 + np.exp(-x))     # Define sigmoid function
        sig = np.minimum(sig, 0.9999)  # Set upper bound
        sig = np.maximum(sig, 0.0001)  # Set lower bound
        return sig

    def sigmoid_derivative(self, x):
        #computing derivative to the Sigmoid function
        return x * (1 - x)

    def train(self, training_inputs, training_outputs, training_iterations):
        
        #training the model to make accurate predictions while adjusting weights continually
        for iteration in range(training_iterations):
            #siphon the training data via  the neuron
            output = self.think(training_inputs)

            #computing error rate for back-propagation
            error = training_outputs - output
            
            #performing weight adjustments
            adjustments = np.dot(training_inputs.T, error * self.sigmoid_derivative(output))

            self.synaptic_weights += adjustments

    def think(self, inputs):
        #passing the inputs via the neuron to get output   
        #converting values to floats
        
        inputs = inputs.astype(float)
        output = self.sigmoid(np.dot(inputs, self.synaptic_weights))
        return output


if __name__ == "__main__":

    #initializing the neuron class
    neural_network = NeuralNetwork()

    print("Beginning Randomly Generated Weights: ")
    print(neural_network.synaptic_weights)

    #training data consisting of 4 examples--3 input values and 1 output
    #those 4 examples is the most occured MAC Address
    training_inputs = np.array([[.75,.762,.785],
                                [.047,.178,.214],
                                [.309,.452,.273],
                                [.761,.178,.5]]) #taken from mapping RSSI to 0-1 range to fit sigmoid fx

    training_outputs = np.array([[.702,.428,.428,1]]).T

    #training taking place
    neural_network.train(training_inputs, training_outputs, 15000)

    print("Ending Weights After Training: ")
    print(neural_network.synaptic_weights)

    user_input_one = 0.678571
    user_input_two = 0.619048
    user_input_three = 0.0952381 # str(input("User Input Three: "))
    
    print("Considering New Situation: ", user_input_one, user_input_two, user_input_three)
    print("New Output data: ")
    print(neural_network.think(np.array([user_input_one, user_input_two, user_input_three])))
    print(neural_network.think(np.array([user_input_two, user_input_one, user_input_three])))
    print(neural_network.think(np.array([user_input_three, user_input_one, user_input_two])))
    
    
    # reversed map and comparison:   
    #original:  -53, -58, -102
    #predicted: -60, -72, -100
