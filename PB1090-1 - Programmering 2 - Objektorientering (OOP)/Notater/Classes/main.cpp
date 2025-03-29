import std;

class Box {
public:
	Box() {
		m_objCount++;
		std::println("Box() called. Current amount of boxes: {}", m_objCount);
	}
	Box(float length, float width, float height)
		:
		m_length(length),
		m_width(width),
		m_height(height)
	{
		m_objCount++;
		std::println("Box(float, float, float) called. Current amount of boxes: {}", m_objCount);
	}
	explicit Box(float side_length) 
		:
		Box(side_length, side_length, side_length)
	{
		std::println("Box(float) called.");
	}

	// Copy constructor
	Box(const Box& other)
		:
		Box(other.Length(), other.Width(), other.Height())
	{
		std::println("Box(Box) called.");
	}

	// Destructor
	~Box() {
		m_objCount--;
		std::println("~Box() called. Current amount of boxes: {}", m_objCount);
	}

	// Operators
	// Dette gir også <, >, <= og >=
	// Hadde det vært strong-ordering, ville vi også fått == og !=
	std::partial_ordering operator<=>(const Box& rhs) const {
		return Volume() <=> rhs.Volume();
	}

	std::partial_ordering operator<=>(float n) const {
		return Volume() <=> n;
	}

	// Dette gir også !=
	bool operator==(const Box& rhs) const {
		return 
			Length() == rhs.Length() &&
			Width() == rhs.Width() &&
			Height() == rhs.Height();
	}

	bool operator==(float n) const {
		return Volume() == n;
	}

	Box operator+(const Box& rhs) const {
		return {
			Length() + rhs.Length(),
			std::max(Width(), rhs.Width()),
			std::max(Height(), rhs.Height())
		};
	}

	// Getters
	float Length() const {
		return m_length;
	}
	float Width() const {
		return m_width;
	}
	float Height() const {
		return m_height;
	}

	// Setters
	void SetLength(float newLength) {
		m_length = newLength;
	}
	void SetWidth(float newWidth) {
		m_width = newWidth;
	}
	void SetHeight(float newHeight) {
		m_height = newHeight;
	}

public:
	float Volume() const {
		return Length() * Width() * Height();
	}

	void PrintSides(bool newline = false) const {
		std::print("{{ l: {:.2f}, w: {:.2f}, h: {:.2f} }}", Length(), Width(), Height());
		if (newline) std::println("");
	}

	size_t HowMany() {
		return m_objCount;
	}
private:
	static inline size_t m_objCount = 0;
	float m_length;
	float m_width;
	float m_height;
};



class Person {
public:
	Person() {
		std::println("Person() called.");
	}
	Person(const std::string& name, unsigned int age) 
		:
		m_name(name),
		m_age(age)
	{
		std::println("Person(string, uint) called.");
	}

	const std::string& GetName() const {
		return m_name;
	}
	unsigned int GetAge() const {
		return m_age;
	}

	void SetName(const std::string& newName) {
		m_name = newName;
	}
	void SetAge(unsigned int newAge) {
		m_age = newAge;
	}
private:
	std::string m_name;
	unsigned int m_age;
};

class Student : public Person {
public:
	Student() {
		std::println("Student() called.");
	}
	Student(const std::string& name, unsigned int age, unsigned int semester, const std::string& course)
		:
		Person(name, age),
		m_semester(semester),
		m_course(course)
	{
		std::println("Student(string, uint, uint, string) called.");
	}

	unsigned int GetSemester() const {
		return m_semester;
	}

	const std::string& GetCourse() const {
		return m_course;
	}

	void SetSemester(unsigned int newSemester) {
		m_semester = newSemester;
	}
	void SetCourse(const std::string& newCourse) {
		m_course = newCourse;
	}
private:
	unsigned int m_semester;
	std::string m_course;
};

class Proffesor : public Person {
public:
	Proffesor() {
		std::println("Proffesor() called.");
	}
	Proffesor(const std::string& name, unsigned int age, float salary, const std::vector<std::string> courses)
		:
		Person(name, age),
		m_salary(salary),
		m_courses(courses)
		
	{
		std::println("Proffesor(string, uint, float, vector<string>) called.");
	}

	float GetSalary() const {
		return m_salary;
	}
	const std::vector<std::string>& GetCourses() const {
		return m_courses;
	}

	void SetSalary(float newSalary) {
		m_salary = newSalary;
	}
	void AddCourse(const std::string& course) {
		m_courses.push_back(course);
	}
private:
	float m_salary;
	std::vector<std::string> m_courses;
};



class Shape {
public:
	Shape() = default;

	virtual float Perimeter() const = 0;
	virtual float Area() const = 0;
};

class Rectangle : public Shape {
public:
	Rectangle(float length, float height)
		:
		length(length),
		height(height)
	{}

	float Perimeter() const override {
		return 2.0f * (length + height);
	}
	float Area() const override {
		return length * height;
	}
private:
	float length;
	float height;
};

