#include <stdio.h>
#include <iostream>
#include <random>
#include <string>
#include <cmath>
#include <vector>
using namespace std;


// структура матрица [2][2]
struct Matrix
{
    double matrix[2][2];
};

// вывод матрицы [2][2]
void PrintMatrix(Matrix matrix)
{
    std::cout << matrix.matrix[0][0] << " " << matrix.matrix[0][1] << "\n";
    std::cout << matrix.matrix[1][0] << " " << matrix.matrix[1][1] << "\n";
    std::cout << "\n";
}

// генерация вещественного значения в заданном диапозоне
double GetRandom(double min = 0, double max = 70)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution <double>distrib(min, max);
    return distrib(generator);
}

// создание случайной матрицы [2][2]
Matrix GetRandomMatrix()
{
    Matrix matrix;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            matrix.matrix[i][j] = GetRandom();
        }
    }
    return matrix;
}

// структура стек
struct Stack
{
    Matrix* storage;
    int capacity;       // размер динамического массива
    int top;            // верхний элемент
};

// создание нового стека      // здесь надо создать новый ваектор
Stack NewStack()
{
    Stack stack;
    stack.capacity = 100;
    stack.storage = new Matrix[stack.capacity];
    stack.top = -1;
    return stack;
}

//
void ChangeStorage(Stack* stack, int newCapacity)
{
    Matrix* st2 = new Matrix[newCapacity];
    for (int i = 0; i <= stack->top; i++)
    {
        st2[i] = stack->storage[i];
    }
    delete[] stack->storage;
    stack->storage = st2;
    stack->capacity = newCapacity;
}

//  добавление элемента в стек
void Push(Stack* stack, Matrix matrix)
{
    if (stack->top < stack->capacity - 1)    // это надо бы выделить в отдельную функцию void PushUsualy(Stack *stack, Matrix matrix)
    {
        stack->top = stack->top + 1;
        stack->storage[stack->top] = matrix;
    }
    else
    {
        ChangeStorage(stack, 2 * (stack->capacity));
        Push(stack, matrix);
    }
}

// значение верхнего элемента
Matrix TopValue(Stack* stack)
{
    return stack->storage[stack->top];
}

// проверить пуста ли функция 
bool Empty(Stack* stack)
{
    return stack->top == -1;
}

// удаление верхнего элемента стека
void Pop(Stack* stack)
{
    if (!(Empty(stack)))
    {
        stack->top -= 1;
    }
}

// изменение размера массива
void ChangeCapacity(Stack* stack)
{
    int newCapacity = stack->capacity;
    if (stack->top <= 5)
    {
        newCapacity = 100;
    }
    while ((stack->top < (newCapacity / 2)) and (stack->top > 5))
    {
        newCapacity = newCapacity / 2;
    }
    ChangeStorage(stack, newCapacity);
}

//вывести размер массива
void PrintCapacity(Stack* stack)
{
    std::cout << stack->capacity << "\n";
}

// очистить стек
void Clear(Stack* stack)
{
    stack->top = -1;
    ChangeCapacity(stack);
}

//удалить стек
void DelStack(Stack* stack)
{
    delete[] stack->storage;
}

int main() {
    Stack stack = NewStack();
    std::cout << std::boolalpha << Empty(&stack) << "\n";
    Matrix matrix = GetRandomMatrix();
    PrintMatrix(matrix);
    Push(&stack, matrix);
    Matrix matrix1;
    matrix1 = TopValue(&stack);
    PrintMatrix(matrix1);
    std::cout << std::boolalpha << Empty(&stack) << "\n";
    Pop(&stack);
    std::cout << std::boolalpha << Empty(&stack) << "\n";
    Push(&stack, matrix);
    Clear(&stack);
    std::cout << std::boolalpha << Empty(&stack) << "\n";
    for (int i = 0; i < 40; i++)
    {
        Push(&stack, GetRandomMatrix());
        PrintMatrix(TopValue(&stack));
    }
    PrintCapacity(&stack);
    //   Clear(&stack);
    ChangeCapacity(&stack);
    PrintCapacity(&stack);
    std::cout << "Hello world\n";
    DelStack(&stack);
    std::cout << "Programm the end\n";
    return 0;
}