#include "QS.h"

QS::QS() {
    items = new int[0];
    capacity = 0;
    count = 0;
}

QS::~QS() {
    clear();
}

/**
 * sort()
 *
 * Sorts elements in a subarray.  After this function is called, every
 * element between the given left and right indices is less than or
 * equal to its successor.
 *
 * Does nothing if the array is empty, or if right is greater than left.
 */
void QS::sort(int left, int right) {
    if (left > right) {
        return;
    }
    
    int pivotIdx = medianOfThree(left, right);
    if (pivotIdx == -1) {
        return;
    }
    
    int midBound = partition(left, right, pivotIdx);
    if (midBound == -1) {
        return;
    }
    
    sort(left, midBound - 1);
    sort(midBound + 1, right);
}

/**
 * sortAll()
 *
 * Sorts elements of the array.  After this function is called, every
 * element in the array is less than or equal its successor.
 *
 * Does nothing if the array is empty.
 */
void QS::sortAll() {
    int leftBound = 0;
    int rightBound = getSize() - 1;
    sort(leftBound, rightBound);
}

/**
 * medianOfThree()
 *
 * The median of three pivot selection has two parts:
 *
 * 1) Calculates the middle index by averaging the given left and right indices:
 *
 * middle = (left + right)/2
 *
 * 2) Then bubble-sorts the values at the left, middle, and right indices.
 *
 * After this method is called, data[left] <= data[middle] <= data[right].
 * The middle index will be returned.
 *
 * Returns -1 if the array is empty, if either of the given integers
 * is out of bounds, or if the left index is not less than the right
 * index.
 *
 * @param left
 *         The left boundary for the subarray from which to find a pivot
 * @param right
 *         The right boundary for the subarray from which to find a pivot
 * @return
 *         The index of the pivot (middle index); -1 if provided with invalid input.
 */
int QS::medianOfThree(int left, int right) {
    if (left < 0 || right > getSize() - 1 || left >= right) {
        return -1;
    }
    
    int middle = (left + right) / 2;
    int tmpVal;
    
    if (items[middle] < items[left]) {
        tmpVal = items[middle];
        items[middle] = items[left];
        items[left] = tmpVal;
    }
    if (items[right] < items[left]) {
        tmpVal = items[right];
        items[right] = items[left];
        items[left] = tmpVal;
    }
    if (items[middle] > items[right]) {
        tmpVal = items[middle];
        items[middle] = items[right];
        items[right] = tmpVal;
    }
    
    return middle;
}

/**
 * Partitions a subarray around a pivot value selected according to
 * median-of-three pivot selection.  Because there are multiple ways to partition a list,
 * we will follow the algorithm on page 611 of the course text when testing this function.
 *
 * The values which are smaller than the pivot should be placed to the left
 * of the pivot; the values which are larger than the pivot should be placed
 * to the right of the pivot.
 *
 * Returns -1 if the array is null, if either of the given integers is out of
 * bounds, or if the first integer is not less than the second integer, or if the
 * pivot is not within the sub-array designated by left and right.
 *
 * @param left
 *         The left boundary for the subarray to partition
 * @param right
 *         The right boundary for the subarray to partition
 * @param pivotIndex
 *         The index of the pivot in the subarray
 * @return
 *         The pivot's ending index after the partition completes; -1 if
 *          provided with bad input.
 */
int QS::partition(int left, int right, int pivotIndex) {
    // Check for invalid arguments
    if (getSize() == 0 || left < 0 || right >= getSize() || left >= right || pivotIndex < left || pivotIndex > right) {
        return -1;
    }
    
    // Save pivot value
    int pivotVal = items[pivotIndex];
    
    // Swap the pivot with leftmost
    int tmpVal = items[left];
    items[left] = items[pivotIndex];
    items[pivotIndex] = tmpVal;
    
    // Left and right indices
    int leftIdx = left + 1;
    int rightIdx = right;
    
    do {
        // Increment left until we're greater than the pivot, or hit right boundary.
        while (items[leftIdx] <= pivotVal && leftIdx < right) {
            leftIdx += 1;
        }
        
        // Decrement right until we're less than or equal to the pivot, or hit low boundary.
        while (items[rightIdx] > pivotVal && rightIdx > left) {
            rightIdx -= 1;
        }
        
        // If left < right, swap them.
        if (leftIdx < rightIdx) {
            tmpVal = items[leftIdx];
            items[leftIdx] = items[rightIdx];
            items[rightIdx] = tmpVal;
        }

    } while (leftIdx < rightIdx);
    
    tmpVal = items[left];
    items[left] = items[rightIdx];
    items[rightIdx] = tmpVal;
    
    return rightIdx;
}

/**
 * Produces a comma delimited string representation of the array. For example: if my array
 * looked like {5,7,2,9,0}, then the string to be returned would look like "5,7,2,9,0"
 * with no trailing comma.  The number of cells included equals the number of values added.
 * Do not include the entire array if the array has yet to be filled.
 *
 * Returns an empty string, if the array is NULL or empty.
 *
 * @return
 *        The string representation of the current array
 */
string QS::getArray() const {
    string result = "";
    
    for (int i = 0; i < getSize(); i++) {
        result += to_string(items[i]);
        
        if (i < getSize() - 1) {
            result += ",";
        }
    }
    
    return result;
}

/**
 * Returns the number of elements which have been added to the array.
 */
int QS::getSize() const {
    return count;
//    return sizeof(items) / sizeof(*items);
}

/**
 * Adds the given value to the end of the array starting at index 0.
 * For example, the first time addToArray is called,
 * the give value should be found at index 0.
 * 2nd time, value should be found at index 1.
 * 3rd, index 2, etc up to its max capacity.
 *
 * If the array is filled, do nothing.
 * returns true if a value was added, false otherwise.
 */
bool QS::addToArray(int value) {
    int endIndex = getSize();
    if (endIndex >= capacity) {
        return false;
    }
    
    items[endIndex] = value;
    count += 1;
    
    return true;
}

/**
 * Dynamically allocates an array with the given capacity.
 * If a previous array had been allocated, delete the previous array.
 * Returns false if the given capacity is non-positive, true otherwise.
 *
 * @param capacity
 *        The size of array
 * @return
 *        True if the array was created, false otherwise
 */
bool QS::createArray(int capacity) {
    if (capacity < 0) {
        return false;
    }
    
    clear();
    items = new int[capacity];
    this->capacity = capacity;
    
    return true;
}

/**
 * Resets the array to an empty or NULL state.
 */
void QS::clear() {
    if (getSize() == 0) { return; }
    delete[] items;
    count = 0;
}
