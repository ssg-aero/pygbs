from pygbs.core import *
from pygbs.interpolate import *
from pygbs.tools import *

import warnings

warnings.warn(
    "Importing from `gbs` is deprecated. Please import from submodules.",
    DeprecationWarning,
    stacklevel=2,
)