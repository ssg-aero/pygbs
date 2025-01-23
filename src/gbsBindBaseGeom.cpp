#include "gbsBindBaseGeom.h"

void gbs_bind_base_geom(py::module &m)
{
        gbs_bind_base_geom<double,1>(m);
        gbs_bind_base_geom<double,2>(m);
        gbs_bind_base_geom<double,3>(m);

}