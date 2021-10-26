
#include <iostream>
#include <string>
#include <sstream>

#ifndef DASKER_COLLECTIONS_ARRAYLIST_H
#define DASKER_COLLECTIONS_ARRAYLIST_H


// This arraylist implementation is made by Daniel Masker
// GitHub: DaDarkWizard
namespace dasker::collections
{
    template<typename T>
    class ArrayList
    {
        private:
            int arraySize;                      // Size of the memory space allocated to the array of elements.
            int sizeVal;                        // Number of elements in the array.
            T* ptr;                             // Pointer to the array of elements.
            void ensureSize();                  // Helper function to ensure the array has enough space.
        public:
            ArrayList();                        // Constructor for the array.
            ~ArrayList();                       // Deconstructor for the array.
            int add(T value);                   // Add an element to the end of the array.
            std::string toString();             // Display the array and it's contents as a std::string.
            void remove(int index);             // Remove the element at the given index.
            int contains(T value);              // Check if the given element is within the array.
            int removeIfContains(T value);      // Remove the first occurance of the given element if it is within the array.
            int size();                         // Return the size of the array.
            T get(int index);                   // Get the element at the given index.
            T set(int index, T value);          // Set the element at the given index to the given value.
    };
    
    
    /* 
     * Constructor for the array.
     * Contains all defaults.
     */
    template <typename T>
    ArrayList<T>::ArrayList()
    {
        int defaultSize = 10;
        ptr = new T[defaultSize];
        sizeVal = 0;
        arraySize = defaultSize;
    }
    
    /*
     * Converts the array to a string.
     * Displayed as 'ArrayList: [e1, e2, e3, ...]
     */
    template <typename T>
    std::string ArrayList<T>::toString()
    {
        std::stringstream outputStream;
        outputStream << "ArrayList: [";
        for(int i = 0; i < sizeVal - 1; i++){
            outputStream << ptr[i] << ", ";
        }
        if(sizeVal > 0)
        {
            outputStream << ptr[sizeVal - 1];
        }
        outputStream << "]";
        
        return outputStream.str();
    }
    
    /*
     * Adds an element to the end of the array.
     */
    template <typename T>
    int ArrayList<T>::add(T value)
    {
        ensureSize();
        ptr[sizeVal] = value;
        sizeVal++;
        return sizeVal - 1;
    }
    
    template <typename T>
    void ArrayList<T>::ensureSize()
    {
        if(sizeVal == arraySize)
        {
            T* tmp = ptr;
            arraySize *= 2;
            ptr = new T[arraySize];
            for(int i = 0; i < sizeVal; i++)
            {
                ptr[i] = tmp[i];
            }
            delete [] tmp;
        }
    }
    
    template <typename T>
    ArrayList<T>::~ArrayList()
    {
        delete [] ptr;
    }
    
    template <typename T>
    void ArrayList<T>::remove(int index)
    {
        if(index < 0 || index >= sizeVal)
        {
            std::cerr << "Error: index out of bounds in remove! \n";
            exit(-1);
        }
        for(int i = index; i < sizeVal - 1; i++){
            ptr[i] = ptr[i + 1];
        }
        sizeVal--;
    }
    
    template <typename T>
    int ArrayList<T>::contains(T value)
    {
        for(int i = 0; i < sizeVal; i++)
        {
            if(ptr[i] == value)
            {
                return i;
            }
        }
        
        return -1;
    }
    
    template <typename T>
    int ArrayList<T>::removeIfContains(T value)
    {
        int cont = contains(value);
        if(cont != -1){
            remove(cont);
        }
        return cont;
    }
    
    template <typename T>
    int ArrayList<T>::size()
    {
        return sizeVal;
    }
    
    template <typename T>
    T ArrayList<T>::get(int index)
    {
        if(index < 0 || index >= sizeVal)
        {
            std::cerr << "Error: index out of bounds in get!\n";
            exit(-1);
        }
        return ptr[index];
    }
    
    template <typename T>
    T ArrayList<T>::set(int index, T value)
    {
        if(index < 0 || index > sizeVal)
        {
            std::cerr << "Error: index out of bounds on set!\n";
            exit(-1);
        }
        if(index == sizeVal)
        {
            add(value);
            return value;
        }
        T tmp = ptr[index];
        ptr[index] = value;
        return tmp;
    }
}

#endif
