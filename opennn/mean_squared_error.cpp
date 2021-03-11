//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   M E A N   S Q U A R E D   E R R O R   C L A S S
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "mean_squared_error.h"

namespace OpenNN
{

/// Default constructor.
/// It creates a mean squared error term not associated to any
/// neural network and not measured on any data set.
/// It also initializes all the rest of class members to their default values.

MeanSquaredError::MeanSquaredError() : LossIndex()
{
}


/// Neural network and data set constructor.
/// It creates a mean squared error term object associated to a
/// neural network and measured on a data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_data_set_pointer Pointer to a data set object.

MeanSquaredError::MeanSquaredError(NeuralNetwork* new_neural_network_pointer, DataSet* new_data_set_pointer)
    : LossIndex(new_neural_network_pointer, new_data_set_pointer)
{
}


/// Destructor.

MeanSquaredError::~MeanSquaredError()
{
}


/// \brief MeanSquaredError::calculate_error
/// \param batch
/// \param forward_propagation
/// \param back_propagation

void MeanSquaredError::calculate_error(const DataSetBatch& batch,
                     const NeuralNetworkForwardPropagation& forward_propagation,
                     BackPropagation& back_propagation) const
{
    Tensor<type, 0> sum_squared_error;

    const Index batch_samples_number = batch.inputs_2d.dimension(0);

    sum_squared_error.device(*thread_pool_device) = back_propagation.errors.contract(back_propagation.errors, SSE);

    back_propagation.error = sum_squared_error(0)/static_cast<type>(batch_samples_number);
}


void MeanSquaredError::calculate_error_terms(const DataSetBatch& batch,
                                             const NeuralNetworkForwardPropagation& forward_propagation,
                                             LossIndexBackPropagationLM& second_order_loss) const
{
    const Index trainable_layers_number = neural_network_pointer->get_trainable_layers_number();

    const Layer* output_layer_pointer = neural_network_pointer->get_output_layer_pointer();

    LayerForwardPropagation* output_layer_forward_propagation = forward_propagation.layers(trainable_layers_number-1);

    const Eigen::array<int, 1> rows_sum = {Eigen::array<int, 1>({1})};

    const Tensor<type, 2>& targets = batch.targets_2d;


    switch(output_layer_pointer->get_type())
    {
    case Layer::Perceptron:
    {
        PerceptronLayerForwardPropagation* perceptron_layer_forward_propagation
        = static_cast<PerceptronLayerForwardPropagation*>(output_layer_forward_propagation);

        const Tensor<type, 2>& outputs = perceptron_layer_forward_propagation->activations;

        second_order_loss.squared_errors.device(*thread_pool_device) = ((outputs - targets).square().sum(rows_sum)).sqrt();
    }
        break;

    case Layer::Probabilistic:
    {
        ProbabilisticLayerForwardPropagation* probabilistic_layer_forward_propagation
        = static_cast<ProbabilisticLayerForwardPropagation*>(output_layer_forward_propagation);

        const Tensor<type, 2>& outputs = probabilistic_layer_forward_propagation->activations;

        second_order_loss.squared_errors.device(*thread_pool_device) = ((outputs - targets).square().sum(rows_sum)).sqrt();
    }
        break;

    case Layer::Recurrent:
    {
        RecurrentLayerForwardPropagation* recurrent_layer_forward_propagation
        = static_cast<RecurrentLayerForwardPropagation*>(output_layer_forward_propagation);

        const Tensor<type, 2>& outputs = recurrent_layer_forward_propagation->activations;

        second_order_loss.squared_errors.device(*thread_pool_device) = ((outputs - targets).square().sum(rows_sum)).sqrt();
    }
        break;

    case Layer::LongShortTermMemory:
    {
        LongShortTermMemoryLayerForwardPropagation* long_short_term_memory_layer_forward_propagation
        = static_cast<LongShortTermMemoryLayerForwardPropagation*>(output_layer_forward_propagation);

        const Tensor<type, 2>& outputs = long_short_term_memory_layer_forward_propagation->activations;

        second_order_loss.squared_errors.device(*thread_pool_device) = ((outputs - targets).square().sum(rows_sum)).sqrt();
    }
        break;

    default: break;
    }

    const Index batch_samples_number = batch.get_samples_number();

    Tensor<type, 0> error;
    error.device(*thread_pool_device) = second_order_loss.squared_errors.contract(second_order_loss.squared_errors, AT_B);

    second_order_loss.error = error()/static_cast<type>(batch_samples_number);
}


void MeanSquaredError::calculate_output_delta(const DataSetBatch& batch,
                                              NeuralNetworkForwardPropagation& forward_propagation,
                                              BackPropagation& back_propagation) const
{
     #ifdef __OPENNN_DEBUG__

     check();

     #endif

     const Index trainable_layers_number = neural_network_pointer->get_trainable_layers_number();

     LayerBackPropagation* output_layer_back_propagation = back_propagation.neural_network.layers(trainable_layers_number-1);

     const Index batch_samples_number = batch.inputs_2d.dimension(0);

     const type coefficient = static_cast<type>(2.0)/static_cast<type>(batch_samples_number);

     switch(output_layer_back_propagation->layer_pointer->get_type())
     {
     case Layer::Perceptron:
     {
         PerceptronLayerBackPropagation* perceptron_layer_back_propagation
         = static_cast<PerceptronLayerBackPropagation*>(output_layer_back_propagation);

         perceptron_layer_back_propagation->delta.device(*thread_pool_device) = coefficient*back_propagation.errors;
     }
         break;

     case Layer::Probabilistic:
     {
         ProbabilisticLayerBackPropagation* probabilistic_layer_back_propagation
         = static_cast<ProbabilisticLayerBackPropagation*>(output_layer_back_propagation);

         probabilistic_layer_back_propagation->delta.device(*thread_pool_device) = coefficient*back_propagation.errors;
     }
         break;

     case Layer::Recurrent:
     {
         RecurrentLayerBackPropagation* recurrent_layer_back_propagation
         = static_cast<RecurrentLayerBackPropagation*>(output_layer_back_propagation);

         recurrent_layer_back_propagation->delta.device(*thread_pool_device) = coefficient*back_propagation.errors;
     }
         break;

     case Layer::LongShortTermMemory:
     {
         LongShortTermMemoryLayerBackPropagation* long_short_term_memory_layer_back_propagation
         = static_cast<LongShortTermMemoryLayerBackPropagation*>(output_layer_back_propagation);

         long_short_term_memory_layer_back_propagation->delta.device(*thread_pool_device) = coefficient*back_propagation.errors;
     }
         break;

     default: break;
     }
}


void MeanSquaredError::calculate_Jacobian_gradient(const DataSetBatch& batch,
                                                   LossIndexBackPropagationLM& second_order_loss) const
{
#ifdef __OPENNN_DEBUG__

    check();

#endif

    const Index batch_samples_number = batch.get_samples_number();

    const type coefficient = static_cast<type>(2)/static_cast<type>(batch_samples_number);

    second_order_loss.gradient.device(*thread_pool_device) = second_order_loss.squared_errors_Jacobian.contract(second_order_loss.squared_errors, AT_B);

    second_order_loss.gradient.device(*thread_pool_device) = coefficient*second_order_loss.gradient;
}



void MeanSquaredError::calculate_hessian_approximation(const DataSetBatch& batch, LossIndexBackPropagationLM& second_order_loss) const
{
     #ifdef __OPENNN_DEBUG__

     check();

     #endif

     const Index batch_samples_number = batch.inputs_2d.dimension(0);

     const type coefficient = (static_cast<type>(2.0)/static_cast<type>(batch_samples_number));

     second_order_loss.hessian.device(*thread_pool_device) = second_order_loss.squared_errors_Jacobian.contract(second_order_loss.squared_errors_Jacobian, AT_B);

     second_order_loss.hessian.device(*thread_pool_device) = coefficient*second_order_loss.hessian;
}


/// Returns a string with the name of the mean squared error loss type, "MEAN_SQUARED_ERROR".

string MeanSquaredError::get_error_type() const
{
    return "MEAN_SQUARED_ERROR";
}


/// Returns a string with the name of the mean squared error loss type in text format.

string MeanSquaredError::get_error_type_text() const
{
    return "Mean squared error";
}


/// Serializes the cross entropy error object into a XML document of the TinyXML library without keep the DOM tree in memory.
/// See the OpenNN manual for more information about the format of this document

void MeanSquaredError::write_XML(tinyxml2::XMLPrinter& file_stream) const
{
    // Error type

    file_stream.OpenElement("MeanSquaredError");

    file_stream.CloseElement();
}

}


// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2021 Artificial Intelligence Techniques, SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
