cmake_minimum_required(VERSION 3.17)
project(DataStructure)

set(CMAKE_CXX_STANDARD 14)


add_executable(list List/list.h List/list.cpp)
add_executable(testData List/testData.cpp List/list.h List/list.cpp List/queue.cpp List/queue.h List/stack.cpp List/stack.h)
add_executable(dsstring String/dsstring.cpp String/dsstring.h String/testData.cpp)
add_executable(testString String/testData.cpp)

add_executable(RandomCodes RandomCodes.cpp)
add_executable(tsmatrix tsmatrix.cpp)
add_executable(crosslist crosslist.cpp)
add_executable(bitree Tree/bitree.cpp Tree/bitree.h)
add_executable(test test.cpp)
add_executable(graph Graph/graph.cpp Graph/graph.h)
add_executable(adjList Graph/adjList.cpp Graph/adjList.h)
add_executable(hash Hash/hash.cpp Hash/hash.h)
add_executable(avl AVL/avl.cpp AVL/avl.h)
add_executable(minbinheap Sort/minbinheap.cpp Sort/minbinheap.h)