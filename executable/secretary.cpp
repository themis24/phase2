#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

int valid_id(string id){
    if (id.length() != 10){                                     // Check the length
        cout << "Error: University ID is too long." << endl;
        return 0;                                               //return as non valid
    }
    if (id.substr(0, 3) != "sdi"){                              //check if the first 3 characters are sdi with substring func from 0 to 3
        cout << "Error: University ID must start with 'sdi'." << endl;
        return 0;                                               //return as non valid
    }
    string numeric_part = id.substr(3);                         //extract the numbers from the string excluding sdi
    for (char c : numeric_part){                        //we use a char c and go through the entire string of supposed numbers
        if (!(c == '0' || c == '1' || c == '2' ||c == '3' ||
            c == '4' || c == '5' || c == '6' || 
            c == '7' || c == '8' || c == '9')){
            return 0;                                           //return as non valid
        }
    }
    int numbers_of_id = stoi(numeric_part);                     //convert the numeric part to an integer
    return numbers_of_id;
}

class Person{
private:                                                        //the characteristics that students and professors have in common
    string name;
    int age;
    long long int tel_num;
    string email;
    long long int uni_id;
    static int count;
    string occupation;

public:                                                         //first constructor we use initialiaser list if were given veriables for the person
    Person(const string& n, int years, long int num, const string& mail, long int id, string oc)
        : name(n), age(years), tel_num(num), email(mail), uni_id(id), occupation(oc){
        count++;                                                //we increase the sum by one
        cout << "Created a new Person. In total: " << count << endl;
    }
    Person(const Person& copied)                                //copy constructor
    : name(copied.name), age(copied.age), tel_num(copied.tel_num), email(copied.email),
     uni_id(copied.uni_id), occupation(copied.occupation){      //copy from the original from intialiser list
        count++;                                                //increase the sum
        cout << "Created a new Person. In total: " << count << endl;
    }
    Person(){                                                   //constructor in case we are not given any variables and want to just get a blank person
        count++;
        cout << "Created a new Person. In total: " << count << endl;
    }
    ~Person(){                                                  //destructor
        count--;                                                //decrease the sum
        cout << "Deleted a Person. In total: " << count << endl;
    }
    int const Get_id(){                                         //getter function for uni id
        return this->uni_id;
    }
    friend istream& operator>>(istream& in, Person& person) {   //ovberload the in>> operator
        cout << "Enter name: " << endl;                         //get inputs
        in >> person.name;                                      //put them in the respective variables
        cout << "Enter age: " << endl;
        in >> person.age;
        cout << "Enter telephone number: " << endl;
        in >> person.tel_num;
        cout << "Enter e-mail: " << endl;
        in >> person.email;
        cout << "Enter university identification number: " << endl;
        in >> person.uni_id;
        cout << "Enter occupation" << endl;
        in >> person.occupation;
        return in;
    }
    friend ostream& operator<<(ostream& out, const Person& person){
        out << "Person's name: " << person.name << endl;    //overload the out<< operator and just print everything about a person
        out << person.name << "'s age: " << person.age << endl;
        out << person.name << "'s telephone number: " << person.tel_num << endl;
        out << person.name << "'s e-mail: " << person.email << endl;
        out << person.name << "'s university identification number: sdi" << person.uni_id << endl;
        out << person.name <<"'s occupation: " << person.occupation << endl;
        return out;
    }
};

int Person::count = 0;                                      //initialise the count

class Secretary{
private:                                                    //each secretary has a name and knows every person
    vector<Person*> people;                                 //we load the data into a vector of pointer person
    string name;
public:
    Secretary(string n):name(n){                            //constructor and destructor (2.1)
        cout << "Constructed the secretary." << endl;
    }
    ~Secretary(){
        for(int i = 0; i < people.size(); i++){             //dont forget to delete every person inside the vector
            delete people[i];
        }
        cout << "Destructed the secretary." << endl;
    }
    Secretary& operator+(Person person){                    //overload the += operator to add a person with dynamic memory allocation (2.2)
        Person* temp = new Person(person);                  //make a temp of the values you need and got via the main or function call
        people.push_back(temp);                             //put the temp inside the vector
        return *this;
    }
    bool search(Person target){                             //search for any person based on their university id (2.4)
        for(int i = 0; i < people.size(); i++){
            if(target.Get_id() == people[i]->Get_id()){     //if the ids match you found them
                return true;
            }
        }
        return false;                                       //if they dont then you didnt
    }
    int search_id(int id){                                  //search for any person based on their university id but with only their sdi as input
        for(int i = 0; i < people.size(); i++){             //instead of working with strings i just
            if(id == people[i]->Get_id()){                  //if the ids match you found them
                return i;
            }
        }
        return 0;
    }                                                       //overload the in>> operator and take a name from keyboard and insert it into the secretary
    friend istream& operator>>(istream& in, Secretary& sec){
        cout<<"Give name."<<endl;                           //(2.3.a)
        in>>sec.name;
        return in;
    }                                                       //overload the out<< operator and print every person in the vector of the secretary
    friend ostream& operator<<(ostream& out, const Secretary& Sec){
        out<<Sec.name<<"\n";                                //(2.3.b)
        for(int i = 0; i < Sec.people.size(); i++){
            out<<*(Sec.people[i]);
        }
        return out;
    }
    Secretary(const Secretary& copied)                      //copy constructor (2.5)
    : name(copied.name)
    {
        for (int i = 0; i < copied.people.size(); i++){     //deep copy
            Person* temp = new Person(*(copied.people[i])); //copy every person from the original vector to the new one
            people.push_back(temp);
        }
        cout << "Created a copied Secretary."<< endl;
    }
};
/*
class Student: public Person{
private:
    int year;
    int average;
    string password;
    int points;
public:
    int Get_year(){
        return year;
    }
    float Get_average(){
        return average;
    }
    string Get_password(){
        return password;
    }
    int Get_points(){
        return points;
    }
    void Set_year(int x){
        year = x;
    }
    void Set_average(float x){
        average = x;
    }
    void Set_password(const string& newpass){
        password = newpass;
    }
    void Set_points(int x){
        points = x;
    }
    //dont forget to write an instruction thing for this cause its long
    Student(const string& n, int years, long int num, const string& mail, long int id, string oc,
            int studentYear, int studentAverage, const string& studentPassword, int studentPoints)
        : Person(n, years, num, mail, id, oc),                                      //call base class constructor
          year(studentYear), average(studentAverage), password(studentPassword), points(studentPoints) {
        cout << "Created a new Student." << endl;
    }
    Student() : year(0), average(0), points(0) {
        cout << "Created a new Student" << endl;
    }
    ~Student(){
        cout<< "Deleted student" << endl;
    }
};
*/
class Professor: public Person{
private:
    int years_active;
    string password;
public:
    int Get_years(){
        return years_active;
    }
    string Get_password(){
        return password;
    }
    void Set_years(int x){
        if(x >= 0){
            years_active = x;
        }
        else{
            cout << "Cant have less than 0 years of being active." << endl;
        }
    }

