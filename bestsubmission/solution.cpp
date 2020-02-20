#include <bits/stdc++.h>

using namespace std;


struct library {
    int signup_time;
    int total_time;
    int num_books;
    int index;
    vector<int> books;

    bool operator<(const library & l2) {
        if (this->signup_time == l2.signup_time) {
            return this->total_time > l2.total_time;
        }
        return this->signup_time < l2.signup_time;
    }
};

struct book {
    int score;
    int copies; // prioritize books with fewer copies (how many libraries has it)

    bool operator<(const book& b2) {
        return (double) this->score / (double) this->copies > (double) b2.score / (double) b2.copies;
    }
};


int b, num_libraries, d; 
vector<book> books;
vector<library> Libraries;


bool CompareBooks(const int& b1, const int& b2) {
    return books[b1] < books[b2];
}

void input() {
    freopen("f_libraries_of_the_world.txt", "r", stdin);
    freopen("SUBMISSIONf.txt", "w", stdout);
    cin >> b >> num_libraries >> d;
    books = vector<book>(b);
    for (int i = 0; i < b; ++i) {
        cin >> books[i].score;
    }
    Libraries = vector<library>(num_libraries);
    for (int i = 0; i < num_libraries; ++i) {
        int num_books; cin >> num_books;
        Libraries[i].index = i;
        Libraries[i].books = vector<int>(num_books);

        int signup; cin >> signup;
        int ship_rate; cin >> ship_rate;
        int days_to_complete = ceil((double) num_books / (double) ship_rate);
        for (int j = 0; j < num_books; ++j) {
            int index;
            cin >> index;
            Libraries[i].books[j] = index;
            books[index].copies++;
        }
    }
}



int main() {

    input();

    // output
    cout << num_libraries << endl;
    sort(Libraries.begin(), Libraries.end());
    for (int i = 0; i < num_libraries; ++i) {
        // library index
        cout << Libraries[i].index << " ";
        // number of books to send
        cout << Libraries[i].books.size() << endl;
        // Compare book indexes based on vector<book> books
        sort(Libraries[i].books.begin(), Libraries[i].books.end(), CompareBooks);
        for (auto book : Libraries[i].books) {
            cout << book << " ";
        }
        cout << endl;
    }
}