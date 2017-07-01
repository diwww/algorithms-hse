# Cyber Police

Выполнил Суровцев Максим Алексеевич, гр. БПИ151(1)

Чтобы соблюсти принцип DRY, я добавил следующую функцию:
```
template<class Value, class Key, int numLevels>
std::array<typename SkipList<Value, Key, numLevels>::TypeNode*, numLevels + 1>
find(SkipList<Value, Key, numLevels> list, Key key)
```
Она работает точно так же, как и findLastLessThan(), но в дополнение к этому, в ней
запоминается массив для хранения последних вершин на каждом уровне для заданного ключа.
Это нужно для вставки вершины на разреженные уровни. Первые numLevels элеметов - это вершины
на разреженных уровнях, а последний элемент - сама найденная вершина.
Применить эту функцию в remove не удалось.