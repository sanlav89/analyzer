#pragma once

#include <tensorflow/c/c_api.h>

#include "method.h"
#include "utils/types.h"

namespace model {

namespace idf {

class ConvNeuralNet : public Method
{
public:

    using features_t = std::vector<float>;

    ConvNeuralNet(const std::string &modelpath, const int &length);

    ConvNeuralNet(const ConvNeuralNet &) = delete;

    ConvNeuralNet& operator=(const ConvNeuralNet &) = delete;

    probas_t identify(const spectrum_t &spectrum) override;

protected:

    size_t num_classes() const;


    static void delete_tf_session(TF_Session *);

    using tf_graph = std::unique_ptr<TF_Graph, decltype(&TF_DeleteGraph)>;
    using tf_buffer = std::unique_ptr<TF_Buffer, decltype(&TF_DeleteBuffer)>;
    using tf_import_graph_def_options = std::unique_ptr<TF_ImportGraphDefOptions, decltype(&TF_DeleteImportGraphDefOptions)>;
    using tf_status = std::unique_ptr<TF_Status, decltype(&TF_DeleteStatus)>;
    using tf_session_options = std::unique_ptr<TF_SessionOptions, decltype(&TF_DeleteSessionOptions)>;
    using tf_tensor = std::unique_ptr<TF_Tensor, decltype(&TF_DeleteTensor)>;
    using tf_session = std::unique_ptr<TF_Session, decltype(&delete_tf_session)>;

protected:
    tf_graph m_graph{TF_NewGraph(), TF_DeleteGraph};
    tf_session_options m_session_opts{TF_NewSessionOptions(), TF_DeleteSessionOptions};
    tf_session m_session = {nullptr, delete_tf_session};
    TF_Operation *m_input_op = nullptr;
    TF_Operation *m_output_op = nullptr;
    int m_length;
};

}

}
