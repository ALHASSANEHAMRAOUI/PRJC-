#include "projet_medical.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>

// ==================== INITIALISATION STATIQUE ====================
int Patient::compteurDossiers = 1000;

// ==================== IMPLEMENTATION CLASSE DATE ====================

// Constructeur avec validation
Date::Date(int j, int m, int a) : jour(1), mois(1), annee(2000) {
    setDate(j, m, a);
}

// Constructeur de copie
Date::Date(const Date& autre) : jour(autre.jour), mois(autre.mois), annee(autre.annee) {}

// Validation de date
bool Date::estDateValide() const {
    if (annee < 1900 || annee > 2100) return false;
    if (mois < 1 || mois > 12) return false;
    if (jour < 1 || jour > joursDansMois()) return false;
    return true;
}

// Nombre de jours dans le mois courant
int Date::joursDansMois() const {
    switch (mois) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return estBissextile() ? 29 : 28;
        default:
            return 0;
    }
}

// Setters avec validation
void Date::setJour(int j) {
    int temp = jour;
    jour = j;
    if (!estDateValide()) {
        jour = temp;
        throw std::invalid_argument("Jour invalide pour cette date");
    }
}

void Date::setMois(int m) {
    int temp = mois;
    mois = m;
    if (!estDateValide()) {
        mois = temp;
        throw std::invalid_argument("Mois invalide");
    }
}

void Date::setAnnee(int a) {
    int temp = annee;
    annee = a;
    if (!estDateValide()) {
        annee = temp;
        throw std::invalid_argument("Annee invalide");
    }
}

void Date::setDate(int j, int m, int a) {
    jour = j;
    mois = m;
    annee = a;
    if (!estDateValide()) {
        jour = 1; mois = 1; annee = 2000;
        throw std::invalid_argument("Date invalide");
    }
}

// Surcharge opérateur +
Date Date::operator+(int jours) const {
    Date resultat = *this;
    for (int i = 0; i < jours; i++) {
        resultat.jour++;
        if (resultat.jour > resultat.joursDansMois()) {
            resultat.jour = 1;
            resultat.mois++;
            if (resultat.mois > 12) {
                resultat.mois = 1;
                resultat.annee++;
            }
        }
    }
    return resultat;
}

// Surcharge opérateur ==
bool Date::operator==(const Date& autre) const {
    return (jour == autre.jour && mois == autre.mois && annee == autre.annee);
}

bool Date::operator!=(const Date& autre) const {
    return !(*this == autre);
}

bool Date::operator<(const Date& autre) const {
    if (annee != autre.annee) return annee < autre.annee;
    if (mois != autre.mois) return mois < autre.mois;
    return jour < autre.jour;
}

bool Date::operator>(const Date& autre) const {
    if (annee != autre.annee) return annee > autre.annee;
    if (mois != autre.mois) return mois > autre.mois;
    return jour > autre.jour;
}

Date& Date::operator=(const Date& autre) {
    if (this != &autre) {
        jour = autre.jour;
        mois = autre.mois;
        annee = autre.annee;
    }
    return *this;
}

// Vérification année bissextile
bool Date::estBissextile() const {
    return (annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0);
}

// Différence en jours entre deux dates
int Date::differenceJours(const Date& autre) const {
    // Simplification: différence en jours absolus
    int jours1 = annee * 365 + mois * 30 + jour;
    int jours2 = autre.annee * 365 + autre.mois * 30 + autre.jour;
    return std::abs(jours1 - jours2);
}

// Conversion en string
std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << jour << "/"
        << std::setfill('0') << std::setw(2) << mois << "/"
        << annee;
    return oss.str();
}

// Vérification si même mois
bool Date::estDansMemeMois(const Date& autre) const {
    return (mois == autre.mois && annee == autre.annee);
}

// Surcharge opérateur <<
std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.toString();
    return os;
}

// ==================== IMPLEMENTATION CLASSE MEDECIN ====================

Medecin::Medecin(const std::string& n, const std::string& spec, int exp) 
    : nom(n), specialisation(spec), experience(exp) {
    if (experience < 0) experience = 0;
}

Medecin::Medecin(const Medecin& autre) 
    : nom(autre.nom), specialisation(autre.specialisation), experience(autre.experience) {}

bool Medecin::operator==(const Medecin& autre) const {
    return (nom == autre.nom && specialisation == autre.specialisation);
}

bool Medecin::operator!=(const Medecin& autre) const {
    return !(*this == autre);
}

Medecin& Medecin::operator=(const Medecin& autre) {
    if (this != &autre) {
        nom = autre.nom;
        specialisation = autre.specialisation;
        experience = autre.experience;
    }
    return *this;
}

std::string Medecin::toString() const {
    return nom + " - " + specialisation + " (" + std::to_string(experience) + " ans d'expérience)";
}

