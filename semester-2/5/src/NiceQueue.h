#ifndef _NICE_QUEUE_H_
#define _NICE_QUEUE_H_

#include <stdexcept>

#include "NiceStack.h"

//=============================================================================
//  ____          _          _                                     
// |    \ ___ ___| |_    ___| |_ ___ ___ ___ ___    _____ ___      
// |  |  | . |   |  _|  |  _|   | .'|   | . | -_|  |     | -_|     
// |____/|___|_|_|_|    |___|_|_|__,|_|_|_  |___|  |_|_|_|___|     
//                                      |___|                      
//=============================================================================

// Не менять этот файл!

template <class T>
	class NiceQueue
	{
	private:
		// Нельзя создать NiceQueue по умолчанию
		// Только с помощью другого конструктора с параметром
		NiceQueue(void) {}

		// Входной стек
		NiceStack<T> inStack;
		// Выходной стек
		NiceStack<T> outStack;

	public:
		// Создать NiceQueue с вместимостью capacity.
		NiceQueue(size_t capacity);
		// Вместимость очереди
		size_t m_capacity;

		// Возвращает число элементов в очереди
		size_t size(void) const;

		// Деструктор. Почему тут не нужен деструктор?
		// ~NiceQueue(void);

		// Положить новый элемент в очередь
		// Возникает исключение out_of_range если очередь полна
		void enq (T newelement) throw (out_of_range);

		// Извлечь элемент из очереди
		// Возникает исключение out_of_range если очередь пуста
		T deq (void) throw (out_of_range);

		// Возвращает минимальный элемент в очереди
		T getMinimum(void) throw (out_of_range);
	};

#include "NiceQueue.hpp"

#endif

