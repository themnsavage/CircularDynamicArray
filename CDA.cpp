#include<iostream>
#include<array>
using namespace std;


template <class T>

class CDA
{
    private:
        // variables
        T *array; // pointer to array
        int front, rear; // the pointer for front and rear of array
        int capacity; // memory size
        int size; // how full the array is of elements
        bool reverse = false; // indicates if in reverse mode
        T *missingObject = new T[1];

        // helper functions
        bool isFull() //checks if array is full
        {
            return capacity == size;
        }

        bool isEmpty() // checks to see if array is empty
        {
            return size == 0;
        }

        bool isShrink() // checks if array is shrinkable
        {
            return (capacity / 2) > 4 && size <= (capacity / 4); // capacity should never go below 4 and array is 25% full
        }

        int iterateRight(int index) // iterate index once to the right 
        {
            return (index + 1) % capacity;
        }

        int iterateRightBy(int index, int num) // iterate right by num
        {
            return (index + num) % capacity;
        }

        

        int iterateLeft(int index) // iterate index once to the left
        {
            int num = (index - 1) % capacity;

            if(num < 0)
            {
                num = num + capacity;
            }

            return num;
        }

        int iterateLeftBy(int index, int num) // iterate to left by num
        {
            int n = (index - num) % capacity;
            if(n < 0)
            {
                n = n + capacity;
            }
                        
            return n;
        }

        void copyArray(T *newArray) // copy objects from old array to new array 
        {
            int j;

            if(!reverse) // copy old array in new array (foward)
            {
               j = front;

                for(int i = 0; i < size; i++)
                {
                    newArray[i] = array[j];
                    j = iterateRight(j);
                }
                front = 0;
                rear = size - 1;
            } 
            else // copy old array in new array (reverse)
            {
                j = rear;
                
                for(int i = 0; i < size; i++)
                {
                    newArray[i] = array[j];
                    j = iterateRight(j);
                }
                rear = 0;
                front = size - 1;
            }
        }

        void grow() // doubles the array size
        {
            T* newArray = new T[2 * capacity];
        
            copyArray(newArray);

            capacity = capacity * 2;
            array = newArray;
            
            
        }
        
        void shrink() // shrinks array by 1/2
        {
            T *newArray = new T[capacity / 2];
            
            copyArray(newArray);

            capacity = capacity / 2;
            array = newArray;
           
            
        }

        T quickSelect(CDA<T> A, int k) 
        {
            T pivot = A[(A.front + A.rear) / 2];
            CDA<T> L, E, G;
            int j = A.front;

            for(int i = 0; i < A.size; i++)
            {
                if(A[j] < pivot)
                {
                    L.AddEnd(A[j]);
                }
                else if(A[j] == pivot)
                {
                    E.AddEnd(A[j]);
                }
                else
                {
                    G.AddEnd(A[j]);
                }
                j = iterateRight(j);
            }

            if(k <= L.size)
            {
                return quickSelect(L, k);
            }
            else if(k <= L.size + E.size)
            {
                return pivot;
            }
            else
            {
                return quickSelect(G, k - L.size - E.size);
            }
        }

        void swap(T *a, T *b)
        {
            T temp = *a;
            *a = *b;
            *b = temp;
        }

        int sortPartition(T *A, int low, int high)
        {
            T pivot = A[high];
            int i = low - 1;

            for(int j = low; j <= high - 1; j++)
            {
                if(A[j] < pivot)
                {
                    i++;
                    swap(&A[i], &A[j]);
                }
            }

            swap(&A[i + 1], &A[high]);
            return i + 1;
        }

        void quickSort(T *A, int low, int high)
        {
            if(low < high)
            {
                int pivot = sortPartition(A, low, high);

                quickSort(A, low, pivot - 1);
                quickSort(A, pivot + 1, high);
            }
                
        }

        int binCases(int index, T object) // partition array based on cases
        {
            if(front == 0 && rear >= 0) // only added rear
            {
                return index;
            }
            else if(front > 0 && rear == 0) // only added front
            {
                if(index == 0)
                {
                    return size - 1; 
                }
                else
                {
                    return index - front;
                }
            }
            else // added front and rear
            {
                if(object >= array[0] && object <= array[rear])
                {
                    return index + (capacity - front);
                }
                else
                {
                    return index - front;
                }
            }
        }
        int binarySearch(T *A, int low, int high, T object) // searching algorithm
        {
            if(high >= low)
            {
                int middle = low + (high - low) / 2;

                if(A[middle] == object)
                {
                    middle = binCases(middle, object);
                    return middle;
                }
                else if(A[middle] > object)
                {
                    return binarySearch(A, low, middle - 1, object);
                }
                else
                {
                    return binarySearch(A, middle + 1, high, object);
                }
            } 

            if(high == rear)
            {
                return ~size;
            }
            else
            {
                high = binCases(high, object);
                return ~iterateRight(high);
            }
        }


    public:
        // constructors and destructor
        CDA(); // empty array constructor 
        CDA(int s); // array with size constructor
        CDA(CDA<T> const &object); // copy constructor 
        ~CDA(); // deconstructor

        CDA<T>& operator=(const CDA<T> object) // copy operator 
        {
            array = new T[object.capacity];
            capacity = object.capacity;
            size = object.size;
            front = object.front;
            rear = object.rear;
            reverse = object.reverse;

            //copy array
            int j;
            if(!reverse)
            {
                j = front;
                do
                {
                    array[j] = object.array[j];
                    j = iterateRight(j);
                }while(j != iterateRight(rear));
            }
            else
            {
                j = rear;
                do
                {
                    array[j] = object.array[j];
                    j = iterateRight(j);
                }while(j != iterateRight(front));
            }
            return *this;
        }

