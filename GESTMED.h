#include <iostream>
#include <string>
using namespace std;




// Classe Date
class Date {
private:
    int jour;
    int mois;
    int annee;
    
 // Méthode privée pour valider une date
    bool estDateValide() const;
    
public:
// Constructeur
    Date(int j = 1, int m = 1, int a = 2000);
    
// Getters
    int getJour() const;
    int getMois() const;
    int getAnnee() const;

// Surcharge des opérateurs
    Date operator+(int jours) const;  // Ajoute des jours
    bool operator==(const Date& autre) const;  // Compare deux dates
    bool operator!=(const Date& autre) const;  // Compare deux dates
    
  // Méthode d'affichage
    void afficher() const;
};






// Classe Medecin
class Medecin {
private:
    string nom;
    string specialisation;
    int experience;  // en années
    
public:
// Constructeur
    Medecin(string n = "", string s = "", int exp = 0000);
// Getters
    string getNom() const;
    string getSpecialisation() const;
    int getExperience() const;
    
// Surcharge des opérateurs
    bool operator==(const Medecin& autre) const;  // Compare deux médecins
    
// Méthode d'affichage
    void afficher() const;
};





// Classe Patient
class Patient {
private:
    string nom;
    int age;
    char sexe;  // 'M' ou 'F'
    string numeroDossier;
    
public:
    // Constructeur
    Patient(string n = "", int a = 0, char s = 'M', string nd = "");
    
    // Getters
    string getNom() const;
    int getAge() const;
    char getSexe() const;
    string getNumeroDossier() const;
    
    // Surcharge des opérateurs
    bool operator==(const Patient& autre) const;  // Compare deux patients
    
    // Méthode d'affichage
    void afficher() const;
};






// Classe Consultation
class Consultation {
private:
    Medecin* medecin;
    Patient* patient;
    Date date;
    string diagnostic;
    
public:
// Constructeur
    Consultation(Medecin* m = nullptr, Patient* p = nullptr, 
                 Date d = Date(), string diag = "");
    
// Getters
    Medecin* getMedecin() const;
    Patient* getPatient() const;
    Date getDate() const;
    string getDiagnostic() const;
    
// Surcharge des opérateurs
    bool operator==(const Consultation& autre) const;  // Compare deux consultations
    
// Méthode d'affichage
    void afficher() const;
};
