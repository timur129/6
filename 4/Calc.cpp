#include "Calc.h"

double pi = 3.14159265358979323846;
double e = 2.71828182845904523536;

void calc::reset_list()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

calc::calc()
{
	reset_list();
}

calc::~calc() {
	if (head) {
		while (head->next) {
			head = head->next;
			delete head->prev;
		}
		reset_list();
	}
}

void calc::add_first(string newElem, double res, Node::Priopity order, Node::Type exp)
{
	head = new Node(newElem, res, exp, order);
	tail = head;
}

bool calc::isEmpty()
{
	return (head == nullptr);
}

void calc::push_back(string newElem, double res, Node::Priopity order = Node::Priopity::undef, Node::Type exp = Node::Type::undef) // add in the end
{
	if (size == 0) {
		add_first(newElem, res, order, exp);
	}
	else {
		Node* tmp = new Node(newElem, res, exp, order);
		tmp->prev = tail;
		tail->next = tmp;
		tail = tmp;
	}
	size++;
}

void calc::push_front(string newElem, double res, Node::Priopity order, Node::Type exp) // add in the beginning
{
	if (size == 0) {
		add_first(newElem, res, order, exp);
	}
	else {
		Node* tmp = new Node(newElem, res, exp, order);
		head->prev = tmp;
		tmp->next = head;
		head = tmp;
	}
	size++;
}


void calc::pop_back() // delete last
{
	if (size == 0) {
		throw out_of_range("Nothing to delete");
	}
	if (size == 1) {
		delete head;
		reset_list();
	}
	else {
		Node* current = tail->prev;
		current->next = nullptr;
		delete tail;
		tail = current;
		size--;
	}
}

void calc::read_expression() { // read formula
	bool cont = true;
	string added;
	int bracket = 0;

	if (!head) {
		cin >> added;
		if (added[0] == '(') {
			tail->expression = static_cast<Node::Type>(16);
			tail->order = static_cast<Node::Priopity>(0);
			bracket++;
		}
		if (added[added.length() - 1] == ';') {
			cont = false;
			added.erase(added.length() - 1, 1);
		}
		push_back(added, 0, Node::Priopity::undef, Node::Type::undef);
		check_type(added);
		if (tail->expression == static_cast<Node::Type>(0)) {
			// incorrect input
			cout << endl << "Incorrect input. Can not identify expression." << endl;
			cont = false;
			return;
		}
	}

	while (cont) {
		cin >> added;
		if (added[added.length() - 1] == ';') {
			cont = false;
			added.erase(added.length() - 1, 1);
		}
		if (added[0] == '(') { bracket++;}
		if (added[0] == ')') { bracket--;}
		push_back(added, 0, Node::Priopity::undef, Node::Type::undef);
		check_type(added);
		if (tail->expression == static_cast<Node::Type>(0)) {
			// incorrect input
			cout << endl << "Incorrect input. Can not identify expression." << endl;
			return;
		}
	}
	if (bracket != 0) {
		// incorrect input
		cout << "Incorrect input: wrong bracket amount" << endl;
		return;
	}
}

