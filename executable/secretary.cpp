#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
using namespace std;



int valid_id(string id){
    if (id.length() != 10){                                     // Check the length
        cout << "Error: University ID is invalid." << endl;
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
        int uni_id;
        static int count;
        string occupation;

    public:                                                         //first constructor we use initialiaser list if were given veriables for the person
        string Get_pname(){
            return name;
        }
        int Get_pid(){
            return uni_id;
        }
        string Get_poccupation(){
            return occupation;
        }
        Person(const string& n, long int id, string oc)
            : name(n), uni_id(id), occupation(oc){
            count++;                                                //we increase the sum by one
            //cout << "Created a new Person. In total: " << count << endl;
        }
        Person(const Person& copied)                                //copy constructor
        : name(copied.name), uni_id(copied.uni_id), occupation(copied.occupation){      //copy from the original from intialiser list
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
        int const Get_id(){                                         //getter function for uni id
            return this->uni_id;
        }
        friend istream& operator>>(istream& in, Person& person) {   //ovberload the in>> operator
            cout << "Enter name: " << endl;                         //get inputs
            in >> person.name;                                      //put them in the respective variables
            cout << "Enter age: " << endl;
            in >> person.uni_id;
            cout << "Enter occupation" << endl;
            in >> person.occupation;
            return in;
        }
        friend ostream& operator<<(ostream& out, const Person& person){
            out << "Person's name: " << person.name << endl;    //overload the out<< operator and just print everything about a person
            out << person.name << "'s university identification number: sdi" << person.uni_id << endl;
            out << person.name <<"'s occupation: " << person.occupation << endl;
            return out;
        }
};

int Person::count = 0;                                      //initialise the count

class Professor: public Person{
    private:
        string password;
    public:
        string Get_password(){
            return password;
        }
        Professor(const string& n, long int num, long int id, string oc, const string& newpass)
            : Person(n, id, oc), password(newpass){                                      //call base class constructor
            //cout << "Created a new Professor." << endl;
        }
        Professor(const Professor& copied)
            : Person(copied), password(copied.password) {
            //cout << "Created a new Professor by copying." << endl;
        }
        Professor(){
            //cout << "Created a new Professor." << endl;
        }
        ~Professor(){
            //cout << "Deleted a Professor." << endl;
        }
};

class Course{
    private:
        int ects_points;
        string name;
        Professor* prof;
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
        Professor Get_Professor(){
            return *prof;
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
        void Set_Professor(Professor* new_professor){
            prof = new_professor;                               //uses the copy constructor of Professor
        }
        Course(int p, string n, Professor* pr, int m):ects_points(p), name(n), prof(pr), mandatory(m){
            //cout << "New course." << endl;
        }
        Course(){//maybe set reference for professor and initialise it here and give it to the course with &
            //cout << "New course." << endl;
        }
        ~Course(){
        }
};

class Student: public Person{
    private:
        int year;
        int average = 0;
        string password;
        int points = 0; 
        list<Course> current_semester;
        static int stud_count;
    public:
        string Get_name(){
            return Get_pname();
        }
        int Get_id(){
            return Get_pid();
        }
        string Get_occupation(){
            return Get_poccupation();
        }
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
        Student(const string& n, string& id, string& oc, int studentYear, int studentAverage, const string& studentPassword, int studentPoints)
            : Person(n, valid_id(id), oc),                                      //call base class constructor
            year(studentYear), average(studentAverage), password(studentPassword), points(studentPoints) {
            //cout << "Created a new Student." << endl;
        }
        Student() : year(0), average(0), points(0) {
            //cout << "Created a new Student" << endl;
        }
        ~Student(){
            //cout<< "Deleted student" << endl;
        }
};

int Student::stud_count = -1;


class Secretary{
    private:                                                    //each secretary has a name and knows every person
        vector<Person*> people;                                 //we load the data into a list of pointer person
        vector<Student*> students;
        vector<Professor*> professors;
        string name;//probably gonna make this a vector and search with login just like student
    public:
        Student* Get_stud(int i){
            return students[i];
        }
        Secretary(string n):name(n){                            //constructor and destructor (2.1)
            //cout << "Constructed the secretary." << endl;
        }
        ~Secretary(){
            for(int i = 0; i < people.size(); i++){             //dont forget to delete every person inside the list
                delete people[i];
            }
            for(int i = 0; i < students.size(); i++){             //dont forget to delete every person inside the list
                delete students[i];
            }
            //cout << "Destructed the secretary." << endl;
        }
        Secretary& operator+(Person& person){                    //overload the += operator to add a person with dynamic memory allocation (2.2)
            Person* temp = new Person(person);                               //make a temp of the values you need and got via the main or function call
            people.push_back(temp);                            //put the person inside the vector
            cout<<people.size()<<endl;
            return *this;
        }
        Secretary& operator+(Student& stud){                    //overload the += operator to add a person with dynamic memory allocation (2.2)
            Student* temp = new Student(stud);                               //make a temp of the values you need and got via the main or function call
            students.push_back(temp);                            //put the person inside the vector
            //cout<<"stud:"<<students.size()<<endl;
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
        int search_id(int id, string stud_or_teacher){              //search for any person based on their university id but with only their sdi as input
            for(int i = 0; i < people.size(); i++){             //instead of working with strings i just
                if(id == people[i]->Get_id()){                  //if the ids match you found them
                    //if(stud_or_teacher == people[i]->occupation){
                        return id;
                    //}
                }
            }
            return 0;
        }
        Student* search_id_stud(int id){              //search for any person based on their university id but with only their sdi as input
            for(int i = 0; i < students.size(); i++){             //instead of working with strings i just
                Student *temp = students[i];
                //cout<<"STUDID"<<temp->Get_id()<<endl;
                int c = temp->Get_id();
                if(id == c){                  //if the ids match you found them
                    return temp;                //return the object
                }
            }
            return nullptr;                 //if not then return null pointer
        }                                                    //overload the in>> operator and take a name from keyboard and insert it into the secretary
        friend istream& operator>>(istream& in, Secretary& sec){
            cout<<"Give name."<<endl;                           //(2.3.a)
            in>>sec.name;
            return in;
        }                                                       //overload the out<< operator and print every person in the list of the secretary
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
                Person* temp = new Person(*(copied.people[i])); //copy every person from the original list to the new one
                people.push_back(temp);
            }
            //cout << "Created a copied Secretary."<< endl;
        }
};

void stud(Secretary &secretary){
    string input;    
    cout << "Please provide your University ID." << endl;
    cin >> input;
    int id = valid_id(input);
    cout<<id<<endl;
    if(id == 0){
        cout << "You have entered a non valid University. Proper syntax is:\nsdi1234567 (sdi followed by 7 numbers)" << endl;
        return;
    }
    Student* s;
    s = secretary.search_id_stud(id);
    if(!s){
        cout << "The University ID you have entered doesnt exist." << endl;
        return;
    }
    if(s->Get_id() == id){
        cout << "ID found." << endl;
    }
    cout << "Enter password." << endl;
    string pass;
    cin >> pass;
    cout << endl;
    if(pass == s->Get_password()){
        cout << "Login successful." << endl<<endl;
        cout << "Press 1 to show your grades for this semester."<<endl<<"Press 2 to show total average."<<endl<<"Press 3 to show your ECTS points."<<endl<<"Press 4 to sign up for a course."<<endl<<"Press 5 to change password."<<endl<<"Press 6 to logout." << endl<<endl;
        int choice;
        cin >> choice;
        while(choice != 6){
            /*if(choice == 1){
                cout << "Press 1 if its winter semester or 2 for spring semester." << endl;
                int c;
                cin >> c;
                int s = 2* s->Get_year();
                if(c == 1){
                    s = s - 1;
                    for(auto it = cursemester[s].begin(); it != semester[s].end(); it++){

                    }
                }
                if(c == 2){
                    for(auto it = semester[s].begin(); it != semester[s].end(); it++)

                }
            }*/
            if(choice == 2){
                float av = s->Get_average();
                cout << "Your average is: " << av <<endl<<endl;
            }
            else if(choice == 3){
                int epoints = s->Get_points();
                cout << "Your ECTS points are: "<< epoints << endl<<endl;
            }
            else if(choice == 4){
                float f;
                cin >> f;
                s->Set_average(f);
            }
            else if(choice == 5){
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
            cout << "Press 1 to show your grades for this semester."<<endl<<"Press 2 to show total average."<<endl<<"Press 3 to show your ECTS points."<<endl<<"Press 4 to sign up for a course."<<endl<<"Press 5 to change your password."<<endl<<"Press 6 to logout" << endl<<endl;
            cin >> choice;
        }
    }
    else{
        cout << "Wrong password. Try again" << endl;
    }
}

int main(){
    //was intially list but too much work to move around courses so we make it a list
    static list<Course> semester[8];                               //just to be simpler im gonna initialise the semesters with only 2 courses in each
    static Secretary secretary("Bob"); 
    Course Intro;
    Professor John; 
    Intro.Set_Professor(&John);                             //we can add a professor to the course
    semester[0].push_back(Intro);
    Course Discrete_Math;
    semester[0].push_back(Discrete_Math);
    Course Data_Structs;
    semester[1].push_back(Data_Structs);
    Course PC_Architecture;
    semester[1].push_back(PC_Architecture);
    string a = "Themis";
    int y = 4;
    string ide = "sdi2000071";
    string oc = "student";
    string pas = "ilikecar";
    Student me(a, ide, oc, 4, 0.0, pas, 0);
    secretary = secretary + me;
    Student* temp = secretary.Get_stud(0);
    secretary = secretary + me;
    //cout<<"IN THE VECTOR STUDENTS "<<temp.Get_year()<<endl;
    //cout<<"OAASS "<< temp.Get_name();
    cout << "\n\nMyStudy Menu:\nPress 1 if Student, 2 if Professor, 3 if Secretary." << endl;
    int path;
    cin >> path;
    if(path == 1){  //use exception here and on the others
        stud(secretary);
        //return 0;
    }
    Student* temp2 = secretary.Get_stud(0); 
    //*temp2 = secretary.Get_stud(0);
    string newp = temp->Get_password();
    cout << newp <<endl;
    float f = temp->Get_average();
    cout<<f<<endl;
    return 0;
}