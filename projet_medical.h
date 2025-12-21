#ifndef PROJET_MEDICAL_H
#define PROJET_MEDICAL_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

// ==================== CLASSE DATE ====================
class Date {
private:
    int jour;
    int mois;
    int annee;

    bool estDateValide() const;
    int joursDansMois() const;

public:
    // Constructeurs
    Date(int j = 1, int m = 1, int a = 2000);
    Date(const Date& autre);
    
    // Getters
    int getJour() const { return jour; }
    int getMois() const { return mois; }
    int getAnnee() const { return annee; }
    
    // Setters avec validation
    void setJour(int j);
    void setMois(int m);
    void setAnnee(int a);
    void setDate(int j, int m, int a);
    
    // Surcharge d'opérateurs
    Date operator+(int jours) const;
    bool operator==(const Date& autre) const;
    bool operator!=(const Date& autre) const;
    bool operator<(const Date& autre) const;
    bool operator>(const Date& autre) const;
    Date& operator=(const Date& autre);
    
    // Méthodes utilitaires
    bool estBissextile() const;
    int differenceJours(const Date& autre) const;
    std::string toString() const;
    bool estDansMemeMois(const Date& autre) const;
    
    // Surcharge de l'opérateur <<
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

// ==================== CLASSE MEDECIN ====================
class Medecin {
private:
    std::string nom;
    std::string specialisation;
    int experience; // en années

public:
    // Constructeurs
    Medecin(const std::string& n = "", const std::string& spec = "", int exp = 0);
    Medecin(const Medecin& autre);
    
    // Getters
    std::string getNom() const { return nom; }
    std::string getSpecialisation() const { return specialisation; }
    int getExperience() const { return experience; }
    
    // Setters
    void setNom(const std::string& n) { nom = n; }
    void setSpecialisation(const std::string& spec) { specialisation = spec; }
    void setExperience(int exp) { experience = exp; }
    
    // Surcharge d'opérateurs
    bool operator==(const Medecin& autre) const;
    bool operator!=(const Medecin& autre) const;
    Medecin& operator=(const Medecin& autre);
    
    // Méthodes utilitaires
    std::string toString() const;
    bool estSpecialiste(const std::string& specialite) const;
    
    // Surcharge de l'opérateur <<
    friend std::ostream& operator<<(std::ostream& os, const Medecin& medecin);
};

// ==================== CLASSE PATIENT ====================
class Patient {
private:
    std::string nom;
    int age;
    char sexe; // 'M' ou 'F'
    int numeroDossier;
    static int compteurDossiers; // pour générer des numéros uniques

public:
    // Constructeurs
    Patient(const std::string& n = "", int a = 0, char s = 'M');
    Patient(const Patient& autre);
    
    // Getters
    std::string getNom() const { return nom; }
    int getAge() const { return age; }
    char getSexe() const { return sexe; }
    int getNumeroDossier() const { return numeroDossier; }
    
    // Setters avec validation
    void setNom(const std::string& n) { nom = n; }
    void setAge(int a);
    void setSexe(char s);
    void setNumeroDossier(int num) { numeroDossier = num; }
    
    // Surcharge d'opérateurs
    bool operator==(const Patient& autre) const;
    bool operator!=(const Patient& autre) const;
    Patient& operator=(const Patient& autre);
    
    // Méthodes utilitaires
    std::string toString() const;
    bool estAgeSuperieurA(int ageLimite) const;
    
    // Surcharge de l'opérateur <<
    friend std::ostream& operator<<(std::ostream& os, const Patient& patient);
};

// ==================== CLASSE CONSULTATION ====================
class Consultation {
private:
    Medecin medecin;
    Patient patient;
    Date date;
    std::string diagnostic;

public:
    // Constructeurs
    Consultation(const Medecin& med, const Patient& pat, const Date& d, const std::string& diag = "");
    Consultation(const Consultation& autre);
    
    // Getters
    Medecin getMedecin() const { return medecin; }
    Patient getPatient() const { return patient; }
    Date getDate() const { return date; }
    std::string getDiagnostic() const { return diagnostic; }
    
