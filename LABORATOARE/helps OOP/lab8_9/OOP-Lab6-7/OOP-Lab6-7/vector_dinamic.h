#pragma once
#define INIT_CAPACITY 100

template <class TElem>

class VectorDinamic {
private:
	TElem* elems;
	int n;
	int cp;
	void resize() {
		TElem* new_elems = new TElem[cp * 2];
		for (int i = 0; i < n; i++) {
			new_elems[i] = this->elems[i];
		}
		delete[] this->elems;
		this->elems = new_elems;
		this->cp = 2 * cp;
	}

public:

	//constructorul
	VectorDinamic() {
		this->n = 0;
		this->cp = INIT_CAPACITY;
		this->elems = new TElem[cp];
	}
	//constructor de copiere
	VectorDinamic(const VectorDinamic < TElem>& v) {
		n = v.n;
		cp = v.cp;
		elems = new TElem[cp];
		for (int i = 0; i < n; i++)
			this->elems[i] = v.elems[i];
	}
												
	//functie care returneaza dimensiunea VectorDinamicului dinamic
	int size() {
		return n;
	}

	//functia care reinitializeaza lista cu lista goala
	void clear() {
		if (n != 0) {
			delete elems;
			this->n = 0;
			this->cap = INIT_CAPACITY;
			this->elems = new TElem[cp];
		}
	}

	/*
	functia adauga un element la finalul listei
	el->TElem, elementul pe care il adaugam
	*/
	void push_back(TElem el) {
		if (this->n == this->cp)
			resize();
		this->elems[n++] = el;
	}

	//functia rescrie operatorul "[]" pt aceasta clasa
	TElem& operator[](int i) {
		return elems[i];
	}

	//functia returneaza pozitia primului element
	int begin() {
		return 0;
	}

	int end() {

	}

	/*
	functia sterge un element de pe o anumita pozitie
	poz->int, pozitia elementului care va fi sters.
	*/
	void erase(int poz) {
		for (int i = poz; i < n; i++)
			elems[i] = elems[i + 1];
		n--;
	}

	//functia rescrie opeeratorul "=" pt aceasta clasa.
	void operator=(const VectorDinamic<TElem>& v) {
		this->n = v.n;
		this->cp = v.cp;
		delete[] this->elems;
		this->elems = new TElem[cp];
		for (int i = 0; i < n; i++)
			this->elems[i] = v.elems[i];
	}


	//destructor
	~VectorDinamic() {
		if (elems)
			delete[] elems;
	}

};


