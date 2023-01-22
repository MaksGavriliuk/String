#include "String.h"

int len(char const* _str) {
	int len = 0, i = 0;
	while (_str[i] != '\0') {
		len++;
		i++;
	}
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
}

String::String(char const* str) {
	_len = len(str);
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
}

String::String(string str) {
	_len = str.length();
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++) {
		_str[i] = str[i];
	}
	_str[_len] = '\0';
}

String::String(int x) {
	char* str = intToString(x);
	_len = len(str);
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
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++) {
		_str[i] = str[i];
	}
	_str[_len] = '\0';
}

String::String(size_t count, char symbol) {
	try {
		_str = new char[count + 1];
		for (size_t i = 0; i < count; i++)
			_str[i] = symbol;
		_str[count] = '\0';
		_len = count;
	}
	catch (...) { cout << "\nÍå óäàëîñü ñîçäàòü îáúåêò\n"; return; }
}

String::String(String& str, size_t start, size_t len) {
	if (start >= str._len) {
		String();
	}
	else if (start + len > str._len) {
		int new_len = str._len - start;
		_str = new char[new_len + 1];
		for (size_t i = 0; i < new_len; i++) 
			_str[i] = str[start + i]; 
		_str[new_len] = '\0';
		_len = new_len;
	}
	else {
		_str = new char[len + 1];
		for (size_t i = 0; i < len; i++) 
			_str[i] = str[start + i];
		_str[len] = '\0';
		_len = len;
	}
}

String::String(char const* str, size_t start, size_t lenght) {
	if (start >= len(str)) {
		String();
	}
	else if (start + lenght > len(str)) {
		int new_len = len(str) - start;
		_str = new char[new_len + 1];
		for (size_t i = 0; i < new_len; i++)
			_str[i] = str[start + i];
		_str[new_len] = '\0';
		_len = new_len;
	}
	else {
		_str = new char[lenght + 1];
		for (size_t i = 0; i < lenght; i++)
			_str[i] = str[start + i];
		_str[lenght] = '\0';
		_len = lenght;
	}
}

String::String(const String& str) {
	_len = str._len;
	_str = new char[_len + 1];
	for (size_t i = 0; i < _len; i++)
		_str[i] = str[i];
	_str[_len] = '\0';
}

String::~String() {
	delete _str;
	_len = 0;
}

int String::lenght() const {
	int len = 0, i = 0;
	while (_str[i] != '\0') {
		len++;
		i++;
	}
	return len;
}

void String::print() const {
	for (int i = 0; i < _len; i++) 
		std::cout << _str[i];
}

void String::println() const {
	for (int i = 0; i < _len; i++)
		std::cout << _str[i];
	cout << endl;
}

int String::count(char const* in) const {
	int count = 0;
	int _len_in = len(in);
	for (int i = 0; i <= _len - _len_in; i++) {
		bool _is = true;
		for (int j = 0; j < _len_in; j++) {
			if (_str[i + j] != in[j]) {
				_is = false;
				break;
			}
		}
		if (_is) count++;
	}
	return count;
}

//
//String String::append(char symbol) {
//
//
//
//}



String String::lower() {
	for (int i = 0; i < _len; i++)
		_str[i] = to_lower(_str[i]);
	return String(_str);
}

String String::upper() {
	for (int i = 0; i < _len; i++)
		_str[i] = to_upper(_str[i]);
	return String(_str);
}

String String::title() {
	if (_str[0] != '\0') {
		_str[0] = to_upper(_str[0]);
		return _str;
	}
}

