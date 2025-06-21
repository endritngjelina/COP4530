//////////////////////////////////////////////////////////////////////////////////////////////////////
/* Arrays coding problem */
#include <iostream>
#include <vector>

int removeElement(std::vector<int>& nums, int val) {
    // Use two-pointer technique
    int writeIndex = 0;  // Position to write the next non-val element
    
    // Iterate through the array
    for (int readIndex = 0; readIndex < nums.size(); readIndex++) {
        // If current element is not val, copy it to writeIndex position
        if (nums[readIndex] != val) {
            nums[writeIndex] = nums[readIndex];
            writeIndex++;
        }
        // If current element is val, skip it (don't increment writeIndex)
    }
    return writeIndex;  // writeIndex represents the new length
}

// Example usage
int main() {
    std::vector<int> nums = {0, 1, 2, 2, 3, 0, 4, 2};
    int val = 2;
    std::cout << "Original array: ";
    for (int num : nums) std::cout << num << " ";
    std::cout << std::endl;
    int newLength = removeElement(nums, val);
    std::cout << "Array after removing " << val << ": ";
    for (int i = 0; i < newLength; i++) std::cout << nums[i] << " ";
    std::cout << std::endl;
    std::cout << "New length: " << newLength << std::endl;
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//------
/* linked list coding problem*/
#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to insert a node at the end of the list
ListNode* insertNode(ListNode* head, int value) {
    ListNode* newNode = new ListNode(value);
    if (head == nullptr) return newNode;    // If list is empty, new node becomes head
    ListNode* current = head;   // Traverse to the end of the list
    while (current->next != nullptr) current = current->next;
    current->next = newNode;    // Insert the new node at the end
    return head;
}

int sumFirstHalf(ListNode* head) {
    // Edge cases
    if (head == nullptr) return 0;
    if (head->next == nullptr) return 0;
    ListNode* slow = head;  // Initialize pointers
    ListNode* fast = head;
    int sum = 0;
    
    // Move fast pointer two steps and slow pointer one step
    // When fast reaches end, slow will be at midpoint
    while (fast != nullptr && fast->next != nullptr) {
        sum += slow->val;   // Add current value to sum before moving slow pointer
        slow = slow->next;  // Move pointers
        fast = fast->next->next;
    }
    
    return sum;
}

// Function to print the list
void printList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        std::cout << current->val;
        if (current->next != nullptr)std::cout << " → ";
        current = current->next;
    }
    std::cout << std::endl;
}

int main() {
    ListNode* head = nullptr;
    head = insertNode(head, 1); // Insert nodes one by one
    head = insertNode(head, 2);
    head = insertNode(head, 3);
    head = insertNode(head, 4);
    head = insertNode(head, 5);
    head = insertNode(head, 6);
    std::cout << "Created linked list: ";
    printList(head);
    int result = sumFirstHalf(head);
    std::cout << "Sum of first half: " << result << std::endl;
    // Clean up memory
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}