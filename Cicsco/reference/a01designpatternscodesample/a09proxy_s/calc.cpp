#include <iostream>


using namespace std;

//To do pre and post processing anonymously



class LoanDetail
{
    public:
        double principal;
        int time;
        double rate;

        LoanDetail()
        {

        }
        LoanDetail(double principal, double rate, int time)
        {
            this->principal = principal;
            this->rate = rate;
            this->time = time;
        }
};

class Calculator
{
    public:
        virtual double interest(LoanDetail details) = 0;
};

class SimpleInterestCalculator: public Calculator
{
    public:
        SimpleInterestCalculator()
        {
        }
        double interest(LoanDetail details){
            return details.principal*details.rate*details.time/100;
        }
};

class ValidationProxy: public Calculator
{
    private:
        Calculator* target;
    public:
        ValidationProxy(Calculator* target)
        {
            this->target = target;
        }

        double interest(LoanDetail details){
            if(details.principal <= 0 || details.rate <= 0 || details.time <= 0) 
                throw "Invalid details";
            return target->interest(details);
        }
};

class LoggingProxy: public Calculator
{
    private:
        Calculator* target;
    public:
        LoggingProxy(Calculator* target)
        {
            this->target = target;
        }
        double interest(LoanDetail details){
            cout << "computing interest against Rs." << details.time << " at a rate of " << details.rate << "% for " << details.time << "months" << endl;
            double i =  target->interest(details);
            cout << "Returning " << i << endl;
            return i;
        }
};

class CalculatorFactory 
{
    public:
        static Calculator* getCalculator(bool validation){
            Calculator* calc = new SimpleInterestCalculator();
            if(validation == true)
            {
                return new ValidationProxy(calc);
            }else{
                return calc;
            }
        }
};

int main()
{
    try {
        LoanDetail details = LoanDetail(1000, 8, 12);
        Calculator* calc = CalculatorFactory::getCalculator(true);
        double interest = calc->interest(details);
        cout << "Interest against Rs." << details.time << " at a rate of " << details.rate << "% for " << details.time << "months is: Rs. " << interest << endl;
    }catch(char const* error){
        cout << error << endl;
    }
    return 0;
}