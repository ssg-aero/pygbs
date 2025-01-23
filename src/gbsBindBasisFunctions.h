#pragma once

#include <format>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include <gbs/curves>

namespace py = pybind11;

template <typename T, size_t dim>
void gbs_bind_basis_function(py::module &m)
{
    m.def("eval",
            py::overload_cast<
                    T,
                    const std::vector<T> &,
                    const gbs::points_vector<T, dim> &,
                    size_t,
                    size_t,
                    bool
            >(&gbs::eval_value_decasteljau<T,dim>),
            "Non rational BSplineCurve evaluation",
            py::arg("u"), py::arg("knots_flat"), py::arg("poles"), py::arg("degree"), py::arg("derivative") = 0, py::arg("use_span_reduction") = true
    );

    m.def("eval", 
        [](
            T u, 
            const std::vector<T> &k, 
            const std::vector<std::array<T, dim>> &poles, 
            const std::vector<T> &weights, size_t p, 
            size_t d = 0, 
            bool use_span_reduction = true
        )
        { return gbs::eval_rational_value_simple<T, dim>(u, k, gbs::add_weights_coord(poles, weights), p, d, use_span_reduction); },
        "Rational BSplineCurve evaluation", 
        py::arg("u"), 
        py::arg("knots_flat"), 
        py::arg("poles"), 
        py::arg("weights"), 
        py::arg("degree"), 
        py::arg("derivative") = 0, 
        py::arg("use_span_reduction") = true
    );

    m.def("eval",
        py::overload_cast<
                T,
                T,
                const std::vector<T> &,
                const std::vector<T> &,
                const gbs::points_vector<T, dim> &,
                size_t,
                size_t,
                size_t,
                size_t
        >(&gbs::eval_value_decasteljau<T,dim>),
        "Non rational BSplineSurface evaluation",
        py::arg("u"), 
        py::arg("v"), 
        py::arg("ku"), 
        py::arg("kv"), 
        py::arg("poles"), 
        py::arg("degreeU"), 
        py::arg("degreeV"), 
        py::arg("du") = 0, 
        py::arg("dv") = 0
    );
}