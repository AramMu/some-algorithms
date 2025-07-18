TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14

SOURCES += \
    main.cpp \
    geometry_alg.cpp \
    geometry_struct.cpp \
    convex_hull.cpp \
    graph_alg.cpp \
    structures.cpp \
    image_processing.cpp \
    sorting.cpp \
    Algorithms/graph_alg.cpp \
    Algorithms/sorting.cpp \
    Backup/image_processing.cpp \
    Geometry/convex_hull.cpp \
    Geometry/geometry_alg.cpp \
    Geometry/geometry_struct.cpp \
    Structures/structures.cpp \
    Structures/disjoint_set.cpp \
    Structures/edge.cpp \
    Structures/binary_heap.cpp


include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    geometry_struct.h \
    geometry_alg.h \
    geometry.h \
    convex_hull.h \
    graph_alg.h \
    structures.h \
    image_processing.h \
    sorting.h \
    rb_tree.h \
    Algorithms/graph_alg.h \
    Algorithms/sorting.h \
    Backup/image_processing.h \
    Geometry/convex_hull.h \
    Geometry/geometry.h \
    Geometry/geometry_alg.h \
    Geometry/geometry_struct.h \
    Structures/graph_struct.h \
    Structures/rb_tree.h \
    Structures/structures.h \
    Structures/disjoint_set.h \
    Structures/edge.h \
    Structures/binary_heap.h \
    Structures/basic_structs.h

DISTFILES += \
    oldgeometry.txt \
    structures.txt \
    avl_treeh.txt \
    rb_treeh.txt \
    avl_treecpp.txt \
    rb_treecpp.txt \
    hash_seth.txt \
    hash_setcpp.txt \
    rb_treeaaacpp.txt

