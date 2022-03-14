#include <fstream>
#include <iostream>
#include <algorithm>

#include <gtest/gtest.h>

#include "tfidentifier.h"

using namespace idf;

const size_t length = 1024;

TEST(TensorflowIdentifier, empty)
{
    // Load Tensrflow model
    std::cout << "TensorFlow Version: " << TF_Version() << std::endl;
    ASSERT_TRUE(true);
}

TEST(TensorflowIdentifier, accuracy)
{
    // Load Tensrflow model
    TfIdentifier clf{"d:/Workspace/OTUS/analyzer/ml/saved_model", length};

    // Load test data
    spectrum_t spectrum;
    std::ifstream test_data{"d:/Workspace/OTUS/analyzer/ml/test.csv"};
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

