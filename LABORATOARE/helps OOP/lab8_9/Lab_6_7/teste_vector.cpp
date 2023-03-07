//#pragma once
//#define INIT_CAPACITY 100
//
//template <typename TElem>
//class IteratorVectorA;
//
//template <typename TElem>
//
//class VectorDinamic {
//private:
//	TElem* elems;
//	int n;
//	int cp;
//
//
//public:
//
//	//constructorul
//	VectorDinamic() {
//		this->n = 0;
//		this->cp = INIT_CAPACITY;
//		this->elems = new TElem[cp];
//	}
//	//constructor de copiere
//	VectorDinamic(const VectorDinamic < TElem>& v) {
//		n = v.n;
//		cp = v.cp;
//		elems = new TElem[cp];
//		for (int i = 0; i < n; i++)
//			elems[i] = v.elems[i];
//	}
//
//	/*
//	Pentru a adauga un element
//	*/
//	void add(const TElem& el) {
//		ensureCapacity();//daca e nevoie mai alocam memorie
//		elems[n++] = el;
//	}
//
//	/*
//	Determina elementul de pe pozitia poz
//	*/
//	TElem& get(int poz) const {
//		return elems[poz];
//	}
//
//	/*
//	Seteaza elementul de pe pozitia poz, cu elementul el
//	*/
//	void set(int poz, const TElem& el) {
//		elems[poz] = el;
//	}
//
//	/*
//	Resize
//	*/
//	void ensureCapacity() {
//		if (n < cp) {
//			return; //mai avem loc
//		}
//		cp *= 2;
//		TElem* aux = new TElem[cp];
//		for (int i = 0; i < n; i++) {
//			aux[i] = elems[i];
//		}
//		delete[] elems;
//		elems = aux;
//	}
//
//	/*
//	Face rezise la vector
//	*/
//	void resize() {
//		TElem* new_elems = new TElem[cp * 2];
//		for (int i = 0; i < n; i++) {
//			new_elems[i] = this->elems[i];
//		}
//		delete[] this->elems;
//		this->elems = new_elems;
//		this->cp = 2 * cp;
//	}
//
//	friend class IteratorVectorA<TElem>;
//
//	/*
//	Returneaza primul iterator
//	*/
//	IteratorVectorA<TElem> begin()
//	{
//		return IteratorVectorA<TElem>(*this);
//	}
//
//	/*
//	Returneaza primul iterator
//	*/
//	IteratorVectorA<TElem> end()
//	{
//		return IteratorVectorA<TElem>(*this, n);
//	}
//
//	//functie care returneaza dimensiunea VectorDinamicului dinamic
//	int size() {
//		return n;
//	}
//
//	/*
//	functia adauga un element la finalul listei
//	el->TElem, elementul pe care il adaugam
//	*/
//	void push_back(TElem el) {
//		if (this->n == this->cp)
//			resize();
//		this->elems[n++] = el;
//	}
//
//	//functia rescrie operatorul "[]" pt aceasta clasa
//	TElem& operator[](int i) {
//		return elems[i];
//	}
//
//	////functia care reinitializeaza lista cu lista goala
//	void clear_2() {
//		if (n != 0) {
//			delete elems;
//			this->n = 0;
//			this->cp = INIT_CAPACITY;
//			this->elems = new TElem[cp];
//		}
//	}
//
//
//	/*
//	functia sterge un element de pe o anumita pozitie
//	poz->int, pozitia elementului care va fi sters.
//	*/
//	void erase(int poz) {
//		for (int i = poz; i < n; i++)
//			elems[i] = elems[i + 1];
//		n--;
//	}
//
//	//functia rescrie opeeratorul "=" pt aceasta clasa.
//	void operator=(const VectorDinamic<TElem>& v) {
//		this->n = v.n;
//		this->cp = v.cp;
//		delete[] this->elems;
//		this->elems = new TElem[cp];
//		for (int i = 0; i < n; i++)
//			this->elems[i] = v.elems[i];
//	}
//
//
//	//destructor
//	~VectorDinamic() {
//		if (elems)
//			delete[] elems;
//	}
//
//};
//
//
//template<typename TElem>
//class IteratorVectorA {
//private:
//	const VectorDinamic<TElem>& v;
//	int poz = 0;
//public:
//	IteratorVectorA(const VectorDinamic<TElem>& v) noexcept;
//
//	IteratorVectorA(const VectorDinamic<TElem>& v, int poz)noexcept;
//
//
//	/*
//	Verifica daca elementul este valid
//	*/
//	bool valid()const {
//		return poz < v.lg;
//	}
//
//	/*
//	Returneaza elementul curent
//	*/
//	TElem& element() const {
//		return v.elems[poz];
//	}
//
//	/*
//	Trece iteratorul la urmatoarea pozitie
//	*/
//	void next() {
//		poz++;
//	}
//	/*
//	Suprascrie operatorul: "*"
//	*/
//	TElem& operator*() {
//		return element();
//	}
//
//	/*
//	Suprascrie operatorul: "++"
//	*/
//	IteratorVectorA& operator++() {
//		next();
//		return *this;
//	}
//
//	/*
//	Suprascrie operatorul "=="
//	*/
//	bool operator==(const IteratorVectorA& ot)noexcept {
//		return poz == ot.poz;
//	}
//
//	/*
//	Suprascire operatorul "!="
//	*/
//	bool operator!=(const IteratorVectorA& ot)noexcept {
//		return !(*this == ot);
//	}
//};
//
//template<typename TElem>
//IteratorVectorA<TElem>::IteratorVectorA(const VectorDinamic<TElem>& v) noexcept :v{ v } {}
//
//template<typename TElem>
//IteratorVectorA<TElem>::IteratorVectorA(const VectorDinamic<TElem>& v, int poz)noexcept : v{ v }, poz{ poz } {}
