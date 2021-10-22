//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   S C A L I N G   L A Y E R   T E S T   C L A S S
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "scaling_layer_test.h"


ScalingLayerTest::ScalingLayerTest() : UnitTesting()
{
    scaling_layer.set_display(false);

}


ScalingLayerTest::~ScalingLayerTest()
{
}


void ScalingLayerTest::test_constructor()
{
   cout << "test_constructor\n";

   ScalingLayer scaling_layer_1;

   assert_true(scaling_layer_1.get_type() == Layer::Type::Scaling, LOG);
//   assert_true(scaling_layer_1.().size() == 0, LOG);

   ScalingLayer scaling_layer_2(3);

   assert_true(scaling_layer_2.get_descriptives().size() == 3, LOG);
   assert_true(scaling_layer_2.get_scaling_methods().size() == 3, LOG);

   descriptives.resize(2);

   ScalingLayer scaling_layer_3(descriptives);

   assert_true(scaling_layer_3.get_descriptives().size() == 2, LOG);
}


void ScalingLayerTest::test_set()
{
   cout << "test_set\n";

   // Test

   scaling_layer.set();

   assert_true(scaling_layer.get_descriptives().size() == 0, LOG);

   descriptives.resize(4);
   scaling_layer.set_descriptives(descriptives);
   scaling_layer.set();

   assert_true(scaling_layer.get_descriptives().size() == 0, LOG);

   // Test

   Index new_inputs_number_ = 4;
   scaling_layer.set(new_inputs_number_);

   assert_true(scaling_layer.get_descriptives().size()== 4, LOG);
   assert_true(scaling_layer.get_scaling_methods().size()== 4, LOG);

   // Test

   scaling_layer.set();

   Tensor<Index, 1> new_inputs_dimensions(1);
   new_inputs_dimensions.setConstant(3);
   scaling_layer.set(new_inputs_dimensions);

   assert_true(scaling_layer.get_descriptives().size()== 3, LOG);
   assert_true(scaling_layer.get_scaling_methods().size()== 3, LOG);

   // Test 

   scaling_layer.set();

   descriptives.resize(0);
   scaling_layer.set(descriptives);

   assert_true(scaling_layer.get_descriptives().size()== 0, LOG);
   assert_true(scaling_layer.get_scaling_methods().size()== 0, LOG);

   // Test

   descriptives.resize(4);
   scaling_layer.set(descriptives);

   assert_true(scaling_layer.get_descriptives().size()== 4, LOG);
   assert_true(scaling_layer.get_scaling_methods().size()== 4, LOG);

}


void ScalingLayerTest::test_set_inputs_number()
{
   cout << "test_set_inputs_number\n";

   Index new_inputs_number(0);
   scaling_layer.set_inputs_number(new_inputs_number);

   assert_true(scaling_layer.get_descriptives().size()== 0, LOG);
   assert_true(scaling_layer.get_scaling_methods().size()== 0, LOG);

   Index new_inputs_number_ = 4;
   scaling_layer.set_inputs_number(new_inputs_number_);

   assert_true(scaling_layer.get_descriptives().size()== 4, LOG);
   assert_true(scaling_layer.get_scaling_methods().size()== 4, LOG);
}


void ScalingLayerTest::test_set_neurons_number()
{
   cout << "test_set_neurons_number\n";

   Index new_inputs_number(0);
   scaling_layer.set_neurons_number(new_inputs_number);

   assert_true(scaling_layer.get_descriptives().size()== 0, LOG);
   assert_true(scaling_layer.get_scaling_methods().size()== 0, LOG);

   Index new_inputs_number_ = 4;
   scaling_layer.set_neurons_number(new_inputs_number_);

   assert_true(scaling_layer.get_descriptives().size()== 4, LOG);
   assert_true(scaling_layer.get_scaling_methods().size()== 4, LOG);
}


