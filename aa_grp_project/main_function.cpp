#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>


using namespace std;


struct LibraryRecord 
{
    string StudentID, BookID, IssueDate, DueDate, ReturnDate, ReservationStatus;
    double FineAmount;
    int RenewalCount;
    
};

LibraryRecord record[10000];
LibraryRecord ori_record[10000];
// Function declarations
void DisplayData(LibraryRecord record[10000]);
void ReadLibraryRecord();
void MainMenu();
//Sorting relavent function
void ExecuteSorting(int option);
void BubbleSort(int n);
void Merge(int left, int mid, int right);
void MergeSort(int left, int right);
void SortingControl();

//void  ReadRandomData();

int loopCount;


int main()
{
    system("cls");
    ReadLibraryRecord();

    int option;

    while (true)
    {
        option = 0;

        cout << string(10, '\n');
        MainMenu();
        cin >> option;
        cin.clear();
        cin.ignore(10, '\n');
        system("cls");
        cout << string(10, '\n');

        switch (option)
        {
        case 1:
            DisplayData(record);
            cout << "\n\n" << string(9, '\t') << "Please press 'Enter' to continue... ";
            cin.ignore();
            system("cls");
            break;

        case 2:
            SortingControl();
            break;

        case 3:
           /* SearchingControl();*/
            break;

        case 4:
            /*AnalysisControl();*/
            break;

        case 5:
            cout << string(9, '\t') << "system closed" << endl;
            return 0;
            break;

        default:
            cout << string(9, '\t') << "Please enter the valid choice" << endl;
        }
    }
}

void DisplayData(LibraryRecord record[10000])
{
    cout << string(5, '\t') << "=========================================================================================================" << endl;
    cout << string(5, '\t') << "|                                              Library Record Data                                      |" << endl;
    cout << string(5, '\t') << "=========================================================================================================" << endl;
    cout << string(5, '\t');
    cout << "|" << left << setw(10) << "StudentID";
    cout << "|" << left << setw(10) << "IssueDate";
    cout << "|" << left << setw(10) << "DueDate";
    cout << "|" << left << setw(8) << "ReturnDate";
    cout << "|" << left << setw(10) << "FineAmount";
    cout << "|" << left << setw(15) << "Renewal Count";
    cout << "|" << left << setw(20) << "Reservation Status";
    cout << "|" << left << setw(11) << "BookID" << "|" << endl;
    cout << string(5, '\t') << "=========================================================================================================" << endl;

    for (int i = 0; i < 100; i++) // Loop through the first 100 data
    {
        // Check if the record contains valid data
        if (!record[i].StudentID.empty()) // Assuming StudentID is a string
        {
            cout << string(5, '\t');
            cout << "|" << left << setw(10) << record[i].StudentID;
            cout << "|" << left << setw(10) << record[i].IssueDate;
            cout << "|" << left << setw(10) << record[i].DueDate;
            cout << "|" << left << setw(8) << record[i].ReturnDate;
            cout << "|" << left << setw(10) << record[i].FineAmount;
            cout << "|" << left << setw(15) << record[i].RenewalCount;
            cout << "|" << left << setw(20) << record[i].ReservationStatus;
            cout << "|" << left << setw(11) << record[i].BookID << "|" << endl;
        }
    }
    cout << string(5, '\t') << "=========================================================================================================" << endl;
}



void ReadLibraryRecord()
{
    fstream fin;

    fin.open("library_data.csv", ios::in);

    if (!fin.is_open())
    {
        cout << "Error: Could not open file 'library_data.csv'" << endl;
        return;
    }

    vector<string> row;
    string line, word;

    // Skip the header line
    getline(fin, line);

    int i = 0;
    try
    {
        while (getline(fin, line) && i < 10000) // Limit to 10,000 records
        {
            row.clear();
            stringstream s(line);

            // Parse each field in the row
            while (getline(s, word, ','))
            {
                row.push_back(word);
            }

            // Check if the row has enough fields to avoid out-of-range errors
            if (row.size() < 8)
            {
                cout << "Error: Incomplete data in row " << i + 1 << endl;
                continue;
            }

            // Assign fields to the struct
            ori_record[i].StudentID = row[0];
            ori_record[i].IssueDate = row[1];
            ori_record[i].DueDate = row[2];
            ori_record[i].ReturnDate = row[3];
            ori_record[i].FineAmount = stod(row[4]); // Convert to double
            ori_record[i].RenewalCount = stoi(row[5]); // Convert to int
            ori_record[i].ReservationStatus = row[6];
            ori_record[i].BookID = row[7];


            i++;
        }

        copy_n(ori_record, i, record); // Copy parsed records
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
        cout << "Failed at record index: " << i << endl;
    }

    fin.close();
}




