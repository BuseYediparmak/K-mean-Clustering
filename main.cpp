#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <typeinfo>
#include <iomanip>

using namespace std;

class Data
{
    float value;
    int group;

public:
    void setValue(float newValue) { value = newValue; }
    void setGroup(int i) { group = i; }
    float getValue() { return value; }
    int getGroup() { return group; }
};

int main()
{
    Data array[388];
    float input;
    float min = 0, max = 0; // I will use the smallest and biggest data as the initial central values for k-means
    int size = 0;           // to follow the number of values that are read from the text file.

    ifstream file("input.txt");

    while (file >> input)
    {
        if (input > max || max == 0) // I set the first value as max and then compare each value that I read from the file
        {
            max = input;
        }
        if (input < min || min == 0) // I set the first value as min and then compare each value that I read from the file
        {
            min = input;
        }
        array[size].setValue(input);
        size++;
    }
    file.close();

    // initial centers will be the min and max value
    float center1 = min;
    float center2 = max;
    // this variable is for counting the iterations.
    int iteration = 0;

    while (true)
    {
        iteration++;
        // these are to calculate the average value of the group
        float average1 = 0;
        float average2 = 0;
        // to find the average value, we need to know the number of values in a group
        int count1 = 0;
        int count2 = 0;

        for (int i = 0; i < size; i++)
        {
            // calculating the distance of both centers.
            float firstDistance = array[i].getValue() - center1;
            float secondDistance = array[i].getValue() - center2;

            // absolute values are need to be compared
            if (abs(firstDistance) <= abs(secondDistance))
            {
                array[i].setGroup(1);            // if its closer to center1, then its group is 1
                average1 += array[i].getValue(); // all values in group1 are getting summed up
                count1++;                        // count increases everytime we add a new value
            }
            else
            {
                array[i].setGroup(2);            // if its closer to center2, then its group is 2
                average2 += array[i].getValue(); // all values in group2 are getting summed up
                count2++;                        // count increases everytime we add a new value
            }
        }
        // Sums are divided by number of values and average values are found.
        average1 /= count1;
        average2 /= count2;

        cout << iteration << ". Iteration:" << endl;
        cout << "First groups center is " << center1 << "  -  Second groups center is " << center2 << "." << endl;
        cout << left;
        cout << setw(25) << "Count of first group: " << count1 << "     Average of the first group:  " << average1 << endl;

        cout << setw(25) << "Count of second group: " << count2 << "     Average of the first group:  " << average2 << endl
             << endl;
        ;
        if (average1 == center1 && average2 == center2)
        {
            cout << "Central values did not change at the last step, so iteration is over. " << average1 << " and " << average2 << " are centers of clusters." << endl;
            cout << "First cluster has " << count1 << " elements and the second cluster has " << count2 << " elements." << endl;
            break; // if average is equal to central value, then iteration is over and final values are found
        }
        else
        {
            // if iteration is not over, loop continues with averages as new central values
            center1 = average1;
            center2 = average2;
        }
    }

    // this is for styling the output
    int count = 0;

    cout << endl
         << "-----FIRST CLUSTER-----" << endl;
    for (int i = 0; i < size; i++)
    {
        if (array[i].getGroup() == 1)
        {
            cout << left; // this is also for styling the output
            cout << setw(7) << array[i].getValue();
            count++;
            if (count % 17 == 0)
            {
                cout << endl;
            }
        }
    }
    cout << endl
         << endl
         << endl;

    // this is for styling the output
    count = 0;

    cout << "-----SECOND CLUSTER-----" << endl;
    for (int i = 0; i < size; i++)
    {
        if (array[i].getGroup() == 2)
        {
            cout << left;
            cout << setw(7) << array[i].getValue();
            count++;
            if (count % 17 == 0)
            {
                cout << endl;
            }
        }
    }
    cout << endl;

    return 0;
}