void ScalingLayerTest::test_set_default()
{
   cout << "test_set_default\n";

   scaling_layer.set(1);

   scaling_layer.set_default();

   Tensor<Descriptives, 1> sl_descriptives = scaling_layer.get_descriptives();

   assert_true(scaling_layer.get_scaling_methods()(0) == Scaler::MinimumMaximum, LOG);
   assert_true(scaling_layer.get_display(), LOG);
   assert_true(scaling_layer.get_type() == Layer::Type::Scaling, LOG);
//   assert_true(scaling_layer.get_type() == 0, LOG);
   assert_true(abs(sl_descriptives(0).minimum + type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(sl_descriptives(0).maximum - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(sl_descriptives(0).mean) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(sl_descriptives(0).standard_deviation - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
}


void ScalingLayerTest::test_set_descriptives()
{
   cout << "test_set_descriptives\n";  

   Descriptives item_0(type(1), type(1), type(1), type(0));
   Descriptives item_1(type(2), type(2), type(2), type(0));

   // Test

   descriptives.resize(1);

   scaling_layer.set_descriptives(descriptives);

//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,0) + type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,1) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,2)) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,3) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test

   descriptives.resize(2);
   descriptives.setValues({item_0, item_1});

   scaling_layer.set_descriptives(descriptives);

//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,0) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,2) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(1,1) - type(2)) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(1,3)) < type(NUMERIC_LIMITS_MIN), LOG);

}


void ScalingLayerTest::test_set_item_descriptives()
{
   cout << "test_set_item_descriptives\n";

   Descriptives item_descriptives_1;
   Descriptives item_descriptives_2;

   // Test

   scaling_layer.set(1);

   scaling_layer.set_item_descriptives(0, item_descriptives_1);

//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,0) + type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,1) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,2)) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,3) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test

   scaling_layer.set(2);

//   item_descriptives_1.set(1,1,1,0);
//   item_descriptives_2.set(2,2,2,0);

   scaling_layer.set_item_descriptives(0, item_descriptives_1);
   scaling_layer.set_item_descriptives(1, item_descriptives_1);

//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,0) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,2) - type(1)) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(1,1) - type(2)) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(1,3)) < type(NUMERIC_LIMITS_MIN), LOG);

}

void ScalingLayerTest::test_set_minimum()
{
   cout << "test_set_minimum\n";

   // Test

   scaling_layer.set(2);
   descriptives.resize(2);

   scaling_layer.set_descriptives(descriptives);

   scaling_layer.set_minimum(0, type(-5));
   scaling_layer.set_minimum(1, type(-6));

//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,0) + 5) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(1,0) + type(6)) < type(NUMERIC_LIMITS_MIN), LOG);
}


void ScalingLayerTest::test_set_maximum()
{
   cout << "test_set_maximum\n";

   scaling_layer.set(2);

   // Test

   Tensor<Descriptives, 1> descriptives(2);

   scaling_layer.set_descriptives(descriptives);

   scaling_layer.set_maximum(0, type(5));
   scaling_layer.set_maximum(1, type(6));

//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,1) - 5) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(1,1) - type(6)) < type(NUMERIC_LIMITS_MIN), LOG);
}


void ScalingLayerTest::test_set_mean()
{
   cout << "test_set_mean\n";

   scaling_layer.set(2);

   // Test

   Tensor<Descriptives, 1> descriptives(2);

   scaling_layer.set_descriptives(descriptives);

   scaling_layer.set_mean(0, type(5));
   scaling_layer.set_mean(1, type(6));

//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,2) - 5) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(1,2) - type(6)) < type(NUMERIC_LIMITS_MIN), LOG);
}


void ScalingLayerTest::test_set_standard_deviation()
{
   cout << "test_set_standard_deviation\n";

   scaling_layer.set(2);

   // Test

   Tensor<Descriptives, 1> descriptives(2);

   scaling_layer.set_descriptives(descriptives);

   scaling_layer.set_standard_deviation(0, type(5));
   scaling_layer.set_standard_deviation(1, type(6));

//   assert_true(abs(scaling_layer.get_descriptives_matrix()(0,3) - 5) < type(NUMERIC_LIMITS_MIN), LOG);
//   assert_true(abs(scaling_layer.get_descriptives_matrix()(1,3) - type(6)) < type(NUMERIC_LIMITS_MIN), LOG);
}


void ScalingLayerTest::test_set_scaling_method()
{
   cout << "test_set_scaling_method\n";

    scaling_layer.set(4);

    // Test

    Tensor<Scaler, 1> method_tensor_1(4);
    method_tensor_1.setValues({Scaler::NoScaling,
                                Scaler::MinimumMaximum,
                                Scaler::MeanStandardDeviation,
                                Scaler::StandardDeviation});

    scaling_layer.set_scalers(method_tensor_1);

/*
    assert_true(scaling_layer.get_scaling_methods()(0) == Scaler::NoScaling, LOG);
    assert_true(scaling_layer.get_scaling_methods()(0) == 0, LOG);

    assert_true(scaling_layer.get_scaling_methods()(1) == Scaler::MinimumMaximum, LOG);
    assert_true(scaling_layer.get_scaling_methods()(1) == 1, LOG);

    assert_true(scaling_layer.get_scaling_methods()(2) == Scaler::MeanStandardDeviation, LOG);
    assert_true(scaling_layer.get_scaling_methods()(2) == 2, LOG);

    assert_true(scaling_layer.get_scaling_methods()(3) == Scaler::StandardDeviation, LOG);
    assert_true(scaling_layer.get_scaling_methods()(3) == 3, LOG);

    // Test
*/
    Tensor<string, 1> method_tensor_2(4);
    method_tensor_2.setValues({"NoScaling",
                                "MinimumMaximum",
                                "MeanStandardDeviation",
                                "StandardDeviation"});

    scaling_layer.set_scalers(method_tensor_2);

    assert_true(scaling_layer.get_scaling_methods()(0) == Scaler::NoScaling, LOG);
//    assert_true(scaling_layer.get_scaling_methods()(0) == 0, LOG);

    assert_true(scaling_layer.get_scaling_methods()(1) == Scaler::MinimumMaximum, LOG);
//    assert_true(scaling_layer.get_scaling_methods()(1) == 1, LOG);

    assert_true(scaling_layer.get_scaling_methods()(2) == Scaler::MeanStandardDeviation, LOG);
//    assert_true(scaling_layer.get_scaling_methods()(2) == 2, LOG);

    assert_true(scaling_layer.get_scaling_methods()(3) == Scaler::StandardDeviation, LOG);
//    assert_true(scaling_layer.get_scaling_methods()(3) == 3, LOG);

    // Test

    string no_scaling = "NoScaling";
    string minimum_maximum = "MinimumMaximum";
    string mean_standard_deviation = "MeanStandardDeviation";
    string standard_deviation = "StandardDeviation";

    scaling_layer.set_scalers(no_scaling);

    assert_true(scaling_layer.get_scaling_methods()(0) == Scaler::NoScaling, LOG);
//    assert_true(scaling_layer.get_scaling_methods()(0) == 0, LOG);

    scaling_layer.set_scalers(minimum_maximum);

    assert_true(scaling_layer.get_scaling_methods()(0) == Scaler::MinimumMaximum, LOG);
//    assert_true(scaling_layer.get_scaling_methods()(0) == 1, LOG);

    scaling_layer.set_scalers(mean_standard_deviation);

    assert_true(scaling_layer.get_scaling_methods()(0) == Scaler::MeanStandardDeviation, LOG);
//    assert_true(scaling_layer.get_scaling_methods()(0) == 2, LOG);

    scaling_layer.set_scalers(standard_deviation);

    assert_true(scaling_layer.get_scaling_methods()(0) == Scaler::StandardDeviation, LOG);
//    assert_true(scaling_layer.get_scaling_methods()(0) == 3, LOG);

    // Test 

    Scaler no_scaling_4 = Scaler::NoScaling;

    Scaler minimum_maximum_4 = Scaler::MinimumMaximum;

    Scaler mean_standard_deviation_4 = Scaler::MeanStandardDeviation;

    Scaler standard_deviation_4 = Scaler::StandardDeviation;

    scaling_layer.set_scalers(no_scaling_4);

    assert_true(scaling_layer.get_scaling_methods()(0) == Scaler::NoScaling, LOG);
//    assert_true(scaling_layer.get_scaling_methods()(0) == 0, LOG);

    scaling_layer.set_scalers(minimum_maximum_4);

    assert_true(scaling_layer.get_scaling_methods()(0) == Scaler::MinimumMaximum, LOG);
//    assert_true(scaling_layer.get_scaling_methods()(0) == 1, LOG);

    scaling_layer.set_scalers(mean_standard_deviation_4);

    assert_true(scaling_layer.get_scaling_methods()(0) == Scaler::MeanStandardDeviation, LOG);
//    assert_true(scaling_layer.get_scaling_methods()(0) == 2, LOG);

    scaling_layer.set_scalers(standard_deviation_4);

    assert_true(scaling_layer.get_scaling_methods()(0) == Scaler::StandardDeviation, LOG);
//    assert_true(scaling_layer.get_scaling_methods()(0) == 3, LOG);

    }


void ScalingLayerTest::test_is_empty()
{
   cout << "test_is_empty\n";

   scaling_layer.set(1);

   assert_true(scaling_layer.is_empty(), LOG);
   assert_true(!scaling_layer.is_empty(), LOG);
}


void ScalingLayerTest::test_check_range()
{
   cout << "test_check_range\n";

   Tensor<type, 1> inputs;

   // Test

   scaling_layer.set(1);

   inputs.resize(1);
   inputs.setConstant(type(0));
   scaling_layer.check_range(inputs);

   // Test

   Tensor<Descriptives, 1> descriptives(1);
   Descriptives des(type(-1), type(1), type(1), type(0));
   descriptives.setValues({des});

   scaling_layer.set_descriptives(descriptives);

   scaling_layer.check_range(inputs);
}


void ScalingLayerTest::test_calculate_outputs()
{
   cout << "test_calculate_outputs\n";

   Tensor<type, 2> inputs;
   Tensor<type, 2> outputs;

   // Test

   scaling_layer.set(1);
   scaling_layer.set_scalers(Scaler::NoScaling);

   inputs.resize(1,1);
   outputs = scaling_layer.calculate_outputs(inputs);
   assert_true(outputs.dimension(0) == 1, LOG);
   assert_true(outputs.dimension(1) == 1, LOG);
   assert_true(abs(outputs(0) - inputs(0)) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test

   scaling_layer.set(3);
   scaling_layer.set_scalers(Scaler::NoScaling);

   inputs.resize(1,3);
   inputs.setConstant(type(0));
   outputs = scaling_layer.calculate_outputs(inputs);

   assert_true(outputs.dimension(0) == 1, LOG);
   assert_true(outputs.dimension(1) == 3, LOG);
   assert_true(abs(outputs(0)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(outputs(1)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(outputs(2)) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test

   scaling_layer.set(1);
   scaling_layer.set_scalers(Scaler::MinimumMaximum);

   inputs.resize(1,1);
   outputs = scaling_layer.calculate_outputs(inputs);
   assert_true(outputs.dimension(0) == 1, LOG);
   assert_true(outputs.dimension(1) == 1, LOG);

   assert_true(abs(outputs(0) - inputs(0)) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test

   scaling_layer.set(3);
   scaling_layer.set_scalers(Scaler::MinimumMaximum);

   Tensor<type, 2> minimums_maximums(3, 4);
   minimums_maximums.setValues({{type(-1),type(2),type(0),type(0)},{type(-2),type(4),type(0),type(0)},{type(-3),type(6),type(0),type(0)}});

   inputs.resize(1,3);
   inputs.setConstant(type(0));
   outputs = scaling_layer.calculate_outputs(inputs);

   assert_true(outputs.dimension(0) == 1, LOG);
   assert_true(outputs.dimension(1) == 3, LOG);
   assert_true(abs(outputs(0) + static_cast<type>(0.333)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(outputs(1) + static_cast<type>(0.333)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(outputs(2) + static_cast<type>(0.333)) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test

   scaling_layer.set(1);
   scaling_layer.set_scalers(Scaler::MeanStandardDeviation);

   inputs.resize(1,1);
   outputs = scaling_layer.calculate_outputs(inputs);
   assert_true(outputs.dimension(0) == 1, LOG);
   assert_true(outputs.dimension(1) == 1, LOG);
   assert_true(abs(outputs(0) - inputs(0)) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test

   scaling_layer.set(2);
   scaling_layer.set_scalers(Scaler::MeanStandardDeviation);

   Tensor<type, 2> mean_standard_deviation(2,4);
   mean_standard_deviation.setValues({{type(-1),type(1),type(-1),type(2)},{type(-1),type(1),type(1),type(4)}});

   inputs.resize(1,2);
   inputs.setConstant(type(0));
   outputs = scaling_layer.calculate_outputs(inputs);

   assert_true(outputs.dimension(0) == 1, LOG);
   assert_true(outputs.dimension(1) == 2, LOG);

   assert_true(abs(outputs(0) - static_cast<type>(0.5)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(outputs(1) + static_cast<type>(0.25)) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test

   scaling_layer.set(1);
   scaling_layer.set_scalers(Scaler::StandardDeviation);

   inputs.resize(1,1);
   outputs = scaling_layer.calculate_outputs(inputs);
   assert_true(outputs.dimension(0) == 1, LOG);
   assert_true(outputs.dimension(1) == 1, LOG);
   assert_true(abs(outputs(0) - inputs(0)) < type(NUMERIC_LIMITS_MIN), LOG);

   // Test
   scaling_layer.set(2);
   scaling_layer.set_scalers(Scaler::StandardDeviation);

   Tensor<type, 2> standard_deviation(2,4);
   standard_deviation.setValues({{type(-1),type(1),type(-1),type(2)},{type(-1),type(1),type(1),type(4)}});

   inputs.resize(1,2);
   inputs.setConstant(type(1));
   outputs = scaling_layer.calculate_outputs(inputs);

   assert_true(outputs.dimension(0) == 1, LOG);
   assert_true(outputs.dimension(1) == 2, LOG);
   assert_true(abs(outputs(0) - static_cast<type>(0.5)) < type(NUMERIC_LIMITS_MIN), LOG);
   assert_true(abs(outputs(1) - static_cast<type>(0.25)) < type(NUMERIC_LIMITS_MIN), LOG);
}


void ScalingLayerTest::run_test_case()
{
   cout << "Running scaling layer test case...\n";

   // Constructor and destructor methods

   test_constructor();

   // Set methods

   test_set();
   test_set_inputs_number();
   test_set_neurons_number();
   test_set_default();

   // Input variables descriptives

   test_set_descriptives();
   test_set_item_descriptives();
   test_set_minimum();
   test_set_maximum();
   test_set_mean();
   test_set_standard_deviation();

   // Variables scaling and unscaling

   test_set_scaling_method();

   // Input range

   test_is_empty();
   test_check_range();

   // Scaling and unscaling

   test_calculate_outputs();

   cout << "End of scaling layer test case.\n\n";
}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2021 Artificial Intelligence Techniques, SL.
//
// This library sl free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library sl distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
