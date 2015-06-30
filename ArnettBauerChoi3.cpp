/*
Authors: Austin Arnett, Aaron Choi, Brian Bauer
Course: Data Structures
Instructor: Anca Ralescu
TA: Suryadip Chakraborty
Abstract: This program creates a gmail of given communications from the user. the program counts the subjects with the
    same name and will let the user know how many emails are within a given communication. Once the user is done with
    creating the first gmail, the copy constructor copies gmail and creates "Copymail", where you are able to test or
    verify that the copy constructor works, or add more to Copymail.
Preconditions: User commands - "Display", "Insert", "Delete", and "Finish". Follow on-screen commands to add subjects.
Postconditions: An email to review all the subjects you entered.
*/

#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<string>
#include<vector>

using namespace std;
/*=======================================================================================================================*/
//Inbox Class
class Inbox{
private:
    int Number_of_Comms;

    //Communication is the main make-up of Inbox It provides a list of Subjects to the user.
    struct Communication{

        string Subject;
        int Number_of_Emails;

        Communication *next; //Next string of emails
        Communication *previous; //Previous string of emails

        //Emails are the linked list within communication. Each node provides message details.
        struct Email{
            //Email details
            string To;
            string From;
            string Message;

            //These pointers navigate the linked list.
            Email *Older_Email; // "*next"
            Email *Newer_Email; // "*previous"
        };//End Email

        //This is the pointer that points to the front of an "Email" string (or top of the "Email" stack).
        Email *NewestEmail; // "*head" (or "*top" of stack) of "Email"

    };//End Communication

    Communication *NewestComm; //Points to first Communication ("*top" of stack)

public:
    //Constructors & Destructor
    Inbox(); //Default Constructor
    ~Inbox(); //Destructor
    Inbox(const Inbox& object); //Copy constructor, unsure of what to name the object. Maybe just "object"?

    //Main methods for Inbox.
    void Menu();
    void InsertEmail(); //Prompts user for email information and adds it to linked list(s)
    void DeleteCommunication(string subject); //Deletes a communication having a given subject.
    Communication* SearchCommunication(string keyword); //Searches Inbox for a given Subject, will ask user for subject.
    void DisplayInbox();
};//End Inbox

/*=======================================================================================================================*/
//Normal Constructor
Inbox::Inbox(){
    Number_of_Comms = 0;
    NewestComm = NULL;
}

/*=======================================================================================================================*/
//Copy Constructor
/*It should be noted that CommTraveler and EmailTraveler travel through the object's pointers
    to acquire data. These pointers are not in any way related to the new Inbox being made.*/
