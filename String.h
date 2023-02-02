#pragma once
#define _CTR_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

int len(char const*);
char to_lower(char);
char to_upper(char);
char* intToString(int number);


class String {
private:
	char* _str;
	int _len;
	int _cap;

	// дописать end (static size_t end = -1) как символ конца строки. ѕрименить в конструкторах и функци€х с длиной


	// работа с capation
	void resize();
	void resize(size_t);
	void rewrite(); // перезапись строки после довыделени€ пам€ти

public:
	static const int end = INT_MAX;

public:
	String();
	String(char const*);
	String(char);
	String(const string&);
	String(int);
	String(double);
	String(int, char);
	String(const String&, int, int);
	String(char const*, int, int);
	String(string&, int, int);
	String(const String&);
	~String();

	String& append(char);
	String& append(char const*);
	String& append(int, char);
	String& append(const String&);
	String& append(const string&);
	String& append(String&, int, int);
	String& append(char const*, int, int);

	String& assign(char);
	String& assign(char const*);
	String& assign(const string&);
	String& assign(const String&);
	String& assign(char const*, int, int);
	String& assign(String&, int, int);
	String& assign(string&, int, int);

	static String ascii_lowercase(char const*);
	static String ascii_uppercase(char const*);

	char at(int) const;
	int capacity() const;
	void clear();
	int count(char const*) const;
	static String digits();
	bool empty() const;
	bool endswith(char const*) const;

	String& erase(int); // удал€ет из строки символы, начина€ с переданного индекса и до конца
	String& erase(int, int); // удал€ет, начина€ с определЄнного индекса несколько элементов

	vector<int> find(char const*) const;
	bool in(char) const;
	bool in(char const*) const;
	bool in(const string&) const;
	bool in(const String&) const;

	String& insert(int, char) ; // вставл€ет 1 символ
	String& insert(int, int, char); // вставл€ем несколько одинаковых символов
	String& insert(int, String&); 
	String& insert(int, char const*);
	String& insert(int, string&);

	int length() const;
	int lfind(char const*) const;
	String lower() const;
	void print() const;
	void println() const;

	String replace(char const*, char const*) const;
	String replaceAll(char const*, char const*) const;

	String reverse();
	int rfind(char const*) const;
	string S_to_string() const;

	String slice(int) const; // возвращает строку, начина€ с определЄнного индекса
	String slice(int, int) const; // возвращает строку с первого до второго индекса
	String slice(int, int, int) const; // возвращает строку с первого до второго индекса с определЄнным шагом

	String sort() const;
	bool startswith(char const*) const;
	void swap(String&); // a.swap(b) содержимое строк свапаетс€
	String swapcase() const;
	String title() const;
	char* to_char() const;
	const char* to_const_char() const;
	String upper() const;


	template<class T>
	static String join(vector<T>& args, char const* sep) {
		String str;
		for (size_t i = 0; i < args.size();i++) {
			str += args[i];
			str.append(sep);
		}
		return str;
	}


	String& as() {
		_str[0] = 'a';
		return *this;
	}




	/*
	class iterator {
	private:
		String* _cur;
	public:
		iterator(String* first) : _cur(first) {}
		String& operator+(int n) { return *(_cur + n); }
		String& operator-(int n) { return *(_cur - n); }
		String& operator++(int n) { return *_cur++; }
		String& operator--(int n) { return *_cur--; }
		String& operator++() { return *++_cur; }
		String& operator--() { return *--_cur; }

		bool operator!=(const iterator& it) { return _cur != it._cur; }
		bool operator==(const iterator& it) { return _cur == it._cur; }
		String& operator*() { return *_cur; }
	};

	iterator begin() { return this; }
	iterator end() { return this + sizeof(this->_str); }
	*/


	char& operator[](int) const;
	
	String& operator=(char);
	String operator=(char const*);
	String operator=(const String&);
	String operator=(const string&);

	friend String operator+(String, String);
	friend String operator+(String&, char const*);
	friend String operator+(char const*, String&);
	friend String operator+(String&, int);
	friend String operator+(int, String&);
	friend String operator+(String&, double);
	friend String operator+(double, String&);

	friend String operator*(String&, int);
	friend String operator*(int, String&);
	
	String& operator*=(int);
	
	String& operator+=(const String&);
	String& operator+=(char const*);
	String& operator+=(const string&);
	String& operator+=(char);
	String& operator+=(int);
	String& operator+=(double);

	friend ostream& operator<<(ostream&, const String&);
	friend String operator>>(istream&, String&);
	
	friend bool operator==(const String&, const String&);
	friend bool operator==(const String&, char const*);
	friend bool operator==(char const*, const String&);
	friend bool operator==(const String&, const string&);
	friend bool operator==(const string&, const String&);

	friend bool operator!=(const String&, const String&);
	friend bool operator!=(const String&, char const*);
	friend bool operator!=(char const*, const String&);
	friend bool operator!=(const String&, const string&);
	friend bool operator!=(const string&, const String&);

};

