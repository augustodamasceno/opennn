//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   L E V E N B E R G - M A R Q U A R D T   A L G O R I T H M   C L A S S
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "levenberg_marquardt_algorithm.h"

namespace OpenNN
{

/// Default constructor.
/// It creates a Levenberg-Marquardt optimization algorithm object not associated to any loss index object.
/// It also initializes the class members to their default values.

LevenbergMarquardtAlgorithm::LevenbergMarquardtAlgorithm()
    : OptimizationAlgorithm()
{
    set_default();
}


/// Loss index constructor.
/// It creates a Levenberg-Marquardt optimization algorithm object associated associated with a given loss index object.
/// It also initializes the class members to their default values.
/// @param new_loss_index_pointer Pointer to an external loss index object.

LevenbergMarquardtAlgorithm::LevenbergMarquardtAlgorithm(LossIndex* new_loss_index_pointer)
    : OptimizationAlgorithm(new_loss_index_pointer)
{
    set_default();
}


/// XML Constructor.
/// Creates a Levenberg-Marquardt algorithm object, and loads its members from a XML document.
/// @param document TinyXML document containing the Levenberg-Marquardt algorithm data.

LevenbergMarquardtAlgorithm::LevenbergMarquardtAlgorithm(const tinyxml2::XMLDocument& document)
    : OptimizationAlgorithm(document)
{
    set_default();

    from_XML(document);
}


/// Destructor.
/// This destructor does not delete any object.

LevenbergMarquardtAlgorithm::~LevenbergMarquardtAlgorithm()
{
}


/// Returns the minimum value for the norm of the parameters vector at wich a warning message is
/// written to the screen.

const type& LevenbergMarquardtAlgorithm::get_warning_parameters_norm() const
{
    return warning_parameters_norm;
}


/// Returns the minimum value for the norm of the gradient vector at wich a warning message is written
/// to the screen.

const type& LevenbergMarquardtAlgorithm::get_warning_gradient_norm() const
{
    return warning_gradient_norm;
}


/// Returns the value for the norm of the parameters vector at wich an error message is
/// written to the screen and the program exits.

const type& LevenbergMarquardtAlgorithm::get_error_parameters_norm() const
{
    return error_parameters_norm;
}


/// Returns the value for the norm of the gradient vector at wich an error message is written
/// to the screen and the program exits.

const type& LevenbergMarquardtAlgorithm::get_error_gradient_norm() const
{
    return error_gradient_norm;
}


/// Returns the minimum norm of the parameter increment vector used as a stopping criteria when training.

const type& LevenbergMarquardtAlgorithm::get_minimum_parameters_increment_norm() const
{
    return minimum_parameters_increment_norm;
}


/// Returns the minimum loss improvement during training.

const type& LevenbergMarquardtAlgorithm::get_minimum_loss_decrease() const
{
    return minimum_loss_decrease;
}


/// Returns the goal value for the loss.
/// This is used as a stopping criterion when training a neural network.

const type& LevenbergMarquardtAlgorithm::get_loss_goal() const
{
    return training_loss_goal;
}


/// Returns the goal value for the norm of the loss function gradient.
/// This is used as a stopping criterion when training a neural network.

const type& LevenbergMarquardtAlgorithm::get_gradient_norm_goal() const
{
    return gradient_norm_goal;
}


/// Returns the maximum number of selection failures during the training process.

const Index& LevenbergMarquardtAlgorithm::get_maximum_selection_error_increases() const
{
    return maximum_selection_error_increases;
}


/// Returns the maximum number of iterations for training.

const Index& LevenbergMarquardtAlgorithm::get_maximum_epochs_number() const
{
    return maximum_epochs_number;
}


/// Returns the maximum training time.

const type& LevenbergMarquardtAlgorithm::get_maximum_time() const
{
    return maximum_time;
}


/// Returns true if the final model will be the neural network with the minimum selection error, false otherwise.

const bool& LevenbergMarquardtAlgorithm::get_choose_best_selection() const
{
    return choose_best_selection;
}


/// Returns true if the selection error decrease stopping criteria has to be taken in account, false otherwise.

const bool& LevenbergMarquardtAlgorithm::get_apply_early_stopping() const
{
    return apply_early_stopping;
}


/// Returns true if the error history vector is to be reserved, and false otherwise.

const bool& LevenbergMarquardtAlgorithm::get_reserve_training_error_history() const
{
    return reserve_training_error_history;
}


/// Returns true if the selection error history vector is to be reserved, and false otherwise.

const bool& LevenbergMarquardtAlgorithm::get_reserve_selection_error_history() const
{
    return reserve_selection_error_history;
}


/// Returns the damping parameter for the hessian approximation.

const type& LevenbergMarquardtAlgorithm::get_damping_parameter() const
{
    return damping_parameter;
}


/// Returns the damping parameter factor(beta in the User's Guide) for the hessian approximation.

const type& LevenbergMarquardtAlgorithm::get_damping_parameter_factor() const
{
    return damping_parameter_factor;
}


/// Returns the minimum damping parameter allowed in the algorithm.

const type& LevenbergMarquardtAlgorithm::get_minimum_damping_parameter() const
{
    return minimum_damping_parameter;
}


/// Returns the maximum damping parameter allowed in the algorithm.

const type& LevenbergMarquardtAlgorithm::get_maximum_damping_parameter() const
{
    return maximum_damping_parameter;
}


/// Sets the following default values for the Levenberg-Marquardt algorithm:
/// Training parameters:
/// <ul>
/// <li> Levenberg-Marquardt parameter: 0.001.
/// </ul>
/// Stopping criteria:
/// <ul>
/// <li> Loss goal: 1.0e-6.
/// <li> Gradient norm goal: 1.0e-6.
/// <li> Maximum training time: 1000 secondata_set.
/// <li> Maximum number of iterations: 1000.
/// </ul>
/// User stuff:
/// <ul>
/// <li> Iterations between showing progress: 10.
/// </ul>

void LevenbergMarquardtAlgorithm::set_default()
{
    // TRAINING PARAMETERS

    warning_parameters_norm = 1.0e6;
    warning_gradient_norm = 1.0e6;

    error_parameters_norm = 1.0e9;
    error_gradient_norm = 1.0e9;

    // Stopping criteria

    minimum_parameters_increment_norm = static_cast<type>(1.0e-3);

    minimum_loss_decrease = static_cast<type>(1.0e-9);
    training_loss_goal = static_cast<type>(1.0e-3);
    gradient_norm_goal = static_cast<type>(1.0e-3);
    maximum_selection_error_increases = 1000;

    maximum_epochs_number = 1000;
    maximum_time = 1000.0;

    choose_best_selection = false;
    apply_early_stopping = true;

    // TRAINING HISTORY

    reserve_training_error_history = false;
    reserve_selection_error_history = false;

    // UTILITIES

    display = true;
    display_period = 5;

    // Training parameters

    damping_parameter = static_cast<type>(1.0e-3);

    damping_parameter_factor = 10.0;

    minimum_damping_parameter = static_cast<type>(1.0e-6);
    maximum_damping_parameter = static_cast<type>(1.0e6);
}


/// Sets a new damping parameter(lambda in the User's Guide) for the hessian approximation.
/// @param new_damping_parameter Damping parameter value.

void LevenbergMarquardtAlgorithm::set_damping_parameter(const type& new_damping_parameter)
{
    if(new_damping_parameter <= minimum_damping_parameter)
    {
        damping_parameter = minimum_damping_parameter;
    }
    else if(new_damping_parameter >= maximum_damping_parameter)
    {
        damping_parameter = maximum_damping_parameter;
    }
    else
    {
        damping_parameter = new_damping_parameter;
    }
}


/// Sets a new damping parameter factor(beta in the User's Guide) for the hessian approximation.
/// @param new_damping_parameter_factor Damping parameter factor value.

void LevenbergMarquardtAlgorithm::set_damping_parameter_factor(const type& new_damping_parameter_factor)
{
#ifdef __OPENNN_DEBUG__

    if(new_damping_parameter_factor <= static_cast<type>(0.0))
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: LevenbergMarquardtAlgorithm class." << endl
               << "void set_damping_parameter_factor(const type&) method." << endl
               << "Damping parameter factor must be greater than zero." << endl;

        throw logic_error(buffer.str());
    }

#endif