        T& operator[](int i) // returns the reference at i index 
        {
                if((i >= 0 && i <= size - 1) && !isEmpty()) // in boundary and array can't be empty
                {
                    if(!reverse)
                    {
                        return array[iterateRightBy(front, i)];
                    }
                    else
                    {
                       return array[iterateLeftBy(front, i)];
                    }
                }
                else
                {
                    cout<<"--OUT OF BOUNDS--"<<endl;
                    return missingObject[0];
                }
                
        }
        
        // memory functions 
        int Length() //returns the size of array
        {
            return size;
        } 

        int Capacity() // returns the capacity of array
        {
            return capacity;
        }
        
        int getFront() // returns Front 
        {
            return front;
        }
        
        int getRear() // returns rear
        {
            return rear;
        }


        void AddEnd(T object) // add object to the end of array
        {
            if(isFull())
            {
                grow();
            }
            else if(isEmpty())
            {
                front++;
            }

            if(!reverse)
            {
                rear = iterateRight(rear);
            }
            else
            {
                rear = iterateLeft(rear);
            }

            array[rear] = object;
            size++;
        }
        
        void AddFront(T object) // add object to the front of array
        {
            if(isFull())
            {
                grow();
            }
            if(isEmpty())
            {
                rear++;
            }
            
            if(!reverse)
            {
                front = iterateLeft(front);
            }
            else
            {
                front = iterateRight(front);
            }

            array[front] = object;
            size++;
        }
        
        void DelEnd() // delete object at the end of list
        {
           if(!isEmpty()) 
           {
               if(!reverse)
               {
                   rear = iterateLeft(rear);
               }
               else
               {
                   rear = iterateRight(rear);
               }

               size--;
               
               if(isEmpty()) // array is empty reset pointers
               {
               front = -1;
               rear = -1;
               }

               if(isShrink())
               {
                   shrink();
               }
           }
        }
       
        void DelFront() // delete object at the front of the list
        {
            if(!isEmpty()) 
            {
                if(!reverse)
                {
                    front = iterateRight(front);
                }
                else
                {
                    front = iterateLeft(front);
                }

                size--;

                if(isEmpty()) // array is empty reset pointers
                {
                    front = -1;
                    rear = -1;
                }

                if(isShrink())
                {
                    shrink();
                }
            }
        }
        
        void Clear() // frees any space and reset with array with capacity 4 and size 0
        {
            delete [] array;
            array = new T[4];
            capacity = 4;
            size = 0;
            front = -1;
            rear = -1;
        }
        
        void Reverse() // change logical direction of the array
        {
            int hold = front;
            front = rear;
            rear = hold;
            reverse = !reverse;
        }
        
        //search and sort
        T Select(int k) // returns kth smallest element
        {
            bool r = false;
            
            if(reverse)
            {
                r = true;
                Reverse();
            }
            
            T temp;
            T pivot = array[front];
            CDA<T> L, E, G;
            
            int j = front;
            for(int i = 0; i < size; i++)
            {
                if(array[j] < pivot)
                {
                    L.AddEnd(array[j]);
                }
                else if(array[j] == pivot)
                {
                    E.AddEnd(array[j]);
                }
                else
                {
                    G.AddEnd(array[j]);
                }

                j = iterateRight(j);
            }
            
            if(k <= L.size)
            {
                temp = quickSelect(L, k);
            }
            else if(k <= L.size + E.size)
            {
                temp = pivot;
            }
            else
            {
                temp = quickSelect(G, k - L.size - E.size);
            }
            if(r)
            {
                Reverse();
            }
            return temp;
        }

        void Sort() // uses an n lg n sorting algorithm to sort
        {
            if(reverse)
            {
                Reverse();
            }
            T *newArray = new T[capacity];
            copyArray(newArray);
            array = newArray;
           
            
            
            quickSort(array, front, rear);
            
           
        }

        int Search(T object) // use linear search to find object
        {
            int j = front;
            int i = 0;

            if(!reverse)
            {
                do
                {
                    if(array[j] == object)
                    {
                        return i;
                    }

                    j = iterateRight(j);
                    i++;
                }while (j != iterateRight(rear));
            }
            else
            {
                do
                {
                    if(array[j] == object)
                    {
                        return i;
                    }

                    j = iterateLeft(j);
                    i++;
                }while(j != iterateLeft(rear));
            }
            return -1;
        }
        
        int BinSearch(T object) // uses binary search to find object
        {
            int num;
            if(reverse)
            {
                Reverse();
            }
            if(object >= array[0] && object <= array[rear])
            {

                return binarySearch(array, 0, rear, object);
            }
            else
            {
                return binarySearch(array, front, capacity - 1, object);
            }

        }
};

// constructors and destructors 
template<class T>
CDA<T>::CDA()
{
    array = new T[1];
    capacity = 1;
    size = 0;
    front = -1; 
    rear = -1;
}

template<class T>
CDA<T>::CDA(int s)
{
    array = new T[s];
    capacity = s;
    size = s;
    front = 0;
    rear = s - 1;
}

template<class T>
CDA<T>::CDA(CDA<T> const &object)
{
    array = new T[object.capacity];
    capacity = object.capacity;
    size = object.size;
    front = object.front;
    rear = object.rear;
    reverse = object.reverse;

    //copy array
    int j;
    if(!reverse)
    {
        j = front;
        do
        {
            array[j] = object.array[j];
            j = iterateRight(j);
        }while(j != iterateRight(rear));
    }
    else
    {
        j = rear;
        do
        {
            array[j] = object.array[j];
            j = iterateRight(j);
        }while(j != iterateRight(front));
    }
}

template<class T>
CDA<T>::~CDA()
{
    delete [] array;
}