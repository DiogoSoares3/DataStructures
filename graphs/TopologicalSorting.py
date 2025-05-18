from utils import read_graph_from_file


def dfs_visit_ot(graph, v, C, T, F, time, O):
    C[v] = True
    time[0] += 1
    T[v] = time[0]
    
    for u in graph[v]:
        if not C[u]:
            dfs_visit_ot(graph, u, C, T, F, time, O)
    
    time[0] += 1
    F[v] = time[0]
    O.insert(0, v) 


def topological_sort(graph):
    C = {v: False for v in graph}
    T = {}
    F = {}
    time = [0]
    O = []
    
    for u in graph:
        if not C[u]:
            dfs_visit_ot(graph, u, C, T, F, time, O)

    return O


def main():
    filename = "entry_files/DAG.txt" 
    graph, labels, _ = read_graph_from_file(filename)

    O = topological_sort(graph)

    # Convert vertex indices to labels
    sorted_labels = [labels[v] for v in O]

    # Print the result
    print(" , ".join(sorted_labels) + '.')


if __name__ == "__main__":
    main()