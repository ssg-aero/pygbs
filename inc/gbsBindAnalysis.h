#pragma once

#include <format>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include <gbs/bscanalysis.h>


namespace py = pybind11;

template <typename T, size_t dim>
void gbs_bind_analysis(py::module &m)
{

    const size_t N_GAUSS_abs_curv{31};

    m.def("abs_curv",
        py::overload_cast<
            const gbs::Curve<T, dim> &, 
            size_t, 
            size_t
        >(&gbs::abs_curv<T, dim, N_GAUSS_abs_curv>),
        "Builds a function returning curve's parameter corresponding to the curvilinear abscissa",
        py::arg("crv"), 
        py::arg("n") = 30, 
        py::arg("p") = 3
    );

    m.def("abs_curv",
        py::overload_cast<
            const gbs::Curve<T, dim> &, 
            T, 
            T, 
            size_t, 
            size_t
        >(&gbs::abs_curv<T, dim, N_GAUSS_abs_curv>),
        "Builds a function returning curve's parameter corresponding to the curvilinear abscissa",
        py::arg("crv"), 
        py::arg("u1"), 
        py::arg("u2"), 
        py::arg("n") = 30, 
        py::arg("p") = 3
    );

    m.def("abs_curv_adaptive",
        py::overload_cast<
            const gbs::Curve<T, dim> &, 
            size_t, 
            size_t, 
            T
        >(&gbs::abs_curv_adaptive<T, dim, N_GAUSS_abs_curv>),
        "Builds a function returning curve's parameter corresponding to the curvilinear abscissa",
        py::arg("crv"), 
        py::arg("n") = 30, 
        py::arg("p") = 3, 
        py::arg("tolerance") = 0.001
    );

    m.def("abs_curv_adaptive",
        py::overload_cast<
            const gbs::Curve<T, dim> &, 
            T,
            T,
            size_t, 
            size_t, 
            T
        >(&gbs::abs_curv_adaptive<T, dim, N_GAUSS_abs_curv>),
        "Builds a function returning curve's parameter corresponding to the curvilinear abscissa",
        py::arg("crv"), 
        py::arg("u1"), 
        py::arg("u2"),
        py::arg("n") = 30, 
        py::arg("p") = 3, 
        py::arg("tolerance") = 0.001
    );

    const size_t n_int_pt{100};
    const size_t n_int_fast_pt{15};
    m.def("length",
            py::overload_cast<
                const gbs::Curve<T,dim> &, 
                size_t, 
                bool
            >(&gbs::length<T,dim,n_int_pt>),
            // "Precise curve length using "+std::to_string( n_int_pt )+" gauss integration points",
            std::format("Precise curve length using {} gauss integration points", n_int_pt).c_str(),
            py::arg("crv"),
            py::arg("d")=0, 
            py::arg("adaptive")=false
    );

    m.def("length",
        py::overload_cast<
            const gbs::Curve<T,dim> &, 
            T,
            T,
            size_t, 
            bool
        >(&gbs::length<T,dim,n_int_pt>),
        // "Precise curve length using "+std::to_string( n_int_pt )+" gauss integration points",
        std::format("Precise curve length using {} gauss integration points", n_int_pt).c_str(),
        py::arg("crv"),
        py::arg("u1"),
        py::arg("u2"),
        py::arg("d")=0, 
        py::arg("adaptive")=false
    );

    m.def("length_fast",
        py::overload_cast<
            const gbs::Curve<T,dim> &, 
            size_t, 
            bool
        >(&gbs::length<T,dim,n_int_fast_pt>),
        std::format("Fast curve length using {} gauss integration points", n_int_fast_pt).c_str(),
        py::arg("crv"),
        py::arg("d")=0,
        py::arg("adaptive")=false
    );

    m.def("length_fast",
        py::overload_cast<
            const gbs::Curve<T,dim> &, 
            T,
            T,
            size_t, 
            bool
        >(&gbs::length<T,dim,n_int_fast_pt>),
        std::format("Fast curve length using {} gauss integration points", n_int_fast_pt).c_str(),
        py::arg("crv"),
        py::arg("u1"),
        py::arg("u2"),
        py::arg("d")=0,
        py::arg("adaptive")=false
    );

    m.def("length_adaptive_15",
        py::overload_cast<
            const gbs::Curve<T,dim> &, 
            size_t, 
            bool
        >(&gbs::length<T,dim,15>),
        "Adap curve length using 15 gauss_kronrods integration points",
        py::arg("crv"),
        py::arg("d")=0, 
        py::arg("adaptive")=true
    );

    m.def("length_adaptive_15",
        py::overload_cast<
            const gbs::Curve<T,dim> &, 
            T, 
            T, 
            size_t, 
            bool
        >(&gbs::length<T,dim,15>),
        "Adap curve length using 15 gauss_kronrods integration points between u1 and u2",
        py::arg("crv"),
        py::arg("u1"),
        py::arg("u2"),
        py::arg("d")=0, 
        py::arg("adaptive")=true
    );

    m.def("length_adaptive_31",
        py::overload_cast<
            const gbs::Curve<T,dim> &, 
            size_t, 
            bool
        >(&gbs::length<T,dim,31>),
        "Adap curve length using 31 gauss_kronrods integration points",
        py::arg("crv"),
        py::arg("d")=0, 
        py::arg("adaptive")=true
    );

    m.def("length_adaptive_31",
        py::overload_cast<
            const gbs::Curve<T,dim> &, 
            T, 
            T, 
            size_t, 
            bool
        >(&gbs::length<T,dim,31>),
        "Adap curve length using 31 gauss_kronrods integration points between u1 and u2",
        py::arg("crv"),
        py::arg("u1"),
        py::arg("u2"),
        py::arg("d")=0, 
        py::arg("adaptive")=true
    );

    if constexpr (dim == 2 || dim == 3)
    {
        m.def("normal_direction",
            py::overload_cast<const gbs::Curve<T,dim> &, T>(&gbs::normal_direction<T>),
            "Curve normal direction at given parameter",
            py::arg("crv"),py::arg("u")
        );

        m.def("tangential_direction",
                py::overload_cast<const gbs::Curve<T,dim> &, T>(&gbs::tangential_direction<T,dim>),
                "Curve tangential direction at given parameter",
                py::arg("crv"),py::arg("u")
        );
    }
}