#include <iostream>
#include <random>
#include <chrono>
#include <vector>

#include "Neuron.h"

using namespace std;

void dataGenerator(int numberOfSamples, Matrix<float> &featureMatrix, Array<float> &classificationVector)
{
    // Set the matrix sizes
    int dimensionality = 2;
    featureMatrix.setSize(dimensionality, numberOfSamples);
    classificationVector.setSize(numberOfSamples); // 1D column vector

    // cout << "Sample data:" << endl;

    for (int i = 0; i < numberOfSamples; i++)
    {
        // Set the feature matrix sample data range
        for (int j = 0; j < dimensionality; j++)
            featureMatrix[j][i] = rand() % 1001 - 500;

        // The real classification function
        if (featureMatrix[0][i] - featureMatrix[1][i] >= 0) // Condition: x - y >= 0
            classificationVector[i] = 1;
        else // Class 0 otherwise
            classificationVector[i] = 0;
    }
}

float perceptronTest()
{
    cout << "### Neural network: Neuron test ###" << endl;
    Neuron perceptron;
    perceptron.activationFunctionEnum = TANH01;
    // perceptron.activationFunctionEnum = LOGISTIC;
    // perceptron.activationFunctionEnum = TANH; // Not sure why this doesn't work
    Matrix<float> featureMatrix;
    Array<float> classificationVector;
    dataGenerator(500, featureMatrix, classificationVector);

    /* Learning phase */
    cout << "\nLearning phase:" << endl;
    perceptron.deltaLearning(featureMatrix, classificationVector, 50, 0.5f);
    cout << "Success." << endl;
    // perceptron.hebbianLearning(featureMatrix, 50, 0.5);

    /* Data classification with training data */
    cout << "\nTraining data classification phase" << endl;
    int correct = 0;
    for (int i = 0; i < classificationVector.size(); i++)
    {
        Matrix<float> dataPoint = featureMatrix.subMatrix(0, featureMatrix.getSizeX(), i, i);
        if (round(perceptron.predict(dataPoint)) == classificationVector[i])
            correct++;
    }
    cout << "Correctly classified = " << correct << ", incorrectly classified = " << classificationVector.size() - correct << endl;

    /* Data prediction with new data samples */
    cout << "\nNew data testing phase" << endl;
    Matrix<float> testFeatureMatrix; // Generate test data
    Array<float> testClassificationMatrix;
    dataGenerator(100, testFeatureMatrix, testClassificationMatrix);
    correct = 0;
    for (int i = 0; i < testClassificationMatrix.size(); i++)
    {
        Matrix<float> dataPoint = testFeatureMatrix.subMatrix(0, testFeatureMatrix.getSizeX(), i, i);
        if (round(perceptron.predict(dataPoint)) == testClassificationMatrix[i])
            correct++;
    }
    cout << "Correctly classified = " << correct << ", incorrectly classified = " << testClassificationMatrix.size() - correct << endl;
    cout << "Neuron success rate = " << correct / (float) testClassificationMatrix.size() * 100 << "%" << endl;
    perceptron.printWeightMatrix();

    return correct / (float) testClassificationMatrix.size() * 100; // Return the success rate
}

int main()
{
    /* Initialisation */
    srand(time(NULL));

    // Testing a single neuron/perceptron
    perceptronTest();

    return 0;
}
