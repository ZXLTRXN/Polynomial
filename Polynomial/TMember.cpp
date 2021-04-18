#include "TMember.h"

using namespace Polynomial;

TMember::TMember() {
    this->FCoeff = 0;
    this->FDegree = 0;
}

TMember::TMember(int coeff,int deg) {
    this->FCoeff = coeff;
    this->FDegree = deg;
}



int TMember::get_degree()
{
    return this->FDegree;
}

int TMember::get_coeff()
{
    return this->FCoeff;
}

void TMember::set_degree(int deg)
{
    this->FDegree = deg;
}

void TMember::set_coeff(int coeff)
{
    this->FCoeff = coeff;
}



bool Polynomial::operator==(const TMember& c1, const TMember& c2)
{
    return (c1.FCoeff == c2.FCoeff &&
        c1.FDegree == c2.FDegree);
}

bool Polynomial::operator!= (const TMember& c1, const TMember& c2)
{
    return !(c1 == c2);
}

std::string Polynomial::TMember::to_string()
{ 
    if (this->FCoeff == 0) {
        return std::to_string(this->FCoeff);
    }
    if (this->FDegree == 0) {
        return std::to_string(this->FCoeff);
    }

    if (this->FDegree == 1) {
        if (this->FCoeff == 1) {
            return "x";
        }
        else {
            return std::to_string(this->FCoeff) + "x";
        }
  
    }

    if (this->FCoeff == 1) {
        return "x^" + std::to_string(this->FDegree);
    }
    else {
        return std::to_string(this->FCoeff) + "x^" + std::to_string(this->FDegree);
    }
}



TMember* TMember::diff()
{
    if(this->FDegree == 0) return new TMember();

    int new_coeff = this->FCoeff * this->FDegree;
    int new_deg = this->FDegree - 1;
    return new TMember(new_coeff, new_deg);
}

double TMember::calc(int x) {
    return this->FCoeff * pow(x, this->FDegree);
}