void calc::check_type(string str) {
	if (str.length() == 1) { // it could be only a sign or an int
		if (str == "+") { 
			tail->expression = static_cast<Node::Type>(1); 
			tail->order = static_cast<Node::Priopity>(1); 
		
		}
		else if (str == "-") { 
			tail->expression = static_cast<Node::Type>(2); 
			tail->order = static_cast<Node::Priopity>(1); 
			
		}
		else if (str == "*") { 
			tail->expression = static_cast<Node::Type>(3); 
			tail->order = static_cast<Node::Priopity>(2); 

		}
		else if (str == "/") { 
			tail->expression = static_cast<Node::Type>(4); 
			tail->order = static_cast<Node::Priopity>(2); 
		
		}
		else if (str == "^") { 
			tail->expression = static_cast<Node::Type>(5); 
			tail->order = static_cast<Node::Priopity>(3); 
		
		}
		else if (str == "(") {
			tail->expression = static_cast<Node::Type>(16);
			tail->order = static_cast<Node::Priopity>(0);
		}
		else if (str == ")") {
			tail->expression = static_cast<Node::Type>(16);
			tail->order = static_cast<Node::Priopity>(0);
		}
		else {
			tail->expression = static_cast<Node::Type>(14);
			tail->order = static_cast<Node::Priopity>(10);
			tail->res = (double)(stoi(tail->data));
		}
	}
	else if ((str[0] == 'p') && (str[1] == 'i')) { 
		tail->expression = static_cast<Node::Type>(15); 
		tail->order = static_cast<Node::Priopity>(10); 
		tail->res = pi;
	}
	else if ((str[0] == 'e') && (str[1] == 'p') && (str[2] == 's')) { 
		tail->expression = static_cast<Node::Type>(15); 
		tail->order = static_cast<Node::Priopity>(10); 
		tail->res = e;
	}
	else if ((str[0] == 's') && (str[1] == 'i') && (str[2] == 'n')) { 
		tail->expression = static_cast<Node::Type>(6); 
		tail->order = static_cast<Node::Priopity>(4); 
	}
	else if ((str[0] == 'c') && (str[1] == 'o') && (str[2] == 's')) { 
		tail->expression = static_cast<Node::Type>(7); 
		tail->order = static_cast<Node::Priopity>(4); 
	}
	else if ((str[0] == 't') && (str[1] == 'g')) { 
		tail->expression = static_cast<Node::Type>(8); 
		tail->order = static_cast<Node::Priopity>(4); 
	}
	else if ((str[0] == 'c') && (str[1] == 't') && (str[2] == 'g')) { 
		tail->expression = static_cast<Node::Type>(9); 
		tail->order = static_cast<Node::Priopity>(4); 
	}
	else if ((str[0] == 'l') && (str[1] == 'n')) { 
		tail->expression = static_cast<Node::Type>(10); 
		tail->order = static_cast<Node::Priopity>(4); 
	}
	else if ((str[0] == 'l') && (str[1] == 'g')) { 
		tail->expression = static_cast<Node::Type>(11); 
		tail->order = static_cast<Node::Priopity>(4); 
	}
	else if ((str[0] == 's') && (str[1] == 'q') && (str[2] == 'r') && (str[3] == 't')) { 
		tail->expression = static_cast<Node::Type>(12); 
		tail->order = static_cast<Node::Priopity>(4); 
	}
	else if ((str[0] == 'c') && (str[1] == 'u') && (str[2] == 'b') && (str[3] == 'e') && (str[4] == 'r')) { 
	tail->expression = static_cast<Node::Type>(13); 
	tail->order = static_cast<Node::Priopity>(4);
	}
	else // chiselco
	{ 
		bool dot = false, number = false, incorrect = false, minus = (str[0] =='-');
		if (minus) {
			str.erase(0, 1); // delele minus before checking
		}
		for (int i = 0; i < (int)str.length(); i++) {
			number = ((str[i] == '0') || (str[i] == '1') || (str[i] == '2') || (str[i] == '3') || (str[i] == '4') || (str[i] == '5') || (str[i] == '6') ||
				(str[i] == '7') || (str[i] == '8') || (str[i] == '9'));
			if (!dot) dot = str[i] == '.'; // if prev symbols were not dots, check for dot
			if ((!number) && (!dot)) { // if str[i] is a letter, bracket or smth else
				incorrect = true;
				tail->expression = static_cast<Node::Type>(0);
				break;
			}
		}
		if (number && dot) {
			tail->expression = static_cast<Node::Type>(15);
			tail->order = static_cast<Node::Priopity>(10);
			tail->res = atof(tail->data.c_str());
		}
		else if (number && !dot) {
			tail->expression = static_cast<Node::Type>(14);
			tail->order = static_cast<Node::Priopity>(10);
			tail->res = (double)(stoi(tail->data));
		}
		if (minus) tail->res = - tail->res;
	}
}

