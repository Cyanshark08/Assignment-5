// DoublyListApp.cpp
// Implementation for the Doubly Linked List application (std::list<student>)

#include "DoublyListApp.h"
#include <cstdlib>  // system()
#include "Input.h"

using std::getline;

static void hr() { cout << "\t\t" << string(80, '-') << '\n'; }

/* ---------- parsing ---------- */
bool DoublyListApp::parseStudentLine(const string &line, Student &s) {
    if (line.empty()) return false;
    string t = line; for (char &c : t) if (c == ',') c = ' ';
    istringstream iss(t); vector<string> a; string w;
    while (iss >> w) a.push_back(w);
    if (a.size() < 3) return false;
    double gpa{}; try { gpa = stod(a.back()); }
    catch (...) { return false; }
    string grade = a[a.size() - 2], name;
    for (size_t i = 0; i + 2 < a.size(); ++i) { if (i) name += ' '; name += a[i]; }
    s.setName(name); s.setGradeLevel(grade); s.setGPA(gpa);
    return true;
}

/* ---------- placeholder for growth ---------- */
Student DoublyListApp::placeholderStudent() {
    Student s;
    s.setName("N/A");
    s.setGradeLevel("N/A");
    s.setGPA(0.00);
    return s;
}

/* ---------- private UI ---------- */
void DoublyListApp::showMenu() const {

    cout << "\t4> Doubly Linked List container\n";
    cout << "\t" << string(80, char(205)) << "\n";
    cout << "\t\tA> clear() - Destroys all elements from the list\n";
    cout << "\t\tB> resize(n) - Changes the list so that it contains n elements\n";
    cout << "\t\tC> Read input.dat and push_front(e) - Adds a new element at the front of the list\n";
    cout << "\t\tD> pop_front() - Deletes the first element\n";
    cout << "\t\tE> front() - Accesses the first element\n";
    cout << "\t\tF> Read input.dat and push_back(e) - Adds a new element at the end of the list\n";
    cout << "\t\tG> pop_back() - Delete the last element\n";
    cout << "\t\tH> back() - Accesses the last element\n";
    cout << "\t\tI> begin() - Returns an iterator refereing to the first element in the list\n";
    cout << "\t\tJ> end() - Returns an iterator referring to the past-the-end element in the list\n";
    cout << "\t\tK> Using iterator begin() and end() returns all elements in the list\n";
    cout << "\t\tL> rbegin() - Returns a reverse iterator pointing to the last element in the list\n";
    cout << "\t\tM> rend() - Returns a reverse iterator pointing to the element preceding the first element in the list\n";
    cout << "\t\tN> Using iterator rbegin() and rend() returns all elements in the list\n";
    cout << "\t\tO> erase(it) - Removes from the vector a single element(using an iterator)\n";
    cout << "\t\tP> erase(start_it,end_it) - Removes from the vector a range of elements( using iterators)\n";
    cout << "\t\tQ> insert(it, entry) - Insert a new entry at the iterator.\n";
    cout << "\t\tR> swap() - Exchanges the content of the container by another list's content of the same type\n";
    cout << "\t\tS> Sort - Sorts the list.\n";
    cout << "\t" << string(80, char(196)) << "\n";
    cout << "\t\t0> return\n";
    cout << "\t" << string(80, char(205));
}

void DoublyListApp::print(const string &title) const {
    cout << "\n\t\t" << title << " (" << L.size() << "):\n"; hr();
    size_t i = 0; for (const auto &s : L) cout << "\n\t\t" << i++ << " | " << s << '\n';
    hr();
}


/* ---------- public run loop ---------- */
void DoublyListApp::Run() {
    while (m_MenuState != MenuState::Exited)
    {
        std::system("cls");
        showMenu();
        
        HandleInput(Input::inputChar("\n\t\tOption: ", "ABCDEFGHIJKLMNOPQRS0"));

        if (!statusMsg.empty()) {
            cout << "\n\t\t" << statusMsg;
        }
        std::cout << "\n";
        std::system("pause");
    }
}

void DoublyListApp::Clean()
{
    m_MenuState = MenuState::Exited;
}

void DoublyListApp::Restart()
{
    this->Clean();
}