bool Medecin::estSpecialiste(const std::string& specialite) const {
    return specialisation == specialite;
}

std::ostream& operator<<(std::ostream& os, const Medecin& medecin) {
    os << medecin.toString();
    return os;
}

// ==================== IMPLEMENTATION CLASSE PATIENT ====================

Patient::Patient(const std::string& n, int a, char s) 
    : nom(n), age(a), sexe(s) {
    numeroDossier = ++compteurDossiers;
    setAge(a);
    setSexe(s);
}

Patient::Patient(const Patient& autre) 
    : nom(autre.nom), age(autre.age), sexe(autre.sexe), numeroDossier(autre.numeroDossier) {}

void Patient::setAge(int a) {
    if (a < 0 || a > 150) {
        throw std::invalid_argument("Âge invalide");
    }
    age = a;
}

void Patient::setSexe(char s) {
    s = toupper(s);
    if (s != 'M' && s != 'F') {
        throw std::invalid_argument("Sexe doit être 'M' ou 'F'");
    }
    sexe = s;
}

bool Patient::operator==(const Patient& autre) const {
    return numeroDossier == autre.numeroDossier;
}

bool Patient::operator!=(const Patient& autre) const {
    return !(*this == autre);
}

Patient& Patient::operator=(const Patient& autre) {
    if (this != &autre) {
        nom = autre.nom;
        age = autre.age;
        sexe = autre.sexe;
        numeroDossier = autre.numeroDossier;
    }
    return *this;
}

std::string Patient::toString() const {
    std::ostringstream oss;
    oss << "Dossier #" << numeroDossier << ": " << nom 
        << " (" << age << " ans, " << (sexe == 'M' ? "Homme" : "Femme") << ")";
    return oss.str();
}

bool Patient::estAgeSuperieurA(int ageLimite) const {
    return age > ageLimite;
}

std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    os << patient.toString();
    return os;
}

// ==================== IMPLEMENTATION CLASSE CONSULTATION ====================

Consultation::Consultation(const Medecin& med, const Patient& pat, const Date& d, const std::string& diag)
    : medecin(med), patient(pat), date(d), diagnostic(diag) {}

Consultation::Consultation(const Consultation& autre)
    : medecin(autre.medecin), patient(autre.patient), date(autre.date), diagnostic(autre.diagnostic) {}

bool Consultation::operator==(const Consultation& autre) const {
    return (medecin == autre.medecin && patient == autre.patient && date == autre.date);
}

bool Consultation::operator!=(const Consultation& autre) const {
    return !(*this == autre);
}

Consultation& Consultation::operator=(const Consultation& autre) {
    if (this != &autre) {
        medecin = autre.medecin;
        patient = autre.patient;
        date = autre.date;
        diagnostic = autre.diagnostic;
    }
    return *this;
}

std::string Consultation::toString() const {
    std::ostringstream oss;
    oss << "Consultation du " << date << "\n"
        << "  Médecin: " << medecin.getNom() << "\n"
        << "  Patient: " << patient.getNom() << "\n"
        << "  Diagnostic: " << (diagnostic.empty() ? "Non précisé" : diagnostic);
    return oss.str();
}

bool Consultation::estAvecMedecin(const Medecin& med) const {
    return medecin == med;
}

bool Consultation::estAvecPatient(const Patient& pat) const {
    return patient == pat;
}

bool Consultation::estALaDate(const Date& d) const {
    return date == d;
}

std::ostream& operator<<(std::ostream& os, const Consultation& consultation) {
    os << consultation.toString();
    return os;
}

// ==================== IMPLEMENTATION CLASSE GESTION CONSULTATIONS ====================

GestionConsultations::GestionConsultations() {
    // Initialisation avec quelques données de test
    ajouterMedecin(Medecin("Dr. Martin", "Cardiologie", 15));
    ajouterMedecin(Medecin("Dr. Dubois", "Pédiatrie", 10));
    ajouterMedecin(Medecin("Dr. Bernard", "Neurologie", 20));
    ajouterMedecin(Medecin("Dr. Petit", "Cardiologie", 8));
    
    ajouterPatient(Patient("Jean Dupont", 45, 'M'));
    ajouterPatient(Patient("Marie Curie", 55, 'F'));
    ajouterPatient(Patient("Pierre Martin", 65, 'M'));
    ajouterPatient(Patient("Sophie Bernard", 35, 'F'));
    ajouterPatient(Patient("Robert Durand", 70, 'M'));
}

GestionConsultations::~GestionConsultations() {
    // Nettoyage automatique par les vecteurs
}

void GestionConsultations::ajouterMedecin(const Medecin& medecin) {
    medecins.push_back(medecin);
}

