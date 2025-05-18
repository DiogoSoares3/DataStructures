from utils import read_graph_from_file


def dfs(graph, custom_order=None):
    C = {v: False for v in graph}
    T = {}
    F = {}
    A = {}
    time = [0]  # Use list to make it mutable

    if custom_order is None:
        vertices = list(graph.keys())
    else:
        vertices = custom_order

    for u in vertices:
        if not C[u]:
            dfs_visit(graph, u, C, T, A, F, time)

    return C, T, F, A


def dfs_visit(graph, v, C, T, A, F, time):
    C[v] = True
    time[0] += 1
    T[v] = time[0]

    for u in graph[v]:
        if not C[u]:
            A[u] = v
            dfs_visit(graph, u, C, T, A, F, time)

    time[0] += 1
    F[v] = time[0]


def find_root(v, A):
    while v in A:
        v = A[v]
    return v


def kosaraju_algorithm(graph):
    # First DFS to get finish times
    C, T, F, A = dfs(graph)

    # Build the transpose graph
    TGraph = {v: [] for v in graph}
    for u in graph:
        for v in graph[u]:
            TGraph[v].append(u)
    
    # Sort vertices by decreasing finish time
    order = sorted(F, key=F.get, reverse=True)

    # Second DFS in transposed graph
    C, _, _, A = dfs(TGraph, custom_order=order)

    # Group components using DFS forest
    components = {}
    for v in graph:
        root = find_root(v, A)
        if root not in components:
            components[root] = []
        components[root].append(v)
    
    return list(components.values())


def main():
    filename = "entry_files/UnweightedDirectedGraph.txt" 
    graph, _, _ = read_graph_from_file(filename)

    sccs = kosaraju_algorithm(graph)

    # Sort and print SCCs
    for component in sccs:
        component_sorted = sorted(component)
        print(",".join(str(v) for v in component_sorted))


if __name__ == "__main__":
    main()