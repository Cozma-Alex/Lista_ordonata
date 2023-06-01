#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

LO::LO(Relatie r) {
	 rel = r;
     this->primul = nullptr;
     this->ultim = nullptr;
}

// returnare dimensiune
int LO::dim() const {
    int s=0;
    Nod *nod_curent = primul;
    while (nod_curent != nullptr)
    {
        s++;
        nod_curent = nod_curent->urmator;
    }
    return s;
}

// verifica daca LO e vida
bool LO::vida() const {
	if(dim() == 0)
    	return true;
    return false;
}

// prima pozitie din LO
Iterator LO::prim() const {
    Iterator it = Iterator(*this);
    return it;
}

// returnare element de pe pozitia curenta
//arunca exceptie daca poz nu e valid
TElement LO::element(Iterator poz) const {
    if(!poz.valid()){
        throw std::exception();
    }
    return poz.element();
}

//sterge element de pe o pozitie poz si returneaza elementul sters
//dupa stergere poz e pozitionat pe elementul de dupa cel sters
//arunca exceptie daca poz nu e valid
TElement LO::sterge(Iterator& poz) {
	if(!poz.valid()){
        throw std::exception();
    }
    TElement el = poz.element();

    if(poz.curent != primul)
    {
        Iterator it = Iterator(*this);
        Iterator it2 = cauta(el);
        while(it.valid() and it.curent->urmator != it2.curent)
            it.urmator();
        it.curent->urmator = it2.curent->urmator;
        it.curent->precedent = it2.curent->precedent;
    }
    else
    {
        poz.urmator();
        primul = poz.curent;
    }
    return el;
}


// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
Iterator LO::cauta(TElement e) const {
    Iterator it = Iterator(*this);
    it.curent = nullptr;

    if (primul == nullptr)
        return it;

    Nod *p = primul;
    while ((p != nullptr) and (p->el != e) and (!rel(e, p->el))) {
        p = p->urmator;
    }

    if ((p != nullptr) and (p->el == e)) {
        it.curent = p;
    }
    return it;
}


// adaugare element in LO
void LO::adauga(TElement e) {
    Nod *nou = new Nod(e, nullptr, nullptr);
    if(primul == nullptr)
        primul = nou;
    else{
        Nod* nod_curent = primul;
        while(nod_curent->urmator != nullptr and rel(nod_curent->el, e))
            nod_curent = nod_curent->urmator;

        if(!rel(nod_curent->el,e))
        {
            nou->urmator = nod_curent;
            if(nod_curent->precedent != nullptr)
                nod_curent->precedent->urmator = nou;
            else {
                primul = nou;
            }
            nou->precedent = nod_curent->precedent;
            nod_curent->precedent = nou;
        }
        else{
            nou->urmator = nod_curent->urmator;
            nod_curent->urmator = nou;
            nou->precedent = nod_curent;
        }
    }
}

void LO::eraseList() {
    Nod* curent = primul;
    Nod* next = nullptr;
    while (curent != nullptr) {
        next = curent->urmator;
        delete curent;
        curent = next;
    }
    primul = nullptr;
    ultim = nullptr;
}

//destructor
LO::~LO() {
	while(primul != nullptr)
    {
        Nod *p = primul;
        primul = primul->urmator;
        delete p;
    }
}
