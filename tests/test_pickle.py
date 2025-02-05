import copy
from math import pi
import pytest
import pickle
import numpy as np
from pygbs.core import( 
    BSCurve2d, 
    BSCurve3d, 
    BSCurveRational2d,
    BSSurface3d,
    BSSurfaceRational3d,
    CurveOnSurface3d,
    BSCfunction,
    BSSfunction,
    CurveOffset2d_bs,
    CurveOffset2d_func,
    CurveOffset3d_bs,
    Circle2d,
    Circle3d,
    Line2d,
    SurfaceOfRevolution,
)

def test_bs_curve():

    crv2d = BSCurve2d(
        [[0., 0.],[0., 1.]],
        [0., 1.],
        [2, 2],
        1
    )

    crv2d_pickled = pickle.dumps(crv2d)
    crv2d_new = pickle.loads(crv2d_pickled)

    np.testing.assert_allclose(np.array(crv2d_new.poles()), np.array(crv2d.poles()))
    np.testing.assert_allclose(np.array(crv2d_new.knots()), np.array(crv2d.knots()))
    np.testing.assert_allclose(np.array(crv2d_new.mults()), np.array(crv2d.mults()))
    np.testing.assert_allclose(np.array(crv2d_new.degree()), np.array(crv2d.degree()))

    crv2d = BSCurveRational2d(
        [[0., 0.],[0., 1.]],
        [0., 1.],
        [2, 2],
        [1., 0.8],
        1
    )

    crv2d_pickled = pickle.dumps(crv2d)
    crv2d_new = pickle.loads(crv2d_pickled)

    np.testing.assert_allclose(np.array(crv2d_new.poles()), np.array(crv2d.poles()))
    np.testing.assert_allclose(np.array(crv2d_new.knots()), np.array(crv2d.knots()))
    np.testing.assert_allclose(np.array(crv2d_new.mults()), np.array(crv2d.mults()))
    np.testing.assert_allclose(np.array(crv2d_new.weights()), np.array(crv2d.weights()))
    np.testing.assert_allclose(np.array(crv2d_new.degree()), np.array(crv2d.degree()))


def assert_curve_all_close(crv1, crv2, u1=0., u2 = 1., n = 100):

    u_lst = np.linspace(u1, u2, n)
    pts1  = crv1(u_lst)
    pts2  = crv2(u_lst)

    np.testing.assert_allclose(pts1, pts2)

def assert_surface_all_close(srf1, srf2, u1=0., u2 = 1., v1=0., v2 = 1., n = 100):

    u_lst = np.linspace(u1, u2, n)
    v_lst = np.linspace(v1, v2, n)
    pts1  = srf1(u_lst, v_lst)
    pts2  = srf2(u_lst, v_lst)

    np.testing.assert_allclose(pts1, pts2)

def test_surface_curve():

    crv2d = BSCurve2d(
        [[0., 0.3],[0., .7]],
        [0., 1.],
        [2, 2],
        1
    )

    srf3d = BSSurface3d(
        [
            [0., 0., 0],[0., 1., 0],
            [1., 0., 1],[1., 1., 1],
        ],
        [0., 1.],
        [0., 1.],
        [2, 2],
        [2, 2],
        1,
        1
    )

    crv3d = CurveOnSurface3d(crv2d, srf3d)
    crv3d_pickled = pickle.dumps(crv3d)
    crv3d_new = pickle.loads(crv3d_pickled)

    assert_curve_all_close(crv3d, crv3d_new)


def test_bsfunction():
    law        = BSCfunction([0., 0.1, 0.], [0., 1.], [3, 3], 2)
    law_pickle = pickle.dumps(law)
    law_new    = pickle.loads(law_pickle)

    np.testing.assert_allclose(np.array(law_new.basisCurve().poles()), np.array(law.basisCurve().poles()))
    np.testing.assert_allclose(np.array(law_new.basisCurve().knots()), np.array(law.basisCurve().knots()))
    np.testing.assert_allclose(np.array(law_new.basisCurve().mults()), np.array(law.basisCurve().mults()))
    np.testing.assert_allclose(np.array(law_new.basisCurve().degree()), np.array(law.basisCurve().degree()))

    law        = BSSfunction(
        [ 0., 0.1, 0.,
          0.,-0.1, 0.], 
        [0., 1.], 
        [0., 1.], 
        [3, 3],
        [2, 2],  
        2,
        1
    )
    law_pickle = pickle.dumps(law)
    law_new    = pickle.loads(law_pickle)

    np.testing.assert_allclose(np.array(law_new.basisSurface().poles()), np.array(law.basisSurface().poles()))
    np.testing.assert_allclose(np.array(law_new.basisSurface().knotsU()), np.array(law.basisSurface().knotsU()))
    np.testing.assert_allclose(np.array(law_new.basisSurface().knotsV()), np.array(law.basisSurface().knotsV()))
    np.testing.assert_allclose(np.array(law_new.basisSurface().multsU()), np.array(law.basisSurface().multsU()))
    np.testing.assert_allclose(np.array(law_new.basisSurface().multsV()), np.array(law.basisSurface().multsV()))
    np.testing.assert_allclose(np.array(law_new.basisSurface().degreeU()), np.array(law.basisSurface().degreeU()))
    np.testing.assert_allclose(np.array(law_new.basisSurface().degreeV()), np.array(law.basisSurface().degreeV()))

