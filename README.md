# phase2
Completed:
B1
B2
B3
B4
B.5.1
B.5.2
B.5.3
B.5.4
B.5.5
B.5.6
B.5.8
B.5.9
Input file for students
Input file for professors and courses
Output file for professors and courses
Output file for students

*only one not done is B.5.7. Η εργασια για μενα ηταν αρκετα δυσκολη να βγει λογω εργασιας, καθως στην διαθεση μου ειχα μονο απογευματα μετα απο την δουλεια.

Παρακαλω να σημειωθει οτι λογω δουλειας δεν μπορουσα να παρακολουθησω τις διαλεξεις και διαβαζα απο το σπιτι τις διαφανειες, καθως και ερχομουν στα εργαστηρια. Αυτο σημαινει οτι οποιεσδηποτε διευκρινισεις που δωθηκαν κατα την ωρα των διαλεξων για την εργασια δεν τις γνωριζω. Εχω πραγματικα δωσει πολυ κοπο για αυτην την εργασια οποτε μια μικρη κατανοηση θα ηταν ευχαριστη. Η εργασια ουτως η αλλως ειναι για να σας δειξουμε οτι εχουμε μαθει c++ το οποιο πιστευω οτι εχω καταφερει να εκφωνησω με τον κωδικα μου.

sdi2000071

BELOW IS A FULL ON MANUAL FOR THE CODE. I AM CONFIDENT THAT I DONT NEED TO COMMENT MY CODE IN THE CPP FILE SINCE ITS SO IN DETAIL BELOW.

DOCUMENTATION:
compile with: g++ -o secretary secretary.cpp
run with ./secretary

MAIN DOCUMENTATION:
    The commented area is the version of the code that works by inputing from main and printing in the terminal instead of the files. Feel free to test it but you have to comment the writeprof and writestud funcs as well as the rest of the main from line 1190 to line 1259. The file main:
        We start by initialising the secretary(static to be easy to modify) and then initialising the employee of the department and inputing them in the secretary by operator+ overloading. We then initialise the two semesters(only 2 for easy of showing the program works). Input them into the secretary

        Now that the base secretary has beem initialised, we open the file profCourses.txt which contains the professors, their info and their taught courses along with their info. We input the professors into the secretary, the courses into the respective semester, and finally the semesters into the secretary.

        We open the file studs.txt which contains all the students and their info and update the secretary by inputing them inside it.

        Lastly, we print the initial choice of student, prof or employee login and use the appropriatte function with an if. After the function is over we update the files and terminate.

Explaining the code:

