import random

def generate_graph_with_cycle(num_vertices):
    """Генерация графа с гамильтоновым циклом"""
    edges = set()
    
    # Создаем гамильтонов цикл
    cycle = list(range(num_vertices))
    random.shuffle(cycle)
    
    # Добавляем ребра цикла
    for i in range(num_vertices):
        edges.add((cycle[i], cycle[(i + 1) % num_vertices]))
    
    # Добавляем дополнительные случайные ребра
    while len(edges) < num_vertices + random.randint(1, num_vertices // 2):
        u, v = random.sample(range(num_vertices), 2)
        edges.add((u, v))
    
    return cycle, list(edges)

def generate_graph_without_cycle(num_vertices):
    """Генерация графа без гамильтонова цикла"""
    edges = set()
    
    # Создаем несколько несвязанных компонент
    num_components = random.randint(2, num_vertices // 2)
    components = [list(range(i, i + num_vertices // num_components)) for i in range(0, num_vertices, num_vertices // num_components)]
    
    for component in components:
        if len(component) > 1:
            for i in range(len(component) - 1):
                edges.add((component[i], component[i + 1]))
    
    # Добавляем дополнительные случайные ребра, не образуя цикл
    while len(edges) < num_vertices + random.randint(1, num_vertices // 2):
        u, v = random.sample(range(num_vertices), 2)
        if (u, v) not in edges and (v, u) not in edges:
            edges.add((u, v))
    
    return [], list(edges)

def save_graph_to_file(filename, num_vertices, edges, cycle=None):
    """Сохранение графа в файл"""
    with open(filename, 'w') as f:
        f.write(f"{num_vertices} {len(edges)}\n")
        for u, v in edges:
            f.write(f"{u} {v}\n")
        if cycle:
            f.write(" ".join(map(str, cycle)) + "\n")

# Генерация 10 файлов
for i in range(5):
    cycle, edges = generate_graph_with_cycle(8)
    save_graph_to_file(f"graph_with_cycle_{i+1}.txt", 8, edges, cycle)

for i in range(5):
    cycle, edges = generate_graph_without_cycle(8)
    save_graph_to_file(f"graph_without_cycle_{i+1}.txt", 8, edges)


