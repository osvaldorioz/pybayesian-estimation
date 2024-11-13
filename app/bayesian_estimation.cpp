#include <iostream>
#include <vector>
#include <cmath>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

//g++ -O2 -Wall -shared -std=c++20 -fPIC `python3.12 -m pybind11 --includes` bayesian_estimation.cpp -o bayesian_estimation`python3.12-config --extension-suffix`


namespace py = pybind11;

class BayesianEstimator {
public:
    BayesianEstimator(double prior_mean, double prior_variance, double observation_variance)
        : prior_mean_(prior_mean), prior_variance_(prior_variance), observation_variance_(observation_variance) {}

    // Método para actualizar la estimación con una nueva observación
    void update(double observation) {
        // Cálculo de la media posterior y la varianza posterior
        double posterior_variance = 1 / ((1 / prior_variance_) + (1 / observation_variance_));
        double posterior_mean = posterior_variance * ((prior_mean_ / prior_variance_) + (observation / observation_variance_));

        // Actualizar los valores a los valores posteriores
        prior_mean_ = posterior_mean;
        prior_variance_ = posterior_variance;
    }

    double get_mean() const { return prior_mean_; }
    double get_variance() const { return prior_variance_; }

private:
    double prior_mean_;
    double prior_variance_;
    double observation_variance_;
};

PYBIND11_MODULE(bayesian_estimation, m) {
    py::class_<BayesianEstimator>(m, "BayesianEstimator")
        .def(py::init<double, double, double>(), py::arg("prior_mean"), py::arg("prior_variance"), py::arg("observation_variance"))
        .def("update", &BayesianEstimator::update, py::arg("observation"))
        .def("get_mean", &BayesianEstimator::get_mean)
        .def("get_variance", &BayesianEstimator::get_variance);
}