void MainMenu()
{
    cout << string(9, '\t') << "***********************************" << endl;
    cout << string(9, '\t') << "         MAIN MENU OF LIBRARY      " << endl;
    cout << string(9, '\t') << "***********************************" << endl;
    cout << string(9, '\t') << "[1] Display First 100 Data" << endl;
    cout << string(9, '\t') << "[2] Sorting" << endl;
    cout << string(9, '\t') << "[3] Searching" << endl;
    cout << string(9, '\t') << "[4] Analysis" << endl;
    cout << string(9, '\t') << "[5] Exit" << endl;
    cout << "\n\n" << string(9, '\t') << "Please enter your choice (Number 1 - 5 only): ";
}


void SortingControl()
{
    system("cls");
    cout << string(10, '\n');

    int option;
    cout << string(9, '\t') << "****************" << endl;
    cout << string(9, '\t') << "  SORTING MENU  " << endl;
    cout << string(9, '\t') << "****************" << endl;
    cout << string(9, '\t') << "[1] Bubble Sort" << endl;
    cout << string(9, '\t') << "[2] Merge Sort" << endl;
    cout << string(9, '\t') << "[3] Unsort" << endl;
    cout << string(9, '\t') << "[4] Back" << endl;

    cout << "\n\n" << string(9, '\t') << "Please enter your choice (Number 1 - 3 only): ";

    while (true)
    {
       
        cin >> option;
        cin.clear();
        cin.ignore(10, '\n');
        system("cls");
        cout << string(10, '\n');

        switch (option)
        {
        case 1:
        case 2:
            ExecuteSorting(option);
            break;

        /*case 3:
            UnsortData();
            break;*/

        case 4:
            system("cls");
            return;

        default:
            cout << string(9, '\t') << "Please enter the valid choice" << endl;
        }
    }
}

void ExecuteSorting(int option)
{
    // Initialize a variable 'loopCount' to keep track of the number of loops
    loopCount = 0;

    // Create a variable 'elapsed_seconds' to store the time duration of the sorting process.
    chrono::duration<double> elapsed_seconds;

    // Print a message to let the user know that the program is processing and the user should wait.
    cout << string(9, '\t') << "Please wait for a while..." << endl;

    // Check if the user has chosen the option to perform BubbleSort (assuming 'option' is provided earlier in the code).
    if (option == 1)
    {
        // Record the start time of the BubbleSort operation using the system clock.
        auto start = chrono::system_clock::now();

        // Call the BubbleSort function with an array of size 10,000 (assuming BubbleSort takes care of sorting the array).
        BubbleSort(10000);

        // Record the end time after the sorting operation completes.
        auto end = chrono::system_clock::now();

        // Calculate the elapsed time between the start and end using the difference between the two times.
        elapsed_seconds = end - start;
        

    }
    else  // If the user didn't choose option 1, assume they want to run MergeSort instead.
    {
        // Record the start time of the MergeSort operation using the system clock.
        auto start = chrono::system_clock::now();

        // Call the MergeSort function with the array indices to sort (from index 0 to index 9999).
        MergeSort(0, 9999);

        // Record the end time after the sorting operation completes.
        auto end = chrono::system_clock::now();

        // Calculate the elapsed time between the start and end using the difference between the two times.
        elapsed_seconds = end - start;
        
    }


    system("cls");
    cout << string(10, '\n');
    try 
    {
        DisplayData(record);
    }
    catch (const exception& e)
    {
        cerr << "Error in DisplayData: " << e.what() << endl;
        throw;
    }

    cout << "\n\n" << string(9, '\t') << "Total numbers of swaps: " << loopCount << endl;
    cout << string(9, '\t') << "The duration time is " << elapsed_seconds.count() << " second" << endl;
    cout << "\n\n" << string(9, '\t') << "Please press 'Enter' to continue...";
    cin.ignore();
    
    system("pause");
    SortingControl();
}

void Swap(LibraryRecord& x, LibraryRecord& y)
{
    LibraryRecord temp = x;
    x = y;
    y = temp;
    loopCount++;
}

void BubbleSort(int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int k = 0; k < n - i - 1; k++)
        {
            if (record[k].StudentID > record[k + 1].StudentID)
            {
                Swap(record[k], record[k + 1]);
            }
        }
    }
}
void MergeSort(int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        MergeSort(left, mid);
        MergeSort(mid + 1, right);

        Merge(left, mid, right);
    }
}




void Merge(int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    LibraryRecord* leftArray = new LibraryRecord[n1];
    LibraryRecord* rightArray = new LibraryRecord[n2];

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++) {
        leftArray[i] = record[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = record[mid + 1 + j];
    }

    // Merge the temp arrays back into record[left...right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].StudentID <= rightArray[j].StudentID) {
            record[k] = leftArray[i];
            i++;
        }
        else {
            record[k] = rightArray[j];
            j++;
        }
        k++;
        loopCount++;
    }

    // Copy remaining elements of leftArray
    while (i < n1) {
        record[k] = leftArray[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightArray
    while (j < n2) {
        record[k] = rightArray[j];
        j++;
        k++;
    }

    // Free dynamically allocated memory
    delete[] leftArray;
    delete[] rightArray;
}




