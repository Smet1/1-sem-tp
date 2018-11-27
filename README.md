**HW_2 (algs):**
---
1. Задача 1-1.

    Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв. **_Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера_**. Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4. Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству. 
    
        1_1. Для разрешения коллизий используйте квадратичное пробирование. 
        i-ая проба g(k, i) = (g(k, i-1) + i^2) (mod m). m - степень двойки. 
        
        1_2. Для разрешения коллизий используйте двойное хеширование.
    
    _Формат ввода_
    
    Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция. 
    
    Тип операции – один из трех символов: 
    - '+' означает добавление данной строки в множество; 
    - '-' означает удаление строки из множества; 
    - '?' означает проверку принадлежности данной строки множеству. 
    
    При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
    
    _Формат вывода_
    
    Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того, встречается ли данное слово в нашем множестве.

    |__in__|__out__|
    |---|:----:|
    |+ hello|OK|
    |+ bye|OK|
    |? bye|OK|
    |+ bye|FAIL|
    |- bye|OK|
    |? bye|FAIL|
    |? hello|OK|
---
2. Задача 2-3
    
    Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
    
    Требуется построить бинарное дерево, заданное наивным порядком вставки.
    
    Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
    
    `Рекурсия запрещена.`
    
    **Выведите элементы в порядке post-order (снизу вверх)**
    
    |__in__|__out__|
    |---|:----:|
    |3|1 3 2|
    |2 1 3|
    
    |__in__|__out__|
    |---|:----:|
    |3|3 2 1|
    |1 2 3|
    
    |__in__|__out__|
    |---|:----:|
    |3|2 1 3|
    |3 1 2|

---
3. Задача 3-2

    Дано число N < 106 и последовательность пар целых чисел из [-231, 231] длиной N. 
    
    Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi). Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве. 
    
    Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции: 
        
        При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. 
        
        Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. 
        
        Получившиеся два дерева сделайте дочерними для нового узла (x, y). 
        
        Новый узел вставьте на место узла P. 
        
    Построить также наивное дерево поиска по ключам Xi. 
    
    Равные ключи добавляйте в правое поддерево. 
    
    Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска. 
    
    Вывести их разницу. Разница может быть отрицательна.
    
    Алгоритм вставки:
    
        1. Спускаемся по дереву, останавливаемся на элементе, в котором значение приоритета оказалось меньше y
        
        2. Разрезаем поддерево найденного элемента Т1 и Т2
        
        3. Полученные Т1 и Т2 записываем в качестве левого и правого сына добавленного элемента
        
        4. Полученное дерево ставим на место элемента, найденного в первом пункте
        
    |__in__|__out__|
    |---|:----:|
    |10|2
    |5 11
    |18 8
    |25 7
    |50 12
    |30 30
    |15 15
    |20 10
    |22 5
    |40 20
    |45 9
    
    |__in__|__out__|
    |---|:----:|
    |10|2
    |38 19
    |37 5
    |47 15
    |35 0
    |12 3
    |0 42
    |31 37
    |21 45
    |30 26
    |41 6

---
4. Задача 4-2
---
DEADLINE: 27.10.18
