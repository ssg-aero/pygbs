#include "gbsBindTransform.h"

void gbs_bind_transform(py::module &m)
{
        gbs_bind_transform<double,1>(m);
        gbs_bind_transform<double,2>(m);
        gbs_bind_transform<double,3>(m);

}