    damping_parameter_factor = new_damping_parameter_factor;
}


/// Sets a new minimum damping parameter allowed in the algorithm.
/// @param new_minimum_damping_parameter Minimum damping parameter value.

void LevenbergMarquardtAlgorithm::set_minimum_damping_parameter(const type& new_minimum_damping_parameter)
{
#ifdef __OPENNN_DEBUG__

    if(new_minimum_damping_parameter <= static_cast<type>(0.0))
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: LevenbergMarquardtAlgorithm class." << endl
               << "void set_minimum_damping_parameter(const type&) method." << endl
               << "Minimum damping parameter must be greater than zero." << endl;

        throw logic_error(buffer.str());
    }

#endif

    minimum_damping_parameter = new_minimum_damping_parameter;
}


/// Sets a new maximum damping parameter allowed in the algorithm.
/// @param new_maximum_damping_parameter Maximum damping parameter value.

void LevenbergMarquardtAlgorithm::set_maximum_damping_parameter(const type& new_maximum_damping_parameter)
{
#ifdef __OPENNN_DEBUG__

    if(new_maximum_damping_parameter <= static_cast<type>(0.0))
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: LevenbergMarquardtAlgorithm class." << endl
               << "void set_maximum_damping_parameter(const type&) method." << endl
               << "Maximum damping parameter must be greater than zero." << endl;

        throw logic_error(buffer.str());
    }

#endif

    maximum_damping_parameter = new_maximum_damping_parameter;
}


/// Sets a new value for the parameters vector norm at which a warning message is written to the
/// screen.
/// @param new_warning_parameters_norm Warning norm of parameters vector value.

void LevenbergMarquardtAlgorithm::set_warning_parameters_norm(const type& new_warning_parameters_norm)
{
#ifdef __OPENNN_DEBUG__

    if(new_warning_parameters_norm < static_cast<type>(0.0))
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: OptimizationAlgorithm class.\n"
               << "void set_warning_parameters_norm(const type&) method.\n"
               << "Warning parameters norm must be equal or greater than 0.\n";

        throw logic_error(buffer.str());
    }

#endif

    // Set warning parameters norm

    warning_parameters_norm = new_warning_parameters_norm;
}


/// Sets a new value for the gradient vector norm at which
/// a warning message is written to the screen.
/// @param new_warning_gradient_norm Warning norm of gradient vector value.

void LevenbergMarquardtAlgorithm::set_warning_gradient_norm(const type& new_warning_gradient_norm)
{
#ifdef __OPENNN_DEBUG__

    if(new_warning_gradient_norm < static_cast<type>(0.0))
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: OptimizationAlgorithm class.\n"
               << "void set_warning_gradient_norm(const type&) method.\n"
               << "Warning gradient norm must be equal or greater than 0.\n";

        throw logic_error(buffer.str());
    }

#endif

    // Set warning gradient norm

    warning_gradient_norm = new_warning_gradient_norm;
}


/// Sets a new value for the parameters vector norm at which an error message is written to the
/// screen and the program exits.
/// @param new_error_parameters_norm Error norm of parameters vector value.

void LevenbergMarquardtAlgorithm::set_error_parameters_norm(const type& new_error_parameters_norm)
{
#ifdef __OPENNN_DEBUG__

    if(new_error_parameters_norm < static_cast<type>(0.0))
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: OptimizationAlgorithm class.\n"
               << "void set_error_parameters_norm(const type&) method.\n"
               << "Error parameters norm must be equal or greater than 0.\n";

        throw logic_error(buffer.str());
    }

#endif

    // Set error parameters norm

    error_parameters_norm = new_error_parameters_norm;
}


