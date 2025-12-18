#include "GestionMedicale.h"
#include <iostream>


// Constructeur de Date
Date::Date(int j, int m, int a) : jour(j), mois(m), annee(a) {
// Si la date n'est pas valide, on met une date par défaut
    if (!estDateValide()) {
        jour = 1;
        mois = 1;
        annee = 2000;
    }
}

// Vérifie si la date est valide
bool Date::estDateValide() const {
    if (annee < 1900 || annee > 2100) return false;
    if (mois < 1 || mois > 12) return false;
    
// Vérification des jours selon le mois
    int joursDansMois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
// Gestion des années bissextiles
    if (mois == 2) {
        bool bissextile = (annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0);
        if (bissextile && jour <= 29) return true;
    }
    
    return (jour >= 1 && jour <= joursDansMois[mois - 1]);
}

// Getters
int Date::getJour() const { return jour; }
int Date::getMois() const { return mois; }
int Date::getAnnee() const { return annee; }

// Opérateur + pour ajouter des jours
Date Date::operator+(int jours) const {
    Date nouvelleDate = *this;
// Version simplifiée (pour un vrai projet, utiliser une bibliothèque de dates)
    nouvelleDate.jour += jours;
    
// Gestion du dépassement (simplifiée)
    while (nouvelleDate.jour > 30) {
        nouvelleDate.jour -= 30;
        nouvelleDate.mois++;
        if (nouvelleDate.mois > 12) {
            nouvelleDate.mois = 1;
            nouvelleDate.annee++;
        }
    }
    
    return nouvelleDate;
}

// Opérateur == pour comparer deux dates
bool Date::operator==(const Date& autre) const {
    return (jour == autre.jour && mois == autre.mois && annee == autre.annee);
}

// Opérateur != pour comparer deux dates
bool Date::operator!=(const Date& autre) const {
    return !(*this == autre);
}

// Affichage de la date
void Date::afficher() const {
    std::cout << jour << "/" << mois << "/" << annee;
}






// Constructeur de Patient
Patient::Patient(std::string n, int a, char s, std::string nd)
    : nom(n), age(a), sexe(s), numeroDossier(nd) {
    // Validation du sexe
    if (sexe != 'M' && sexe != 'F') {
        sexe = 'M';
    }
}

// Getters
std::string Patient::getNom() const { return nom; }
int Patient::getAge() const { return age; }
char Patient::getSexe() const { return sexe; }
std::string Patient::getNumeroDossier() const { return numeroDossier; }

// Opérateur == pour comparer deux patients
bool Patient::operator==(const Patient& autre) const {
    return (nom == autre.nom && 
            age == autre.age && 
            sexe == autre.sexe && 
            numeroDossier == autre.numeroDossier);
}

// Affichage du patient
void Patient::afficher() const {
    std::cout << nom << " (" << age << " ans, " 
              << (sexe == 'M' ? "Homme" : "Femme") 
              << ") - Dossier: " << numeroDossier;
}






// Constructeur de Consultation
Consultation::Consultation(Medecin* m, Patient* p, Date d, std::string diag)
    : medecin(m), patient(p), date(d), diagnostic(diag) {}

// Getters
Medecin* Consultation::getMedecin() const { return medecin; }
Patient* Consultation::getPatient() const { return patient; }
Date Consultation::getDate() const { return date; }
std::string Consultation::getDiagnostic() const { return diagnostic; }

// Opérateur == pour comparer deux consultations
bool Consultation::operator==(const Consultation& autre) const {
    // Vérifie si les pointeurs pointent vers les mêmes objets
    bool memeMedecin = (medecin == autre.medecin);
    bool memePatient = (patient == autre.patient);
    bool memeDate = (date == autre.date);
    
    return (memeMedecin && memePatient && memeDate);
}

// Affichage de la consultation
void Consultation::afficher() const {
    std::cout << "=== Consultation ===" << std::endl;
    std::cout << "Date: ";
    date.afficher();
    std::cout << std::endl;
    
    std::cout << "Medecin: ";
    if (medecin) {
        medecin->afficher();
    } else {
        std::cout << "Non specifie";
    }
    std::cout << std::endl;
    
    std::cout << "Patient: ";
    if (patient) {
        patient->afficher();
    } else {
        std::cout << "Non specifie";
    }
    std::cout << std::endl;
    
    std::cout << "Diagnostic: " << diagnostic << std::endl;
    std::cout << "===================" << std::endl;
}
