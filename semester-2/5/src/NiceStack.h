#ifndef _NICE_STACK_H_
#define _NICE_STACK_H_

#include <string>
#include <stdexcept>
#include <utility>
#include <vector>

//=============================================================================
//  ____          _          _                                     
// |    \ ___ ___| |_    ___| |_ ___ ___ ___ ___    _____ ___      
// |  |  | . |   |  _|  |  _|   | .'|   | . | -_|  |     | -_|     
// |____/|___|_|_|_|    |___|_|_|__,|_|_|_  |___|  |_|_|_|___|     
//                                      |___|                      
//=============================================================================

// Не менять этот файл!

using namespace std;

template <class T>
	class NiceStack
	{
	private:
		// Нельзя создать NiceStack по умолчанию
		// Только с помощью другого конструктора с параметром
		NiceStack(void) {}

		// Определение типа элементов стека - пара <значение, минимум-среди-всех-элементов-ниже-включая-текущий>
		typedef std::pair<T,T> TypeElementStack;

		// Вектор элементов стека
		vector<TypeElementStack> storage;
		size_t m_capacity; // вместимость стека
		size_t iHead; // индекс головы стека

	public:
		// Создать NiceStack с вместимостью capacity
		NiceStack(size_t capacity);

		// Сколько элементов находится в стеке
		size_t size() const;

		// Деструктор. Нужен ли тут деструктор?
		~NiceStack(void);

		// Положить новый элемент
		// Возникает исключение out_of_range если стек полный
		void push (T newelement) throw (out_of_range);

		// Извлечь вершину стека.
		// Возвращается значение верхнего элемента стека и
		// верхний элемент удаляется из стека
		// Возникает исключение out_of_range если стек пустой
		T pop (void) throw (out_of_range);

		// Возвращает минимальный элемент в стеке
		T getMinimum(void) throw (out_of_range);
	};

#include "NiceStack.hpp"

#endif