Inbox::Inbox(const Inbox& object){
    Number_of_Comms = object.Number_of_Comms;

    //CommTraveler will travel through object's Comm Linked List to acquire data.
    Communication *CommTraveler = object.NewestComm;

    //Initial Setup for Comm loop
    Communication *TempComm = new Communication();
    //NULL node (not sure if this is necessary or not)
    TempComm->Subject = ""; TempComm->Number_of_Emails = 0;
    TempComm->previous = NULL; TempComm->next = NULL;

    //Temporarily sets head pointer to NULL node, will adjust after creation.
    NewestComm = TempComm;

    while(CommTraveler != NULL){

        Communication *newComm = new Communication();

        //Get/Set data
        newComm->Subject = CommTraveler->Subject;
        newComm->Number_of_Emails = CommTraveler->Number_of_Emails;

/*---------------------------------------------Start Email Linked List Setup---------------------------------------------*/

        //Email Traveler will travel through each email within CommTraveler to acquire data.
        Communication::Email *EmailTraveler = CommTraveler->NewestEmail;

        //Initial Setup for Email loop.
        Communication::Email *TempEmail = new Communication::Email();
        //NULL node (again, not sure if this is necessary or not)
        TempEmail->To = ""; TempEmail->From = ""; TempEmail->Message = "";
        TempEmail->Newer_Email = NULL; TempEmail->Older_Email = NULL;

        //Again, temporarily sets head pointer to NULL node, will adjust after creation.
        newComm->NewestEmail = TempEmail;

        while(EmailTraveler != NULL){

            Communication::Email *newEmail = new Communication::Email();

            //Get/Set data
            newEmail->To = EmailTraveler->To;
            newEmail->From = EmailTraveler->From;
            newEmail->Message = EmailTraveler->Message;

            //Assignment of pointers. Remember Older_Email is "*next" and Newer_Email is "*previous"
            TempEmail->Older_Email = newEmail; //Set the previous node's "*next" to current node.
            newEmail->Newer_Email = TempEmail; //Set current's "*previous" to previous node, or NULL node if first loop
            TempEmail = newEmail;              //Set previous node to current node.
//            newEmail = newEmail->Older_Email;

            EmailTraveler = EmailTraveler->Older_Email; //Progress to next email
        }
        //Adjust back end
        TempEmail->Older_Email = NULL;                           //Set last "*next" to NULL


        //Adjust front end
        if(newComm->NewestEmail->Older_Email != NULL){
            newComm->NewestEmail = newComm->NewestEmail->Older_Email;//Move head from NULL node to first node
            delete newComm->NewestEmail->Newer_Email;                //Delete initial NULL node;
            newComm->NewestEmail->Newer_Email = NULL;                //Set first "*previous" to NULL
        }
        else{
            delete newComm->NewestEmail;
            newComm->NewestEmail = NULL;
        }

/*----------------------------------------------End Email Linked List Setup----------------------------------------------*/

        //Assignment of pointers. For Communication nodes
        TempComm->next = newComm;
        newComm->previous = TempComm;
        TempComm = newComm;
//        newComm = newComm->next;

        CommTraveler = CommTraveler->next;//Progress to the next communication
    }

    //Adjust back end
    TempComm->next = NULL;//Set last "*next" to NULL

    //Adjust front end
    if(NewestComm->next != NULL){
        NewestComm = NewestComm->next;//Move head from NULL node to first node
        delete NewestComm->previous;  //Delete initial NULL node
        NewestComm->previous = NULL;  //Set first "*previous to NULL
    }
    else{
        delete NewestComm;
        NewestComm = NULL;
    }
}//End Copy Constructor

/*=======================================================================================================================*/
//Destructor
Inbox::~Inbox(){
    if(NewestComm != NULL){
        while(NewestComm->next!=NULL){
            //Delete emails within communication, if there exist any.
            if(NewestComm->NewestEmail != NULL){
                while(NewestComm->NewestEmail->Older_Email != NULL){
                    NewestComm->NewestEmail = NewestComm->NewestEmail->Older_Email;
                    delete NewestComm->NewestEmail->Newer_Email;
                }
                delete NewestComm->NewestEmail;
            }

            //Delete communication node
            NewestComm = NewestComm->next;
            delete NewestComm->previous;
        }
        delete NewestComm;
    }
    Number_of_Comms = 0;
}//End Destructor

/*=======================================================================================================================*/
//InsertEmail()
void Inbox::InsertEmail(){

    vector<string> ArrOfStrs; //"Array Of Strings"
    string UserInput;
    cout << "Enter the subject of your email. (Type \"done\" to finish)\n";
    do{
        getline(cin, UserInput);
        ArrOfStrs.push_back(UserInput);
    }while(UserInput != "done");

    Communication* SubjectGiven;
    for(int i = 0; i < ArrOfStrs.size()-1; i++){
        SubjectGiven = SearchCommunication(ArrOfStrs[i]);
        if(SubjectGiven == NULL){
            SubjectGiven = new Communication;
            SubjectGiven->Subject = ArrOfStrs[i];
            SubjectGiven->Number_of_Emails = 1;
            SubjectGiven->next = NewestComm;
            SubjectGiven->previous = NULL;
            SubjectGiven->NewestEmail = NULL;
            if(NewestComm != NULL){
                NewestComm->previous = SubjectGiven;
            }
            NewestComm = SubjectGiven;
            Number_of_Comms++;
        }
        else{
            //Increment number of Emails
            SubjectGiven->Number_of_Emails++;

            //Check if subject is already at front. If so, continue to next iteration of loop.
            if(NewestComm->Subject == SubjectGiven->Subject){
                continue;
            }
            //If not, adjust neighboring nodes' pointers...
            SubjectGiven->previous->next = SubjectGiven->next;
            if(SubjectGiven->next != NULL){
                SubjectGiven->next->previous = SubjectGiven->previous;
            }

            //...then move node to front.
            NewestComm->previous = SubjectGiven;
            SubjectGiven->next = NewestComm;
            SubjectGiven->previous = NULL;
            NewestComm = SubjectGiven;
        }
    }





}//End InsertEmail()

