#pragma once
#include <iostream>
#include "container.h"
#include "object.h"

int main() {
	//Container<Task*>* tasks = new Container<Task*>;
	Container<Task*> tasks;


	/*test tasks*/
	Binary* sum1 = new Binary("+", 2, 3);
	Binary* mult1 = new Binary("*", 2, 5);
	Count_Objects* obj_count = new Count_Objects(tasks);
	Count_Results* res_count = new Count_Results(tasks);
	Binary* div1 = new Binary("/", 6, 3);
	Binary* div2 = new Binary("/",9, 3);
	All_Objects* all_count = new All_Objects();
	Clear_Task* clearer = new Clear_Task(tasks);
	Binary* sum2 = new Binary("+", 6, 7);
	Binary* sub = new Binary("-", 56, 49);

	/*adders*/
	Container<Task*> adders;
	adders.push_back(new Add_Task(tasks, sum1));
	adders.push_back(new Add_Task(tasks, mult1));
	adders.push_back(new Add_Task(tasks, obj_count));
	adders.push_back(new Add_Task(tasks, res_count));
	adders.push_back(new Add_Task(tasks, div1));
	adders.push_back(new Add_Task(tasks, div2));
	adders.push_back(new Add_Task(tasks, all_count));
	adders.push_back(new Add_Task(tasks, clearer));
	adders.push_back(new Add_Task(tasks, sum2));
	adders.push_back(new Add_Task(tasks, sub));

	for (auto i = adders.begin(); i != adders.end(); ++i) {
		i.value()->complete();
	}

	/*completing some:*/
	sum1->complete();
	mult1->complete();
	div2->complete();
	obj_count->complete();
	all_count->complete();
	sub->complete();

	std::cout << "the size of the container with tasks is " << (tasks.size()) << std::endl << std::endl;

	Container<std::string> infos;

	for(auto i = tasks.begin(); i != tasks.end(); ++i){
		infos.push_back(i.value()->toString());
		delete i.value();
	}

	for(auto i = infos.begin(); i != infos.end(); ++i) {
		std::cout << i.value() << std::endl;
	}

	for (auto i = adders.begin(); i != adders.end(); ++i) {
		delete i.value();
	}


	int counter = Object::get_count();
	std::cout << std::endl << "the amount of objects is " <<counter;

	return 0;
}