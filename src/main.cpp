#include <iostream>
#include "Student.h"
#include <vector>
#include <algorithm>
using namespace std;

int choices() // Function created to get user's input
{
    cout << "What would you like to do?  Please enter a number 1-4." << endl;
    cout << "1) Add; 2) Sort; 3) Print; 4) Quit" << endl;
    // Integer n is created to take the input of the user's choice.
    int n; 
    cin >> n; 
    while (n > 4 || n < 1) // Exception handling if user does not pick an integer between 4 and 1
    {
        cout << "Error! Please enter a valid input" << endl;
        cin >> n;
    }
    return n; // Return user's choice
}
void add(vector<Student> &s) // Function to add student information into database
{
    int numOfStudents; // A variable is created to determine the number of students adding into vector
    cout << "How many students would you like to add?" << endl; 
    cin >> numOfStudents; // User input
    /*  
    Within the for loop:
    - Iterates through the number of students inputted previously
    - Create a temporary student variable
    - Use .readStudentInfo() method from class
    - Push the information recieved from method into vector
    */
    for (int i = 0; i < numOfStudents; i++)
    {
        Student temp;
        temp.readStudentInfo();
        s.push_back(temp);
    }
};

void print(vector<Student> s) // Function used to print out information from database
{
    cout << "Name" << " " << "ID" << " " << "GPA" << endl; // Acts as a header for information given
    for (int i = 0; i < s.size(); i++)
    {
        s[i].display(); // Couts each student's information separately
    }
};

template <class dataType> // A function template was added to accomadate for any information

vector<dataType> merge(vector<dataType> left, vector<dataType> right, int comparison (Student, Student)) // The merge will input a left vector, right vector and a comparison function
{
    vector<dataType> final; // A third vector is initialized
    while (left.size() > 0 || right.size() > 0) // While loop that checks whether there are elements in either of the vectors
    {
        if (left.size() > 0 && right.size() > 0) // Conditional checks if BOTH vectors have elements
        {
            if (comparison(left.at(0), right.at(0)) <= 0) // Refer to comparisons from "Ascend and Descend"
            {
                final.push_back(left.at(0)); // Pushes first element of left vector into final vector
                left.erase(left.begin()); // Removes first element in left vector
            }
            else
            {
                final.push_back(right.at(0)); // Pushes first element of right vector into final vector
                right.erase(right.begin()); // Removes first element in right vector
            }
        }
        else if (left.size() > 0) // If only one vector had elements, the next condition is to check which vector had elelemtns
        {
            for (int i = 0; i < left.size(); i++)
            {
                final.push_back(left.at(i)); // Push remaining elements in left vector into final vector 
            }
            break;
        }
        else // Else condition identifies that the right vector is the only vector with elelements
        {
            for (int i = 0; i < right.size(); i++)
            {
                final.push_back(right.at(i)); // Push remaining elements in right vector into final vector 
            }
            break;
        }
    }
    return final; // Returns the completed merged vector
}

template <class dataType> // Function template again

vector<dataType> mergeSort(vector<dataType> V, int comparison (Student s1, Student s2)) // Takes one vector as input with comparison function
{
    if (V.size() == 1) // If there is only vector element left, return it
    // This base case checks for when the recursively called vectors (left and right) reach one element left in the vector
    {
        return V;
    }
    else
    {
        vector<dataType> left, right; // Initialize two more vectors (left, right)
        int mid = V.size() / 2; // The vector is split into half and a mid variable is intiialized; LOG_2(n)
        for (int i = 0; i < V.size(); i++)
        {
            if (i < mid)
            {
                left.push_back(V[i]); // Move elements left of mid position to left vector
            }
            else
            {
                right.push_back(V[i]); // Move elements right of mid position to right vector
            }
        }
        vector<dataType> sortleft = mergeSort(left, comparison); 
        // Recursively call mergeSort with the left side of the original vector until there is only one element left in the vector
        vector<dataType> sortright = mergeSort(right, comparison);
        // Recursively call mergeSort with the right side of the original vector until there is only one element left in the vector
        return merge(sortleft, sortright, comparison); // Merge the left and right sorted vectors to create the final vector
    }
}

