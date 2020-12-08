#include "LinkedList.h"

LinkedList::LinkedList():buffer(0), size(0), length(0)
{
}

LinkedList::~LinkedList()
{
	delete[] buffer;
	buffer = 0;
	length = 0;
	size = 0;
}

void LinkedList::increaseBuffer()
{
	if(length < size){
		return;
	}
	float *old = buffer;
	size = length + 1;
	buffer = new float[size];
	for(uint16_t i=0; i<length; ++i){
		buffer[i] = old[i];
	}
	delete[] old;
}

void LinkedList::push(float value)
{
	increaseBuffer();
	buffer[length] = value;
	++length;
}

void LinkedList::removeAt(uint16_t index)
{
	if(index >= length){
		return;
	}
	--length;
	for(uint16_t i=index; i<length; ++i){
		buffer[i] = buffer[i+1];
	}
}

void LinkedList::insertAt(uint16_t index, float value)
{
	if(index >= length){
		push(value);
		return;
	}
	increaseBuffer();
	for(uint16_t i=length; i>index; --i){
		buffer[i] = buffer[i-1];
	}
	buffer[index] = value;
	++length;
}

void LinkedList::replaceAt(uint16_t index, float value)
{
	if(index >= length){
		return;
	}
	buffer[index] = value;
}

float LinkedList::getValueAt(uint16_t index)
{
	if(index >= length){
		return 0;
	}
	return buffer[index];
}

uint16_t LinkedList::getLength()
{
	return length;
}

bool LinkedList::include(float value)
{
	return indexOf(value) >= 0;
}

void LinkedList::clear()
{
	length = 0;
}

int LinkedList::indexOf(float value)
{
	for(uint16_t i=0; i<length; ++i){
		if(buffer[i] == value){
			return i;
		}
	}
	return -1;
}