void DoublyListApp::HandleInput(char p_Input)
{
    switch (p_Input) {
    case 'A':
        L.clear();
        statusMsg = "The list has been cleared.";
        break;

    case 'B': {
        int n = Input::inputInteger("\n\t\tEnter a new size (1...100): ", 1, 100);

        try {
            const size_t cur = L.size();
            if (n > cur) {
                const size_t add = n - cur;
                Student ph = placeholderStudent();
                for (size_t i = 0; i < add; ++i) L.push_back(ph);
            }
            else if (n < cur) {
                auto it = L.begin();
                advance(it, static_cast<long>(n));
                L.erase(it, L.end());
            }
        }
        catch (const std::bad_alloc &) {
            statusMsg = "Not enough memory to resize.";
            break; // redraw menu with status
        }

        // <<< EXACT status line like your screenshot
        statusMsg = "The list has been resized to " + to_string(n) + " elements.";
        break; // immediately redraw the menu with the status line
    }

    case 'C':
        loadFromFileFront(); statusMsg.clear(); break;

    case 'D':
        if (L.empty()) { statusMsg = "List is empty."; break; }
        L.pop_front(); statusMsg = "Deleted first element."; break;

    case 'E':
        statusMsg.clear();
        if (L.empty()) cout << "\n\t\tEmpty.\n"; else cout << "\n\t\tFront: " << L.front() << '\n';
        break;

    case 'F':
        loadFromFileBack(); statusMsg.clear(); break;

    case 'G':
        if (L.empty()) { statusMsg = "List is empty."; break; }
        L.pop_back(); statusMsg = "Deleted last element."; break;

    case 'H':
        statusMsg.clear();
        if (L.empty()) cout << "\n\t\tEmpty.\n"; else cout << "\n\t\tBack: " << L.back() << '\n'; 
        break;

    case 'I':
        statusMsg.clear();
        if (L.empty()) cout << "\n\t\tEmpty.\n";
        else { cout << "\n\t\tTraversal [begin..end)\n"; hr(); for (auto it = L.begin(); it != L.end(); ++it) cout << *it << '\n'; hr(); }
        break;

    case 'J':
        statusMsg.clear();
        cout << "\n\t\tend() = past-the-end sentinel; used for comparisons only.\n";
        break;

    case 'K':
        statusMsg.clear(); print("\n\t\tUsing begin()/end()"); break;

    case 'L':
        statusMsg.clear();
        if (L.empty()) cout << "\n\t\tEmpty.\n";
        else { cout << "\n\t\tTraversal [rbegin..rend)\n"; hr(); for (auto it = L.rbegin(); it != L.rend(); ++it) cout << *it << '\n'; hr(); }
        break;

    case 'M':
        statusMsg.clear();
        cout << "\n\t\trend() = before-the-first reverse sentinel.\n";
        break;

    case 'N':
        statusMsg.clear();
        if (L.empty()) cout << "\n\t\tEmpty.\n";
        else { cout << "\n\t\tUsing rbegin()/rend()\n"; hr(); for (auto it = L.rbegin(); it != L.rend(); ++it) cout << "\n\t\t" << *it << '\n'; hr(); }
        break;

    case 'O': {
        if (L.empty()) { statusMsg = "\n\t\tList is empty."; break; }
        print(); size_t pos; cout << "\n\t\tErase index: "; cin >> pos;
        if (!cin || pos >= L.size()) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            statusMsg = "Invalid index.";
            break;
        }
        auto it = iterAt(pos);
        L.erase(it);
        statusMsg = "Erased element at index " + to_string(pos) + ".";
        break;
    }

    case 'P': {
        if (L.empty()) { statusMsg = "List is empty."; break; }
        print(); size_t a, b; cout << "\n\t\tErase [a,b) (b may equal size). Enter a b: "; cin >> a >> b;
        if (!cin || a > b || a > L.size() || b > L.size()) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            statusMsg = "Invalid range.";
            break;
        }
        auto ita = iterAt(a), itb = iterAt(b);
        L.erase(ita, itb);
        statusMsg = "Erased range [" + to_string(a) + "," + to_string(b) + ").";
        break;
    }

    case 'Q': {
        print();
        int pos = Input::inputInteger("\n\t\tInsert at index (0..." + to_string(L.size()) + "): ", 0, (int)L.size());
        auto it = (pos == L.size()) ? L.end() : iterAt(pos);
        Student s = promptStudent(); L.insert(it, s);
        statusMsg = "Inserted new element at index " + to_string(pos) + ".";
        break;
    }

    case 'R': {
        list<Student> other;
        ifstream fin(filePath); string line; Student st;
        while (getline(fin, line)) if (parseStudentLine(line, st)) other.push_back(st);
        L.swap(other);
        statusMsg = "Swapped with file list (size=" + to_string(other.size()) + ").";
        break;
    }

    case 'S':
        L.sort(); statusMsg = "List sorted by name.";break;

    case '0':
        statusMsg.clear();
        this->Restart();
        break;

    default:
        statusMsg = "Invalid choice.";
        break;
    }
}


/* ---------- helpers ---------- */
list<Student>::iterator DoublyListApp::iterAt(size_t pos) {
    if (pos > L.size()) return L.end();
    auto it = L.begin(); advance(it, static_cast<long>(pos));
    return it;
}

Student DoublyListApp::promptStudent() {
    string name;
    int grade; 
    double gpa{};
    name = Input::inputString("\n\t\tEnter name: ", true);
    grade = Input::inputInteger("\t\tEnter their grade level (1-Freshman, 2-Sophmore, 3-Junior, or 4-Senior): ", 1, 4);
    gpa = Input::inputDouble("\t\tEnter their gpa (0.0...4.0): ", 0.0, 4.0);

    std::string levels[4] = { "Freshmen", "Sophmore", "Junior", "Senior" };

    Student s; s.setName(name); s.setGradeLevel(levels[grade - 1]); s.setGPA(gpa);
    return s;
}

/* ---------- load from file ---------- */
bool DoublyListApp::loadFromFileFront() {
    ifstream fin(filePath);
    if (!fin) { cout << "Cannot open file: " << filePath << '\n'; return false; }
    string line; Student st; vector<Student> buf;
    while (getline(fin, line)) if (parseStudentLine(line, st)) buf.push_back(st);
    for (auto it = buf.rbegin(); it != buf.rend(); ++it) L.push_front(*it);
    cout << "Pushed " << buf.size() << " to FRONT from " << filePath << ".\n";
    return true;
}

bool DoublyListApp::loadFromFileBack() {
    ifstream fin(filePath);
    if (!fin) { cout << "Cannot open file: " << filePath << '\n'; return false; }
    string line; Student st; size_t n = 0;
    while (getline(fin, line)) if (parseStudentLine(line, st)) { L.push_back(st); ++n; }
    cout << "Pushed " << n << " to BACK from " << filePath << ".\n";
    return true;
}