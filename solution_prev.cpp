#include <bits/stdc++.h>

using namespace std;

vector<bool> bookScanned;

struct library {
    int signup_time;
    int total_time;
    int num_books;
    int index;
    vector<int> books;

    bool operator<(const library & l2) {
        return (double) this->total_time / (double) this->signup_time > (double) l2.total_time / (double) l2.signup_time;
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

void input(const char* filename_in, const char* filename_out) {

    freopen(filename_in, "r", stdin);
    freopen(filename_out, "w", stdout);
    cin >> b >> num_libraries >> d;
    bookScanned = vector<bool>(b);
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

void output() {
    cout << num_libraries << endl;
    sort(Libraries.begin(), Libraries.end());
    for (int i = 0; i < num_libraries; ++i) {
        // library index
        cout << Libraries[i].index << " ";

        // number of books to send
        vector<int> booksToSend;
        sort(Libraries[i].books.begin(), Libraries[i].books.end(), CompareBooks);
        for (auto book : Libraries[i].books) {
            if (bookScanned[book]) continue;
            bookScanned[book] = true;
            booksToSend.push_back(book);
        }

        cout << ((booksToSend.size() == 0) ? 1 : booksToSend.size()) << endl;
        // Compare book indexes based on vector<book> books
        for (int b : booksToSend) {
            cout << b << " ";
        }
        if (booksToSend.size() != 0) { 
            cout << endl; 
        } else {
            // cout the first book if all books in the library have been scanned already
            cout << Libraries[i].books[0] << endl;
        }
    }
}

int main() {
    vector<string> inputs = { "a_example.txt", "b_read_on.txt", "c_incunabula.txt",
                              "d_tough_choices.txt", "e_so_many_books.txt", "f_libraries_of_the_world.txt" };
    vector<string> outputs = { "SUBMISSIONa.txt", "SUBMISSIONb.txt", "SUBMISSIONc.txt",
                               "SUBMISSIONd.txt", "SUBMISSIONe.txt", "SUBMISSIONf.txt" };
    for (int i = 0; i < 6; ++i) {
        input(inputs[i].c_str(), outputs[i].c_str());
        output();
    }

}