#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
#include<limits>

using namespace std;

struct Task{
    int priority;
    string deadline;
    string description;
};

void swapTasks(Task &a, Task &b){
    Task temp = a;
    a = b;
    b = temp;
}

void heapifyUp(vector<Task> &heap, int index){
    if(index == 0) return;

    int parent = (index - 1) / 2;
    if(heap[index].priority < heap[parent].priority){
        swapTasks(heap[index], heap[parent]);
        heapifyUp(heap, parent);
    }
}

void heapifyDown(vector<Task> &heap, int index){
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int size = heap.size();

    if(left < size && heap[left].priority < heap[smallest].priority)
        smallest = left;

    if(right < size && heap[right].priority < heap[smallest].priority)
        smallest = right;

    if(smallest != index){
        swapTasks(heap[index], heap[smallest]);
        heapifyDown(heap, smallest);
    }
}

void addTask(vector<Task> &heap){
    Task t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nEnter task description: ";
    getline(cin, t.description);

    cout << "Enter deadline (YYYY-MM-DD): ";
    getline(cin, t.deadline);

    cout << "Enter priority (lower = higher importance): ";
    cin >> t.priority;

    heap.push_back(t);
    heapifyUp(heap, heap.size() - 1);

    cout << "Task added successfully!\n";
}

void displayTasks(vector<Task> heap){
    if(heap.empty()){
        cout << "\nNo tasks available.\n";
        return;
    }

    cout << "\n----- Task List (Sorted by Priority) -----\n";

    while(!heap.empty()){
        cout << "Priority: " << setw(3) << heap.front().priority
             << " | Deadline: " << setw(10) << heap.front().deadline
             << " | Description: " << heap.front().description << endl;

        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(heap, 0);
    }
}

int findTaskIndex(vector<Task> &heap, const string &desc){
    for(int i = 0; i < heap.size(); ++i){
        if(heap[i].description == desc)
            return i;
    }
    return -1;
}

void updateTask(vector<Task> &heap){
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nEnter description of task to update: ";
    string desc;
    getline(cin, desc);

    int index = findTaskIndex(heap, desc);
    if(index == -1){
        cout << "Task not found!\n";
        return;
    }

    cout << "Enter new description: ";
    getline(cin, heap[index].description);

    cout << "Enter new deadline: ";
    getline(cin, heap[index].deadline);

    cout << "Enter new priority: ";
    cin >> heap[index].priority;

    heapifyUp(heap, index);
    heapifyDown(heap, index);

    cout << "Task updated!\n";
}

void deleteTask(vector<Task> &heap){
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nEnter description of task to delete: ";
    string desc;
    getline(cin, desc);

    int index = findTaskIndex(heap, desc);
    if(index == -1){
        cout << "Task not found!\n";
        return;
    }

    heap[index] = heap.back();
    heap.pop_back();

    if(!heap.empty()){
        heapifyUp(heap, index);
        heapifyDown(heap, index);
    }

    cout << "Task deleted!\n";
}

int main(){
    vector<Task> taskHeap;
    int choice;

    do{
        cout << "\n========== Task Scheduler ==========\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Update Task\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        switch(choice){
            case 1: addTask(taskHeap); break;
            case 2: displayTasks(taskHeap); break;
            case 3: updateTask(taskHeap); break;
            case 4: deleteTask(taskHeap); break;
            case 5: cout << "\nExiting...\n"; break;
            default: cout << "Invalid option! Try again.\n";
        }

    } while(choice != 5);

    return 0;
}