    Professor(const string& n, int years, long int num, const string& mail, long int id, string oc,
            int profYear, const string& newpass)
        : Person(n, years, num, mail, id, oc),                                      //call base class constructor
          years_active(profYear), password(newpass){
        cout << "Created a new Professor." << endl;
    }
    Professor(const Professor& copied)
        : Person(copied), years_active(copied.years_active), password(copied.password) {
        cout << "Created a new Professor by copying." << endl;
    }
    Professor(){
        cout << "Created a new Professor." << endl;
    }
    ~Professor(){
        cout << "Deleted a Professor." << endl;
    }
};

class Course{
private:
    int ects_points;
    string name;
    int prof_id;
    int mandatory;
public:
    int Get_ects(){
        return ects_points;
    }
    string Get_name(){
        return name;
    }
    int Get_mandatory(){
        return mandatory;
    }
    int Get_Professor_id(){
        return prof;
    }
    void Set_ects(int x){
        ects_points = x;
    }
    void Set_name(const string& n){
        name = n;
    }
    void Set_mandatory(int a){
        if(a == 0 || a == 1){
            mandatory = a;
        }
        else{
            cout << "Wrong input. Use 1 for mandatory, 0 for non mandatory." << endl;
        }
    }
    void Set_Professor(const Professor& new_professor){
        prof = new_professor;                               //uses the copy constructor of Professor
    }
    Course(int p, string n, Professor pr, int m):ects_points(p), name(n), prof(pr), mandatory(m){
        cout << "New course." << endl;
    }
    Course(){
        cout << "New course." << endl;
    }
    ~Course(){}
};


/*void stud(){
    string input;    
    cout << "Please provide your University ID." << endl;
    cin >> input;
    int id = valid_id(input);
    if(id == 0){
        cout << "You have entered a non valid University. Proper syntax is:\nsdi1234567 (sdi followed by 7 numbers)" << endl;
        return;
    }
    Secretary secretary("temp");
    int stud_number =secretary.search_id(id);
    if(stud_number == 0){
        cout << "The University ID you have entered doesnt exist." << endl;
    }

}*/

int main(){
    vector<Course> semester[2];                             //just to be simpler im gonna initialise the semesters with only 2 courses in each
    Course Intro;
    semester[0].push_back(Intro);
    Course Discrete_Math;
    semester[0].push_back(Discrete_Math);
    Course Data_Structs;
    semester[1].push_back(Data_Structs);
    Course PC_Architecture;
    semester[1].push_back(PC_Architecture);
    /*Person person1("John Doe", 30, 1234567890, "john.doe@example.com", 9876543210, "Student");
    cout << person1;

    Person person2;
    cout << "Enter details for a new person:" << endl;
    cin >> person2;

    cout << "Details of person2:" << endl;                  //prove Person works
    cout << person2;

    Secretary secretary("Bob");                             //prove its constructed
    secretary = secretary + person1;                        //prove a person can be added


    cout << "Details of the secretary:" << endl;
    cout << secretary;                                      //prove that out<< overloading works
    if(secretary.search(person1)){                          //prove that i can find something inside the vector 
        cout<<"Found"<<endl;
    }
    Secretary copy(secretary);                              //prove i can copy
    cout << secretary;                                      //prove its the same
    cout << "\n\nMyStudy Menu:\nPress 1 if Student, 2 if Professor, 3 if Secretary." << endl;
    int path;
    cin >> path;
    if(path == 1){  //use exception here and on the others
        stud();
        return 0;
    }
    /*else if(path == 2){

    }
    else if(path == 3){

    }
    else{
        cout << "Wrong input." << endl;
        return 1;
    }*/
    return 0;
}