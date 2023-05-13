#pragma once
#include <iostream>
#include <string>
#include "container.h"

class Object {
protected:
	static unsigned int count;
public:
	virtual std::string toString() const = 0;
	Object() {
		count++;
	}

	static int const get_count() {
		return count;
	}
	virtual ~Object() {
		count--;
	}
};

unsigned int Object::count = 0;

class Task : public virtual Object {
protected:
	bool is_completed;
public:
	Task() : is_completed(false) {}

	virtual void complete() = 0;

	bool const completed() {
		return is_completed;
	}
};

class Named : public virtual Object {
protected:
	std::string name;
public:
	Named(std::string const &Name): name(Name) {}
};

class Binary : public Task, public Named {
protected:
	double arg1;
	double arg2;
	double result;
public:
	Binary(std::string n, double a1, double a2, double res = 0) :
		Named(n), arg1(a1), arg2(a2), Task(), result(res) {}

	virtual void complete() {
		if (name == "+") {
			result = arg1 + arg2;
		}
		else if (name == "-") {
			result = arg1 - arg2;
		}
		else if (name == "*") {
			result = arg1 * arg2;
		}
		else if (name == "/") {
			result = arg1 / arg2;
		}
		else {
			throw std::invalid_argument("Invalid operand");
		}
		is_completed = true;
	}

	virtual std::string toString() const override{
		std::string info = "Binary operation " + name;
		if (is_completed) {
			info += " with result ";
			info += std::to_string(result);
		}
		info += "\n";
		return info;
	}
};

class Add_Task : public Task {
protected:
	Container<Task*> &container;
	Task* task;
public:
	Add_Task(Container<Task*> &cont, Task* t) :
		container(cont), task(t), Task() {}

	virtual void complete() {
		container.push_front(task);
		is_completed = true;
	}

	virtual std::string toString() const override{
		std::string info = "Task of pushing to container is ";
		if (!is_completed) {
			info += "not ";
		}
		info += "completed\n";
		return info;
	}
};

class Count_Objects : public Task {
protected:
	Container<Task*> &container;
	int result;
public:
	Count_Objects(Container<Task*> &cont) : container(cont), Task() {}

	virtual void complete() {
		result = container.size();
		is_completed = true;
	}

	virtual std::string toString() const override {
		std::string info = "Task of counting Objects in container ";
		if (is_completed) {
			info += " with result ";
			info += std::to_string(result);
		}
		info += "\n";
		return info;
	}
};

class Count_Results : public Task {
protected:
	Container<Task*> &container;
	int result;
public:
	Count_Results(Container<Task*> &cont) : container(cont), Task() {}

	virtual void complete() {
		result = 0;
		for (auto i = container.begin(); i != container.end(); ++i) {
			if ((i.value())->completed()) {
				result++;
			}
		}
		is_completed = true;
	}

	virtual std::string toString() const override {
		std::string info = "Task of counting resulted tasks in container ";
		if (is_completed) {
			info += " with result ";
			info += std::to_string(result);
		}
		info += "\n";
		return info;
	}
};

class Clear_Task : public Task {
protected:
	Container<Task*> &container;
public:
	Clear_Task(Container<Task*> &cont) : container(cont), Task() {}

	virtual void complete() {
		container.clear();
		is_completed = true;
	}

	virtual std::string toString() const override {
		std::string info = "Task of clearing container is ";
		if (!is_completed) {
			info += "not ";
		}
		info += "completed\n";
		return info;
	}
};

class All_Objects : public Task {
protected:
	int result;
public:
	All_Objects() : Task() {}

	virtual void complete() {
		result = count;
		is_completed = true;
	}

	virtual std::string toString() const override {
		std::string info = "Task of counting all objects in program ";
		if (is_completed) {
			info += " with result ";
			info += std::to_string(result);
		}
		info += "\n";
		return info;
	}
};