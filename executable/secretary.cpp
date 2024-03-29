#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#define MIN_ECTS 20
using namespace std;

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

class Course;

class Professor: public Person{
    private:
        Course* current;
        int sem;
    public:
        void Remove_course(){
            current = nullptr;
        }
        void Set_sem(int x){
            sem = x;
        }
        int Get_sem(){
            return sem;
        }
        void Set_course(const Course& newCourse);
        Course* Get_course(){
            if(current != nullptr){
                return current;
            }
            else{return nullptr;}
        }
        Professor(const string& n, const string& id, const string& p)
        :Person(n, id, p){current = nullptr;}
        Professor(const string& n, const string& id, const string& p, int x)
        :Person(n, id, p), sem(x) {current = nullptr;}
        Professor(){current = nullptr;}
        Professor(const Professor& copied)
        :Person(copied), sem(copied.sem){
            if(copied.current){
                current = copied.current;
            }
        }
        ~Professor(){

        }
};

class Course{
    private:
        Professor p;
        string name;
        int ects_points;
        int mandatory;
    public:
        void Set_professor(const Professor& newprofessor) {
            p = newprofessor;
        }
        Professor& Get_professor(){
            return p;
        }
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
        Course(){}
        Course(const string& n, int epo, int mand)
        :name(n), ects_points(epo), mandatory(mand){}
        Course( Professor& s,const string& n, int epo, int mand)
        :p(s),name(n), ects_points(epo), mandatory(mand){}
        Course(const Course& copied)
        :p(copied.p) ,name(copied.name), ects_points(copied.ects_points), mandatory(copied.mandatory)
        {}
        ~Course(){}
};

void Professor::Set_course(const Course& newCourse){
    current = new Course(newCourse);
}

class Student: public Person{
    private:
        vector<Course*> Passed;
        vector<int> Passed_grade;
        vector<Course*> current_semester;
        int ects;
        float average;
        int year;
    public:
        void show_grades(){     //5.8
            for(int i = 0; i < Passed.size(); ++i){
                cout<<Passed[i]->Get_name()<< " with grade: "<< Passed_grade[i] << endl;
            }
        }
        //for simplicity were going to make it mandatory to pass only 4 courses
        void graduates(){
            int totalects;
            for(int i = 0; i < Passed.size(); ++i){
                if(Passed[i]->Get_mandatory() == 1){
                    totalects = totalects + Passed[i]->Get_ects();
                }
            }
            if(totalects = MIN_ECTS){
                cout << Get_name() << endl;
            }
        }
        void check_passed_stud(const string& mname, int base){ //ask for the origin of the course when cout
            for(int i = 0; i < Passed.size(); ++i){
                string c = Passed[i]->Get_name();
                if (c == mname){
                    cout<<Get_name() <<" passed the course."<<endl;
                    return;  // exit the function after the move
                }
            }
            return;
        }
        void stud_add_course(const Course& newCourse){
            Course* temp = new Course(newCourse);
            current_semester.push_back(temp);
        }
        void stud_add_passed(const Course& newCourse, int x){
            Course* temp = new Course(newCourse);
            Passed.push_back(temp);
            Passed_grade.push_back(x);
        }
        void print_grades(){                //5.8
            cout << "Grades for courses passed by " << Get_name() << endl;
            for(int i = 0; i < Passed.size(); ++i) {
                cout << "Course: " << Passed[i]->Get_name() << ", Grade: " << Passed_grade[i] << endl;
            }
        }
        int Get_coursesize(){
            return current_semester.size();
        }
        vector<Course*> Get_courses(){
            return current_semester;
        }
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
        Student(const string& n, const string& id, const string& p, int poects, float stuaver, int stuyear)
        :Person(n, id, p), ects(poects), average(stuaver), year(stuyear){}
        Student(const Student& copied)
            : Person(copied), ects(copied.ects), average(copied.average), year(copied.year){}
        Student(const string& n, const string& id, const string& p)
        :Person(n, id, p){}
        Student(): year(0), average(0), ects(0){}
        ~Student(){

        }
};

