#pragma once
#include <vector>
#include <iostream>

template <typename T>
class FilesManager
{
private:
	char _fileName[30];
public:
	FilesManager(const char* fileName);
	T read(int pos);
	bool write(T obj);
	int countEntries(); 
	std::vector<T> readAll();
	std::vector<T> top5();
	int top5Size;
};

template <typename T>
FilesManager<T>::FilesManager(const char* fileName)
{
	strcpy_s(_fileName, fileName);
}

template<typename T>
T FilesManager<T>::read(int pos)
{
	T obj;

	FILE* p = fopen(_fileName, "rb");

	if (p == NULL) return obj;

	fseek(p, pos * sizeof obj, 0);
	fread(&obj, sizeof obj, 1, p);
	fclose(p);

	return obj;
}

template<typename T>
bool FilesManager<T>::write(T obj)
{
	FILE* p = fopen(_fileName, "ab");

	if (p == NULL) return false;

	int itWrote = fwrite(&obj, sizeof obj, 1, p);

	fclose(p);

	return itWrote;
}

template<typename T>
int FilesManager<T>::countEntries()
{
	FILE* p = fopen(_fileName, "rb");

	if (p == NULL) return -1;

	fseek(p, 0, SEEK_END);

	int count = ftell(p) / sizeof(T);

	fclose(p);

	return count;
}

template<typename T>
std::vector<T> FilesManager<T>::readAll()
{
	std::vector<T> entries;
	int amount = this->countEntries();

	for (int i = 0; i < amount; i++) {
		T obj = this->read(i);
		entries.push_back(obj);
	}

	return entries;
}

template<typename T>
std::vector<T> FilesManager<T>::top5() {
	std::vector<T> top5(5);

	std::vector<T> entries = this->readAll();

	for (int i = 0; i < entries.size(); ++i) {
		for (int j = 0; j < entries.size() - 1; ++j) {
			if (entries[j].getPoints() < entries[j + 1].getPoints()) {
				T temp = entries[j];
				entries[j] = entries[j + 1];
				entries[j + 1] = temp;
			}
		}
	}

	int numElements = entries.size() > 5 ? 5 : entries.size();

	top5Size = numElements;

	for (int i = 0; i < numElements; i++) {
		top5[i] = entries[i];
	}

	return top5;
}