To create an array of size (n)

    Array(n)
    
To create an array out of a primitive c++ array

    Array(x* data, size)
    
To initialize an array with a value

    Array(size, val)
    
To access or set an element use the bracket operator

    name_of_your_array[index]
    
If you have a dynamically allocated (pointer to a new Array<x>()) array you will need to dereference the array

    (*array_name)[index]
    
If you have a sorted array you can call binarySearch to find an element

    array.binarySearch(x find, 0, size)
    
 Or you can call the much slower contains on an unsorted array
 
     contains(x find)
     
 You can also find the index of an element in an unsorted array with 
 
     index(x find)
     
 You can print an array to console with ostream operator
 
     cout << your_array // *your_array if dynamically allocated
