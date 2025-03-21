//Endrit Ngjelina U43630372
#include "linked_calc.hpp"

// Default constructor definition
template <typename T>
LinkedCalc<T>::LinkedCalc() : head(nullptr) {}

// Destructor to deallocate memory
template <typename T>       
LinkedCalc<T>::~LinkedCalc() {
    Node<T>* current = head;
    while (current != nullptr) {    //current different from null pointer

        Node<T>* node_next = current->next;

        delete current;     //deallocate memory 

        current = node_next;    
    }
}

// Function to insert a new node at the end of the linked list
template <typename T>
void LinkedCalc<T>::insert(const T& value) {
    Node<T>* new_node = new Node<T>(value);

    if (head == nullptr) head = new_node;
    else {
        Node<T>* current = head;
        while (current->next != nullptr) current = current->next;
        current->next = new_node;
    }
}

// Helper function to determine if a character is a digit
template <typename T>
bool LinkedCalc<T>::isDigit(const T& c) {
    return (c >= '0' && c <= '9');
}

template <typename T>
bool LinkedCalc<T>::validateExpression() {

    Node<T>* current = head;    //set current to head and 3 bools to false
    bool last_digit = false;
    bool last_operator = false;
    bool last_decimal = false;

    while (current) {
        T c = current->data;

        if (isDigit(c)) last_digit = true;  //check c, if digit boolean becomes true
        
        else if (c == '.') {
            if (last_decimal || last_operator || !last_digit) return false; //validate input
            last_digit = false;
        } 

        else if (c == '*' || c == '/' || c == '-' || c == '+') {//check if c is operation
            if (last_operator || !last_digit) return false; //invalid input
            last_digit = false;     //assign last digit to false
        } 

        current = current->next;
    }
    return last_digit;  //return last digit
}

template <typename T>
float LinkedCalc<T>::convertToFloat(Node<T>*& current) {
    bool flag = false;  //check if its decimal number
    float result = 0.0f;
    float decimal_division_part = 1.0f;
    
    //traverse list until a non-digit or non-decimal point is seen
    while (current && (isDigit(current->data) || current->data == '.')) {

        if (current->data == '.') flag = true; //check if its decimal point
        
        else {
            if (!flag) result = result * 10 + (current->data - '0');   //create integer part

            else {
                decimal_division_part *= 10;   //decimal part
                result += (current->data - '0') / decimal_division_part;    //get result
            }
        }
        current = current->next;  //go to next node in list
    }

    return result;  //return resulting float
}

template <typename T>    //evaluate expression
float LinkedCalc<T>::evaluateExpression() {     //checks validity of expression 
    if (!validateExpression()) throw std::runtime_error("Invalid expression");

    Node<T>* current = head;    //pointers to current and previous nodes
    Node<T>* prev = nullptr;

    float result = 0;       
    while (current) {
        if (current->data == '*' || current->data == '/') { //check if multiplication or division
            char operation = current->data; //operation stored in variable
            Node<T>* node_next = current->next;     

            //convert left and right operands to floats
            float left_value = convertToFloat(prev ? prev : head);  //if prev not null prev returned, else head returned
            float right_value= convertToFloat(node_next);

            //multiply or divide
            result = (operation == '*') ? left_value * right_value : left_value / right_value;
            return result;
        }
        current = current->next;
    }
    
    //current pointer to the head
    current = head;
    result = convertToFloat(current);

    while (current) {   //addition and subtraction

        char operation = current->data; //operation sign stored in operation 

        current = current->next;        //move current

        float right_value = convertToFloat(current);   //convert to float

        if (operation == '+') result += right_value;    //addition and subtraction
        else if (operation == '-') result -= right_value;  
    }

    return result;

}