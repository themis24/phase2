#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#define MIN_ECTS 240
using namespace std;

class Course{
    private:
        string name;
        int ects_points;
        int mandatory;
    public:
        string Get_name(){
            return name;
        }
        int Get_ects(){
            return ects_points;
        }
        int Get_mandatory(){
            return mandatory;
        }
        void Set_name(const string& newname){
            name = newname;
        }
        void Set_ects(int x){
            ects_points = x;
        }
        void Set_mandatory(int x){
            mandatory = x;
        }
        Course(const string& n, int epo, int mand)
        :name(n), ects_points(epo), mandatory(mand){}
        Course(const Course& copied)
        : name(copied.name), ects_points(copied.ects_points), mandatory(copied.mandatory)
        {}
        ~Course(){}
};

class Person{
    private:                                                        //the characteristics that students and professors have in common
        string name;
        string uni_id;
        string password;
        static int count;
    public:                                                         //first constructor we use initialiaser list if were given veriables for the person
        virtual string Get_name(){
            return name;
        }
        virtual string Get_id(){
            return uni_id;
        }
        virtual string Get_password(){
            return password;
        }
        virtual void Set_name(const string& newname){
            name = newname;
        }
        virtual void Set_id(const string& newid){
            uni_id = newid;
        }
        virtual void Set_password(const string& newpass){
            password = newpass;
        }
        Person(const string& n, const string& id,const string& pass)
            : name(n), uni_id(id), password(pass){
            count++;                                                //we increase the sum by one
            //cout << "Created a new Person. In total: " << count << endl;
        }
        Person(const Person& copied)                                //copy constructor
        : name(copied.name), uni_id(copied.uni_id), password(copied.password){      //copy from the original from intialiser list
            count++;                                                //increase the sum
            //cout << "Created a new Person. In total: " << count << endl;
        }
        Person(){                                                   //constructor in case we are not given any variables and want to just get a blank person
            count++;
            //cout << "Created a new Person. In total: " << count << endl;
        }
        ~Person(){                                                  //destructor
            count--;                                                //decrease the sum
            //cout << "Deleted a Person. In total: " << count << endl;
        }
        friend istream& operator>>(istream& in, Person& person) {   //ovberload the in>> operator
            cout << "Enter Name: " << endl;                         //get inputs
            in >> person.name;                                      //put them in the respective variables
            cout << "Enter University ID: " << endl;
            in >> person.uni_id;
            cout << "Enter Password:" << endl;
            in >> person.password;
            return in;
        }
        friend ostream& operator<<(ostream& out, const Person& person){
            out << "Person's name: " << person.name << endl;    //overload the out<< operator and just print everything about a person
            out << person.name << "'s university identification number: sdi" << person.uni_id << endl;
            return out;
        }
};

class Student: public Person{
    private:
        vector<Course> Passed;
        vector<Course> current_semester;
        int ects;
        float average;
        int year;
    public:
        int Get_ects(){
            return ects;
        }
        float Get_average(){
            return average;
        }
        int Get_year(){
            return year;
        }
        void Set_ects(int x){
            ects = x;
        }
        void Set_average(float x){
            average = x;
        }
        void Set_year(int x){
            year = x;
        }
        Student(const Student& copied)
            : Person(copied), ects(copied.ects), average(copied.average), year(copied.year){}
        Student(const string& n, const string& id, const string& p)
        :Person(n, id, p){}
        Student(): year(0), average(0), ects(0){}
        ~Student(){

        }
};

class Professor: public Person{
    private:
        vector<Course> current_semester;
    public:

        Professor(const string& n, const string& id, const string& p)
        :Person(n, id, p){}
        Professor(){}
        Professor(const Professor& copied)
        :Person(copied), current_semester(copied.current_semester){}
        ~Professor(){

        }
};

