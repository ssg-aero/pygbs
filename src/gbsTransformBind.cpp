#include <pybind11/pybind11.h>
#include <gbs/curves>
#include <gbs/surfaces>
#include <gbs/bsctools.h>
#include <gbs/bsstools.h>

namespace py = pybind11;

void gbs_bind_transform(py::module &m);

PYBIND11_MODULE(transform, m) {

    gbs_bind_transform(m);

}