bool String::startswith(char const* start) const {
	int _len_start = len(start);
	if (_len_start > _len)
		return false;
	for (int i = 0; i < _len_start; i++)
		if (_str[i] != start[i])
			return false;
	return true;
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

String String::append(char const* str) {
	String _old(_str), _new(str);
	char const* _add = (*this + _new).to_char();
	int _len_add = len(_add);
	_str = new char[_len_add + 1];
	for (int i = 0; i < _len_add; i++)
		_str[i] = _add[i];
	_str[_len_add] = '\0';
	_len = _len_add;
	return *this;
}

const char* String::to_char() const {
	return _str;
}

string String::S_to_string() const {
	return string(_str);
}

int String::lfind(char const* _find) const {
	for (int i = 0; i <= _len - len(_find); i++) {
		bool _is = true;
		for (int j = 0; j < len(_find); j++) {
			if (_str[i + j] != _find[j]) {
				_is = false;
				break;
			}
		}
		if (_is) return i;
	}
	return -1;
}

int String::rfind(char const* _find) const {
	return 0;
}

vector<int> String::find(char const* _find) const {
	vector<int> vect;
	for (int i = 0; i <= _len - len(_find); i++) {
		bool _is = true;
		for (int j = 0; j < len(_find); j++) {
			if (_str[i + j] != _find[j]) {
				_is = false;
				break;
			}
		}
		if (_is) vect.push_back(i);
	}
	return vect;
}

String String::replace(char const* _old, char const* _new) {
	if (count(_old) == 0)
		return _str;

}

String String::replaceAll(char const* _old, char const* _new) {
	if (count(_old) == 0)
		return _str;

}

String String::swapcase() {
	for (size_t i = 0; i < _len; i++) {
		if (_str[i] == to_lower(_str[i]))
			_str[i] = to_upper(_str[i]);
		else if (_str[i] == to_upper(_str[i]))
			_str[i] = to_lower(_str[i]);
	}
	return String(_str);
}

void String::clear() {
	delete _str;
	_len = 0;
	_str = new char[1];
	_str[0] = '\0';
	_len = 0;
}

bool String::empty() const {
	return !_len;
}

String String::erase(size_t index) {
	if (index >= _len)
		return *this;
	int i = index;
	for (i; i < _len - 1; i++)
		_str[i] = _str[i + 1];
	_str[i] = '\0';
	return String(_str);
}

String String::reverse() {
	return this->slice(_len, -1, -1);
}




String String::slice(size_t first) {
	if (first >= _len) 
		return String();
	return String(_str, first, _len);
}

String String::slice(size_t first, size_t second) {
	if (first >= _len)
		return String();
	if(second >= _len)
		return String(_str, first, _len);
	return String(_str, first, second - first);
}

String String::slice(int first, int second, int step) {
	if (step == 0)
		return String();

	if (step > 0) {
		if (first >= _len)
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



String String::ascii_lowercase(char const*lang){
	if (strcmp(lang, "en") == 0)
		return String("abcdefghijklmnopqrstuvwxyz");
	else if (strcmp(lang, "ru") == 0)
		return String("àáâãäå¸æçèéêëìíîïğñòóôõö÷øùúûüışÿ");
}
String String::ascii_uppercase(char const*lang){
	if (strcmp(lang, "en") == 0)
		return String("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	else if (strcmp(lang, "ru") == 0)
		return String("ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß");
}

String String::digits() {
	return String("0123456789");
}





char& String::operator[](int index) const {
	return _str[index];
}

char* String::operator=(char const* str) {
	_len = len(str);
	delete _str;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++) 
		_str[i] = str[i];
	_str[_len] = '\0';
	return _str;
}

String String::operator=(String& str) {
	_len = str.lenght();
	delete _str;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++)
		_str[i] = str[i];
	_str[_len] = '\0';
	return String(_str);
}

String String::operator=(const String& str) {
	_len = str.lenght();
	delete _str;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++)
		_str[i] = str[i];
	_str[_len] = '\0';
	return String(_str);
}

String String::operator=(string& str) {
	_len = str.length();
	delete _str;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++)
		_str[i] = str[i];
	_str[_len] = '\0';
	return String(_str);
}

String String::operator=(const string& str) {
	_len = str.length();
	delete _str;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; i++)
		_str[i] = str[i];
	_str[_len] = '\0';
	return String(_str);
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
	int _len_conc = len(_str1) + _str2._len;
	char* str = new char[_len_conc + 1];
	for (int i = 0; i < len(_str1); i++)
		str[i] = _str1[i];
	for (int i = 0; i < _str2._len; i++)
		str[len(_str1) + i] = _str2[i];
	str[_len_conc] = '\0';
	return String(str);
}

String operator+(String& _str, int number) {
	String _str_num(number);
	return _str + _str_num;
}

