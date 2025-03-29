export module nutex;

import std;

export namespace nut {
	class BaseExeption {
	public:
		BaseExeption(const std::string& message = "Something went wrong.")
			:
			message(message) {
		}

		std::string what() const {
			return message;
		}
	private:
		std::string message;
	};

	class LogicError : public BaseExeption {
	public:
		LogicError(const std::string& message = "Runtime logic error.") 
			:
			BaseExeption(message)
		{}
	};

	class DivisonByZero : public LogicError {
	public:
		DivisonByZero(const std::string& message = "Division by zero.") 
			:
			LogicError(message)
		{}
	};
}