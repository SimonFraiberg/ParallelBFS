
# Parallel BFS Implementation

This project provides a parallel implementation of Breadth-First Search (BFS) for graphs. The implementation uses multithreading to efficiently compute shortest paths from all vertices to all others in a graph. The project showcases data structures, synchronization mechanisms, and parallel programming concepts in C.

## Features
- **Parallel BFS Algorithm**: Implements BFS using a thread pool for concurrent processing of graph vertices.
- **Distance Matrix**: Calculates the shortest path from each vertex to every other vertex in the graph.
- **Thread-Safe Queues**: Custom queue implementations for managing tasks and BFS frontiers.
- **Thread Synchronization**: Mutexes ensure safe updates to shared resources.
- **Flexible Graph Representation**: Uses adjacency lists for graph storage.

## Project Structure
### Core Files:
- **parallelBFS.h and parallelBFS.c**: Contains the main parallel BFS logic.
- **vertexQueue.h and vertexQueue.c**: Queue implementation for BFS frontiers, supporting thread-safe enqueue and dequeue operations.
- **graph.h and graph.c**: Defines the graph structure and operations, including adjacency list creation and edge addition.
- **ThreadPool.h and ThreadPool.c**: Manages thread pool for parallel execution of tasks.
- **TaskQueue.h and TaskQueue.c**: Task queue implementation for managing tasks in the thread pool.

## How It Works
1. **Graph Representation**:
   - Graphs are represented using adjacency lists for efficient storage and traversal.
   - Each vertex's adjacency list is a linked list of neighboring vertices.

2. **Parallel BFS**:
   - Starts from a source vertex and uses a queue to maintain the current frontier of vertices.
   - A thread pool processes each vertex in the frontier concurrently.
   - Tasks for visiting neighbors are added dynamically, ensuring efficient resource utilization.

3. **Distance Matrix**:
   - Computes and stores distances between all vertex pairs.
   - Uses a parallel approach for BFS from each vertex to compute the shortest paths efficiently.

## Build and Run Instructions
1. **Prerequisites**:
   - GCC compiler
   - pthreads library (POSIX threads)

2. **Compilation**:
   ```
   use the makefile with the command make or use:
   gcc -o parallelBFS parallelBFS.c vertexQueue.c graph.c ThreadPool.c TaskQueue.c -lpthread
   ```

3. **Execution**:
   ```
   ./parallelBFS
   ```

## Dependencies
- **POSIX Threads**: Used for multithreading and synchronization.

## Future Enhancements
- Support for weighted graphs.
- Performance benchmarking with larger datasets.
- Integration with graph visualization tools.

---

This project demonstrates advanced programming skills in C, focusing on parallelism and efficient data structures.
