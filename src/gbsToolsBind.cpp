#include <pybind11/pybind11.h>
#include <gbs/curves>
#include <gbs/surfaces>
#include <gbs/bsctools.h>
#include <gbs/bsstools.h>

namespace py = pybind11;

void gbs_bind_curveTools(py::module &m);
void gbs_bind_surfaceTools(py::module &m);
void gbs_bind_discretize(py::module &m);

PYBIND11_MODULE(tools, m) {

    m.def("to_bscurve_3d",
            [](const gbs::BSCurve<double, 2> &crv,double z){return gbs::add_dimension(crv,z);},
            "Convert 2d curve to 3d curve",
            py::arg("crv"), py::arg("z") = 0.
    );
    m.def("to_bssurface_3d",
            [](const gbs::BSSurface<double, 2> &srf,double z){return gbs::add_dimension(srf,z);},
            "Convert 2d surface to 3d surface",
            py::arg("srf"), py::arg("z") = 0.
    );

    gbs_bind_curveTools(m);
    gbs_bind_surfaceTools(m);
    gbs_bind_discretize(m);

}