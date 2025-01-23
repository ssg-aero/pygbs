#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

void gbs_bind_base_geom(py::module &m);
void gbs_bind_curves(py::module &m);
void gbs_bind_surfaces(py::module &m);

PYBIND11_MODULE(core, m) {

    gbs_bind_base_geom(m);
    gbs_bind_curves(m);
    gbs_bind_surfaces(m);

}