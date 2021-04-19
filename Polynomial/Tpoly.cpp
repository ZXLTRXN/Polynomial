//#include "TPoly.h"

//using namespace Polynomial;
#include "TMember.h"
#include <iostream> 
#include <algorithm>
#include<vector>
using namespace std;

//TPoly::TPoly()
//{
//	TMember member = TMember();
//	this->push_back(member);
//}
//
//TPoly::TPoly(int coeff, int deg)
//{
//	TMember member = TMember(coeff, deg);
//	this->push_back(member);
//}
//
//TMember& TPoly::get_elem(int pos) {
//	return this->at(pos);
//}

namespace Polynomial
{
    class TPoly : private vector<TMember>
    {
    public:
        TPoly()
        {
            this->push_back(TMember());
        }

        TPoly(int coeff, int deg)
        {
            TMember member = TMember(coeff, deg);
            this->push_back(member);
        }


        TMember& get_elem(int pos) {
            try {
                TMember& res = this->at(pos);
                return res;
            }
            catch (exception e) {
                cout << "invalid position in get_elem()" << endl;
                TMember res = TMember(0,0);
                return res;
            }
        }

        int degree() {
            int max = this->begin()->get_degree();
            for (std::vector<TMember>::iterator it = this->begin(); it != this->end(); ++it) {
                if (max < it->get_degree())max = it->get_degree();
            }
            return max;
        }

        int coeff(int deg) {
            for (std::vector<TMember>::iterator it = this->begin(); it != this->end(); ++it) {
                if (it->get_degree() == deg)return it->get_coeff();
            }
            return 0;
        }

        void clear() {
            this->vector<TMember>::clear();
            this->push_back(TMember());
        }



        bool operator==(const TPoly& c1)
        {
            if (this->size() != c1.size()) return false;

            TPoly additional;
            additional.pop_back();
            for (int j = 0; j < c1.size(); j++) {

                additional.push_back(c1.at(j));
            }
            

            for (int j = 0; j < this->size(); j++) {
                if (this->get_elem(j) != additional.get_elem(j)) return false;
            }
            return true; 
        }

        bool operator!= (const TPoly& c1)
        {
            return !(*this == c1);
        }

        TPoly operator -() {
            TPoly tmp;
            return tmp - *this;
        }

        TPoly operator +(const TPoly& i) {
			TPoly res = TPoly();
			TPoly additional = TPoly();
            for (int j = 0; j < i.size(); j++) {
                additional.push_back(i.at(j));
            }

			for (std::vector<TMember>::iterator it = this->begin(); it != this->end(); ++it) {
				if (*it == TMember()) continue;
				TMember expected = TMember();
                for (std::vector<TMember>::iterator it2 = additional.begin(); it2 != additional.end(); ++it2) {
                    if (it2->get_degree() == it->get_degree()) {
                        expected = TMember(it2->get_coeff(), it2->get_degree());
                        additional.erase(it2);
                        break;
                    }
                }
				if (expected != TMember()) res.push_back(TMember(it->get_coeff() + expected.get_coeff(), it->get_degree()));
				else res.push_back(*it);
			}
            for (std::vector<TMember>::iterator it2 = additional.begin(); it2 != additional.end(); ++it2) {
                res.push_back(*it2);
            }

            res.clear_zeros();
            sort(res.begin(), res.end());
			return res;
		}

        TPoly operator -(const TPoly& i) {
            TPoly res = TPoly();
            TPoly additional = TPoly();
            for (int j = 0; j < i.size(); j++) {
                additional.push_back(i.at(j));
            }

            for (std::vector<TMember>::iterator it = this->begin(); it != this->end(); ++it) {
                if (*it == TMember()) continue;
                TMember expected = TMember();
                for (std::vector<TMember>::iterator it2 = additional.begin(); it2 != additional.end(); ++it2) {
                    if (it2->get_degree() == it->get_degree()) {
                        expected = TMember(it2->get_coeff(), it2->get_degree());
                        additional.erase(it2);
                        break;
                    }
                }
                if (expected != TMember()) res.push_back(TMember(it->get_coeff() - expected.get_coeff(), it->get_degree()));
                else res.push_back(*it);
            }
            for (std::vector<TMember>::iterator it2 = additional.begin(); it2 != additional.end(); ++it2) {
                TMember tmp = TMember(-it2->get_coeff(), it2->get_degree());
                res.push_back(tmp);
            }

            res.clear_zeros();
            sort(res.begin(), res.end());
            return res;
        }

        TPoly operator *(const TPoly& i) {
            TPoly res = TPoly();
            res.pop_back();
            TPoly additional = TPoly();
            additional.pop_back();
            for (int j = 0; j < i.size(); j++) {
                additional.push_back(i.at(j));
            }

            for (std::vector<TMember>::iterator it = this->begin(); it != this->end(); ++it) {
                for (std::vector<TMember>::iterator it2 = additional.begin(); it2 != additional.end(); ++it2) {
                    TMember tmp = TMember(it->get_coeff() * it2->get_coeff(), it->get_degree() + it2->get_degree());
                    res.push_back(tmp);
                }
            }
            res.normalize();
            sort(res.begin(), res.end());
            return res;

        }

        std::string to_string()
        {
            std::string res;
            if (this->size() == 1) {
                vector<TMember>::iterator it = this->begin();
                return it->to_string();
            }
            for (std::vector<TMember>::iterator it = this->begin(); it != this->end(); ++it) {
                if (it->get_coeff() >= 0 && it != this->begin()) res += "+" + it->to_string();
                else res += it->to_string();
            }
            return res;
        }


        TPoly diff() {
            TPoly res = TPoly();
            res.pop_back();
            for (std::vector<TMember>::iterator it = this->begin(); it != this->end(); ++it) {
                res.push_back(it->diff());
            }
            res.normalize();
            return res;
        }

        double calc(int x) {
            double res = 0;
            for (std::vector<TMember>::iterator it = this->begin(); it != this->end(); ++it) {
                res += it->calc(x);
            }
            return res;
        }


    private:
        void clear_zeros() {
            TPoly res;
            res.pop_back();
			bool flag = true;
			if (this->size() > 1) {
				for (std::vector<TMember>::iterator it = this->begin(); it != this->end(); ++it) {
					if (it->get_coeff() != 0) {
						res.push_back(TMember(it->get_coeff(), it->get_degree()));
					}
                }
                this->vector<TMember>::clear();
                if (res.size() == 0) this->push_back(TMember());
                else
					for (std::vector<TMember>::iterator it = res.begin(); it != res.end(); ++it) {
						this->push_back(*it);
					}
            }
        }

        void normalize() {
            TPoly res;
            res.pop_back();
            for (std::vector<TMember>::iterator it = this->begin(); it != this->end(); ++it) {
                for (std::vector<TMember>::iterator it2 = it+1; it2 != this->end(); ++it2) {
                    if (it->get_degree() == it2->get_degree()) {
                        it->set_coeff(it->get_coeff() + it2->get_coeff());
                        it2->set_coeff(0);
                    }       
                }
            }
            clear_zeros();
        }

	};
}