    // Setters
    void setMedecin(const Medecin& med) { medecin = med; }
    void setPatient(const Patient& pat) { patient = pat; }
    void setDate(const Date& d) { date = d; }
    void setDiagnostic(const std::string& diag) { diagnostic = diag; }
    
    // Surcharge d'opérateurs
    bool operator==(const Consultation& autre) const;
    bool operator!=(const Consultation& autre) const;
    Consultation& operator=(const Consultation& autre);
    
    // Méthodes utilitaires
    std::string toString() const;
    bool estAvecMedecin(const Medecin& med) const;
    bool estAvecPatient(const Patient& pat) const;
    bool estALaDate(const Date& d) const;
    
    // Surcharge de l'opérateur <<
    friend std::ostream& operator<<(std::ostream& os, const Consultation& consultation);
};

// ==================== CLASSE GESTION CONSULTATIONS ====================
class GestionConsultations {
private:
    std::vector<Medecin> medecins;
    std::vector<Patient> patients;
    std::vector<Consultation> consultations;

public:
    // Constructeur et destructeur
    GestionConsultations();
    ~GestionConsultations();
    
    // Méthodes d'ajout
    void ajouterMedecin(const Medecin& medecin);
    void ajouterPatient(const Patient& patient);
    void ajouterConsultation(const Consultation& consultation);
    
    // Recherches
    std::vector<Medecin> rechercherMedecinsParSpecialisation(const std::string& specialisation) const;
    std::vector<Patient> rechercherPatientsParNom(const std::string& nom) const;
    std::vector<Consultation> rechercherConsultationsParMedecin(const Medecin& medecin) const;
    std::vector<Consultation> rechercherConsultationsParPatient(const Patient& patient) const;
    std::vector<Consultation> rechercherConsultationsParDate(const Date& date) const;
    
    // Fonctionnalités spécifiques (selon les points 5-14)
    // 5. Afficher tous les médecins ayant des consultations à une date donnée
    std::vector<Medecin> getMedecinsAvecConsultationsALaDate(const Date& date) const;
    
    // 6. Réserver une consultation avec vérification de disponibilité
    bool reserverConsultation(const Patient& patient, const Medecin& medecin, const Date& date, const std::string& diagnostic = "");
    
    // 7. Rechercher consultations pour un patient pendant une période
    std::vector<Consultation> getConsultationsPatientPeriode(const Patient& patient, const Date& debut, const Date& fin) const;
    
    // 8. Consultations d'un médecin pendant un mois
    std::vector<Consultation> getConsultationsMedecinMois(const Medecin& medecin, int mois, int annee) const;
    
    // 9. Patients ayant une consultation à une date spécifique
    std::vector<Patient> getPatientsAvecConsultationALaDate(const Date& date) const;
    
    // 10. Patients > 50 ans ayant consulté un cardiologue
    std::vector<Patient> getPatientsAge50PlusCardio() const;
    
    // 11. Modifier informations personnelles d'un patient
    bool modifierPatient(int numeroDossier, const std::string& nouveauNom, int nouvelAge, char nouveauSexe);
    
    // 12. Vérifier si un patient est déjà inscrit à une date avec un médecin
    bool estPatientInscrit(const Patient& patient, const Medecin& medecin, const Date& date) const;
    
    // 13. Nombre total de consultations par médecin
    std::vector<std::pair<Medecin, int>> getNombreConsultationsParMedecin() const;
    
    // 14. Consultation avec le plus de médecins (ici on adapte: consultation avec diagnostic complexe)
    Consultation getConsultationPlusComplexe() const;
    
    // 15. Statistiques
    void afficherStatistiques() const;
    
    // Getters
    const std::vector<Medecin>& getMedecins() const { return medecins; }
    const std::vector<Patient>& getPatients() const { return patients; }
    const std::vector<Consultation>& getConsultations() const { return consultations; }
    
    // Vérification de disponibilité (point 4)
    bool estMedecinDisponible(const Medecin& medecin, const Date& date) const;
    
    // Affichage
    void afficherTousMedecins() const;
    void afficherTousPatients() const;
    void afficherToutesConsultations() const;
};

#endif // PROJET_MEDICAL_H