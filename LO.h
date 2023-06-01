#pragma once

class Iterator;

typedef int TComparabil;
typedef TComparabil TElement;

typedef bool (*Relatie)(TElement, TElement);

#define NULL_TELEMENT -1

class Nod {
public:

    friend class LO;
    Nod(TElement el, Nod* urmator, Nod* precedent) {
        this->el = el;
        this->urmator = urmator;
        this->precedent = precedent;
    }

    Nod* urm(){
        return urmator;
    }

    TElement elem(){
        return el;
    }

private:
    TElement el;
    Nod *urmator, *precedent;
};

class LO {
private:
	friend class Iterator;
private:
	/* aici reprezentarea */

    Nod* primul;
    Nod* ultim;

    Relatie rel;

public:
		// constructor
		LO (Relatie r);

		// returnare dimensiune
		int dim() const;

		// verifica daca LO e vida
		bool vida() const;

		// prima pozitie din LO
		Iterator prim() const;

		// returnare element de pe pozitia curenta
		//arunca exceptie daca poz nu e valid
		TElement element(Iterator poz) const;

		// adaugare element in LO a.i. sa se pastreze ordinea intre elemente
		void adauga(TElement e);

		// sterge element de pe o pozitie poz si returneaza elementul sters
		//dupa stergere poz e pozitionat pe elementul de dupa cel sters
		//arunca exceptie daca poz nu e valid
		TElement sterge(Iterator& poz);

		// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
		Iterator cauta(TElement e) const;

        void eraseList();

		//destructor
		~LO();

};