void GestionConsultations::ajouterPatient(const Patient& patient) {
    patients.push_back(patient);
}

void GestionConsultations::ajouterConsultation(const Consultation& consultation) {
    consultations.push_back(consultation);
}

std::vector<Medecin> GestionConsultations::rechercherMedecinsParSpecialisation(const std::string& specialisation) const {
    std::vector<Medecin> resultats;
    for (const auto& medecin : medecins) {
        if (medecin.getSpecialisation() == specialisation) {
            resultats.push_back(medecin);
        }
    }
    return resultats;
}

std::vector<Patient> GestionConsultations::rechercherPatientsParNom(const std::string& nom) const {
    std::vector<Patient> resultats;
    for (const auto& patient : patients) {
        if (patient.getNom().find(nom) != std::string::npos) {
            resultats.push_back(patient);
        }
    }
    return resultats;
}

std::vector<Consultation> GestionConsultations::rechercherConsultationsParMedecin(const Medecin& medecin) const {
    std::vector<Consultation> resultats;
    for (const auto& consultation : consultations) {
        if (consultation.estAvecMedecin(medecin)) {
            resultats.push_back(consultation);
        }
    }
    return resultats;
}

std::vector<Consultation> GestionConsultations::rechercherConsultationsParPatient(const Patient& patient) const {
    std::vector<Consultation> resultats;
    for (const auto& consultation : consultations) {
        if (consultation.estAvecPatient(patient)) {
            resultats.push_back(consultation);
        }
    }
    return resultats;
}

std::vector<Consultation> GestionConsultations::rechercherConsultationsParDate(const Date& date) const {
    std::vector<Consultation> resultats;
    for (const auto& consultation : consultations) {
        if (consultation.estALaDate(date)) {
            resultats.push_back(consultation);
        }
    }
    return resultats;
}

// 5. Médecins avec consultations à une date donnée
std::vector<Medecin> GestionConsultations::getMedecinsAvecConsultationsALaDate(const Date& date) const {
    std::vector<Medecin> resultats;
    for (const auto& consultation : consultations) {
        if (consultation.estALaDate(date)) {
            // Éviter les doublons
            if (std::find(resultats.begin(), resultats.end(), consultation.getMedecin()) == resultats.end()) {
                resultats.push_back(consultation.getMedecin());
            }
        }
    }
    return resultats;
}

// 6. Réserver une consultation avec vérification de disponibilité
bool GestionConsultations::reserverConsultation(const Patient& patient, const Medecin& medecin, 
                                               const Date& date, const std::string& diagnostic) {
    // Vérifier si le médecin est disponible
    if (!estMedecinDisponible(medecin, date)) {
        std::cout << "Le médecin n'est pas disponible à cette date." << std::endl;
        return false;
    }
    
    // Vérifier si le patient n'a pas déjà une consultation à cette date
    for (const auto& consultation : consultations) {
        if (consultation.estAvecPatient(patient) && consultation.estALaDate(date)) {
            std::cout << "Le patient a déjà une consultation à cette date." << std::endl;
            return false;
        }
    }
    
    // Créer et ajouter la consultation
    Consultation nouvelleConsultation(medecin, patient, date, diagnostic);
    ajouterConsultation(nouvelleConsultation);
    std::cout << "Consultation réservée avec succès!" << std::endl;
    return true;
}

// 7. Consultations d'un patient pendant une période
std::vector<Consultation> GestionConsultations::getConsultationsPatientPeriode(const Patient& patient, 
                                                                              const Date& debut, const Date& fin) const {
    std::vector<Consultation> resultats;
    for (const auto& consultation : consultations) {
        if (consultation.estAvecPatient(patient) && 
            !(consultation.getDate() < debut) && 
            !(consultation.getDate() > fin)) {
            resultats.push_back(consultation);
        }
    }
    return resultats;
}

// 8. Consultations d'un médecin pendant un mois
std::vector<Consultation> GestionConsultations::getConsultationsMedecinMois(const Medecin& medecin, 
                                                                           int mois, int annee) const {
    std::vector<Consultation> resultats;
    for (const auto& consultation : consultations) {
        if (consultation.estAvecMedecin(medecin)) {
            Date date = consultation.getDate();
            if (date.getMois() == mois && date.getAnnee() == annee) {
                resultats.push_back(consultation);
            }
        }
    }
    return resultats;
}

// 9. Patients ayant une consultation à une date spécifique
std::vector<Patient> GestionConsultations::getPatientsAvecConsultationALaDate(const Date& date) const {
    std::vector<Patient> resultats;
    for (const auto& consultation : consultations) {
        if (consultation.estALaDate(date)) {
            // Éviter les doublons
            if (std::find(resultats.begin(), resultats.end(), consultation.getPatient()) == resultats.end()) {
                resultats.push_back(consultation.getPatient());
            }
        }
    }
    return resultats;
}

