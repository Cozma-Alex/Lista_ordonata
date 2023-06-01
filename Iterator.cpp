#include "Iterator.h"
#include "LO.h"
#include <stdexcept>

Iterator::Iterator(const LO& lo) : lo(lo){
	this->curent = lo.primul;
}

void Iterator::prim(){
	this->curent = lo.primul;
}

void Iterator::urmator(){
    if(!valid())
        throw std::exception();
	this->curent = this->curent->urm();
}

bool Iterator::valid() const{
    return curent != nullptr;
}

TElement Iterator::element() const{
    if(!valid())
        throw std::exception();
    return curent->elem();
}