/*
ASCEND AND DESCEND FUNCTIONALITY:
In the paramters listed in merge() and mergeSort() the comparison function was the third parameter
Intially, writing the code, the merge function was written to make mergeSort sort in ascending order.
However, the final project requires us to ask the user if they want to ascend or descend the sort.
This is where the comparison function comes in.  In place of the if (comparison(______)) statement is the ascend and descend functions below
If the user decides to choose either of the two, the function would return a value based on the original conditional (if (element1 </> element2))
The else if case in both ascend and descend do not too much, as it would simply return a zero value and produce the same result.
In both cases, the return value created from each function is then compared to be <= 0.  From there on, the original merge and mergeSort continues on.
*/


int ascend(Student s1, Student s2)
{
    if (s1.getGPA() < s2.getGPA())
    {
        return -1;
    }
    else if (s1.getGPA() == s2.getGPA())
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int descend(Student s1, Student s2)
{
    if (s1.getGPA() < s2.getGPA())
    {
        return 1;
    }
    else if (s1.getGPA() == s2.getGPA())
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void sort(vector<Student> &s) // The sort function is the interface of the mergeSort above
{
    // First, we must determine whether or not the user wants the studens to be sorted
    // in ascending or descending order...
    cout << "Would you like to sort in ascending or descending order" << endl;
    cout << "Enter 0 for descending, 1 for ascending..." << endl;
    int temp; // Get a temp variable to get user input (1 or 0)
    cin >> temp;
    while (temp > 1 || temp < 0) // Exception handle for input not 0 or 1
    {
        cout << "Please enter either 0 or 1!" << endl;
        cin >> temp;
    }
    if (temp == 0) // If user chooses 0, the information will sort descending
    {
        s = mergeSort(s, descend);
    }
    else // Else, information storted ascending
    {
        s = mergeSort(s, ascend);
    }
};

int main()
{
    cout << "Welcome to the student database system!" << endl;
    vector<Student> sV; // Initialize vector for all students' information
    int choice = choices(); // Create choice variable and assign it to choices() function
    // The while loop below applies what the choices function was supposed to do
    while (choice != 4)
    {
        if (choice == 1)
        {
            add(sV);
        }
        else if (choice == 2)
        {
            sort(sV);
            cout << "Sorted!" << endl;
        }
        else
        {
            print(sV);
        }
        choice = choices();
    }
    // If the user chooses 4) Exit, the while loop will end and the program will terminate.
    cout << "Terminating program..." << endl;
    return 0;
}

/*
MERGE SORT TIME COMPLEXITY ANALYSIS
EX USED : Vector : {1, 2, 3}
BEST CASE SCENARIO: The vector is already sorted in the correct order EX: {1,2,3,4}
AVERAGE CASE SCENARIO: The vector is partially sorted EX: {1,3,2,4}
WORST CASE SCENARIO: The vector is sorted in the wrong order. EX: If wanting to sort in ascending order - {4, 3, 2, 1}

merge in BEST CASE
1) Initializes final vector : +1
2) While loop : n
3) Any of the if statement : n
3a) pushback and erase calls : 2n
4) return final : + 1
Total: 4n + 2
Transfer onto...
||
V

mergeSort in BEST CASE ABOVE
1) Checks if size of vector is 1: + 1
2) Initializes vectors (left, right): + 2
3) Initializes mid to be vector size / 2 : logn
4) For loop using size of vector: n
4a) Checks if i < mid : n
4b) Regardless, pushback to either left or right vector : n
5) Create sortLeft assigning it to mergeSort(left) : nlogn
6) Create sortRight assigning it to mergeSort(right) : nlogn
7) return merge(sortleft, sortright) : 4n + 2
Total: 2nlog_2n + 3n + log_2n + 5

Although the Best case was only calculated, the average case and worst case would have the same result.
Within each of the cases, the original vector is broken into separate vectors (log_2n) until eacch vector has one remaining element in the vector
Because of this, each element is checked regardless, making the 2nlog_2n always appear.

Big O for all three: O(nlog(n))
How does O(nlog(n)) apply to our merge sort?
- Each element must be checked in the vector, hence the n
- The vector continues to split into two (2 vectors, 4 vectors, 8 vectors....) which causes log_2(n) to appear
- The log_2(n) turns into just log(n) and is put with the original n
- Putting it all together, the algorithm is O(nlog(n))
*/
