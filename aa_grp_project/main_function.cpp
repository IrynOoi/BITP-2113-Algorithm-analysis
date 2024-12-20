#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>


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
void  ReadRandomData();


int main()
{
    system("cls");
    ReadLibraryRecord();
    ReadRandomData();

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
          /*  SortingControl();*/
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
    cout << "\n" << string(5, '\t') << "======================================================================================================" << endl;
    for (int i = 0; i < 100; i++)
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

void ReadRandomData()
{

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
    cout << string(9, '\t') << "***************************" << endl;
    cout << string(9, '\t') << "         MAIN MENU         " << endl;
    cout << string(9, '\t') << "***************************" << endl;
    cout << string(9, '\t') << "[1] Display First 100 Data" << endl;
    cout << string(9, '\t') << "[2] Sorting" << endl;
    cout << string(9, '\t') << "[3] Searching" << endl;
    cout << string(9, '\t') << "[4] Analysis" << endl;
    cout << string(9, '\t') << "[5] Exit" << endl;
    cout << "\n\n" << string(9, '\t') << "Please enter your choice (Number 1 - 5 only): ";
}