class Semester{
    private:
        vector<Course> courses;
        Professor p;
    public:
        const Professor& Get_professor(){
            return p;
        }
        void Set_professor(const Professor& newprofessor) {
            p = newprofessor;
        }
        Semester(const vector<Course>& initialCourses)
        : courses(initialCourses){}
        vector<Course>& Get_courses(){
            return courses;
        }
        void Add_course(const Course& newCourse){
            courses.push_back(newCourse);
        }
        void Remove_course(const string& rmname){
            for (auto it = courses.begin(); it != courses.end();){      //go through the vector and find the course based on name
                if (it->Get_name() == rmname) {
                    it = courses.erase(it);  // erase returns the next valid iterator after the erased element
                } else {
                    ++it;
                }
            }
        }
        //were in semester[i] whiuch we know the course is in and call this 
        //semester[1].Move_course("Intro", semester[2]);
        void Move_course(const string& mname, Semester& msem){ //ask for the origin of the course when cout
            for(auto it = courses.begin(); it != courses.end(); ++it){
                if (it->Get_name() == mname){
                    msem.Add_course(*it);
                    courses.erase(it);
                    return;  // exit the function after the move
                }
                else{
                    // Handle invalid destination semester
                    cout << "Invalid destination semester.\n";
                    return;  // exit the function since no valid move is performed
                }
            }
        }
        ~Semester(){}
};

class Employee: public Person{
    public:  
        Employee(const string& n, const string& id, const string& p)
        :Person(n, id, p){}
        Employee(){}
        Employee(const Employee& copied)
        :Person(copied){}
        ~Employee(){

        }
};

class Secretary{
    private:                                                    //each secretary has a name and knows every person
        vector<Student*> students;
        vector<Professor*> professors;
        vector<Employee*> employees;
        vector<Semester*> semesters;
    public:
        int semesters_size(){
            return semesters.size();
        }
        int studs_size(){
            return students.size();
        }
        int professors_size(){
            return professors.size();
        }
        int employees_size(){
            return employees.size();
        }
        string get_n(){
            return n;
        }
        Student* Get_stud(int i){
            return students[i];
        }
        Professor* Get_prof(int i){
            return professors[i];
        }
        Employee* Get_empl(int i){
            return employees[i];
        }
        Secretary(){}
        ~Secretary(){
            for(int i = 0; i < employees.size(); i++){             //dont forget to delete every person inside the list
                delete employees[i];
            }
            for(int i = 0; i < students.size(); i++){             //dont forget to delete every person inside the list
                delete students[i];
            }
            for(int i = 0; i < professors.size(); i++){             //dont forget to delete every person inside the list
                delete professors[i];
            }
            //cout << "Destructed the secretary." << endl;
        }
        Secretary& Delete_stud(const string& id){
            for(auto it = students.begin(); it != students.end(); ++it){
                Student *temp = *it;
                string c = temp->Get_id();
                if(id == c){                  //if the ids match you found them
                    delete temp; // Delete the student object
                    students.erase(it); // Erase the element from the vector
                    return *this;
                }
            }
            cout<<"The student you want to delete doesnt exist."<<endl;
            return *this;
        }
        Secretary& Delete_prof(const string& id){
            for(auto it = professors.begin(); it != professors.end(); ++it){
                Professor *temp = *it;
                string c = temp->Get_id();
                if(id == c){                  //if the ids match you found them
                    delete temp; // Delete the student object
                    professors.erase(it); // Erase the element from the vector
                    return *this;
                }
            }
            cout<<"The student you want to delete doesnt exist."<<endl;
            return *this;
        }
        Secretary& operator+(Employee& newem){                    //overload the += operator to add a person with dynamic memory allocation (2.2)
            Employee* temp = new Employee(newem);                               //make a temp of the values you need and got via the main or function call
            employees.push_back(temp);                            //put the person inside the vector
            cout<<employees.size()<<endl;
            return *this;
        }
        Secretary& operator+(Student& stud){                    //overload the += operator to add a person with dynamic memory allocation (2.2)
            Student* temp = new Student(stud);                               //make a temp of the values you need and got via the main or function call
            students.push_back(temp);                            //put the person inside the vector
            //cout<<"stud:"<<students.size()<<endl;
            return *this;
        }
        Secretary& operator+(Professor& prof){                    //overload the += operator to add a person with dynamic memory allocation (2.2)
            Professor* temp = new Professor(prof);                               //make a temp of the values you need and got via the main or function call
            professors.push_back(temp);                            //put the person inside the vector
            //cout<<"prof:"<<professors.size()<<endl;
            return *this;
        }
        bool search(Student target){                             //search for any person based on their university id (2.4)
            for(int i = 0; i < students.size(); i++){
                if(target.Get_id() == students[i]->Get_id()){     //if the ids match you found them
                    return true;
                }
            }
            return false;                                       //if they dont then you didnt
        }
        Employee* search_id_employee(const string& id){              //search for any person based on their university id but with only their sdi as input
            for(int i = 0; i < employees.size(); i++){             //instead of working with strings i just
                Employee *temp = employees[i];
                string c = employees[i]->Get_id();
                if(c == id){                  //if the ids match you found them
                    return temp;
                }
            }
            return nullptr;
        }
        Professor* search_id_prof(const string& id){
            for(int i = 0; i < professors.size(); i++){
                Professor *temp = professors[i];
                string c = temp->Get_id();
                //cout << "Comparing: " << c << " with " << username << endl;
                if(c == id){
                    return temp;
                }
            }
            return nullptr;
        }
        Student* search_id_stud(const string& id){              //search for any person based on their university id but with only their sdi as input
            for(int i = 0; i < students.size(); i++){             //instead of working with strings i just
                Student *temp = students[i];
                string c = temp->Get_id();
                if(id == c){                  //if the ids match you found them
                    return temp;                //return the object
                }
            }
            return nullptr;                 //if not then return null pointer
        }                                                    //overload the in>> operator and take a name from keyboard and insert it into the secretary
        /*friend istream& operator>>(istream& in, Secretary& sec){
            cout<<"Give name."<<endl;                           //(2.3.a)
            string n;
            in>>n;
            cout<<"Give id."<<endl;
            string i;
            in>>i;
            cout<<"Give password."<<endl;
            string p;
            in>>p;
            Employee* ne = new Employee(n,i,p);
            employees.push_back(ne);
            return in;
        }                                                       //overload the out<< operator and print every person in the list of the secretary
        friend ostream& operator<<(ostream& out, const Secretary& Sec, int i){
            out<<employees[i].Get_name<<endl;                                //(2.3.b)
            for(int i = 0; i < employees.size(); i++){
                out<<*(Sec.people[i]);
            }
            return out;
        }*/
};