String operator+(int number, String& _str) {
	String _str_num(number);
	return _str_num + _str;
}

String operator+(String& _str, double number) {
	String _str_num(number);
	return _str + _str_num;
}

String operator+(double number, String& _str) {
	String _str_num(number);
	return _str_num + _str;
}





String operator*(String& _str, int number) {
	int _len = _str._len;
	char* str = new char[_len * number + 1];
	for (int i = 0; i < number; i++) 
		for (int j = 0; j < _len; j++) 
			str[i * _len + j] = _str[j];
	str[_len * number] = '\0';
	return String(str);
}

String operator*(int number, String& _str) {
	int _len = _str._len;
	char* str = new char[_len * number + 1];
	for (int i = 0; i < number; i++)
		for (int j = 0; j < _len; j++)
			str[i * _len + j] = _str[j];
	str[_len * number] = '\0';
	return String(str);
}


String operator*=(String & _str, int number) {
	_str = _str * number;
	return _str;
}

String operator+=(String& _str, String _str2) {
	_str = _str + _str2;
	return _str;
}

String operator+=(String& _str, char const* _str2) {
	_str = _str + _str2;
	return _str;
}

String operator+=(String& _str, int number) {
	_str = _str + number;
	return _str;
}

String operator+=(String& _str, double number) {
	_str = _str + number;
	return _str;
}

ostream& operator<<(ostream& stream, String& _str) {
	for (int i = 0; i < _str._len; i++)
		stream << _str[i];
	return stream;
}

ostream& operator<<(ostream& stream, const String& _str) {
	for (int i = 0; i < _str._len; i++)
		stream << _str[i];
	return stream;
}

String operator>>(istream& stream, String& _str) {
	_str._str = new char[1024];
	stream >> _str._str;
	_str._len = len(_str._str);
	return _str;
}


bool operator==(String& _str1, String& _str2) {
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(const String& _str1, String& _str2) {
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(String& _str1, const String& _str2) {
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(const String& _str1, const String& _str2) {
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(String& _str1, char const* _str2) {
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(char const* _str1, String& _str2) {
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(const String& _str1, char const* _str2) {
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(char const* _str1, const String& _str2) {
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(String& _str1, string& _str2){
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(string& _str1, String& _str2){
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(string& _str1, const String& _str2){
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(const String& _str1, string& _str2){
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(String& _str1, const string& _str2){
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(const string& _str1, String& _str2){
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(const String& _str1, const string& _str2){
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}

bool operator==(const string& _str1, const String& _str2){
	for (int i = 0; _str1[i] != '\0' || _str2[i] != '\0'; i++)
		if (_str1[i] != _str2[i])
			return false;
	return true;
}


bool operator!=(String& str1, String& str2) {
	return str1 == str2 ? false : true;
}

bool operator!=(const String& str1, String& str2) {
	return str1 == str2 ? false : true;
}

bool operator!=(String& str1, const String& str2) {
	return str1 == str2 ? false : true;
}

bool operator!=(const String& str1, const String& str2) {
	return str1 == str2 ? false : true;
}

bool operator!=(String& str1, char const* str2){
	return str1 == str2 ? false : true;
}

bool operator!=(char const* str1, String& str2){
	return str1 == str2 ? false : true;
}

bool operator!=(const String& str1, char const* str2){
	return str1 == str2 ? false : true;
}

bool operator!=(char const* str1, const String& str2){
	return str1 == str2 ? false : true;
}

bool operator!=(String& str1, string& str2){
	return str1 == str2 ? false : true;
}

bool operator!=(string& str1, String& str2){
	return str1 == str2 ? false : true;
}

bool operator!=(string& str1, const String& str2){
	return str1 == str2 ? false : true;
}

bool operator!=(const String& str1, string& str2){
	return str1 == str2 ? false : true;
}

bool operator!=(String& str1, const string& str2){
	return str1 == str2 ? false : true;
}

bool operator!=(const string& str1, String& str2){
	return str1 == str2 ? false : true;
}

bool operator!=(const String& str1, const string& str2){
	return str1 == str2 ? false : true;
}

bool operator!=(const string& str1, const String& str2){
	return str1 == str2 ? false : true;
}
