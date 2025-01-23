#pragma once

#include <format>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include <gbs/curves>
#include <gbs/surfaces>
#include <gbs/transform.h>

namespace py = pybind11;

template <typename T, size_t dim>
void gbs_bind_transform(py::module &m)
{
      m.def("translate",
            py::overload_cast<gbs::BSCurve<T, dim> &, const std::array<T, dim> &>(&gbs::translate<T, dim>),
            "Translate geom",
            py::arg("crv"), py::arg("vec"));

      m.def("translated",
            py::overload_cast<const std::array<T, dim> &, const std::array<T, dim> &>(&gbs::translated<T, dim>),
            "Translate geom",
            py::arg("pt"), py::arg("vec")); 

      m.def("scaled",
            py::overload_cast<const gbs::point<T,dim> &, T, gbs::point<T,dim> >(&gbs::scaled<T,dim>),
            py::arg("pt"), py::arg("s"), py::arg("center")=gbs::point<T,dim>{});

      m.def("scale",
            py::overload_cast<gbs::point<T,dim> &, T, gbs::point<T,dim> >(&gbs::scale<T,dim>),
            py::arg("pt"), py::arg("s"), py::arg("center")=gbs::point<T,dim>{});

      m.def("scale",
            py::overload_cast<gbs::BSCurve<T,dim> &, T, gbs::point<T,dim> >(&gbs::scale<T,dim>),
            py::arg("crv"), py::arg("s"), py::arg("center")=gbs::point<T,dim>{});

      m.def("scale",
            py::overload_cast<gbs::BSSurface<T,dim> &, T, gbs::point<T,dim> >(&gbs::scale<T,dim>),
            py::arg("srf"), py::arg("s"), py::arg("center")=gbs::point<T,dim>{});

      if constexpr ( dim == 2 )
      {
            m.def("rotate",
                  py::overload_cast<gbs::point<T, 2> &, T,const gbs::point<T, 2>&>(&gbs::rotate<T,2>),
                  "Rotate geom",
                  py::arg("pt"), py::arg("angle"), py::arg("center")= gbs::point<T, 2>{0.,0.});

            m.def("rotated",
                  py::overload_cast<const gbs::point<T, 2> &, T,const gbs::point<T, 2>&>(&gbs::rotated<T,2>),
                  "Rotate geom",
                  py::arg("pt"), py::arg("angle"), py::arg("center")= gbs::point<T, 2>{0.,0.});

            m.def("rotate",
                  py::overload_cast<gbs::BSCurve<T, 2> &, T>(&gbs::rotate<gbs::BSCurve<T, 2>, T>),
                  "Rotate geom",
                  py::arg("crv"), py::arg("angle"));

      }
      if constexpr ( dim == 3 )
      {
            m.def("rotated",
                  py::overload_cast<const gbs::point<T, dim> &, T,const std::array<T, dim>&>(&gbs::rotated<T>),
                  "Rotate geom",
                  py::arg("pt"), py::arg("angle"), py::arg("ax")= gbs::point<T, dim>{0.,0.,1.});

            m.def("rotate",
                  py::overload_cast<gbs::BSCurve<T, dim> &, T, const std::array<T, dim> &>(&gbs::rotate<gbs::BSCurve<T, dim>, T>),
                  "Rotate geom",
                  py::arg("crv"), py::arg("angle"), py::arg("axis"));

            m.def("rotate",
                  py::overload_cast<gbs::BSSurface<T, dim> &, T, const std::array<T, dim> &>(&gbs::rotate<gbs::BSSurface<T, dim>, T>),
                  "Rotate geom",
                  py::arg("srf"), py::arg("angle"), py::arg("axis"));
      }
}