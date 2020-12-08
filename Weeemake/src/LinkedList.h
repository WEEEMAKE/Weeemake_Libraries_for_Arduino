#pragma once

#include <Arduino.h>

class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	void push(float value);
	void removeAt(uint16_t index);
	void insertAt(uint16_t index, float value);
	void replaceAt(uint16_t index, float value);
	void clear();
	int indexOf(float value);

	float getValueAt(uint16_t index);
	uint16_t getLength();
	bool include(float value);
private:
	void increaseBuffer();
private:
	uint16_t length;
	uint16_t size;
	float *buffer;
};