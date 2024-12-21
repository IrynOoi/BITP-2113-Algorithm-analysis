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
string randomData[100];
LibraryRecord record[10000];
LibraryRecord ori_record[10000];
// Function declarations
void ReadRandomData();
void DisplayData(LibraryRecord record[10000]);
void ReadLibraryRecord();
//Sorting relavent function
void ExecuteSorting(int option);
void BubbleSort(int n);
void Merge(int left, int mid, int right);
void MergeSort(int left, int right);
void SortingControl();
void UnsortData();
//void  ReadRandomData();

//Searching relevant functions
void ExecuteSearching(int option);
void SearchingControl();
int LinearSearch(string k);
int loopCount;


int main()
{
    system("cls");
    ReadRandomData();
    ReadLibraryRecord();


    int option;

    while (true)
    {
        option = 0;

        cout << string(10, '\n');
        cout << string(9, '\t') << "***********************************" << endl;
        cout << string(9, '\t') << "         MAIN MENU OF LIBRARY      " << endl;
        cout << string(9, '\t') << "***********************************" << endl;
        cout << string(9, '\t') << "[1] Display First 100 Data" << endl;
        cout << string(9, '\t') << "[2] Sorting" << endl;
        cout << string(9, '\t') << "[3] Searching" << endl;
        cout << string(9, '\t') << "[4] Analysis" << endl;
        cout << string(9, '\t') << "[5] Exit" << endl;
        cout << "\n\n" << string(9, '\t') << "Please enter your choice (Number 1 - 5 only): ";
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
            SearchingControl();
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

void ReadRandomData()
{
    fstream fin;
    string s;

    fin.open("random_data.csv", ios::in); // Open the file in read mode

    for (int i = 0; i < 100 && getline(fin, s); i++) // Read up to 100 lines or until EOF
    {
        randomData[i] = s; // Store the string directly into the array
    }

    fin.close(); // Close the file
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
    cout << "|" << left << setw(10) << "ReturnDate";
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
            cout << "|" << left << setw(10) << record[i].ReturnDate;
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

        case 3:
            UnsortData();
            break;

        case 4:
            system("cls");
            main();

        default:
            cout << string(9, '\t') << "Please enter the valid choice" << endl;
        }
    }
}

void ExecuteSorting(int option)
{
    copy_n(ori_record, 10000, record);
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



void UnsortData() // Function to reset the `record` array back to its original unsorted state
{
    // Copy the first 10000 elements from the 'ori_record' array to the 'record' array
    // 'ori_record' is assumed to store the original unsorted data, while 'record' holds the current data.
    copy_n(ori_record, 10000, record);

    // Display the updated (unsorted) 'record' array on the screen
    DisplayData(record);

    // Print a message to notify the user that the data has been unsorted
    cout << "\n\n" << string(9, '\t') << "Data Unsorted. Please press 'Enter' to continue...";

    // Wait for the user to press 'Enter' before proceeding
    cin.ignore();

    

    // Print 10 new lines to create some visual space on the console
    cout << string(10, '\n');
    system("pause");
    SortingControl();
}

void SearchingControl()
{
    int option;

    while (true)
    {
        cout << string(9, '\t') << "***********************************" << endl;
        cout << string(9, '\t') << "          LIBRARY DATA SYSTEM      " << endl;
        cout << string(9, '\t') << "***********************************" << endl;
        cout << string(9, '\t') << "[1] Linear Search 100 Random Data" << endl;
        cout << string(9, '\t') << "[2] Binary Search 100 Random Data" << endl;
        cout << string(9, '\t') << "[3] Improved Linear Search 100 Random Data" << endl;
        cout << string(9, '\t') << "[4] Back" << endl;

        cout << "\n\n" << string(9, '\t') << "Please enter your choice (Number 1 - 4 only): ";
        cin >> option;
        cin.clear();
        cin.ignore(10, '\n');
        system("cls");
        cout << string(10, '\n');

        switch (option)
        {
        case 1:
        case 2:
        case 3:
            ExecuteSearching(option);
            break;

        case 4:
            system("cls");
            return;

        default:
            cout << string(9, '\t') << "Please enter the valid choice" << endl;
        }
    }
}



void ExecuteSearching(int option)
{
    int index;
    string info[100][2];
    chrono::duration<double> elapsed_seconds;

    if (option == 1)
    {
        auto start = chrono::system_clock::now();

        for (int i = 0; i < 100; i++)
        {
            index = LinearSearch(randomData[i]);
            info[i][0] = randomData[i];
            info[i][1] = (index == -1) ? "Not Found" : to_string(index); // Convert index to string
        }

        auto end = chrono::system_clock::now();
        elapsed_seconds = end - start;
    }
    else if (option == 2)
    {
        auto start = chrono::system_clock::now();

        for (int i = 0; i < 100; i++)
        {
            // Uncomment and modify appropriately for binary search
            /*
            index = BinarySearch(randomData[i]);
            info[i][0] = randomData[i];
            info[i][1] = (index == -1) ? "Not Found" : to_string(index);
            */
        }

        auto end = chrono::system_clock::now();
        elapsed_seconds = end - start;
    }
    else
    {
        auto start = chrono::system_clock::now();

        for (int i = 0; i < 100; i++)
        {
            // Uncomment and modify appropriately for improved linear search
            /*
            index = ImprovedLinearSearch(randomData[i]);
            info[i][0] = randomData[i];
            info[i][1] = (index == -1) ? "Not Found" : to_string(index);
            */
        }

        auto end = chrono::system_clock::now();
        elapsed_seconds = end - start;
    }

    cout << string(9, '\t') << "=====================================" << endl;
    cout << string(9, '\t') << "|         LIBRARY  DATA              |" << endl;
    cout << string(9, '\t') << "=====================================" << endl;
    cout << string(9, '\t');
    printf("|%10s|%18s|%5s|", "BookID", "Is Found/Not Found", "Index");
    cout << "\n" << string(9, '\t') << "====================================" << endl;
    for (int i = 0; i < 100; i++)
    {
        cout << string(9, '\t');
        cout << "|" << left << setw(10) << info[i][0];
        if (info[i][1] == "Not Found") // Compare with "Not Found"
        {
            cout << "|" << left << setw(18) << "Not Found";
            cout << "|" << left << setw(5) << "  -  " << "|";
        }
        else
        {
            cout << "|" << left << setw(18) << "Is Found";
            cout << "|" << left << setw(5) << info[i][1] << "|";
        }
        cout << endl;
    }
    cout << string(9, '\t') << "=====================================" << endl;

    cout << "\n" << string(9, '\t') << "The duration searching time is " << elapsed_seconds.count() * 1000000 << " microseconds" << endl;
    cout << "\n\n" << string(9, '\t') << "Please press 'Enter' to continue...";
    cin.ignore();
    system("cls");
    cout << string(10, '\n');
}



int LinearSearch(string k)
{
    int i;
    for (i = 0; i < 10000; i++)
    {
        if (k == record[i].BookID)
        {
            return i;
        }
    }

    return -1;
}

