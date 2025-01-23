#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

void gbs_bind_build_curve(py::module &m);
void gbs_bind_build_surface(py::module &m);

PYBIND11_MODULE(build, m) {

    gbs_bind_build_curve(m);
    gbs_bind_build_surface(m);

}