// 10. Patients > 50 ans ayant consulté un cardiologue
std::vector<Patient> GestionConsultations::getPatientsAge50PlusCardio() const {
    std::vector<Patient> resultats;
    for (const auto& consultation : consultations) {
        if (consultation.getMedecin().getSpecialisation() == "Cardiologie" &&
            consultation.getPatient().estAgeSuperieurA(50)) {
            // Éviter les doublons
            if (std::find(resultats.begin(), resultats.end(), consultation.getPatient()) == resultats.end()) {
                resultats.push_back(consultation.getPatient());
            }
        }
    }
    return resultats;
}

// 11. Modifier informations personnelles d'un patient
bool GestionConsultations::modifierPatient(int numeroDossier, const std::string& nouveauNom, 
                                          int nouvelAge, char nouveauSexe) {
    for (auto& patient : patients) {
        if (patient.getNumeroDossier() == numeroDossier) {
            try {
                patient.setNom(nouveauNom);
                patient.setAge(nouvelAge);
                patient.setSexe(nouveauSexe);
                return true;
            } catch (const std::invalid_argument& e) {
                std::cerr << "Erreur: " << e.what() << std::endl;
                return false;
            }
        }
    }
    std::cout << "Patient non trouvé." << std::endl;
    return false;
}

// 12. Vérifier si un patient est déjà inscrit
bool GestionConsultations::estPatientInscrit(const Patient& patient, const Medecin& medecin, 
                                            const Date& date) const {
    for (const auto& consultation : consultations) {
        if (consultation.estAvecPatient(patient) && 
            consultation.estAvecMedecin(medecin) && 
            consultation.estALaDate(date)) {
            return true;
        }
    }
    return false;
}

// 13. Nombre total de consultations par médecin
std::vector<std::pair<Medecin, int>> GestionConsultations::getNombreConsultationsParMedecin() const {
    std::vector<std::pair<Medecin, int>> resultats;
    for (const auto& medecin : medecins) {
        int count = 0;
        for (const auto& consultation : consultations) {
            if (consultation.estAvecMedecin(medecin)) {
                count++;
            }
        }
        resultats.push_back(std::make_pair(medecin, count));
    }
    return resultats;
}

// 14. Consultation la plus complexe (celle avec le diagnostic le plus long)
Consultation GestionConsultations::getConsultationPlusComplexe() const {
    if (consultations.empty()) {
        throw std::runtime_error("Aucune consultation disponible");
    }
    
    Consultation plusComplexe = consultations[0];
    for (const auto& consultation : consultations) {
        if (consultation.getDiagnostic().length() > plusComplexe.getDiagnostic().length()) {
            plusComplexe = consultation;
        }
    }
    return plusComplexe;
}

// 15. Statistiques
void GestionConsultations::afficherStatistiques() const {
    std::cout << "\n=== STATISTIQUES ===" << std::endl;
    std::cout << "Nombre total de médecins: " << medecins.size() << std::endl;
    std::cout << "Nombre total de patients: " << patients.size() << std::endl;
    std::cout << "Nombre total de consultations: " << consultations.size() << std::endl;
    
    auto consultationsParMedecin = getNombreConsultationsParMedecin();
    std::cout << "\nConsultations par médecin:" << std::endl;
    for (const auto& pair : consultationsParMedecin) {
        std::cout << "  " << pair.first.getNom() << ": " << pair.second << " consultation(s)" << std::endl;
    }
}

// Vérification de disponibilité d'un médecin
bool GestionConsultations::estMedecinDisponible(const Medecin& medecin, const Date& date) const {
    for (const auto& consultation : consultations) {
        if (consultation.estAvecMedecin(medecin) && consultation.estALaDate(date)) {
            return false; // Médecin déjà occupé à cette date
        }
    }
    return true; // Médecin disponible
}

void GestionConsultations::afficherTousMedecins() const {
    std::cout << "\n=== LISTE DES MEDECINS ===" << std::endl;
    for (size_t i = 0; i < medecins.size(); i++) {
        std::cout << i+1 << ". " << medecins[i] << std::endl;
    }
}

void GestionConsultations::afficherTousPatients() const {
    std::cout << "\n=== LISTE DES PATIENTS ===" << std::endl;
    for (size_t i = 0; i < patients.size(); i++) {
        std::cout << i+1 << ". " << patients[i] << std::endl;
    }
}

void GestionConsultations::afficherToutesConsultations() const {
    std::cout << "\n=== LISTE DES CONSULTATIONS ===" << std::endl;
    for (size_t i = 0; i < consultations.size(); i++) {
        std::cout << i+1 << ". " << consultations[i] << "\n" << std::endl;
    }
}