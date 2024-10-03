#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

// Class to represent an Experiment
class Experiment {
public:
    string exp_name;
    int deadline; // deadline in terms of date (e.g., 3 for the 3rd of the month)

    Experiment() {}
    Experiment(string name, int d) : exp_name(name), deadline(d) {}
};

// Class to represent a Subject
class Subject {
public:
    int id;
    int credits;
    string name;
    int no_exp;
    bool is_lab;  // Boolean to check if it's a lab subject
    int pages;
    float priority;
    vector<Experiment> experiments;  // Use vector to store experiments dynamically

    Subject() {}

    // Constructor to initialize a subject
    Subject(int i, int c, string n, bool lab) : id(i), credits(c), name(n), is_lab(lab) {
        if (is_lab) {
            cout << "Enter the number of lab experiments to write up: \n";
            cin >> no_exp;
            experiments.resize(no_exp);  // Resize the vector to hold experiments
        }
    }

    // Function to assign experiments with their deadlines
    void assignExperiments() {
        for (int i = 0; i < no_exp; i++) {
            int temp_deadline;
            string temp_name;
            cout << "Enter Experiment " << i + 1 << " name and deadline (day of the month): \n";
            cin >> temp_name >> temp_deadline;
            experiments[i] = Experiment(temp_name, temp_deadline);
        }
    }

    // Function to calculate time required to complete the lab work
    void timeCalculator() {
        pages = no_exp * 5;  // Assume 5 pages per experiment
        int total_time = pages * 5;  // 5 minutes per page
        int hours = total_time / 60;
        cout << "Total time required for " << name << ": " << hours << " hours.\n";
    }

    // Function to calculate average deadline for prioritization
    float calculateAverageDeadline() {
        int sum = 0;
        for (int i = 0; i < no_exp; i++) {
            sum += experiments[i].deadline;
        }
        return (float)sum / no_exp;
    }
};

// Function to calculate priority of subjects based on experiment deadlines
bool subjectPriorityComparator(Subject& a, Subject& b, int current_date) {
    // Priority is based on the closest deadline
    float a_avg_deadline = a.calculateAverageDeadline();
    float b_avg_deadline = b.calculateAverageDeadline();

    // The subject with the most urgent experiment comes first
    return a_avg_deadline < b_avg_deadline;
}

int main() {
    int current_date;
    cout << "Enter today's date (e.g., 3 for the 3rd of the month): ";
    cin >> current_date;

    int num_subjects;
    cout << "Enter the number of subjects: ";
    cin >> num_subjects;

    vector<Subject> subjects(num_subjects);  // Create a vector of subjects

    // Input subject details
    for (int i = 0; i < num_subjects; i++) {
        int id, credits;
        string name;
        bool is_lab;

        cout << "Enter Subject " << i + 1 << " ID, Credits, Name, and if it's a lab subject (1 for yes, 0 for no): \n";
        cin >> id >> credits >> name >> is_lab;

        subjects[i] = Subject(id, credits, name, is_lab);

        if (is_lab) {
            subjects[i].assignExperiments();
        }
    }

    // Sort subjects based on experiment deadlines (closer deadlines have higher priority)
    sort(subjects.begin(), subjects.end(), [current_date](Subject& a, Subject& b) {
        return subjectPriorityComparator(a, b, current_date);
    });

    // Display prioritized subjects
    cout << "\nPrioritized subjects based on deadlines:\n";
    for (int i = 0; i < num_subjects; i++) {
        cout << subjects[i].name << " with average deadline: " << subjects[i].calculateAverageDeadline() << "\n";
    }

    return 0;
}
