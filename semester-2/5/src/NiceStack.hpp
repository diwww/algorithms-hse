template<typename T>
NiceStack<T>::NiceStack(size_t capacity)
{
    m_capacity = capacity;
    storage.reserve(m_capacity);
}

template<typename T>
size_t NiceStack<T>::size() const
{
    return storage.size();
}

template<typename T>
void NiceStack<T>::push(T newelement) throw(out_of_range)
{
    if (storage.size() == m_capacity)
        throw std::out_of_range("Stack is full.");

    T min = storage.empty() ? newelement : std::min(storage.back().second, newelement);
    TypeElementStack temp(newelement, min);

    storage.push_back(temp);
}

template<typename T>
T NiceStack<T>::pop() throw(out_of_range)
{
    if (storage.empty())
        throw std::out_of_range("Stack is empty.");

    T value = storage.back().first;
    storage.pop_back();
    return value;
}

template<typename T>
T NiceStack<T>::getMinimum(void) throw(out_of_range)
{
    if (storage.empty())
        throw std::out_of_range("Stack is empty.");

    return storage.back().second;
}

template<typename T>
NiceStack<T>::~NiceStack() { }
