#include "gbsBindAnalysis.h"

void gbs_bind_analysis(py::module &m)
{

    using T = double;

    // m.def("compute_rolling_ball",
    //         py::overload_cast<const gbs::Curve<double,2> &, const gbs::Curve<double,2> &, double>(&gbs::compute_rolling_ball<double>),
    //         "Compute the rolling ball contact point between two 2D curves crv1 and crv2 given a parameter value u1.\n\nThe function returns a tuple containing three values:\n\t- The parameter value u2 representing the position on crv2 where the rolling ball contact occurs.\n\t- The 2D point representing the rolling ball contact point, calculated as the average of the corresponding points on crv1 and crv2.\n\t- A boolean value indicating whether the rolling ball contact is a special case where the curves are parallel at the contact point (true for parallel, false otherwise)",
    //         py::arg("crv1"), py::arg("crv2"), py::arg("u1")
    // );

    gbs_bind_analysis<T, 1>(m);
    gbs_bind_analysis<T, 2>(m);
    gbs_bind_analysis<T, 3>(m);

}