#include <bits/stdc++.h>

using namespace std;

vector<bool> bookScanned;

struct library {
    int signup_time;
    int total_time;
    int num_books;
    int index;
    int ship_rate;
    vector<int> books;
    vector<int> booksToSend;
    int bookSum;
    bool zeroBooksToSend = false;
    double score;

    //bool operator<(const library & l2) {
    //    return (double) this->total_time / (double) this->signup_time > (double) l2.total_time / (double) l2.signup_time;
    //}

    bool operator<(const library& l2) {
        return this->score > l2.score;
    }
};

struct book {
    int score;
    int copies; // prioritize books with fewer copies (how many libraries has it)

    bool operator<(const book& b2) {
        return (double) this->score / (double) this->copies > (double) b2.score / (double) b2.copies;
    }
};


int b, num_libraries, d; // number of books, number of libraries, number of days
vector<book> books;
vector<library> Libraries;

bool CompareBooksScoreOnly(const int& b1, const int& b2) {
    return books[b1].score > books[b2].score;
}

bool CompareBooks(const int& b1, const int& b2) {
    return books[b1] < books[b2];
}

void input(const char* filename_in, const char* filename_out) {
    freopen(filename_in, "r", stdin);
    freopen(filename_out, "w", stdout);
    cin >> b >> num_libraries >> d;
    bookScanned = vector<bool>(b, false);
    books = vector<book>(b);
    for (int i = 0; i < b; ++i) {
        cin >> books[i].score;
    }
    Libraries = vector<library>(num_libraries);
    for (int i = 0; i < num_libraries; ++i) {
        int num_books; cin >> num_books;
        Libraries[i].index = i;
        Libraries[i].books = vector<int>(num_books);
        Libraries[i].bookSum = 0;
        cin >> Libraries[i].signup_time;
        cin >> Libraries[i].ship_rate;
        int days_to_complete = ceil((double) num_books / (double) Libraries[i].ship_rate);
        Libraries[i].total_time = days_to_complete + Libraries[i].signup_time;
        for (int j = 0; j < num_books; ++j) {
            int index;
            cin >> index;
            Libraries[i].books[j] = index;
            Libraries[i].bookSum += books[j].score;
            books[index].copies++;
        }
    }


    // "score function"
    for (auto& lib : Libraries) {
        // penalty for book copies
        int total_copies = 0;
        for (auto b : lib.books) {
            total_copies += books[b].copies;
        }
        lib.bookSum /= total_copies;
        // calculate a score for the library
        // return (double) this->total_time / (double) this->signup_time > (double) l2.total_time / (double) l2.signup_time;
        // lib.score = (double) lib.bookSum / ((double) lib.total_time + 20000 * (double) lib.signup_time / d);
        lib.score = (double) lib.bookSum / ((double) lib.total_time + 20000 * (double) lib.signup_time / d);
    }
}

void output() {
    // go through libraries
    sort(Libraries.begin(), Libraries.end());
    for (auto& lib : Libraries) {
        sort(lib.books.begin(), lib.books.end(), CompareBooks);
        for (auto book : lib.books) {
            if (bookScanned[book]) continue;
            bookScanned[book] = true;
            lib.booksToSend.push_back(book);
        }
        if (lib.booksToSend.size() == 0) {
            lib.zeroBooksToSend = true;
        }
    }

    vector<pair<int, int>> nonEmptyLibraries; // list of index of non empty libraries
    for (int i = 0; i < Libraries.size(); ++i) {
        if (Libraries[i].zeroBooksToSend) {
            continue;
        }
        nonEmptyLibraries.push_back({Libraries[i].index, i});
    }

    // cout
    cout << nonEmptyLibraries.size() << endl;
    for (int j = 0; j < nonEmptyLibraries.size(); ++j) {
        // library index
        cout << nonEmptyLibraries[j].first << " ";
        auto& lib = Libraries[nonEmptyLibraries[j].second];
        // number of books to send
        cout << lib.booksToSend.size() << endl;
        if (lib.booksToSend.size() == 0) {
            cout << "break";
        }
        sort(lib.booksToSend.begin(), lib.booksToSend.end(), CompareBooksScoreOnly);
        for (auto book : lib.booksToSend) {
            cout << book << " ";
        }
        cout << endl;
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