void calc::print_to_console()
{
	cout << "Size is " << size << endl;
	if (head != nullptr) {
		Node* tmp = head;
		while (tmp->next) {
			cout << tmp->data << " ";
			tmp = tmp->next;
		}
		if (tmp) cout << tmp->data << endl;
		cout << "....." << endl;
	}
	else cout << "nothing to print" << endl;
}

void calc::clear()
{
	if (head) {
		while (head->next) {
			head = head->next;
			delete head->prev;
		}
		reset_list();
	}
}

void calc::inf_to_pref() {
	calc* top = new calc;
	Node* work = tail;
	calc* res = new calc;
	while (work->prev)
	{
		switch (work->order)
		{
		case calc::Node::Priopity::operands:
			res->push_front(work->data, work->res, work->order, work->expression);
			break;
		case calc::Node::Priopity::brackets:
			if (work->data == ")") {
				top->push_back(work->data, work->res, work->order, work->expression);
			}
			else {
				while (top->tail->data != ")")
				{
					res->push_front(top->tail->data, top->tail->res, top->tail->order, top->tail->expression);
					top->pop_back();
				}
				top->pop_back();
			}
			break;
		case calc::Node::Priopity::plus:
			//case calc::Node::Priopity::minus:
			if ((!top->isEmpty()) && ((int)top->tail->order >= (int)calc::Node::Priopity::plus)) {
				while ((int)top->tail->order >= (int)calc::Node::Priopity::plus) {
					res->push_front(work->data, work->res, work->order, work->expression);
					top->pop_back();
					if (top->isEmpty()) break;
				}
			}
			else top->push_back(work->data, work->res, work->order, work->expression);
			break;
		case calc::Node::Priopity::multiply:
			//case calc::Node::Priopity::divide:
			if ((!top->isEmpty()) && ((int)top->tail->order >= (int)calc::Node::Priopity::multiply)) {
				while ((int)top->tail->order >= (int)calc::Node::Priopity::multiply) {
					res->push_front(work->data, work->res, work->order, work->expression);
					top->pop_back();
					if (top->isEmpty()) break;
				}
			}
			else top->push_back(work->data, work->res, work->order, work->expression);
			break;
		case calc::Node::Priopity::raise:
			if ((!top->isEmpty()) && ((int)top->tail->order >= (int)calc::Node::Priopity::raise)) {
				while ((int)top->tail->order >= (int)calc::Node::Priopity::raise) {
					res->push_front(work->data, work->res, work->order, work->expression);
					top->pop_back();
					if (top->isEmpty()) break;
				}
			}
			else top->push_back(work->data, work->res, work->order, work->expression);
			break;
		case calc::Node::Priopity::func:
			if ((!top->isEmpty()) && ((int)top->tail->order == (int)calc::Node::Priopity::func)) {
				while ((int)top->tail->order == (int)calc::Node::Priopity::func) {
					res->push_front(work->data, work->res, work->order, work->expression);
					top->pop_back();
					if (top->isEmpty()) break;
				}
			}
			else top->push_back(work->data, work->res, work->order, work->expression);
			break;
		}
		work = work->prev;
	}
	switch (work->order)
	{
	case calc::Node::Priopity::operands: {
		res->push_front(work->data, work->res, work->order, work->expression);
		break;
	}
	case calc::Node::Priopity::brackets: {
		if (work->data == ")") {
			top->push_back(work->data, work->res, work->order, work->expression);
		}
		else {
			while (top->tail->data != ")")
			{
				res->push_front(work->data, work->res, work->order, work->expression);
				top->pop_back();
			}
		}
		break;
	}
	case calc::Node::Priopity::func: {
		if ((!top->isEmpty()) && ((int)top->tail->order == (int)calc::Node::Priopity::func)) {
			while ((int)top->tail->order == (int)calc::Node::Priopity::func) {
				res->push_front(work->data, work->res, work->order, work->expression);
				top->pop_back();
				if (top->isEmpty()) break;
			}
		}
		else top->push_back(work->data, work->res, work->order, work->expression);
		break;
	}
	}
		if (!top->isEmpty()) {
			do {
				res->push_front(top->tail->data, 0, top->tail->order, top->tail->expression);
				top->pop_back();
			} while (!top->isEmpty());
		}
		// exchange inf to pref
		head = res->head;
		tail = res->tail;
}

