String is a custom Array class of type char. Automatically null terminated. Insert is not done. 

Create a string of size

    string = String(size)
    
Create a string out of an array of chars

    string = String(data)
    
 Concatenate this string with another
 
    string->concatenate(another_string)
    
 Or just use the adition operator
 
    string_C = string_A + string_B
    
 All comparison operators are overloaded
 
    <
    >
    <=
    >=
    ==
    
 Get a substring
 
    string->substring(left, right)
    
 Get the index of a char 
 
    string->index(char)
    
 Get the length of the string
 
    string->length()
    
 Check if it contains a char
 
    string->contains(char)
    
 Insert is not implemented
 
 Assignment operator is implemented
