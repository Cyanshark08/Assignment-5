// ListApp.cpp
// Implementation for the Doubly Linked List application (std::list<student>)

#include "ListApp.h"
#include <cstdlib>  // system()

using std::getline;

static void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\x1B[2J\x1B[H";
#endif
}

static void hr() { cout << string(80, '-') << '\n'; }

/* ---------- parsing ---------- */
bool ListApp::parseStudentLine(const string& line, student& s) {
    if (line.empty()) return false;
    string t = line; for (char& c : t) if (c == ',') c = ' ';
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

/* ---------- safe numeric input ---------- */
size_t ListApp::askSizeT_1_100() {
    while (true) {
        cout << "\nEnter the new size(1..100): ";
        size_t n;
        if (cin >> n) {
            if (n < 1) { cout << "  Please enter at least 1.\n"; continue; }
            if (n > 100) { cout << "  Max allowed is 100. Using 100.\n"; return 100; }
            return n;
        }
        cout << "  Invalid number. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/* ---------- placeholder for growth ---------- */
student ListApp::placeholderStudent() {
    student s;
    s.setName("N/A");
    s.setGradeLevel("N/A");
    s.setGPA(0.00);
    return s;
}

/* ---------- private UI ---------- */
void ListApp::showMenu() const {
    // Show the one-line status message above the menu (like your screenshot)
    if (!statusMsg.empty()) {
        cout << "    " << statusMsg << "\n\n";
    }

    cout << "\t2> List container\n";
    cout << "\t" << string(80, char(196)) << "\n";
    cout << "\t A> clear() - Destroys all elements from the list\n";
    cout << "\t B> resize(n) - Changes the list so that it contains n elements\n";
    cout << "\t C> Read input.dat and push_front(e) - Adds a new element at the front of the list\n";
    cout << "\t D> pop_front() - Deletes the first element\n";
    cout << "\t E> front() - Accesses the first element\n";
    cout << "\t F> Read input.dat and push_back(e) - Adds a new element at the end of the list\n";
    cout << "\t G> pop_back() - Delete the last element\n";
    cout << "\t H> back() - Accesses the last element\n";
    cout << "\t I> begin() - Returns an iterator refereing to the first element in the list\n";
    cout << "\t J> end() - Returns an iterator referring to the past-the-end element in the list\n";
    cout << "\t K> Using iterator begin() and end() returns all elements in the list\n";
    cout << "\t L> rbegin() - Returns a reverse iterator pointing to the last element in the list\n";
    cout << "\t M> rend() - Returns a reverse iterator pointing to the element preceding the first element in the list\n";
    cout << "\t N> Using iterator rbegin() and rend() returns all elements in the list\n";
    cout << "\t O> erase(it) - Removes from the vector a single element(using an iterator)\n";
    cout << "\t P> erase(start_it,end_it) - Removes from the vector a range of elements( using iterators)\n";
    cout << "\t Q> insert(it, entry) - Insert a new entry at the iterator.\n";
    cout << "\t R> swap() - Exchanges the content of the container by another list's content of the same type\n";
    cout << "\t S> Sort - Sorts the list.\n";
    cout << "\t" << string(80, char(196)) << "\n";
    cout << "\t 0> return\n";
    cout << "\t" << string(80, char(196)) << "\n\n";
    cout << "Option: ";
}

void ListApp::print(const string& title) const {
    cout << "\n" << title << " (" << L.size() << "):\n"; hr();
    size_t i = 0; for (const auto& s : L) cout << setw(3) << i++ << " | " << s << '\n';
    hr();
}

/* ---------- helpers ---------- */
list<student>::iterator ListApp::iterAt(size_t pos) {
    if (pos > L.size()) return L.end();
    auto it = L.begin(); advance(it, static_cast<long>(pos));
    return it;
}

student ListApp::promptStudent() {
    string name, grade; double gpa{};
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << " Enter name: ";  getline(cin, name);
    cout << " Enter grade: "; getline(cin, grade);
    cout << " Enter GPA: ";   cin >> gpa;
    student s; s.setName(name); s.setGradeLevel(grade); s.setGPA(gpa);
    return s;
}

/* ---------- load from file ---------- */
bool ListApp::loadFromFileFront() {
    ifstream fin(filePath);
    if (!fin) { cout << "Cannot open file: " << filePath << '\n'; return false; }
    string line; student st; vector<student> buf;
    while (getline(fin, line)) if (parseStudentLine(line, st)) buf.push_back(st);
    for (auto it = buf.rbegin(); it != buf.rend(); ++it) L.push_front(*it);
    cout << "Pushed " << buf.size() << " to FRONT from " << filePath << ".\n";
    return true;
}

bool ListApp::loadFromFileBack() {
    ifstream fin(filePath);
    if (!fin) { cout << "Cannot open file: " << filePath << '\n'; return false; }
    string line; student st; size_t n = 0;
    while (getline(fin, line)) if (parseStudentLine(line, st)) { L.push_back(st); ++n; }
    cout << "Pushed " << n << " to BACK from " << filePath << ".\n";
    return true;
}

/* ---------- public run loop ---------- */
void ListApp::run() {
    char c;
    do {
        clearScreen();             // clear before showing the list menu
        showMenu();                // this also prints any status message
        cin >> c;
        c = static_cast<char>(toupper(static_cast<unsigned char>(c)));

        switch (c) {
        case 'A':
            L.clear();
            statusMsg = "The list has been cleared.";
            break;

        case 'B': {
            const size_t n = askSizeT_1_100();

            try {
                const size_t cur = L.size();
                if (n > cur) {
                    const size_t add = n - cur;
                    student ph = placeholderStudent();
                    for (size_t i = 0; i < add; ++i) L.push_back(ph);
                }
                else if (n < cur) {
                    auto it = L.begin();
                    advance(it, static_cast<long>(n));
                    L.erase(it, L.end());
                }
            }
            catch (const std::bad_alloc&) {
                statusMsg = "Not enough memory to resize.";
                continue; // redraw menu with status
            }

            // <<< EXACT status line like your screenshot
            statusMsg = "The list has been resized to " + to_string(n) + " elements.";
            continue; // immediately redraw the menu with the status line
        }

        case 'C':
			loadFromFileFront(); statusMsg.clear(); system("pause"); break;

        case 'D':
            if (L.empty()) { statusMsg = "List is empty."; system("pause"); break; }
            L.pop_front(); statusMsg = "Deleted first element."; system("pause"); break;

        case 'E':
            statusMsg.clear();
            if (L.empty()) cout << "Empty.\n"; else cout << "Front: " << L.front() << '\n'; system("pause");
            break;

        case 'F':
            loadFromFileBack(); statusMsg.clear(); system("pause"); break;

        case 'G':
            if (L.empty()) { statusMsg = "List is empty."; system("pause"); break; }
            L.pop_back(); statusMsg = "Deleted last element."; system("pause"); break;

        case 'H':
            statusMsg.clear();
            if (L.empty()) cout << "Empty.\n"; else cout << "Back: " << L.back() << '\n'; system("pause");
            break;

        case 'I':
            statusMsg.clear();
            if (L.empty()) cout << "Empty.\n";
            else { cout << "Traversal [begin..end)\n"; hr(); for (auto it = L.begin(); it != L.end(); ++it) cout << *it << '\n'; hr(); }
            system("pause");
            break;

        case 'J':
            statusMsg.clear();
            cout << "end() = past-the-end sentinel; used for comparisons only.\n";
            system("pause");
            break;

        case 'K':
            statusMsg.clear(); print("Using begin()/end()"); system("pause"); break;

        case 'L':
            statusMsg.clear();
            if (L.empty()) cout << "Empty.\n";
            else { cout << "Traversal [rbegin..rend)\n"; hr(); for (auto it = L.rbegin(); it != L.rend(); ++it) cout << *it << '\n'; hr(); }
            system("pause");
            break;

        case 'M':
            statusMsg.clear();
            cout << "rend() = before-the-first reverse sentinel.\n";
            system("pause");
            break;

        case 'N':
            statusMsg.clear();
            if (L.empty()) cout << "Empty.\n";
            else { cout << "Using rbegin()/rend()\n"; hr(); for (auto it = L.rbegin(); it != L.rend(); ++it) cout << *it << '\n'; hr(); }
            system("pause");
            break;

        case 'O': {
            if (L.empty()) { statusMsg = "List is empty."; break; }
            print(); size_t pos; cout << "Erase index: "; cin >> pos;
            if (!cin || pos >= L.size()) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                statusMsg = "Invalid index.";
                system("pause");
                break;
            }
            auto it = iterAt(pos);
            L.erase(it);
            statusMsg = "Erased element at index " + to_string(pos) + ".";
            system("pause");
            break;
        }

        case 'P': {
            if (L.empty()) { statusMsg = "List is empty."; break; }
            print(); size_t a, b; cout << "Erase [a,b) (b may equal size). Enter a b: "; cin >> a >> b;
            if (!cin || a > b || a > L.size() || b > L.size()) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                statusMsg = "Invalid range.";
                system("pause");
                break;
            }
            auto ita = iterAt(a), itb = iterAt(b);
            L.erase(ita, itb);
            statusMsg = "Erased range [" + to_string(a) + "," + to_string(b) + ").";
            system("pause");
            break;
        }

        case 'Q': {
            print(); size_t pos; cout << "Insert at index (0..size): "; cin >> pos;
            if (!cin || pos > L.size()) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                statusMsg = "Invalid index.";
                system("pause");
                break;
            }
            auto it = (pos == L.size()) ? L.end() : iterAt(pos);
            student s = promptStudent(); L.insert(it, s);
            statusMsg = "Inserted new element at index " + to_string(pos) + ".";
            system("pause");
            break;
        }

        case 'R': {
            list<student> other;
            ifstream fin(filePath); string line; student st;
            while (getline(fin, line)) if (parseStudentLine(line, st)) other.push_back(st);
            L.swap(other);
            statusMsg = "Swapped with file list (size=" + to_string(other.size()) + ").";
            system("pause");
            break;
        }

        case 'S':
            L.sort(); statusMsg = "List sorted by name."; system("pause"); break;

        case '0':
            statusMsg.clear();
            break;

        default:
            statusMsg = "Invalid choice.";
            break;
        }
    } while (c != '0');
}
