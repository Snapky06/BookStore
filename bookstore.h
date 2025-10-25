#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include "book.h"
#include <list>
#include <vector>
class BookStore
{
public:
    std::vector<Book> catalogue;
    std::list<std::string> audit;

    BookStore();
    void insertBook(Book b);
    int searchBookByTitle(std::string title);
    int searchBookByIsbn(std::string Isbn);
    std::vector<int> sortIndiceByIsbn(const std::vector<Book>&);
    std::array<int,13> stringToIsbnArray(const std::string& input);
    std:: string getCurrentTimestamp();

    std::vector<std::string> logs;

   void log(const std::string& message);
};

#endif // BOOKSTORE_H
