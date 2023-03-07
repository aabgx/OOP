	#pragma once
#define INIT_CAPACITY 100


template <class TElem>
class VectorDinamic {
private:
	/*
	Aici e reprezentarea interna
	*/
	TElem* elems;
	int n;
	int cp;
	void resize() {
		TElem* new_elems = new TElem[cp * 2];
		for (int i = 0; i < n; i++) {
			new_elems[i] = elems[i];
		}
		delete[] elems;
		elems = new_elems;
		cp = 2 * cp;
	}
public:
	/*
	Aici e interfata publica
	*/

	/*
	Constructorul implicit
	*/
	VectorDinamic() {
		n = 0;
		cp = INIT_CAPACITY;
		elems = new TElem[cp];
	}
	VectorDinamic(const VectorDinamic<TElem>& v) {
		n = v.n;
		cp = v.cp;
		elems = new TElem[cp];
		for (int i = 0; i < n; i++)
			elems[i] = v.elems[i];
	}

	/*
	Returneaza dimensiunea vectorului dinamic
	return->int
	*/
	int size() {
		return n;
	}


	/*
	Reface lista sa fie goala
	*/
	void clear() {
		if (n != 0)
		{
		delete elems;
		n = 0;
		cp = INIT_CAPACITY;
		elems = new TElem[cp];
		}
	}


	/*
	Adauga un element la finalul listei
	el->TElem, elementul pe care dorim sa il adaugam
	*/
	void push_back(TElem el) {
		if (n == cp)resize();
		elems[n++] = el;
	}

	
	/*
	Rescrie operatorul "[]" pentru aceasta clasa
	*/
	TElem& operator[](int i) {
		return elems[i];
	}

	/*
	Deconstructor implicit
	*/
	~VectorDinamic() {
		if(elems)
			delete[] elems;
	}

	/*
	Determina pozitia primului element
	*/
	int begin() {
		return 0;
	}

	/*
	Sterge un element de pe o anumita pozitie
	poz->int, pozitia elementului din vector pe care urmeaza sa il stergem
	*/
	void erase(int poz) {
		for (int i = poz; i < n; ++i)
			elems[i] = elems[i + 1];
		n--;
	}

	/*
	Rescrie operatorul "="
	*/
	void operator=(const VectorDinamic<TElem>& v) {
		n = v.n;
		cp = v.cp;
		delete[] elems;
		elems = new TElem[cp];
		for (int i = 0; i < n; i++)
			elems[i] = v.elems[i];
	}
};