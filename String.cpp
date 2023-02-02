#include "String.h"

int len(char const* str) {
	int len = 0, i = 0;
	for (int i = 0; str[i] != '\0'; i++)
		len++;
	return len;
}

char to_lower(char symbol) {
	if (symbol >= 65 && symbol <= 90)
		return symbol + 32;
	else if (symbol >= -64 && symbol <= -33)
		return symbol + 32;
}

char to_upper(char symbol) {
	if (symbol >= 97 && symbol <= 122)
		return symbol - 32;
	else if (symbol >= -32 && symbol <= -1)
		return symbol - 32;
}

char* intToString(int number) {
	int length = snprintf(nullptr, 0, "%d", number);
	char* str = new char[length + 1];
	snprintf(str, length + 1, "%d", number);
	return str;
}



String::String() {
	_str = new char[1];
	_str[0] = '\0';
	_len = 0;
	_cap = 0;
}

String::String(char const* str) {
	_len = len(str);
	_cap = _len;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++) {
		_str[i] = str[i];
	}
	_str[_len] = '\0';
}

String::String(char c) {
	_str = new char[2];
	_str[0] = c;
	_str[1] = '\0';
	_len = 1;
	_cap = 1;
}

String::String(const string& str) {
	_len = str.length();
	_cap = _len;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++) {
		_str[i] = str[i];
	}
	_str[_len] = '\0';
}

String::String(int x) {
	char* str = intToString(x);
	_len = len(str);
	_cap = _len;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++) {
		_str[i] = str[i];
	}
	_str[_len] = '\0';
}

String::String(double x) {

	string s = to_string(x);

	if (s[s.size() - 1] == '0')
		for (size_t i = s.size() - 1; s[i] == '0'; i--)
			s.erase(i, 1);

	if (s[s.size() - 1] == '.')
		s.erase(s.size() - 1, 1);

	char const* str = s.c_str();
	_len = len(str);
	_cap = _len;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++) {
		_str[i] = str[i];
	}
	_str[_len] = '\0';
}

String::String(int count, char symbol) {
	_len = count;
	_cap = _len;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++)
		_str[i] = symbol;
	_str[_len] = '\0';
}

String::String(const String& str, int start, int len) {
	if (start >= str._len || start < (-str._len)) {
		*this = String();
		return;
	}

	if (len == 0)
		*this = String();
	else if (len > 0) {
						
		if (start + len > str._len)
			_len = str._len - start;
		else
			_len = len;
				
		_cap = _len + 1;
		_str = new char[_len + 1];
		for (int i = 0; i < _len; i++)
			_str[i] = str[start + i];
		_str[_len] = '\0';
				
	}
	else {

		if (start + len < -str._len)
			_len = str._len + start + 1;
		else
			_len = -len;

		_cap = _len;
		_str = new char[_len + 1];
		for (int i = 0; i < _len; i++)
			_str[i] = str[start - i];
		_str[_len] = '\0';

	}

}

String::String(char const* str, int start, int len) {
	String str_(str);
	*this = String(str_, start, len);
}

String::String(string& str, int start, int len) {
	String str_(str);
	*this = String(str_, start, len);
}

String::String(const String& str) {
	_len = str._len;
	_cap = _len;
	_str = new char[_len + 1];
	for (size_t i = 0; i < _len; i++)
		_str[i] = str[i];
	_str[_len] = '\0';
}

String::~String() {
	delete _str;
	_len = 0;
	_cap = 0;
}



String& String::append(char symbol) {
	
	bool is_resize = false;
	while (_cap <= _len + 1) {
		resize(10);
		is_resize = true;
	}
	if (is_resize)
		rewrite();

	_str[_len++] = symbol;
	_str[_len] = '\0';
	return *this;
}

String& String::append(char const* str) {
	
	int length = len(str);

	bool is_resize = false;
	while (_cap <= _len + length) {
		resize(length);
		is_resize = true;
	}
	if (is_resize)
		rewrite();

	for (int i = 0; i < length; i++)
		_str[_len + i] = str[i];
	_len += length;
	_str[_len] = '\0';
	return *this;
}

String& String::append(int count, char symbol) {
	
	bool is_resize = false;
	while (_cap <= _len + count) {
		resize();
		is_resize = true;
	}
	if (is_resize)
		rewrite();

	for (int i = 0; i < count; i++)
		_str[_len + i] = symbol;
	
	_len += count;
	_str[_len] = '\0';
	return *this;
}

