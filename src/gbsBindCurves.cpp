#include "gbsBindCurves.h"
#include <gbs-io/tojson.h>
#include <pybind11/functional.h>

void gbs_bind_curves(py::module &m)
{
        gbs_bind_curves<double,1>(m);
        gbs_bind_curves<double,2>(m);
        gbs_bind_curves<double,3>(m);

        // Offsest without direction only have sense in 2d
        py::class_<
                gbs::CurveOffset2D<double, gbs::BSCfunction<double>>, 
                std::shared_ptr<gbs::CurveOffset2D<double, gbs::BSCfunction<double>>>, 
                gbs::CurveOffset<double, 2, gbs::BSCfunction<double>>
        >(m, "CurveOffset2d_bs")
        .def(py::init<const std::shared_ptr<gbs::Curve<double, 2>> &, const gbs::BSCfunction<double> &>())
        .def("basisCurve", &gbs::CurveOffset2D<double, gbs::BSCfunction<double>>::basisCurve)
        .def("offset", &gbs::CurveOffset2D<double, gbs::BSCfunction<double>>::offset)
        .def("__copy__", [](const gbs::CurveOffset2D<double, gbs::BSCfunction<double>> &self)
                { return gbs::CurveOffset2D<double, gbs::BSCfunction<double>>(self); })
        .def("__repr__", [](const gbs::CurveOffset2D<double, gbs::BSCfunction<double>> &self)
                { return build_rep(self); });

        py::class_<
                gbs::CurveOffset2D<double, std::function<double(double, size_t)>>, 
                std::shared_ptr<gbs::CurveOffset2D<double, std::function<double(double, size_t)>>>, 
                gbs::CurveOffset<double, 2, std::function<double(double, size_t)>>
        >(m, "CurveOffset2d_func")
            .def(py::init<const std::shared_ptr<gbs::Curve<double, 2>> &, const std::function<double(double, size_t)> &>())
            .def("basisCurve", &gbs::CurveOffset2D<double, std::function<double(double, size_t)>>::basisCurve)
            .def("offset", &gbs::CurveOffset2D<double, std::function<double(double, size_t)>>::offset)
        .def("__copy__", [](const gbs::CurveOffset2D<double, std::function<double(double, size_t)>> &self)
                { return gbs::CurveOffset2D<double, std::function<double(double, size_t)>>(self); });

        py::class_<
                gbs::CurveOffset3D<double, gbs::BSCfunction<double>>, 
                std::shared_ptr<gbs::CurveOffset3D<double, gbs::BSCfunction<double>>>, 
                gbs::CurveOffset<double, 3, gbs::BSCfunction<double>>
        >(m, "CurveOffset3d_bs")
        .def(py::init<const std::shared_ptr<gbs::Curve<double, 3>> &, const gbs::BSCfunction<double> &, const std::array<double,3>&>())
        .def("basisCurve", &gbs::CurveOffset3D<double, gbs::BSCfunction<double>>::basisCurve)
        .def("offset", &gbs::CurveOffset3D<double, gbs::BSCfunction<double>>::offset)
        .def("direction", &gbs::CurveOffset3D<double, gbs::BSCfunction<double>>::direction)
        .def("__copy__", [](const gbs::CurveOffset3D<double, gbs::BSCfunction<double>> &self)
                { return gbs::CurveOffset3D<double, gbs::BSCfunction<double>>(self); })
        .def("__repr__", [](const gbs::CurveOffset3D<double, gbs::BSCfunction<double>> &self)
                { return build_rep(self); })
        ;

        py::class_<gbs::BSCfunction<double>>(m,"BSCfunction")
                .def(py::init<const gbs::BSCfunction<double> &>())
                .def(py::init<const BSCurve<double,1> &>())
                .def(py::init<const std::vector<std::array<double, 1>> &, const std::vector<double> &, size_t >(),
                        py::arg("poles"),py::arg("knotsFlats"),py::arg("degree"))
                .def(py::init<const std::vector<double> &, const std::vector<double> &, size_t >(),
                        py::arg("poles"),py::arg("knotsFlats"),py::arg("degree"))
                .def(py::init<const std::vector<double> &, const std::vector<double> &, const std::vector<size_t> &, size_t >(),
                        py::arg("poles"), py::arg("knots"), py::arg("mults"), py::arg("degree"))
                .def("value",&gbs::BSCfunction<double>::value,"Function evaluation at given parameter",py::arg("u"),py::arg("d") = 0)
                .def("basisCurve",&gbs::BSCfunction<double>::basisCurve )
                .def("bounds",&gbs::BSCfunction<double>::bounds )
                .def("changeBounds",py::overload_cast<double, double>(&gbs::BSCfunction<double>::changeBounds))
                .def("changeBounds",py::overload_cast<const std::array<double,2>&>(&gbs::BSCfunction<double>::changeBounds))
                .def("__call__",&gbs::BSCfunction<double>::operator(),"Function evaluation at given parameter",py::arg("u"),py::arg("d") = 0)
                // .def("__reduce__", [](gbs::BSCfunction<double> const &self) { // for pickle https://github.com/pybind/pybind11/issues/1261
                //         return py::make_tuple(py::cpp_function([](){return gbs::BSCfunction<double>();}), py::make_tuple());
                // })
                .def(py::pickle(
                        [](const gbs::BSCfunction<double> &f) {
                                auto crv = f.basisCurve();
                                return py::make_tuple(
                                                crv.poles(),
                                                crv.knots(),
                                                crv.mults(),
                                                crv.degree()
                                        );
                                },
                        [](py::tuple t){
                                if (t.size() != 4)
                                        throw std::runtime_error("Invalid state!");
                                gbs::BSCurve<double,1> crv{
                                        t[0].cast<std::vector<std::array<double,1>>>(),
                                        t[1].cast<std::vector<double>>(),
                                        t[2].cast<std::vector<size_t>>(),
                                        t[3].cast<size_t>()
                                };
                                return gbs::BSCfunction<double>{crv};
                        }
                ))
                .def("__copy__",  [](const  gbs::BSCfunction<double> &self) {
                        return  gbs::BSCfunction<double>(self);
                })
                .def("__repr__", [](const BSCfunction<double> &self) { return build_rep( self ); } )
                ;

        py::class_<Circle2d<double>, std::shared_ptr<Circle2d<double>>, Curve<double,2>>(m,"Circle2d")
        .def(py::init<const Circle2d<double> &>())
        .def(py::init<double, const point<double, 2> &>(), py::arg("r") = 1., py::arg("C") = point<double,2>{0.,0.})
        .def("value",&Circle2d<double>::value,"Circle evaluation at given angle",py::arg("u"),py::arg("d") = 0)
        ;

        py::class_<Circle3d<double>, std::shared_ptr<Circle3d<double>>, Curve<double,3> >(m,"Circle3d")
        .def(py::init<const Circle3d<double> &>())
        .def(py::init<double, const ax2<double, 3> &>(), py::arg("r") , py::arg("ax"))
        .def(py::init<double, const ax1<double, 3> &>(), py::arg("r") = 1., py::arg("ax")=ax1<double, 3>{point<double,3>{0.,0.,0.},point<double,3>{0.,0.,1.}})
        .def("value",&Circle3d<double>::value,"Circle evaluation at given angle",py::arg("u"),py::arg("d") = 0)
        ;
}