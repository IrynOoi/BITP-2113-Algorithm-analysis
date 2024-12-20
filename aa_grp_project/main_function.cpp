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
void MergeSort(int left, int right);

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
    printf("|%10s|%10s|%10s|%8s|%10s|%15s|%20s|%11s|", "StudentID", "IssueDate", "DueDate", "ReturnDate", "FineAmount", "Renewal Count", "Reservation Status","BookID");
    cout << "\n" << string(5, '\t') << "========================================================================================================" << endl;
    for (int i = 0; i < 100; i++)//loop first 100 data
    {
        cout << string(5, '\t');
        cout << "|" << left << setw(10) << record[i].StudentID;
        cout << "|" << left << setw(10) << record[i].IssueDate;
        cout << "|" << left << setw(10) << record[i].DueDate;
        cout << "|" << left << setw(8) << record[i].ReturnDate;
        cout << "|" << left << setw(10) << record[i].FineAmount;
        cout << "|" << left << setw(15) << record[i].RenewalCount;
        cout << "|" << left << setw(20) << record[i].ReservationStatus ;
        cout << "|" << left << setw(11) << record[i].BookID << "|";
        cout << endl;

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
        cout << "Error" << endl;
        
    }


    system("cls");
    cout << string(10, '\n');
    try {
        DisplayData(record);
    }
    catch (const exception& e) {
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
    int mid = (left + right) / 2;
    if (left < right)
    {
        MergeSort(left, mid); //first half sub array
        MergeSort(mid + 1, right); //second half sub array
        Merge(left, mid, right);
    }
}



void Merge(int left, int mid, int right)
{
    LibraryRecord temp[10000];
    // left -> first element 
    // right -> last element

    int i = left; //index of left sub array
    int j = mid + 1; //index of right sub array
    int k = left; //index of array

    // Merge two subarrays into temp
    while (i <= mid && j <= right)
    {
        if (record[i].StudentID <= record[j].StudentID)
        {
            temp[k] = record[i];
            i++;
            k++;
        }
        else
        {
            temp[k] = record[j];
            j++;
            k++;
        }
        loopCount++;
    }

    //copy remaining element from left to temp
    while (i <= mid)
    {
        temp[k] = record[i];
        i++;
        k++;
    }

    //copy remaining element from right to temp
    while (j <= right)
    {
        temp[k] = record[j];
        j++;
        k++;
    }

    //copy element from temp to original array
    for (int m = left; m <= right; m++)
    {
        record[m] = temp[m];
    }
}


