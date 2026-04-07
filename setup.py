from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "meu_modulo",
        ["p2_p4.cpp", "p3.cpp"],
        cxx_std=17,
    ),
]

setup(
    name="meu_modulo",
    version="0.1.0",
    description="Exemplo de integração Python + C++ com pybind11",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)