class Semester{
    private:
        vector<Course*> courses;
    public:
        int size_course(){
            return courses.size();
        }
        Course* search_name_course(const string& name){
            for(int i = 0; i < courses.size(); i++){
                Course *temp = courses[i];
                string c = temp->Get_name();
                if(c == name){
                    return temp;
                }
            }
            throw out_of_range("Course not found");//error if i dont have this
        }
        /*Semester(const vector<Course>& initialCourses)
        : courses(initialCourses){}*/
        vector<Course*>* Get_courses(){
            return &courses;
        }
        
        Semester(){}
        void Add_course( Course& newCourse){
            Course* temp = new Course(newCourse);
            courses.push_back(temp);
                cout << "Course added to the semester: " << newCourse.Get_name() << endl;
                cout << "Number of courses in the semester after adding: " << courses.size() << endl;

            return;
        }
        void Remove_course(const string& rmname){
            for(int i = 0; i < courses.size(); ++i){
                string c = courses[i]->Get_name();
                if(rmname == c){
                    delete courses[i];
                    courses.erase(courses.begin() + i);
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
        void print_graduates(){
            for(int i = 0 ;i < students.size(); i++ ){
                students[i]->graduates();
            }
        }
        //were in semester[i] whiuch we know the course is in and call this 
        //semester[1].Move_course("Intro", semester[2]);
        void Move_course(const string& mname, int base, int dest){ //ask for the origin of the course when cout
            vector<Course*>* basesem = semesters[base - 1]->Get_courses();
            Semester* destination = semesters[dest - 1];
            for(int i = 0; i < basesem->size(); ++i){
                string c = (*basesem)[i]->Get_name();
                if (c == mname){
                    destination->Add_course(*((*basesem)[i]));
                    delete (*basesem)[i];
                    basesem->erase(basesem->begin() + i);
                    return;  // exit the function after the move
                }
                else{
                    // Handle invalid destination semester
                    cout << "Invalid destination semester.\n";
                    return;  // exit the function since no valid move is performed
                }
            }
        }
        void check_passed_sec(const string& mname, int base){ //ask for the origin of the course when cout
            for(int i = 0 ;i < students.size(); i++ ){
                students[i]->check_passed_stud(mname, base);
            }
        }
        void remove_course_sec(const string& mname, int base){ //ask for the origin of the course when cout
            vector<Course*>* basesem = semesters[base - 1]->Get_courses();
            for(int i = 0; i < basesem->size(); ++i){
                string c = (*basesem)[i]->Get_name();
                if (c == mname){
                    delete (*basesem)[i];
                    basesem->erase(basesem->begin() + i);
                    return;  // exit the function after the move
                }
                else{
                    // Handle invalid destination semester
                    cout << "Invalid base semester or name.\n";
                    return;  // exit the function since no valid move is performed
                }
            }
        }
        Semester* Get_semester(int i){
            return semesters[i-1];      //cause its the first but it is in pos 0 in vec
        }
        int sem_size(){
            int total_courses = 0;
            for (const auto& semester : semesters) {
                total_courses += semester->size_course();
            }
            return total_courses;
        }
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
        Student* Get_stud(int i){
            return students[i];
        }
        Professor* Get_prof(int i){
            return professors[i];
        }
        Employee* Get_empl(int i){
            return employees[i];
        }
        Semester* Get_sem(int i){
            return semesters[i];
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
            for(int i = 0; i < semesters.size(); i++){             //dont forget to delete every person inside the list
                delete semesters[i];
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
        Secretary& Delete_course(const string& name){
            for (auto it1 = semesters.begin(); it1 != semesters.end(); ++it1){
                Semester* tsem = *it1;
                for (auto it2 = tsem->Get_courses()->begin(); it2 != tsem->Get_courses()->end(); ++it2) {
                    Course* temp = (*it2);
                    string c = temp->Get_name();
                    if (name == c) { // if the names match, you found the course
                        it2 = tsem->Get_courses()->erase(it2); // Erase the element from the vector
                        delete temp; // Delete the course object
                        return *this;
                    }
                }
            }
            cout<<"The course you want to delete doesnt exist."<<endl;
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
            cout<<"The professor you want to delete doesnt exist."<<endl;
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
        Secretary& operator+(Semester& s){                    //overload the += operator to add a person with dynamic memory allocation (2.2)
            Semester* temp = new Semester(s);                               //make a temp of the values you need and got via the main or function call
            semesters.push_back(temp);                            //put the person inside the vector
            //cout<<"prof:"<<professors.size()<<endl;
            return *this;
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
                //cout << "Comparing: " << c << " with " << id << endl;
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

void stud(Secretary &secretary){
    string input;    
    cout << "Please provide your University ID." << endl;
    cin >> input;
    Student* s;
    s = secretary.search_id_stud(input);   //search for the student id and if it exists we have the data already in here
    if(!s){
        cout << "The University ID you have entered doesnt exist." << endl;
        return;
    }
    if(s->Get_id() == input){
        cout << "ID found." << endl;
    }
    cout << "Enter password." << endl;
    string pass;
    cin >> pass;
    cout << endl;
    if(pass == s->Get_password()){
        cout << "Login successful." << endl<<endl;
        cout << "Press 1 to show total average."<<endl<<"Press 2 to show your ECTS points."<<endl<<"Press 3 to sign up for a course."<<endl<<"Press 4 to change password."<<endl<<"Press 5 to see grades for the passed courses."<<endl<<"Press 6 to logout." << endl<<endl;
        int choice;
        cin >> choice;
        while(choice != 6){
            if(choice == 1){
                float av = s->Get_average();
                cout << "Your average is: " << av <<endl<<endl;
            }
            else if(choice == 2){
                int epoints = s->Get_ects();
                cout << "Your ECTS points are: "<< epoints << endl<<endl;
            }
            else if(choice == 3){
                cout<<"Enter the semester you want to choose:"<<endl;
                int sc5;
                cin>> sc5;
                if(sc5/2 <= s->Get_year()){
                    Semester* checksem = secretary.Get_semester(sc5);
                    cout << "Enter the course you want to choose: " << endl;
                    string choicec5;
                    cin >> ws;  //skip whitespaces
                    getline(cin, choicec5);       
                    cout << "Entered course name: " << choicec5 << endl;
                    try{
                        Course* modify = checksem->search_name_course(choicec5);
                        cout << "Found course: " << modify->Get_name() << endl;
                        s->stud_add_course(*modify);
                        vector<Course*> markcour = s->Get_courses();
                        int i = s->Get_coursesize();
                        i--;//cause vector positions are one pos minus
                        string enrolled =  markcour[i]->Get_name();
                        cout<<"You have been enrolled to: " <<enrolled <<endl<<endl;
                    }
                    catch(const out_of_range& ex){
                        cout << "Error: could not find the course" << endl<<endl;
                    }
                }
            }
            else if(choice == 4){
                string newp;
                cout << endl << "Type your new password." << endl;
                cin >> newp;
                cout<<"Confirm the password reset by typing 1"<<endl;
                int con;
                cin >> con;
                if(con == 1){
                    s->Set_password(newp);
                    cout<<"Password changed successfully."<<endl<<endl;
                }
            }
            else if(choice == 5){
                s->show_grades();
            }
            cout << "Press 1 to show total average."<<endl<<"Press 2 to show your ECTS points."<<endl<<"Press 3 to sign up for a course."<<endl<<"Press 4 to change password."<<endl<<"Press 5 to see grades for passed classes."<<endl<<"Press 6 to logout." << endl<<endl;
            cin >> choice;
            if(choice != 1 & choice != 2 & choice != 3 & choice != 4 & choice != 5 ){
                break;
            }
        }
    }
    else{
        cout << "Wrong password. Try again" << endl;
    }
}

void teach(Secretary &secretary){
    string input;    
    cout << "Please provide your University ID." << endl;
    cin >> input;
    Professor* s;
    s = secretary.search_id_prof(input);   //search for the student id and if it exists we have the data already in here
    if(s == nullptr){
        cout << "The University ID you have entered doesnt exist." << endl;
        return;
    }
    if(input == s->Get_name()){
        cout << "ID found." << endl;
    }
    cout << "Enter password." << endl;
    string pass;
    cin >> pass;
    cout << endl;
    if(pass == s->Get_password()){
        cout << "Login successful." << endl<<endl;
        cout << "Press 1 to show semester statistics."<<endl<<"Press 2 to change password."<<endl<<"Press 3 to logout." << endl<<endl;
        int choice;
        cin >> choice;
        while(choice != 3){
            if(choice == 1){
                
            }
            else if(choice == 2){
                string newp;
                cout << endl << "Type your new password." << endl;
                cin >> newp;
                cout<<"Confirm the password reset by typing 1"<<endl;
                int con;
                cin >> con;
                if(con == 1){
                    s->Set_password(newp);
                    cout<<"Password changed successfully."<<endl<<endl;
                }
            }
            cout << "Press 1 to show semester statistics."<<endl<<"Press 2 to change password."<<endl<<"Press 3 to logout." << endl<<endl;
            cin >> choice;
        }

    }
}

void employee(Secretary& secretary){
   string input;    
    cout << "Please provide your University ID." << endl;
    cin >> input;
    Employee* s;
    s = secretary.search_id_employee(input);   //search for the employee id and if it exists we have the data already in here
    if(!s){
        cout << "The University ID you have entered doesnt exist." << endl;
        return;
    }
    if(s->Get_id() == input){
        cout << "ID found." << endl;
    }
    cout << "Enter password." << endl;
    string pass;
    cin >> pass;
    cout << endl;
    if(pass == s->Get_password()){
        cout<<"Press 1 if you want to edit professor related data." << endl << "Press 2 if you want to edit student related data." << endl << "Press 3 if you want to edit semester data." << endl << "Press 4 if you want to print everyone who can graduate." << endl << "Press 5 to logout." << endl;
        int choice;
        cin >> choice;
        while(choice != 5){    
            if(choice == 4){
                secretary.print_graduates();
            }  
            if(choice == 1){
                cout << "Press 1 if you want to add a professor, 2 if you want to edit one, 3 if you want to delete one." << endl;
                int pchoice;
                cin >> pchoice;
                cout << "Provide the Professors University ID." << endl;
                string prof;
                cin >> prof;
                Professor* s;
                s = secretary.search_id_prof(prof);   //search for the student id and if it exists we have the data already in here
                if(!s){
                    cout << "The University ID you have entered doesnt exist." << endl;
                    return;
                }
                if(s->Get_id() == prof){
                    cout << "ID found." << endl;
                }
                
                if(pchoice == 1){
                    string name;
                    cout << "Give the professors name."<< endl;
                    cin >> name;
                    string id;
                    cout << "Give the professors id."<< endl;
                    cin>>id;
                    string pass;
                    cout << "Give the password." << endl;
                    cin >> pass;
                    Professor newprof( name, id, pass);
                    secretary = secretary + newprof;
                }
                else if(pchoice == 2){
                    cout<< "Press 1 if you want to edit the id or 2 if you want to edit the password" << endl;
                    int edit;
                    cin >> edit;
                    if(edit == 1){
                        string na;
                        cout << "Provide new name." << endl;
                        cin >> na;
                        s->Set_name(na);
                    }
                    if(edit == 2){
                        string na;
                        cout << "Provide new password." << endl;
                        cin >> na;
                        s->Set_password(na);
                    }
                }
                else if(pchoice == 3){
                    cout << "Provide the Professors University ID." << endl;
                    string prof;
                    cin >> prof;
                    Professor* s;
                    s = secretary.search_id_prof(prof);   //search for the student id and if it exists we have the data already in here
                    if(!s){
                        cout << "The University ID you have entered doesnt exist." << endl;
                        return;
                    }
                    if(s->Get_id() == prof){
                        cout << "ID found." << endl;
                        delete s;
                    }
                }
            }
            else if(choice == 2){
                cout << "Press 1 if you want to add a student, 2 if you want to edit one, 3 if you want to delete one." << endl;
                int pchoice;
                cin >> pchoice;
                cout << "Provide the Students University ID." << endl;
                string stu;
                cin >> stu;
                Student* s;
                s = secretary.search_id_stud(stu);   //search for the student id and if it exists we have the data already in here
                if(!s){
                    cout << "The University ID you have entered doesnt exist." << endl;
                    return;
                }
                if(s->Get_id() == stu){
                    cout << "ID found." << endl;
                }
                
                if(pchoice == 1){
                    string name;
                    cout << "Give the students name."<< endl;
                    cin >> name;
                    string pass;
                    cout << "Give the password." << endl;
                    cin >> pass;
                    string id;
                    cout << "Give the Univerisity ID." << endl;
                    cin >> id;
                    int ye;
                    cout << "Give the year theyre in." << endl;
                    cin >> ye;
                    float ave;
                    cout << "Give the average." << endl;
                    cin >> ave;
                    int points;
                    cout << "Give the amount of points." << endl;
                    cin >> points;
                    Student newprof( name, id, pass, points, ave, ye);
                    secretary = secretary + newprof;
                }
                else if(pchoice == 2){
                    cout << "Provide the Students University ID." << endl;
                    string stu;
                    cin >> stu;
                    Student* s;
                    s = secretary.search_id_stud(stu);   //search for the student id and if it exists we have the data already in here
                    if(!s){
                        cout << "The University ID you have entered doesnt exist." << endl;
                    }
                    if(s->Get_id() == stu){
                        cout << "ID found." << endl;
                        cout<< "Press 1 if you want to edit the name."<< endl<<"Press 2 if you want to edit the average." << endl<<"Press 3 if you want to edit the password." << endl<<"Press 4 if you want to edit the points." << endl;
                        int edit;
                        cin >> edit;
                        if(edit == 1){
                            string na;
                            cout << "Provide new name." << endl;
                            cin >> na;
                            s->Set_name(na);
                        }
                        else if(edit == 2){
                            float na;
                            cout << "Provide new average." << endl;
                            cin >> na;
                            s->Set_average(na);
                        }
                        else if(edit == 3){
                            string na;
                            cout << "Provide new password." << endl;
                            cin >> na;
                            s->Set_password(na);
                        }
                        else if(edit == 4){
                            int na;
                            cout << "Provide new points." << endl;
                            cin >> na;
                            s->Set_ects(na);
                        }
                    }
                }
                else if(pchoice == 3){
                    cout << "Provide the Students University ID." << endl;
                    string prof;
                    cin >> prof;
                    Student* s;
                    s = secretary.search_id_stud(prof);   //search for the student id and if it exists we have the data already in here
                    if(!s){
                        cout << "The University ID you have entered doesnt exist." << endl;
                        return;
                    }
                    if(s->Get_id() == prof){
                        cout << "ID found." << endl;
                        delete s;
                    }
                }
            }
            else if(choice == 3){
                cout << "Press 1 if you want to add a course, 2 if you want to edit one, 3 if you want to delete one. Press 4 to see who passed the course. Press 5 to logout." << endl;
                int pchoice;
                cin >> pchoice;
                while(pchoice != 5){
                    if(pchoice == 1){
                        int cousem;
                        cout<<"Provide the Semester its going to be in."<<endl;
                        cin>>cousem;
                        Semester* checksem = secretary.Get_semester(cousem);
                        cout<<"Give the name."<<endl;
                        string nam1;
                        cin>>nam1;
                        cout<<"Give the points."<<endl;
                        int p1;
                        cin>>p1;
                        cout<<"Give the mandatory status."<<endl;
                        int man1;
                        cin>>man1;
                        Course newc1(nam1,p1,man1);
                        cout<<"Give the professors id"<<endl;
                        string profid;
                        cin>>profid;
                        cout<<"Give the professors name"<<endl;
                        string profname;
                        cin>>profname;
                        cout<<"Give the professors password"<<endl;
                        string profpass;
                        cin>>profpass;
                        Professor p(profname,profid,profpass);
                        p.Set_course(newc1);
                        newc1.Set_professor(p);
                        secretary = secretary + p;
                        checksem->Add_course(newc1);                        
                    }
                    if(pchoice == 2){
                        cout << "Provide the Courses name." << endl;
                        string cou;
                        cin >> cou;
                        int cousem;
                        cout<<"Provide the Semester its in."<<endl;
                        cin>>cousem;
                        Semester* checksem = secretary.Get_semester(cousem);
                        Course* modify = checksem->search_name_course(cou);
                        int flagfound = 0;
                        Professor* p;
                        for(int j = 0; j < secretary.professors_size(); j++){//if were editing courses in the semesters we need to also update them in the professors
                            p = secretary.Get_prof(j);
                            Course* printcour = p->Get_course();
                            string cprintname = printcour->Get_name();
                            if(cprintname == modify->Get_name()){
                                break;
                                flagfound = 1;
                            }
                        }
                        try{                                                               //prove i can modify a course inside a semester
                            Course* modify = checksem->search_name_course(cou);
                            cout << "Found course: " << modify->Get_name() << endl;
                        } 
                        catch(const out_of_range){
                            cout << "Course not found." << endl;
                        }
                        if(pchoice == 2){
                            cout<<"Press 1 to modify the courses name, 2 to modify the courses ects points, 3 to set a professor, 4 to move it to another semester."<<endl;
                            int couchoice;
                            cin>>couchoice;
                            if(couchoice == 1){
                                cout<<"Give the new name."<<endl;
                                string counewname;
                                cin>> counewname;
                                modify->Set_name(counewname);
                                p->Set_course(*modify);
                            }
                            if(couchoice == 2){
                                cout<<"Give the new points."<<endl;
                                int counewects;
                                cin>> counewects;
                                modify->Set_ects(counewects);
                                p->Set_course(*modify);
                            }
                            if(couchoice == 3){     //5.4
                                cout<<"Give the new professors name."<<endl;
                                string counewname;
                                cin>> counewname;
                                cout<<"Give new professors id."<<endl;
                                string newid;
                                cin>>newid;
                                cout<<"Give new password."<<endl;
                                string newpass;
                                cin>>newpass;
                                Professor prof(counewname, newid, newpass);
                                modify->Set_professor(prof);
                            }
                            if(couchoice == 4){//move semesters 5.5
                                cout<<"What semester would you like to move it to?"<<endl;
                                int movesem;
                                cin>>movesem;
                                //Semester* checkmovesem = secretary.Get_semester(cousem);
                                secretary.Move_course(cou, cousem,movesem);
                                p->Set_course(*modify);
                                p->Set_sem(movesem);
                            }
                        }
                    }
                    if(pchoice == 3){
                        cout << "Provide the Courses name." << endl;
                        string cou;
                        cin >> cou;
                        int cousem;
                        cout<<"Provide the Semester its in."<<endl;
                        cin>>cousem;
                        Semester* checksem = secretary.Get_semester(cousem);
                        Course* modify = checksem->search_name_course(cou);
                        int flagfound = 0;
                        Professor* p;
                        for(int j = 0; j < secretary.professors_size(); j++){//if were editing courses in the semesters we need to also update them in the professors
                            p = secretary.Get_prof(j);
                            Course* printcour = p->Get_course();
                            string cprintname = printcour->Get_name();
                            if(cprintname == cou){ 
                                flagfound = 1;
                                break;
                            }
                        }
                        if(flagfound){
                            Course* deleted = new Course();
                            deleted->Set_name("DELETED");
                            deleted->Set_ects(0);
                            p->Set_sem(0);
                            deleted->Set_mandatory(0);
                            p->Set_course(*deleted);
                        }
                        secretary.remove_course_sec(cou, cousem);
                    }
                    if(pchoice == 4){
                        cout << "Provide the Courses name." << endl;
                        string cou;
                        cin >> cou;
                        int cousem;
                        cout<<"Provide the Semester its in."<<endl;
                        cin>>cousem;
                        secretary.check_passed_sec(cou, cousem);            //5.6
                    }
                    cout << "Press 1 if you want to add a course, 2 if you want to edit one, 3 if you want to delete one, 4 to show who passed it. Press 5 to logout." << endl;
                    cin>>pchoice;
                }
            }
            cout<<"Press 1 if you want to edit professor related data." << endl << "Press 2 if you want to edit student related data." << endl << "Press 3 if you want to edit semester data." << endl << "Press 4 if you want to print everyone who can graduate." <<endl<< "Press 5 to logout." << endl;
            cin >> choice;
        }
        return;
    }
    cout << "Wrong password." << endl;
    return;
}


void writeProfessorsToFile( Secretary& secretary, const string& filename) {
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    // Iterate over professors and write their information to the file
    for(int j = 0; j < secretary.professors_size(); j++){
        Professor* p = secretary.Get_prof(j);
        Course* printcour = p->Get_course();//its this mfer right here
        string cprintname = printcour->Get_name();
        int courects = printcour->Get_ects();
        int courmand = printcour->Get_mandatory();
        if(printcour){
            outputFile << p->Get_name() << " " << p->Get_id() << " " << p->Get_password() << " " << p->Get_sem() << " " << cprintname<< " " << courects<<" "<< courmand<<endl;
        }
    }
    outputFile.close();
}

void writeStudentsToFile( Secretary& secretary, const string& filename) {
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }
    cout<<secretary.studs_size()<<endl;
    // Iterate over professors and write their information to the file
    for (int j = 0; j < secretary.studs_size(); ++j) {
        cout << "TEST" << endl;
        Student* s = secretary.Get_stud(j);
        outputFile << s->Get_name() << " " << s->Get_id() << " " << s->Get_password() << " " << s->Get_ects() << " " << s->Get_average() << " " << s->Get_year();
        outputFile << endl;
    }
    outputFile.close();
}

int main(){
    static Secretary secretary;
    //THIS COMMENTED AREA IS THE PROOF OF WORK FOR 5.1,5.2,5.3,5.5,5.8
    //IN CASE OF A CHECK FOR THE PROOF COMMENT THE MENU FOR IT WORK
/*    //5.1
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

    //5.3
    cout<<"Number of semesters: "<<secretary.semesters_size()<<endl;         //prove semestersents is empty
    string namecourse = "Intro to Programming";
    int ectscourse = 6;
    int man = 1;
    Course intro(eleni,namecourse, ectscourse,man);
    vector<Course*> firstcourses;
    firstcourses.push_back(&intro);
    Semester first; //initialise the semester
    first.Add_course(intro);
    secretary = secretary + first;
    cout<<"Number of semesters: "<<secretary.semesters_size()<<endl;//prove semester is added to sec
    Semester* checksem = secretary.Get_semester(1);
    cout<<"Courses in first semester: "<<checksem->size_course()<<endl;     //prove we can add courses to a semester
    vector<Course*> L = checksem->Get_courses();                               //prove it is inside the vector courses of the semester
    cout<<"In the vector of Courses the name is: "<<L[0]->Get_name()<<endl;
    try{                                                               //prove i can modify a course inside a semester
        Course* modify = checksem->search_name_course("Intro to Programming");
        cout << "Found course: " << modify->Get_name() << endl;
        string newnamecourse = "John";
        string newidcourse = "sdi54";
        string newpasscourse = "INeedToMakeTheMenuTooButThisIsJustDemonstratingItWorks";
        Professor john(newnamecourse, newidcourse, newpasscourse);
        modify->Set_professor(john);
        vector<Course*> check = first.Get_courses();
        Professor testcourse = check[0]->Get_professor();
        cout <<"New name of professor: "<<testcourse.Get_name()<<endl;
    } 
    catch(const out_of_range){
        cout << "Course not found." << endl;
    }
    
    //5.5
    string name5 = "Mark";
    string id5 = "sdimark";
    string pass5 = "immark";
    Student mark(name5, id5, pass5);
    mark.Set_year(5);
    cout<<"Enter the semester you want to choose:"<<endl;
    int sc5;
    cin>> sc5;
    if(sc5/2 <= mark.Get_year()){
        cout << "Enter the course you want to choose: " << endl;
        string choicec5;
        cin >> ws;  //skip whitespaces
        getline(cin, choicec5);
        if(sc5 == 1){//also will do for the rest                                                               
            try{
                Course* modify = checksem->search_name_course(choicec5);
                cout << "Found course: " << modify->Get_name() << endl;
                mark.stud_add_course(*modify);
                vector<Course*> markcour = mark.Get_courses();
                cout<<"Mark has been enrolled to: "<< markcour[0]->Get_name()<<endl;
            }
            catch(const out_of_range& ex){
                cout << "Error: could not find the course" << endl;
            }
            
        } 
    }
*/
/*  string nameprof = "Eleni";
    string idprof = "sdiEleni1";
    string passwordprof = "HopeIPass";
    Professor prof1(nameprof, idprof, passwordprof);
    Employee emp(nameprof,idprof,passwordprof);
    secretary = secretary + emp;
    secretary = secretary + prof1;
    string nameprof2 = "Eleni2";
    string idprof2 = "sdiEleni2";
    string passwordprof2 = "HopeIPass2";
    Professor prof2(nameprof2, idprof2, passwordprof2);
    secretary = secretary + prof2;
    string namecourse = "Intro";
    int pointcourse = 5;
    int mandcourse = 1;
    Course intro(prof1,namecourse,pointcourse, mandcourse);
    namecourse = "Datastructs";
    pointcourse = 5;
    mandcourse = 1;
    Course datastructs(prof2,namecourse, pointcourse, mandcourse);
    namecourse = "Linear Algebra";
    pointcourse = 5;
    mandcourse = 1;
    Course linear(prof2,namecourse, pointcourse, mandcourse);
    namecourse = "Physics";
    pointcourse = 5;
    mandcourse = 1;
    Course physics(prof2,namecourse, pointcourse, mandcourse);
    Semester first;
    Semester second;
    string namestud = "Themis";
    string idstud = "sdi2000071";
    string passwordstud = "Itriedmybest";
    Employee empl(namestud, idstud, passwordstud);
    Student me(namestud, idstud, passwordstud);
    int g = 10;
    me.stud_add_passed(intro, g);
    me.stud_add_passed(linear, g);
    me.stud_add_passed(datastructs, g);
    me.stud_add_passed(physics, g);
    me.Set_average(10);
    me.Set_year(4);
    me.Set_ects(20);
    secretary = secretary + me;
    first.Add_course(intro);
    first.Add_course(linear);
    secretary = secretary + first;
    cout<<first.size_course()<<endl;
    second.Add_course(datastructs);
    second.Add_course(physics);
    secretary = secretary + second;
*/
    string nameprof = "Eleni";
    string idprof = "sdiEleni1";
    string passwordprof = "HopeIPass";
    Employee emp(nameprof,idprof,passwordprof);
    secretary = secretary + emp;
    Semester first;
    Semester second;            //only two semesters so that we can be more simple
    ifstream inputFile("profcourses.txt");
    if(!inputFile.is_open()){
        cerr << "Error opening file." << endl;
        return 0;
    }
    string line;
    while(getline(inputFile, line)){
        // Use stringstream to extract data from the line
        stringstream lineStream(line);

        // Variables to store data
        string name, id, password, course;
        int semester, ects, mandatory;

        // Extract data from the line
        lineStream >> name >> id >> password >> semester >> course >> ects >> mandatory;
        Professor temp(name, id, password);
        Course tempc(temp, course, ects, mandatory);
        if(semester == 1){
            first.Add_course(tempc);
            temp.Set_course(tempc);
            temp.Set_sem(semester);
        }
        else if(semester == 2){
            temp.Set_course(tempc);
            temp.Set_sem(semester);
            second.Add_course(tempc);
        }
        secretary = secretary + temp;
        // Process the extracted data (you can customize this part)
    }

    secretary = secretary + first;
    secretary = secretary + second;

    ifstream inputFile2("studs.txt");
    if(!inputFile2.is_open()){
        cerr << "Error opening file." << endl;
        return 0;
    }
    while(getline(inputFile2, line)){
        // Use stringstream to extract data from the line
        stringstream lineStream(line);
        // Variables to store student data
        string name, id, password;
        int ects, average, year;
        // Extract student data from the line
        lineStream >> name >> id >> password >> ects >> average >> year;
        Student student(name, id, password, ects, average, year);
        // Variables for course data
        int semester;
        string course;
        int grade;
        // Read semester, course, and grade information
        while(lineStream >> semester >> course >> grade){
            Semester* check = secretary.Get_semester(semester);
            Course* modify = check->search_name_course(course);
            student.stud_add_passed(*modify, grade);
        }
        secretary = secretary + student;
    }
    // Close the file
    inputFile.close();
    cout << "\n\nMyStudy Menu:\nPress 1 if Student, 2 if Professor, 3 if Secretary." << endl;
    int path;
    cin >> path;
    if(path == 1){  //use exception here and on the others
        stud(secretary);
        writeProfessorsToFile(secretary, "profcourses.txt");
        writeStudentsToFile(secretary, "studs.txt");
        return 0;
    }
    if(path == 2){
        teach(secretary);
        writeProfessorsToFile(secretary, "profcourses.txt");
        writeStudentsToFile(secretary, "studs.txt");
        return 0;
    }
    if(path == 3){
        employee(secretary);
        writeProfessorsToFile(secretary, "profcourses.txt");
        writeStudentsToFile(secretary, "studs.txt");
        return 0;
    }
    return 0;
}