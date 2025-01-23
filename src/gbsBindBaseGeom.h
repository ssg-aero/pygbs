#pragma once

#include <format>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include <gbs/curves>
#include <gbs/surfaces>

namespace py = pybind11;

template <typename T, size_t dim>
void gbs_bind_base_geom(py::module &m)
{

    using namespace gbs;

    m.def("add", [](const point<T, dim> &v1, const point<T, dim> &v2)
          { return v1 + v2; }, "Add points/vector", py::arg("v1"), py::arg("v2"));
    m.def("sub", [](const point<T, dim> &v1, const point<T, dim> &v2)
          { return v1 - v2; }, "Substract points/vector", py::arg("v1"), py::arg("v2"));
    m.def("mult", [](T s, const point<T, dim> &v)
          { return s * v; }, "Add points/vector", py::arg("s"), py::arg("v"));

    if constexpr (dim == 3)
    {
        m.def("cross", [](const point<T, dim> &v1, const point<T, dim> &v2)
              { return v1 ^ v2; }, "Cross product points/vector", py::arg("v1"), py::arg("v2"));
    }
    if constexpr (dim == 2 || dim == 3)
    {
        m.def("angle", [](const point<T, dim> &v1, const point<T, dim> &v2)
              { return angle(v1, v2); }, "Angle between 2 vectors", py::arg("v1"), py::arg("v2"));
    }

    m.def("dot", [](const point<T, dim> &v1, const point<T, dim> &v2)
          { return v1 * v2; }, "Dot product points/vector", py::arg("v1"), py::arg("v2"));


    m.def("neg", [](const point<T, dim> &v)
          { return -1. * v; });

    m.def("adim", [](const point<T, dim> &v)
          { return v / norm(v); });

    m.def("norm", [](const point<T, dim> &v)
          { return norm(v); });

    m.def("dist", [](const point<T, dim> &a, const point<T, dim> &b)
          { return distance(a, b); });

    py::class_<Geom<T, dim>, std::shared_ptr<Geom<T, dim>>>(m, std::format("Geom{}d", dim).c_str());
}