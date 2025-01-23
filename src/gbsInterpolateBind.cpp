#include <pybind11/pybind11.h>

namespace py = pybind11;

void gbs_bind_interp(py::module &m);
void gbs_bind_approx(py::module &m);

PYBIND11_MODULE(interpolate, m) {

    gbs_bind_interp(m);
    gbs_bind_approx(m);

}