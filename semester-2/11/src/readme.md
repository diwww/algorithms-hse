# Assessing Infection

Выполнил Суровцев Максим Алексеевич, гр. БПИ151(1)

Переименовал некоторые методы: 
```
infected() -> isInfected()
indexof() -> indexOf()
```
Добавил метод для проверки посещенной вершины:
```
bool grid::isVisited(int row, int col) const
```
В функции count() посещенными отмечаются только зараженные вершины в силу
следующего условия:
```
if (!checkIndex(row, col) || !isInfected(row, col)
    || isVisited(row, col))
    return 0;
```
То есть, если вершина не зараженная, то она не отметится как посещенная.
Поэтому в операторе << для вывода знака '+' проверяется только посещенность.
```
stream << ob._area[ob.indexOf(row, col)].first << 
    (ob.isVisited(row, col) ? "+" : "") << "\t";
```