String& String::append(const String& str) {
	
	bool is_resize = false;
	while (_cap <= _len + str.length()) {
		resize(str.length());
		is_resize = true;
	}
	if (is_resize)
		rewrite();

	for (int i = 0; i < str.length(); i++)
		_str[_len + i] = str[i];
	
	_len += str.length();
	_str[_len] = '\0';
	return *this;
}

String& String::append(const string& str) {
	
	bool is_resize = false;
	while (_cap <= _len + str.length()) {
		resize(str.length());
		is_resize = true;
	}
	if (is_resize)
		rewrite();

	for (int i = 0; i < str.length(); i++)
		_str[_len + i] = str[i];
	
	_len += str.length();
	_str[_len] = '\0';
	return *this;
}

String& String::append(String& str, int start, int end) {
	return append(String(str, start, end));
}

String& String::append(char const* str, int start, int end) {
	return append(String(str, start, end));
}


String& String::assign(char symbol) {
	delete _str;
	_len = 1;
	_cap = 5;
	_str = new char[2];
	_str[0] = symbol;
	_str[1] = '\0';
	return *this;
}

String& String::assign(char const* str) {
	delete _str;
	_len = len(str);
	_cap = _len + 1;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++)
		_str[i] = str[i];
	_str[_len] = '\0';
	return *this;
}

String& String::assign(const string& str) {
	delete _str;
	_len = str.length();
	_cap = _len + 1;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++)
		_str[i] = str[i];
	_str[_len] = '\0';
	return *this;
}

String& String::assign(const String& str){
	delete _str;
	_len = str.length();
	_cap = _len + 1;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++)
		_str[i] = str[i];
	_str[_len] = '\0';
	return *this;
}

//String& String::assign(char const*, int, int){}
//String& String::assign(String&, int, int){}
//String& String::assign(string&, int, int) {}



String String::ascii_lowercase(char const* lang) {
	String language = String(lang).lower().slice(0, 2);
	if (language == "en")
		return String("abcdefghijklmnopqrstuvwxyz");
	else if (language == "ru")
		return String("àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ");
}