/// Sets a new value for the gradient vector norm at which an error message is written to the screen
/// and the program exits.
/// @param new_error_gradient_norm Error norm of gradient vector value.

void LevenbergMarquardtAlgorithm::set_error_gradient_norm(const type& new_error_gradient_norm)
{
#ifdef __OPENNN_DEBUG__

    if(new_error_gradient_norm < static_cast<type>(0.0))
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: OptimizationAlgorithm class.\n"
               << "void set_error_gradient_norm(const type&) method.\n"
               << "Error gradient norm must be equal or greater than 0.\n";

        throw logic_error(buffer.str());
    }

#endif

    // Set error gradient norm

    error_gradient_norm = new_error_gradient_norm;
}


/// Sets a new value for the minimum parameters increment norm stopping criterion.
/// @param new_minimum_parameters_increment_norm Value of norm of parameters increment norm used to stop training.

void LevenbergMarquardtAlgorithm::set_minimum_parameters_increment_norm(
        const type& new_minimum_parameters_increment_norm)
{
#ifdef __OPENNN_DEBUG__

    if(new_minimum_parameters_increment_norm < static_cast<type>(0.0))
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: OptimizationAlgorithm class.\n"
               << "void new_minimum_parameters_increment_norm(const type&) method.\n"
               << "Minimum parameters increment norm must be equal or greater than 0.\n";

        throw logic_error(buffer.str());
    }

#endif

    // Set error training rate

    minimum_parameters_increment_norm = new_minimum_parameters_increment_norm;
}


/// Sets a new minimum loss improvement during training.
/// @param new_minimum_loss_decrease Minimum improvement in the loss between two iterations.

void LevenbergMarquardtAlgorithm::set_minimum_loss_decrease(const type& new_minimum_loss_decrease)
{
#ifdef __OPENNN_DEBUG__

    if(new_minimum_loss_decrease < static_cast<type>(0.0))
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: OptimizationAlgorithm class.\n"
               << "void set_minimum_loss_decrease(const type&) method.\n"
               << "Minimum loss improvement must be equal or greater than 0.\n";

        throw logic_error(buffer.str());
    }

#endif

    // Set minimum loss improvement

    minimum_loss_decrease = new_minimum_loss_decrease;
}


/// Sets a new goal value for the loss.
/// This is used as a stopping criterion when training a neural network.
/// @param new_loss_goal Goal value for the loss.

void LevenbergMarquardtAlgorithm::set_loss_goal(const type& new_loss_goal)
{
    training_loss_goal = new_loss_goal;
}


/// Sets a new the goal value for the norm of the loss function gradient.
/// This is used as a stopping criterion when training a neural network.
/// @param new_gradient_norm_goal Goal value for the norm of the loss function gradient.

void LevenbergMarquardtAlgorithm::set_gradient_norm_goal(const type& new_gradient_norm_goal)
{
#ifdef __OPENNN_DEBUG__

    if(new_gradient_norm_goal < static_cast<type>(0.0))
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: OptimizationAlgorithm class.\n"
               << "void set_gradient_norm_goal(const type&) method.\n"
               << "Gradient norm goal must be equal or greater than 0.\n";

        throw logic_error(buffer.str());
    }

#endif

    // Set gradient norm goal

    gradient_norm_goal = new_gradient_norm_goal;
}


/// Sets a new maximum number of selection error increases.
/// @param new_maximum_selection_error_increases Maximum number of iterations in which the
/// selection evalutation increases.

void LevenbergMarquardtAlgorithm::set_maximum_selection_error_increases(
        const Index& new_maximum_selection_error_increases)
{
    maximum_selection_error_increases = new_maximum_selection_error_increases;
}


/// Sets a maximum number of iterations for training.
/// @param new_maximum_epochs_number Maximum number of iterations for training.

void LevenbergMarquardtAlgorithm::set_maximum_epochs_number(const Index& new_maximum_epochs_number)
{
    maximum_epochs_number = new_maximum_epochs_number;
}


/// Sets a new maximum training time.
/// @param new_maximum_time Maximum training time.

void LevenbergMarquardtAlgorithm::set_maximum_time(const type& new_maximum_time)
{
#ifdef __OPENNN_DEBUG__

    if(new_maximum_time < static_cast<type>(0.0))
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: OptimizationAlgorithm class.\n"
               << "void set_maximum_time(const type&) method.\n"
               << "Maximum time must be equal or greater than 0.\n";

        throw logic_error(buffer.str());
    }

#endif

    // Set maximum time

    maximum_time = new_maximum_time;
}


/// Makes the minimum selection error neural network of all the iterations to be returned or not.
/// @param new_choose_best_selection True if the final model will be the neural network with
/// the minimum selection error, false otherwise.

void LevenbergMarquardtAlgorithm::set_choose_best_selection(const bool& new_choose_best_selection)
{
    choose_best_selection = new_choose_best_selection;
}


/// Makes the selection error decrease stopping criteria has to be taken in account or not.
/// @param new_apply_early_stopping True if the selection error decrease stopping criteria
/// has to be taken in account, false otherwise.

void LevenbergMarquardtAlgorithm::set_apply_early_stopping(const bool& new_apply_early_stopping)
{
    apply_early_stopping = new_apply_early_stopping;
}


/// Makes the error history vector to be reseved or not in memory.
/// @param new_reserve_training_error_history True if the error history vector is to be reserved, false otherwise.

void LevenbergMarquardtAlgorithm::set_reserve_training_error_history(const bool& new_reserve_training_error_history)
{
    reserve_training_error_history = new_reserve_training_error_history;
}


/// Makes the selection error history to be reserved or not in memory.
/// This is a vector.
/// @param new_reserve_selection_error_history True if the selection error history is to be reserved, false otherwise.

void LevenbergMarquardtAlgorithm::set_reserve_selection_error_history(const bool& new_reserve_selection_error_history)
{
    reserve_selection_error_history = new_reserve_selection_error_history;
}


