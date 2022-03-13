#include <iostream>

#include <gtest/gtest.h>

#include <tensorflow/c/c_api.h>

TEST(TensorflowIdentifier, empty)
{
    // Load Tensrflow model
    std::cout << "TensorFlow Version: " << TF_Version() << std::endl;
    ASSERT_TRUE(true);
}
