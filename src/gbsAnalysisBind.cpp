#include <pybind11/pybind11.h>

namespace py = pybind11;

void gbs_bind_analysis(py::module &m);

PYBIND11_MODULE(analysis, m) {

    gbs_bind_analysis(m);

}