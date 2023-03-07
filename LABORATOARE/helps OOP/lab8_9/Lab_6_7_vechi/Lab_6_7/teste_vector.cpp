#pragma once
#include "vector_dinamic.h"
#include <cassert>
#include <iostream>
using namespace std;

void test_size() {

	VectorDinamic<int> v;
	assert(v.size() == 0);
}

void test_push_back() {
	VectorDinamic<int> v;
	assert(v.size() == 0);

	v.push_back(1);
	assert(v.size() == 1);

	v.push_back(1);
	assert(v.size() == 2);

	v.push_back(1);
	assert(v.size() == 3);

}

void test_get() {
	VectorDinamic<int> v;
	assert(v.size() == 0);

	v.push_back(1);
	assert(v.size() == 1);

	v.push_back(2);
	assert(v.size() == 2);

	v.push_back(3);
	assert(v.size() == 3);

	assert(v[0] == 1);
	assert(v[1] == 2);
	assert(v[2] == 3);

	v.clear();
	assert(v.size() == 0);

	for (int i = 0; i <= 20; i++)
		v.push_back(2 * i);
	for (int i = 0; i <= 20; i++)
		assert(v[i] == 2 * i);

}

void test_clear() {
	VectorDinamic<int>v;
	for (int i = 0; i <= 80; i++)
		v.push_back(2 * i);
	v.clear();
	assert(v.size() == 0);
	for (int i = 0; i <= 80; i++)
		v.push_back(2 * i);
	v.clear();
	assert(v.size() == 0);
	for (int i = 0; i <= 80; i++)
		v.push_back(2 * i);
	v.clear();
	assert(v.size() == 0);
	for (int i = 0; i <= 80; i++)
		v.push_back(2 * i);
	v.clear();
	assert(v.size() == 0);
}

void test_resize() {
	VectorDinamic<int> v;
	for (int i = 0; i <= 200; i++)
		v.push_back(2 * i);
	for (int i = 0; i <= 200; i++)
		assert(v[i] == 2 * i);
	
	assert(v.size() == 201);

}

void test_erase() {
	VectorDinamic<int>v;
	for (int i = 0; i <= 200; i++)
		v.push_back(2 * i);
	for (int i = 0; i <= 200; i++)
		v.erase(v.begin() + i);
	assert(v.size() == 0);

	v.push_back(1);
	v.push_back(2);
	v.erase(0);
	assert(v[0] == 2);
	assert(v.size() == 1);
	v.push_back(1);
	v.erase(0);
	assert(v.size() == 1);
	assert(v[0] == 1);
}