/// Sets a new number of iterations between the training showing progress.
/// @param new_display_period
/// Number of iterations between the training showing progress.

void LevenbergMarquardtAlgorithm::set_display_period(const Index& new_display_period)
{
#ifdef __OPENNN_DEBUG__

    if(new_display_period <= 0)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: OptimizationAlgorithm class.\n"
               << "void set_display_period(const type&) method.\n"
               << "First training rate must be greater than 0.\n";

        throw logic_error(buffer.str());
    }

#endif

    display_period = new_display_period;
}

/// Checks that the Levenberg-Marquard object is ok for training.
/// In particular, it checks that:
/// <ul>
/// <li> The loss index pointer associated to the optimization algorithm is not nullptr,
/// <li> The neural network associated to that loss index is neither nullptr.
/// <li> The data set associated to that loss index is neither nullptr.
/// </ul>
/// If that checkings are not hold, an exception is thrown.

void LevenbergMarquardtAlgorithm::check() const
{
    ostringstream buffer;

    if(!loss_index_pointer)
    {
        buffer << "OpenNN Exception: LevenbergMarquardtAlgorithm class.\n"
               << "void check() const method.\n"
               << "Pointer to loss index is nullptr.\n";

        throw logic_error(buffer.str());
    }

    const DataSet* data_set_pointer = loss_index_pointer->get_data_set_pointer();

    if(!data_set_pointer)
    {
        buffer << "OpenNN Exception: LevenbergMarquardtAlgorithm class." << endl
               << "void check() const method.\n"
               << "The loss funcional has no data set." << endl;

        throw logic_error(buffer.str());
    }

    const NeuralNetwork* neural_network_pointer = loss_index_pointer->get_neural_network_pointer();

    if(!neural_network_pointer)
    {
        buffer << "OpenNN Exception: LevenbergMarquardtAlgorithm class." << endl
               << "void check() const method.\n"
               << "Pointer to neural network is nullptr." << endl;

        throw logic_error(buffer.str());
    }
}


/// Trains a neural network with an associated loss index according to the Levenberg-Marquardt algorithm.
/// Training occurs according to the training parameters.

