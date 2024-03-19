

// Function to search for an item by position
Node* searchByPosition(List *list, int position) {
    if (list == NULL || list->head == NULL || position <= 0) {
        return NULL; // Empty list or invalid position
    }

    Node *current = list->head;
    int count = 1; // Start counting from the first node

    // Traverse the list until the desired position or back to the head
    do {
        if (count == position) {
            return current; // Found the node at the specified position
        }
        current = current->link; // Move to the next node
        count++;
    } while (current != list->head);

    // If the position is greater than the number of nodes in the list,
    // return NULL indicating that the position is out of bounds
    return NULL;
}
