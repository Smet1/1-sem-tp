**HW_2 (algs):**
---
1. Задача 1 «Представление графа» (5 баллов)

    Дан базовый интерфейс для представленияориентированного графа:
    
        struct IGraph {
            virtual ~IGraph() {}
            
            // Добавление ребра от from к to.
            virtual void AddEdge(int from, int to) = 0;
        
            virtual int VerticesCount() const  = 0;
        
            virtual std::vector<int> GetNextVertices(int vertex) const = 0;
            virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
        };
    
    Необходимо написать несколько реализаций интерфейса:
    
    - CListGraph, хранящий граф в виде массива списков смежности
    
    - CMatrixGraph, хранящий граф в виде матрицы смежности
    
    - CSetGraph, хранящий граф в виде массива хэш-таблиц
    
    - CArcGraph, хранящий граф в виде одного массива пар {from, to}
    
    Также необходимо реализовать конструктор, принимающий const IGraph*. Такой конструктор должен скопировать переданный граф в создаваемый объект.
    
    Для каждого класса создавайте отдельные h и cpp файлы.
    
    Число вершин графа задается в конструкторе каждой реализации.
---
2. Задача 2 Количество различных путей (3 балла)
---
3. Задача 3 «Города» (4 балла)
---
4. Задача 4 «Пятнашки» (8 баллов)
---
5. Задача 5-1 Приближенное решение метрической неориентированной задачи коммивояжера (5 баллов)
---
DEADLINE: 21.12.18