OptimizationAlgorithm::Results LevenbergMarquardtAlgorithm::perform_training()
{
    ostringstream buffer;

    // Control sentence

#ifdef __OPENNN_DEBUG__

    check();

#endif

    // Start training

    if(display) cout << "Training with Levenberg-Marquardt algorithm...\n";

    Results results;

    results.resize_training_history(maximum_epochs_number);

    // Data set

    DataSet* data_set_pointer = loss_index_pointer->get_data_set_pointer();

    const bool has_selection = data_set_pointer->has_selection();

    const Index training_instances_number = data_set_pointer->get_training_instances_number();
    const Index selection_instances_number = data_set_pointer->get_selection_instances_number();

    Tensor<Index, 1> training_instances_indices = data_set_pointer->get_training_instances_indices();
    Tensor<Index, 1> selection_instances_indices = data_set_pointer->get_selection_instances_indices();
    const Tensor<Index, 1> inputs_indices = data_set_pointer->get_input_variables_indices();
    const Tensor<Index, 1> target_indices = data_set_pointer->get_target_variables_indices();

    DataSet::Batch training_batch(training_instances_number, data_set_pointer);
    DataSet::Batch selection_batch(selection_instances_number, data_set_pointer);

    training_batch.fill(training_instances_indices, inputs_indices, target_indices);
    selection_batch.fill(selection_instances_indices, inputs_indices, target_indices);

    // Neural network

    NeuralNetwork* neural_network_pointer = loss_index_pointer->get_neural_network_pointer();

    const Index parameters_number = neural_network_pointer->get_parameters_number();

    const Index trainable_layers_number = neural_network_pointer->get_trainable_layers_number();

    NeuralNetwork::ForwardPropagation training_forward_propagation(training_instances_number, neural_network_pointer);
    NeuralNetwork::ForwardPropagation selection_forward_propagation(selection_instances_number, neural_network_pointer);

    Tensor<type, 1> parameters = neural_network_pointer->get_parameters();

    type parameters_norm = 0;

    // Loss index

    type training_loss = 0;
    type old_training_loss = 0;
    type training_loss_decrease = 0;

    type selection_error = 0;
    type old_selection_error = 0;

    Index selection_failures = 0;

    type gradient_norm = 0;

    LossIndex::BackPropagation training_back_propagation(training_instances_number, loss_index_pointer);
    LossIndex::BackPropagation selection_back_propagation(selection_instances_number, loss_index_pointer);

    LossIndex::SecondOrderLoss terms_second_order_loss(parameters_number, training_instances_number);

    // Training strategy stuff

    Tensor<type, 1> parameters_increment(parameters_number);
    type parameters_increment_norm;

    Tensor<type, 1> minimal_selection_parameters(parameters_number);
    type minimum_selection_error = numeric_limits<type>::max();

    bool stop_training = false;

    time_t beginning_time, current_time;
    time(&beginning_time);
    type elapsed_time = 0;

    // Main loop

    for(Index epoch = 1; epoch <= maximum_epochs_number; epoch++)
    {
        // Neural network

        parameters_norm = l2_norm(parameters);

        if(display && parameters_norm >= warning_parameters_norm)
        {
            cout << "OpenNN Warning: Parameters norm is " << parameters_norm << "." << endl;
        }

        // Neural Network

        neural_network_pointer->forward_propagate(training_batch, training_forward_propagation);

        // Loss index

        loss_index_pointer->calculate_terms_second_order_loss(training_batch, training_forward_propagation, training_back_propagation, terms_second_order_loss);

        training_loss = terms_second_order_loss.loss;

        // Update epoch

        gradient_norm = l2_norm(terms_second_order_loss.gradient);

        if(display && gradient_norm >= warning_gradient_norm)
        {
            cout << "OpenNN Warning: Gradient norm is " << gradient_norm << "." << endl;
        }

        do
        {
             terms_second_order_loss.sum_hessian_diagonal(damping_parameter);

             parameters_increment = perform_Householder_QR_decomposition(terms_second_order_loss.hessian,(-1.)*terms_second_order_loss.gradient);

             Tensor<type, 1> new_parameters = parameters + parameters_increment;

             neural_network_pointer->forward_propagate(training_batch, new_parameters, training_forward_propagation);

             loss_index_pointer->calculate_error(training_batch, training_forward_propagation, training_back_propagation);

             const type new_loss = training_back_propagation.error;

             if(new_loss <= training_loss) // succesfull step
             {
                 set_damping_parameter(damping_parameter/damping_parameter_factor);

                 parameters += parameters_increment;

                 neural_network_pointer->set_parameters(parameters);

                 training_loss = new_loss;

                break;
             }
             else
             {
                 terms_second_order_loss.sum_hessian_diagonal(-damping_parameter);

                 set_damping_parameter(damping_parameter*damping_parameter_factor);
             }
        }
        while(damping_parameter < maximum_damping_parameter);

        parameters_increment_norm = l2_norm(parameters_increment);

        if(epoch == 1)
        {
            training_loss_decrease = 0;
        }
        else
        {
            training_loss_decrease = training_loss - old_training_loss;
        }

        if(has_selection)
        {
          neural_network_pointer->forward_propagate(selection_batch, selection_forward_propagation);

          loss_index_pointer->calculate_error(selection_batch, selection_forward_propagation, selection_back_propagation);

          selection_error = selection_back_propagation.loss;
        }

        if(epoch == 0)
        {
            minimum_selection_error = selection_error;

            minimal_selection_parameters = neural_network_pointer->get_parameters();
        }
        else if(epoch != 0 && selection_error > old_selection_error)
        {
            selection_failures++;
        }
        else if(selection_error <= minimum_selection_error)
        {
            minimum_selection_error = selection_error;

            minimal_selection_parameters = neural_network_pointer->get_parameters();
        }

        // Elapsed time

        time(&current_time);
        elapsed_time = static_cast<type>(difftime(current_time, beginning_time));

        // Training history loss index

        if(reserve_training_error_history)
        {
            results.training_error_history(epoch) = training_loss;
        }

        if(reserve_selection_error_history)
        {
            results.selection_error_history(epoch) = selection_error;
        }

        // Stopping Criteria

//        parameters_increment_norm = 0;

        if(parameters_increment_norm <= minimum_parameters_increment_norm)
        {
            if(display)
            {
                cout << "Epoch " << epoch+1 << ": Minimum parameters increment norm reached.\n"
                     << "Parameters increment norm: " << parameters_increment_norm << endl;
            }

            stop_training = true;

            results.stopping_condition = MinimumParametersIncrementNorm;
        }

        else if(training_loss <= training_loss_goal)
        {
            if(display) cout << "Epoch " << epoch+1 << ": Loss goal reached.\n";

            stop_training = true;

            results.stopping_condition = LossGoal;
        }

        else if(epoch != 0 && training_loss_decrease >= minimum_loss_decrease)
        {
            if(display)
            {
                cout << "Epoch " << epoch+1 << ": Minimum loss decrease (" << minimum_loss_decrease << ") reached.\n"
                     << "Loss decrease: " << training_loss_decrease << endl;
            }

            stop_training = true;

            results.stopping_condition = MinimumLossDecrease;
        }

        else if(gradient_norm <= gradient_norm_goal)
        {
            if(display) cout << "Epoch " << epoch+1 << ": Gradient norm goal reached." << endl;

            stop_training = true;

            results.stopping_condition = GradientNormGoal;
        }

        else if(selection_failures >= maximum_selection_error_increases && apply_early_stopping)
        {
            if(display)
            {
                cout << "Epoch " << epoch+1 << ": Maximum selection error increases reached.\n"
                     << "Selection loss increases: "<< selection_failures << endl;
            }

            stop_training = true;

            results.stopping_condition = MaximumSelectionErrorIncreases;
        }

        else if(epoch == maximum_epochs_number)
        {
            if(display) cout << "Epoch " << epoch+1 << ": Maximum number of epochs reached." << endl;

            stop_training = true;

            results.stopping_condition = MaximumEpochsNumber;
        }

        else if(elapsed_time >= maximum_time)
        {
            if(display)
            {
                cout << "Epoch " << epoch+1 << ": Maximum training time reached." << endl;
            }

            stop_training = true;

            results.stopping_condition = MaximumTime;
        }

        if(epoch != 0 && epoch % save_period == 0)
        {
            neural_network_pointer->save(neural_network_file_name);
        }

        if(stop_training)
        {
            if(display)
            {
                cout << "Parameters norm: " << parameters_norm << "\n"
                     << "Training loss: " << training_loss << "\n"
                     << "Gradient norm: " << gradient_norm << "\n"
                     << loss_index_pointer->write_information()
                     << "Damping parameter: " << damping_parameter << "\n"
                     << "Elapsed time: " << write_elapsed_time(elapsed_time) << endl;

                if(has_selection)
                {
                    cout << "Selection error: " << selection_error << endl;
                }
            }

            results.resize_training_history(1+epoch);

            results.final_parameters = parameters;
            results.final_parameters_norm = parameters_norm;

            results.final_training_error = training_loss;
            results.final_selection_error = selection_error;

            results.final_gradient_norm = gradient_norm;

            results.elapsed_time = elapsed_time;

            results.epochs_number = epoch;

            break;
        }
        else if(display && epoch % display_period == 0)
        {
            cout << "Epoch " << epoch+1 << ";\n"
                 << "Parameters norm: " << parameters_norm << "\n"
                 << "Training loss: " << training_loss << "\n"
                 << "Gradient norm: " << gradient_norm << "\n"
                 << loss_index_pointer->write_information()
                 << "Damping parameter: " << damping_parameter << "\n"
                 << "Elapsed time: " << write_elapsed_time(elapsed_time) << endl;

            if(abs(selection_error - 0) < numeric_limits<type>::epsilon())
            {
                cout << "Selection error: " << selection_error << endl;
            }
        }

        // Update stuff

        old_training_loss = training_loss;
        old_selection_error = selection_error;
    }

    if(choose_best_selection)
    {
        parameters = minimal_selection_parameters;
        parameters_norm = l2_norm(parameters);

        neural_network_pointer->set_parameters(parameters);

        neural_network_pointer->forward_propagate(training_batch, training_forward_propagation);

        loss_index_pointer->back_propagate(training_batch, training_forward_propagation, training_back_propagation);

        training_loss = training_back_propagation.loss;

        selection_error = minimum_selection_error;
    }

    results.final_parameters = parameters;
    results.final_parameters_norm = parameters_norm;

    results.final_training_error = training_loss;
    results.final_selection_error = selection_error;

    results.final_gradient_norm = gradient_norm;

    results.elapsed_time = elapsed_time;

    return results;
}


