/*

#pragma once

#include <iostream>

using namespace std;



template <typename eT>
class IteratorVectorT;



template <typename eT>
class myVector {
private:
	int cap;
	int nrOfEl;
	eT* lista;

public:

	myVector(int size = 5);
	myVector(const myVector& ot);
	~myVector();

	//redimensionare x2
	void expand();

	//add push_back
	void push(const eT& element);

	void erase(const int index);

	const int size() const noexcept { return this->nrOfEl; }

	eT& operator[] (const int index) const;

	myVector& operator=(const myVector& ot);

	eT& get(int poz) const;

	friend class IteratorVectorT<eT>;
	//functii care creaza iteratori
	IteratorVectorT<eT> begin();
	IteratorVectorT<eT> end();
};



template<typename eT>
myVector<eT>::myVector(int size) {
	this->cap = size;
	this->nrOfEl = 0;
	this->lista = new eT[cap];
}

template<typename eT>
myVector<eT>::myVector(const myVector& ot) {
	lista = new eT[ot.cap];
	for (int i = 0; i < ot.size(); i++)
		lista[i] = ot.lista[i];
	cap = ot.cap;
	nrOfEl = ot.nrOfEl;
}


template<typename eT>
myVector<eT>::~myVector() {
	delete[] lista;
}

template<typename eT>
eT& myVector<eT>::operator[](const int index) const{
	if (index < 0 || index >= this->nrOfEl)
		throw exception();
	return lista[index];
}



template<typename eT>
myVector<eT>& myVector<eT>::operator=(const myVector<eT>& ot) {
	if (this == &ot) {
		return *this;//s-a facut l=l;
	}
	delete[] lista;
	lista = new eT[ot.cap];
	//copiez elementele
	for (int i = 0; i < ot.lg; i++) {
		lista[i] = ot.lista[i];  //assignment din Pet
	}
	nrOfEl = ot.nrOfEl;
	cap = ot.cap;
	return *this;
}


template<typename eT>
eT& myVector<eT>::get(int poz) const {
	return lista[poz];
}



template<typename eT>
void myVector<eT>::expand() {
	this->cap *= 2;

	eT* copiereLista = new eT [this->cap];

	for (int i = 0; i < this->nrOfEl; i++)
	{
		copiereLista[i] = this->lista[i];
	}

	delete[] this->lista;

	this->lista = copiereLista;
}



template<typename eT>
void myVector<eT>::push(const eT& element) {
	if (this->nrOfEl >= this->cap) {
		this->expand();
	}

	this->lista[this->nrOfEl++] = element;
}


template<typename eT>
void myVector<eT>::erase(const int index) {
	if (index < 0 || index >= this->nrOfEl)
		throw exception();


	for (int i = index; i < this->nrOfEl-1; i++) {
		auto& c = lista[i];
		lista[i] = lista[i + 1];
		lista[i + 1] = c;
	}


	this->nrOfEl--;
}


template<typename eT>
IteratorVectorT<eT> myVector<eT>::begin()
{
	return IteratorVectorT<eT>(*this);
}

template<typename eT>
IteratorVectorT<eT> myVector<eT>::end()
{
	return IteratorVectorT<eT>(*this, nrOfEl);
}



//---------------------------------ITERATOR-------------------------------


template<typename eT>
class IteratorVectorT {
private:
	const myVector<eT>& v;
	int poz = 0;
public:
	IteratorVectorT(const myVector<eT>& v) noexcept;
	IteratorVectorT(const myVector<eT>& v, int poz)noexcept;
	bool valid()const;
	eT& element() const;
	void next();
	eT& operator*();
	IteratorVectorT& operator++();
	bool operator==(const IteratorVectorT& ot)noexcept;
	bool operator!=(const IteratorVectorT& ot)noexcept;
};

template<typename eT>
IteratorVectorT<eT>::IteratorVectorT(const myVector<eT>& v) noexcept :v{ v } {}

template<typename eT>
IteratorVectorT<eT>::IteratorVectorT(const myVector<eT>& v, int poz)noexcept : v{ v }, poz{ poz } {}

template<typename eT>
bool IteratorVectorT<eT>::valid()const {
	return poz < v.lg;
}

template<typename eT>
eT& IteratorVectorT<eT>::element() const {
	return v.elems[poz];
}

template<typename eT>
void IteratorVectorT<eT>::next() {
	poz++;
}

template<typename eT>
eT& IteratorVectorT<eT>::operator*() {
	return element();
}

template<typename eT>
IteratorVectorT<eT>& IteratorVectorT<eT>::operator++() {
	next();
	return *this;
}

template<typename eT>
bool IteratorVectorT<eT>::operator==(const IteratorVectorT<eT>& ot) noexcept {
	return poz == ot.poz;
}

template<typename eT>
bool IteratorVectorT<eT>::operator!=(const IteratorVectorT<eT>& ot)noexcept {
	return !(*this == ot);
}

*/