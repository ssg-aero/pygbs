# PyGbs is the new binding of GBS
The original c++ project can be found at:
https://github.com/ssg-aero/gbs

## Introduction

### Py Gbs is fast.

Compared to scipy interpolation PyGbs runs roughly 10x faster.
``` python
import numpy as np
from scipy.interpolate import CubicSpline
x = np.arange(10)
y = np.sin(x)
```
``` python
from pygbs import core
from pygbs import interpolate

points = [[x_, y_] for x_, y_ in zip(x, y)]
```
``` python
%%timeit
cs = CubicSpline(x, y)
```
86.8 μs ± 3.41 μs per loop (mean ± std. dev. of 7 runs, 10,000 loops each)
``` python
%%timeit
crv = interpolate.interpolate_cn(points, 3)
```
14.8 μs ± 406 ns per loop (mean ± std. dev. of 7 runs, 100,000 loops each)
### Object oriented

### Implements most of the NURBS's Book algorythm

## Examples

### Direct curves creation
``` python
from pygbs import core

    poles = [
        [0.,0.,0.], # Pole 1 [x, y, z]
        [1.,0.,0.], # Pole 2 [x, y, z]
    ]
    knots          = [0.0, 1.0] # Curve parametrization
    multiplicities = [1, 1]
    degree         = 1
    curve = core.BSCurve3d(
        poles,
        knots,
        multiplicities,
        degree
    )

    point = crv(0.5)

```
### Points interpolation

For instance point interpolation with tangency control:
``` python
from pygbs.core import BSCurve2d
from pygbs.interpolate import interpolate_c1
from pygbs.plotlyplot import plot_bs_curve_2d

constraints = [
    [ [0.,0.], [0., 1.] ], # [ [x0, y0], [dx0/du, dy0/du] ]
    [ [1.,0.], [0.,-2.] ], # [ [x1, y1], [dx1/du, dy1/du] ]
]

curve = interpolate_c1(constraints)

plot_bs_curve_2d(curve)
```
!["Interpolation"](https://raw.githubusercontent.com/ssg-aero/pygbs/master/docs/images/simple_interpolation.png )

### Points approximation

``` python
# Create points
import requests

foil_name = 'e1098'
url = f"http://airfoiltools.com/airfoil/seligdatfile?airfoil={foil_name}-il"

response = requests.get(url)
lines = response.text.split("\n")
lines .pop(0)
lines .pop(-1)

points = [ list(map(float, line.split())) for line in lines]
# Create an approximation of degree 3
from pygbs import core
from pygbs import interpolate

curve = interpolate.approx(
    points,
    deg=3
)
```

The green dots are representing the foil's points and the purple ones the control points of the approximating curve.
!["Points approximation"](https://raw.githubusercontent.com/ssg-aero/pygbs/master/docs/images/foilApprox.png "Points approximation example on a airfoil")

A closer look shows the benefit of approximation on stiff interpolation, in the case of a poorly discretized profile the algorythm is able to produce a smooth curve.

!["Points approximation"](https://raw.githubusercontent.com/ssg-aero/pygbs/master/docs/images/foilApproxZoom.png "Points approximation example on a airfoil")