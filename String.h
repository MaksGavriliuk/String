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
	char* _str;
	int _len;

public:
	String();
	String(char const*);
	String(char);
	String(string);
	String(int);
	String(double);
	String(size_t, char);
	String(String&, size_t, size_t);
	String(char const*, size_t, size_t);
	String(const String&);
	~String();

	int lenght() const;
	void print() const;
	void println() const;

	int count(char const*) const;
	String lower();
	String upper();
	String title();
	bool startswith(char const*) const;
	bool endswith(char const*) const;

	String replace(char const*, char const*);
	String replaceAll(char const*, char const*);
	int lfind(char const*) const;
	int rfind(char const*) const; // дописать
	vector<int> find(char const*) const;
	String swapcase();
	const char* to_char() const;
	string S_to_string() const;
	void clear();
	bool empty() const;
	String reverse();
	//bool in()
	
	String erase(size_t); // удаляет из строки символы, начиная с переданного индекса и до конца
	String erase(size_t, size_t); // удаляет начиная с определённого индекса несколько элементов
	
	String insert(size_t, char); // вставляет 1 символ
	String insert(size_t, size_t, char); // вставляем несколько одинаковых символов
	String insert(size_t, String&);
	String insert(size_t, char const*);
	String insert(size_t, string&);
	String substr(size_t);
	String substr(size_t, size_t); // возвращает подстроку от i до j индекса
	
	String append(char);
	String append(char const*);
	String append(int, char);
	String append(String&, size_t, size_t);
	String append(char const*, size_t, size_t);

	String slice(size_t); // возвращает строку, начиная с определённого индекса
	String slice(size_t, size_t); // возвращает строку с первого до второго индекса
	String slice(int, int, int); // возвращает строкус первого до второго индекса с определённым шагом


	static String ascii_lowercase(char const*);
	static String ascii_uppercase(char const*);
	static String digits();



	char& operator[](int) const;
	
	char* operator=(char const*);
	String operator=(String&);
	String operator=(const String&);
	String operator=(string&);
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
	
	friend String operator*=(String&, int);
	friend String operator+=(String&, String);
	friend String operator+=(String&, char const*);
	friend String operator+=(String&, int);
	friend String operator+=(String&, double);

	friend ostream& operator<<(ostream&, String&);
	friend ostream& operator<<(ostream&, const String&);
	friend String operator>>(istream&, String&);
	
	friend bool operator==(String&, String&);
	friend bool operator==(const String&, String&);
	friend bool operator==(String&, const String&);
	friend bool operator==(const String&, const String&);

	friend bool operator==(String&, char const*);
	friend bool operator==(char const*, String&);
	friend bool operator==(const String&, char const*);
	friend bool operator==(char const*, const String&);

	friend bool operator==(String&, string&);
	friend bool operator==(string&, String&);
	friend bool operator==(string&, const String&);
	friend bool operator==(const String&, string&);
	
	friend bool operator==(String&, const string&);
	friend bool operator==(const string&, String&);
	friend bool operator==(const String&, const string&);
	friend bool operator==(const string&, const String&);

	friend bool operator!=(String&, String&);
	friend bool operator!=(const String&, String&);
	friend bool operator!=(String&, const String&);
	friend bool operator!=(const String&, const String&);
	
	friend bool operator!=(String&, char const*);
	friend bool operator!=(char const*, String&);
	friend bool operator!=(const String&, char const*);
	friend bool operator!=(char const*, const String&);
	
	friend bool operator!=(String&, string&);
	friend bool operator!=(string&, String&);
	friend bool operator!=(string&, const String&);
	friend bool operator!=(const String&, string&);

	friend bool operator!=(String&, const string&);
	friend bool operator!=(const string&, String&);
	friend bool operator!=(const String&, const string&);
	friend bool operator!=(const string&, const String&);

};