int Person::count = 0;                                      //initialise the count



int main(){
    static Secretary secretary;

    //5.1
    cout<<"Number of professors: "<<secretary.professors_size()<<endl;         //prove professors is empty
    string nameprof = "Eleni";
    string idprof = "sdi1";
    string passprof = "ilikebike";
    Professor eleni(nameprof, idprof, passprof);
    secretary = secretary + eleni;                 
    cout<<"Number of professors: "<<secretary.professors_size()<<endl;         //prove its added
    Professor* tprof;
    tprof = secretary.Get_prof(0);
    string tnameprof = tprof->Get_name();           //prove we can add a professor
    cout<<tnameprof<<endl;
    Professor* searchprof = secretary.search_id_prof(idprof);
    cout<<searchprof->Get_id()<<endl;       //prove we can search for the student inside the vector
    string newnaprof = "Helen";
    searchprof->Set_name(newnaprof);
    cout<<searchprof->Get_name()<<endl;
    secretary.Delete_prof(idprof);              //prove i can delete a student given his uni id
    cout<<"Number of professors: "<<secretary.professors_size()<<endl;


    //5.2
    cout<<"Number of students: "<<secretary.studs_size()<<endl;         //prove students is empty
    string nstud = "Themistoklis";
    string idstud = "sdi2000071";
    string passstud = "ilikecar";
    Student me(nstud, idstud, passstud);
    secretary = secretary + me;                 
    cout<<"Number of students: "<<secretary.studs_size()<<endl;         //prove its added
    Student* tstud;
    tstud = secretary.Get_stud(0);
    string tnamestud = tstud->Get_name();           //prove we can add a student
    cout<<tnamestud<<endl;
    Student* searchstud = secretary.search_id_stud(idstud);
    cout<<searchstud->Get_id()<<endl;       //prove we can search for the student inside the vector
    string newnastud = "Themis";
    searchstud->Set_name(newnastud);
    cout<<searchstud->Get_name()<<endl;
    secretary.Delete_stud(idstud);              //prove i can delete a student given his uni id
    cout<<"Number of students: "<<secretary.studs_size()<<endl;
    return 0;
}