FUNCTIONS OTHER THAN STUDENT:
    STUD DOCUMENTATION:
        We input the secretary into the function so that we can modify and add to it. stud function is basically a terminal operated menu, used when selected by the user in the codes initial step of choosing login method. When choosing to login as a student the code is redirected to the stud function which asks the user for their University ID. Upon providing the code with an id, stud validates that it exists, and then asks for the students password. If the student provides the correct one they can access the function described below, otherwise the program exits. The function includes:
            secretary.search_id_stud:
                Described above, this function searches for the students id. We then check if the ID exists already inside the secretary. Last we set a pointer to the student called s that points inside the secretary.
            s->Get_password:
                Since we have all the data of the student where the ID provided belongs, we also have their password. We ask the user to provide their password and check it is the same as the actual one.
            while(choice != 6):
                We successfulyl logged into the service. We are presented with 6 choices listed and if we press 6 we log out, the while loop terminates and the stud func terminates.
            choice == 3:
                This choice means the student wants to enroll to a certain course. We ask them for the semester the course is in, the name of the course, and if found we make a pointer modify pointing to it. We also use exception for this. Also for the name of the course we use getline to skip the whitespaces between the name of the course. For example "Intro to Programming" with cin would only read Intro.
            choice == 4:
                Ask for a new password and store it in the Student object.
            choice == 1 | choice == 2 | choice == 3:
                All of them pretty self explanatory.

    TEACH DOCUMENTATION:
        Just like stud we input the secretary, ask the user to login and then we can modify data. Just like stud we have a menu and the user chooses what he wants to do from it. Only one not done is show semester stats which is B.5.7(for reason look at the * below the completed parts). Teach is pretty simple, we can only change password or logout. Changing password works the same as in stud.

    EMPLOYEE DOCUMENTATION:
        First we ask for the employee to login just like stud and teach. Same procedure so dont need to explain. Then we present the employee with the menu. We take in their choice and act accordingly. More in detail:
            choice == 1:
                We are working with professor data. We ask what we want to do with the professor data.
                    pchoice == 1
                        We want to add a professor so we ask the employee for all the data and we initialise a Professor object with them. We then add it to the secretary with operator+ overolading.
                    pchoice == 2
                        We either want to edit the id or the password so we ask and then edit them inside the pointer.
                    pchoice == 3
                        We want to delete the professor. We ask for the University ID again because we need to make sure who were deleting. We find him make a pointer s to him and delete him.
            choice == 2
                We want to work with student data. So we ask for the student info and then present the menu options:
                    pchoice == 1
                        We want to add a student so we get all the info from the employee and we then initialise a Student Object which we later input into tje secretary with operator+ overloading.
                    pchoice == 2
                        We want to edit a student so we ask for the id again search for it make a pointer to the student. We ask which part we want to edit:
                            edit == 1
                                We provide a new name.
                            edit == 2
                                We provide a new average.
                            edit == 3
                                We provide a new password.
                            edit == 4
                                We provide a new sum of ects points.
                    pchoice == 3
                        We want to delete a student so we ask for the id again and we delete them.
            choice == 3
                We want to work with Course data. We ask for the type of operation we want to perform:
                    pchoice == 1
                        We want to add a course so we ask for the new courses info initialise a course newc1 with that info and input it in the semester we decided.
                    pchoice == 2
                        We want to edit a course so we ask for the name of the course and the semester its in and use search_name_course. We use *modify wit the function to get the pointer and be able to change what we want. We then ask for the choice of edit:
                            couchoice == 1
                                We  ask for the new name and awr it to the *modify course.
                            couchoice == 2
                                Same but with ects points
                            couchoice == 3
                                We set a new professor for the course by asking the info about them, intialising them and setting them to the course with modify->Set_professor.
                            couchoice == 4
                                We want to move a course from one semester to another so we ask where do we want to move it. We then use the Move_course function with the original semester number and then destination semester number.
                    pchoice == 3
                        We want to delete a course so we search for it, find it, and once found we set its name to DELETED, 0 to everything else and we remove it from the secretary.
                    pchoice == 4
                        We want to see who passed a certain course so we ask for the courses name and then we use the check_passed_sec function.
                    pchoice == 5
                        We logout and Employee terminates

    WRITEPROFESSORSTOFILE DOCUMENTATION:
        When the menu is finishes and we have all the altered data inside secretery we need to be able to update the files of input. So in this function:
            We get the filename of the file and use ofstream to redirect the output.
            We check we can open the file.
            And we go over every professor and write in the format we want their info and the info of the course theyre teaching.
            We then close the file.

    WRITESTUDENTSTOFILE DOCUMENTATION:
        Same as writeProfessorsToFile but for the students.

CLASS DOCUMENTATION:
    1.Person is a base class with all the characteristics that students, professors and employees share(name, id etc).

    2.Student is a derived class from Person with public access to its contents. It also sets the unique variables a student has, like his grades, the courses he has passed etc.

    3.Professor, just like the Student class is a derived class from public accessed Person class. Has its own unique features, such as the course the professor is currently teaching and the semester its in.

    4.Employee is just like the other derived from public Person classes. We need employee objects so that the core changing feautures of the program like moving the courses from one semester to another can be locked behind a password to limit access.

    5.Course is a class made to store the info of a course inside. It includes the ects points, the mandatory status, name and the professor teaching it.

    6.Semester is basically a container class for Course objects. We use it as a bundle of Course objects to define a semester.

    7.Secretary is the core class of this program. The class that all ties it together. We have most of our mutators and accessors in this class and it can be used to reach every object in this code.

