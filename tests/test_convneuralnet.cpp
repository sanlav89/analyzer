#include <fstream>
#include <iostream>
#include <algorithm>

#include <gtest/gtest.h>

#include <model/idf/convneuralnet.h>

using namespace analyzer::model::idf;

const size_t length = 1024;

bool read_features_csv(std::istream &stream, spectrum_t &spectrum, char sep = ',')
{
    std::string line;
    std::getline(stream, line);
    std::stringstream linestream{line};
    std::string cell;

    auto idx = 0;
    while (std::getline(linestream, cell, sep)) {
        if (!cell.empty()) {
            spectrum[idx++] = std::stof(cell);
        }
    }
    return stream.good();
}

TEST(ConvNeuralNet, empty)
{
    // Load Tensrflow model
    std::cout << "TensorFlow Version: " << TF_Version() << std::endl;
    ASSERT_TRUE(true);
}

TEST(TensorflowIdentifier, accuracy)
{
    // Load Tensrflow model
    ConvNeuralNet clf{"../data/saved_model", length};

    // Load test data
    spectrum_t spectrum;
    std::ifstream test_data{"../../analyzer/ml/test.csv"};
    assert(test_data.is_open());

    // Calculate Accuracy
    auto steps_all = 0;
    float accuracy = 0;

    for (;;) {
        size_t y_true;
        test_data >> y_true;
        if (!read_features_csv(test_data, spectrum)) {
            break;
        }

        auto pred = clf.identify(spectrum);
        auto argmax = std::max_element(pred.begin(), pred.end());
        size_t y_pred = std::distance(pred.begin(), argmax);
        if (y_true == y_pred) {
            accuracy += 1;
        }
        steps_all++;
    }
    accuracy /= steps_all;

    std::cout << accuracy << std::endl;

    ASSERT_NEAR(accuracy, 0.9841820987654321, 1e-5);
}

