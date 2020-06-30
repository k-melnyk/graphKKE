%module graph
%{
    #define SWIG_FILE_WITH_INIT
    #define SWIG_PYTHON_CAST_MODE
    #define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
    #include "graph.h"
%}

%include "std_string.i"
%include "std_vector.i"
%include "std_pair.i"
%include "std_set.i"
%include "numpy.i"

%init %{
    import_array();
%}

%include "graph.h"

%apply(int* IN_ARRAY1) {(std::vector<int> vec)}
%apply(int* IN_ARRAY1) {(std::vector<std::vector<int>> vectorOfNodeLabels)}
%apply(int* IN_ARRAY1) {(std::vector<std::pair<size_t, size_t>> vectorOfNodeLabels)}

%template(IntVector) std::vector<int>;
%template(SizeVectorVector) std::vector<std::vector<size_t>>;
%template(IntVectorVector) std::vector<std::vector<int>>;
%template(SizePair) std::pair<size_t, size_t>;
%template(SizeVectorPair) std::vector<std::pair<size_t, size_t>>;
%template(StringVector) std::vector<std::string>;
%template(GraphiiVector) std::vector<GraphLib::Graph<int, int>>;

%template(Graphii) GraphLib::Graph<int, int>;
%template(Graphstst) GraphLib::Graph<size_t, size_t>;
%template(Graphis) GraphLib::Graph<int, std::string>;

