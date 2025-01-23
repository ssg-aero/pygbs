#include "gbsBindBasisFunctions.h"

void gbs_bind_basis_function(py::module &m)
{
    using T = double;

    m.def("basis_function",
            py::overload_cast<
            T,
            size_t,
            size_t,
            size_t,
            const std::vector<T> &
            >(&gbs::basis_function<T>),
            "BSpline basis function",
            py::arg("u"),
            py::arg("i"),
            py::arg("p"),
            py::arg("d"),
            py::arg("k")
    );

    m.def("unflat_knots",
            py::overload_cast<const std::vector<T> &>(&gbs::unflat_knots<T>),
            "Get unique knots and theire multiplicities",
            py::arg("knots_flat")
    );

    m.def("flat_knots",
            py::overload_cast<const std::vector<T> &, const std::vector<size_t>& >(&gbs::flat_knots<T, size_t>),
            "Get flat knots",
            py::arg("knots"),
            py::arg("mults")
    );

    m.def("build_simple_mult_flat_knots",
            py::overload_cast<T, T, size_t, size_t>(&gbs::build_simple_mult_flat_knots<T>),
            "Build simple multiplicity flat knots.",
            py::arg("u1"), py::arg("u2"), py::arg("n_poles"), py::arg("degree")
    );
    m.def("build_simple_mult_flat_knots",
            py::overload_cast<const std::vector<T> &, size_t>(&gbs::build_simple_mult_flat_knots<T>),
            "Build simple multiplicity flat knots.",
            py::arg("u"), py::arg("degree")
    );
    m.def("knots_and_mults",
            py::overload_cast<const std::vector<T> &>(&gbs::knots_and_mults<T>),
            "Extract knots and multiplicity from flat knots",
            py::arg("flat_knots")
    );

    gbs_bind_basis_function<T,1>(m);
    gbs_bind_basis_function<T,2>(m);
    gbs_bind_basis_function<T,3>(m);

}