String String::ascii_uppercase(char const* lang) {
	String language = String(lang).lower().slice(0, 2);
	if (language == "en")
		return String("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	else if (language == "ru")
		return String("ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß");
}



char String::at(int index) const {
	if (index < 0) {
		if (index < (-_len))
			abort();
		return _str[index + _len];
	}
	if (index >= _len)
		abort();
	return _str[index];
}

int String::capacity() const {
	return _cap;
}

void String::clear() {
	delete _str;
	_len = 0;
	_cap = 5;

	_str = new char[5];
	_str[0] = '\0';
}

int String::count(char const* str) const {
	int count = 0;
	int len_str = len(str);
	for (int i = 0; i <= _len - len_str; i++) {
		bool is = true;
		for (int j = 0; j < len_str; j++) {
			if (_str[i + j] != str[j]) {
				is = false;
				break;
			}
		}
		if (is) count++;
	}
	return count;
}


String String::digits() {
	return String("0123456789");
}

bool String::empty() const {
	return !_len;
}

bool String::endswith(char const* end) const {
	int _len_end = len(end);
	if (_len_end > _len)
		return false;
	for (int i = 0; i < _len_end; i++)
		if (_str[_len - _len_end + i] != end[i])
			return false;
	return true;
}


String& String::erase(int index) {
	if (index <= -_len || index >= _len)
		return *this;
	if (index < 0)
		index += _len;
	int i = index;
	for (i; i < _len - 1; i++)
		_str[i] = _str[i + 1];
	_str[i] = '\0';
	--_len;
	return *this;
}

String& String::erase(int start, int len) {
	if (start <= -_len || start >= _len)
		return *this;
	if (start < 0)
		start += _len;
	// äîïèñàòü



	return *this;
}


vector<int> String::find(char const* find) const {
	vector<int> vect;
	vect.reserve(count(find));
	for (int i = 0; i <= _len - len(find); i++) {
		bool is = true;
		for (int j = 0; j < len(find); j++) {
			if (_str[i + j] != find[j]) {
				is = false;
				break;
			}
		}
		if (is) vect.push_back(i);
	}
	return vect;
}

bool String::in(char symbol) const {
	for (int i = 0; i <= _len; i++) 
		if (_str[i] == symbol)
			return true;
	return false;
}

bool String::in(char const* str) const {

	int len_str = len(str);
	for (int i = 0; i <= _len - len_str; i++) {
		bool is = true;
		for (int j = 0; j < len_str; j++) {
			if (_str[i + j] != str[j]) {
				is = false;
				break;
			}
		}
		if (is) return true;
	}
	return false;
}

// ïîäóìàòü, ñòîèò ëè ïèñàòü îäèíàêîâûå ìåòîäû
bool String::in(const string& str) const {
	for (int i = 0; i <= _len - str.length(); i++) {
		bool is = true;
		for (int j = 0; j < str.length(); j++) {
			if (_str[i + j] != str[j]) {
				is = false;
				break;
			}
		}
		if (is) return true;
	}
	return false;
}

bool String::in(const String& str) const {
	for (int i = 0; i <= _len - str.length(); i++) {
		bool is = true;
		for (int j = 0; j < str.length(); j++) {
			if (_str[i + j] != str[j]) {
				is = false;
				break;
			}
		}
		if (is) return true;
	}
	return false;
}


String& String::insert(int index, char symbol)  {
	
	if (index < -_len || index >= _len)
		return *this;
	if (index < 0)
		index += _len + 1;
	
	bool is_resize = false;
	while (_cap <= _len + 1) {
		resize(10);
		is_resize = true;
	}
	if (is_resize)
		rewrite();
	
	for (int i = _len; i > index; i--)
		_str[i] = _str[i - 1];
	_str[index] = symbol;
	_str[++_len] = '\0';
	return *this;
}

String& String::insert(int index, int count, char symbol) {
	
	if (index < -_len || index >= _len || count <= 0)
		return *this;
	if (index < 0)
		index += _len + 1;
	
	bool is_resize = false;
	while (_cap <= _len + 1) {
		resize(count);
		is_resize = true;
	}
	if (is_resize)
		rewrite();

	char* rstr = new char[_len - index + 1];
	for (int i = 0; i < _len - index; i++)
		rstr[i] = _str[index + i];
	rstr[_len - index] = '\0';

	for (int i = 0; i < count; i++)
		_str[index + i] = symbol;
	for (int i = 0; i < _len - index; i++)
		_str[index + count + i] = rstr[i];
	
	delete rstr;

	_len += count;
	_str[_len] = '\0';
	return *this;
}

String& String::insert(int index, String& str) {
	
	if (index < -_len || index >= _len)
		return *this;
	if (index < 0)
		index += _len + 1;
	
	bool is_resize = false;
	while (_cap <= _len + str.length()) {
		resize(str.length());
		is_resize = true;
	}
	if (is_resize)
		rewrite();

	char* rstr = new char[_len - index + 1];
	for (int i = 0; i < _len - index; i++)
		rstr[i] = _str[index + i];
	rstr[_len - index] = '\0';

	for (int i = 0; i < str.length(); i++)
		_str[index + i] = str[i];
	for (int i = 0; i < _len - index; i++)
		_str[index + str.length() + i] = rstr[i];

	delete rstr;

	_len += str.length();
	_str[_len] = '\0';
	return *this;
}

String& String::insert(int index, char const* str) {
	
	if (index < -_len || index >= _len)
		return *this;
	if (index < 0)
		index += _len + 1;
	int length = len(str);
	
	bool is_resize = false;
	while (_cap <= _len + length) {
		resize(length);
		is_resize = true;
	}
	if (is_resize)
		rewrite();

	char* rstr = new char[_len - index + 1];
	for (int i = 0; i < _len - index; i++)
		rstr[i] = _str[index + i];
	rstr[_len - index] = '\0';

	for (int i = 0; i < length; i++)
		_str[index + i] = str[i];
	for (int i = 0; i < _len - index; i++)
		_str[index + length + i] = rstr[i];

	delete rstr;

	_len += length;
	_str[_len] = '\0';
	return *this;
}

String& String::insert(int index, string& str) {

	if (index < -_len || index >= _len)
		return *this;
	if (index < 0)
		index += _len + 1;
	
	bool is_resize = false;
	while (_cap <= _len + str.length()) {
		resize(str.length());
		is_resize = true;
	}
	if (is_resize)
		rewrite();

	char* rstr = new char[_len - index + 1];
	for (int i = 0; i < _len - index; i++)
		rstr[i] = _str[index + i];
	rstr[_len - index] = '\0';

	for (int i = 0; i < str.length(); i++)
		_str[index + i] = str[i];
	for (int i = 0; i < _len - index; i++)
		_str[index + str.length() + i] = rstr[i];

	delete rstr;

	_len += str.length();
	_str[_len] = '\0';
	return *this;
}


int String::length() const {
	return _len;
}

int String::lfind(char const* find) const {
	for (int i = 0; i <= _len - len(find); i++) {
		bool is = true;
		for (int j = 0; j < len(find); j++) {
			if (_str[i + j] != find[j]) {
				is = false;
				break;
			}
		}
		if (is) return i;
	}
	return -1;
}


String String::lower() const {
	String str(*this);
	for (int i = 0; i < str._len; i++)
		str[i] = to_lower(str[i]);
	return str;
}


void String::print() const {
	for (int i = 0; i < _len; i++)
		cout << _str[i];
}

void String::println() const {
	for (int i = 0; i < _len; i++)
		cout << _str[i];
	cout << endl;
}

String String::replace(char const* old_, char const* new_) const {
	while (in(old_)) {

	}
	return *this;
}

String String::replaceAll(char const* _old, char const* _new) const {
	if (count(_old) == 0)
		return String(*this);

}


String String::reverse() {
	return slice(_len, -1, -1);
}


int String::rfind(char const* find) const {
	int len_find = len(find);
	for (int i = _len - len_find; i >= 0; i--) {
		bool is = true;
		for (int j = 0; j < len_find; j++) {
			if (_str[i + j] != find[j]) {
				is = false;
				break;
			}
		}
		if (is) return i;
	}
	return -1;
}


string String::S_to_string() const {
	return string(_str);
}

String String::slice(int first) const {
	if (first >= _len)
		return String();
	if (first < -_len)
		first = 0;
	if (first < 0)
		first += _len;
	return String(*this, first, _len);
}

String String::slice(int first, int second) const {
	if (first >= _len)
		return String();
	if (first < -_len)
		first = 0;
	if (first < 0)
		first += _len;
	if (second < 0)
		second += _len;
	if (first >= second)
		return String();
	if (second >= _len)
		return String(*this, first, _len);
	return String(*this, first, second - first);
}

String String::slice(int first, int second, int step) const {
	if (step == 0)
		return String();

	if (step > 0) {
		if (first >= _len)
			return String();
		if (first < -_len)
			first = 0;
		if (first < 0)
			first += _len;
		if (second < 0)
			second += _len;
		if (first >= second)
			return String();
		if (second >= _len)
			second = _len;
		char* new_str = new char[(_len - first) / step + 2];
		int k = 0;
		for (size_t i = first; i < second; i += step) {
			new_str[k] = _str[i];
			k++;
		}
		new_str[k] = '\0';
		return String(new_str);

	}

	if (second >= first)
		return String();
	if (first >= _len)
		first = _len - 1;
	if (first < 0)
		return String();
	if (second < 0)
		second = -1;
	if (second >= _len)
		return String();
	char* new_str = new char[(first - second) / (-step) + 2];
	int k = 0;
	for (int i = first; i > second; i += step) {
		new_str[k] = _str[i];
		k++;
	}
	new_str[k] = '\0';
	return String(new_str);

}

String String::sort() const {
	return *this;
}

bool String::startswith(char const* start) const {
	int len_start = len(start);
	if (len_start > _len)
		return false;
	for (int i = 0; i < len_start; i++)
		if (_str[i] != start[i])
			return false;
	return true;
}

void String::swap(String& str) {
	String buf(*this);
	*this = str;
	str = buf;
}

String String::swapcase() const {
	String str(*this);
	for (size_t i = 0; i < str._len; i++) {
		if (str[i] == to_lower(str[i]))
			str[i] = to_upper(str[i]);
		else str[i] = to_lower(str[i]);
	}
	return str;
}

String String::title() const {
	String str(*this);
	if (_str[0] != '\0') 
		str[0] = to_upper(str[0]);
	return str;
}

char* String::to_char() const {
	char* str = new char[_len + 1];
	for (int i = 0; i < _len; i++)
		str[i] = _str[i];
	str[_len] = '\0';
	return str;
}


const char* String::to_const_char() const {
	return _str;
}

String String::upper() const {
	String str(*this);
	for (int i = 0; i < _len; i++)
		str[i] = to_upper(str[i]);
	return str;
}




void String::resize() {
	
	if (_len < 10)
		_cap += 5;
	else if (_len < 40)
		_cap += 1.5 * _len;
	else if (_len < 100)
		_cap += 1.4 * _len;
	else _cap += 1.25 * _len;
	
}

void String::resize(size_t count) {

	if (_len < 10)
		_cap += count + 1;
	else if (_len < 40)
		_cap += 2 * count;
	else if (_len < 100)
		_cap += 5 * count;
	else if (_cap < 500)
		_cap += 10 * count;
	else
		_cap += 20 * count;

}

void String::rewrite() {
	
	char* str = new char[_len];

	for (int i = 0; i < _len; i++)
		str[i] = _str[i];
	delete _str;

	_str = new char[_cap];
	for (int i = 0; i < _len; i++)
		_str[i] = str[i];

	_str[_len] = '\0';
	delete str;
}





char& String::operator[](int index) const {
	if (index < 0) {
		if (index < (-_len))
			abort();
		return _str[index + _len];
	}
	if (index >= _len)
		abort();
	return _str[index];
}


String& String::operator=(char symbol) {
	return assign(symbol);
}

String String::operator=(char const* str) {
	return assign(str);
}

String String::operator=(const String& str) {
	return assign(str);
}

String String::operator=(const string& str) {
	return assign(str);
}


String operator+(String _str1, String _str2) {
	int _len_conc = _str1._len + _str2._len;
	char* str = new char[_len_conc + 1];
	for (int i = 0; i < _str1._len; i++)
		str[i] = _str1[i];
	for (int i = 0; i < _str2._len; i++)
		str[_str1._len + i] = _str2[i];
	str[_len_conc] = '\0';
	return String(str);
}

String operator+(String& _str1, char const* _str2) {
	int _len_conc = _str1._len + len(_str2);
	char* str = new char[_len_conc + 1];
	for (int i = 0; i < _str1._len; i++)
		str[i] = _str1[i];
	for (int i = 0; i < len(_str2); i++)
		str[_str1._len + i] = _str2[i];
	str[_len_conc] = '\0';
	return String(str);
}

String operator+(char const* _str1, String& _str2) {
	String sum(_str1); 
	sum += _str2;
	return sum;
}

String operator+(String& _str, int number) {
	String sum(_str);
	sum += String(number);
	return sum;
}

String operator+(int number, String& _str) {
	String sum(number);
	sum += _str;
	return sum;
}

String operator+(String& _str, double number) {
	String sum(_str);
	sum += String(number);
	return sum;
}

String operator+(double number, String& _str) {
	String sum(number);
	sum += _str;
	return sum;
}


String operator*(String& str, int number) {
	String multy(str);
	multy *= number;
	return multy;
}

String operator*(int number, String& str) {
	String multy(str);
	multy *= number;
	return multy;
}


String& String::operator*=(int number) {
	
	String old(_str);
	delete _str;

	_str = new char[_len * number + 1];
	for (int i = 0; i < number; i++)
		for (int j = 0; j < _len; j++)
			_str[i * _len + j] = old[j];
	_str[_len * number] = '\0';
	_len = _len * number;

	return *this;

}


String& String::operator+=(const String& str2) {

	String old(*this);
	delete _str;

	int _len_conc = old._len + str2._len;
	_str = new char[_len_conc + 1];

	for (int i = 0; i < old._len; i++)
		_str[i] = old[i];
	for (int i = 0; i < str2._len; i++)
		_str[old._len + i] = str2[i];

	_str[_len_conc] = '\0';
	_len = _len_conc;
	return *this;
}

String& String::operator+=(const string& str) {
	return *this += String(str);
}

String& String::operator+=(char const* _str2) {
	return *this += String(_str2);;
}

String& String::operator+=(char symbol) {
	return append(symbol);
}

String& String::operator+=(int number) {
	return *this += String(number);
}

String& String::operator+=(double number) {
	return *this += String(number);
}


ostream& operator<<(ostream& stream, const String& _str) {
	for (int i = 0; i < _str._len; i++)
		stream << _str[i];
	return stream;
}

String operator>>(istream& stream, String& _str) {
	_str._str = new char[1024]; // ïîäóìàòü
	stream >> _str._str;
	_str._len = len(_str._str);
	return _str;
}


bool operator==(const String& _str1, const String& _str2) {
	for (int i = 0; i < _str1._len && i < _str2._len; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(const String& _str1, char const* _str2) {
	for (int i = 0; i < _str1._len && i < len(_str2); i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(char const* _str1, const String& _str2) {
	for (int i = 0; i < len(_str1) && i < _str2._len; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(const String& _str1, const string& _str2){
	for (int i = 0; i < _str1._len && i < _str2.length(); i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(const string& _str1, const String& _str2){
	for (int i = 0; i < _str1.length() && i < _str2._len; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}



bool operator!=(const String& str1, const String& str2) {
	return str1 == str2 ? false : true;
}

bool operator!=(const String& str1, char const* str2){
	return str1 == str2 ? false : true;
}

bool operator!=(char const* str1, const String& str2){
	return str1 == str2 ? false : true;
}

bool operator!=(const String& str1, const string& str2){
	return str1 == str2 ? false : true;
}

bool operator!=(const string& str1, const String& str2){
	return str1 == str2 ? false : true;
}
