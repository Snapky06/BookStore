#include "bookstore.h"
#include "book.h"
#include <algorithm>
#include <iostream>
#include <array>
#include <cctype>
#include <ctime>

using namespace std;
using std::cout;
using std::endl;

BookStore::BookStore() {}

void BookStore::log(const std::string& message) {
    std::time_t t = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    logs.push_back(std::string("[") + buf + "] " + message);
}

void BookStore::insertBook(Book book) {
    catalogue.push_back(book);
    log("Insert: " + book.title);
    std::sort(catalogue.begin(), catalogue.end(),
              [](const Book& a, const Book& b) {
                  return a.isbn < b.isbn;
              });
    log("Sort: catalogue by ISBN");
}

int BookStore::searchBookByTitle(std::string title) {
    int low = 0;
    int high = static_cast<int>(catalogue.size()) - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        const std::string& key = catalogue[mid].title;

        if (key == title) {
            log("SearchTitle: found '" + title + "' at " + std::to_string(mid));
            return mid;
        } else if (key < title) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    log("SearchTitle: not found '" + title + "'");
    return -1;
}

std::vector<int> BookStore::sortIndiceByIsbn(const std::vector<Book>&) {
    std::vector<int> indices(catalogue.size());
    for (int i = 0; i < static_cast<int>(catalogue.size()); ++i) {
        indices[i] = i;
    }
    std::sort(indices.begin(), indices.end(),
              [&](int a, int b) {
                  return catalogue[a].isbn < catalogue[b].isbn;
              });
    return indices;
}

std::array<int, 13> BookStore::stringToIsbnArray(const std::string& input) {
    std::array<int, 13> result{};
    if (input.size() != 13) {
        cout << "Error: ISBN must have exactly 13 digits." << endl;
        result.fill(-1);
        return result;
    }
    for (size_t i = 0; i < 13; ++i) {
        if (!std::isdigit(static_cast<unsigned char>(input[i]))) {
            cout << "Error: ISBN must contain only digits." << endl;
            result.fill(-1);
            return result;
        }
        result[i] = input[i] - '0';
    }
    return result;
}

int BookStore::searchBookByIsbn(std::string isbn) {
    std::array<int, 13> target = stringToIsbnArray(isbn);
    if (target[0] == -1) {
        log("SearchISBN: invalid input '" + isbn + "'");
        return -1;
    }

    int low = 0;
    int high = static_cast<int>(catalogue.size()) - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        const auto& key = catalogue[mid].isbn;

        if (key == target) {
            log("SearchISBN: found '" + isbn + "' at " + std::to_string(mid));
            return mid;
        } else if (key < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    log("SearchISBN: not found '" + isbn + "'");
    return -1;
}
