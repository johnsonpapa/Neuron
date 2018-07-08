#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include <string>
#include <memory>

template <class T>
class Array
{
    int arraySize = 0;
    std::shared_ptr<T[]> object;

    public:
        Array(){};
        Array(int size){arraySize = size; object.reset(new T[arraySize]);};
        ~Array(){};

        int size(){return arraySize;}
        T* getArray(){return object.get();};
        void setSize(int size)
        {
            // Create a new object array
            T* newObject = new T[size];

            // Copy over the old contents to the new one
            for (int i = 0; i < size && i < arraySize; i++)
                newObject[i] = object[i];

            // Set the new object array reference
            object.reset(newObject);

            // Update the size
            arraySize = size;
        }

        /**
            Inserts the target data at the specified index
            [FRONTDATA, VALUE, ENDDATA]

            Memmove not used because it prevents insert operation
            applied to the same array

            @warning Unstable
        */
        void insert(T value, int index)
        {
            // Safety check
//            if (index >= arraySize + 1)
//                exit(1);

            // 1) Create a new object array of new size
            T* newObject = new T[arraySize + 1];

            // 2) Memcpy/Memmove front half to new array
            // memmove(&newObject[0], &object[0], index * sizeof(T));
            memcpy(&newObject[0], &object[0], index * sizeof(T));

            // 3) Set the data at the new index position
            // memmove(&newObject[index], &value, sizeof(T));
            newObject[index] = value;

            // 4) Memcpy/Memmove end half to new array
            // memmove(&newObject[index + 1], &object[index], (arraySize - index) * sizeof(T));
            memcpy(&newObject[index + 1], &object[index], (arraySize - index) * sizeof(T));

            // 5) Update the object and size
            object.reset(newObject);
            arraySize++;
        }

        /**
            Inserts the target array data at the specified index
            [FRONTDATA, NEWARRAYDATA, ENDDATA]

            Memmove not used because it prevents insert operation
            applied to the same array

            @warning Unstable
        */
        void insert(Array<T> &array, int index)
        {
            // Safety check
//            if (index >= arraySize + array.size())
//                return;

            // 1) Create a new object array of new size
            T* newObject = new T[arraySize + array.size()];

            // 2) Memcpy/Memmove front half to new array
            // memmove(&newObject[0], &object[0], index * sizeof(T));
            memcpy(&newObject[0], &object[0], index * sizeof(T));

            // 3) Memcpy/Memmove new array data to new array
            // memmove(&newObject[index], &array[0], array.size() * sizeof(T));
            memcpy(&newObject[index], &array[0], array.size() * sizeof(T));

            // 4) Memcpy/Memmove end half to new array
            // memmove(&newObject[index + array.size()], &object[index], (arraySize - index) * sizeof(T));
            memcpy(&newObject[index + array.size()], &object[index], (arraySize - index) * sizeof(T));

            // 5) Update the object and size
            object.reset(newObject);
            arraySize = arraySize + array.size();
        }

        /**
            Removes an object from the array given an index
            Uses memmove to speed up memory operations
        */
        void remove(int index)
        {
            // Create a new object array
            T* newObject = new T[arraySize - 1];

            // Copy over the old contents to the new one
            memmove(&newObject[0], &object[0], index * sizeof(T));
            memmove(&newObject[index], &object[index + 1], (arraySize - index - 1) * sizeof(T));

            // Set the new object array reference
            object.reset(newObject);

            // Update the size
            arraySize = arraySize - 1;
        }

        /**
            Removes an object from the array given a range of index to remove
            Uses memmove to speed up memory operations
        */
        void remove(int startIndex, int endIndex)
        {
            // Create a new object array
            T* newObject = new T[arraySize + startIndex - endIndex - 1];

            // Copy over the old contents to the new one
            memmove(&newObject[0], &object[0], startIndex * sizeof(T));
            memmove(&newObject[startIndex], &object[endIndex + 1], (arraySize - endIndex - 1) * sizeof(T));

            // Set the new object array reference
            object.reset(newObject);

            // Update the size
            arraySize = arraySize + startIndex - endIndex - 1;
        }

        /* Operator overloading */
        void operator = (Array& otherArray)
        {
            /// Deep copy
            // Update the size
            arraySize = otherArray.size();

            // Create a new object array
            object.reset(new T[arraySize]);

            // Copy over the all contents
            for (int i = 0; i < arraySize; i++)
                object[i] = otherArray[i];
        }

        T& operator [] (int index)
        {
            // Ensuring the object exists, and selecting the correct index is the programmer's job.
            return object[index];
        }
};

#endif // ARRAY_H_INCLUDED