/*=======================================================================================================================*/
//SearchCommunication()
Inbox::Communication* Inbox::SearchCommunication(string keyword){
    if(NewestComm == NULL){
        return NULL;
    }
    Communication* commPointer = NewestComm;
    while(commPointer->Subject != keyword && commPointer->next != NULL){
        commPointer = commPointer->next;
    }
    if(commPointer->Subject == keyword && commPointer->next == NULL){
        return commPointer;
    }
    else if(commPointer->next == NULL){
        return NULL;
    }
    return commPointer;
}//End SearchCommunication()

/*=======================================================================================================================*/
//DeleteCommunication(string)
void Inbox::DeleteCommunication(string subject){
    Communication* target = SearchCommunication(subject);
    //Check for stupidity
    if(target == NULL){
        cout << "Could not find given subject for deletion.\n";
        return;
    }

    //Nullify data
    target->Subject = "";
    target->Number_of_Emails = 0;

    //Delete Email list
    if(target->NewestEmail != NULL){
        while(target->NewestEmail->Older_Email != NULL){
            target->NewestEmail = target->NewestEmail->Older_Email;
            delete target->NewestEmail->Newer_Email;
        }
        delete target->NewestEmail;
    }

    //Adjust Comm pointers
    if(target == NewestComm){
        NewestComm = NewestComm->next;
    }
    if(target->previous != NULL){
        target->previous->next = target->next;
    }
    if(target->next != NULL){
        target->next->previous = target->previous;
    }
    delete target;
    Number_of_Comms--;
    return;
}//End DeleteCommunication(string)

/*=======================================================================================================================*/
//DisplayInbox()
void Inbox::DisplayInbox(){
    if(NewestComm == NULL){
        cout << "Nothing to display.\n\n";
        return;
    }

    Communication *DisplayPointer;
    DisplayPointer = NewestComm;

    for(int i = 0; i < Number_of_Comms; i++){
        cout << DisplayPointer->Subject << " - " << DisplayPointer->Number_of_Emails << "\n";
        DisplayPointer = DisplayPointer->next;
    }

    return;
}//End DisplayInbox()

/*=======================================================================================================================*/
//Menu()
void Inbox::Menu(){
    string Selection;

    while(Selection !="Finish"){
      cout << "Enter a command: ";
      getline(cin, Selection);
      if(Selection == "Display"){
        DisplayInbox();
      }
      else if(Selection == "Insert"){
        InsertEmail();
      }
      else if(Selection == "Delete"){
        string delsubj;
        cout << "Enter the subject you want to delete: ";
        getline(cin, delsubj);
        DeleteCommunication(delsubj);
      }
      else if(Selection == "Finish"){
        string confirmation;
        cout << "Confirm Exit? (y/n)\n";
        getline(cin, confirmation);
        if(confirmation != "y"){
            Selection = "Not Exiting";
        }
      }
      else{
        cout << "Unrecognized command. Please read preconditions for commands.\n";
      }
    }
}//End Menu()

/*=======================================================================================================================*/
//main()
int main(){
    Inbox gmail;
    gmail.Menu();

    Inbox Copymail(gmail);
    Copymail.Menu();

    return 0;
}//End main()
/*======================================================END PROGRAM======================================================*/