void LevenbergMarquardtAlgorithm::perform_training_void()
{
    perform_training();
}


void LevenbergMarquardtAlgorithm::set_reserve_all_training_history(const bool&)
{
    reserve_training_error_history = true;
    reserve_selection_error_history = true;
}


string LevenbergMarquardtAlgorithm::write_optimization_algorithm_type() const
{
    return "LEVENBERG_MARQUARDT_ALGORITHM";
}


/// Writes as matrix of strings the most representative atributes.

Tensor<string, 2> LevenbergMarquardtAlgorithm::to_string_matrix() const
{
    ostringstream buffer;

    Tensor<string, 1> labels;
    Tensor<string, 1> values;
    /*
        // Damping parameter factor

        labels.push_back("Damping parameter factor");

        buffer.str("");
        buffer << damping_parameter_factor;

        values.push_back(buffer.str());

       // Minimum parameters increment norm

       labels.push_back("Minimum parameters increment norm");

       buffer.str("");
       buffer << minimum_parameters_increment_norm;

       values.push_back(buffer.str());

       // Minimum loss decrease

       labels.push_back("Minimum loss decrease");

       buffer.str("");
       buffer << minimum_loss_decrease;

       values.push_back(buffer.str());

       // Loss goal

       labels.push_back("Loss goal");

       buffer.str("");
       buffer << training_loss_goal;

       values.push_back(buffer.str());

       // Gradient norm goal

       labels.push_back("Gradient norm goal");

       buffer.str("");
       buffer << gradient_norm_goal;

       values.push_back(buffer.str());

       // Maximum selection error increases

       labels.push_back("Maximum selection error increases");

       buffer.str("");
       buffer << maximum_selection_error_increases;

       values.push_back(buffer.str());

       // Maximum iterations number

       labels.push_back("Maximum iterations number");

       buffer.str("");
       buffer << maximum_epochs_number;

       values.push_back(buffer.str());

       // Maximum time

       labels.push_back("Maximum time");

       buffer.str("");
       buffer << maximum_time;

       values.push_back(buffer.str());

       // Reserve training error history

       labels.push_back("Reserve training error history");

       buffer.str("");

       if(reserve_training_error_history)
       {
           buffer << "true";
       }
       else
       {
           buffer << "false";
       }

       values.push_back(buffer.str());

       // Reserve selection error history

       labels.push_back("Reserve selection error history");

       buffer.str("");

       if(reserve_selection_error_history)
       {
           buffer << "true";
       }
       else
       {
           buffer << "false";
       }

       values.push_back(buffer.str());


       const Index rows_number = labels.size();
       const Index columns_number = 2;

       Tensor<string, 2> string_matrix(rows_number, columns_number);

       string_matrix.set_column(0, labels, "name");
       string_matrix.set_column(1, values, "value");

        return string_matrix;
    */
    return Tensor<string, 2>();
}


