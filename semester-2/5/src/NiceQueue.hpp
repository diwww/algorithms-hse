template<typename T>
NiceQueue<T>::NiceQueue(size_t capacity) : inStack(capacity), outStack(capacity)
{
    m_capacity = capacity;
}

template<typename T>
size_t NiceQueue<T>::size() const
{
    return inStack.size() + outStack.size();
}

template<typename T>
void NiceQueue<T>::enq(T newelement) throw(out_of_range)
{
    if (size() == m_capacity)
        throw std::out_of_range("Queue is full.");

    inStack.push(newelement);
}

template<typename T>
T NiceQueue<T>::deq() throw(out_of_range)
{
    if (size() == 0)
        throw std::out_of_range("Queue is empty.");
    else if (outStack.size() == 0)
    {
        while (inStack.size() > 0)
            outStack.push(inStack.pop());
    }

    return outStack.pop();
}

template<typename T>
T NiceQueue<T>::getMinimum() throw(out_of_range)
{
    if (size() == 0)
        throw std::out_of_range("Queue is empty.");
    else if (outStack.size() == 0)
        return inStack.getMinimum();
    else if (inStack.size() == 0)
        return outStack.getMinimum();
    else
        return std::min(inStack.getMinimum(), outStack.getMinimum());
}
