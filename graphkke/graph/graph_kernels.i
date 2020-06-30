%module graph_kernels
%{
    #define SWIG_FILE_WITH_INIT
    #define SWIG_PYTHON_CAST_MODE
    #define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

    #include "graph_kernels.h"
%}

%include "graph_kernels.h"
%include "numpy.i"

%template(WLSubtreeKernelii) GraphLib::WLSubtreeKernel<int, int>;