tinyxml2::XMLDocument* LevenbergMarquardtAlgorithm::to_XML() const
{
    ostringstream buffer;

    tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

    // Optimization algorithm

    tinyxml2::XMLElement* root_element = document->NewElement("LevenbergMarquardtAlgorithm");
    document->InsertFirstChild(root_element);

    tinyxml2::XMLElement* element = nullptr;
    tinyxml2::XMLText* text = nullptr;

    // Damping parameter

//   element = document->NewElement("DampingParameter");
//   root_element->LinkEndChild(element);

//   buffer.str("");
//   buffer << damping_parameter;

//   text = document->NewText(buffer.str().c_str());
//   element->LinkEndChild(text);

    // Minimum damping parameter.

//   element = document->NewElement("MinimumDampingParameter");
//   root_element->LinkEndChild(element);

//   buffer.str("");
//   buffer << minimum_damping_parameter;

//   text = document->NewText(buffer.str().c_str());
//   element->LinkEndChild(text);

    // Maximum damping parameter.

//   element = document->NewElement("MaximumDampingParameter");
//   root_element->LinkEndChild(element);

//   buffer.str("");
//   buffer << maximum_damping_parameter;

//   text = document->NewText(buffer.str().c_str());
//   element->LinkEndChild(text);

    // Damping parameter factor.

    element = document->NewElement("DampingParameterFactor");
    root_element->LinkEndChild(element);

    buffer.str("");
    buffer << damping_parameter_factor;

    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Return minimum selection error neural network

    element = document->NewElement("ReturnMinimumSelectionErrorNN");
    root_element->LinkEndChild(element);

    buffer.str("");
    buffer << choose_best_selection;

    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Apply early stopping

    element = document->NewElement("ApplyEarlyStopping");
    root_element->LinkEndChild(element);

    buffer.str("");
    buffer << apply_early_stopping;

    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Warning parameters norm

//   element = document->NewElement("WarningParametersNorm");
//   root_element->LinkEndChild(element);

//   buffer.str("");
//   buffer << warning_parameters_norm;

//   text = document->NewText(buffer.str().c_str());
//   element->LinkEndChild(text);

    // Warning gradient norm

//   element = document->NewElement("WarningGradientNorm");
//   root_element->LinkEndChild(element);

//   buffer.str("");
//   buffer << warning_gradient_norm;

//   text = document->NewText(buffer.str().c_str());
//   element->LinkEndChild(text);

    // Error parameters norm

//   element = document->NewElement("ErrorParametersNorm");
//   root_element->LinkEndChild(element);

//   buffer.str("");
//   buffer << error_parameters_norm;

//   text = document->NewText(buffer.str().c_str());
//   element->LinkEndChild(text);

    // Error gradient norm

//   element = document->NewElement("ErrorGradientNorm");
//   root_element->LinkEndChild(element);

//   buffer.str("");
//   buffer << error_gradient_norm;

//   text = document->NewText(buffer.str().c_str());
//   element->LinkEndChild(text);

    // Minimum parameters increment norm

    element = document->NewElement("MinimumParametersIncrementNorm");
    root_element->LinkEndChild(element);

    buffer.str("");
    buffer << minimum_parameters_increment_norm;

    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Minimum loss decrease

    element = document->NewElement("MinimumLossDecrease");
    root_element->LinkEndChild(element);

    buffer.str("");
    buffer << minimum_loss_decrease;

    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Loss goal

    element = document->NewElement("LossGoal");
    root_element->LinkEndChild(element);

    buffer.str("");
    buffer << training_loss_goal;

    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Gradient norm goal

    element = document->NewElement("GradientNormGoal");
    root_element->LinkEndChild(element);

    buffer.str("");
    buffer << gradient_norm_goal;

    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Maximum selection error increases

    element = document->NewElement("MaximumSelectionErrorIncreases");
    root_element->LinkEndChild(element);

    buffer.str("");
    buffer << maximum_selection_error_increases;

    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Maximum iterations number

    element = document->NewElement("MaximumEpochsNumber");
    root_element->LinkEndChild(element);

    buffer.str("");
    buffer << maximum_epochs_number;

    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Maximum time

    element = document->NewElement("MaximumTime");
    root_element->LinkEndChild(element);

    buffer.str("");
    buffer << maximum_time;

    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Reserve training error history

    element = document->NewElement("ReserveTrainingErrorHistory");
    root_element->LinkEndChild(element);

    buffer.str("");
    buffer << reserve_training_error_history;

    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Reserve selection error history

    element = document->NewElement("ReserveSelectionErrorHistory");
    root_element->LinkEndChild(element);

    buffer.str("");
    buffer << reserve_selection_error_history;

    text = document->NewText(buffer.str().c_str());
    element->LinkEndChild(text);

    // Display period

//   element = document->NewElement("DisplayPeriod");
//   root_element->LinkEndChild(element);

//   buffer.str("");
//   buffer << display_period;

//   text = document->NewText(buffer.str().c_str());
//   element->LinkEndChild(text);

    // Save period
//   {
//       element = document->NewElement("SavePeriod");
//       root_element->LinkEndChild(element);

//       buffer.str("");
//       buffer << save_period;

//       text = document->NewText(buffer.str().c_str());
//       element->LinkEndChild(text);
//   }

    // Neural network file name
//   {
//       element = document->NewElement("NeuralNetworkFileName");
//       root_element->LinkEndChild(element);

//       text = document->NewText(neural_network_file_name.c_str());
//       element->LinkEndChild(text);
//   }

    // Display

//   element = document->NewElement("Display");
//   root_element->LinkEndChild(element);

//   buffer.str("");
//   buffer << display;

//   text = document->NewText(buffer.str().c_str());
//   element->LinkEndChild(text);

    return document;
}


/// Serializes the Levenberg Marquardt algorithm object into a XML document of the TinyXML library
/// without keep the DOM tree in memory.
/// See the OpenNN manual for more information about the format of this document.

void LevenbergMarquardtAlgorithm::write_XML(tinyxml2::XMLPrinter& file_stream) const
{
    ostringstream buffer;

    // Damping paramterer factor.

    file_stream.OpenElement("DampingParameterFactor");

    buffer.str("");
    buffer << damping_parameter_factor;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Return minimum selection error neural network
    {
        file_stream.OpenElement("ReturnMinimumSelectionErrorNN");

        buffer.str("");
        buffer << choose_best_selection;

        file_stream.PushText(buffer.str().c_str());

        file_stream.CloseElement();
    }

    // Apply early stopping

    {
        file_stream.OpenElement("ApplyEarlyStopping");

        buffer.str("");
        buffer << apply_early_stopping;

        file_stream.PushText(buffer.str().c_str());

        file_stream.CloseElement();
    }

    // Minimum parameters increment norm

    file_stream.OpenElement("MinimumParametersIncrementNorm");

    buffer.str("");
    buffer << minimum_parameters_increment_norm;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Minimum loss decrease

    file_stream.OpenElement("MinimumLossDecrease");

    buffer.str("");
    buffer << minimum_loss_decrease;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Loss goal

    file_stream.OpenElement("LossGoal");

    buffer.str("");
    buffer << training_loss_goal;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Gradient norm goal

    file_stream.OpenElement("GradientNormGoal");

    buffer.str("");
    buffer << gradient_norm_goal;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Maximum selection error increases

    file_stream.OpenElement("MaximumSelectionErrorIncreases");

    buffer.str("");
    buffer << maximum_selection_error_increases;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Maximum iterations number

    file_stream.OpenElement("MaximumEpochsNumber");

    buffer.str("");
    buffer << maximum_epochs_number;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Maximum time

    file_stream.OpenElement("MaximumTime");

    buffer.str("");
    buffer << maximum_time;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Reserve training error history

    file_stream.OpenElement("ReserveTrainingErrorHistory");

    buffer.str("");
    buffer << reserve_training_error_history;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Reserve selection error history

    file_stream.OpenElement("ReserveSelectionErrorHistory");

    buffer.str("");
    buffer << reserve_selection_error_history;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();
}


/// Loads a Levenberg-Marquardt method object from a XML document.
/// Please mind about the format, wich is specified in the OpenNN manual.
/// @param document TinyXML document containint the object data.

