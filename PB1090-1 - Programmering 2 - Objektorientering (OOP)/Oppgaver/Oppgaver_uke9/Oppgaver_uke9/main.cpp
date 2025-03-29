import std;

class Book {
public:
	Book(std::string_view title, std::string_view author, unsigned int pages) 
		:
		m_title(title),
		m_author(author),
		m_nPages(pages)
	{}

	std::string Title() const { return m_title; }
	std::string Author() const { return m_author; }
	unsigned int Pages() const { return m_nPages; }

	void Print() const {
		std::println("\"{}\" - {}, {} Pages", Title(), Author(), Pages());
	}
private:
	std::string m_title;
	std::string m_author;
	unsigned int m_nPages;
};

class Author {
public:
	Author(std::string_view name, std::string_view mail, std::vector<Book*> books = {}) 
		:
		m_name(name),
		m_mailAddr(mail),
		m_books(books)
	{}

	std::string Name() const { return m_name; }
	std::string MailAddress() const { return m_mailAddr; }
	std::vector<Book*> Books() const { return m_books; }

	void AddBook(Book* pBook) {
		m_books.push_back(pBook);
	}

	void Print() const {
		std::println("{} (Email: {}):", Name(), MailAddress());
		for (auto pb : Books()) {
			pb->Print();
		}
	}

private:
	std::string m_name;
	std::string m_mailAddr;
	std::vector<Book*> m_books;
};

int main() {
	Book b1("title", "J. Mama", 69);
	Book b2("title, part 2", "J. Mama", 420);

	std::println("\"{}\" - {}, {} Pages", b1.Title(), b1.Author(), b1.Pages());
	std::println("\"{}\" - {}, {} Pages", b2.Title(), b2.Author(), b2.Pages());

	Author a1("J. Mama", "joemama@yahoo.com", {&b1, &b2});

	Book b3("title, the finale", "J. Mama", 1234);

	a1.AddBook(&b3);

	a1.Print();
	
	return 0;
}