class Circle : public Shape {
public:
	Circle(float radius)
		:
		radius(radius)
	{}

	float Perimeter() const override {
		return 2.0f * pi * radius;
	}
	float Area() const override {
		return pi * radius * radius;
	}
private:
	static constexpr float pi = 3.14f;

	float radius;
};



class Counter {
public:
	Counter() {
		n_counters++;
	}
	Counter(const Counter& other) {
		n_counters++;
	}
	~Counter() {
		n_counters--;
	}

	static unsigned int HowMany() {
		return n_counters;
	}
private:
	static inline unsigned int n_counters = 0;
};

template<typename T>
class _Vec2 {
public:
	T x;
	T y;

	_Vec2 operator+(const _Vec2<T>& rhs) const {
		return { x + rhs.x, y + rhs.y };
	}
	_Vec2 operator*(T scalar) const {
		return { x * scalar, y * scalar };
	}

	_Vec2 operator-(const _Vec2<T>& rhs) const {
		return *this + (rhs * -(T)1);
	}
};

typedef _Vec2<int> Vei2;
typedef _Vec2<float> Vec2;

class Projectile {
public:
	Projectile()
	{
		objCount++;
	}

	virtual ~Projectile() {
		objCount--;
	}

	virtual bool Update() = 0;

	static size_t ObjectCount() {
		return objCount;
	}
private:
	bool state = true;

	static inline size_t objCount = 0;
};


class Bullet : public Projectile {
public:
	Bullet(int lifetime)
		:
		lifetime(lifetime)
	{
		id = id_ctr;
		id_ctr++;
		std::println("Added Bullet - id: {}, lifetime: {}", id, lifetime);
	}
	~Bullet() {
		std::println("Bullet {}: Pew! Bullet destroyed.", id);
	}

	bool Update() override {
		if (lifetime <= 0) return false;
		lifetime--;

		std::println("Bullet {}: Lifetime left:{}", id, lifetime);

		return true;
	}
private:
	int lifetime;
	
	static inline int id_ctr = 0;
	int id;
};

class Rocket : public Projectile {
public:
	Rocket(int lifetime)
		:
		lifetime(lifetime) {
		id = id_ctr;
		id_ctr++;
		std::println("Added Rocket - id: {}, lifetime: {}", id, lifetime);
	}
	~Rocket() {
		std::println("Rocket {}: Boom! Rocket destroyed.", id);
	}

	bool Update() override {
		if (lifetime <= 0) return false;
		lifetime--;

		std::println("Rocket {}: Lifetime left:{}", id, lifetime);

		return true;
	}
private:
	int lifetime;

	static inline int id_ctr = 0;
	int id;
};

class ProjectileManager {
public:
	void Add(Projectile* pProj) {
		projectiles.push_back(pProj);
	}
	void Update() {
		for (Projectile* &pProj : projectiles) {
			if (!pProj->Update()) {

				delete pProj;
				pProj = nullptr;
			}
		}
		projectiles.remove(nullptr);
	}
private:
	std::list<Projectile*> projectiles;
};

std::vector<std::string> SplitString(const std::string& str, const std::string& delims) {
	if (str.empty()) return {};

	std::vector<std::string> strings;

	std::size_t begin = 0;
	std::size_t end = 0;

	while (begin != std::string::npos) {
		begin = str.find_first_not_of(delims, end);
		end = str.find_first_of(delims, begin);

		if (begin == std::string::npos) break;

		strings.push_back(str.substr(begin, end - begin));

		begin = end;
	}
	
	return strings;
}


int main() {
	ProjectileManager pm;

	while (true) {
		std::print("> ");
		std::string input;
		std::getline(std::cin, input);

		std::vector<std::string> args = std::move(SplitString(input, " "));

		if (args.empty() || args[0] == "u" || args[0] == "update") {
			if (Projectile::ObjectCount() != 0) {
				pm.Update();
			}
			else {
				std::println("No projectiles active.");
			}
		}
		else if (args[0] == "a" || args[0] == "add") {
			std::string type;
			if (args.size() != 3) {
				std::println("\"Add\" doesn't take {} argument.", args.size());
				continue;
			}

			int lifetime = -1;
			try {
				lifetime = std::stoi(args[2]);
			}
			catch (std::invalid_argument e) {
				std::println("\"{}\": {}", args[2], e.what());
				continue;
			}
				

			Projectile* pProj = nullptr;
			if (args[1] == "b" || args[1] == "bullet") {
				pProj = new Bullet(lifetime);
			}
			else if (args[1] == "r" || args[1] == "rocket") {
				pProj = new Rocket(lifetime);
			}
			else {
				std::println("\"{}\": Invalid projectile type.", type);
				continue;
			}

			pm.Add(pProj);
		}
		else {
			std::println("\"{}\": Unrecognized command.", input);
		}
	}

	return 0;
}