void LevenbergMarquardtAlgorithm::from_XML(const tinyxml2::XMLDocument& document)
{
    const tinyxml2::XMLElement* root_element = document.FirstChildElement("LevenbergMarquardtAlgorithm");

    if(!root_element)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: LevenbergMarquardtAlgorithm class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Levenberg-Marquardt algorithm element is nullptr.\n";

        throw logic_error(buffer.str());
    }

    // Damping parameter factor

    const tinyxml2::XMLElement* damping_parameter_factor_element
            = root_element->FirstChildElement("DampingParameterFactor");

    if(damping_parameter_factor_element)
    {
        const type new_damping_parameter_factor = static_cast<type>(atof(damping_parameter_factor_element->GetText()));

        try
        {
            set_damping_parameter_factor(new_damping_parameter_factor);
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }

    // Return minimum selection error neural network

    const tinyxml2::XMLElement* choose_best_selection_element
            = root_element->FirstChildElement("ReturnMinimumSelectionErrorNN");

    if(choose_best_selection_element)
    {
        const string new_choose_best_selection = choose_best_selection_element->GetText();

        try
        {
            set_choose_best_selection(new_choose_best_selection != "0");
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }

    // Apply early stopping

    const tinyxml2::XMLElement* apply_early_stopping_element = root_element->FirstChildElement("ApplyEarlyStopping");

    if(apply_early_stopping_element)
    {
        string new_apply_early_stopping = apply_early_stopping_element->GetText();

        try
        {
            set_apply_early_stopping(new_apply_early_stopping != "0");
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }

    // Minimum parameters increment norm

    const tinyxml2::XMLElement* minimum_parameters_increment_norm_element
            = root_element->FirstChildElement("MinimumParametersIncrementNorm");

    if(minimum_parameters_increment_norm_element)
    {
        const type new_minimum_parameters_increment_norm
                = static_cast<type>(atof(minimum_parameters_increment_norm_element->GetText()));

        try
        {
            set_minimum_parameters_increment_norm(new_minimum_parameters_increment_norm);
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }

    // Minimum loss decrease

    const tinyxml2::XMLElement* minimum_loss_decrease_element = root_element->FirstChildElement("MinimumLossDecrease");

    if(minimum_loss_decrease_element)
    {
        const type new_minimum_loss_decrease = static_cast<type>(atof(minimum_loss_decrease_element->GetText()));

        try
        {
            set_minimum_loss_decrease(new_minimum_loss_decrease);
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }

    // Loss goal

    const tinyxml2::XMLElement* loss_goal_element = root_element->FirstChildElement("LossGoal");

    if(loss_goal_element)
    {
        const type new_loss_goal = static_cast<type>(atof(loss_goal_element->GetText()));

        try
        {
            set_loss_goal(new_loss_goal);
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }

    // Gradient norm goal

    const tinyxml2::XMLElement* gradient_norm_goal_element = root_element->FirstChildElement("GradientNormGoal");

    if(gradient_norm_goal_element)
    {
        const type new_gradient_norm_goal = static_cast<type>(atof(gradient_norm_goal_element->GetText()));

        try
        {
            set_gradient_norm_goal(new_gradient_norm_goal);
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }

    // Maximum selection error increases

    const tinyxml2::XMLElement* maximum_selection_error_increases_element
            = root_element->FirstChildElement("MaximumSelectionErrorIncreases");

    if(maximum_selection_error_increases_element)
    {
        const Index new_maximum_selection_error_increases
                = static_cast<Index>(atoi(maximum_selection_error_increases_element->GetText()));

        try
        {
            set_maximum_selection_error_increases(new_maximum_selection_error_increases);
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }

    // Maximum epochs number

    const tinyxml2::XMLElement* maximum_epochs_number_element = root_element->FirstChildElement("MaximumEpochsNumber");

    if(maximum_epochs_number_element)
    {
        const Index new_maximum_epochs_number = static_cast<Index>(atoi(maximum_epochs_number_element->GetText()));

        try
        {
            set_maximum_epochs_number(new_maximum_epochs_number);
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }

    // Maximum time

    const tinyxml2::XMLElement* maximum_time_element = root_element->FirstChildElement("MaximumTime");

    if(maximum_time_element)
    {
        const type new_maximum_time = static_cast<type>(atof(maximum_time_element->GetText()));

        try
        {
            set_maximum_time(new_maximum_time);
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }

    // Reserve training error history

    const tinyxml2::XMLElement* reserve_training_error_history_element
            = root_element->FirstChildElement("ReserveTrainingErrorHistory");

    if(reserve_training_error_history_element)
    {
        const string new_reserve_training_error_history = reserve_training_error_history_element->GetText();

        try
        {
            set_reserve_training_error_history(new_reserve_training_error_history != "0");
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }

    // Reserve selection error history

    const tinyxml2::XMLElement* reserve_selection_error_history_element
            = root_element->FirstChildElement("ReserveSelectionErrorHistory");

    if(reserve_selection_error_history_element)
    {
        const string new_reserve_selection_error_history = reserve_selection_error_history_element->GetText();

        try
        {
            set_reserve_selection_error_history(new_reserve_selection_error_history != "0");
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }
}


/// Uses Eigen to solve the system of equations by means of the Householder QR decomposition.

Tensor<type, 1> LevenbergMarquardtAlgorithm::perform_Householder_QR_decomposition(const Tensor<type, 2>& A,
        const Tensor<type, 1>& b) const
{
    const Index n = A.dimension(0);

    Tensor<type, 1> x(n);

    const Map<Matrix<type, Dynamic, Dynamic>> A_eigen((type*)A.data(), n, n);

    const Map<Matrix<type, Dynamic, 1>> b_eigen((type*)b.data(), n, 1);

    Map<Matrix<type, Dynamic, 1>> x_eigen((type*)x.data(), n);

    x_eigen = A_eigen.colPivHouseholderQr().solve(b_eigen);

    return x;
}

}

// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2020 Artificial Intelligence Techniques, SL.
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
