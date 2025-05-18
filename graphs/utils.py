def read_graph_from_file(file_path):
    with open(file_path, 'r') as f:
        lines = [line.strip() for line in f if line.strip()]

    if not lines[0].lower().startswith("*vertices"):
        raise ValueError("File must start with '*vertices n'.")

    num_vertices = int(lines[0].split()[1])
    labels = {}
    adjacency = {i: [] for i in range(1, num_vertices + 1)}

    i = 1
    # Read vertex labels
    while not lines[i].startswith("*"):
        parts = lines[i].split()
        idx = int(parts[0])
        labels[idx] = parts[1]
        i += 1

    # Determine if graph is directed or undirected
    is_directed = lines[i].lower() == "*arcs"
    i += 1

    # Read edges
    while i < len(lines):
        u, v, _ = lines[i].split()
        u, v = int(u), int(v)
        adjacency[u].append(v)
        if not is_directed:
            adjacency[v].append(u)
        i += 1

    return adjacency, labels, is_directed