def test_offset_curve():

    law = BSCfunction([0., 0.1, 0.], [0., 1.], [3, 3], 2)
    crv2d = BSCurve2d(
        [[0., 0.],[0., 1.]],
        [0., 1.],
        [2, 2],
        1
    )

    offset2d         = CurveOffset2d_bs( crv2d, law )
    offset2d_pickled = pickle.dumps(offset2d)
    offset2d_new     = pickle.loads(offset2d_pickled)

    assert_curve_all_close( offset2d, offset2d_new)


    # cst_law = lambda u : 0.1
    # crv2d = BSCurve2d(
    #     [[0., 0.],[0., 1.]],
    #     [0., 1.],
    #     [2, 2],
    #     1
    # )

    # offset2d         = CurveOffset2d_func( crv2d, cst_law )
    # offset2d_pickled = pickle.dumps(offset2d)
    # offset2d_new     = pickle.loads(offset2d_pickled)

    # assert_curve_all_close( offset2d, offset2d_new)


    law = BSCfunction([0., 0.1, 0.], [0., 1.], [3, 3], 2)
    crv3d = BSCurve3d(
        [[0., 0., 0,],[0., 1., 1.]],
        [0., 1.],
        [2, 2],
        1
    )

    offset3d         = CurveOffset3d_bs( crv3d, law, [0.,0.,1.] )
    offset3d_pickled = pickle.dumps(offset3d)
    offset3d_new     = pickle.loads(offset3d_pickled)

    assert_curve_all_close( offset3d, offset3d_new)

    offset3d_new = copy.deepcopy(offset3d)

    assert_curve_all_close( offset3d, offset3d_new)

def test_base_curves():

    circle2d        = Circle2d(0.3, [0., 1.])
    circle2d_pickle = pickle.dumps(circle2d)
    circle2d_new    = pickle.loads(circle2d_pickle)

    assert circle2d_new.r() == pytest.approx(circle2d.r())
    assert circle2d_new.c() == pytest.approx(circle2d.c())

    circle3d        = Circle3d(0.3, [[0., 1., 0.], [0.,1.,0.]])
    circle3d_pickle = pickle.dumps(circle3d)
    circle3d_new    = pickle.loads(circle3d_pickle)

    assert circle3d_new.r() == pytest.approx(circle3d.r())
    assert circle3d_new.c() == pytest.approx(circle3d.c())
    assert circle3d_new.z() == pytest.approx(circle3d.z())

    line2d        = Line2d([[0., 0], [0., 1.]])
    line2d_pickle = pickle.dumps(line2d)
    line2d_new    = pickle.loads(line2d_pickle)

    assert line2d(0.) == line2d_new(0.)
    assert line2d(1.) == line2d_new(1.)

def test_bs_suface():

    srf3d = BSSurface3d(
        [
            [0., 0., 0],[0., 1., 0],
            [1., 0., 1],[1., 1., 1],
        ],
        [0., 1.],
        [0., 1.],
        [2, 2],
        [2, 2],
        1,
        1
    )
    srf3d_pickle = pickle.dumps(srf3d)
    srf3d_new    = pickle.loads(srf3d_pickle)

    assert_surface_all_close(srf3d, srf3d_new)

    srf3d = BSSurfaceRational3d(
        [
            [0., 0., 0],[0., 1., 0],
            [1., 0., 1],[1., 1., 1],
        ],
        [  0.6, 0.7,
           1.2, 1.,
        ],
        [0., 1.],
        [0., 1.],
        [2, 2],
        [2, 2],
        1,
        1
    )
    srf3d_pickle = pickle.dumps(srf3d)
    srf3d_new    = pickle.loads(srf3d_pickle)

    assert_surface_all_close(srf3d, srf3d_new)

def test_revolution_surface():

    crv2d = BSCurve2d(
        [[0., 0.9],[1., 1.]],
        [0., 1.],
        [2, 2],
        1
    )

    srf = SurfaceOfRevolution(
        crv2d,
        [[0., 0., 0.], [0., 0., 1.], [0., 1., 0.]]
    )
    srf_pickle = pickle.dumps(srf)
    srf_new    = pickle.loads(srf_pickle)

    assert_surface_all_close(srf, srf_new, v2= 2 * pi)