Technical analysis of the classes step by step:
    1.Person:
        We start by making the mutators and accessors of this class virtual since we will use derived classes. We have the accessors for name, id and password, and the respective mutators. The constructor takes in a name an id and a password and initialises the Object Person. Copy Constructor just does the same but with the data from the copied Person. 

    2.Student:
        We have inside a vector of Pointers to Objects of class Course called Passed used to store the Students passed courses. Personally pointers in this instance make it easier to access the objects of Course type and alter them/ extract data from them. Next there is a vector of type int with the grades of the respective Passed Courses. Next is the current enrolled courses same idea as the Passed, then the total ects of the student, the average and finally the year they are in.

        The functions include:
            show_grades:
                Shows every passed courses name and then its grade.
            graduates:
                We calculate the total ects for every student just to be sure, and if it exceeds the minimum the we print the students name.
            check_passed_stud:
                We take a name of the course were looking for. Then we search for it inside the vector of Passed Courses and if we find it, we print the name of the student. 
            stud_add_course:
                Pretty straightforward. We take in a course and use dynamic memory allocation on a temp Course, in which we copy the original course. We later add it to the vector of courses of the current semester.
            stud_add_passed:
                Same concept as above but we also add a grade since its passed.
            print_grades:
                We iterate through all the Passed Courses and their grades and we print both of them for each pair.
            Get_coursesize:
                Just returns the size of the current semester vector. Used later in the code for accessing.
            Get_courses:
                Returns the vector of current semester.
            Get_ects:
                Returns the ects of the student.
            Get_average:
                Returns the average of the student.
            Get_year:
                Returns the year of the student.
            Set_ects:
                Sets the new value x for the ects of the student.
            Set_average:
                Sets the new value x for the average of the student.
            Set_year:
                Sets the new value x for the year of the student.
            Constructor:
                Takes in a name, an id, a password, an ects value, an average value and a year value and initialises a Student object with those values inside it.
            Copy Constructor:
                Same as above but we just use the data from the copied Student. Pay attention to the copied Student being passed as a copied object to the Person Object. This means we also copy the copied objects person data.
            Limited Constructor:
                Same as our base constructor but used in instances where we dont need to be initialise any more then the Students name, id and password
            Empty Constructor:
                Cosntructs an empty student.
            Destructor:
                Deletes the Student object.

    3.Professor:
        The Professor class is a more limited class than the student one. In this one we only deal with the Professors name, id , password and the current course theyre teaching and the semester the respective course is in. The functions include:
            Remove_course:
                Remove the course the Professor is teaching and set as a nullptr since were using a pointing of class Course to store it in the Professor class.
            Set_sem:
                Sets the new semester the course the professor teaches.
            Get_sem:
                Returns the semester the Course is in.
            Set_course:
                CAUTION. This function is initialised elsewhere because otherwise we would be getting incomplete type Course since Professor is below course.
                Gets in a course and copies it and stores it inside the current course.
            Constructor:
                Takes in a name, an id, a password and initialise the Professor object. Also since we havent yet set the course the professor teaches we set it as nullptr.
            Constructor with sem:
                Same as above but we also have the semester the course is in. Used with Set_course to later set our course.
            Empty Constructor:
                Initialises an empty Professor object.
            Copy Constructor:
                Just like in Student class we copy everything from the copied Professor. We also copy the Person data from the copied Professor and we check if the copied Professor had a Course they were teaching. If their taught course isnt nullptr(we check to avoid seg fault), we insert it to the new Professor.
            Destructor:
                Deletes the Professor Object.

    4.Employee:
        We dont need to access or alter anythig about the employee class so we just have a Constructor, a copied Constructor and a Destructor.

    5.Course:
        Inside the Course class we have the data of a course, meaning the Professor currently teaching the course, the courses name, its ects points and its mandatory status. The functions include:
            Set_professor:
                We get a professor, copy them and then set them as the teaching professor for the course.
            Get_professor:
                We return a reference to the Professor currently teaching the Course.
            Get_name:
                Returns the name of the course.
            Get_ects:
                Returns the ects of the course.
            Set_name:
                Gets a name and sets it as the new name of the course.
            Set_ects:
                Gets an x value and sets it as the new ects points.
            Set_mandatory:
                Gets an x value and sets it as the mandatory status for the course.
            Constructor:
                Gets a name, a value for the ects points and a value for the mandatory status and initialises a course with the respective values in the correct variables.
            Empty Constructor:
                Initialises an empty Course.
            Copy Constructor:
                Copies one course to another.
            Destructor:
                Deletes a course

    6.Semester:
        The Semester class is just a container to store many Course Objects inside it. Simple as that. The functions include:
            size_course:
                Returns the how many Courses are inside the semester.
            search_name_course:
                Gets a name for a course and iterates through the whole vector. If the Course in the current position of the vector, has a name that matches the one inputed into the function, then we found the Course we want and we return it.
            Get_courses:
                Returns a reference to the courses vector in the semester, effectively returning the whole vector.
            Add_course:
                Gets a course and copies it to a temp with dynamic memory allocation, then we push temp into the courses vector.
            Remove_course:
                We get a course name. We use it to search through the whole semester. If we find a course that has the same name as the name given, we erase it from the vector courses and we delete it.
            Constructor:
                We only have an empty constructor since thats all we need. If we need to add courses we just use the functions provided.
            Destructor:
                Deletes the whole semester.

    7.Secretary:
        The Secretary class holds in the all the Student, Professor, Employee and Semester Objects. We have functions to mutate and access all of the above. It is the most essential class in the program. The functions include:
            print_graduates:
                We iterate through every student in the Secretary and we call the graduates function for every one of them. The graduates function was described in the Student class description.
            Move_course:
                We get a course name, an origin semester number and a destination semester number. We use the name given to search through the courses of the semester, and if we find it, we add it to the destination numbered semester, and we delete it from the original semester and erase it from the vector.
            check_passed_sec:
                We get a course name, and a semester number. We iterate through every student and call check_passed_stud for it. check_passed_stud has been described in the Student class description.
            remove_course_sec:
                We get a course name and an original semester number. We search for the course and if we find one that its name matches the name we were given we delete it from the semester and erase it from the vector of the semester.
            Get_semester:
                We get a number of the semester we want to return and return the one before it because vectors start from 0.
            sem_size:
                Returns the number of total courses in a semester through iterating each one an updating a counter. This was done for debugging reasons but we leave it for future proofing the code in case of future debugging attempts.
            semesters_size:
                Does the same as above but with the vector.size() func.
            studs_size:
                Returns the number of Students inside the vector students.
            professors_size:
                Returns the number of Professors inside the vector professors.
            employees_size:
                Returns the number of Employees inside the vector employee.
            Get_stud:
                We get a number i and we return the Student object inside the position i in the vector students.
            Get_prof:
                We get a number i and we return the Professor object inside the position i in the vector professors.
            Get_sem:
                We get a number i and we return the Semester object inside the position i in the vector semesters.
            Constructor:
                We only need an empty constructor.
            Destructor:
                We Destruct the class secretary but also we dont forget to delete the vectors employees, students, professors and semesters.
            Delete_stud:
                We get an id, search through the students vector and if we find a student with the same id, then we delete them and erase them from the vector.
            Delete_course:
                Same concept as above but we get a name of a course and if we find it we delete it an erase from vector.
            Delete_prof:
                Same as Delete_student but we just search in professors.
            operator+Employee:
                We get an employee newem. We copy it to an Employee Object temp and then we push it into the vector employees. This is operator overloading.
            operator+Student:
                Same as above operator overloading for Student Objects.
            operator+Professor:
                Same as above operator overloading for Professor Objects.
            search_id_employee:
                Used to shorten the search for an employees id. We get a name and search for it through the vector employees. If we find it we return the Employee Object in the respective position of the vector.
            search_id_prof:
                Same as search_id_employee but for the professors vector.
            search_id_stud:
                Same as search_id_employee but for the students vector.
            operator>> and <<:
                Used in the first part of the assignment so we dont need them anymore.