double calc::count(){
	Node* tmp = tail;
	Stack* top = new Stack;

	while (tmp->prev) {
		if (tmp->order == calc::Node::Priopity::operands) // if a number
		{
			top->push_back(tmp->res);
		}
		else if ((int)tmp->order == 4) {
			if (!top->isEmpty()) {
				double first = top->return_last();
				top->pop_back();
				switch ((int)tmp->expression)
				{
				case 6: { // sin
					top->push_back(sin(first));
					break;
				}
				case 7: { // cos
					top->push_back(cos(first));
					break;
				}
				case 8: { //tg
					top->push_back(tan(first));
					break;
				}
				case 9: { //ctg
					top->push_back(1 / tan(first));
					break;
				}
				case 10: { // ln
					top->push_back(log(first));
					break;
				}
				case 11: { // lg
					top->push_back(log10(top->return_last()));
					break;
				}
				case 12: { // sqrt
					top->push_back(sqrt(first));
					break;
				}
				case 13: { // cuber
					top->push_back(cbrt(first));
					break;
				}
				}
			}
			else {
				cout << "incorrect input. not enough chiselco";
				return 0.00;
			}
		}
		else {
			double first, second;
			if (!top->isEmpty()) {
				first = top->return_last();
				top->pop_back();
			}
			else {
				cout << "incorrect input. not enough chiselco";
				return 0.0;
			}
			if (!top->isEmpty()) {
				second = top->return_last();
				top->pop_back();
			}
			else {
				cout << "incorrect input. not enough chiselco";
				return 0.0;
			}
			switch ((int)tmp->expression)
			{
			case 1: {
				top->push_back((second + first));
				break;
			}
			case 2: {
				top->push_back((first - second));
				break;
			}
			case 3: {
				top->push_back((first * second));
				break;
			}
			case 4: {
				top->push_back((first / second));
				break;
			}
			}
		}
		tmp = tmp->prev;
	}

	if ((int)tmp->order == 4) {
		if (!top->isEmpty()) {
			double first = top->return_last();
			top->pop_back();
			switch ((int)tmp->expression)
			{
			case 6: { // sin
				top->push_back(sin(first));
				break;
			}
			case 7: { // cos
				top->push_back(cos(first));
				break;
			}
			case 8: { //tg
				top->push_back(tan(first));
				break;
			}
			case 9: { //ctg
				top->push_back(1 / tan(first));
				break;
			}
			case 10: { // ln
				top->push_back(log(first));
				break;
			}
			case 11: { // lg
				top->push_back(log10(first));
				break;
			}
			case 12: { // sqrt
				top->push_back(sqrt(first));
				break;
			}
			case 13: { // cuber
				top->push_back(cbrt(first));
				break;
			}
			}
		}
		else {
			cout << "incorrect input. not enough chiselco";
			return 0.00;
		}
	}
	else {
		double first, second;
		if (!top->isEmpty()) {
			first = top->return_last();
			top->pop_back();
		}
		else {
			cout << "incorrect input. not enough chiselco";
			return 0.0;
		}
		if (!top->isEmpty()) {
			second = top->return_last();
			top->pop_back();
		}
		else {
			cout << "incorrect input. not enough chiselco";
			return 0.0;
		}
		switch ((int)tmp->expression)
		{
		case 1: {
			top->push_back((second + first));
			break;
		}
		case 2: {
			top->push_back((first - second));
			break;
		}
		case 3: {
			top->push_back((first * second));
			break;
		}
		case 4: {
			top->push_back((first / second));
			break;
		}
		case 5: {
			top->push_back(pow(first, second));
			break;
		}
		}
	}

	return top->return_last(); // when counting is over, on the top of chiselco stack is the result
}

