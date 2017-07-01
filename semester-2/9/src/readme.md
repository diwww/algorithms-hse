# Europe by Rail using Dijkstra Algorithm

Выполнил Суровцев Максим Алексеевич, гр. БПИ151(1)

Видимо, очередь с приоритетами сравнивает элементы при добавлении в нее, а не при вызове top().
Поэтому я использовал вместо очереди с приоритетами вектор и каждый раз сортировал его, чтобы добиться
правильного порядка по убыванию total_fee.
Также пришлось изменить в файле RailSystem.h компаратор (в двух методах теперь стоит знак больше):
```
bool operator()(City* city1, City* city2) 
{
    return city1->total_fee > city2->total_fee;
}
bool operator()(const City city1, const City city2) 
{
    return city1.total_fee > city2.total_fee;
}
```
