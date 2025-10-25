#include <limits>
#include <iostream>
#include <string>
#include "book.h"
#include "bookstore.h"

    using namespace std;

int main() {
    BookStore* store = new BookStore();

    while (true) {
        cout << "\nMenu\n";
        cout << "1. Insert book\n";
        cout << "2. Search by title\n";
        cout << "3. Search by ISBN\n";
        cout << "4. Show catalogue\n";
        cout << "5. Show change log\n";
        cout << "0. Exit\n";
        cout << "Option: ";

        int option;
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
            continue;
        }

        if (option == 0) {
            cout << "Goodbye.\n";
            break;
        } else if (option == 1) {
            Book book;
            cout << "Title (no spaces): ";
            cin >> book.title;
            cout << "ISBN (13 digits): ";
            string isbnStr;
            cin >> isbnStr;
            auto arr = store->stringToIsbnArray(isbnStr);
            if (arr[0] == -1) {
                cout << "Invalid ISBN.\n";
                store->log(string("InsertFailed: invalid ISBN for '") + book.title + "'");
            } else {
                book.isbn = arr;
                store->insertBook(book);
                cout << "Inserted.\n";
            }
        } else if (option == 2) {
            cout << "Title (no spaces): ";
            string title;
            cin >> title;
            int idx = store->searchBookByTitle(title);
            if (idx == -1) {
                cout << "Not found.\n";
            } else {
                cout << "Index: " << idx << "\n";
                cout << "Title: " << store->catalogue[idx].title << "\n";
                cout << "ISBN: ";
                for (int d : store->catalogue[idx].isbn) cout << d;
                cout << "\n";
            }
        } else if (option == 3) {
            cout << "ISBN (13 digits): ";
            string isbnStr;
            cin >> isbnStr;
            int idx = store->searchBookByIsbn(isbnStr);
            if (idx == -1) {
                cout << "Not found or invalid.\n";
            } else {
                cout << "Index: " << idx << "\n";
                cout << "Title: " << store->catalogue[idx].title << "\n";
                cout << "ISBN: ";
                for (int d : store->catalogue[idx].isbn) cout << d;
                cout << "\n";
            }
        } else if (option == 4) {
            if (store->catalogue.empty()) {
                cout << "Catalogue is empty.\n";
            } else {
                for (size_t i = 0; i < store->catalogue.size(); ++i) {
                    cout << "[" << i << "] " << store->catalogue[i].title << " | ISBN: ";
                    for (int d : store->catalogue[i].isbn) cout << d;
                    cout << "\n";
                }
            }
        } else if (option == 5) {
            if (store->logs.empty()) {
                cout << "Log is empty.\n";
            } else {
                cout << "Change log:\n";
                for (size_t i = 0; i < store->logs.size(); ++i) {
                    cout << "[" << i << "] " << store->logs[i] << "\n";
                }
            }
        } else {
            cout << "Unknown option.\n";
        }
    }

    store->catalogue.clear();
    store->catalogue.shrink_to_fit();
    store->logs.clear();
    store->logs.shrink_to_fit();

    delete store;

    return 0;
}
