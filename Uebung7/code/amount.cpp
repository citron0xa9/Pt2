#include <string>
#include <iostream>
#include <cassert>
#include <cmath>

enum currency {EUR=0,USD=1};

class Amount {
	//ToDo 7.2
	//Implement class Amount 
public:

	std::string description_;

	Amount(double netto, /*long brutto,*/ float tax, currency cur, std::string description);
	//Amount(long netto, /*long brutto,*/ float tax, currency cur);
	//~Amount();

//***********************************
//  Tax in full percent: 19%, 22%, etc.
	void setTax(float tax);
	float getTax(void);
//***********************************
	currency getCurrency(void);
	void toEUR(void);
	void toUSD(void);
//***********************************
	float getChange(void);
//***********************************
	void setNetto(double netto);
	double getNetto(void);
//***********************************
	void setBrutto(double brutto);
	double getBrutto(void);
//***********************************
	std::string getSymbol(void);
//***********************************
	void outputAmount(void);

private:
	float change_ = 0.8963;
	double netto_;
	double brutto_;
	float tax_;
	currency currency_;
};

Amount::Amount(double netto, /*long brutto,*/ float tax, currency cur = EUR, std::string description = ""):
	netto_{ netto },
	//brutto_{ brutto },
	tax_{ tax },
	currency_{ cur },
	description_{ description }{
		setTax(tax);
		brutto_ = netto_*tax_;
}

void Amount::setTax(float tax){
	tax_= tax/100 + 1;
	brutto_ = netto_*tax_;
}

float Amount::getTax(void){
	return (tax_-1)*100;
}

currency Amount::getCurrency(void){
	return currency_;
}

float Amount::getChange(void){
	return change_;
}

void Amount::toEUR(void){
	if (Amount::getCurrency() == EUR) return;
	netto_ /= Amount::getChange();
	brutto_ /= Amount::getChange();
	currency_ = EUR;
}

void Amount::toUSD(void){
	if (Amount::getCurrency() == USD) return;
	netto_ *= Amount::getChange();
	brutto_ *= Amount::getChange();
	currency_ = USD;
}

void Amount::setNetto(double netto){
	netto_ = netto;
	brutto_ = netto*tax_;
}

double Amount::getNetto(void){
	return netto_;
}

void Amount::setBrutto(double brutto){
	brutto_ = brutto;
	netto_ = brutto_/tax_;
}

double Amount::getBrutto(void){
	return brutto_;
}

std::string Amount::getSymbol(void){
	if(Amount::getCurrency() == EUR) return " EURO";
	return " USD";
}

void Amount::outputAmount(void){
	std::cout <<"Netto: "<<getNetto()<<getSymbol()<<" Tax: "<<getTax()<<"% Brutto: "<<getBrutto()<<getSymbol()<<" " << description_<<std::endl;
}

inline bool isApprox(const double val1, const double val2, double epsilon)
{
	return ((val1-epsilon)<val2<(val1+epsilon));
}

void test() {
	//ToDo 7.2
	//implement tests
	Amount test(20,10,EUR);

	assert(test.getCurrency() == EUR);
	assert(test.getNetto() == 20.0);
	assert(round(test.getBrutto()) == 22);	//round because otherwise assertion would fail because its not completely equal 22.000000000

	test.outputAmount();
	test.setTax(5);

	assert(round(test.getBrutto()) == 21);

	test.outputAmount();
	test.toUSD();

	assert(test.getCurrency() == USD);
	assert(test.getNetto() == (20.0*test.getChange()));
	assert(isApprox(test.getBrutto(), (21.0*test.getChange()), 0.001));	//make approximation comparison because of precision problems (test.getBrutto isnt 100% equal 21.0000000)

	test.outputAmount();	

	std::cout << std::endl << "Successfully finished test" << std::endl;
}

int main() {
	test();
    return 0;
}
