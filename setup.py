from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "Recomendador",
        # Adicionado p1.cpp (ERRO 2)
        ["p1.cpp", "p2_p4.cpp", "p3.cpp", "solver.cpp"],
        cxx_std=17,
    ),
]

setup(
    name="Recomendador",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)