string calc::return_data()
{
	return tail->data;
}

//
//void calc::pop_front() // delete first
//{
//	if (size == 0) {
//		throw out_of_range("Nothing to delete");
//	}
//	if (size == 1) {
//		delete inf_head;
//		reset_list();
//	}
//	else {
//		inf_head = inf_head->next;
//		delete inf_head->prev;
//		size--;
//	}
//}

//void calc::insert(string newElem, int index) // add #index
//{
//	if (index > size - 1) {
//		throw out_of_range("Index is greater than list size");
//	}
//	if (index < 0) {
//		throw out_of_range("Index is less than zero");
//	}
//	if (index == 0) { // newElem - new head
//		push_front(newElem);
//	}
//	else if (index == size - 1) { // newElem - new tail
//		push_back(newElem);
//	}
//	else {
//		Node* add = new Node(newElem);
//		Node* tmp = inf_head;
//		for (int i = 1; i < index - 1; i++) {
//			tmp = tmp->next;
//		} // tmp - before adding
//		add->prev = tmp;
//		add->next = tmp->next;
//		tmp->next = add;
//		size++;
//	}
//}

//string calc::at(size_t index) const // find data from #index
//{
//	if (index >= size) {
//		throw out_of_range("Index is greater than list size");
//	}
//	if (index < 0) {
//		throw out_of_range("Index is less than zero");
//	}
//	size_t counter = 0;
//	Node* current = inf_head;
//	while (counter != index) {
//		current = current->next;
//		counter++;
//	}
//	return current->data;
//}

//void calc::remove(int index)
//{
//	Node* tmp = inf_head;
//	if (index > size - 1) {
//		throw out_of_range("Index is greater than list size");
//	}
//	if (index < 0) {
//		throw out_of_range("Index is less than zero");
//	}
//	if (index == 0) { // delete head
//		pop_front();
//	}
//	else if (index == size - 1) { // delete tail
//		pop_back();
//	}
//	else {
//		for (int i = 0; i < index; i++) {
//			tmp = tmp->next;
//		} // tmp should be deleted
//		tmp->prev->next = tmp->next;
//		tmp->next->prev = tmp->prev;
//		delete tmp;
//		size--;
//	}
//}

//size_t calc::get_size() const
//{
//	return size;
//}

//void calc::set(int index, string newElem)
//{
//	if (index > size - 1) {
//		throw out_of_range("Index is greater than list size");
//	}
//	if (index < 0) {
//		throw out_of_range("Index is less than zero");
//	}
//	else {
//		Node* tmp = inf_head;
//		for (int i = 0; i < index; i++) {
//			tmp = tmp->next;
//		}
//		tmp->data = newElem;
//	}
//}

//void calc::insert(calc newList, int index)
//{
//	if (index > size - 1) {
//		throw out_of_range("Index is greater than list size");
//	}
//	if (index < 0) {
//		throw out_of_range("Index is less than zero");
//	}
//	if (index == 0) {
//		newList.inf_tail->next = inf_head;
//		inf_head->prev = newList.inf_tail;
//		inf_head = newList.inf_head;
//		size = size + newList.get_size();
//	}
//	else if (index == size - 1) {
//		inf_tail->next = newList.inf_head;
//		newList.inf_head->prev = inf_tail;
//		inf_tail = newList.inf_tail;
//		size = size + newList.get_size();
//	}
//	else {
//		Node* tmp = inf_head;
//		int counter = index;
//		while (counter)
//		{
//			tmp = tmp->next;
//			counter--;
//		} // add after tmp
//		newList.inf_tail->next = tmp->next;
//		tmp->next->prev = newList.inf_tail;
//		tmp->next = newList.inf_head;
//		newList.inf_head->prev = inf_head;
//		size = size + newList.get_size();
//	}
//}