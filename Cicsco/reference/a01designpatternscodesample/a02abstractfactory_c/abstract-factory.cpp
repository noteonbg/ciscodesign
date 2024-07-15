#include <iostream>

//To separate the responsbility of object creation from it's user

using namespace std;

class Question 
{
    public:
        string description;
        string a;
        string b;
        string c;
        string answer;
};

class Quiz 
{
    public:
        virtual Question fetch() = 0;
};

class QuizFactory
{
    public:
        virtual Quiz* getQuiz() = 0;
};

class DemoQuiz : public Quiz
{
    public:
        Question fetch() 
        {
            Question q = Question();
            q.description = "Demo Question: Capital of India?";
            q.a = "Kolkota";
            q.b = "New Delhi";
            q.c = "Mumbai";
            q.answer = "B";
            return q;
        }
};

class DemoQuizFactory : public QuizFactory
{
    public: 
        Quiz* getQuiz() 
        {
            return new DemoQuiz();
        }
};

class MockQuiz : public Quiz
{
    public:
        Question fetch() 
        {
            Question q = Question();
            q.description = "Mock Question: 1+2?";
            q.a = "1";
            q.b = "2";
            q.c = "3";
            q.answer = "C";
            return q;
        }
};

class MockQuizFactory : public QuizFactory
{
    public: 
        Quiz* getQuiz() 
        {
            return new MockQuiz();
        }
};

class AbstractQuizFactory
{
    public:
        static QuizFactory* getFactory(string name)
        {
            if(name == "demo")
                return new DemoQuizFactory();
            if(name == "mock")
                return new MockQuizFactory();
            throw "Not Found";
        }
};

class QuizApp
{
    public: 
        void main()
        {
            string option;
            QuizFactory* factory = AbstractQuizFactory::getFactory("demo");
            Quiz* quiz = factory->getQuiz();
            Question question = quiz->fetch();
            cout << question.description << endl;
            cout << "A. " << question.a << endl;
            cout << "B. " << question.b << endl;
            cout << "C. " << question.c << endl;
            cout << "Answer: ";
            cin >> option;
            if(option == question.answer)
                cout << "Correct :-)" <<endl;
            else
                cout << "Incorrect :-(" <<endl;
        }
};

int main() {
    QuizApp().main();
    return 0;
};